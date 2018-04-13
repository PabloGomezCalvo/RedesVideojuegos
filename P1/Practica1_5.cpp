#include <time.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
//g++ Practica1_5.cpp -o Practica1 -lrt

int main() {
	timespec t1;
	clockid_t c1;
	clock_gettime(c1,&t1);
	for(int i = 0; i < 10000; i++);
	
	timespec t2;
	clockid_t c2;
	clock_gettime(c2,&t2);
	
	std::cout << "Tiempo en nanosegundos de hacer 10000 veces i++: " << t2.tv_nsec - t1.tv_nsec << std::endl; 
	
    return 1;
}
