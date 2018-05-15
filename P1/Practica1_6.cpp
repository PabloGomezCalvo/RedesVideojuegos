#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//g++ Practica1_6.cpp -o P6 -lrt

int main(){

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];
	time (&rawtime);
	
	timeinfo = localtime(&rawtime);
	strftime (buffer,80,"Estamos en el año %G. Hoy es %A, %R.", timeinfo);
	puts (buffer);


return 0;

}
