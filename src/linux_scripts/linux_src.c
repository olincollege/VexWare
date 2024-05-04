#include "linux_src.h"

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char* get_home() {
  char* fileloc;
  if ((fileloc = getenv("HOME")) == NULL) {
    fileloc = getpwuid(getuid())->pw_dir;
  }

  return fileloc;
}

void make_exec(char* file) {
  pid_t pid = fork();

  if (pid == 0) {
    execl("/usr/bin/chmod", "/usr/bin/chmod", "+x", file, (char*)0);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }
}

void download_file(char* home_loc, char* file_path, int need_exec, char* url) {
  size_t path_len = strlen(home_loc) + strlen(file_path) + 2;
  char download_loc[path_len];

  snprintf(download_loc, path_len, "%s%s", home_loc, file_path);

  pid_t pid = fork();

  if (pid == 0) {
    execl("/usr/bin/wget", "/usr/bin/wget", "-nc", "-q", "-O", download_loc,
          url, (char*)0);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }

  if (need_exec) {
    make_exec(download_loc);
  }
}

void bashrc_edit(char* home_loc, char* edit) {
  char* file = "/.bashrc";

  size_t path_len = strlen(home_loc) + strlen(file) + 1;

  char fileloc[path_len];
  snprintf(fileloc, path_len, "%s%s", home_loc, file);

  FILE* fptr;
  fptr = fopen(fileloc, "a");
  if (fptr == NULL) {
    printf("Error! Could not write to file.");
    exit(1);
  }

  fprintf(fptr, edit);

  fclose(fptr);
}

void add_cron_script(char* home_loc, char* script_loc, char* job_timing) {
  const char* cmd_pt1 =
      "( (crontab -l 2>/dev/null || echo "
      ")  ; echo \"";
  const char* cmd_pt2 = " export XDG_RUNTIME_DIR=/run/user/1000 && ";
  const char* cmd_pt3 = "\") | sort -u - | crontab -";

  size_t cmd_size = strlen(script_loc) + strlen(home_loc) + strlen(job_timing) +
                    strlen(cmd_pt1) + strlen(cmd_pt2) + strlen(cmd_pt3) + 6;
  // char* cron_cmd = (char*)calloc(cmd_size, sizeof(char));
  char cron_cmd[cmd_size];
  snprintf(cron_cmd, cmd_size, "%s%s%s%s%s%s", cmd_pt1, job_timing, cmd_pt2,
           home_loc, script_loc, cmd_pt3);

  /*strcat(cron_cmd, cmd_pt1);
  strcat(cron_cmd, job_timing);
  strcat(cron_cmd, cmd_pt2);
  strcat(cron_cmd, home_loc);
  strcat(cron_cmd, script_loc);
  strcat(cron_cmd, cmd_pt3);*/

  // NOLINTNEXTLINE(concurrency-mt-unsafe, cert-env33-c)
  system(cron_cmd);
}

void add_cron_speak(char* text, char* job_timing) {
  const char* cmd_pt1 =
      "( (crontab -l 2>/dev/null || echo "
      ")  ; echo \"";
  const char* cmd_pt2 =
      " export XDG_RUNTIME_DIR=/run/user/1000 && /usr/bin/spd-say '";
  const char* cmd_pt3 = "')\") | sort -u - | crontab -";

  size_t cmd_size = strlen(text) + strlen(job_timing) + strlen(cmd_pt1) +
                    strlen(cmd_pt2) + strlen(cmd_pt3) + 5;

  char cron_cmd[cmd_size];
  snprintf(cron_cmd, cmd_size, "%s%s%s%s%s", cmd_pt1, job_timing, cmd_pt2, text,
           cmd_pt3);

  /*char* cron_speak = (char*)calloc(speak_cmd_size, sizeof(char));

  strcat(cron_speak, cmd_pt1);
  strcat(cron_speak, job_timing);
  strcat(cron_speak, cmd_pt2);
  strcat(cron_speak, text);
  strcat(cron_speak, cmd_pt3);*/

  // NOLINTNEXTLINE(concurrency-mt-unsafe, cert-env33-c)
  system(cron_cmd);
}
