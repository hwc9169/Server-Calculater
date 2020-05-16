#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>

#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 1024
#define INT 4
void error() {
	printf("ERROR!!"); //¿¡·¯  
	exit(1);
}

int main(int argc, char* argv[]) {
	// usage
	if (argc != 3) {
		printf("USAEG : %s ip port", argv[0]);
		exit(1);
	}
	
	WSADATA wsadata;
	SOCKET serversock;
	SOCKET clientsock;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	char operand[BUF_SIZE];
	int strlen, total=0;
	
	memset(&serveraddr,0,sizeof(sockaddr));
	serveraddr.sin_family = AF_INET;								// Initialize Address Family
	serveraddr.sin_port = htons(atoi(argv[1]));						// Initialize port 
	serveraddr.sin_addr.s_addr = inet_addr(argv[2]);				// Initialie ip address

	WSAStartup(MAKEWORD(1, 2), &wsadata);

	serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);			//1. Socket()
	bind(serversock, (sockaddr*)&serveraddr, sizeof(serveraddr));	//2. Bind()
	listen(serversock, 5);											//3. listen()

	int socklen = sizeof(clientaddr); 

	clientsock = accept(serversock,(sockaddr*)&clientaddr,&socklen);// 4. accept()
	recv(clientsock, operand, BUF_SIZE,0);
	int* cnt = (int*)&operand[0];
	int* point = (int*)&operand[INT];
	int sum = *point;
	
	switch (operand[(*cnt + 1) * INT + 1]) { // calculate
	case '+':
		for (int i = 2; i <= *cnt; i++) {
			point = (int*)&operand[i * INT];
			sum += *point;;
		}
			break;
	case '-':
		for (int i = 2; i <= *cnt; i++) {
			point = (int*)&operand[i * INT];
			sum -= *point;
		}
			break;
	case '*':
		for (int i = 2; i <= *cnt; i++) {
			point = (int*)&operand[i * INT];
			sum *= *point;
		}
			break;
	}

	send(clientsock,(char*)&sum, BUF_SIZE, 0); // send() 
	printf("close the connection...");
	closesocket(clientsock);
	closesocket(serversock);
	WSACleanup();
	return 0;
}

