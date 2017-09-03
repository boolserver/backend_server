#include "client_for_frontend.h"
#include "client_for_msg_queue.h"

int main(){
    while(1){
        char* uuid_str = main_client_for_msg_queue();

        if(strcmp(uuid_str, EMPTY_STR) == 0){
            printf("No UUID in msg queue\n");
            sleep(5);
            continue;
        }

        char* filename = main_client_for_frontend_json(uuid_str);

        char* output_filename = malloc(strlen(filename) - 1);
        strcpy(output_filename, TEMP_DATA_DIR);
        strcat(output_filename, uuid_str);
        strcat(output_filename, ".txt");

        printf("Output FIle -> %s\n", output_filename);
        printf("Filename -> %s\n", filename);
        
        char command[256];
        snprintf(command, sizeof(command), "./boolean_solver %s anf_equations %s", filename, output_filename);
        int status = system(command);
        
        printf("Status -> %i\n", status);

        if(status == 0){
            main_send_result(uuid_str, output_filename);
            printf("Sent data to frontend\n");
        }
        else{printf("\nError: Not sending FILE\n");}

        break;
    }
}
