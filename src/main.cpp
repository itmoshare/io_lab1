#include "cpu.h"
#include "bus.h"
#include "timer.h"
#include "oc.h"

int sc_main(int argc, char* argv[])
{
    
    CPU cpu("cpu");
    Bus bus("bus");
    Timer timer1("timer1", 0);
    Timer timer2("timer2", 0x0000000C);
    Oc oc("oc");
    
    sc_clock clk("clk", sc_time(10, SC_NS));

    // CPU to Bus
    sc_signal<int> cpu_addr_bo;
    sc_signal<int> cpu_data_cpu_bo;
    sc_signal<int> cpu_data_cpu_bi;
    sc_signal<bool> cpu_wr;
    sc_signal<bool> cpu_rd;
    
    cpu.clk_i(clk);
    cpu.addr_bo(cpu_addr_bo);
    cpu.data_bo(cpu_data_cpu_bo);
    cpu.data_bi(cpu_data_cpu_bi);
    cpu.rd_o(cpu_rd);
    cpu.wr_o(cpu_wr);
    
    bus.clk_i(clk);
    bus.cpu_addr_bo(cpu_addr_bo);
    bus.cpu_data_bo(cpu_data_cpu_bo);
    bus.cpu_data_bi(cpu_data_cpu_bi);
    bus.cpu_wr_o(cpu_wr);
    bus.cpu_rd_o(cpu_rd);
    
    // Bus to timers
    sc_signal<int> timers_addr;
    sc_signal<int> timers_data_bus_bo;
    sc_signal<int> timers_data_bus_bi;

    sc_signal<bool> timer1_wr;
    sc_signal<bool> timer1_rd;

    sc_signal<bool> timer2_wr;
    sc_signal<bool> timer2_rd;

    sc_signal<bool> oc_wr;
    sc_signal<bool> oc_rd;

    bus.addr_bo(timers_addr);
    bus.data_bo(timers_data_bus_bo);
    bus.data_bi(timers_data_bus_bi);
    bus.timer1_rd_o(timer1_rd);
    bus.timer1_wr_o(timer1_wr);
    bus.timer2_wr_o(timer2_wr);
    bus.timer2_rd_o(timer2_rd);
    bus.oc_wr_o(oc_wr);
    bus.oc_rd_o(oc_rd);

    sc_signal<int32_t> timer1_data_bo;
    timer1.clk_i(clk);
    timer1.addr_bi(timers_addr);
    timer1.data_bi(timers_data_bus_bo);
    timer1.data_bo(timer1_data_bo);
    timer1.rd_i(timer1_rd);
    timer1.wr_i(timer1_wr);

    sc_signal<int32_t> timer2_data_bo;
    timer2.clk_i(clk);
    timer2.addr_bi(timers_addr);
    timer2.data_bi(timers_data_bus_bo);
    timer2.data_bo(timer2_data_bo);
    timer2.rd_i(timer2_rd);
    timer2.wr_i(timer2_wr);

    sc_signal<int32_t> oc_data_bo;
    oc.clk_i(clk);
    oc.addr_bi(timers_addr);
    oc.data_bi(timers_data_bus_bo);
    oc.data_bo(oc_data_bo);
    oc.rd_i(oc_rd);
    oc.wr_i(oc_wr);

    // Timers to oc
    sc_signal<int> timer1_out;
    sc_signal<int> timer2_out;

    timer1.out(timer1_out);
    timer2.out(timer2_out);

    oc.timer1_in(timer1_out);
    oc.timer2_in(timer2_out);

    sc_signal<bool> oc_outs;
    oc.outs(oc_outs);

    // sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    // sc_trace(wf, clk, "clk");
    // sc_trace(wf, addr, "addr_bo");
    // sc_trace(wf, data_cpu_bi, "data_bi");
    // sc_trace(wf, data_cpu_bo, "data_bo");
    // sc_trace(wf, wr, "wr");
    // sc_trace(wf, rd, "rd");
    // sc_trace(wf, rd, "rd");

    sc_start();
 
    // sc_close_vcd_trace_file(wf);
    
    return(0);
    
}
