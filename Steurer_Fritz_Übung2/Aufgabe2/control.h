//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       control.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:Central control unit
//
/////////////////////////////////////////////////////

#ifndef _control_h_
#define _control_h_

#include <systemc.h>
#include "packet.h"
#include "defines.h"


enum machineState {RUN, STOP};

SC_MODULE(control){

    // Ports:
    sc_in <packet_type> in_command;
    sc_out <packet_type> out_control_1;
	sc_out <packet_type> out_control_2;

    sc_out<unsigned int>    machine1;
    sc_out<unsigned int>    machine2;

    //---------------------------------------
    // Insert required signals here!!
    //---------------------------------------
	sc_signal<unsigned int> id1_cmd;
	sc_signal<unsigned int> id1_value;
	sc_signal<unsigned int> id2_cmd;
	sc_signal<unsigned int> id2_value;

	//sc_buffer <packet_type> out_control_X;
//	sc_signal <unsigned int> machine_X;
//	unsigned int ID_1_cmd;
    //
    //  .............................
    //

    //------------------------------------------------------------------
    //  Method:  control::controller()
    //  Description: main process of the control unit
    //  Parameter: None
    //  @Sensitivity: in_command (packet_type)
    //------------------------------------------------------------------
    void controller();

    //------------------------------------------------------------------
    //  Method:  control::fsm1()
    //  Description: process to control machine 1 of the technical system
    //  Parameter: None
    //  @Sensitivity: ID_1_cmd (unsigned int)
    //------------------------------------------------------------------
    void fsm1();

    //------------------------------------------------------------------
    //  Method:  control::fsm2()
    //  Description: process to control machine 2 of the technical system
    //  Parameter: None
    //  @Sensitivity: ID_2_cmd (unsigned int)
    //------------------------------------------------------------------
    void fsm2();

    //------------------------------------------------------------------
    //  Method:  control::generate_command()
    //  Description: writes id and value into data stream of a packet
    //  Parameter:
    //  @Input: id  command identifier
    //  @Input: value cammand parameter
    //  @return generated packet with set length attribute
    //------------------------------------------------------------------
    packet_type generate_command( unsigned int id, unsigned int value);
	unsigned int byteToInt( unsigned char* data);
    //------------------------------------------------------------------
    //  Method: Constructor
    //------------------------------------------------------------------
    SC_CTOR(control){

        //-------------------------------------
        // Declare finite state machines here!!
        //-------------------------------------
		SC_THREAD(controller);
		sensitive << in_command;// out_data;
		SC_THREAD(fsm1);
		sensitive << id1_cmd;// out_data;
		SC_THREAD(fsm2);
		sensitive << id2_cmd;
        //
        //  .............................
        //

        fsm1_state = STOP;
        fsm2_state = STOP;
	
    }
private:
    // state variables
    machineState    fsm1_state;
    machineState    fsm2_state;

};
	    
#endif