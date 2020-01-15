#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define size_t READ_SPEED = 1

#define EINVAL 22
#define EINTR  4 

serial_com newSerial_Com(){
serial_com * cs;
cs = (serial_com*)malloc(sizeof(serial_com));
cs->name = "/dev/ttyACM0";
cs->desc = -1;
return *cs;
}

int msleep(long msec)
{
    struct timespec ts;
    int res;
    int errno;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

serial_com * serial_open(serial_com * sc){
   sc->desc = open(sc->name,O_RDWR);
   return sc;
}

serial_com * serial_close(serial_com * sc){
    int success = close(sc->desc);
    if(success != -1){
        sc->desc = -1;
    }
    return sc;
}

void serial_read(serial_com sc, char* buf){
    read(sc.desc,buf,1);
    printf("Read %c\n",*buf);
}

void serial_write(serial_com sc,const char *message){
char c;
int index = 0;

    do{
        c = message[index];
        write(sc.desc,&c,1);
        index += 1;
    } while(c != '\0');
}

/*
void main(void){
    serial_com sc = newSerial_Com("/dev/ttyACM0",-1);
    char buf;
    char message[] = "ssssszzzzzdddddqqqqq";

    serial_open(sc);

    serial_write(sc,message);
    printf("%c, %d",sc->name[1],sc->desc);
    serial_close(sc);
   
}*/