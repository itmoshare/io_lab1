#include "timer.h"

using namespace std;

Timer::Timer(sc_module_name nm)
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
}

Timer::~Timer()
{

}