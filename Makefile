NAME = minishell
LIBFT = libft/libft.a
INC = includes
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
CC = cc

FILES = minishell.c freadline.c garbage/gc.c
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC)  $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "minishell created"

$(LIBFT):
	@make -C libft

%.o:%.c $(INC)/minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)
	@echo "compiling..."

clean:
	@$(RM) $(OBJS)
	@make clean -C libft
	@echo "successfuly cleaned"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@echo "executable removed successfuly"

re: fclean all