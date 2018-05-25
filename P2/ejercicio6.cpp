#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <features.h>

//a la hora de compilar poner -l pthread

//el ejecutable se llama con localhost 8080  (estructura ip puerto)
#define NUM_THREADS 5;

class ServerThread
{
public:
	ServerThread(int s):sd(s){};
	virtual ~ServerThread(){};
//recibo mensaje y trato el mensaje
void do_message(){

while (true){

	char buf[256];
	struct sockaddr src_addr;
	socklen_t addrlen = sizeof(src_addr);

	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];

	size_t s = recvfrom(sd,buf,255,0,&src_addr,&addrlen);
	buf[s] = '\0';
	getnameinfo(&src_addr,addrlen,host,NI_MAXHOST, serv, NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);

	std::cout << "Thread: " << pthread_self()<< "\n";
	std::cout << "Host: " << host << "\n";
	std::cout << "Server: " << buf<< "\n";
	
	time_t rawtime;
	struct tm* timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
			
			
			if(buf[0] == 'q'){
				std::cout << " Saliendo...\n";
				
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
	
	sleep(10);

}
}

private: 
	int sd;
	
};



extern "C" {
	void* start_routine (void* _st)
{
	ServerThread * st = static_cast<ServerThread*> (_st);
	st-> do_message();

	delete st;
	return 0;

}
}




int main(int argc, char**argv){
	struct addrinfo hints;
	struct addrinfo *res;
	memset((void*) &hints, '\0', sizeof(struct addrinfo));

	//hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
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


//---------------------------------------------------------------------
//	2.Inicializar Pool of Threads
//---------------------------------------------------------------------



int i=0;
while(i<= NUM_THREADS){

	pthread_t tid;
	pthread_attr_t attr;

	ServerThread* st = new ServerThread(sd);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_create(&tid,&attr,start_routine,static_cast<void *> (st));
	i++;
}

//---------------------------------------------------------------------
//	3. Thread Ppal
//---------------------------------------------------------------------

	
	//para que no acabe
	char c;
	do std::cin >> c;
	while( c!='q');
	
	freeaddrinfo(res);
	exit(0);

	//la alternativa elegante sería hacer un for haciendo joins de todos los threads anteriormente creados.

	return 0;
}
