GCC = gcc

NAME = libft.a

SRC =	ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_strlen.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoll.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_atoi_base.c \
		ft_double_free.c \
		ft_strcmp.c \
		ft_strfind.c \
		ft_get_line.c \
		ft_strappend.c

BSRC =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		$(SRC)

HEADER = libft.h

OBJ = $(SRC:%.c=%.o)

BOBJ = $(BSRC:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ) $(HEADER)

bonus: $(BOBJ)
	@ar rc $(NAME) $(BOBJ) $(HEADER)

%.o: %.c
	$(GCC) $(FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(BOBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
