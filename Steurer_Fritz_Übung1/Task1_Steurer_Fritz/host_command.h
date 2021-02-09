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
#include "packet.h"
#include "data_gen.h"

SC_MODULE(host_command){
public:
    //------------------------------------------
    //  Hierarchical ports to system 
    //------------------------------------------
    sc_in <unsigned char> in_data;
    sc_out <packet_type> out_packet;
	
    //------------------------------------------
    //  Internal signal
    //------------------------------------------
	sc_signal <packet_type> packet_net;

    //-------------------------------------------
    //  declare your objects here!!
    //-------------------------------------------
	receive *receiver;
	check *checker;

    SC_CTOR(host_command){
        //----------------------------------------
        //  create your objects here!!
        //----------------------------------------
	//	std::cout << "in host" << "\n";
        receiver = new receive("Receiver");
		checker = new check("Header_Checking");

        //----------------------------------------
        //  connect your signals here
        //----------------------------------------
		receiver -> in_byte(in_data);
		receiver -> out_packet(packet_net);
	
		checker -> in_packet(packet_net);
		checker -> out_decoder(out_packet);
		//data_gen -> buffer_data(command_net);
    }
};
#endif	    
