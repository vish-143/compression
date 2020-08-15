
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<math.h>

typedef struct node{
	char c;
	int frequency;
	struct node* right;
	struct node* left;
	}node ;

void encode(int fd1,int fd2);
void decode(int fd1,int fd2);
int assigncodes(node* root,char* str,int l,int dif);
void printarray( int* frequency,int fd2,char* arr,int dif);
void printcode(int fd1,int dif,int fd2);
void sortdescending(int *frequency,char* arr,int dif);
void printdecoded(int fd1,int fd2,node* root);
//void chageassignedcode(int dif);
void changecode(int pos);
void ascii_to_string(char* str,unsigned char c);
unsigned char ascii_from_string(char* str);
//void printleaftree(node* root);
