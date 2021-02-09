//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       top.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:System configuration
//
/////////////////////////////////////////////////////


#ifndef _top_h_
#define _top_h_

#include <systemc.h>
#include "data_gen.h"
#include "host_command.h"


SC_MODULE( top ) {

public:
    // input clock
    sc_in_clk clock;

    //---------------------------------
    //  internal nets
    //----------------------------------
	sc_buffer<unsigned char> data;
	sc_signal<packet_type> command_net;
    //
    //..................
    //

    // Object declaration:
	//--------------------------------------------------
	//	data generation
	//--------------------------------------------------
    data_gen *dg1;//("Data_Generation");

    //--------------------------------------------------
	//	command from host
	//	includes three blocks: 
	//		receiver
	//		header checking
	//		rsa-decryption
	//--------------------------------------------------
	host_command *hc1; //("Command_from_Host");
    SC_CTOR( top ) {

        //----------------------------------------
        //  create your objects here!!
        //----------------------------------------
		dg1 = new data_gen("data_gen");
		hc1 = new host_command("host_command");
		//
        // ......................
        //

        //----------------------------------------
        //  connect your signals here
        //----------------------------------------
		dg1->clock(clock);
		dg1->out_data(data);
		hc1->in_data(data);
		hc1->out_packet(command_net);
        //
        // .........
        //
    }
};

#endif