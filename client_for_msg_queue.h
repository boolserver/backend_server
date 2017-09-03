#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>
#include <netdb.h>

#define SERVER_IP_ADDR "127.0.0.1"
#define PORT 5000
#define UUID_SIZE_FOR_STR 32
#define EMPTY_STR "00000000000000000000000000000000"

int init_sockfd();
char* get_uuid_str_from_msg_queue(int connfd);
char* main_client_for_msg_queue();
