/**
 * @file
 * @copyright  Copyright 2016 GNSS Sensor Ltd. All right reserved.
 * @author     Sergey Khabarov - sergeykhbr@gmail.com
 * @brief      Branch predictor.
 */

#ifndef __DEBUGGER_RIVERLIB_BR_PREDIC_H__
#define __DEBUGGER_RIVERLIB_BR_PREDIC_H__

#include <systemc.h>
#include "../river_cfg.h"

namespace debugger {

SC_MODULE(BranchPredictor) {
    sc_in<bool> i_clk;                  // CPU clock
    sc_in<bool> i_nrst;                 // Reset. Active LOW.
    sc_in<bool> i_hold;                 // Hold pipeline by any reason
    sc_in<bool> i_f_mem_request;        // Memory request from 'fetch' is valid, form next prediction address
    sc_in<bool> i_f_predic_miss;        // Fetch modul detects deviation between predicted and valid pc.
    sc_in<bool> i_f_instr_valid;        // Fetched instruction is valid
    sc_in<sc_uint<32>> i_f_instr;       // Fetched instruction value is used for fast parse 'jump/branch' in predictor
    sc_in<sc_uint<32>> i_e_npc;         // Valid instruction value awaited by 'Executor'
    sc_in<sc_uint<RISCV_ARCH>> i_ra;    // Return address register value
    sc_out<sc_uint<32>> o_npc_predict;  // Predicted next instruction address

    void comb();
    void registers();

    SC_HAS_PROCESS(BranchPredictor);

    BranchPredictor(sc_module_name name_, sc_trace_file *vcd=0);

private:
    struct RegistersType {
        sc_signal<sc_uint<BUS_ADDR_WIDTH>> npc;
    } v, r;
    sc_signal<sc_uint<BUS_ADDR_WIDTH>> wb_npc;
};


}  // namespace debugger

#endif  // __DEBUGGER_RIVERLIB_BR_PREDIC_H__