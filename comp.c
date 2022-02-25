// Yarden Mirko : 209329416
// Dan Sasi : 313369423
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#define  SIZE 60
int main(int argc,char* arvg[]){
char buf1;//[SIZE+1];
char buf2;
int charReadA;
int charReadB;
int fd_a, fd_b;
int flag=1;
fd_a = open(arvg[1],O_RDONLY);
if(fd_a<0)
{
 write(1,"error",8);
 _exit(-1);
}
fd_b = open(arvg[2],O_RDONLY);
if(fd_b<0)
{
 write(1,"error",8);
  _exit(-1);
}
while(flag==1)
{
 charReadA=read(fd_a, &buf1, 1);
 charReadB=read(fd_b, &buf2, 1);
 if(charReadA!=charReadB)flag=0;
 else if(charReadA==0)break;
 else if(buf1!=buf2)flag=0;
}
close(fd_a);
close(fd_b);
if(flag==1)_exit(2);
else 
_exit(1);
}

