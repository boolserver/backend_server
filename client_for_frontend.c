#include "client_for_frontend.h"
/*
int init_sockfd(struct sockaddr_in serv_addr){
    int sfd = 0;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_FRONTBACK_END);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDR);
    
    return sfd;
}
*/
char* get_json_file_from_frontend(char* uuid_str){
    int sfd = 0;

    struct sockaddr_in serv_addr;
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_FRONTBACK_END);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDR);
    
    int n=0, b, tot;
    char rbuff[BUF_SIZE + 1]; 
    memset(rbuff, '0', sizeof(rbuff));
    //char sendbuffer[BUF_SIZE];
    
    //int sfd = init_sockfd(serv_addr);

    b=connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (b==-1) {
        perror("Connect");
        //return "1";
    }
    printf("Connection setup\n");

    //sending UUID str
    send(sfd, uuid_str, UUID_SIZE_FOR_STR, 0);
    printf("UUID send\n");
    //Creating Filename
    char *filename = malloc(strlen(uuid_str) + strlen(TEMP_DATA_DIR) + strlen(".json") + 1);
    size_t filename_size = strlen(filename);
    
    strcpy(filename, TEMP_DATA_DIR);
    strcat(filename, uuid_str);
    strcat(filename, ".json");
    printf("Filename -> %s and len-> %d\n", filename, strlen(filename));

    FILE *fp = fopen(filename, "wb");
    if(fp == NULL){
        perror("File");
        //return "2";
    }

    while( (b = recv(sfd, rbuff, sizeof(rbuff), 0))> 0 ) {
        tot+=b;
        printf("Bytes recived -> %i\n", b);
        fwrite(rbuff, 1, b, fp);
    }

    printf("Closing file\n");
    fclose(fp);

    printf("UUID for the file->%s\n", uuid_str);

    close(sfd);

    return filename;
    
}
/*
int main(int argc, char** argv){
    printf("Starting client\n");
    char* uuid_str = "08a97c1a045f4f0c8115c80234a7bbf6";
    get_json_file_from_frontend(uuid_str);
}*/
