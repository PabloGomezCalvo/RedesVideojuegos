#include <time.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

int main() {
	time_t t;
	
	char * c;
	c = ctime(&t);
	std::cout <<  time(0) << std::endl << c << std::endl;
    return 1;
}
