
// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
 
   

int isNumber(char* s) 
{ 
    for (int i = 0; i <= strlen(s)-2; i++) {
        if ((int)s[i] < 48 || (int)s[i] >57) {//other than numbers...
            return 0;
        }
    }
        
    return 1; 
} 

int main(int argc, char const *argv[]) 
{ 

    //GET IP ADDRESS
    char *toIpAddress;
    toIpAddress = argv[1];
    //GET PORT NUMBER 
    int toPortNumber = atoi(argv[2]);

    int sock = 0; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(toIpAddress)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(toPortNumber); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    //CONNECTION ESTABLISHED

    //CLIENT INPUTS "NUMBER"
    printf("Enter string:");
    fflush(stdout);
    char str[50]; 
    fgets(str, 50, stdin); 

    //NUMBER GETS SENT
    send(sock , str , strlen(str) , 0 ); 
   
    
    read(sock , buffer, 1024); 
    if(isNumber(buffer) == 0){
        printf("From Server: %s", buffer);
        close(sock);
        return 0;
    }else{
               read(sock , buffer, 1024);
               printf("From server: %s", buffer);
        }
    printf("From Server2:");
    
    
    
    return 0; 
} 
