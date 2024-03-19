COLOR_RESET = \033[0m
COLOR_RED = \033[91m
COLOR_GREEN = \033[92m
COLOR_YELLOW = \033[93m
COLOR_BOLD = \033[1m
MAKEFLAGS += --no-print-directory


NAME			:= philo

SRC_DIR			:= src
OBJ_DIR			:= obj
SRCS			= $(PHILOSOPHERS_PATH)

PHILOSOPHERS_PATH	= $(PHILOSOPHERS:%=src/philo/%)
PHILOSOPHERS		= parsing_utils.c philosophers.c philo_utils.c philo_stats.c\
				
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS			:= -Wall -Wextra -Werror
CFLAGS			+= -g3
CCFLAGS			:= -I include

RM				:= rm -rf
DIR_DUP			= mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(OBJS) -o $(NAME) 
		@echo "$(COLOR_GREEN)$(COLOR_BOLD)Compilation fini 👍 $(COLOR_RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/philo.h
		@$(DIR_DUP)
		@$(CC) $(CFLAGS) $(CCFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(OBJ_DIR) $(NAME)


re:
	@$(MAKE) fclean
	@$(MAKE) all

git: fclean
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- Cleaning done$(COLOR_RESET)"
	@git add *
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- All files is adding$(COLOR_RESET)"
	@git commit -m "git make fast"
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- All files is committed$(COLOR_RESET)"
	@git push
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)- Save is done$(COLOR_RESET)"


.PHONY: all clean fclean re git