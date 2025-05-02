#include "../tetris.h"

/**
 * @file high_score.c
 * @brief Функции, для работы с файлом, который хранит рекордный счет игры
 */

/**
 * @brief Получение рекордного счета из файла
 * @param char *fileName - название файла с содержимым рекодным счетом
 * @return Возвращаемое значение - рекордный счет, который хранится в файле
 */
int getHighScore(char *fileName) {
  FILE *fileHighScore = fopen(fileName, "a+");
  char buffer[256] = "";
  fgets(buffer, 256, fileHighScore);
  fclose(fileHighScore);
  int record = atoi(buffer);
  // free(buffer);
  return record;
}

/**
 * @brief Очистка файла
 * @param char *fileName - название файла с содержимым рекодным счетом
 * @return Возвращаемого значения нету
 */
void cleanFile(char *nameFile) {
  FILE *file = fopen(nameFile, "w");
  fclose(file);
}

/**
 * @brief Написание рекорда в файл
 * @deprecated Функция вызывается в конце игры, если игрок побил свой рекордный
 * результат
 * @param char *fileName - название файла с содержимым рекодным счетом
 * @param int score - счет, который набрал игрок в течении игры
 * @return Возвращаемого значения нету
 */
void writeToRecordFile(char *fileName, int score) {
  FILE *file = fopen(fileName, "w");
  char buffer[256] = "";
  snprintf(buffer, sizeof buffer, "%d", score);
  fputs(buffer, file);
  fclose(file);
}
