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


