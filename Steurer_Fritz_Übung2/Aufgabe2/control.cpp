//////////////////////////////////////////////////////
//
//  Project:    HWSW CD Lab 2009
//  Author:     Andreas Schuhai, Ulrich Neffe, Michael Karner
//  Date:       5.3.2009
//  File:       control.cpp
//  Compiler:   VC++ 8.0
//  SystemC:    Version 2.2.0
//  Description:Central control unit
//
/////////////////////////////////////////////////////


#include "control.h"

unsigned int control::byteToInt(unsigned char* data) {
	unsigned int intValue = 0;

	intValue = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
	
	return intValue;
}

//------------------------------------------------------------------
//  Method:  control::controller()
//  Description: main process of the control unit
//  Parameter: None
//  @Sensitivity: in_command (packet_type)
//------------------------------------------------------------------
void control::controller() {

	// define local variables here

	while (true) {
		//---------------------------------
		// insert synchronization code here
		//---------------------------------
		wait();
		packet_type rcv = in_command.read();

		//-----------------------------------------------
		// parse message
		//-----------------------------------------------
		int pos = rcv.data[0] + 1;
		for (int i = 0; i< rcv.data[0]; i++) {
			//-------------------------------------------
			// get MachineID
			unsigned int ID = byteToInt(rcv.data + pos);
			pos += 4;
			// get Command
			unsigned int command = byteToInt(rcv.data + pos);
			pos += 4;
			// get Value
			//------------------------------------------
			unsigned int value = byteToInt(rcv.data + pos);
			pos += 4;

			std::cout << "----------------------" << std::endl;

			std::cout << "ID: " << ID << std::endl;
			std::cout << "COMMAND: " << command << std::endl;
			std::cout << "VALUE: " << value << std::endl;

	
			//-------------------------------------------
			// decode message
			//-------------------------------------------
			if (ID == ID_1) {
				// commands for Machine 1
				packet_type packet = generate_command(command, value);
				id1_value.write(value);
				id1_cmd.write(command);
			}
			else if (ID == ID_2) {
				// commands for Machine 2
				packet_type packet = generate_command(command, value);
				id2_value.write(value);
				id2_cmd.write(command);
			}
			// update byte position

		}
	}
}

//------------------------------------------------------------------
//  Method:  control::fsm1()
//  Description: process to control machine 1 of the technical system
//  Parameter: None
//  @Sensitivity: ID_1_cmd (unsigned int)
//------------------------------------------------------------------
void control::fsm1() {
	machineState state = STOP;
	// implement Finite State Machine here
	while (true) {
		wait();
		unsigned int command = id1_cmd.read();
		unsigned int value = id1_value.read();

		std::cout << "command1: " << command << std::endl;
		std::cout << "value1: " << value << std::endl;

		packet_type packet = generate_command(command, value);
		switch (state)
		{
		case STOP:
			if (command == M_START) {
				state = RUN;
			}
			break;
		case RUN:
			if (command == M_SET) {
				state = RUN;
			}
			else if (command == M_STOP) {
				state = STOP;
			}
			break;
		default:
			break;
		}

		machine1.write(value);
		out_control_1.write(packet);
	}
}

//------------------------------------------------------------------
//  Method:  control::fsm2()
//  Description: process to control machine 2 of the technical system
//  Parameter: None
//  @Sensitivity: ID_2_cmd (unsigned int)
//------------------------------------------------------------------
void control::fsm2() {
	machineState state = STOP;
	// implement Finite State Machine here
	while (true) {
		wait();
		unsigned int command = id2_cmd.read();
		unsigned int value = id2_value.read();

		std::cout << "command2: " << command << std::endl;
		std::cout << "value2: " << value << std::endl;

		packet_type packet = generate_command(command, value);
		switch (state)
		{
		case STOP:
			if (command == M_START) {
				state = RUN;
			}
			break;
		case RUN:
			if (command == M_SET) {
				state = RUN;
			}
			else if (command == M_STOP) {
				state = STOP;
			}
			break;
		default:
			break;
		}

		machine2.write(value);
		out_control_2.write(packet);
	}
}

//------------------------------------------------------------------
//  Method:  control::generate_command()
//  Description: writes id and value into data stream of a packet
//  Parameter:
//  @Input: id  command identifier
//  @Input: value cammand parameter
//  @return generated packet with set length attribute
//------------------------------------------------------------------
packet_type control::generate_command(unsigned int id, unsigned int value) {
	packet_type packet;
	packet.length = 8;
	packet.data[0] = id & 0xFF;
	packet.data[1] = (id & 0xFF00) >> 8;
	packet.data[2] = (id & 0xFF0000) >> 16;
	packet.data[3] = (id & 0xFF000000) >> 24;
	packet.data[4] = value & 0xFF;
	packet.data[5] = (value & 0xFF00) >> 8;
	packet.data[6] = (value & 0xFF0000) >> 16;
	packet.data[7] = (value & 0xFF000000) >> 24;
	return packet;
}
