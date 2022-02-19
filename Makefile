NAME = minishell
LIBFT = libft/libft.a
INC = includes
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
CC = cc

ENV = env.c
TOKENIZER = replace_vars.c tokenizer.c tokenizer_utils.c
LEXER = lexer.c
PROMPT = shell.c freadline.c
PARSER = check_error.c

FILES = minishell.c garbage/gc.c\
		$(addprefix prompt/, $(PROMPT))\
		$(addprefix tokenizer/, $(TOKENIZER))\
		$(addprefix lexer/, $(LEXER))\
		$(addprefix parser/, $(PARSER))\
		$(addprefix env/, $(ENV))
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC)  $(OBJS) $(LIBFT) -L$(shell brew --prefix readline)/lib -lreadline -o $(NAME)
	@echo "minishell created"

$(LIBFT):
	@make bonus -C libft

%.o:%.c $(INC)/minishell.h
	@$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@ -I $(INC)
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