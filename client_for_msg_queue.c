#include "client_for_msg_queue.h"

int init_sockfd(int port, char* server_ip_addr){ 
    int sockfd = 0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        printf("\nERROR: Could not create socket\n");
        return -1; 
    }   
        
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(server_ip_addr);

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
        printf("\nERROR : Connect Failed\n\n");
        return -1; 
    }   

    return sockfd;
}

char* get_uuid_str_from_msg_queue(int sockfd){
    char frontend_or_msgqueue = 'm';
    write(sockfd, &frontend_or_msgqueue, sizeof(char));
    
    char* uuid_str = malloc(UUID_SIZE_FOR_STR);
    int br = read(sockfd, uuid_str, UUID_SIZE_FOR_STR);

    if(br < UUID_SIZE_FOR_STR){
        printf("Incorrect Read");
    }

    printf("UUID read as -> %s\n", uuid_str);
    
    sleep(1);
    close(sockfd);

    return uuid_str;
}

char* main_client_for_msg_queue(){
    int sockfd = init_sockfd(PORT, SERVER_IP_ADDR);
    char* uuid_str = get_uuid_str_from_msg_queue(sockfd);

    return uuid_str;
}
/*
int main(int argc, char** argv){
    int sockfd = init_sockfd();
    char* uuid_str = get_uuid_str_from_msg_queue(sockfd);
    //if(*uuid_str == EMPTY_STR){printf("Message Queue Empty\n");}
}*/
