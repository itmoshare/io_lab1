#ifndef _TIMER_H
#define _TIMER_H

#include "systemc.h"

SC_MODULE(Timer)
{
    sc_in<bool>  clk_i;
    
    // адрес обращения, 32 бита
    sc_in<int32_t> addr_bi;
    // данные записи от ведущего к ведомому, 32 бита
    sc_in<int32_t> data_bi;
    // данные чтения от ведомого к ведущему, 32 бита
    sc_out<int32_t> data_bo;
    // сигнал операции чтения
    sc_in<bool> rd_i;
    // сигнал операции записи
    sc_in<bool> wr_i;

    sc_out<int32_t> out;
    
    SC_HAS_PROCESS(Timer);
    
    Timer(sc_module_name nm, int addr_offset);
    ~Timer();

private:
    int addr_offset;

    int tmr = 0;
    int tval = 0;
    int tconf = 0;

    void handle();
    void handle_write();
    void handle_tick();
};


#endif
