#include "../tetris.h"

/**
 * @file process_game.c
 * @brief Функции, которые описывают каждый статус в игре. Они реализуют
 * конечный автомат
 */

/**
 * @brief Инициализация игры
 * @deprecated Инициализация всех параметров, а после печатание
 * инициализационного экрана, пока не будет нажат Space
 * @return Возвращаемого значения нету
 */
void initialStatus() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  initializeGame();
  while (getch() != Start) {
    printInitializationBox();
  }
  gameInfo->status = Spawn;
}

/**
 * @brief Стадия спавна фигуры
 * @deprecated Создание текущей и следующей фигуры
 * @return Возвращаемого значения нету
 */
void spawnStatus() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (gameInfo->figure != NULL)
    freeMatrix(gameInfo->figure, gameInfo->blockSize);
  gameInfo->figure = gameInfo->game.nextFigure;
  gameInfo->blockSize = gameInfo->sizeNextFigure;
  gameInfo->game.nextFigure = createNextFigure();
  gameInfo->status = Moving;
}

/**
 * @brief Стадия движения фигуры
 * @deprecated Происходит определение статуса после движения фигуры - если она с
 * чем-либо встретилась, то Attaching, если нет, игрок совершает свои действия.
 * @return Возвращаемого значения нету
 */
void movingStatus() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (isReachedEnd() == 1) {
    gameInfo->status = Attaching;
  } else {
    gameInfo->status = Shifting;
  }
}

/**
 * @brief Стадия ввода пользователем клавиш
 * @deprecated Пользователь нажимает кнопку -> Меняются координаты фигуры ->
 * Далее опять Moving
 * @return Возвращаемого значения нету
 */
void shiftingStatus() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  timeout(gameInfo->game.speed);
  int action = getch();
  gameInfo->status = Moving;
  userInput(action, false);
}

/**
 * @brief Стадия прикрепления фигуры
 * @deprecated Функция прикрепляет фигуру и проверяет - не наступил ли конец
 * игры. Если да - GameOver, иначе - Spawn
 * @return Возвращаемого значения нету
 */
void attachingStatus() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (lastMovesBeforeAttachingFigure() == 0) {
    attachingBLock();
    checkFillLines();
    gameInfo->timeWhile = 0.6 - 0.05 * gameInfo->game.level;
    if (checkGameOver() == 1)
      gameInfo->status = GameOver;
    else {
      gameInfo->status = Spawn;
    }
  }
}

/**
 * @brief Стадия конца игры
 * @deprecated Функция печатает экран конца игры, ожидает от пользователя
 * дальнейших вводов, а после идет запись рекорда
 * @return Возвращаемого значения нету
 */
void gameOverStatus(int *flagGameOver) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;
  printGameOver();
  if (getHighScore(highScoreFile) < gameInfo->game.score) {
    cleanFile(highScoreFile);
    writeToRecordFile(highScoreFile, gameInfo->game.score);
  }
  while (flag == 0) {
    flag = userActionGameOver(getch());
  }
  if (gameInfo->status != Initial) *flagGameOver = 1;
  // else freeAllMemory();
}