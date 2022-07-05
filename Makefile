CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

all: server client

bonus: re

libft.a:
	make re -C ./libft

server: server.c libft.a
	$(CC) $(CFLAGS) server.c libft/libft.a -o server

client: client.c libft.a
	$(CC) $(CFLAGS) client.c libft/libft.a -o client

clean:
	make clean -C libft/

fclean:
	rm -f server
	rm -f client
	make fclean -C libft/

re: fclean all