NAME = pipex
NAMEBONUS = pipex
CFLAGS = -Wextra -Wall -Werror
LIBFT = -L./libft -lft

SRCS =	src/main.c \
		src/tools.c \
		src/pipex.c \
		src/init.c \
		src/exit.c \
		src/command.c \

OBJS = $(SRCS:.c=.o)

BONUS_SRCS =	src_bonus/main_bonus.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

bonus: $(NAMEBONUS)

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@cc $(OBJS) $(LIBFT) -o $(NAME)

$(NAMEBONUS): $(BONUS_OBJS)
	@$(MAKE) -C ./libft
	@cc $(BONUS_OBJS) $(LIBFT) -o $(NAMEBONUS)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -rf $(NAME) $(NAMEBONUS)
	@$(MAKE) -C ./libft fclean

re: clean all

.PHONY: all clean fclean re bonus
