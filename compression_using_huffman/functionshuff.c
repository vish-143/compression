#include "functionshuff.h"

//declare the array for storing the values
char codearr[256][30];
void encode(int fd1,int fd2){
	//now declare character array to store differnt characters
	char arr[256];
	//to store frequency of characters
        int frequency[256]={0};  
	
	int dif=0;  //variable to take count of different characters in paragraph
	
	int i,j ;  // variables to use in loop
	char ch;  //varaiable to scan characters
	int ret=0;  //after using using function on file to store return value of function
	int found;//variable to search chacters in array
	

	/*below while loop is used
	to find total number of 
	diffrent characters in input
	file and how many times every character occurs*/
	
	//differnt characters and their respective
	//frequency is stored in character array arr and
	//integer array frequency respectively

	ret=read(fd1,&ch,1);
	while(ret!=0){
		
		found=-1;
		for(i=0;i<dif;i++){
			if(arr[i]==ch){
				found=i;
				break;
				}
			}
		if(found==-1){
			arr[dif]=ch;
			frequency[dif]++;
			dif++;
			}
		else if(found!=-1){
			frequency[found]++;
			}

		ret=read(fd1,&ch,1);
		}

       
	/*there are 2 corner case for this algorithm
	which doesn't follow in general rule
 	that is when input file contain no
	character or only
	one differnt character ,for this 
	case we need to see if dif==1
	while compresssing and decompressing and
	we should handle it separately as in 
	general it will give segfault since
	there will be only one node in tree
	which will be leaf node, so we can't
	assign code to it as left or right traversal is 
	impossible since node->left=node->right=NULL*/
	
	//so to cover this corner case we are done after
	//printing character and it's frequency
	//below both cases are covered
	if(dif==0){
		i=0;
		write(fd2,&i,4);
		exit(0);
		}
	if(dif==1){
		i=1;
		write(fd2,&i,4);
		write(fd2,arr,1);
		write(fd2,frequency,4);
		exit(0);
		}
	
	/*for(i=0;i<dif;i++){
	printf("%c %d\n",arr[i],frequency[i]);}
	this loop was used to check correctness
         */
	


	/*After knowing differnt characters and
	and their frequency in input file 
	our task is to sort them in descending order
	to form tree
				*/

	//below function sort frequency in descending order and
	//and changes respective characters position accordingly
	sortdescending(frequency,arr,dif);
	int p=dif;

	//below function printarray prints
	//characters and their frequency
	//in sorted descending order in
	//compressed file
	//so while decompressing we can
	//rebuild tree to get
	//specific codes for characters
	

        printarray(  frequency, fd2, arr,dif);
	

	


	//to create leaf nodes for every character
	//array is created  
	//this is array of pointers
	//that is array of pointer node*
	//node* points to node that is stores adress of node
	//in which character and frequency is stored
	//every element of array stores
	//adress of node
	node** nodearr;
	nodearr=(node**)malloc(256*sizeof(node*));



	/*below for loop is used to create leaf nodes of all 
	differnt chracters*/
	for(i=0;i<dif;i++){
		node* temp;
		temp=(node*)malloc(sizeof(node));
		temp->frequency=frequency[i];
		temp->c=arr[i];
		temp->right=NULL;
		temp->left=NULL;
		nodearr[i]=temp;
		}
	
	
	


	/*for(i=0;i<dif;i++){
		printf("%c %d\n",nodearr[i]->c,nodearr[i]->frequency);}*/


	/*below while loop is to form tree using leaf nodes*/
	while(p!=1){
		node* temp;
		int newfrequency=frequency[p-1]+frequency[p-2];// to form internal nodes
		temp=(node*)malloc(sizeof(node));
		temp->frequency=newfrequency;
		temp->c='`';//for internal nodes character '`' is used to reprsent it
		temp->right=nodearr[p-2];
		temp->left=nodearr[p-1];
		int pos=0;//position to insert new formed node
		for(j=0;j<p;j++){
			if(frequency[j]<=newfrequency){
				pos=j;
				break;
				}
			}
		for(j=p-3;j>=pos;j--){
			frequency[j+1]=frequency[j];
			nodearr[j+1]=nodearr[j];
			
			}
		frequency[pos]=newfrequency;
		nodearr[pos]=temp;
		p--;
		}


	/* printleaftree(nodearr[0]); function was created to check
	correctness of program ,using depth first traversal 
 	tree is traversed in function */





	/*now we need to assign codes to every character using tree*/
	char str2[30] ;
	
	//for assigning codes
	//recursion is used 
	//below we have called function assigncodes
	//In this function codes for every letter are 
	//stroed in 2D array which is globally declared
	//first column of 2D array
	//represents letter and their codes
	//are written in subsequent column of 
	//every row.

	assigncodes(nodearr[0],str2,0,0);//assigncodes(&codea,nodearr[0],str2,0,0);
	
	
	/*for(i=0;i<dif;i++){
	printf("%c %s\n",codearr[i][0],codearr[i]+1);} - used for checking correctness*/

	//below lseek is used to set cursor of
	//file1 to 0th position
	//as we had already traversed file1
	//it was set to last postion
	//so below is reset of cursor 
	//to initial posiion
	lseek(fd1,SEEK_SET,0);

	//below printcode function prints
	//codes for every letter in file 1 to
	//compressed file in encoded format
	
	printcode(fd1,dif,fd2);

	}

void decode(int fd1,int fd2){
	char arr[256];//to store differnt letters iin array
	int frequency[256];//to store frequency of charcters
	int i,j,dif,p;

	//at start of compressed file
	//number of differnt characters were stored 
	//so first we need to scan it
	read(fd1,&dif,4);

	//now those differnt character and their
	//respected frequency is stored
	//so we need to scan characters and
	//their frequency now
	//below in for loop
	//scanned differnt characters
	//are stored in character array
	//named as arr
	//and their respective frequency is 
	//stored in intger array named as 
	//frequency.
	for(i=0;i<dif;i++){
		read(fd1,arr+i,1);
		read(fd1,frequency+i,4);
		}


	/*there were 2 corner case for this algorithm
	which weren't following  general rule
 	that is when input file contain no
	character or only
	one differnt character ,for this 
	case we need to see if dif==1
	while compresssing and decompressing and
	we should handle it separately as in 
	general it will give segfault since
	there will be only one node in tree
	which will be leaf node, so we can't
	assign code to it as left or right traversal is 
	impossible since node->left=node->right=NULL*/

	//below those 2 cases are covered while decompressing
	
	if(dif==0){
		exit(0);
		}
	if(dif==1){
		for(i=0;i<frequency[0];i++){
			write(fd2,arr,1);
			}
		exit(0);
		}


	/*for(i=0;i<dif;i++){
		printf("%c %d\n",arr[i],frequency[i]);}
	this loop was used to check correctness */

	//now need to build tree from data




	//to create leaf nodes for every character
	//array is created  
	//this is array of pointers
	//that is array of pointer node*
	//node* points to node that is stores adress of node
	//in which character and frequency is stored
	//every element of array stores
	//adress of node
	node** nodearr;
	nodearr=(node**)malloc(256*sizeof(node*));



	/*below for loop is used to create leaf nodes of all 
	differnt chracters*/
	for(i=0;i<dif;i++){
		node* temp;
		temp=(node*)malloc(sizeof(node));
		temp->frequency=frequency[i];
		temp->c=arr[i];
		temp->right=NULL;
		temp->left=NULL;
		nodearr[i]=temp;
		}
	p=dif;
	/*below loop is used to form tree using leaf
		nodes*/
	while(p!=1){
		node* temp;
		int newfrequency=frequency[p-1]+frequency[p-2];// to form internal nodes
		temp=(node*)malloc(sizeof(node));
		temp->frequency=newfrequency;
		temp->c='`';// character '`' is used to reprsent internal nodes
		//it can be used in leaf nodes also
		//so we are not sacrifying it

		temp->right=nodearr[p-2];
		temp->left=nodearr[p-1];
		int pos=0;//position to insert new formed node
		for(j=0;j<p;j++){
			if(frequency[j]<=newfrequency){
				pos=j;
				break;
				}
			}
		for(j=p-3;j>=pos;j--){
			frequency[j+1]=frequency[j];
			nodearr[j+1]=nodearr[j];
			}
		frequency[pos]=newfrequency;
		nodearr[pos]=temp;
		p--;
		}
	
	/* printleaftree(nodearr[0]); function was created to check
	correctness of program ,using depth first traversal 
 	tree is traversed in function */

	node* root;
	root=nodearr[0];

	//now tree is formed
	//so we need to print 
	//compressed code in uncompressed file
	//this is done in below function
	printdecoded(fd1,fd2,root); 
	
	}



//below code is to assign 
//specific coede to every character 
//using tree
//function assigncode is recurively called
//for internal nodes
//function is called again
//giving left node and right node
//as root adress and strings formed
//with it
//whenever leaf node is encounterd
//character in that node is sored in 
//codearr array's first column
//and then code for that character 
//which we get as function argument
//stored after character in a row
//in codearr array
//while assigning codes
//while traversing to right
//1 is appended to code
//while traversing left 0
//is appended

int assigncodes(node* root,char* str,int l,int dif){
	if(root->left==NULL&&root->right==NULL){
		
		
		codearr[dif][0]=root->c;
		
		strcpy(codearr[dif]+1,str);
		
		//printf("%d %s entered\n",dif,codearr[dif]+1);
		dif++;
		//printf("%c\n",root->c);
		return dif;
		
		}
	
	//char str2[30];
	//strcpy(str2,str);


	str[l]='0';
	l++;
	str[l]='\0';
	dif=assigncodes(root->left,str,l,dif);
	str[l]='\0';
	l--;
	str[l]='1';
	l++;
 	
	dif=assigncodes(root->right,str,l,dif);	
	
	return dif;

	}


/*below is printarray function
in this function initially number of different 
characters are printed 
after that every character with their 
respective frequency in 
descending order is printed 
so while decompressing we can scan initially  
total number of different charcters follwed by
characters and their frequency to build  tree to 
get codes for characters	*/

void printarray( int* frequency,int fd2,char* arr,int dif){
	
	int i;write(fd2,&dif,4);
	for(i=0;i<dif;i++){
		write(fd2,arr+i,1);
		write(fd2,frequency+i,4);
		}


	}




//below is printcode function
//this function is used to
//print input file into new
//in a decoded language
void printcode(int fd1,int dif,int fd2){
	int i,j,ret,k;
	unsigned char ch,c;unsigned char p1=0,p3;
	char str[9];
	ret=read(fd1,&ch,1);
	
	while(ret!=0){

	   
		for(j=0;j<dif;j++){
			if(ch==codearr[j][0]){
				p3=strlen(codearr[j]+1);k=1;
				if(p1+p3>8){
					while(k<=p3){
						for(i=p1;i<8&&k<=p3;i++){
							str[p1]=codearr[j][k];
							p1++;
							k++;
							}
						if(p1==8){	
							c=ascii_from_string(str);
							write(fd2,&c,1);
							p1=0;
							}
						}
					
					}
				else {
					while(codearr[j][k]!='\0'){
						str[p1]=codearr[j][k];
						p1++;
						k++;
						}
					}
				}
			}
		
		ret=read(fd1,&ch,1);	
	   }
	c=ascii_from_string(str);
	write(fd2,&c,1);
	//write(fd2,&p1,1);

	}
void sortdescending(int *frequency,char* arr,int dif){
	int i,j,temp;char temp3;
	for(i=0;i<dif;i++){
		for(j=0;j<dif-i-1;j++){
			if(frequency[j+1]>frequency[j]){
				temp=frequency[j];
				
				temp3=arr[j];
				
				frequency[j]=frequency[j+1];
				arr[j]=arr[j+1];
				frequency[j+1]=temp;
				
				arr[j+1]=temp3;
				}
			}
		}
	}



//below function scans characters
//from input compressed file
//and traverse tree accordingly
//when it reaches leaf node
//function prints
//character in that leaf node
//to uncompressed/decoded file

void printdecoded(int fd1,int fd2,node* root){
	
	int ret,i;
	unsigned char ch;
	char str[9];//={'1','1','1','1','0','1','0','0'};
	node* temp;
	//ch=ascii_from_string(str);
	//printf("%d\n",ch);
	//ascii_to_string(str,ch);
	//printf("%s\n",str);
	ret=read(fd1,&ch,1);
	temp=root;
	while(ret!=0){
		
		
		ascii_to_string(str,ch);
	
		for(i=0;i<8;i++){
			
			if(str[i]-'0'==0){
				temp=temp->left;
				
				
				}
			else if(str[i]-'1'==0){
				temp=temp->right;
					
			}
			if(temp->left==NULL&&temp->right==NULL){
				write(fd2,&(temp->c),1);
				temp=root;
				
				}
			
			}
		ret=read(fd1,&ch,1);
		}			



	} 


/*
below function 
was created to check correctness 
if letters are getting assigned
and if tree is formed as we had imagined
can be checked is using below function
It used  depth first trversal
to print all nodes


void printleaftree(node* root){
	if(root->left!=NULL){
		printleaftree(root->left);
		printleaftree(root->right);
		}
	else printf("%c\n",root->c);
	}


*/

//below function is to change codes
//of characters which has more than 
//8 bits in their representation
/*void chageassignedcode(int dif){
	int i=0;
	for(i=0;i<dif;i++){
		if(strlen(codearr[i]+1)>8){
			changecode(i);
			}
		}
	}
*/
//below is to change code of
//character to it's ascii value
void changecode(int pos){
	char str[9];
	ascii_to_string(str,codearr[pos][0]);
	strcpy(codearr[pos]+1,str);
	}

//to get ascii code of character in 
//character below function works
void ascii_to_string(char* str,unsigned char c){
	str[8]='\0';
	int i;
	for(i=7;i>=0;i--){
		if(c%2==1){
			str[i]='1';
			}
		else str[i]='0';
		c/=2;
		}
	}

//below is function to get
//ascii value fromm string
unsigned char ascii_from_string(char* str){
	int i=0,j;
	unsigned char c=0;
 	for(j=7;j>=0;j--){
		c+=(str[j]-'0')*pow(2,i);
		i++;
		}
	return c;
	}

//end of file free to raise any issues
