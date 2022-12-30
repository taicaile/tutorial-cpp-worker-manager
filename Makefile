# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o workerManager.o employee.o manager.o boss.o
	$(CC) $(CFLAGS) -o main main.o workerManager.o employee.o manager.o boss.o
	./main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

workerManager.o: workerManager.cpp
	$(CC) $(CFLAGS) -c workerManager.cpp

employee.o: employee.cpp
	$(CC) $(CFLAGS) -c employee.cpp

manager.o: manager.cpp
	$(CC) $(CFLAGS) -c manager.cpp

boss.o: boss.cpp
	$(CC) $(CFLAGS) -c boss.cpp

clean:
	rm -f *.o *.gch main
