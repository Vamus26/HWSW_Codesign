//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       machine_command.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:class declaration hierarchical module to encapsulate data postprocessing
//
/////////////////////////////////////////////////////


#ifndef _machine_command_h_
#define _machine_command_h_

#include <systemc.h>
#include "encrypt.h"
#include "generate2.h"
#include "transmit.h"
#include "packet.h"

SC_MODULE(machine_command){
    sc_in <packet_type> in;
    sc_out <unsigned char> out;
	
	sc_buffer <packet_type> encrypt_net;
	sc_signal <packet_type> generate_net;

	encrypt *encr;
	generate2 *head;
	transmit *trans;


    SC_CTOR(machine_command){

		encr = new encrypt("RSA_Encryption");
		head = new generate2("Header_Generation");
		trans = new transmit("Transmitter");

		encr -> in_controller(in);
		encr -> out_encrypt(encrypt_net);

		head -> in_encrypt(in);
		head -> out_generate(generate_net);

		trans -> in_generate(generate_net);
		trans -> out_transmit(out);
    }
};
	    
#endif