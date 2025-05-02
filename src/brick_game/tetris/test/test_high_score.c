#include "tests.h"

START_TEST(getHighScore_test_1) {
  int flag = 0;
  cleanFile(highScoreFile);
  writeToRecordFile(highScoreFile, 600);
  int score = getHighScore(highScoreFile);
  if (score == 600) flag = 1;
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(cleanFile_test_2) {
  int flag = 0;
  cleanFile(highScoreFile);
  writeToRecordFile(highScoreFile, 600);
  cleanFile(highScoreFile);
  int score = getHighScore(highScoreFile);
  if (score == 0) flag = 1;
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(writeToRecordFile_test_3) {
  int flag = 0;
  cleanFile(highScoreFile);
  writeToRecordFile(highScoreFile, 1200);
  int score = getHighScore(highScoreFile);
  if (score == 1200) flag = 1;
  ck_assert_int_eq(flag, 1);
}
END_TEST

Suite *suite_high_score(void) {
  Suite *s1 = suite_create("high_score_suite");
  TCase *tc1_1 = tcase_create("high_score_tcase");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, getHighScore_test_1);
  tcase_add_test(tc1_1, cleanFile_test_2);
  tcase_add_test(tc1_1, writeToRecordFile_test_3);
  return s1;
}