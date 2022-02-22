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
BUILTIN = pwd_cmd.c env_cmd.c cd_cmd.c exit_cmd.c echo_cmd.c unset_cmd.c export_cmd.c export_utils.c

FILES = minishell.c garbage/gc.c\
		$(addprefix prompt/, $(PROMPT))\
		$(addprefix tokenizer/, $(TOKENIZER))\
		$(addprefix lexer/, $(LEXER))\
		$(addprefix parser/, $(PARSER))\
		$(addprefix builtin_cmds/, $(BUILTIN))\
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