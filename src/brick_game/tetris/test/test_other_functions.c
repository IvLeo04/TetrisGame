#include "../../../gui/cli/frontend.h"
#include "tests.h"

START_TEST(isReachedEnd_test_1) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->blockSize = 2;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][0] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][0] = 1;
  gameInfo->figure[1][1] = 1;

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->coordX = 14;
  gameInfo->coordY = 5;

  gameInfo->copyField[gameInfo->coordX + 2][gameInfo->coordY] = 1;

  ck_assert_int_eq(isReachedEnd(), 1);
  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->figure, gameInfo->blockSize);
}
END_TEST

START_TEST(isReachedEnd_test_2) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->blockSize = 2;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][0] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][0] = 1;
  gameInfo->figure[1][1] = 1;

  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->coordX = 14;
  gameInfo->coordY = 5;

  gameInfo->copyField[gameInfo->coordX + 3][gameInfo->coordY] = 1;

  ck_assert_int_eq(isReachedEnd(), 0);
  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->figure, gameInfo->blockSize);
}
END_TEST

START_TEST(userActionGameOver_test_3) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;
  userActionGameOver(Restart);
  if (gameInfo->status == Initial) flag = 1;
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(checkGameOver_test_4) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->copyField[0][5] = 1;

  gameInfo->sizeNextFigure = 2;
  gameInfo->game.nextFigure =
      createMatrix(gameInfo->sizeNextFigure, gameInfo->sizeNextFigure);
  gameInfo->game.nextFigure[0][0] = 1;
  gameInfo->game.nextFigure[0][1] = 1;
  gameInfo->game.nextFigure[1][0] = 1;
  gameInfo->game.nextFigure[1][1] = 1;

  ck_assert_int_eq(checkGameOver(), 1);
  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->game.nextFigure, gameInfo->sizeNextFigure);
}
END_TEST

START_TEST(canDoRotate_test_5) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][0] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][1] = 1;
  gameInfo->figure[1][2] = 1;
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->copyField[16][6] = 1;
  gameInfo->coordX = 14;
  gameInfo->coordY = 5;

  int **rotatedFigure = rotate(gameInfo->figure);
  int flag = canDoRotate(rotatedFigure);

  ck_assert_int_eq(flag, 0);  // notRotate

  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(rotatedFigure, gameInfo->blockSize);
}
END_TEST

START_TEST(canDoRotate_test_6) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  gameInfo->blockSize = 3;
  gameInfo->figure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  gameInfo->figure[0][0] = 1;
  gameInfo->figure[0][1] = 1;
  gameInfo->figure[1][1] = 1;
  gameInfo->figure[1][2] = 1;
  gameInfo->copyField = createMatrix(LINES, COLUMNS);
  gameInfo->coordX = 14;
  gameInfo->coordY = 5;

  int **rotatedFigure = rotate(gameInfo->figure);
  int flag = canDoRotate(rotatedFigure);

  ck_assert_int_eq(flag, 1);  // doRotate

  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(rotatedFigure, gameInfo->blockSize);
}
END_TEST

Suite *suite_other_functions(void) {
  Suite *s1 = suite_create("other_functions_suite");
  TCase *tc1_1 = tcase_create("other_functions_tcase");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, isReachedEnd_test_1);
  tcase_add_test(tc1_1, isReachedEnd_test_2);
  tcase_add_test(tc1_1, userActionGameOver_test_3);
  tcase_add_test(tc1_1, checkGameOver_test_4);
  tcase_add_test(tc1_1, canDoRotate_test_5);
  tcase_add_test(tc1_1, canDoRotate_test_6);
  return s1;
}