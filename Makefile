#valgrind --leak-check=full --gen-suppressions=all --log-file=memcheck.log ./minishell
#valgrind --leak-check=full --show-leak-kinds=all ./minishell
#valgrind --leak-check=full ./minishell
#main new pull try Jasmin
#valgrind --leak-check=full --show-leak-kinds=all --suppressions=./minishell.supp --log-file=memcheck.log ./minishell
#valgrind --errors-for-leak-kinds=all --leak-check=full --read-var-info=yes --show-error-list=yes --show-leak-kinds=all --suppressions=./minishell.supp --trace-children=yes --trace-children-skip=$(subst $(SPACE),$(COMMA),$(ABSOLUTE_PATHS)) --track-origins=yes

# Colors
black = \033[3;30m
red = \033[1;31m
green = \033[1;32m
yellow = \033[1;33m
blue = \033[1;34m
reset = \033[0m

NAME			=	minishell

SRC_DIR			=	./srcs
OBJ_DIR			=	./objs
LINK			=	-I./includes
LIBFT			=	./libft/libft.a
MAKEFLAGS 		+= 	--no-print-directory


SRC				=	$(addprefix $(SRC_DIR)/,\
					minishell.c list.c case.c signal.c exit.c \
					init_variables.c free_loop.c make_groups.c \
					init_argv.c ft_split_modified.c childs.c \
					pipes.c redirections.c ft_strcmp.c get_next_line.c \
					get_next_line_utils.c heredoc_dollar.c dollar_found.c \
					dollar_found_in_double_quote.c dollar_check.c \
					syntax_error.c update_values.c cd.c proccesses.c \
					redirection_error_msgs.c redirection_reset.c \
					heredoc.c helper.c echo.c pwd.c export.c unset.c env.c \
					exit_cmd.c environment.c side.c built_in.c \
					dollar_found_utils.c heredoc_dollar_utils.c init_argv_utils.c \
					init_variables_utils.c utils.c list_group.c list_argv.c \
					list_group_utils.c check_in_env.c copy_env.c)
OBJ				=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS 			= 	-Wall -Werror -Wextra -g
LDFLAGS 		= 	-lreadline

RM				=	rm -f
RM_DIR			=	rm -rf
CC				=	cc -DVALGRIND

.PHONY:				all clean fclean re push run val fun hel

all:				$(NAME)

$(NAME):			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)
					@echo "$(green)compiled$(reset)"
					
$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
					@$(CC) -c $(CFLAGS) $< -o $@ $(LINK)

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)
					
clean:				
					@$(MAKE) clean -C ./libft
					@$(RM) $(OBJ)
					@$(RM_DIR) $(OBJ_DIR)

					@echo "$(green)clean" 	

fclean:
					@$(MAKE) fclean -C ./libft
					@$(RM) $(OBJ)
					@$(RM_DIR) $(OBJ_DIR)
					@$(RM) $(NAME)
					@echo "$(green)fclean$(reset)"

re:					fclean all

