#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#include "doorlock.h"
#include "keypad.h"
#include "motor.h"
#include "buzzer.h"

#define BUF_SIZE 		128
#define INIT_VAL_OF_MEM	0
#define NUM_OF_ARGC		2
#define PROTOCOL_TYPE	0
#define NUM_OF_QUEUE	5
#define DATA_SIZE		1

#define PKT_STX	0x01	
#define PKT_ETX	0x05

#define CMD_SENSOR_REQ	0x10
#define CMD_SENSOR_RES	0x90

int getData(void);
void error_handling(char *message);
char* trim(char *s);


int main(int argc, char *argv[])
{
	char *str2 = malloc(sizeof(char) * 128);
	int serv_sock, clnt_sock;
	FILE * fp;
	char snd_buf[BUF_SIZE];
	char rcv_buf[BUF_SIZE];
	int read_cnt;
	int readBufSize;
	int i = 0;
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	
	int getData;

	char getData_msb = 0;
	char getData_lsb = 0;

	printf("=========================================\n");
	printf("TCP/IP Data Transmission Program - Server\n");
	printf("=========================================\n\n");
	
	// check port info
	if(argc != NUM_OF_ARGC) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock =  socket(PF_INET, SOCK_STREAM, PROTOCOL_TYPE); 
	
	
	int option;
	option = 1;	
	setsockopt( serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); 
	  
	if (serv_sock == -1)
	        error_handling("socket() error");

	memset(&serv_adr, INIT_VAL_OF_MEM, sizeof(serv_adr));

	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);	// get ip address
	serv_adr.sin_port = htons(atoi(argv[1]));		// get port num

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	        error_handling("bind() error");
	
	if (listen(serv_sock, NUM_OF_QUEUE) == -1)
        	error_handling("listen() error");

	clnt_adr_sz = sizeof(clnt_adr);

	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

	printf("Connected IP : %s\n\n", inet_ntoa(clnt_adr.sin_addr));

	setupWiringPiGpio();
	
	initMotor();
	initKeypad();
	initBuzzer();
	
	printf("ENTER PASSWD:");
	fflush(stdout);
	
	while(1)
	{
		//printf("[check1]sn : %s\n", str2);
		if(readBufSize = read(clnt_sock, rcv_buf, BUF_SIZE) != -1) {
//			printf("[check2]sn : %s\n", str2);
			if(rcv_buf[0] == PKT_STX) {
//				printf("[check3]sn : %s\n", str2);
				if(rcv_buf[1] == CMD_SENSOR_REQ) {
					if(rcv_buf[4] == PKT_ETX) {
//						printf("[check4]sn : %s\n", str2);					
						controlDoorlock(rcv_buf[2], str2);
						getData = getSensorData();

						getData_lsb = (getData & 0xff);
						getData_msb = ((getData>>8) & 0xff);
						
						snd_buf[0] = PKT_STX;
						snd_buf[1] = CMD_SENSOR_RES;
						snd_buf[2] = getData_lsb;
						snd_buf[3] = getData_msb;
						snd_buf[4] = PKT_ETX;

						write(clnt_sock, snd_buf, BUF_SIZE);
					}
	//				printf("out4\n");
				}
	//			printf("out3\n");
			}else{
				strcpy(str2, rcv_buf);
				write(clnt_sock, rcv_buf, BUF_SIZE);
//				printf("check str2 : %s\n", str2);
			}
//			printf("out2\n");
		}
		else {
			write(clnt_sock, snd_buf, BUF_SIZE);
			break;
		}
//		printf("out1\n");
		i++;
	}
	free(str2);
	close(clnt_sock);
	close(serv_sock);
	printf("Transmission terminated.\n");
	printf("Disconnected(IP : %s)\n\n", inet_ntoa(clnt_adr.sin_addr));
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
