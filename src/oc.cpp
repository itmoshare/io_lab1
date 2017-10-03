#include "oc.h"

using namespace std;

Oc::Oc(sc_module_name nm)
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
}

Oc::~Oc()
{

}