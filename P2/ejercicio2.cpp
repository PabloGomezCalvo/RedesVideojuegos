#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//ejecutar con ./ejericicio2 0.0.0.0 3000 por ejemplo

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
	bind (sd,res->ai_addr,res->ai_addrlen);
	std::cout << "Server Open." << '\n';
	while (true){

		char buf[256];
		struct sockaddr src_addr;
		socklen_t addrlen = sizeof(src_addr);

		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
		bool salir = false;
			
		while(!salir){
			
			size_t s = recvfrom(sd,buf,256,0,&src_addr,&addrlen);
			buf [s]='\0';
			getnameinfo(&src_addr,addrlen,host,NI_MAXHOST, serv, NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);
			std::cout << "Conected to " << host << '\n';
			
			time_t rawtime;
			struct tm* timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			
			
			if(buf[0] == 'q'){
				std::cout << " Saliendo...\n";
				salir=true;
				}
			else if(buf[0] == 't'){//la hora
				std::cout << "2 bytes de " << host;
				size_t tam = strftime(buf,255,"%r",timeinfo);
				sendto(sd,buf,tam,0,&src_addr,addrlen);
			}
			else if(buf[0] == 'd'){//la fecha
				std::cout << "2 bytes de " << host;
				
				size_t tam = strftime(buf,255,"%F",timeinfo);
				sendto(sd,buf,tam,0,&src_addr,addrlen);
				
			}
			else{
				std::cout << "2 bytes de " << host << '\n';
				std:: cout << "Comando no soportado " << buf[0] <<'\n';
			
			
			}
			
		}
	}


freeaddrinfo(res);

	
	return 0;
}
