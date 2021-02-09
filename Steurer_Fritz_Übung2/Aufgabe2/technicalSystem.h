//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       technicalSystem.h
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:Implementation of the technical System
//
/////////////////////////////////////////////////////

#ifndef _technicalSystem_h_
#define _technicalSystem_h_

#include <systemc.h>

SC_MODULE(technicalSystem) {
public:

    sc_in<unsigned int> machine1;
    sc_in<unsigned int> machine2;

    void m1_process();
    void m2_process();

    SC_CTOR( technicalSystem ) {

        SC_THREAD( m1_process );
        sensitive << machine1;

        SC_THREAD( m2_process );
        sensitive << machine2;
    }
};
#endif