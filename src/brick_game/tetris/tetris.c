#include "tetris.h"

int main() {
  struct timespec startTime = {0};
  struct timespec endTime = {0};
  double totalTimeInWhile = 0;
  int flagGameOver = 0;

  initialCurses();

  MyGameInfo_t *gameInfo = getCurrentMyGameInfo_t();
  gameInfo->status = Initial;

  while (flagGameOver != 1) {
    while (totalTimeInWhile <= gameInfo->timeWhile &&
           gameInfo->status != GameOver) {
      if (gameInfo->status == Initial) initialStatus();
      printAllBox();
      if (gameInfo->status == Spawn) spawnStatus();
      printAllBox();
      clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);
      if (gameInfo->status == Moving) movingStatus();
      if (gameInfo->status == Shifting) shiftingStatus();
      if (gameInfo->status == Attaching) attachingStatus();
      printAllBox();
      if (gameInfo->status == GameOver) gameOverStatus(&flagGameOver);
      // printAllBox();
      if (gameInfo->status == Quit) flagGameOver = 1;
      clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);
      totalTimeInWhile = (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.0 +
                         (endTime.tv_sec - startTime.tv_sec) + totalTimeInWhile;
    }
    gameInfo->coordX++;
    totalTimeInWhile = 0;
  }
  freeAllMemory();
  endwin();
}
