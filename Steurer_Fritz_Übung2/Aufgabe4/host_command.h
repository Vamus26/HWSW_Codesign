//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       host_command.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:class declaration hierarchical module to encapsulate data preprocessing
//
/////////////////////////////////////////////////////

#ifndef _host_command_h_
#define _host_command_h_

#include <systemc.h>
#include "receive.h"
#include "check.h"
#include "decrypt.h"
#include "packet.h"
#include "bus_slave_if.h"

class host_command : public sc_module,
                     public bus_slave_if
{
public:
    sc_in <unsigned char> in_data;

    sc_fifo <packet_type> out_packet;
	
	sc_signal <packet_type> packet_net;
	sc_fifo <packet_type> check_net;

	receive *receiver;
	check *checker;
	decrypt *decrypter;
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

    SC_HAS_PROCESS(host_command);

    host_command(sc_module_name name_, unsigned int startAddr, unsigned int endAddr)
        : sc_module( name_ )
    {

        receiver = new receive("Receiver");
		checker = new check("Header_Checking");
		decrypter = new decrypt("RSA_Decryption");

		receiver -> in_byte(in_data);
		receiver -> out_packet(packet_net);
	
		checker -> in_packet(packet_net);
		checker -> out_decoder(check_net);
	
		decrypter -> in(check_net);
		decrypter -> out(out_packet);

        startAddress_ = startAddr;
        endAddress_ = endAddr;
    }
private:
    unsigned int startAddress_;
    unsigned int endAddress_;
};
#endif	    
