NAME = pipex

SRCS = srcs/
INCLUDE = include/

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FILES = pipex.c cmd.c ft_split.c \
		utils.c utils_tab.c utils_error.c
OBJECTS = $(addprefix $(SRCS), $(FILES:.c=.o))

FILES_BONUS = main_bonus.c pipex_bonus.c cmd.c ft_split.c \
				utils.c utils_tab.c utils_error.c utils_bonus.c \
				gnl/gnl.c gnl/gnl_utils.c
OBJECTS_BONUS = $(addprefix $(SRCS), $(FILES_BONUS:.c=.o))

%.o: %.c
	@echo $@
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -I $(INCLUDE)

bonus: $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME) -I $(INCLUDE)

clean:
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all