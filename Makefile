# Project Structure
NAME	=	pipex
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs
LIBDIR	=	libs
LIBFT	=	libft

# Files
SRCS	:=	pipex.c \
			setup1.c \
			setup2.c \
			setup3.c \
			utils.c
OBJS	:=	$(SRCS:.c=.o)
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))

# Compiler Options
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
CLIBS	=	-L./$(LIBDIR) -lft
CINCS	=	-I./$(INCDIR)
DEBUG	=	-g3 -gdwarf-4

# Other
RM	=	rm -rf

all: $(NAME)

bonus: all

$(NAME): $(LIBDIR)/libft.a $(OBJS)
	$(CC) $(DEBUG) $(CFLAGS) $(OBJS) $(CLIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(LIBDIR)
	$(CC) $(DEBUG) $(CFLAGS) $(CINCS) -c $< -o $@

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

fclean:	clean
	$(RM) $(LIBFT)/libft.a
	$(RM) $(LIBDIR)/libft.a
	$(RM) $(NAME)

re: fclean all

norm:
	norminette $(SRCS) $(INCDIR) | awk '{if ($$NF == "OK!") { print "\033[0;92m"$$0"\033[0m" } else if ($$NF == "Error!") { print "\033[0;91m"$$0"\033[0m" } else { print }}'

.PHONY: all bonus clean fclean re resrcs cleansrcs norm
