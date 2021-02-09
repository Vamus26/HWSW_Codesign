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
#include "machine_command.h"
#include "packet.h"
#include "technicalSystem.h"
#include "machine.h"
#include "bus.h"

SC_MODULE( top ) {

public:
    sc_in_clk clock;

    sc_buffer <unsigned char> data_net;	
////    sc_signal <packet_type> command_net; replaced by bus system

	//sc_buffer <packet_type> control_net_1;
	//sc_buffer <packet_type> control_net_2;
//	sc_fifo <packet_type> control_net_1;
//	sc_fifo <packet_type> control_net_2;
	sc_buffer <unsigned char> machine_net_1;
	sc_buffer <unsigned char> machine_net_2;

    sc_signal< unsigned int > m1_control;
    sc_signal< unsigned int > m2_control;

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
	//	command from host
	//	includes three blocks: 
	//		receiver
	//		header checking
	//		rsa-decryption
	//--------------------------------------------------
	control *ct1;// ("Main_Controller");
	//--------------------------------------------------
	//	command to machine 1
	//	includes three blocks: 
	//		rsa-encryption
	//		header generation
	//		transmitter
	//--------------------------------------------------
	machine_command *mc1; //("Command_To_Machine_1");
	//--------------------------------------------------
	//	command to machine 2
	//	includes three blocks: 
	//		rsa-encryption
	//		header generation
	//		transmitter
	//--------------------------------------------------
	machine_command *mc2;// ("Command_To_Machine_2");

    // technical system directly controlled by this controller
    technicalSystem *tS;

    // machines indirectly controlled with encrypted messages
    machine     *m1;
    machine     *m2;
    bus         *bus1;

    SC_CTOR( top ) {

        dg1 = new data_gen("Data_Generation");

        //
        //  Instantiate hc1 and bus here!!
        //
		hc1 = new host_command("Host Command", 0x100, 0x200);
		bus1 = new bus("Bus");
        ct1 = new control("Main_Controller");
    //    mc1 = new machine_command("Command_To_Machine_1");
  //      mc2 = new machine_command("Command_To_Machine_2");
		mc1 = new machine_command("Command_To_Machine_1", 0x300, 0x400);
		mc2 = new machine_command("Command_To_Machine_2", 0x500, 0x600);
        m1  = new machine("Machine_1", "m1_output.txt");
        m2  = new machine("Machine_2", "m2_output.txt");
        tS  = new technicalSystem("Technical_System");
        

        dg1->clock( clock );
        dg1->out_data(data_net);
		hc1->in_data(data_net);
        //
        //  Connect bus to system here!!
        //
	//  ct1->out_control_1(control_net_1);
	//	ct1->out_control_2(control_net_2);
		ct1->machine1(m1_control);
		ct1->machine2(m2_control);
		bus1->slave(*hc1);
		bus1->slave(*mc1);
		bus1->slave(*mc2);

		ct1->bus(*bus1);

	    mc1->out(machine_net_1);
	    mc2->out(machine_net_2);

        m1->in( machine_net_1 );
        m2->in( machine_net_2 );

        tS->machine1( m1_control );
        tS->machine2( m2_control );

    }
};

#endif