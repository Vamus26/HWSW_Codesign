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


#include "technicalSystem.h"


void technicalSystem::m1_process() {

    while( true ) {
        wait(); // wait for new input value

        cout << sc_time_stamp() << ": Machine 1 new parameter: " << machine1.read() << endl;;
    }
}

void technicalSystem::m2_process() {

    while( true ) {
        wait(); // wait for new input value

        cout << sc_time_stamp() << ": Machine 2 new parameter: " << machine2.read() << endl;;
    }
}