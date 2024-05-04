#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../src/linux_scripts/linux_src.h"

// Check that the home directory is a non-empty string.
Test(get_home, nonempty) { cr_assert_str_not_empty(get_home()); }

// Check that the input file is executable after running make_exec.
Test(make_exec, execperms) {
  char test_file_path[] = "/tmp/my_temp_file_XXXXXX";

  mkstemp(test_file_path);

  make_exec(test_file_path);

  cr_assert_eq(access(test_file_path, X_OK), 0);
}

// Check that bashrc file actually changes.
Test(bashrc_edit, bashconfigchanged) {
  char* file = "/.bashrc";
  char* home_loc = get_home();

  size_t path_len = strlen(home_loc) + strlen(file) + 1;

  char fileloc[path_len];
  // NOLINTNEXTLINE
  snprintf(fileloc, path_len, "%s%s", home_loc, file);

  FILE* file1 = fopen(fileloc, "rbe");
  if (fseek(file1, 0, SEEK_END) < 0) {
    error_and_exit("Error!");
  }
  size_t fsize = (size_t)ftell(file1);
  if (fseek(file1, 0, SEEK_SET) < 0) {
    error_and_exit("Error!");
  }

  char* og_bash_text = malloc(fsize + 1);
  if (fread(og_bash_text, fsize, 1, file1) == 0) {
    error_and_exit("Error!");
  }
  if (fclose(file1) < 0) {
    error_and_exit("Error!");
  }

  og_bash_text[fsize] = 0;

  bashrc_edit(home_loc, "\n\necho 'test'");

  FILE* file2 = fopen(fileloc, "rbe");
  if (fseek(file2, 0, SEEK_END) < 0) {
    error_and_exit("Error!");
  }
  fsize = (size_t)ftell(file2);
  if (fseek(file2, 0, SEEK_SET) < 0) {
    error_and_exit("Error!");
  }

  char* new_bash_text = malloc(fsize + 1);
  if (fread(new_bash_text, fsize, 1, file2) == 0) {
    error_and_exit("Error!");
  }
  if (fclose(file2) < 0) {
    error_and_exit("Error!");
  }

  new_bash_text[fsize] = 0;

  cr_assert_not(strcmp(og_bash_text, new_bash_text) == 0);
}

// Same test but without modifcation to bashrc so should result in no changes
Test(bashrc_edit, nochange) {
  char* file = "/.bashrc";
  char* home_loc = get_home();

  size_t path_len = strlen(home_loc) + strlen(file) + 1;

  char fileloc[path_len];
  // NOLINTNEXTLINE
  snprintf(fileloc, path_len, "%s%s", home_loc, file);

  FILE* file1 = fopen(fileloc, "rbe");
  if (fseek(file1, 0, SEEK_END) < 0) {
    error_and_exit("Error!");
  }
  size_t fsize = (size_t)ftell(file1);
  if (fseek(file1, 0, SEEK_SET) < 0) {
    error_and_exit("Error!");
  }

  char* og_bash_text = malloc(fsize + 1);
  if (fread(og_bash_text, fsize, 1, file1) == 0) {
    error_and_exit("Error!");
  }
  if (fclose(file1) < 0) {
    error_and_exit("Error!");
  }

  og_bash_text[fsize] = 0;

  FILE* file2 = fopen(fileloc, "rbe");
  if (fseek(file2, 0, SEEK_END) < 0) {
    error_and_exit("Error!");
  }
  fsize = (size_t)ftell(file2);
  if (fseek(file2, 0, SEEK_SET) < 0) {
    error_and_exit("Error!");
  }

  char* new_bash_text = malloc(fsize + 1);
  if (fread(new_bash_text, fsize, 1, file2) == 0) {
    error_and_exit("Error!");
  }
  if (fclose(file2) < 0) {
    error_and_exit("Error!");
  }

  new_bash_text[fsize] = 0;

  cr_assert(strcmp(og_bash_text, new_bash_text) == 0);
}

// Test that correct cronjob exists after add_cron_speak is run
Test(add_cron_speak, testspeak) {
  char* cronjob =
      "* * * * * export XDG_RUNTIME_DIR=/run/user/1000 && /usr/bin/spd-say "
      "'test'";

  add_cron_speak("test", "* * * * *");

  char test_file_path[] = "/tmp/my_temp_file_XXXXXX";

  mkstemp(test_file_path);
  size_t cmd_len = strlen("crontab -l >> ") + strlen(test_file_path) + 1;
  char sys_cmd[cmd_len];

  // NOLINTNEXTLINE
  snprintf(sys_cmd, cmd_len, "%s%s", "crontab -l >> ", test_file_path);

  // NOLINTNEXTLINE(concurrency-mt-unsafe, cert-env33-c)
  system(sys_cmd);

  FILE* file = fopen(test_file_path, "re");
  ssize_t read = 0;
  size_t len = 0;
  char* line = NULL;
  bool job_added = false;

  while ((read = getline(&line, &len, file))) {
    if (read == 0) {
      error_and_exit("Error!");
    }
    line[strcspn(line, "\n")] = 0;
    if (!strcmp(line, cronjob)) {
      job_added = true;
      break;
    }
  }
  if (fclose(file) < 0) {
    error_and_exit("Error!");
  }

  cr_assert(job_added);
}

// Test that correct cronjob exists after add_cron_script is run
Test(add_cron_script, testscript) {
  char* sample_script = "test.sh";  // not a real script, ok for this test

  char* cronjob =
      "* * * * * export XDG_RUNTIME_DIR=/run/user/1000 && /tmp/test.sh";
  char* home_loc = "/tmp/";  // fake home location to create file in tmp

  add_cron_script(home_loc, sample_script, "* * * * *");

  char test_file_path[] = "/tmp/my_temp_file_XXXXXX";

  mkstemp(test_file_path);

  size_t cmd_len = strlen("crontab -l >> ") + strlen(test_file_path) + 1;
  char sys_cmd[cmd_len];

  // NOLINTNEXTLINE
  snprintf(sys_cmd, cmd_len, "%s%s", "crontab -l >> ", test_file_path);

  // NOLINTNEXTLINE(concurrency-mt-unsafe, cert-env33-c)
  system(sys_cmd);

  FILE* file = fopen(test_file_path, "re");
  ssize_t read = 0;
  size_t len = 0;
  char* line = NULL;
  bool job_added = false;

  while ((read = getline(&line, &len, file))) {
    if (read == 0) {
      error_and_exit("Error!");
    }
    line[strcspn(line, "\n")] = 0;
    if (!strcmp(line, cronjob)) {
      job_added = true;
      break;
    }
  }
  if (fclose(file) < 0) {
    error_and_exit("Error!");
  }

  cr_assert(job_added);
}
