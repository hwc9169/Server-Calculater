#include <stdio.h>
#include <winsock2.h>

#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 1024
#define INT 4

void error() {
	printf("ERROR!!");
	exit(1);
}

int main(int argc, char* argv[]) {

	SOCKET sock;
	SOCKADDR_IN sock_addr;
	WSADATA wsadata;
	
	memset(&sock_addr,0,sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(atoi(argv[1]));
	sock_addr.sin_addr.s_addr = inet_addr(argv[2]);
	char operand[BUF_SIZE];
	int strlen, num;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sock, (sockaddr*)&sock_addr, sizeof(sock_addr));
	fprintf(stdout,"Operand count : "); // 인자 갯수 반환
	scanf("%d", (int*)&operand[0]);
	int* cnt = (int*)&operand[0];
	for (int i = 1; i <= *cnt; i++) {
		fprintf(stdout, "Operation %d :",i); //  연산자 입력
		fscanf(stdin, "%d", (int*)&operand[i*INT]); 
	}
	
	fprintf(stdout, "Operation : ");
	getchar();
	fscanf(stdin,"%c",(char*)&operand[(*cnt+1)*INT+1]);

	send(sock, operand, BUF_SIZE, 0);
	recv(sock, operand, BUF_SIZE, 0);

	
		printf("result : %d ", *operand );
	closesocket(sock);
	WSACleanup();

}
