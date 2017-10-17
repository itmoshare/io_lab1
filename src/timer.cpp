#include "timer.h"
#include <iostream>

using namespace std;

Timer::Timer(sc_module_name nm, int32_t addr_offset)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bi("addr_bi"),
    data_bi("data_bi"),
    data_bo("data_bo"),
    rd_i("rd_i"),
    wr_i("wr_i"),
    out("out")
{
    data_bo.initialize(0);
    out.initialize(0);

    this->addr_offset = addr_offset;

    SC_METHOD(handle);
    sensitive << clk_i.pos();
}

Timer::~Timer()
{

}

void Timer::handle()
{
    if (wr_i.read())
        handle_write();
    handle_tick();
}

void Timer::handle_write()
{
    const auto local_offset = addr_bi.read() - addr_offset;
    switch (local_offset)
    {
        case 0:
            tmr = data_bi.read();
            break;
        case 4:
            tval = data_bi.read();
            break;
        case 8:
            tconf = data_bi.read();
            break; 
    }
}

void Timer::handle_tick()
{
    bool increment = !(tconf & 0x1);
    bool stop = !(tconf & 0x2);
    if (!stop)
    {
        if (increment)
        {
            tval++;
            if (tval > tmr)
                tval = 0;
        }
        else
        {
            tval--;
            if (tval < 0)
                tval = tmr;
        }
    }
    out.write(tval);
}
