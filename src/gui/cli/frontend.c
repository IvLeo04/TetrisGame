#include "frontend.h"

#include "../../brick_game/tetris/tetris.h"

/**
 * @file frontend.c
 * @brief Функции, которые занимаются визуализацией игры
 */

/**
 * @brief Инициализация библиотеки ncurses
 * @deprecated Загружает начальный экран и работает с курсором
 * @return Возвращаемого значения нету
 */
void initialCurses() {
  initscr();
  curs_set(0);
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
}

/**
 * @brief Вывод поля игры, но с помеченной линией, которую мы удаляем
 * @param int coordX - Координата по X, которую нужно выделить, чтобы показать,
 * что линия удаляется
 * @return Возвращаемого значения нету
 */
void printDeleteLine(int coordX) {
  GameInfo_t gameInfo = updateCurrentState();
  WINDOW *gameWindow = newwin(LINES + 2, 3 * COLUMNS + 2, 0, 0);
  refresh();
  box(gameWindow, 0, 0);
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (i == coordX)
        mvwprintw(gameWindow, i + 1, 3 * j + 1, "[=]");
      else if (gameInfo.field[i][j] == 1)
        mvwprintw(gameWindow, i + 1, 3 * j + 1, "[ ]");
      else
        mvwprintw(gameWindow, i + 1, 3 * j + 1, " ");
    }
  }
  wrefresh(gameWindow);
}

/**
 * @brief Вывод основного поля игры, где играет пользователь.
 * @deprecated Здесь идет основной процесс.
 * @return Возвращаемого значения нету
 */
void printMainBox() {
  GameInfo_t gameInfo = updateCurrentState();
  WINDOW *gameWindow = newwin(LINES + 2, 3 * COLUMNS + 2, 0, 0);
  box(gameWindow, 0, 0);
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (gameInfo.field[i][j] == 1)
        mvwprintw(gameWindow, i + 1, 3 * j + 1, "[ ]");
      else
        mvwprintw(gameWindow, i + 1, 3 * j + 1, " ");
    }
  }
  wrefresh(gameWindow);
}

/**
 * @brief Вывод приветственного экрана. Выводит надпись, что нужно нажать Space
 * @deprecated Используется только на стадии Initial
 * @return Возвращаемого значения нету
 */
void printInitializationBox() {
  WINDOW *gameWindow = newwin(LINES + 2, 3 * COLUMNS + 2, 0, 0);
  refresh();
  box(gameWindow, 0, 0);
  mvwprintw(gameWindow, LINES / 2, 1.5 * COLUMNS - 9,
            "Press \"Space\" to start");
  wrefresh(gameWindow);
}

/**
 * @brief Вывод второго поля.
 * @deprecated В поле содержится информация о следующей фигуре, уровне, счете и
 * рекорде. Также выведены правила игры
 * @return Возвращаемого значения нету
 */
void printSecondBox() {
  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  WINDOW *gameWindow = newwin(LINES + 2, 3 * COLUMNS + 4, 0, 3 * COLUMNS + 4);
  refresh();
  box(gameWindow, 0, 0);
  WINDOW *windowOfFigure =
      subwin(gameWindow, gameInfo->sizeNextFigure + 2,
             3 * gameInfo->sizeNextFigure + 4, 2, 3 * COLUMNS + 7);
  refresh();
  box(windowOfFigure, 0, 0);
  mvwprintw(gameWindow, 1, 4, "Next figure");
  for (int i = 0; i < gameInfo->sizeNextFigure; i++) {
    for (int j = 0; j < gameInfo->sizeNextFigure; j++) {
      if (gameInfo->game.nextFigure[i][j] == 1)
        mvwprintw(windowOfFigure, i + 1, 3 * j + 2, "[ ]");
      else
        mvwprintw(windowOfFigure, i + 1, 3 * j + 2, " ");
    }
  }
  mvwprintw(gameWindow, 8, 4, "Level %d", gameInfo->game.level);
  mvwprintw(gameWindow, 9, 4, "Score %d", gameInfo->game.score);
  mvwprintw(gameWindow, 10, 4, "High Score %d", getHighScore(highScoreFile));
  mvwprintw(gameWindow, 11, 1, "------------------------------");
  mvwprintw(gameWindow, 12, 10, "Instruction:");
  mvwprintw(gameWindow, 13, 1, " 1) Use arrows on keyboard for");
  mvwprintw(gameWindow, 14, 1, " move figure");
  mvwprintw(gameWindow, 15, 1, " 2) \"Space\" - rotate figure");
  mvwprintw(gameWindow, 16, 1, " 3) \"P\" - Pause");
  mvwprintw(gameWindow, 17, 1, " 4) \"Q\" - Quit");
  mvwprintw(gameWindow, 18, 1, " 5) \"R\" - Retry");
  mvwprintw(gameWindow, 20, 7, "Thanks for playing!");
  wrefresh(gameWindow);
  wrefresh(windowOfFigure);
}

/**
 * @brief Вывод конечного экрана
 * @deprecated В поле выведена информация о конце игры и возможности либо начать
 * заново, либо выйти из игры
 * @return Возвращаемого значения нету
 */
void printGameOver() {
  WINDOW *gameWindow = newwin(LINES + 2, 3 * COLUMNS + 2, 0, 0);
  refresh();
  box(gameWindow, 0, 0);
  mvwprintw(gameWindow, LINES / 2 - 2, 1.5 * COLUMNS - 2, "Game Over");
  mvwprintw(gameWindow, LINES / 2, 1.5 * COLUMNS - 11,
            "Press \"R\" to try again");
  mvwprintw(gameWindow, LINES / 2 + 2, 1.5 * COLUMNS - 11,
            "Press \"Q\" to exit");

  wrefresh(gameWindow);
}

/**
 * @brief Вывод поля приостановления игры
 * @deprecated В поле выведена информация о том, что игра поставлена на паузу и
 * чтобы продолжить нужно нажать Space
 * @return Возвращаемого значения нету
 */
void printPauseBox() {
  WINDOW *gameWindow = newwin(LINES + 2, 3 * COLUMNS + 2, 0, 0);
  refresh();
  box(gameWindow, 0, 0);
  mvwprintw(gameWindow, LINES / 2 - 2, 1.5 * COLUMNS - 2, "PAUSE");
  mvwprintw(gameWindow, LINES / 2, 1.5 * COLUMNS - 11,
            "Press \"Space\" to continue");
  wrefresh(gameWindow);
}