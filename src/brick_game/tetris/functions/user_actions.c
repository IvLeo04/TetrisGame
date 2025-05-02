#include "../tetris.h"

/**
 * @file other_functions.c
 * @brief Функции, которые используются в течении игры для работы с фигурой и
 * входными данными от пользователя
 */

/**
 * @brief Разворот фигуры
 * @deprecated Данная функция вызывается, когда пользователь решается
 * перевернуть фигуру
 * @return Возвращаемое значение - матрица, которая в себе хранит развернутую
 * фигуру
 */
int **rotate() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int **newFigure = createMatrix(gameInfo->blockSize, gameInfo->blockSize);
  if (gameInfo->blockSize == 4) {
    if (gameInfo->figure[0][0] == 1) {
      newFigure[0][1] = 1;
      newFigure[1][1] = 1;
      newFigure[2][1] = 1;
      newFigure[3][1] = 1;
    } else {
      newFigure[0][0] = 1;
      newFigure[0][1] = 1;
      newFigure[0][2] = 1;
      newFigure[0][3] = 1;
    }
  } else {
    for (int i = 0; i < gameInfo->blockSize; i++) {
      for (int j = 0; j < gameInfo->blockSize; j++) {
        newFigure[j][gameInfo->blockSize - i - 1] = gameInfo->figure[i][j];
      }
    }
  }
  return newFigure;
}

/**
 * @brief Функция для выбора действия в зависимости от действия пользователя
 * @deprecated В зависимости от того, что пользователь ввел с помощью getch(),
 * функция благодаря switch-case выполняет различные блоки команд. Изменения
 * могут происходит как над фигурой, так и над программой, в целом
 * @param UserAction_t action - это входной параметр, который ввел пользователь.
 * @return Возвращаемого значения нету
 */
void userInput(UserAction_t action, bool hold) {
  (void)hold;
  int **rotatedFigure;
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (gameInfo->timeWhile == 0.05) gameInfo->timeWhile = 0.6;
  int canRotate = 0;
  switch (action) {
    case Right:
      moveFigureRight();
      break;
    case Left:
      moveFigureLeft();
      break;
    case Down:
      moveFigureDown();
      break;
    case Action:
      rotatedFigure = rotate();
      canRotate = canDoRotate(rotatedFigure);
      if (canRotate == 1) {
        for (int i = 0; i < gameInfo->blockSize; i++) {
          for (int j = 0; j < gameInfo->blockSize; j++) {
            gameInfo->figure[i][j] = rotatedFigure[i][j];
          }
        }
      }
      freeMatrix(rotatedFigure, gameInfo->blockSize);
      break;
    case Pause:
      gameInfo->game.pause = 1;
      while (gameInfo->game.pause != 0) {
        if (getch() == Start) gameInfo->game.pause = 0;
        printPauseBox();
        continue;
      }
      break;
    case Terminate:
      gameInfo->status = Quit;
      break;
    case Restart:
      gameInfo->status = Initial;
      break;
    default:
      break;
  }
}

/**
 * @brief Функция для опускания линий вниз
 * @deprecated Функция опускает линии вниз, относительно входного параметра
 * startCoordX, пока не упрется в полностью пустую линию. Функция применяется,
 * когда какая-либо линия полностью наполняется и удаляется
 * @param int startCoordX - параметр дает понять, с какой координаты по X нужно
 * начинать смещать линии вниз
 * @return Возвращаемого значения нету
 */
void moveLinesDown(int startCoordX) {
  int flag = 0;
  if (startCoordX >= 0 || startCoordX < LINES - 1) {
    for (int i = startCoordX - 1; i > 0 && flag == 0; i--) {
      if (isEmptyLine(i) == 0) {
        flag = 1;
      } else {
        moveLine(i);
      }
    }
  }
}

/**
 * @brief Функция для смещения фигуры вправо
 * @deprecated Когда пользователь вводит стрелку вправо, то вызывается эта
 * функция. Фигура двигается вправо, если это возможно
 * @return Возвращаемого значения нету
 */
void moveFigureRight() {  //#TODO
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  int flag = 1;
  int newX = 0;
  int newY = 0;

  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      newX = gameInfo->coordX + i;
      newY = gameInfo->coordY + j + 1;
      int gameFigure = 0;
      int gameField = 0;
      if (gameInfo->figure[i][j] == 1 && newY >= COLUMNS)
        flag = 0;
      else if (newX > 0 && newY > 0 && newX <= LINES - 1 &&
               newY <= COLUMNS - 1) {
        gameFigure = gameInfo->figure[i][j];
        gameField = gameInfo->copyField[newX][newY];
        if (gameField + gameFigure == 2) flag = 0;
      }
    }
  }
  if (flag != 0) gameInfo->coordY++;
}

/**
 * @brief Функция для смещения фигуры влево
 * @deprecated Когда пользователь вводит стрелку влево, то вызывается эта
 * функция. Фигура двигается влево, если это возможно
 * @return Возвращаемого значения нету
 */
void moveFigureLeft() {  //#TODO
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  int flag = 1;
  int newX = 0;
  int newY = 0;

  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      newX = gameInfo->coordX + i;
      newY = gameInfo->coordY + j - 1;
      if (gameInfo->figure[i][j] == 1 && newY < 0)
        flag = 0;
      else if (newX >= 0 && newY >= 0 && newX <= LINES - 1) {
        if (gameInfo->figure[i][j] + gameInfo->copyField[newX][newY] == 2)
          flag = 0;
      }
    }
  }
  if (flag != 0) gameInfo->coordY--;
}
