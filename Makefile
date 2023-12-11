NAME = pipex

SRCS = srcs/
INCLUDE = include/

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = pipex.c \
		ft_split.c \
		utils.c \
		utils_2.c \
		cmd.c
FILES_PREFIX = $(addprefix $(SRCS), $(FILES))

OBJECTS = $(FILES:.c=.o)
OBJECTS_PREFIX = $(addprefix $(SRCS), $(OBJECTS))

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -c $(FILES_PREFIX)
	mv $(OBJECTS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJECTS_PREFIX) -o $@ -I $(INCLUDE)

clean:
	rm -rf $(OBJECTS_PREFIX)

fclean: clean
	rm -rf $(NAME)

re: fclean all