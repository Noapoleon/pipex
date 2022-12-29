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
			setup2.c \
			utils.c \
			test_utils.c # REMOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVE LATER
OBJS	:=	$(SRCS:.c=.o)
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))

# Compiler Options
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
CLIBS	=	-L./$(LIBDIR) -lft
CINCS	=	-I./$(INCDIR)
DEBUG	=	-g3 -gdwarf-4 # REMOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVE LATER

# Other
RM	=	rm -rf

all: $(NAME)

$(NAME): $(LIBDIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) -o $(NAME) # REMOOOOOOOOOOOOOOOOOVE LATER

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(LIBDIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@ # REMOOOOOOOOOOOOOOOOOOOOOOOOVE LATER

$(LIBDIR)/libft.a:
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

normi:
	norminette srcs | awk '{if ($$NF == "OK!") { print "\033[0;92m"$$0"\033[0m" } else if ($$NF == "Error!") { print "\033[0;91m"$$0"\033[0m" } else { print }}'
.PHONY: all clean fclean re resrcs cleansrcs
