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

    SC_METHOD(bus_write);
    sensitive << clk_i.pos();

    SC_METHOD(bus_read);
    sensitive << clk_i.pos();
}

Bus::~Bus()
{
}

void Bus::bus_read()
{
    // if(wr_i.read())
    //     mem[addr_bi.read()] = data_bi.read();
}

void Bus::bus_write()
{
    // if(rd_i.read())
    //     data_bo.write(mem[addr_bi.read()]);
}