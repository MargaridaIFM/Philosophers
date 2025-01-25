
MAKEFLAGS += --no-print-directory

NAME			=	philo

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -gdwarf-4

RM				=	rm -rf

INC_DIR			=	includes/

SRC_DIR			=	sources/

OBJ_DIR			=	objs/

RANDOM_MALLOC	=	-Xlinker --wrap=malloc

INPUT = 5 800 200 200

SRC				=	$(addprefix $(SRC_DIR), philo.c philo_utils.c philo_utils_1.c life_routine_utils.c dead_routine_utils.c inits.c errors.c routines.c)

OBJ_DIRS		=	$(OBJ_DIR) $(addprefix $(OBJ_DIR), $(SRC_DIR)) 

OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(NAME):			$(OBJ) | $(SRC) 
					$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) 
					printf '$(NAME) compiled successfully!\n$(RESET)'

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c | $(OBJ_DIRS) 
					$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(OBJ_DIRS):
					mkdir -p $@

all:				$(NAME)

random_malloc:		$(OBJ) | $(SRC)
					$(CC) $(CFLAGS) $(RANDOM_MALLOC) -lreadline $^ -o $(NAME) -I $(INC_DIR) -L$(LFT_PATH) -lft
					printf '$(GREEN)$(NAME) compiled successfully!\n $(RESET)'

clean:
					if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

val: $(NAME)
	make re 
	clear 
	valgrind --leak-check=full ./$(NAME) $(INPUT)
hel: $(NAME)
	make re 
	clear 
	valgrind --tool=helgrind  ./$(NAME) $(INPUT)
drd: $(NAME)
	make re 
	clear 
	valgrind --tool=drd ./$(NAME) $(INPUT)

.PHONY:				all clean fclean re val

