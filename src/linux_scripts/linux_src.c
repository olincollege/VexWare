#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>

char* get_home() {
    /**
     * Get the file path of the home directory
     * 
     * @return the home directory file path
     */
    char *fileloc;
    if ((fileloc = getenv("HOME")) == NULL) {
        fileloc = getpwuid(getuid())->pw_dir;
    }

    return fileloc;
}

void bashrc_edit(char *home_loc, char *edit) {
    /**
     * Append to the user's bash config file
     * 
     * @param home_loc absolute file path of user's home dir
     * @param edit text to append to file
    */
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
    
    fprintf(fptr, edit);

    fclose(fptr);

    char src_cmd[50] = ". ";
    strcat(src_cmd, fileloc);

    system(src_cmd);

    free(fileloc);
}


void add_cron_script(char *home_loc, char *script_loc, char *job_timing) {
    /**
     * Use cron to schedule a recurring job that runs a given script
     * 
     * @param home_loc the home directory file path
     * @param script_loc the script file path, relative to the user's home dir
     * @param job_timing the timing of the recurring job in the cron format
    */

    const char *cmd_pt1 = "( (crontab -l 2>/dev/null || echo "")  ; echo \"";
    const char *cmd_pt2 = " export XDG_RUNTIME_DIR=/run/user/1000 && ";
    const char *cmd_pt3 = "'\") | sort -u - | crontab -";
    
    int cmd_size = strlen(home_loc) + strlen(script_loc) + strlen(job_timing) + strlen(cmd_pt1) + strlen(cmd_pt2) + strlen(cmd_pt3) + 6;
    char *cron_cmd = (char*)calloc(cmd_size, sizeof(char));

    strcat(cron_cmd, cmd_pt1);
    strcat(cron_cmd, job_timing);
    strcat(cron_cmd, cmd_pt2);
    strcat(cron_cmd, home_loc);
    strcat(cron_cmd, script_loc);
    strcat(cron_cmd, cmd_pt3);

    system(cron_cmd);

    free(cron_cmd);
}

void add_cron_speak(char *text, char *job_timing) {
    /**
     * Use cron to schedule a recurring job that speaks the given text aloud
     * 
     * @param text the text for the computer to speak
     * @param job_timing the timing of the recurring job in the cron format
    */
    const char *cmd_pt1 = "( (crontab -l 2>/dev/null || echo "")  ; echo \"";
    const char *cmd_pt2 = " export XDG_RUNTIME_DIR=/run/user/1000 && /usr/bin/spd-say '";
    const char *cmd_pt3 = "'\") | sort -u - | crontab -";
    
    int speak_cmd_size = strlen(text) + strlen(job_timing) + strlen(cmd_pt1) + strlen(cmd_pt2) + strlen(cmd_pt3) + 5;
    char *cron_speak = (char*)calloc(speak_cmd_size, sizeof(char));

    strcat(cron_speak, cmd_pt1);
    strcat(cron_speak, job_timing);
    strcat(cron_speak, cmd_pt2);
    strcat(cron_speak, text);
    strcat(cron_speak, cmd_pt3);

    system(cron_speak);

    free(cron_speak);
}
