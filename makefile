CC = gcc
CFLAGS = -I.
DEPS = hysteresis.h tests.h
OBJ = main.o hysteresis.o tests.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hysteresis: $(OBJ)
	$(CC) -o  $@ $^ $(CFLAGS)
