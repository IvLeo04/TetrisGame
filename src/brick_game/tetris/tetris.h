#define _POSIX_C_SOURCE 200809L

/**
 * @file tetris.h
 * @brief Объявление функций для backend части
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../gui/cli/frontend.h"

#define LINES 20
#define COLUMNS 10
#define highScoreFile "highScore.txt"

/** @brief Enum для фигур (их названия)*/
typedef enum { ALPHA, BETA, GAMMA, DELTA, OMEGA, PSI, ZETA } Figures;

typedef enum {
  Start = 32,
  Pause = 80,
  Restart = 82,
  Terminate = 81,
  Left = KEY_LEFT,
  Right = KEY_RIGHT,
  Up,
  Down = KEY_DOWN,
  Action = 32
} UserAction_t;

/** @brief Enum для статусов*/
typedef enum {
  Initial,
  Spawn,
  Moving,
  Shifting,
  Attaching,
  GameOver,
  Quit
} Status_t;

typedef struct {
  /** @brief Поле с движимыми фигурами */
  int **field;
  /** @brief Следующая фигура */
  int **nextFigure;
  /** @brief Счет*/
  int score;
  /** @brief Рекорд*/
  int high_score;
  /** @brief Уровень*/
  int level;
  /** @brief Скорость*/
  int speed;
  /** @brief Пауза*/
  int pause;
} GameInfo_t;

typedef struct {
  /** @brief Структура для frontend (DAO)*/
  GameInfo_t game;
  /** @brief Поле с прикрепленными фигурами*/
  int **copyField;
  /** @brief Статус в игре для конечного автомата*/
  Status_t status;
  /** @brief Текущая фигура*/
  int **figure;
  /** @brief Размер для текущей фигуры*/
  int blockSize;
  /** @brief Координата по высоте для текущей фигуры*/
  int coordX;
  /** @brief Координата по ширине для текущей фигуры*/
  int coordY;
  /** @brief Размер для текущей фигуры*/
  int sizeNextFigure;
  /** @brief Время для цикла while, который создает зависимость падения фигуры
   * от времени*/
  double timeWhile;
} MyGameInfo_t;

// !!!!!basic_functions.c!!!!!
int **createMatrix(int H, int W);
void freeMatrix(int **matrix, int H);
void initializeGame();
int **createNextFigure();
int **createMainFigure();
int **copyMatrix(int **matrix, int lines, int columns);
void freeAllMemory();

// !!!!!other_functions.c!!!!!
int isReachedEnd();
int canDoRotate(int **rotatedFigure);
int checkGameOver();
int userActionGameOver(int action);
void printAllBox();
MyGameInfo_t *getCurrentMyGameInfo_t();
GameInfo_t updateCurrentState();

// !!!!!high_score.c!!!!!
int getHighScore(char *fileName);
void cleanFile(char *nameFile);
void writeToRecordFile(char *fileName, int score);

//   !!!!!user_actions.c!!!!!
void moveFigureRight();
void moveFigureLeft();
void moveFigureDown();
void userInput(UserAction_t action, bool hold);
int **rotate();

//  !!!!!attaching_functions.c!!!!!
void attachingBLock();
void checkFillLines();
void moveLinesDown(int startCoordX);
void deleteLine(int coordX);
int isEmptyLine(int coordX);
int isFilledLine(int coordX);
int lastMovesBeforeAttachingFigure();
void addScore(int countLine);
void moveLine(int coordX);
void changeCopyField();
void attachFigureToField();

void initialStatus();
void spawnStatus();
void movingStatus();
void shiftingStatus();
void attachingStatus();
void gameOverStatus(int *flagGameOver);