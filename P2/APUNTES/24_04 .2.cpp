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

while (true){

	//gestion de la conexion vs gestion del mensaje
	//send/receive de antes.
	//pd:no se que coño va antes


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
/*AQUI CAMBIAN MUCHAS COSAS PERO NO ME QUIERE Y NO ME LAS ENSEÑA*/
struct addrinfo hints;
struct addrinfo *res;
memset((*void) &hints, '\0',sizeof(struct addrinfo));

//---------------------------------------------------------------------
//	1.Inicializar socket
//---------------------------------------------------------------------
hints.ai_socktype= ?????;
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

while(true){

	int sd_src=accpet(sd,&src_addr,&addrlen)
	pthread_t tid;
	pthread_attr_t attr;

	ServerThread* st = new ServerThread(sd_src);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	int pthread_create(&tid,&attr,start_routine,static_cast<void *> (st));
}


}