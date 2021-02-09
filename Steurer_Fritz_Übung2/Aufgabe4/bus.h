//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       bus.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:bus model for packet_type
//
/////////////////////////////////////////////////////

#ifndef _bus_h_
#define _bus_h_

#include <systemc.h>
#include "packet.h"
#include "bus_data_if.h"
#include "bus_slave_if.h"

class bus : public sc_module, 
            public bus_data_if 
{
public:
    sc_port< bus_slave_if,0 > slave;

    //---------------------------------------
    //  Method: write()
    //  Description: forwards write request to bus 
    //  @Input: address:    target address
    //  @Input: idata:      forwarded package to bus
    //--------------------------------------------
    void write( unsigned int address, packet_type idata );

    //---------------------------------------
    //  Method: read()
    //  Description: forwards read request to bus 
    //  @Input: address:    target address
    //  @return: packet_type:   packet read from target address
    //--------------------------------------------
    packet_type read(unsigned int address);

    SC_CTOR(bus) {
    }
};
#endif