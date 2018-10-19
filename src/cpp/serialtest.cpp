#include <libserialport.h>
#include <stdio.h>
#include <string.h>

struct sp_port *port;

int main(int argc, char *argv[])
{
	printf("test 1, 2, 3, 4\n");

	int i;
	struct sp_port **ports;
	char buffer[255];
	
	sp_return error = sp_list_ports(&ports);
	if(error == SP_OK)
	{
		for(i = 0; ports[i]; i++)
		{
			printf("Found port: %s\n", sp_get_port_name(ports[i]));
		}
		sp_free_port_list(ports);
	}
	else
	{
		printf("No ports found\n");
	}
	
	printf("Opening on-board port\n");
	error = sp_get_port_by_name("/dev/ttyS4", &port);
	if(error == SP_OK)
	{
		error = sp_open(port, SP_MODE_READ_WRITE);
		if(error == SP_OK)
		{
			printf("Opened port\n");
			sp_set_baudrate(port, 115200);

			memcpy(buffer, "L:512",strlen("L:512"));
			error = sp_blocking_write(port,
				buffer,
				strlen(buffer),
				500);
			printf("Return: %d\n", error);
			sp_drain(port);
			memset(buffer,0x00, 255); 
			memcpy(buffer, "R:512",strlen("R:512"));
			error = sp_blocking_write(port,
				buffer,
				strlen(buffer),
				500);
			printf("Return: %d\n", error);
			sp_drain(port);
			
			sp_close(port);
		}
		else
		{
			printf("Error on sp_open %d\n", error);
		}
	}
	else
		printf("Failed: %x\n", error);
	return 0;

}

