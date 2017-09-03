#include "client_for_frontend.h"
#include "client_for_msg_queue.h"

int main(){
    int rm, status;
    char* uuid_str;
    char* filename;
    char* output_filename;
    char command[256];
    while(1){
        uuid_str = main_client_for_msg_queue();

        if(strcmp(uuid_str, EMPTY_STR) == 0){
            printf("No UUID in msg queue\n");
            sleep(5);
            continue;
        }

        filename = main_client_for_frontend_json(uuid_str);

        output_filename = malloc(strlen(filename) - 1);
        strcpy(output_filename, TEMP_DATA_DIR);
        strcat(output_filename, uuid_str);
        strcat(output_filename, ".txt");

        printf("Output FIle -> %s\n", output_filename);
        printf("Filename -> %s\n", filename);
        
        snprintf(command, sizeof(command), "./boolean_solver %s anf_equations %s", filename, output_filename);
        status = system(command);
        
        printf("Status -> %i\n", status);

        if(status == 0){
            main_send_result(uuid_str, output_filename);
            printf("Sent data to frontend\n");
        }
        else{printf("\nError: Not sending FILE\n");}

        printf("Deleting files from backend server\n");
        if((rm = remove(filename)) != 0){printf("Eror Deleting json file");}
        if((rm = remove(output_filename)) != 0){printf("ERROR deleting result file");}

        //break;
    }
}
