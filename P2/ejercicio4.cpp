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
	bind (sd,res->ai_addr,res->ai_addrlen);
	
	//el segundo parametro es la cola de conexiones que aceptas.
	listen (sd,3);
	
	char buf[80];
	int client;
	struct sockaddr src_addr;
	socklen_t addrlen = sizeof(src_addr);
	
	char host[NI_MAXHOST];	
	char serv[NI_MAXSERV];
	
	while(true){
		
		client = accept (sd, (struct sockaddr *) &src_addr,&addrlen);
		
		getnameinfo((struct sockaddr *)&src_addr,addrlen,host,NI_MAXHOST, serv, NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);
		std::cout << "Conexion desde host: " << host <<	"\t"<<serv;	
		
		while(true){
			int i=0;
			int x=0;
			
			//se necesita do while para que intente recibir una vez antes de evaluar la condicion del while.
			
			do{
				x=recv(client, &(buf[i]),1,0);
				
				}
			while(x>=0 && i< 79 && buf[i++] != '\n');
				
				
				
			if(x==0){
				close(client);
				break;
				
				}
				send(client,buf,i,0);
			}	
		std::cout << "Conexion terminada.\n";
		}
	
	
	
	freeaddrinfo(res);
	return 0;
	
}
