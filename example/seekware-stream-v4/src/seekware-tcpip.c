// this code made by sulac. 
// seekware-streem <-> seekware-tcpip <-> PC winform
//            shared memory       tcp/ip socket 
//     maker            user
//                           server           client 
//
#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h>     
#include <stdlib.h>   
#include <netinet/in.h>  
#include <string.h>   
#include <fcntl.h>   
#include <sys/ipc.h>
#include <sys/shm.h>
#include "seekware-sharedMemory.h"

#define PORT 8080                       

int main(int argc, char **argv)
{  

    // shared memory setting 
    int shmid;
    int skey = 5678;
    sSharedMemory *shared_memory;

    shmid = shmget((key_t)skey, sizeof(int), 0666);
    if(shmid == -1)
    {
        perror("shmget failed\n");
        exit(0);
    }

    shared_memory = (sSharedMemory *)shmat(shmid, (void *)0, 0);
    if(!shared_memory)
    {
        perror("shmat failed : ");
        exit(0);
    }
    printf("shm id : %d\n", shmid);

    //test print shared memory data
    /*
        sSharedMemory temper = *shared_memory;
        printf("key[%d] : read shm data ---------\n", skey);
        printf("max temp[%0.1f], x,y= (%d, %d)\n", temper.max_t, temper.max_p.x, temper.max_p.y);
        printf("min temp[%0.1f], x,y= (%d, %d)\n", temper.min_t, temper.min_p.x, temper.min_p.y);
        printf("mode : %d \n", temper.mode_set);
    */

    // tcp/ip socket setting 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1;  
    int addrlen = sizeof(address);  
    char buffer[1024] = {0};     

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 )  
    {  
        perror("socket failed");   
        exit(EXIT_FAILURE); 
    } 

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, & opt, sizeof(opt)))  
    {   
        perror("setsockopt");  
        exit(EXIT_FAILURE);    
    }   

    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    {   
        perror("bind failed"); 
        exit(EXIT_FAILURE);
    } 
    if(listen(server_fd, 3)< 0) 
    {  
        perror("listen"); 
        exit(EXIT_FAILURE);  
    }  
    if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
    {   
        printf("server accept failed....\n");  
        exit(0); 
    }

    while(1)
    {   
        //read temper using shared memory. 
        sSharedMemory temper = *shared_memory;
        printf("key[%d] : read shm data ---------\n", skey);
        printf("max temp[%0.1f], x,y= (%d, %d)\n", temper.max_t, temper.max_p.x, temper.max_p.y);
        printf("min temp[%0.1f], x,y= (%d, %d)\n", temper.min_t, temper.min_p.x, temper.min_p.y);
        printf("mode : %d \n", temper.mode_set);

        //send max temp to client using tcp/ip
        char send_data[1024]={0,};
        sprintf(send_data,"start,%.1f,%d,%d,%0.1f,%d,%d,end", temper.max_t, temper.max_p.x, temper.max_p.y, temper.min_t, temper.min_p.x, temper.min_p.y);
        write(new_socket, send_data, strlen(send_data));
        printf("%s \n", send_data); 

        //recv data for change of thermal camera mode 
/*
        char recv_data = 0;
        read(new_socket, recv_data, sizeof(char));
        temper.mode_set = recv_data - '0';
        printf("mode set receved : %d", recv_data - '0');
*/
        sleep(1);
    }
}
