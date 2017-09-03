#include "client_for_frontend.h"
#include "client_for_msg_queue.h"

char* get_json_file_from_frontend(char* uuid_str, int sfd){
    printf("Connection setup\n");
    
    int n=0, b, tot;
    char rbuff[BUF_SIZE + 1]; 
    memset(rbuff, '0', sizeof(rbuff));

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

char* main_client_for_frontend_json(char* uuid_str){
    int sfd = init_sockfd(PORT_FRONTBACK_END, SERVER_IP_ADDR);
    char* filename = get_json_file_from_frontend(uuid_str, sfd);

    return filename;
}

/*
int main(int argc, char** argv){
    printf("Starting client\n");
    char* uuid_str = "08a97c1a045f4f0c8115c80234a7bbf6";
    get_json_file_from_frontend(uuid_str);
}*/
