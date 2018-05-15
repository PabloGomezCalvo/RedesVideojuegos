#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>





int main(int argc, char* argv[])
{
	struct addrinfo hints,*res;
	memset((void*) &hints,'\0', sizeof(struct addrinfo));
	
	hints.ai_family = AF_UNSPEC;
	
	int resultado = getaddrinfo(argv[1],argv[2], &hints,&res);
	
	if (resultado){
		std::cout << "getaddrinfo: "  <<  gai_strerror(resultado) << std::endl;
		exit(1);
		}
	
	
  struct addrinfo *p;
  char host[256];
  char serv[256];

  for(p = res; p != NULL; p = p->ai_next) {

    getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof(host), serv, NI_MAXSERV, NI_NUMERICHOST);
    std::cout << host << '\t' << p->ai_family << '\t' << p->ai_socktype <<  std::endl;
  }

  freeaddrinfo(res);
	
		
	return 0;
	}
