#include <check.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

#include "../tetris.h"
#define S21_TRUE 1
#define S21_FALSE 0

void run_suite(Suite *test_suite);

Suite *suite_attaching_functions(void);
Suite *suite_basic_functions(void);
Suite *suite_high_score(void);
Suite *suite_other_functions(void);
Suite *suite_user_actions(void);
