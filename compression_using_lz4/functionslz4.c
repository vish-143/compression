


#include"functionslz4.h"
//basic idea is  to form dictionary
//using that dictionary we can store characters
//method is LZ4

void encode(int fd1, int fd2){
	
	int size=100;//this is intially allocated size for dictionary 
	//we can change above size later
	int len=10;//this initial word length which can be change later
	
	char* str;
	char str2[9];
	str=(char*)malloc(len*sizeof(char));
	char str3[9];
	str2[0]='\0';
	
	char** arr;
	arr=(char**)malloc(size*sizeof(char*));
	int ret;
	unsigned char c;
	char str4[16];
	char ch;
	int i=0;
	int cursize=1;//this is variable to store current size of dictionary
	int curlen=0;//to store current length of string
	int found=0; //this variable to check if word is already present in dictionary
	int index=0;//to store index where word is found
	ret=read(fd1,&ch,1);
	while(ret!=0){
		
		str[curlen]=ch;
		curlen++;
		str[curlen]='\0';
		found=0;
		for(i=1;i<cursize;i++){
			if(strcmp(arr[i],str)==0&&curlen==strlen(arr[i])){
				found=i;
				break;
			}
		}

		if(found==0){
			arr[cursize]=(char*)malloc(len*sizeof(char));
			strcpy(arr[cursize],str);
			cursize++;
			
			if(index<15){
				//printf("%d\n",index);
				if(strlen(str2)==0){
					for(i=3;i>=0;i--){
						if(index%2==1)str2[i]='1';
						else str2[i]='0';
						index/=2;
					}
					ascii_to_string(str3,str[curlen-1]);
					//printf("%c %s\n",str[curlen-1],str3);
					for(i=4;i<8;i++){
						str2[i]=str3[i-4];
					}
					//printf("%s\n",str2);
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					for(i=0;i<4;i++){
						str2[i]=str3[i+4];
					}
					str2[4]='\0';
				}
				else{
					for(i=7;i>=4;i--){
						if(index%2)str2[i]='1';
						else str2[i]='0';
						index/=2;
					}
					c=ascii_from_string(str2);
					//printf("%s\n%s\n",str2,str+curlen-1);
					write(fd2,&c,1);
					
					write(fd2,&str[curlen-1],1);
					
					str2[0]='\0';
				}

			}
			else if(index<270){
				if(strlen(str2)==0){
					for(i=3;i>=0;i--){
						str2[i]='1';
						
					}
					c=index-15;
					ascii_to_string(str3,c);
					for(i=4;i<8;i++){
						str2[i]=str3[i-4];
					}
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					for(i=0;i<4;i++){
						str2[i]=str3[i+4];
					}
					ascii_to_string(str3,str[curlen-1]);
					for(i=4;i<8;i++){
						str2[i]=str3[i-4];
					}
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					for(i=0;i<4;i++){
						str2[i]=str3[i+4];
					}
					str2[4]='\0';
				}
				else{
					for(i=7;i>=4;i--){
						str2[i]='1';
					}
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					c=index-15;
					write(fd2,&c,1);
					write(fd2,&str[curlen-1],1);
					
					str2[0]='\0';
				}

			}
			else if(index<65805){
				if(strlen(str2)==0){
					c=255;
					write(fd2,&c,1);
					for(i=3;i>=0;i--){
						str2[i]='1';
						
					}
					index-=270;
					

					for(i=15;i>=0;i--){
						if(index%2==1)str4[i]='1';
						else str4[i]='0';
						index/=2;
					}
					for(i=4;i<=7;i++){
						str2[i]=str4[i-4];
						
					}
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					for(i=0;i<=7;i++){
						str2[i]=str4[i+4];
						
					}
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					for(i=3;i>=0;i--){
						str2[i]=str4[i+12];
						
					}

					ascii_to_string(str3,str[curlen-1]);
					for(i=4;i<8;i++){
						str2[i]=str3[i-4];
					}
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					for(i=0;i<4;i++){
						str2[i]=str3[i+4];
					}
					str2[4]='\0';
				}
				else{
					for(i=7;i>=4;i--){
						str2[i]='1';
					}
					c=ascii_from_string(str2);
					write(fd2,&c,1);
					c=255;
					write(fd2,&c,1);
					index-=270;
					for(i=7;i>=0;i--){
						if(index%2==1)str3[i]='1';
						else str3[i]='0';
						index/=2;

					}
 					
					for(i=7;i>=0;i--){
						if(index%2==1)str2[i]='1';
						else str2[i]='0';
						index/=2;

					}
 					c=ascii_from_string(str2);
					write(fd2,&c,1);
					c=ascii_from_string(str3);
					write(fd2,&c,1);
					
					
					write(fd2,&str[curlen-1],1);
					
					str2[0]='\0';
				}
			}
			index=0;
			curlen=0;

		}
		else {
			index=found;
		}
		if(cursize==size){
			size*=2;
			arr=(char**)realloc(arr,size*sizeof(char*));
		}
		if(curlen+1==len){
			len+=20;
			str=(char*)realloc(str,len*sizeof(char));
			
		}

		ret=read(fd1,&ch,1);
		
	}
	
	if(strlen(str2)!=0){
         	for(i=4;i<=7;i++){
			str2[i]='0';
		}
		c=ascii_from_string(str2);
		write(fd2,&c,1);
		}

	//for(i=1;i<cursize;i++)printf("%s\n",arr[i]);
	printf("%d\n",cursize);

	//printf("%d\n",len);
}

void decode(int fd1,int fd2){
	int size=100;
	char* str;
	str=(char*)malloc(9*sizeof(char));
	char* str2;
	str2=(char*)malloc(9*sizeof(char));
	char** arr;
	arr=(char**)malloc(size*sizeof(char*));
	int ret;
	int len=10,l;
	unsigned char c;
	char str4[17];

	int temp=1;
	unsigned char ch;
	int i=0;
	int cursize=1;//this is variable to store current size of dictionary
	
	
	int index=-1;//to store index where word is found
	ret=read(fd1,&ch,1);

	while(ret!=0){
		

		if(temp%2){
			ascii_to_string(str,ch);
			//printf("%s\n",str);
			for(i=0;i<4;i++){
				str4[i]=str[i];
			}
			index=getindex(str4,4);
			
			if(index<15){
				str4[0]='\0';
				for(i=0;i<4;i++){
					str2[i]=str[i+4];
				}
				str2[4]='\0';
				
			}
			else if(index==15){
				for(i=0;i<4;i++){
					str4[i]=str[i+4];
				}
				read(fd1,&ch,1);
				ascii_to_string(str,ch);
				for(i=4;i<8;i++){
					str4[i]=str[i-4];
				}
				index=getindex(str4,8);
				if(index<255){
					index+=15;

					for(i=0;i<4;i++){
						str2[i]=str[i+4];
					}
					str2[4]='\0';
				}
				else if(index==255){
					for(i=0;i<4;i++){
						str4[i]=str[i+4];
					}
					str4[4]='\0';
					read(fd1,&ch,1);
					ascii_to_string(str,ch);
					strcat(str4,str);
					read(fd1,&ch,1);
					ascii_to_string(str,ch);
					for(i=12;i<16;i++){
						str4[i]=str[i-12];
					}
					index=getindex(str4,16);
					index+=270;
					for(i=0;i<4;i++){
						str2[i]=str[i+4];
					}
					str2[4]='\0';

				}
			}
			read(fd1,&ch,1);
			ascii_to_string(str,ch);
			//printf("%s\n",str);
			for(i=4;i<8;i++){
				str2[i]=str[i-4];
			}
			for(i=0;i<4;i++){
				str4[i]=str[i+4];
			}
			str4[4]='\0';

			if(index==0){
				arr[cursize]=(char*)malloc(len*sizeof(char));
				c=ascii_from_string(str2);
				write(fd2,&c,1);
				arr[cursize][0]=c;
				arr[cursize][1]='\0';
				cursize++;
			}
			else{
				l=strlen(arr[index]);
				arr[cursize]=(char*)malloc(len*sizeof(char));
				c=ascii_from_string(str2);
				strcpy(arr[cursize],arr[index]);
				arr[cursize][l]=c;
				arr[cursize][l+1]='\0';
				write(fd2,arr[cursize],l+1);
				cursize++;
			}				

		}


		else{
			

			index=getindex(str4,4);
			str4[0]='\0';
			if(index==15){
				if(ch<255){
					index+=ch;
					}
				else if(ch==255){
					read(fd1,&ch,1);
					ascii_to_string(str,ch);
					strcpy(str4,str);
					read(fd1,&ch,1);
					ascii_to_string(str,ch);
					strcat(str4,str);
					index=getindex(str4,16);
					index+=270;
				}
				read(fd1,&ch,1);
			}
					
			if(index==0){
				arr[cursize]=(char*)malloc(2*sizeof(char));
				
				write(fd2,&ch,1);
				arr[cursize][0]=ch;
				arr[cursize][1]='\0';
				cursize++;
			}
			else{
				l=strlen(arr[index]);
				arr[cursize]=(char*)malloc(len*sizeof(char));
				
				strcpy(arr[cursize],arr[index]);
				arr[cursize][l]=ch;
				arr[cursize][l+1]='\0';
				write(fd2,arr[cursize],l+1);
				cursize++;
			}	


		}


		temp++;
		if(cursize==size){
			size*=2;
			arr=(char**)realloc(arr,size*sizeof(char*));
		}
		if(strlen(arr[cursize-1])+1==len){
			len+=20;
		}

  		ret=read(fd1,&ch,1);

	}
	//for(i=1;i<cursize;i++)printf("%s\n",arr[i]);
	printf("%d\n",cursize);
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

int getindex(char* str,int j){
	int ans=0;int i=0;
	while(j--){
		ans+=(str[j]-'0')*pow(2,i);
		i++;
	}
	return ans;
}
		







	
