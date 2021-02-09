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
#include "bus_data_if.h"
#include "bus_slave_if.h"
enum machineState {RUN, STOP};

SC_MODULE(control){
public:

    //
    // declare bus port here!!!
    //
	sc_port<bus_data_if, 0> bus;
    //sc_out <packet_type> out_control_1;
	//sc_out <packet_type> out_control_2;

    sc_out<unsigned int>    machine1;
    sc_out<unsigned int>    machine2;

	sc_signal<unsigned int> ID_1_value;
	sc_signal<unsigned int> ID_1_cmd;
	sc_signal<unsigned int> ID_2_value;
	sc_signal<unsigned int> ID_2_cmd;

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

    //------------------------------------------------------------------
    //  Method: Constructor
    //------------------------------------------------------------------
    SC_CTOR(control){
		SC_THREAD( controller );
//		sensitive << in_command;

        SC_METHOD( fsm1 );
        sensitive << ID_1_cmd;

        SC_METHOD( fsm2 );
        sensitive << ID_2_cmd;

        fsm1_state = STOP;
        fsm2_state = STOP;
	
    }
private:
    // state variables
    machineState    fsm1_state;
    machineState    fsm2_state;

};
	    
#endif