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

//------------------------------------------------------------------
//  Method:  control::controller()
//  Description: main process of the control unit
//  Parameter: None
//  @Sensitivity: in_command (packet_type)
//------------------------------------------------------------------
void control::controller() {

	packet_type rcv;
	while (true) {

		//
		//  read from bus here!!
		//
		rcv = bus->read(0x100);

		//for debug encryption: out_control_1.write(rcv);
		// parse message
		int pos = rcv.data[0] + 1;
		for (int i = 0; i< rcv.data[0]; i++) {
			// get machineID
			unsigned int ID = rcv.data[pos + 3] | (rcv.data[pos + 2] << 8) | (rcv.data[pos + 1] << 16) | (rcv.data[pos] << 24);
			// get command code
			unsigned int code = rcv.data[pos + 7] | (rcv.data[pos + 6] << 8) | (rcv.data[pos + 5] << 16) | (rcv.data[pos + 4] << 24);
			unsigned int value = rcv.data[pos + 11] | (rcv.data[pos + 10] << 8) | (rcv.data[pos + 9] << 16) | (rcv.data[pos + 8] << 24);
			// decode message
			if (ID == ID_1) {
				ID_1_cmd.write(code);
				ID_1_value.write(value);
			}
			else if (ID == ID_2) {
				ID_2_cmd.write(code);
				ID_2_value.write(value);
			}
			pos += rcv.data[i + 1];
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

	switch (fsm1_state) {
	case STOP:
		switch (ID_1_cmd.read()) {
		case M_STOP:
			// technical system
			machine1.write(0);
			bus->write(ID_1, generate_command(0xCCAA55FF, 0));
			fsm1_state = STOP;
			break;
		case M_START:
			// external machine command
			bus->write(ID_1, generate_command(0xCCAA55FF, 100));
			// technical system
			machine1.write(100);
			fsm1_state = RUN;
			break;
		case M_SET:
			// external machine command
			bus->write(ID_1, generate_command(0xCCAA55FF, 0));
			// technical system
			machine1.write(0);
			fsm1_state = STOP;
			break;
		default:
			break;
		}
		break;
	case RUN:
		switch (ID_1_cmd.read()) {
		case M_STOP:
			// external machine command
			bus->write(ID_1, generate_command(0xCCAA55FF, 0));
			// technical system
			machine1.write(0);
			fsm1_state = STOP;
			break;
		case M_START:
			fsm1_state = RUN;
			break;
		case M_SET:
			// external machine command
			bus->write(ID_1, generate_command(0xCCAA55FF, ID_1_value.read()));
			// technical system
			machine1.write(ID_1_value.read());
			fsm1_state = RUN;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------
//  Method:  control::fsm2()
//  Description: process to control machine 2 of the technical system
//  Parameter: None
//  @Sensitivity: ID_2_cmd (unsigned int)
//------------------------------------------------------------------
void control::fsm2() {
	switch (fsm2_state) {
	case STOP:
		switch (ID_2_cmd.read()) {
		case M_STOP:
			// technical system
			machine2.write(0);
			fsm2_state = STOP;
			break;
		case M_START:
			// external machine command
			bus->write(ID_2, generate_command(0xCCAA55FF, 100));
			// technical system
			machine2.write(100);
			fsm2_state = RUN;
			break;
		case M_SET:
			// external machine command
			bus->write(ID_2, generate_command(0xCCAA55FF, 0));
			// technical system
			machine2.write(0);
			fsm2_state = STOP;
			break;
		default:
			break;
		}
		break;
	case RUN:
		switch (ID_2_cmd.read()) {
		case M_STOP:
			// external machine command
			bus->write(ID_2, generate_command(0xCCAA55FF, 0));
			// technical system
			machine2.write(0);
			fsm2_state = STOP;
			break;
		case M_START:
			fsm2_state = RUN;
			break;
		case M_SET:
			// external machine command
			bus->write(ID_2, generate_command(0xCCAA55FF, ID_2_value.read()));
			// technical system
			machine2.write(ID_2_value.read());
			fsm2_state = RUN;
			break;
		default:
			break;
		}
		break;
	default:
		break;
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
