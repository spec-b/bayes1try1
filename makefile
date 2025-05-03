CC=gcc
CFLAGS=-Wall -O2

all: bayesian_prover

bayesian_prover: main.o beta.o rules.o
	$(CC) $(CFLAGS) -o bayesian_prover main.o beta.o rules.o -lm

main.o: main.c rules.h
	$(CC) $(CFLAGS) -c main.c

beta.o: beta.c beta.h
	$(CC) $(CFLAGS) -c beta.c

rules.o: rules.c rules.h beta.h
	$(CC) $(CFLAGS) -c rules.c

clean:
	rm -f *.o bayesian_prover
