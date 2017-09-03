#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_IP_ADDR "127.0.0.1"
#define PORT_FRONTBACK_END 5500
#define UUID_SIZE_FOR_STR 32
#define BUF_SIZE 256
#define FILE_BUF_SIZE 1024

#define TEMP_DATA_DIR "tmp_data/"

//int init_sockfd(struct sockaddr_in serv_addr);
char* get_json_file_from_frontend(char* uuid_str, int sfd);
char* main_client_for_frontend_json(char* uuid_str);
