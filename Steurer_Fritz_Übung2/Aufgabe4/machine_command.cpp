#include "machine_command.h"



    //-----------------------------------------
    // Method: write()
    // Description: Slave write method
    // @Input: idata: packet which should be written to slave
    //-----------------------------------------
void machine_command::write( packet_type idata ){
	in.write(idata);
}

    //-----------------------------------------
    // Method: read()
    // Description: Slave read method
    // @return: packet read from the slave
    //-----------------------------------------
packet_type machine_command::read(){
    // return received package
	return packet_type();
}

    //-----------------------------------------
    //  Method: getStartAddress()
    //  Description: returns slave start address
    //  @return : 32-bit Address
    //-----------------------------------------
unsigned int machine_command::getStartAddress(){
	return startAddress_;
    }

    //-----------------------------------------
    //  Method: getEndAddress()
    //  Description: returns slave start address
    //  @return : 32-bit Address
    //-----------------------------------------
unsigned int machine_command::getEndAddress(){
	return endAddress_;
    }
