#include "tests.h"

START_TEST(attachingBLock_test_1) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->game.field[5][5] = 1;
  attachingBLock();
  if (gameInfo->game.field[5][5] == 1 && gameInfo->copyField[5][5] == 1)
    flag = 1;
  freeMatrix(gameInfo->game.field, LINES);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(attachingBLock_test_2) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->game.field[0][0] = 1;
  gameInfo->game.field[LINES - 1][COLUMNS - 1] = 1;
  attachingBLock();
  if (gameInfo->game.field[0][0] == 1 && gameInfo->copyField[0][0] == 1 &&
      gameInfo->game.field[LINES - 1][COLUMNS - 1] == 1 &&
      gameInfo->copyField[LINES - 1][COLUMNS - 1] == 1)
    flag = 1;
  freeMatrix(gameInfo->game.field, LINES);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(checkFillLines_test_3) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  for (int i = 0; i < COLUMNS; i++) {
    gameInfo->copyField[LINES - 1][i] = 1;
  }
  checkFillLines();
  for (int i = 0; i < COLUMNS; i++) {
    if (gameInfo->copyField[LINES - 1][i] == 1) flag = 1;
  }
  freeMatrix(gameInfo->game.field, LINES);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(checkFillLines_test_4) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  for (int i = LINES - 1; i > LINES - 4; i--) {
    for (int j = 0; j < COLUMNS; j++) {
      gameInfo->copyField[i][j] = 1;
    }
  }
  checkFillLines();
  for (int i = LINES - 2; i > LINES - 4; i--) {
    for (int j = 0; j < COLUMNS; j++) {
      if (gameInfo->copyField[i][j] == 1) {
        flag = 1;
      }
    }
  }
  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->game.field, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(addScore_test_5) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.score = 0;   // initializeGame()
  gameInfo->game.level = 0;   // initializeGame()
  gameInfo->timeWhile = 0.6;  // initializeGame()
  addScore(4);
  if (gameInfo->game.score == 1500 && gameInfo->game.level == 2) flag = 1;
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(addScore_test_6) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.score = 0;   // initializeGame()
  gameInfo->game.level = 0;   // initializeGame()
  gameInfo->timeWhile = 0.6;  // initializeGame()
  addScore(5);
  if (gameInfo->game.score == 0 && gameInfo->game.level == 0) flag = 1;
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(deleteLine_test_7) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  for (int i = 0; i < COLUMNS; i++) {
    gameInfo->copyField[4][i] = 1;
  }
  deleteLine(4);
  for (int i = 0; i < COLUMNS; i++) {
    if (gameInfo->copyField[4][i] == 1) flag = 1;
  }
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(deleteLine_test_8) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  deleteLine(50);  // LINES < 50
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(deleteLine_test_9) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  deleteLine(-50);  // -50 < 0
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(isEmptyLine_test_10) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  for (int i = 0; i < COLUMNS; i++) gameInfo->copyField[4][i] = 1;
  flag = isEmptyLine(4);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(isEmptyLine_test_11) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->copyField[4][0] = 1;
  flag = isEmptyLine(4);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(isEmptyLine_test_12) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  flag = isEmptyLine(4);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(isFilledLine_test_13) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->copyField[4][0] = 1;
  flag = isFilledLine(4);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(isFilledLine_test_14) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  flag = isFilledLine(4);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(isFilledLine_test_15) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  for (int i = 0; i < COLUMNS; i++) {
    gameInfo->copyField[4][i] = 1;
  }
  flag = isFilledLine(4);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(moveDown_test_16) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.speed = 0;
  gameInfo->timeWhile = 0;
  moveFigureDown();
  if (gameInfo->game.speed == 3 && gameInfo->timeWhile == 0.02) flag = 1;
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(moveLine_test_17) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->copyField[4][7] = 1;
  gameInfo->copyField[4][9] = 1;
  moveLine(4);
  if (gameInfo->copyField[5][7] == 1 && gameInfo->copyField[5][9] == 1)
    flag = 1;
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(moveLine_test_18) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  for (int i = 0; i < COLUMNS; i++) {
    gameInfo->copyField[LINES - 2][i] = 1;
  }
  moveLine(LINES - 2);
  flag = isFilledLine(LINES - 1);
  freeMatrix(gameInfo->copyField, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

Suite *suite_attaching_functions(void) {
  Suite *s1 = suite_create("attaching_functions_suite");
  TCase *tc1_1 = tcase_create("attaching_functions_tcase");
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, attachingBLock_test_1);
  tcase_add_test(tc1_1, attachingBLock_test_2);
  tcase_add_test(tc1_1, checkFillLines_test_3);
  tcase_add_test(tc1_1, checkFillLines_test_4);
  tcase_add_test(tc1_1, addScore_test_5);
  tcase_add_test(tc1_1, addScore_test_6);
  tcase_add_test(tc1_1, deleteLine_test_7);
  tcase_add_test(tc1_1, deleteLine_test_8);
  tcase_add_test(tc1_1, deleteLine_test_9);
  tcase_add_test(tc1_1, isEmptyLine_test_10);
  tcase_add_test(tc1_1, isEmptyLine_test_11);
  tcase_add_test(tc1_1, isEmptyLine_test_12);
  tcase_add_test(tc1_1, isFilledLine_test_13);
  tcase_add_test(tc1_1, isFilledLine_test_14);
  tcase_add_test(tc1_1, isFilledLine_test_15);
  tcase_add_test(tc1_1, moveDown_test_16);
  tcase_add_test(tc1_1, moveLine_test_17);
  tcase_add_test(tc1_1, moveLine_test_18);
  return s1;
}
