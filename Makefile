# Project Structure
NAME	=	pipex
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs
LIBDIR	=	libs
LIBFT	=	libft

# Files
SRCS	:=	pipex.c \
			test_utils.c # REMOVE LATER
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

$(NAME): $(LIBDIR)/libft.a $(OBJS)
	$(CC) $(DEBUG) $(CFLAGS) $(OBJS) $(CLIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(LIBDIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

$(LIBDIR)/libft.a:
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a $(LIBDIR)/

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	make clean -C $(LIBFT)
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(LIBFT)/libft.a
	$(RM) $(LIBDIR)/libft.a
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
