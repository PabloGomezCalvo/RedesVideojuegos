#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <features.h>


/*

PROGRAMMING TIME RAMPAGE MODE

TCP MULTITHREAD
*/
//a la hora de compilar poner -l pthread

//el ejecutable se llama con localhost 8080  (estructura ip puerto)
#define NUM_THREADS =5;

class ServerThread
{
public:
	ServerThread(int s):sd(s){};
	virtual ~ServerThread(){close (sd);};
//recibo mensaje y trato el mensaje
void do_message(){
char buf[80];
while (true){

	//gestion de la conexion vs gestion del mensaje
	//send/receive de antes.
	
	
			int i=0;
			int x=0;
			
			//se necesita do while para que intente recibir una vez antes de evaluar la condicion del while.
			
			do{
				x=recv(sd, &(buf[i]),1,0);
				
				}
			while(x>=0 && i< 79 && buf[i++] != '\n');
				
				
				
			if(x==0){
				close(sd);
				std::cout << "Conexion terminada.\n";
				break;
				
				}
				send(sd,buf,i,0);
			}	
		



}

private: 
	int sd;
	
};



extern "C" void* start_routine (void* _st)
{
	ServerThread * st = static_cast<ServerThread*> (_st);
	st->do_message();

	delete st;
	return 0;

};




int main(int argc, char**argv){
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
	
	std::cout << "Conexion desde host: " << host << "\tPuerto: " << serv << '\'n';
	
	pthread_t tid;
	pthread_attr_t attr;

	ServerThread* st = new ServerThread(client);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_create(&tid,&attr,start_routine,static_cast<void *> (st));
	
}

exit(0);
return 0;

}
