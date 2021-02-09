//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       receive.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:class declaration of receiver module
//
/////////////////////////////////////////////////////

#ifndef _receive_h_
#define _receive_h_

#include <systemc.h>
#include "packet.h"

// States for finite state machine
enum rcv_states {CONTROL, LENGTH, DATA, CRC};

//--------------------------------------------------
// Insert the code of your receiver module here!!
//-------------------------------------------------
SC_MODULE(receive) {
	//in_byte(in_data);
	//receiver->out_packet(packet_net);
	sc_in <unsigned char> in_byte;//out_data;
	sc_out <packet_type> out_packet;// in_packet;

	void packet_creater();

	SC_CTOR(receive) {
		SC_THREAD(packet_creater);
		sensitive << in_byte;// out_data;
	}
};

#endif