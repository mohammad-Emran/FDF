NAME	= libftprintf.a
CC	= cc
CFLAGS	= -Wall -Wextra -Werror
AR	= ar
ARFLAGS = rcs
RM	= rm -rf
SRCS 	= ft_printf.c ft_put.c
OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)
OBJDIR = obj
SRCDIR = src
all: $(NAME)
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re 
