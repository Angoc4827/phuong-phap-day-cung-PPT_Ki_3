# Makefile - make / make test / make clean (TV 7, H-06)
# Windows (MinGW): dung mingw32-make thay cho make

CC     = gcc
CFLAGS = -std=c99 -Wall -Wextra
LDLIBS = -lm

CHUNG  = day_cung.c ham_mau.c

all: day_cung

day_cung: main.c $(CHUNG) day_cung.h ham_mau.h
	$(CC) $(CFLAGS) -o $@ main.c $(CHUNG) $(LDLIBS)

test_day_cung: test_day_cung.c $(CHUNG) day_cung.h ham_mau.h
	$(CC) $(CFLAGS) -o $@ test_day_cung.c $(CHUNG) $(LDLIBS)

so_sanh: so_sanh.c $(CHUNG) day_cung.h ham_mau.h
	$(CC) $(CFLAGS) -o $@ so_sanh.c $(CHUNG) $(LDLIBS)

test: test_day_cung
	./test_day_cung

clean:
	rm -f day_cung test_day_cung so_sanh *.o *.exe

.PHONY: all test clean
