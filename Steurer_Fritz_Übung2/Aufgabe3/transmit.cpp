#include "transmit.h"

void transmit::input() {

	while (true) {
		buffer.nb_write(in_generate.read());
		wait();
	}
}

void transmit::transmitter(){

    packet_type send;
    unsigned char byte;

    while( true ) {
        // read new packet
		wait();
        send = in_generate.read();
        // serialize packet
        // control byte
        out_transmit.write( send.control );
        wait(1,SC_NS);
        // length byte
        out_transmit.write( send.length );
        wait(1,SC_NS);
        // transmit data block = length (crc)
        for( int i=0; i<send.length; i++) {
            out_transmit.write( send.data[i] );
            wait(1,SC_NS);
        }
        // transmit last four bytes (crc)
        out_transmit.write( (send.crc & 0xFF000000)>>24 );
        wait(1,SC_NS);
        out_transmit.write( (send.crc & 0x00FF0000)>>16 );
        wait(1,SC_NS);
        out_transmit.write( (send.crc & 0x0000FF00)>>8 );
        wait(1,SC_NS);
        out_transmit.write(  send.crc & 0x000000FF );
        wait(1,SC_NS);
    }
}
