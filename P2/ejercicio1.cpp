#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
struct addrinfo hints, *res;




int main(int argc, const char* argv[])
{
	hints.ai_family = AF_UNSPEC;
	
	int resultado = getaddrinfo(argv[1],NULL, &hints,&res);
	
	if (resultado){
		std::cout << "getaddrinfo: "  <<  gai_strerror(resultado) << std::endl;
		exit(1);
		}
	
	
  struct addrinfo *p;
  char host[256];

  for(p = res; p != NULL; p = p->ai_next) {

    getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
    std::cout << host << '\t' << p->ai_family << '\t' << p->ai_socktype <<  std::endl;
  }

  freeaddrinfo(res);
	
		
	return 0;
	}
