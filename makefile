TARGET_NAME = signedgraph
TARGET = $(TARGET_NAME)$(TARGET_EXTENSION)

ifeq ($(OS),Windows_NT)
	SHELL = C:/Windows/System32/cmd.exe 	# Necessary if using a different shell, which is usually the case in Windows.
	TARGET_EXTENSION =.exe
	CLEANUP = del /F /Q *.o 
else
	TARGET_EXTENSION =.out
	CLEANUP = rm -f *.o
endif

all: default clean

default: main.o algorithms.o
	$(CC) -o $(TARGET_NAME) main.o algorithms.o -Wall -Wextra

viz: vizmode.o algorithms.o viz.o
	$(CC) -o $(TARGET_NAME) main.o algorithms.o viz.o -Wall -Wextra
	$(CLEANUP)

test: testmode.o algorithms.o test.o
	$(CC) -o $(TARGET_NAME) main.o algorithms.o test.o -Wall -Wextra
	$(CLEANUP)

main.o: main.c include/algorithms.h include/types.h
	$(CC) -c main.c -Iinclude/ -Wall -Wextra

algorithms.o: include/algorithms.c include/algorithms.h include/types.h
	$(CC) -c include/algorithms.c -Iinclude/ -Wall -Wextra

vizmode.o: main.c include/algorithms.h include/types.h include/viz.h
	$(CC) -c main.c -D VIZ -Iinclude/ -Wall -Wextra

viz.o: include/viz.c include/viz.h include/types.h
	$(CC) -c include/viz.c -Iinclude/ -Wall -Wextra

testmode.o: main.c include/algorithms.h include/types.h
	$(CC) -c main.c -D TEST -Iinclude/

test.o: include/test.c include/types.h include/algorithms.h
	$(CC) -c include/test.c  -Iinclude/ -Wall -Wextra

clean:
	$(CLEANUP)
