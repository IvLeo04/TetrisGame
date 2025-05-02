#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * @file frontend.h
 * @brief Объявление функций для frontend части
 */

#define LINES 20
#define COLUMNS 10
#define highScoreFile "highScore.txt"

void initialCurses();
void printMainBox();
void printSecondBox();
void printInitializationBox();
void printPauseBox();
void printGameOver();
void printDeleteLine(int coordX);