#include "oc.h"

using namespace std;

Oc::Oc(sc_module_name nm, int32_t addr_offset)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bi("addr_bi"),
    data_bi("data_bi"),
    data_bo("data_bo"),
    rd_i("rd_i"),
    wr_i("wr_i"),
    timer1_in("timer1_in"),
    timer2_in("timer2_in"),
    outs("outs")
{
    data_bo.initialize(0);
    outs.initialize(false);

    this->addr_offset = addr_offset;

    SC_METHOD(handle);
    sensitive << clk_i.pos();
}

Oc::~Oc()
{

}

void Oc::handle()
{
    if (wr_i.read())
        handle_write();
    handle_tick();
}

void Oc::handle_write()
{
    const auto local_offset = addr_bi.read() - addr_offset;
    switch (local_offset)
    {
        case 0:
            occonf = data_bi.read();
            break;
        case 4:
            ocr = data_bi.read();
            break;
    }
}

void Oc::handle_tick()
{
    const auto mode = occonf & 0x7;
    const auto bit3 = occonf & 0x8;
    int32_t timer = bit3 == 0 ? timer1_in.read() : timer2_in.read();
    switch (mode)
    {
        case 0:
            break;
        case 1:
            if (last_mode != mode)
                outs.write(false);
            if (timer == ocr)
                outs.write(true);
            break;
        case 2:
            if (last_mode != mode)
                outs.write(true);
            if (timer == ocr)
                outs.write(false);
            break;
        case 3:
            if (last_mode != mode)
                outs.write(false);
            if (timer == ocr)
                outs.write(!outs.read());
            break;
        case 4:
            if (last_mode != mode)
                outs.write(false);
            if (timer == ocr)
                outs.write(true);
            if (timer > ocr)
                outs.write(false);
            break;
        case 5:
            if (last_mode != mode)
                outs.write(true);
            if (timer == ocr)
                outs.write(false);
            if (timer > ocr)
                outs.write(true);
            break;
    }
    last_mode = mode;
}