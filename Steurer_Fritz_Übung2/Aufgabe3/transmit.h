//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       transmit.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:class declaration of transmit module
//
/////////////////////////////////////////////////////

#ifndef _transmit_h_
#define _transmit_h_

#include <systemc.h>
#include "packet.h"

SC_MODULE(transmit){
	sc_fifo<packet_type> buffer;
    sc_in <packet_type> in_generate;
    sc_out <unsigned char> out_transmit;

	void input();
    void transmitter();

    SC_CTOR(transmit) {
		SC_THREAD(transmitter);
        sensitive << in_generate;
		SC_THREAD(transmitter);
		sensitive << buffer.data_written_event();
    }

};
	    
#endif