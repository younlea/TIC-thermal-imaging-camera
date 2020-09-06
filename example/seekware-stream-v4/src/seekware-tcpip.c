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

#define PORT 8080                       

int main(int argc, char **argv)
{  

    // shared memory setting 
    int shmid;
    int skey = 5678;
    float *shared_memory;

    shmid = shmget((key_t)skey, sizeof(float), 0666);
    if(shmid == -1)
    {
        perror("shmget failed\n");
        exit(0);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if(!shared_memory)
    {
        perror("shmat failed : ");
        exit(0);
    }
    printf("shm id : %d\n", shmid);

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
        float temper = *shared_memory;
        printf("key[%d] : read shm data : %f\n", skey, temper);

        //send max temp to client using tcp/ip
        char max_temp[5]={0,};
        sprintf(max_temp,"%.1fc",temper);
        write(new_socket, max_temp,strlen(max_temp));
        printf("%s \n", max_temp); 

        sleep(1);
    }
}
