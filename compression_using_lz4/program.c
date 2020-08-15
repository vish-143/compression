/* Project - compression algorithm using LZ4
   Author- Vishal Bhatane   */

//lz4 is next version of lz method
//in this method a dictionary is used 
//to is used to store words so 
//size can be reduced efficiently.

#include "functionslz4.h"



int main(int argc,char* argv[]){
	
	
	
	int fd1,fd2;
	fd1=open(argv[2],O_RDWR|O_CREAT,S_IWUSR|S_IRUSR);
	fd2=open(argv[3],O_RDWR|O_CREAT,S_IWUSR|S_IRUSR);
	

	if(argv[1][1]=='c'){
	encode(fd1,fd2);
	}

	if(argv[1][1]=='u'){
	decode(fd1,fd2);
	}

	return 0;
}	



