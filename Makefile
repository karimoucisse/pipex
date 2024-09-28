NAME = pipex
CC = cc
RM = rm -f
SRC = src/
GNL = gnl/
LIBFT = Libft/
BONUS = bonus/
CFLAGS = -Wall -Werror -Wextra
GNL_FILES = $(GNL)get_next_line_utils.c  $(GNL)get_next_line.c
LIBFT_FILES = $(LIBFT)ft_substr.c $(LIBFT)ft_strjoin.c $(LIBFT)ft_strtrim.c $(LIBFT)ft_split.c $(LIBFT)ft_itoa.c\
	$(LIBFT)ft_putendl_fd.c $(LIBFT)ft_putchar_fd.c $(LIBFT)ft_putstr_fd.c $(LIBFT)ft_putnbr_fd.c\
	$(LIBFT)ft_strmapi.c $(LIBFT)ft_striteri.c $(LIBFT)ft_isalnum.c $(LIBFT)ft_isalpha.c\
	$(LIBFT)ft_isascii.c $(LIBFT)ft_isdigit.c $(LIBFT)ft_isprint.c $(LIBFT)ft_strlen.c  $(LIBFT)ft_tolower.c\
	$(LIBFT)ft_toupper.c $(LIBFT)ft_strchr.c $(LIBFT)ft_strrchr.c $(LIBFT)ft_strncmp.c $(LIBFT)ft_strnstr.c\
	$(LIBFT)ft_atoi.c $(LIBFT)ft_strlcpy.c $(LIBFT)ft_strlcat.c $(LIBFT)ft_strdup.c $(LIBFT)ft_bzero.c\
	$(LIBFT)ft_memset.c $(LIBFT)ft_memcpy.c $(LIBFT)ft_memchr.c $(LIBFT)ft_memcmp.c\
	$(LIBFT)ft_memmove.c $(LIBFT)ft_calloc.c
CFILES = $(SRC)pipex.c $(SRC)utils.c $(SRC)exec.c $(SRC)handle_struct.c $(LIBFT_FILES)
OFILES = $(CFILES:.c=.o)
BONUS_CFILES = $(BONUS)pipex_bonus.c $(BONUS)utils_bonus.c\
		$(BONUS)exec_bonus.c  $(BONUS)handle_struct_bonus.c $(LIBFT_FILES)\
		$(GNL_FILES)
BONUS_OFILES = $(BONUS_CFILES:.c=.o)
all: $(NAME)
$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
bonus : $(BONUS_OFILES)
	$(CC) $(CFLAGS) $(BONUS_OFILES) -o $(NAME)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OFILES) $(BONUS_OFILES)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
