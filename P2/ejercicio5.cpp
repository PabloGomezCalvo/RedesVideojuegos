#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>



//ejecutar con ./ejericicio4 0.0.0.0 3000 por ejemplo

int main (int agrc, const char * argv[]){

	struct addrinfo hints;
	struct addrinfo *res;
	memset((void*) &hints, '\0', sizeof(struct addrinfo));

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family   = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM;
	//---------------------------------------------------------------------
	//	1.Inicializar socket
	//---------------------------------------------------------------------

	int rc = getaddrinfo(argv[1],argv[2],&hints, &res);

	if (rc!=0){
		std::cout << "error: " << gai_strerror(rc)<< std::endl;
		return -1;
	}

	int sd = socket (res->ai_family,res->ai_socktype,0);
	
	//conectamos
	
	connect(sd,(struct sockaddr *) res->ai_addr,res->ai_addrlen);
	
	
	while(true){
		
		char buf[80];
		int x=0;
		int i=0;
		std::cin>>buf;
		
		size_t tam = send(sd,buf,80,0);
		
		
		if(buf[0] != 'q'){
				x=0;
				i=0;
				memset(buf,0,80);
				do{
					
					x=recv(sd,&(buf[i]),1,0);
					i++;
					}while(x>=0 && i < 79);
		}
		else{
				shutdown(sd, SHUT_RDWR);
				x=0;
				i=0;
			do{
					
					x=recv(sd,&(buf[i]),1,0);
					i++;
					}while(x>=0 && i < 79);
			
		}
		
		std::cout << buf <<'\n';
		memset(buf,0,80);
		
	}
	freeaddrinfo(res);
	return 0;
	
}
