#include "tests.h"

START_TEST(rotate_test_1) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  int flag = 0;

  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][2] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][1] = 1;
  gameInfo->figure[1][0] = 1;

  int **rotatedFigure = rotate(gameInfo->figure);
  int **result = createMatrix(gameInfo->blockSize, gameInfo->blockSize);

  result[0][1] = 1;
  result[1][1] = 1;
  result[1][2] = 1;
  result[2][2] = 1;

  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      if (rotatedFigure[i][j] != result[i][j]) flag = 1;
    }
  }

  ck_assert_int_eq(flag, 0);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(rotatedFigure, gameInfo->blockSize);
  freeMatrix(result, gameInfo->blockSize);
}
END_TEST

START_TEST(userInput_test_2) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  int flag = 0;
  gameInfo->coordX = 5;
  gameInfo->coordY = 5;
  gameInfo->timeWhile = 0.6;
  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][2] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][1] = 1;
  gameInfo->figure[1][0] = 1;

  userInput(Right, false);

  if (gameInfo->coordY == 6 && gameInfo->coordX == 5) flag = 1;

  ck_assert_int_eq(flag, 1);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(userInput_test_3) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  int flag = 0;
  gameInfo->coordX = 5;
  gameInfo->coordY = 5;
  gameInfo->timeWhile = 0.6;
  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][2] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][1] = 1;
  gameInfo->figure[1][0] = 1;
  gameInfo->copyField[5][8] = 1;

  userInput(Right, false);

  if (gameInfo->coordY == 5 && gameInfo->coordX == 5) flag = 1;

  ck_assert_int_eq(flag, 1);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(userInput_test_4) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  int flag = 0;
  gameInfo->coordX = 5;
  gameInfo->coordY = 5;
  gameInfo->timeWhile = 0.6;
  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][1] = 1;
  gameInfo->copyField[5][7] = 1;

  userInput(Right, false);

  if (gameInfo->coordY == 5 && gameInfo->coordX == 5) flag = 1;

  ck_assert_int_eq(flag, 1);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(userInput_test_5) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  int flag = 0;
  gameInfo->coordX = 5;
  gameInfo->coordY = 5;
  gameInfo->timeWhile = 0.6;
  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][1] = 1;
  gameInfo->copyField[5][5] = 1;

  userInput(Left, false);

  if (gameInfo->coordY == 5 && gameInfo->coordX == 5) flag = 1;

  ck_assert_int_eq(flag, 1);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(userInput_test_6) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  int flag = 0;
  gameInfo->coordX = 5;
  gameInfo->coordY = 5;
  gameInfo->timeWhile = 0.6;
  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][1] = 1;
  gameInfo->copyField[5][4] = 1;

  userInput(Left, false);

  if (gameInfo->coordY == 4 && gameInfo->coordX == 5) flag = 1;

  ck_assert_int_eq(flag, 1);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(userInput_test_7) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  int flag = 0;
  gameInfo->coordX = 5;
  gameInfo->coordY = 5;
  gameInfo->timeWhile = 0.6;
  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][2] = 1;
  gameInfo->copyField[5][5] = 1;

  userInput(Left, false);

  if (gameInfo->coordY == 4 && gameInfo->coordX == 5) flag = 1;

  ck_assert_int_eq(flag, 1);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(userInput_test_8) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  int flag = 0;

  gameInfo->timeWhile = 0.6;
  gameInfo->copyField = createMatrix(LINES, COLUMNS);

  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][2] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][1] = 1;
  gameInfo->figure[1][0] = 1;

  userInput(Action, false);
  int **result = createMatrix(gameInfo->blockSize, gameInfo->blockSize);

  result[0][1] = 1;
  result[1][1] = 1;
  result[1][2] = 1;
  result[2][2] = 1;

  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      if (gameInfo->figure[i][j] != result[i][j]) flag = 1;
    }
  }

  ck_assert_int_eq(flag, 0);
  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(result, gameInfo->blockSize);
}
END_TEST

START_TEST(userInput_test_9) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  int flag = 0;

  gameInfo->blockSize = 3;
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->coordX = 5;
  gameInfo->coordY = 5;
  gameInfo->copyField[gameInfo->coordX + 1][gameInfo->coordY + 2] = 1;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][2] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][1] = 1;
  gameInfo->figure[1][0] = 1;

  userInput(Up, false);
  int **result = createMatrix(gameInfo->blockSize, gameInfo->blockSize);

  result[0][2] = 1;
  result[0][1] = 1;
  result[1][1] = 1;
  result[1][0] = 1;

  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      if (gameInfo->figure[i][j] != result[i][j]) flag = 1;
    }
  }

  ck_assert_int_eq(flag, 0);

  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(result, gameInfo->blockSize);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(moveLinesDown_test_10) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->copyField[5][5] = 1;
  gameInfo->copyField[5][8] = 1;

  gameInfo->copyField[6][6] = 1;
  gameInfo->copyField[6][9] = 1;

  moveLinesDown(7);

  if (gameInfo->copyField[6][5] == 1 && gameInfo->copyField[6][8] == 1 &&
      gameInfo->copyField[7][6] == 1 && gameInfo->copyField[7][9] == 1)
    flag = 1;
  ck_assert_int_eq(flag, 1);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

Suite *suite_user_actions(void) {
  Suite *s1 = suite_create("user_actions_suite");
  TCase *tc1_1 = tcase_create("user_actions_tcase");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, rotate_test_1);
  tcase_add_test(tc1_1, userInput_test_2);
  tcase_add_test(tc1_1, userInput_test_3);
  tcase_add_test(tc1_1, userInput_test_4);
  tcase_add_test(tc1_1, userInput_test_5);
  tcase_add_test(tc1_1, userInput_test_6);
  tcase_add_test(tc1_1, userInput_test_7);
  tcase_add_test(tc1_1, userInput_test_8);
  tcase_add_test(tc1_1, userInput_test_9);
  tcase_add_test(tc1_1, moveLinesDown_test_10);
  return s1;
}