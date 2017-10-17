#ifndef _CPU_H
#define _CPU_H

#include "systemc.h"
#include <functional>

SC_MODULE(CPU)
{
    using ActionCallback = std::function<void(void)>; 

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

    void bus_write(int32_t addr, int32_t data);
    int32_t  bus_read(int32_t addr);
    
    void setAction(ActionCallback callback);
private:
    ActionCallback callback;
};


#endif
