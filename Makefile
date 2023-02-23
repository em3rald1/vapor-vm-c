CC = gcc
CFLAGS = -g -c
LDFLAGS = -g

SRC = ${wildcard src/*.c}
OBJ = ${SRC:.c=.o}
EXEC = vaporvm

all: ${SRC} ${OBJ} ${EXEC}

%.o: %.c
	$(CC) $? $(CFLAGS) -o $@

${EXEC}:
	$(CC) ${OBJ} ${LDFLAGS} -o $@

clean:
	rm ${OBJ} ${EXEC}