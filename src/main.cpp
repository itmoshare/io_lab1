#include "cpu.h"
#include "bus.h"
#include "timer.h"
#include "oc.h"

static CPU cpu("cpu");

static sc_clock clk("clk", sc_time(10, SC_NS));
// CPU to Bus
static sc_signal<int32_t> cpu_addr_bo;
static sc_signal<int32_t> cpu_data_cpu_bo;
static sc_signal<int32_t> cpu_data_cpu_bi;
static sc_signal<bool> cpu_wr;
static sc_signal<bool> cpu_rd;

// Bus to timers
static sc_signal<int32_t> timers_addr;
static sc_signal<int32_t> timers_data_bus_bo;
static sc_signal<int32_t> timers_data_bus_bi;

static sc_signal<bool> timer1_wr;
static sc_signal<bool> timer1_rd;

static sc_signal<bool> timer2_wr;
static sc_signal<bool> timer2_rd;

static sc_signal<bool> oc_wr;
static sc_signal<bool> oc_rd;

// Timers to oc
static sc_signal<int32_t> timer1_out;
static sc_signal<int32_t> timer2_out;

sc_signal<bool> oc_outs;

// Timer 1 (dec)
void doTestTimer1(sc_trace_file * wf)
{
    sc_trace(wf, clk, "clk");
    sc_trace(wf, cpu_addr_bo, "cpu_addr_bo");
    sc_trace(wf, cpu_data_cpu_bo, "cpu_data_cpu_bo");
    sc_trace(wf, cpu_wr, "cpu_wr");

    sc_trace(wf, timers_addr, "timers_addr");
    sc_trace(wf, timers_data_bus_bo, "timers_data_bus_bo");
    sc_trace(wf, timer1_wr, "timer1_wr");
    sc_trace(wf, timer1_out, "timer1_out");

    cpu.setAction([&]{
        cpu.bus_write(0x0, 0x2);
        cpu.bus_write(0x8, 0x3);
        for (int i = 0; i < 5; i++, wait());
    });
}

// Timer 2 (inc)
void doTestTimer2(sc_trace_file * wf)
{
    sc_trace(wf, clk, "clk");
    sc_trace(wf, cpu_addr_bo, "cpu_addr_bo");
    sc_trace(wf, cpu_data_cpu_bo, "cpu_data_cpu_bo");
    sc_trace(wf, cpu_wr, "cpu_wr");

    sc_trace(wf, timers_addr, "timers_addr");
    sc_trace(wf, timers_data_bus_bo, "timers_data_bus_bo");
    sc_trace(wf, timer2_wr, "timer2_wr");
    sc_trace(wf, timer2_out, "timer2_out");

    cpu.setAction([&]{
        cpu.bus_write(0xC, 0x3);
        cpu.bus_write(0x14, 0x2);
        for (int i = 0; i < 5; i++, wait());
    });
}

// Output Compare mode 1
void doOutputCompareTest1(sc_trace_file * wf)
{
    sc_trace(wf, clk, "clk");
    sc_trace(wf, cpu_addr_bo, "cpu_addr_bo");
    sc_trace(wf, cpu_data_cpu_bo, "cpu_data_cpu_bo");
    sc_trace(wf, cpu_wr, "cpu_wr");

    sc_trace(wf, timer1_out, "timer1_out");
    sc_trace(wf, timer2_out, "timer2_out");
    sc_trace(wf, oc_outs, "oc_outs");

    cpu.setAction([&]{
        // Output Compare
        cpu.bus_write(0x1C, 0x2);
        cpu.bus_write(0x18, 0x3);
        // Timer 1 start
        cpu.bus_write(0x0, 0x6);
        cpu.bus_write(0x8, 0x2);
        // Timer 2 start
        cpu.bus_write(0xC, 0x5);
        cpu.bus_write(0x14, 0x2);
        for (int i = 0; i < 5; i++, wait());
    });
}

void doTaskTest(sc_trace_file * wf, int period)
{
	sc_trace(wf, clk, "clk");
	
	sc_trace(wf, oc_outs, "oc_outs");
	
	cpu.setAction([&]{
        // Output Compare
		cpu.bus_write(0x18, period / 2);
        cpu.bus_write(0x1C, 0x4);
        // Timer 1 start
        cpu.bus_write(0x0, period);
        cpu.bus_write(0x8, 0x2);
        for (int i = 0; i < 10; i++, wait());
    });
}

int32_t sc_main(int32_t argc, char* argv[])
{
	int period = 0;
	if (argc != 2)
	{
		cout << "Invalid args count" << endl;
		return 1;
	} 
	else 
	{
		period = atoi(argv[1]);
		if (perion % 2 != 0)
		{
			cout << "Period must be even" << endl;
			return 2;
		}
	}
	
    Bus bus("bus");
    Timer timer1("timer1", 0);
    Timer timer2("timer2", 0x0000000C);
    Oc oc("oc", 0x00000018);
    
    // CPU to Bus
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
    timer1.out(timer1_out);
    timer2.out(timer2_out);

    oc.timer1_in(timer1_out);
    oc.timer2_in(timer2_out);

    oc.outs(oc_outs);

    sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    //doTestTimer1(wf);
    //doTestTimer2(wf);
    //doOutputCompareTest1(wf);
	doTaskTest(wf, period);
	
    sc_start();
 
    sc_close_vcd_trace_file(wf);
    
    return(0);
}
