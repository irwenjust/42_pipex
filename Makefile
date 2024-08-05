NAME = pipex
CFLAGS = -Wextra -Wall -Werror
LIBFT = -L./libft -lft

SRCS =	src/main.c \
		src/tools.c \
		src/pipex.c \
		src/init.c \
		src/exit.c \
		src/command.c \

OBJS = $(SRCS:.c=.o)

BONUS_SRCS =	src_bonus/main_bonus.c \
				src_bonus/init_bonus.c \
				src_bonus/tools_bonus.c \
				src_bonus/pipex_bonus.c \
				src_bonus/exit_bonus.c \
				src_bonus/command_bonus.c
				

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"



$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@cc $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(BONUS_OBJS)
	@$(MAKE) --no-print-directory -C ./libft
	@cc $(BONUS_OBJS) $(LIBFT) -o $(NAME)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C ./libft fclean

re: clean all

.PHONY: all clean fclean re bonus
