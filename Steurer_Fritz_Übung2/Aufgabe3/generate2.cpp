#include "generate2.h"

void generate2::header_generation(){

    packet_type send;

    while( true ) {
        wait();
        send = in_encrypt.read();

        // set decrypt byte
        send.control = 0x80;

        // set new length parameter to 32 byte
        send.length = 32;

        // generate crc value

        send.crc = 0;
        // forward packet to transmitter

        out_generate.write( send );

    }
}
