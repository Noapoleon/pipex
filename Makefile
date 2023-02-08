# Project Structure
NAME	=	pipex
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs
LIBDIR	=	libs
LIBFT	=	libft

# Files
SRCS	:=	pipex.c \
			setup.c \
			commands.c \
			utils1.c \
			utils2.c
OBJS	:=	$(SRCS:.c=.o)
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))

# Compiler Options
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		=	-Wall -Wextra
CLIBS		=	-L./$(LIBDIR) -lft
CINCS		=	-I./$(INCDIR)
DEBUG		=	-g3 -gdwarf-4
MALLOCATOR	=	-g

# Other
RM	=	rm -rf

all: $(NAME)

bonus: all

$(NAME): $(LIBDIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(LIBDIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

$(LIBDIR)/libft.a: | $(LIBDIR)
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a $(LIBDIR)/

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(LIBDIR):
	mkdir -p $(LIBDIR)

resrcs: cleansrcs $(OBJS)

cleansrcs:
	$(RM) $(OBJS)

clean:
	make clean -C $(LIBFT)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)/libft.a
	$(RM) $(LIBDIR)/libft.a
	$(RM) $(NAME)

re: fclean all

norm:
	@echo "\033[44;97;1m               \033[0m"
	@echo "\033[44;97;1m  LIBFT NORM:  \033[45;97;1m  \033[0m"
	@echo "\033[44;97;1m               \033[45;97;1m  \033[0m"
	@echo " \033[45;97;1m                \033[0m"
	@norminette $(LIBFT) | awk '{if ($$NF == "OK!") { print "\033[0;92m"$$0"\033[0m" } else if ($$NF == "Error!") { print "\033[41;97;5;1m"$$0"\033[0m" } else { print }}'
	@echo "\n"
	@echo "\033[44;97;1m                 \033[0m"
	@echo "\033[44;97;1m  SOURCES NORM:  \033[45;97;1m  \033[0m"
	@echo "\033[44;97;1m                 \033[45;97;1m  \033[0m"
	@echo " \033[45;97;1m                  \033[0m"
	@norminette $(SRCDIR) | awk '{if ($$NF == "OK!") { print "\033[0;92m"$$0"\033[0m" } else if ($$NF == "Error!") { print "\033[41;97;5;1m"$$0"\033[0m" } else { print }}'
	@echo "\n"
	@echo "\033[44;97;1m                  \033[0m"
	@echo "\033[44;97;1m  INCLUDES NORM:  \033[45;97;1m  \033[0m"
	@echo "\033[44;97;1m                  \033[45;97;1m  \033[0m"
	@echo " \033[45;97;1m                   \033[0m"
	@norminette $(INCDIR) | awk '{if ($$NF == "OK!") { print "\033[0;92m"$$0"\033[0m" } else if ($$NF == "Error!") { print "\033[41;97;5;1m"$$0"\033[0m" } else { print }}'

malloc_test: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} $(CLIBS) -L. -lmallocator

.PHONY: all bonus clean fclean re resrcs cleansrcs norm malloc_test
