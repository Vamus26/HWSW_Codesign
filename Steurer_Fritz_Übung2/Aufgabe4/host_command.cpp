#include "host_command.h"


    //-----------------------------------------
    // Method: write()
    // Description: Slave write method
    // @Input: idata: packet which should be written to slave
    //-----------------------------------------
void host_command::write( packet_type idata ){
}

    //-----------------------------------------
    // Method: read()
    // Description: Slave read method
    // @return: packet read from the slave
    //-----------------------------------------
packet_type host_command::read(){
    // return received package
	return out_packet.read();
}

    //-----------------------------------------
    //  Method: getStartAddress()
    //  Description: returns slave start address
    //  @return : 32-bit Address
    //-----------------------------------------
unsigned int host_command::getStartAddress(){
	return startAddress_;
    }

    //-----------------------------------------
    //  Method: getEndAddress()
    //  Description: returns slave start address
    //  @return : 32-bit Address
    //-----------------------------------------
unsigned int host_command::getEndAddress(){
	return endAddress_;
    }
