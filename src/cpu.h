#ifndef _CPU_H
#define _CPU_H

#include "systemc.h"

SC_MODULE(CPU)
{
    sc_in<bool>  clk_i;
    
    // CPU
    // адрес обращения, 32 бита
    sc_out<int32_t> addr_bo;
    // данные записи от ведущего к ведомому, 32 бита
    sc_out<int32_t> data_bo;
    // данные чтения от ведомого к ведущему, 32 бита
    sc_in<int32_t> data_bi;
    // сигнал операции чтения
    sc_out<bool> rd_o;
    // сигнал операции записи
    sc_out<bool> wr_o;
    
    SC_HAS_PROCESS(CPU);
    
    CPU(sc_module_name nm);
    ~CPU();
    
    void mainThread();
private:

    void bus_write(int addr, int data);
    int  bus_read(int addr);

};


#endif
