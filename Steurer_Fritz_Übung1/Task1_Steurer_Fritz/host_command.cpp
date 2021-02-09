#include "host_command.h"


void host_command::full_command(){

	host_byte = in_data.read();	

    byte_net.write(host_byte);	
	out_command.write(decrypt_net.read());    

    cout << " host command: " << host_byte << ", " << out_command.read() << "\n";	
	
}
