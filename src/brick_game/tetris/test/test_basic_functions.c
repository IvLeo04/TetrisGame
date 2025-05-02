#include "tests.h"

START_TEST(createMatrix_test_1) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  gameInfo->game.field[1][1] = 1;
  if (gameInfo->game.field[1][1] == 1) flag = 1;
  ck_assert_int_eq(flag, 1);
  freeMatrix(gameInfo->game.field, LINES);
}
END_TEST

START_TEST(freeMatrix_test_2) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  freeMatrix(gameInfo->game.field, LINES);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(initializeGame_test_3) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = NULL;
  gameInfo->copyField = NULL;
  initializeGame();
  if (gameInfo->status == Initial && gameInfo->game.speed == 25 &&
      gameInfo->timeWhile == 0.6 && gameInfo->coordX == 0 &&
      gameInfo->coordY == 4 && gameInfo->game.level == 0 &&
      gameInfo->game.score == 0 &&
      gameInfo->game.high_score == getHighScore(highScoreFile) &&
      gameInfo->game.field[0][0] == 0 && gameInfo->copyField[0][0] == 0 &&
      gameInfo->sizeNextFigure != 0)
    flag = 1;
  freeMatrix(gameInfo->game.field, LINES);
  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->game.nextFigure, gameInfo->sizeNextFigure);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(createNextFigure_test_4) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.nextFigure = createNextFigure();
  for (int i = 0; i < gameInfo->sizeNextFigure; i++) {
    for (int j = 0; j < gameInfo->sizeNextFigure; j++) {
      if (gameInfo->game.nextFigure[i][j] == 1) flag = 1;
    }
  }
  freeMatrix(gameInfo->game.nextFigure, gameInfo->sizeNextFigure);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(createMainFigure_test_5) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->figure = createMainFigure();
  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      if (gameInfo->figure[i][j] == 1) flag = 1;
    }
  }
  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(copyMatrix_test_6) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  gameInfo->game.field[1][1] = 1;
  gameInfo->game.field[LINES - 1][COLUMNS - 1] = 1;
  gameInfo->copyField = copyMatrix(gameInfo->game.field, LINES, COLUMNS);
  if (gameInfo->copyField[1][1] == 1 &&
      gameInfo->copyField[LINES - 1][COLUMNS - 1] == 1)
    flag = 1;
  ck_assert_int_eq(flag, 1);
  freeMatrix(gameInfo->game.field, LINES);
  freeMatrix(gameInfo->copyField, LINES);
}
END_TEST

START_TEST(copyMatrix_test_7) {
  int flag = 0;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  gameInfo->game.field[1][1] = 1;
  gameInfo->game.field[LINES - 1][COLUMNS - 1] = 1;
  gameInfo->copyField = 0;
  gameInfo->copyField = copyMatrix(gameInfo->game.field, -5, -5);
  ck_assert_int_eq(flag, 0);
  freeMatrix(gameInfo->game.field, LINES);
}
END_TEST

Suite *suite_basic_functions(void) {
  Suite *s1 = suite_create("basic_functions_suite");
  TCase *tc1_1 = tcase_create("basic_functions_tcase");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, createMatrix_test_1);
  tcase_add_test(tc1_1, freeMatrix_test_2);
  tcase_add_test(tc1_1, initializeGame_test_3);
  tcase_add_test(tc1_1, createNextFigure_test_4);
  tcase_add_test(tc1_1, createMainFigure_test_5);
  tcase_add_test(tc1_1, copyMatrix_test_6);
  tcase_add_test(tc1_1, copyMatrix_test_7);
  return s1;
}