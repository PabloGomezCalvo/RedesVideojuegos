/*

PROGRAMMING TIME RAMPAGE MODE

UDP MULTITHREAD
*/
//a la hora de compilar poner -l pthread

//el ejecutable se llama con localhost 8080  (estructura ip puerto)
#define NUM_THREADS =5;

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

	getnameinfo(&src_addr,addrlen,host,NI_MAXHOST, serv, NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);

	std::cout << "Thread: " << pthread_self()<< "\n";
	std::cout << "Host: " <<  << "\n";
	std::cout << "Server: " << buf<< "\n";

	sleep(10);

	sendto(sd,buf,s,0,&src_addr,addrlen);


}
}

private: 
	int sd;
	
};



extern "C" void* start_routine (void* _st)
{
	ServerThread * st = statc_cast<ServerThread*> (_st);
	st->do:do_message();

	delete st;
	return 0;

};




int main(int argc, char**argv){

struct addrinfo hints;
struct addrinfo *res;

//---------------------------------------------------------------------
//	1.Inicializar socket
//---------------------------------------------------------------------

int rc getaddrinfo(argv[1],argv[2],&hints, &res);

if (rc!=0){
	std::cout << "error: " << gai_strerror(rc)<< std::endl;
	return -1;
}

int sd = socket (res->ai_family,res->ai_socketype,0);
bind (sd,res->ai_addr,res->ai_addrlen);

freeaddrinfo(res);


//---------------------------------------------------------------------
//	2.Inicializar Pool of Threads
//---------------------------------------------------------------------

for (int i = 0; i <= NUM_THREADS; ++i)
{

	pthread_t tid;
	pthread_attr_t attr;

	ServerThread* st = new ServerThread(sd);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	int pthread_create(&tid,&attr,start_routine,static_cast<void *> (st));
}

//---------------------------------------------------------------------
//	3. Thread Ppal
//---------------------------------------------------------------------

	
	//para que no acabe
	char c;
	std::cin >> c;

	//la alternativa elegante sería hacer un for haciendo joins de todos los threads anteriormente creados.


}
