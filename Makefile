NAME = minishell

HEADERS = -I includes -I libft

DIR_SRCS = sources

DIR_OBJS = objects

DIRS = tokenizer redirect utils_and_fcts executing launcher dictionnary expanding

SRC = $(wildcard $(DIR_SRCS)/*.c)

SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(DIR_SRCS)/, $(dir)))

SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))

OBJS = $(subst $(DIR_SRCS),$(DIR_OBJS),$(SOURCES:.c=.o))

CC	= clang

RM	= rm -rf

CFLAGS	= -Wall -Wextra -Werror -g $(HEADERS)

TCAPS = -ltermcap

READLINE = -lreadline -lncurses

LIBFT = libft

FLAGS = -L $(LIBFT) -lft $(READLINE)

ifeq ($(SANITIZE_A),true)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

ifeq ($(SANITIZE_L),true)
	CFLAGS += -fsanitize=leak -fno-omit-frame-pointer
endif


$(NAME): $(OBJS)
		@make -C $(LIBFT)
		@-$(CC) $(CFLAGS) $(OBJS) $(FLAGS) $(HEADER) -o $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
		@mkdir -p objects
		@mkdir -p objects/tokenizer
		@mkdir -p objects/redirect
		@mkdir -p objects/utils_and_fcts
		@mkdir -p objects/executing
		@mkdir -p objects/launcher
		@mkdir -p objects/dictionnary
		@mkdir -p objects/expanding
		@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
		@echo "\033[32mCOMPILATION DE \033[0m"$<"\033[32m SANS FAUTES !\033[0m"

all: $(NAME)

clean:
		make clean -C $(LIBFT)
		$(RM) $(OBJS)
		$(RM) $(DIR_OBJS)
		@echo "\033[31mPLUS GRAND CHOSE... \033[0m"

fclean:	clean
		make fclean -C $(LIBFT)
		$(RM) $(NAME)
		$(RM) $(DIR_OBJS)
		@echo "\033[31mPLUS RIEN !\033[0m"

re:		fclean all

install:
	sudo apt-get install libreadline-dev

PHONY:	all clean fclean re install
