
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<math.h>







void encode(int fd1,int fd2);
void decode(int fd1,int fd2);
void ascii_to_string(char* str,unsigned char c);
unsigned char ascii_from_string(char* str);
int getindex(char* str,int j);
