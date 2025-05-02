#include "../tetris.h"

/**
 * @file attaching_functions.c
 * @brief  Функции для прикрепления фигуры и проверки целых линий
 */

/**
 * @brief Функция для прикрепления фигуры к полю field.
 * @return Возвращаемого значения нет
 */
void attachingBLock() {  //#TODO
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      // gameInfo->game.field[i][j] = gameInfo->copyField[i][j];
      gameInfo->copyField[i][j] = gameInfo->game.field[i][j];
    }
  }
  gameInfo->coordX = 0;
  gameInfo->coordY = 4;
}

/**
 * @brief Проверка целых линий на поле
 * @deprecated Функция проверяет поле на полные линии. Если они есть - они
 * удаляются и поле поле смещается вниз. Также добавляется счет к игре. Функция
 * занимается визуализацией удаления линий для пользователя.
 * @return Возвращаемого значения нет
 */
void checkFillLines() {
  int countLine = 0;  // 1
  int flag = 0;
  while (flag == 0) {
    int lineInFor = 0;  // 0
    for (int i = LINES - 1; i >= 0 && lineInFor == 0 && flag != 1; i--) {
      if (isEmptyLine(i) == 0) {
        flag = 1;
      } else if (isFilledLine(i) == 0) {
        lineInFor++;
        countLine++;
        changeCopyField();
        printDeleteLine(i);
        sleep(1);
        deleteLine(i);
        moveLinesDown(i);
      }
    }
  }
  addScore(countLine);
}

/**
 * @brief Добавления счёта в зависимости от того, сколько линий заполнено.
 * @deprecated Функция добавляет счёт в структуру GameInfo_t и, если позволяет
 * счёт, происходит добавление уровня. Если меняется уровень игры - меняется и
 * скорость игры. Здесь изменяется переменная timeInWhile
 * @return Возвращаемого значения нет
 */
void addScore(int countLine) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  switch (countLine) {
    case 1:
      gameInfo->game.score += 100;
      break;
    case 2:
      gameInfo->game.score += 300;
      break;
    case 3:
      gameInfo->game.score += 700;
      break;
    case 4:
      gameInfo->game.score += 1500;
      break;
    default:
      break;
  }
  int newLevel = gameInfo->game.score / 600;
  if (newLevel - gameInfo->game.level > 0 && newLevel <= 10) {
    gameInfo->timeWhile -= 0.05 * (newLevel - gameInfo->game.level);
    gameInfo->game.level = newLevel;
  }
}

/**
 * @brief Дает последние движения фигуры перед окончательным прикреплением
 * @deprecated Когда фигура попала в процесс прикрепления, то есть, либо
 * столкнулась с другими прикрепленными фигурами, либо с полом - то пользователь
 * еще может сделать пару движений фигуры и только потом она прикрепляется и
 * спавнится следующая.
 * @return flag - уведомляет о том, что после этих последних движений фигуры,
 * она все еще столкнулась либо с полом, либо с другими фигурами. 1 - фигура
 * столкнулась, 0 - фигура может лететь дальше вниз.
 */
int lastMovesBeforeAttachingFigure() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;
  double totalTimeBeforeAttaching = 0;
  struct timespec tic = {0};
  struct timespec tac = {0};
  while (totalTimeBeforeAttaching < gameInfo->timeWhile) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &tic);
    int action = getch();
    timeout(gameInfo->game.speed);
    userInput(action, false);
    clock_gettime(CLOCK_MONOTONIC_RAW, &tac);
    totalTimeBeforeAttaching = (tac.tv_nsec - tic.tv_nsec) / 1000000000.0 +
                               (tac.tv_sec - tic.tv_sec) +
                               totalTimeBeforeAttaching;
    for (int i = 0; i < LINES; i++) {
      for (int j = 0; j < COLUMNS; j++) {
        if (gameInfo->copyField[i][j] == 1)
          gameInfo->game.field[i][j] = 1;
        else
          gameInfo->game.field[i][j] = 0;
      }
    }
    for (int i = 0; i < gameInfo->blockSize; i++) {
      for (int j = 0; j < gameInfo->blockSize; j++) {
        int newX = gameInfo->coordX + i;
        int newY = gameInfo->coordY + j;
        if ((gameInfo->figure[i][j] == 1) && (newX >= 0) && (newY < COLUMNS)) {
          gameInfo->game.field[newX][newY] = 1;
          // copyField[newX][newY] = 1;
        }
      }
    }
    printMainBox();
  }
  if (isReachedEnd() == 0) flag = 1;
  return flag;
}

/**
 * @brief Удаляет линию по coordX
 * @deprecated Функция используется в checkFillLines() - если линия полная,
 * вызывается данная функция и линия удаляется
 * @param int coordX - Координата линии, которую нужно удалить
 * @return Возвращаемого значения нет.
 */
void deleteLine(int coordX) {
  if (coordX < LINES && coordX >= 0) {
    MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
    for (int i = 0; i < COLUMNS; i++) {
      gameInfo->copyField[coordX][i] = 0;
    }
  }
}

/**
 * @brief Проверка того, что линия пустая
 * @deprecated Функция проверяет, что линия пустая. Она используется в
 * checkFillLines()
 * @param int coordX - Координата линии, которую нужно проверить
 * @return flag - пустая линия или нет. 1 - линия не пустая, 0 - линия пустая
 */
int isEmptyLine(int coordX) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;
  if (coordX > 0) {
    for (int i = 0; i < COLUMNS; i++) {
      if (gameInfo->copyField[coordX][i] == 1) flag = 1;
    }
  }
  return flag;
}

/**
 * @brief Проверка того, что линия полная
 * @deprecated Функция проверяет, что линия полная. Она используется в
 * checkFillLines()
 * @param int coordX - Координата линии, которую нужно проверить
 * @return flag - полная линия или нет. 1 - линия не полная, 0 - линия полная
 */
int isFilledLine(int coordX) {  // 0 = filled, 1 = notFilled
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;
  if (coordX > 0) {
    for (int i = 0; i < COLUMNS && flag != 1; i++) {
      if (gameInfo->copyField[coordX][i] == 0) flag = 1;
    }
  }
  return flag;
}

/**
 * @brief Опускание фигуры вниз
 * @deprecated Данная функция уменьшает timeWhile, тем самым ускоряя падение
 * фигуры и создавая иллюзия для пользователя, что фигура моментально падает в
 * пол. Вызывается при нажатии пользователем стрелки вниз.
 */
void moveFigureDown() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game.speed = 3;
  gameInfo->timeWhile = 0.02;
}

/**
 * @brief Функция опускания линии вниз на 1 относительно координаты по X.
 * @deprecated Функция опускает вниз линию.
 * @param int coordX - координата X, которая индексует линию, которую нужно
 * сдвинуть вниз.
 */
void moveLine(int coordX) {
  if (coordX >= 0 && coordX < LINES - 1) {
    MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
    for (int i = 0; i < COLUMNS; i++) {
      if (gameInfo->copyField[coordX][i] == 1) {
        gameInfo->copyField[coordX + 1][i] = 1;
        gameInfo->copyField[coordX][i] = 0;
      }
    }
  }
}

void changeCopyField() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (gameInfo->copyField[i][j] == 1)
        gameInfo->game.field[i][j] = 1;
      else
        gameInfo->game.field[i][j] = 0;
    }
  }
}

void attachFigureToField() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      int newX = gameInfo->coordX + i;
      int newY = gameInfo->coordY + j;
      if ((gameInfo->figure[i][j] == 1) && (newX >= 0) && (newY < COLUMNS)) {
        gameInfo->game.field[newX][newY] = 1;
      }
    }
  }
}
