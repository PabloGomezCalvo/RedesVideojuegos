#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

int main() {
   /* Comprobar la ocurrencia de error y notificarlo con la llamada perror(3) */      
    int  coderror = setuid(0);
	
	if(coderror == -1){
		char* cad =  strerror(coderror);
		std::cout <<"Codigo de error: " << cad << std::endl;
		}
	else
		std::cout << "TODO OK" << std::endl;
    return 1;
}
