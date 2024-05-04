#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Get the file path of the home directory
 *
 * @return the home directory file path
 */
char* get_home();

/**
 * Grant execute permissions to the given file by running chmod +x file
 *
 * @param file the absolute path to the file to give perms to
 */
void make_exec(char* file);

/**
 * Use wget to download the given file then grant exec perms if needed
 *
 * @param home_loc the home directory file path
 * @param file_path the location to save the downloaded file
 * @param url the url to download the file from
 * @param need_exec boolean to tell if the file should be granted exec perms
 */
void download_file(char* home_loc, char* file_path, int need_exec, char* url);

/**
 * Append to the user's bash config file
 *
 * @param home_loc absolute file path of user's home dir
 * @param edit text to append to file
 */
void bashrc_edit(char* home_loc, char* edit);

/**
 * Use cron to schedule a recurring job that runs a given script
 *
 * @param home_loc absolute file path of user's home dir
 * @param script_loc the path from the home_dir to the script
 * @param job_timing the timing of the recurring job in the cron format
 */
void add_cron_script(char* home_loc, char* script_loc, char* job_timing);

/**
 * Use cron to schedule a recurring job that speaks the given text aloud
 *
 * @param text the text for the computer to speak
 * @param job_timing the timing of the recurring job in the cron format
 */
void add_cron_speak(char* text, char* job_timing);
