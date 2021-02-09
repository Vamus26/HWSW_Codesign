//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       generate.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:class declaration of header and CRC generation module
//
/////////////////////////////////////////////////////

#ifndef _generate_h_
#define _generate_h_

#include <systemc.h>
#include "packet.h"

SC_MODULE(generate2){
    sc_in <packet_type> in_encrypt;
    sc_fifo_out <packet_type> out_generate;


    void header_generation();

    SC_CTOR(generate2){
		SC_THREAD(header_generation);
		sensitive << in_encrypt;	
    }
};
	    
#endif