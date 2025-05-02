#include "../tetris.h"

/**
 * @file basic_functions.c
 * @brief Базовые функции для работы с матрицами, а также для работы с фигурами
 * и инициализацией игры
 */

/**
 * @brief Cоздание матрица динамическим способом с помощью calloc()
 * @param int H - Высота матрицы
 * @param int W - Ширина матрицы
 * @return Возвращаемое значение matrix - итоговая созданная матрица
 */
int **createMatrix(int H, int W) {
  int **matrix = 0;
  if (H > 0 && W > 0) {
    matrix = (int **)calloc(H, sizeof(int *));
    for (int i = 0; i < H; i++) {
      matrix[i] = (int *)calloc(W, sizeof(int));
    }
  }
  return matrix;
}

/**
 * @brief Освобождение памяти матрицы с помощью free()
 * @param int **matrix - Матрица, которую нужно освободить
 * @param int H - Высота матрицы, по которой делается free()
 * @return Возвращаемого значения нету
 */
void freeMatrix(int **matrix, int H) {
  for (int i = 0; i < H; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

/**
 * @brief Инициализация игры
 * @deprecated Функция вызывается на стадии Initial. Она инициализирует поля в
 * основной структуре GameInfo_t
 * @return Возвращаемого значения нету
 */
void initializeGame() {  // free
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->game = updateCurrentState();
  srand(time(NULL));
  gameInfo->game.speed = 25;
  gameInfo->timeWhile = 0.6;

  gameInfo->coordX = 0;
  gameInfo->coordY = 4;

  if (gameInfo->game.field != NULL) {
    freeMatrix(gameInfo->game.field, LINES);
  }
  gameInfo->game.field = createMatrix(LINES, COLUMNS);
  if (gameInfo->copyField != NULL) {
    freeMatrix(gameInfo->copyField, LINES);
  }
  gameInfo->copyField = createMatrix(LINES, COLUMNS);

  if (gameInfo->game.nextFigure != NULL) {
    freeMatrix(gameInfo->game.nextFigure, gameInfo->sizeNextFigure);
  }
  gameInfo->game.nextFigure = createNextFigure();
  gameInfo->game.level = 0;
  gameInfo->game.score = 0;
  gameInfo->game.high_score = getHighScore(highScoreFile);
}

/**
 * @brief Копирование матрицы
 * @param int **matrix - Матрица, которую нужно скопировать
 * @param int lines - Высота матрицы
 * @param int columns - Ширина матрицы
 * @return Возвращаемое значение resultMatrix - скопированная матрица
 */
int **copyMatrix(int **matrix, int lines, int columns) {  // free
  int **resultMatrix = 0;
  if (lines > 0 && columns > 0) {
    resultMatrix = createMatrix(lines, columns);
    for (int i = 0; i < lines; i++) {
      for (int j = 0; j < columns; j++) {
        resultMatrix[i][j] = matrix[i][j];
      }
    }
  }
  return resultMatrix;
}

/**
 * @brief Выбор размера фигуры в зависимости от нашей фигуры.
 * @param int randomNumber - Номер нашей фигуры по enum Figures.
 * @return Возвращаемое значение figureSize - размер фигуры
 */
int chooseFigureSize(int randomNumber) {
  int figureSize = 0;
  if (randomNumber == ALPHA || randomNumber == 8) {
    figureSize = 4;
  } else if (randomNumber == BETA) {
    figureSize = 3;
  } else if (randomNumber == GAMMA) {
    figureSize = 3;
  } else if (randomNumber == DELTA) {
    figureSize = 2;
  } else if (randomNumber == OMEGA) {
    figureSize = 3;
  } else if (randomNumber == PSI) {
    figureSize = 3;
  } else if (randomNumber == ZETA) {
    figureSize = 3;
  }
  return figureSize;
}

/**
 * @brief Создание нашей фигуры в зависимости от randomNumber
 * @param int randomNumber - Номер нашей фигуры по enum Figures.
 * @param int figureSize - Размер фигуры
 * @return Созданная фигура
 */
int **chooseFigures(int randomNumber, int figureSize) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (gameInfo->game.speed == 10) gameInfo->game.speed = 500;
  int **figure = 0;
  if (randomNumber == ALPHA || randomNumber == 8) {
    figure = createMatrix(figureSize, figureSize);
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[0][3] = 1;
  } else if (randomNumber == BETA) {
    figure = createMatrix(figureSize, figureSize);
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][0] = 1;
  } else if (randomNumber == GAMMA) {
    figure = createMatrix(figureSize, figureSize);
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][2] = 1;
  } else if (randomNumber == DELTA) {
    figure = createMatrix(figureSize, figureSize);
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
  } else if (randomNumber == OMEGA) {
    figure = createMatrix(figureSize, figureSize);
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
  } else if (randomNumber == PSI) {
    figure = createMatrix(figureSize, figureSize);
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][1] = 1;
  } else if (randomNumber == ZETA) {
    figure = createMatrix(figureSize, figureSize);
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][1] = 1;
    figure[1][0] = 1;
  }
  return figure;
}

/**
 * @brief Создание следующей фигуры
 * @deprecated Функция создает следующую фигуру. Она вызывает chooseFigureSize()
 * и chooseFigures(), а далее назначает переменную у структуры sizeNextFigure.
 * @return Созданная фигура
 */
int **createNextFigure() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (gameInfo->game.speed == 10) gameInfo->game.speed = 500;
  int **figure = 0;
  int figureSize = 0;
  int randomNumber = (rand() % 7);
  figureSize = chooseFigureSize(randomNumber);
  figure = chooseFigures(randomNumber, figureSize);
  gameInfo->sizeNextFigure = figureSize;
  return figure;
}

/**
 * @brief Создание основной фигуры
 * @deprecated Функция создает основную фигуру.  Она вызывает chooseFigureSize()
 * и chooseFigures(), а далее назначает переменную у структуры blockSize.
 * @return Созданная фигура
 */
int **createMainFigure() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (gameInfo->game.speed == 10) gameInfo->game.speed = 500;
  int **figure = 0;
  int figureSize = 0;
  int randomNumber = (rand() % 7);
  figureSize = chooseFigureSize(randomNumber);
  figure = chooseFigures(randomNumber, figureSize);
  gameInfo->blockSize = figureSize;
  return figure;
}

/**
 * @brief Освобождение всех динамических массивов
 * @deprecated Функция применяется в конце игры, чтобы освободить все массивы
 * @return Созданная фигура
 */
void freeAllMemory() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  freeMatrix(gameInfo->game.field, LINES);
  freeMatrix(gameInfo->copyField, LINES);
  freeMatrix(gameInfo->figure, gameInfo->blockSize);
  freeMatrix(gameInfo->game.nextFigure, gameInfo->sizeNextFigure);
}