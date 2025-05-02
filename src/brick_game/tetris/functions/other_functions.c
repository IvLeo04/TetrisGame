#include "../tetris.h"

/**
 * @file other_functions.c
 * @brief Функции, которые используются в течении игры для работы с фигурой и
 * входными данными от пользователя
 */

/**
 * @brief Проверка столкновения фигуры с чем-либо
 * @deprecated В функции сравниваются пиксели фигуры с параллельным пикселем, на
 * который она упадет. Проверяется - если на том параллельном пикселе что-либо
 * (либо пол, либо другая прикрепленная фигура)
 * @return Возвращаемое значение flag - если равен 1 - значит фигура с чем-то
 * стокнулась, если равен 0 - значит можно двигаться далее вниз
 */
int isReachedEnd() {  //#TODO
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;
  for (int i = 0; i < gameInfo->blockSize; i++) {
    for (int j = 0; j < gameInfo->blockSize; j++) {
      int newX = gameInfo->coordX + 1 + i;
      int newY = gameInfo->coordY + j;
      if (gameInfo->figure[i][j] == 1) {
        if (newX >= LINES)
          flag = 1;
        else if ((newX >= 0) && (gameInfo->copyField[newX][newY] == 1))
          flag = 1;
      }
    }
  }
  return flag;
}

/**
 * @brief Определяется, что пользователь ввел при конце игры
 * @deprecated Когда кончается игра, пользователю дается выбор - начать заново
 * или выйти из игры. Именно поэтому этот контроллер определяет, что выбрал
 * пользователь. Если выбрал начать заново статус игры преобразуется в Initial и
 * все начинается заново.
 * @return Возвращаемого значения нету
 */
int userActionGameOver(int action) {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();

  int flag = 0;
  switch (action) {
    case Terminate:
      flag = 1;
      break;
    case Restart:
      flag = 1;
      gameInfo->status = Initial;
      break;
  }
  return flag;
}

/**
 * @brief Проверка конца игры
 * @deprecated Если фигура не может заспавниться - игра окончена
 * @return Возвращаемое значение flag - если равен 1 - то игра окончена
 */
int checkGameOver() {  //#TODO
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 0;
  for (int i = 0; i < gameInfo->sizeNextFigure && flag != 1; i++) {
    for (int j = 0; j < gameInfo->sizeNextFigure; j++) {
      if (gameInfo->game.nextFigure[i][j] + gameInfo->copyField[i][j + 4] == 2)
        flag = 1;
    }
  }
  return flag;
}

/**
 * @brief Проверка на то, может ли фигура выполнить разворот
 * @deprecated Функция принимает потенциальную перевернутую фигуру и сравнивает
 * ее координаты с координатами поля - если они в сумме дают 2, то разворот не
 * может быть совершен
 * @return Возвращаемое значение flag - если равен 0 - то фигура не модет быть
 * повернута, если 1 - то может быть
 */
int canDoRotate(int **rotatedFigure) {  //#TODO
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  int flag = 1;
  int newX = 0;
  int newY = 0;
  if (gameInfo->blockSize != 0) {
    for (int i = 0; i < gameInfo->blockSize; i++) {
      for (int j = 0; j < gameInfo->blockSize; j++) {
        newX = gameInfo->coordX + i;
        newY = gameInfo->coordY + j;
        if (newX > LINES - 1 || newY > COLUMNS - 1 || newX < 0 || newY < 0) {
          flag = 0;
        } else if (rotatedFigure[i][j] + gameInfo->copyField[newX][newY] == 2) {
          flag = 0;
        }
      }
    }
  }
  return flag;
}

void printAllBox() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  if (gameInfo->status != GameOver) {
    changeCopyField();
    attachFigureToField();
    printMainBox();
    printSecondBox();
  }
}

MyGameInfo_t *getCurrentMyGameInfo_t() {
  static MyGameInfo_t gameInfo = {0};
  return &gameInfo;
}

/**
 * @brief Получение текущей основной структуры игры
 * @return Возвращаемое значение GameInfo_t - основная структура игры
 */
GameInfo_t updateCurrentState() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  return gameInfo->game;
}