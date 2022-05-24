// #include<iostream>
// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>
// #include<string.h>
// #include<sys/types.h>
// #include<sys/socket.h>
// #include<arpa/inet.h>
// #include<netinet/in.h>
// using namespace std;

// int main()
// {
//     int fd;
//     //afileName-audio file name, vfileName-Video file name, file_Buffer-text file
//     char fileName[2000],afileName[2000],vfileName[2000],file_Buffer[2000],c,caufile[70000],aufile[7000000],vfile[1000000];
//     struct sockaddr_in servaddr;


// //  ------------------------------Creating Socket File Descriptor--------------------------------
// if ((fd=socket(AF_INET,SOCK_DGRAM,0))<0)
// {
//     perror("Socket Creation Failed");
//     exit(EXIT_FAILURE);
// }    
// memset(&servaddr,0,sizeof(servaddr));
// bzero(&servaddr,sizeof(servaddr));



// //-------------------------------Filling Server Information---------------------------------------
// servaddr.sin_family=AF_INET;
// servaddr.sin_port=htons(6666);
// servaddr.sin_addr.s_addr=INADDR_ANY;    //This is for local host machine(single macine)
// //servaddr.sin_addr.s_addr=inet_addr("192.168.99.214");

// int choice=1;

// while(choice=!2)
// {
//     cout<<"Enter \n 1.TEXT \n 2.AUDIO \n 3.VIDEO\n4.EXIT";
//     cin>>choice;   
//     char num=choice;
//     //Input the choice from the user, note the variable is char as we can only send char type in communication(as sendto and recvfrom only receives char type)

//                          //Sending the choice to Server
//     sendto(fd,&num,sizeof(num),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr ));

// switch(choice)
// {
//     //In this code we'll use sendto() function rather than recvfrom() bcoz we need to send the files
//     case 1: //for text file
//         cout<<"Enter text file name to send: "<<endl;
//             cin>>fileName;
//             sendto(fd,fileName,strlen(fileName),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));        //Sending filename to server side
            
//             FILE *fp;
//             fp=fopen(fileName,"r"); //Opening this filename in read mode

//             if(fp)
//             {
//                 //After opening it we're copying the file contents in the fileBuffer
//                 cout<<"Reading file contents: "<<endl;
//                 fseek(fp,0,SEEK_END);
//                 size_t file_size=ftell(fp); 
//                 fseek(fp,0,SEEK_SET);
//                 if(fread(file_Buffer,file_size,1,fp)<=0)    //copied into the file_Buffer using fread()
//                 {
//                     cout<<"Unable to copy file into buffer or empty file";
//                     exit(1);
//                 }
//             }    
//             else
//             {
//                 cout<<"Can't open file "<<endl;
//                 exit(0);
//             }
//             cout<<"File contents to send "<<file_Buffer<<endl; 
//             if(sendto(fd,file_Buffer,strlen(file_Buffer),0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr))<0)   //sending the fileBuffer i.e. content of the file
//             {
//                 cout<<"File was not sent"<<endl;
//             }
//             else
//             {
//                 cout<<"File Sent"<<endl;
//             }
//                 fclose(fp);
//                 break;
//     case 2:
//         //For Audio File
//         cout<<"Enter audio file name to send: "<<endl;
//         cin>>afileName;
//         sendto(fd,afileName,strlen(afileName),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));  //sending the name of the file
//         FILE *afp;
//         afp=fopen(afileName,"r");
//         fseek(afp,0,SEEK_END);
//         size_t afsize=ftell(afp);       //to see/get the size we use size_t (size_t is unsigned integral type as we don't know the size and type of data)
//         fseek(afp,0,SEEK_SET);    //fseek to last point to get the size of audio file  

//         if(afp)
//         {
//             cout<<"Reading file contents"<<endl;
//             if(fread(aufile,afsize,1,afp)<=0)
//             {
//                 cout<<"Unable to copy file into buffer or empty file"<<endl;
//                 exit(1);
//             }
//         }
//         else
//         {
//             cout<<"Could not read audio file";
//             exit(0);
//         }
//         if(sendto(fd,aufile,afsize,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr * ))<0)    //Sending the contents of the file
//         {
//             cout<<"File was not sent "<<endl;
//         }
//         else
//         {
//             cout<<"File Sent";
//         }
//         fclose(afp);
//         break;
    
//     case 3:
//         //For Video File
//         cout<<"Enter the video file name to send "<<endl;
//         cin>>vfileName;
//         sendto(fd,vfileName,strlen(vfileName),0,(struct sockaddr* )&servaddr,sizeof(struct sockaddr)); //Sendint the name of video file
//         FILE *vfp;
//         vfp=fopen(vfileName,"r");
//         fseek(vfp,0,SEEK_END);
//         size_t vfsize=ftell(vfp);  //Getting the size of the video file using size_t
//         fseek(vfp,0,SEEK_SET);     //Setting the pointer at last to get the size of video file     

//         if(vfp)
//         {
//             cout<<"Reading file contents"<<endl;
//             if(fread(vfile,1,vfsize,vfp)<=0)
//             {
//                 cout<<"Unable to copy video file into buffer or empty file"<<endl;
//                 //exit(1);
//             }
//         }
//         else
//         {
//             cout<<"Could not read video file: "<<endl;
//             exit(0);
//         }
//         if(sendto(fd,vfile,vfsize,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr ))<0)
//         {
//             cout<<"File was not sent"<<endl;
//         }
//         else
//         {
//             cout<<"File Sent";
//         }
//         fclose(vfp);
//         break;
//     case 4:
//         close(fd);
//         break;

                
            
// }

// }
// }






#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;

int main()
{
    int fd;
    //afileName-audio file name, vfileName-Video file name, file_Buffer-text file
    char fileName[2000],afileName[2000],vfileName[2000],file_Buffer[2000],c,caufile[70000],aufile[7000000],vfile[1000000];
    struct sockaddr_in servaddr;


//  ------------------------------Creating Socket File Descriptor--------------------------------
if ((fd=socket(AF_INET,SOCK_DGRAM,0))<0)
{
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
}    
memset(&servaddr,0,sizeof(servaddr));
bzero(&servaddr,sizeof(servaddr));



//-------------------------------Filling Server Information---------------------------------------
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(6666);
servaddr.sin_addr.s_addr=INADDR_ANY;    //This is for local host machine(single macine)
//servaddr.sin_addr.s_addr=inet_addr("192.168.99.214");

int choice=1;

// while(choice=!4)
// {
    cout<<"Enter \n 1.TEXT \n 2.AUDIO \n 3.VIDEO \n4.EXIT";
    cin>>choice;   
    char num=choice;
    //Input the choice from the user, note the variable is char as we can only send char type in communication(as sendto and recvfrom only receives char type)

                         //Sending the choice to Server
    sendto(fd,&num,sizeof(num),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr ));

    if(choice==1)
    {
    //In this code we'll use sendto() function rather than recvfrom() bcoz we need to send the files
     //for text file
            cout<<"Enter text file name to send: "<<endl;
            cin>>fileName;
            sendto(fd,fileName,strlen(fileName),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));        //Sending filename to server side
            
            FILE *fp;
            fp=fopen(fileName,"r"); //Opening this filename in read mode

            if(fp)
            {
                //After opening it we're copying the file contents in the fileBuffer
                cout<<"Reading file contents: "<<endl;
                fseek(fp,0,SEEK_END);
                size_t file_size=ftell(fp); 
                fseek(fp,0,SEEK_SET);
                if(fread(file_Buffer,file_size,1,fp)<=0)    //copied into the file_Buffer using fread()
                {
                    cout<<"Unable to copy file into buffer or empty file";
                    exit(1);
                }
            }    
            else
            {
                cout<<"Can't open file "<<endl;
                exit(0);
            }
            cout<<"File contents to send "<<file_Buffer<<endl; 
            if(sendto(fd,file_Buffer,strlen(file_Buffer),0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr))<0)   //sending the fileBuffer i.e. content of the file
            {
                cout<<"File was not sent"<<endl;
            }
            else
            {
                cout<<"File Sent"<<endl;
            }
                fclose(fp);
    }
    else if(choice==2)
    {

    
        //For Audio File
        cout<<"Enter audio file name to send: "<<endl;
        cin>>afileName;
        sendto(fd,afileName,strlen(afileName),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));  //sending the name of the file
        FILE *afp;
        afp=fopen(afileName,"r");
        fseek(afp,0,SEEK_END);
        size_t afsize=ftell(afp);       //to see/get the size we use size_t (size_t is unsigned integral type as we don't know the size and type of data)
        fseek(afp,0,SEEK_SET);    //fseek to last point to get the size of audio file  

        if(afp)
        {
            cout<<"Reading file contents"<<endl;
            if(fread(aufile,afsize,1,afp)<=0)
            {
                cout<<"Unable to copy file into buffer or empty file"<<endl;
                exit(1);
            }
        }
        else
        {
            cout<<"Could not read audio file";
            exit(0);
        }
        if(sendto(fd,aufile,afsize,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr))<0)    //Sending the contents of the file
        {
            cout<<"File was not sent "<<endl;
        }
        else
        {
            cout<<"File Sent";
        }
        fclose(afp);
        
    }
    
        //For Video File
    else if(choice==3)
    {

        cout<<"Enter the video file name to send "<<endl;
        cin>>vfileName;
        sendto(fd,vfileName,strlen(vfileName),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr)); //Sendint the name of video file
        FILE *vfp;
        vfp=fopen(vfileName,"r");
        fseek(vfp,0,SEEK_END);
        size_t vfsize=ftell(vfp);  //Getting the size of the video file using size_t
        fseek(vfp,0,SEEK_SET);     //Setting the pointer at last to get the size of video file     

        if(vfp)
        {
           // cout<<"Reading file contents"<<endl;
            if(fread(vfile,1,vfsize,vfp)<=0)
            {
                cout<<"Unable to copy video file into buffer or empty file"<<endl;
               // exit(1);
            }
        }
        else
        {
            cout<<"Could not read video file: "<<endl;
            exit(0);
        }
        if(sendto(fd,vfile,vfsize,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr ))<0)
        {
            cout<<"File was not sent"<<endl;
        }
        else
        {
            cout<<"File Sent"<<endl;
        }
        fclose(vfp);
        
    }
    else if(choice==4)
    {
        close(fd);
    }

}                
            

//}




