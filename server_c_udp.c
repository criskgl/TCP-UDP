
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>


int countDigits(int n){
    int count = 0;
    //Count number of digits
    while(n != 0)
    {
        // n = n/10
        n = n / 10;
        count = count + 1;
    }
    return count;
}



int sumString(char* s){
    
    int total = 0;
    
    for (int i = 0; i <= strlen(s)-2; i++) {
        total += (int)s[i]-48;
    } 

    return total; 
}

int isNumber(char* s) 
{ 
    for (int i = 0; i <= strlen(s)-2; i++) {
        if ((int)s[i] < 48 || (int)s[i] >57) {//other than numbers...
            return 0;
        }
    }
        
    return 1; 
} 

char* intToString(int n){

    int count = 0;
    int originalNumber = n;
    //Count number of digits
    while(n != 0)
    {
        // n = n/10
        n = n / 10;
        count = count + 1;
    }

    //Allocate memory only for digits we need
    
    char *resultStr = malloc(count);
    sprintf(resultStr, "%i", originalNumber);
    
    return resultStr;    
}

void  updatebuf(char * inputBuf, int resultSum){
    
    char* resultSumString = intToString(resultSum);
    int numberOfChars = countDigits(resultSum);
    for(int i = 0; i < numberOfChars; i++){
        inputBuf[i] = resultSumString[i];
    }
    //Add ending character
    inputBuf[numberOfChars] = '\0';
}

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *failureResponse = "From Server: Sorry, cannot compute!\n";
    
    //GET PORT NUMBER
    if (argc < 2 || argc > 3) 
	{ 
		printf("enter 2 arguments only eg.\"filename arg1 arg2 arg3!!\""); 
		return 0; 
	} 
    int portNumberListener = atoi(argv[1]);

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( portNumberListener ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
            read(new_socket , buffer, 1024);
     if(isNumber(buffer) == 0){
            send(new_socket , failureResponse , strlen(failureResponse) , 0 );         
    }else{
        int count = 0;
        int resultSum = 0;
        
        while(1){
            printf("LOOP  ENTRANCE #%i\n", count);

            //From buffer convert to2
            resultSum = sumString(buffer);
            //Convert result to string to be able to still pass it by buffer
            char* resultStr = intToString(resultSum);
            
            if(resultSum < 10){//Send back last 1 digit & close connection
                send(new_socket , resultStr , strlen(resultStr) , 0 );
                break;
            }
            send(new_socket , resultStr , strlen(resultStr) , 0 );

            updatebuf(buffer, resultSum);          

            count++;
        }
    }  
    return 0;
} 




