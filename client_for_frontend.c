#include "client_for_frontend.h"
#include "client_for_msg_queue.h"

char* get_json_file_from_frontend(char* uuid_str, int sfd){
    printf("Connection setup\n");
    
    int n=0, b, tot;
    char rbuff[BUF_SIZE + 1]; 
    memset(rbuff, '0', sizeof(rbuff));

    //Sending Mode
    char mode = 'j';
    write(sfd, &mode, sizeof(char));

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

    sleep(1);
    close(sfd);

    return filename;
    
}

char* main_client_for_frontend_json(char* uuid_str){
    int sfd = init_sockfd(PORT_FRONTBACK_END, SERVER_IP_ADDR);
    char* filename = get_json_file_from_frontend(uuid_str, sfd);

    return filename;
}

void send_result_to_frontend(int sfd, char* uuid_str, char* output_filename){
    int n=0, b, tot;
    char rbuff[BUF_SIZE]; 
    memset(rbuff, '0', sizeof(rbuff));

    //Sending Mode
    char mode = 'r';
    write(sfd, &mode, sizeof(char));

    //Sending UUID
    send(sfd, uuid_str, UUID_SIZE_FOR_STR, 0);
    printf("UUID send\n");

    FILE *fp = fopen(output_filename, "rb");
    tot=0;
    if(fp != NULL){
        while((b = fread(rbuff, 1, sizeof(rbuff), fp)) > 0){ 
            send(sfd, rbuff, b, 0); 
        }
        if (fclose(fp)) { printf("error closing file."); exit(-1); }
        printf("No error in closing file or sending file\n");
    } else {
        printf("ERROR in FILE\n");
    }

    sleep(1);
    close(sfd);
}

void main_send_result(char* uuid_str, char* output_filename){
    int sfd = init_sockfd(PORT_FRONTBACK_END, SERVER_IP_ADDR);
    send_result_to_frontend(sfd, uuid_str, output_filename);
}

/*
int main(int argc, char** argv){
    printf("Starting client\n");
    char* uuid_str = "08a97c1a045f4f0c8115c80234a7bbf6";
    get_json_file_from_frontend(uuid_str);
}*/
