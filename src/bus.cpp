#include "bus.h"

Bus::Bus(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    cpu_addr_bo("cpu_addr_bo"),
    cpu_data_bo("cpu_data_bo"),
    cpu_data_bi("cpu_data_bi"),
    cpu_rd_o("cpu_rd_o"),
    cpu_wr_o("cpu_wr_o"),
    addr_bo("addr_bo"),
    data_bo("data_bo"),
    data_bi("data_bi"),
    timer1_rd_o("timer1_rd_o"),
    timer1_wr_o("timer1_wr_o"),
    timer2_rd_o("timer2_rd_o"),
    timer2_wr_o("timer2_wr_o"),
    oc_rd_o("oc_rd_o"),
    oc_wr_o("oc_wr_o")
{
    addr_bo.initialize(0);
    data_bo.initialize(0);
    timer1_rd_o.initialize(false);
    timer1_wr_o.initialize(false);

    timer2_rd_o.initialize(false);
    timer2_wr_o.initialize(false);

    oc_rd_o.initialize(false);
    oc_wr_o.initialize(false);

    SC_METHOD(handle);
    sensitive << clk_i.pos();
}

Bus::~Bus()
{
}

void Bus::handle()
{
    addr_bo.write(cpu_addr_bo.read());
    data_bo.write(cpu_data_bo.read());

    int32_t addr = cpu_addr_bo.read();
    if (addr > 0 && addr < 0x0000000C)
    {
        set(cpu_rd_o.read(), cpu_wr_o.read(), false, false, false, false);
    }
    if (addr >= 0x0000000C && addr < 0x00000018)
    {
        set(false, false, cpu_rd_o.read(), cpu_wr_o.read(), false, false);
    }
    if (addr >= 0x00000018 && addr < 0x00000020)
    {
        set(false, false, false, false, cpu_rd_o.read(), cpu_wr_o.read());
    }
}

void Bus::set(bool t1_r, bool t1_w, bool t2_r, bool t2_w, bool oc_r, bool oc_w)
{
    timer1_rd_o.write(t1_r);
    timer1_wr_o.write(t1_w);
    timer2_rd_o.write(t2_r);
    timer2_wr_o.write(t2_w);
    oc_rd_o.write(oc_r);
    oc_wr_o.write(oc_w);
}

