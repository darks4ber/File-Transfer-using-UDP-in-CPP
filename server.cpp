#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
#define maxlen 70000
#define mlen 100000

int main()
{
    char fileName[100];
    char fileBuffer[2000],caufile[maxlen];
    char *vfilep;
    int aufile[70000],vfile[mlen];      //aufile is for audio and vfile is for video
    int sd,connfd;	 //sd-Socket Decriptor 
	socklen_t len; 
    
    for(int i=0;i<=100;i++)
        fileName[i]='\0';

     struct sockaddr_in servaddr,cliaddr;    //struct class and it's member variables
 //         ------------------------------Creation of Socket-----------------------------

    sd=socket(AF_INET,SOCK_DGRAM,0);

    if(sd==-1)
    {
        cout<<"Socket not created in server"<<endl;
        exit(0);
    }
    else
    	cout<<"Socket created in server"<<endl;


bzero(&servaddr,sizeof(servaddr));

//Adding parameter to socket     //Initialisation Member variables
servaddr.sin_family=AF_INET;        //for UDP connection
servaddr.sin_addr.s_addr=INADDR_ANY;    //for local host(server and client are both on the local host and the communicaton will take place)
servaddr.sin_port=htons(6666);   //set the port number

memset(&(servaddr.sin_zero),'\0',8);     //setting the sin_zero parameter as null using function memset(memoryset)



//        ----------------------------Binding the Socket-------------------------------------


if( bind(sd,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)
    cout<<"Not binded"<<endl;
    else
    cout<<"Binded"<<endl;

    len=sizeof(cliaddr);
    int choice=1;
    while(1)
    {
        char num;
        recvfrom(sd,&num,sizeof(num),0,(struct sockaddr *)&cliaddr,&len);  //recvfrom is a function used for UDP transfer 1024 is memory of flag 0 and it's length
        //file name will be saved in variale fileName 
        
		choice=num;
		//int fsize =strlen(fileBuffer);

		if(choice==1)
		{		
			//Case for Text files
			
				recvfrom(sd,fileName,1024,0,(struct sockaddr *)&cliaddr,&len);
				cout<<"NAME OF THE TEXT FILE RECEIVED: " <<endl<<fileName;
        		FILE *fp;
        		cout<<"Contents in the received text file: "<<endl;
        		recvfrom(sd,fileBuffer,1024,0,(struct sockaddr *)&cliaddr,&len);  //recvfunction is a function used for UDP transfer 1024 is memory of flag 0 and it's length
        		cout<<endl<<fileBuffer;

        		int fsize =strlen(fileBuffer);  //fsize is used to save the memory of filebuffer 
				
				fp=fopen(fileName,"w");
				if(fp)
				{
					fwrite(fileBuffer,fsize,1,fp);
					cout<<"File received successfully"<<endl;	
				}
				else
					cout<<"Can't create to output file";
		
				memset(fileName,'\0',sizeof(fileName));
				fclose(fp);
		}
		//Case for audio file
		else if(choice==2)
		{

				recvfrom(sd,fileName,1024,0,(struct sockaddr *)&cliaddr,&len);	//to recieve filename
				cout<<"Name of audio file received"<<endl<<fileName;
				FILE *afp;		//afp is pointer varible
				int numbytes;
				afp=fopen(fileName,"w");	//Opening audio file in write format
				size_t afsize;	//datatype of unsigned intergral type
				afsize=recvfrom(sd,aufile,700000,0,(struct sockaddr *)&cliaddr,&len); //To receive contents of the file name which will be saved in the aufile
				if(afp)
				{
					fwrite(aufile,afsize,1,afp); //running fwrite to save the file(aufile) onto the server side and If it's non zero,then the operation was successfull
					cout<<"File received successfully"<<endl;
				}
				else
					cout<<"Can't open output file";
				memset(fileName,'\0',sizeof(fileName));	//memset, fileName contents are set to null so that we can use it again
				fclose(afp);
				
		}
			//Case for receiving Video file	
		else if(choice==3)
		{
				recvfrom(sd,fileName,1024,0,(struct sockaddr *)&cliaddr,&len);
				cout<<"Video file name received : "<<endl<<fileName;
				FILE *vfp;
				vfp=fopen(fileName,"w");
				size_t vfsize;
				vfsize=recvfrom(sd,vfile,100000,0,(struct sockaddr *)&cliaddr,&len);

				if(vfp)
				{
					fwrite(vfile,vfsize,1,vfp);
					cout<<"File received successfully"<<endl;
				}
				else
					cout<<"Can't open output file"<<endl;
				fclose(vfp);
				
		}	
		else if(choice==4)
		{
				close(sd);
				break;
			
		}
	}
	return 0;
}
