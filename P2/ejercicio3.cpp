#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//ejecutar con ./ejericicio2 127.0.0.1 3000 t por ejemplo

int main (int agrc, const char * argv[]){

	struct addrinfo hints;
	struct addrinfo *res;
	memset((void*) &hints, '\0', sizeof(struct addrinfo));

	hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
	hints.ai_family   = AF_INET; // IPv4
	hints.ai_socktype = SOCK_DGRAM;
	//---------------------------------------------------------------------
	//	1.Inicializar socket
	//---------------------------------------------------------------------

	int rc = getaddrinfo(argv[1],argv[2],&hints, &res);

	if (rc!=0){
		std::cout << "error: " << gai_strerror(rc)<< std::endl;
		return -1;
	}

	int sd = socket (res->ai_family,res->ai_socktype,0);
	char buf[256];
	
	sendto(sd,argv[3],2,0,(struct sockaddr *)res->ai_addr,res->ai_addrlen);
	
	size_t s = recvfrom(sd,buf,256,0,(struct sockaddr *)res->ai_addr,&res->ai_addrlen);
	
	buf[s] = '\0';
	
	std:: cout << buf << '\n' ;
	
	
freeaddrinfo(res);

	
	return 0;
}
