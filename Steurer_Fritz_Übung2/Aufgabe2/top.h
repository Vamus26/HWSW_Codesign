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
#include "control.h"
#include "packet.h"
#include "technicalSystem.h"

SC_MODULE( top ) {

public:
    sc_in_clk clock;

    sc_buffer <unsigned char> data_net;	
    sc_signal <packet_type> command_net;
	sc_buffer <packet_type> control_net_1;
	sc_buffer <packet_type> control_net_2;

    //-------------------------------------
    // Insert additional signals here!!
    //-------------------------------------
	sc_buffer<unsigned int> machine1;
	sc_buffer<unsigned int> machine2;
    //
    //  .........................
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

    //--------------------------------------------------
    // declare additional objects here!!
    //--------------------------------------------------
//	technicalSystem *ts1;
	//control *cs1;
	control *ctrl;
	technicalSystem *logger;
    //
    // .........................
    //

    SC_CTOR( top ) {

        dg1 = new data_gen("Data_Generation");
        hc1 = new host_command("Command_from_Host");
	//	ts1 = new technicalSystem("technicalSystem");
	//	cs1 = new control("control");
		ctrl = new control("Control");
		logger = new technicalSystem("Technical System");

        //----------------------------------------------
        // Instantiate additional objects here!!
        //----------------------------------------------

        //
        //  ........................................
        //

        dg1->clock( clock );
        dg1->out_data(data_net);

	    hc1->in_data(data_net);
	    hc1->out_packet(command_net);

        //----------------------------------------
        // Connect additional signals here
        //----------------------------------------
		ctrl->in_command(command_net);
		ctrl->out_control_1(control_net_1);
		ctrl->out_control_2(control_net_2);
		ctrl->machine1(machine1);
		ctrl->machine2(machine2);

		logger->machine1(machine1);
		logger->machine2(machine2);
        //
        // .........................................
        //
    }
};

#endif