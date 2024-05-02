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

    bashrc_edit(home_loc);
    // add_cron_script(home_loc, cron_start1, cron_end);
    add_cron_speak("test", cron_start2, cron_end);
}
