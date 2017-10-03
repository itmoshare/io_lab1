#ifndef _BUS_H
#define _BUS_H

#include "systemc.h"

SC_MODULE(Bus)
{
    sc_in<bool> clk_i;

    // CPU
    // адрес обращения, 32 бита
    sc_in<int32_t> cpu_addr_bo;
    // данные записи от ведущего к ведомому, 32 бита
    sc_in<int32_t> cpu_data_bo;
    // данные чтения от ведомого к ведущему, 32 бита
    sc_out<int32_t> cpu_data_bi;
    // сигнал операции чтения
    sc_in<bool> cpu_rd_o;
    // сигнал операции записи
    sc_in<bool> cpu_wr_o;

    // адрес обращения, 32 бита
    sc_out<int32_t> addr_bo;
    // данные записи от ведущего к ведомому, 32 бита
    sc_out<int32_t> data_bo;
    // данные чтения от ведомого к ведущему, 32 бита
    sc_in<int32_t> data_bi;

    // сигнал операции чтения
    sc_out<bool> timer1_rd_o;
    // сигнал операции записи
    sc_out<bool> timer1_wr_o;

    // сигнал операции чтения
    sc_out<bool> timer2_rd_o;
    // сигнал операции записи
    sc_out<bool> timer2_wr_o;

    // сигнал операции чтения
    sc_out<bool> oc_rd_o;
    // сигнал операции записи
    sc_out<bool> oc_wr_o;

    SC_HAS_PROCESS(Bus);
    
    Bus(sc_module_name nm);
    ~Bus();
    
private:
    void handle();
    void set(bool t1_r, bool t1_w, bool t2_r, bool t2_w, bool oc_r, bool oc_w);
};


#endif