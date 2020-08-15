/* Project - compression algorithm using huffman algorithm
   Author- Vishal Bhatane   */

/* basic idea- Take input string , form a binary tree to get code for every letter in data 
using the code for letter which we got from tree encode all characters of original  in new string 
which is compressed string, to decode compressed string we need our orginal tree.
this algorithm is quiet good when there's large data to be send since there will be repetition
of characters in big number*/

/* In this code , data to be encoded should be given in file and filename should be command line argument after compress
command ,from that data program will form tree,frequency and different characters will be stored initially  
and encoded data will be stored after that in compressed file whose name needed to be 
given as command line argument .when command will be given to decompress it will read data from first file . Using tree
program will decode it and decoded data will be written in file which is given as command line argument */ 
#include "functionshuff.h"



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



