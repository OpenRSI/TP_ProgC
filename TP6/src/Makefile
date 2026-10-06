COBJS = client.o bmp.o couleur.o protocole.o
SOBJS = serveur.o protocole.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS)

.c.o:
	$(CC) -std=c11 -Wall -Wextra -Wpedantic -Werror -ggdb3 -c $< -o $@

clean:
	rm -f $(SERVER) $(CLIENT) $(COBJS) $(SOBJS)

.PHONY: all clean
