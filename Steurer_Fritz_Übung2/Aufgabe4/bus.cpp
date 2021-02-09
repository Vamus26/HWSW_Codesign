//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       bus.cpp
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:bus model for packet_type
//
/////////////////////////////////////////////////////


#include "bus.h"
#include "defines.h"


void bus::write(unsigned int address, packet_type idata) {
	if (address == ID_1) {
		slave[1]->write(idata);
	}
	else if (address == ID_2) {
		slave[2]->write(idata);
	}
}

packet_type bus::read(unsigned int address) {
	return slave[0]->read();
}
