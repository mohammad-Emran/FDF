NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra 
SRCDIR = src
OBJDIR = obj

SRCS = 	./src/main.c \
		./getNextLine/get_next_line.c \
		./getNextLine/get_next_line_utils.c \
		./src/check_error.c \
		./src/read_map.c \
		./src/draw_line.c \
		./src/init.c \
		./src/iso_projection.c \
		./src/line.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

LIBFT = ./libft
PRINTF = ./ft_printf
INCLUDE = -I./includes/

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a $(PRINTF)/libftprintf.a
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(PRINTF) -lftprintf -L./ -lmlx -lX11 -lXext -lm -o $(NAME)

$(LIBFT)/libft.a:
	@echo "Building libft..."
	@make -C $(LIBFT)

$(PRINTF)/libftprintf.a:
	@echo "Building ft_printf..."
	@make -C $(PRINTF)


$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJDIR)
	@make clean -C $(LIBFT)
	@make clean -C $(PRINTF)

fclean: clean
	@echo "Removing $(NAME)..."
	rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(PRINTF)

re: fclean all

.PHONY: all clean fclean re
