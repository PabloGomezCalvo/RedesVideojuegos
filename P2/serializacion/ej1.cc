#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

class Jugador: public Serializable
{
public:
    Jugador(const char * _n, int16_t _x, int16_t _y):x(_x),y(_y)
    {
        strncpy(name, _n, 80);
    };

    virtual ~Jugador(){};

    void to_bin()
    {
		int32_t total = 80 * sizeof(char) + 2 * sizeof(int16_t);
//primero reservamos memoria.

        alloc_data(total);
//Creamos el puntero temporal para que nos lleve la direccion del buffer que vamos metiendo
        char * tmp = _data + sizeof(int32_t);
        memcpy(tmp, (void*)name, 80);
        tmp+= 80;
        memcpy(tmp, &x, sizeof(int16_t));
        tmp += sizeof(int16_t);
        memcpy(tmp, &y, sizeof(int16_t));
    }

    int from_bin(char * data)
    {
		char *tmp = data + sizeof(int32_t);
        memcpy(name, tmp, 80);
        tmp+= 80;
        memcpy(&x, tmp, sizeof(int16_t));
        tmp += sizeof(int16_t);
        memcpy(&y, tmp, sizeof(int16_t));
        tmp += sizeof(int16_t);

    }

public:
    char name[80];

    int16_t x;
    int16_t y;
};

int main(int argc, char **argv)
{
	
	char name[80];
    int16_t x = 2;
    int16_t y=1;
	
	Jugador one ("player one",x,y);
	
	one.to_bin();
	
	//abrimos el descriptor de fichero con la llamada open y vamos escribiendo con from_bin. Al final cerramos el descriptor de fichero 
	
	int fd = open("player one.txt", O_CREAT|O_TRUNC|O_RDWR, 0660);
	//el .data es como el buffer que usabamos en SO
    write(fd, one.data(), one.size());
    close (fd);
}
