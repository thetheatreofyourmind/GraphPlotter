CC=gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS = 

.PHONY: all clean rebuild

all: graph.o make_postfix.o calculation.o stack.o draw_module.o
	$(CC) $(LDFLAGS) $^ -o ../build/graph
#	cppcheck --enable=all --suppress=missingIncludeSystem .
#	leaks -atExit -- ../build/graph

draw_module.o: draw_module.c
	$(CC) $(CFLAGS)  $<
#	clang-format -i $< draw_module.h

graph.o: graph.c
	$(CC) $(CFLAGS)  $<
#	clang-format -i $<
make_postfix.o: make_postfix.c
	$(CC) $(CFLAGS)  $<
#	clang-format -i $< make_postfix.h
calculation.o: calculation.c
	$(CC) $(CFLAGS)  $<
#	clang-format -i $< calculation.h
stack.o: stack.c
	$(CC) $(CFLAGS)  $<
#	clang-format -i $< stack.h

rebuild: clean all

clean:
	rm -rf *.o
	rm -rf ../build/*