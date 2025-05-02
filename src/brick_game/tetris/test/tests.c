#include "tests.h"

int main(void) {
  Suite *test_suites[] = {suite_attaching_functions(), suite_basic_functions(),
                          suite_high_score(),          suite_other_functions(),
                          suite_user_actions(),        NULL};

  for (Suite **current_suite = test_suites; *current_suite != NULL;
       current_suite++) {
    run_suite(*current_suite);
  }
  return 0;
}

void run_suite(Suite *test_suite) {
  SRunner *runner = srunner_create(test_suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
}
