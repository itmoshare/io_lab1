#ifndef _OC_H
#define _OC_H

#include "systemc.h"

SC_MODULE(Oc)
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

    sc_in<int32_t> timer1_in;
    sc_in<int32_t> timer2_in;
    sc_out<bool> outs;

    SC_HAS_PROCESS(Oc);
    
    Oc(sc_module_name nm, int32_t addr_offset);
    ~Oc();

private:
    int32_t addr_offset;
    int32_t last_mode;

    int32_t occonf;
    int32_t ocr;

    void handle();
    void handle_write();
    void handle_tick();
};


#endif