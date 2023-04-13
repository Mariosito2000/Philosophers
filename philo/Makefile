SRCS	=	$(wildcard SRCS/*.c)

BONUS_SRCS	=

OBJS 	=	$(addprefix $(O_DIR)/, $(SRCS:.c=.o))

BONUS_OBJS	=	$(addprefix $(BO_DIR)/, $(BONUS_SRCS:.c=.o))

O_DIR	=	OBJS

BO_DIR	=	BONUS_OBJS

CC	=	gcc -Wall -Wextra -Werror -pthread

NAME 	=	philo

NAME_BONUS	=	philo_bonus

$(O_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $(O_DIR)/${<:.c=.o} -I

$(BO_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $(BO_DIR)/${<:.c=.o} -I

all:		${NAME}

bonus:		$(NAME_BONUS)  

${NAME}:	${OBJS}
	@	$(CC) $(OBJS) -o ${NAME}
	@	echo "\n\033[92m["philo" COMPILED SUCCESSFULY]\033[0m\n"

${NAME_BONUS}: 	${BONUS_OBJS}
	@	$(CC) $(BONUS_OBJS) -o ${NAME_BONUS}
	@	echo "\n\033[92m["philo_bonus" COMPILED SUCCESSFULY]\033[0m\n"


clean:
	@	rm -rf ${O_DIR} rm -rf ${BO_DIR}
	@	echo "\n\033[31m[Objs DELETED]\033[0m\n"

fclean:		clean
	@	rm -rf ${O_DIR} rm -rf ${BO_DIR} rm ${NAME} rm ${NAME_BONUS}
	@	echo "\n\033[31m[FCLEAN DONE]\033[0m\n"

re:		fclean all

.PHONY:	all clean fclean re bonus
