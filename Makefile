NAME = pipex
# NAMEBONUS = checker
CFLAGS = -Wextra -Wall -Werror
LIBFT = -L./libft -lft

SRCS =	src/main.c src/tools.c src/pipex.c src/init.c src/error.c

OBJS = $(SRCS:.c=.o)

# BONUS_SRCS =	src/bonus/main_bonus.c src/bonus/tools_bonus.c src/bonus/input_check_bonus.c \
# 				src/bonus/ft_long_atoi_bonus.c src/bonus/lst/lst_add_back_bonus.c \
# 				src/bonus/lst/lst_clear_bonus.c src/bonus/lst/lst_last_bonus.c \
# 				src/bonus/lst/lst_new_bonus.c src/bonus/lst/lst_size_bonus.c \
# 				src/bonus/rule/rule_push_bonus.c src/bonus/rule/rule_rotate_bonus.c \
# 				src/bonus/rule/rule_rrotate_bonus.c src/bonus/rule/rule_swap_bonus.c 

#BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

# bonus: $(NAMEBONUS)

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@cc $(OBJS) $(LIBFT) -o $(NAME)

# $(NAMEBONUS): $(BONUS_OBJS)
# 	@$(MAKE) -C ./libft
# 	@cc $(BONUS_OBJS) $(LIBFT) -o $(NAMEBONUS)

clean:
	@rm -rf $(OBJS)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C ./libft fclean

re: clean all

.PHONY: all clean fclean re
