SHELL := /bin/bash -e
FILES = tetris.c functions/other_functions.c ../../gui/cli/frontend.c functions/basic_functions.c functions/high_score.c functions/user_actions.c functions/attaching_functions.c
FUNCTIONS = ./brick_game/tetris/functions/process_game.c ./brick_game/tetris/functions/other_functions.c ./brick_game/tetris/functions/basic_functions.c ./brick_game/tetris/functions/high_score.c ./brick_game/tetris/functions/user_actions.c ./brick_game/tetris/functions/attaching_functions.c
TESTS = brick_game/tetris/test/test_attaching_functions.c brick_game/tetris/test/test_basic_functions.c brick_game/tetris/test/test_high_score.c brick_game/tetris/test/test_user_actions.c brick_game/tetris/test/test_other_functions.c brick_game/tetris/test/tests.c
FRONTEND = gui/cli/frontend.c
COMPILE = tetris_game
COMPILE_TEST = s21_tests
TET_LIB_O = other_functions.o basic_functions.o high_score.o user_actions.o attaching_functions.o process_game.o
FLAGS = -Wall -Werror -Wextra -g -std=c11
NCURSES = -lncurses
GCC = gcc
TFLAGS = -lcheck -lsubunit -lpthread

all: uninstall install

install: tetris_lib.a
	gcc -g -Wall -Wextra -Werror -Wpedantic -o tetris_game brick_game/tetris/tetris.c $(FRONTEND) tetris_lib.a -lncurses
	make clean

uninstall: clean
	rm -rf tetris_game highScore.txt

dvi:
	doxygen Doxyfile
	open doxygen/html/index.html

dist:
	tar -czf tetris.install.tar.gz ./*
	
test: clean
	$(GCC) $(FLAGS) -g $(FUNCTIONS) $(TESTS) $(FRONTEND) -o $(COMPILE_TEST) $(TFLAGS) $(NCURSES) -lm

tetris_lib.a:
	$(GCC) $(FLAGS) -c $(FUNCTIONS)  
	ar rc tetris_lib.a $(TET_LIB_O)
	ranlib tetris_lib.a

valgrind_check_tetris: all
	valgrind --track-origins=yes --tool=memcheck --vgdb=no --leak-check=full --show-leak-kinds=all --verbose ./tetris_game

valgrind_check_test: test
	valgrind --track-origins=yes --tool=memcheck --vgdb=no --leak-check=full --show-leak-kinds=all --verbose ./s21_tests

gcov_report: clean
	$(GCC) $(FLAGS) --coverage $(TESTS) $(FRONTEND) $(FUNCTIONS) -o $(COMPILE_TEST) $(TFLAGS) $(NCURSES) -lm
	./$(COMPILE_TEST)
	lcov -t "report" -o report.info -c -d .
	genhtml -o "html_report" report.info
	open html_report/index.html

clean: 
	rm -rf s21_tests s21_tetris *.gcda *.gcno *.o tetris_lib.a report.info doxygen/ html_report/