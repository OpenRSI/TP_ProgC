CC = gcc
CFLAGS = -Wall -Wextra -g

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): serveur.o
	$(CC) $(CFLAGS) -o $(SERVER) serveur.o

$(CLIENT): client.o
	$(CC) $(CFLAGS) -o $(CLIENT) client.o

serveur.o: serveur.c serveur.h
	$(CC) $(CFLAGS) -c serveur.c

client.o: client.c client.h
	$(CC) $(CFLAGS) -c client.c

clean:
	rm -f *.o $(SERVER) $(CLIENT)
