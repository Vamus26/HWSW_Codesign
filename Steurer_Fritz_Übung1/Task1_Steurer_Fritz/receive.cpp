#include "receive.h"

//---------------------------------------------------------
// Insert process implementation here!!
//---------------------------------------------------------

void receive::packet_creater() {
	//std::cout << "in receive1" << "\n";
	wait();
	unsigned char tmp= in_byte.read();
	wait();
	packet_type current_packet;
	while (true) {
	//	std::cout << "in receive2" << "\n";
		//check packet header
		current_packet.control = in_byte.read();
		wait();
		unsigned char length = in_byte.read();
		wait();
		current_packet.length = length;
		for (int i = 0; i < length; i++) 
		{
			current_packet.data[i] = in_byte.read();
			wait();
		}

		current_packet.crc = ((current_packet.crc & 0x00) | in_byte.read());
		wait();
		current_packet.crc = ((current_packet.crc & 0x00FF) | (in_byte.read() << 8));
		wait();
		current_packet.crc = ((current_packet.crc & 0xFFFF) | (in_byte.read() << 16));
		wait();
		current_packet.crc = ((current_packet.crc & 0xFFFFFF) | (in_byte.read() << 24));
		wait();

//		cout << current_packet.data;
		out_packet.write(current_packet);
	
	}
}