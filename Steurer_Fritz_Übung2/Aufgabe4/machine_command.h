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
#include "bus_slave_if.h"

class machine_command: public sc_module, public bus_slave_if
{
public:
    sc_out <unsigned char> out;

	sc_fifo <packet_type> in;
//    sc_fifo_in  <packet_type> in;

	sc_buffer <packet_type> encrypt_net;
	sc_fifo <packet_type> generate_net;

	encrypt *encr;
	generate2 *head;
	transmit *trans;
    //-----------------------------------------
    // Method: write()
    // Description: Slave write method
    // @Input: idata: packet which should be written to slave
    //-----------------------------------------
    void write( packet_type idata );

    //-----------------------------------------
    // Method: read()
    // Description: Slave read method
    // @return: packet read from the slave
    //-----------------------------------------
    packet_type read();

    //-----------------------------------------
    //  Method: getStartAddress()
    //  Description: returns slave start address
    //  @return : 32-bit Address
    //-----------------------------------------
    unsigned int getStartAddress();

    //-----------------------------------------
    //  Method: getEndAddress()
    //  Description: returns slave start address
    //  @return : 32-bit Address
    //-----------------------------------------
    unsigned int getEndAddress();

	SC_HAS_PROCESS(machine_command);

    machine_command(sc_module_name name_, unsigned int startAddr, unsigned int endAddr): sc_module(name_)
    {

		encr = new encrypt("RSA_Encryption");
		head = new generate2("Header_Generation");
		trans = new transmit("Transmitter");

		encr -> in_controller(in);
		encr -> out_encrypt(encrypt_net);

		head -> in_encrypt(encrypt_net);
		head -> out_generate(generate_net);

		trans -> in_generate(generate_net);
		trans -> out_transmit(out);
        startAddress_ = startAddr;
        endAddress_ = endAddr;
    }
private:
    unsigned int startAddress_;
    unsigned int endAddress_;
};
	    
#endif