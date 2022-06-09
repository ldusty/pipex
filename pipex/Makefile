NAME	=	pipex

SRCS	=	utils/ft_split.c	utils/ft_strjoin.c	pipex.c find_path.c\
			utils.c		utils/utils_libft.c

SRCS_B	=	utils/ft_split.c	utils/ft_strjoin.c	bonus/pipex_bonus.c find_path.c\
            utils.c		utils/utils_libft.c	utils/utils_libft2.c bonus/get_next_line.c\
            bonus/here_doc_bonus.c

OBJECTS	= $(SRCS:.c=.o)

OBJECTS_B	= $(SRCS_B:.c=.o)

D_FILES =	$(patsubst %.c,%.d,$(SRCS))

D_FILES_B =	$(patsubst %.c,%.d,$(SRCS_B))

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

.PHONY	:	all clean fclean re

all		:	$(NAME)

bonus	:	fclean $(OBJECTS_B) $(SRCS_B)
	$(CC) $(CFLAGS) $(OBJECTS_B) -fsanitize=address -o $(NAME)

$(NAME)	:	$(OBJECTS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJECTS) -fsanitize=address -o $(NAME)

%.o 	:	%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))
include $(wildcard $(D_FILES_B))

clean	:
	rm -f $(D_FILES_B) $(OBJECTS_B)
	rm -f $(D_FILES) $(OBJECTS)

fclean	:	clean
	rm -f  $(NAME)

re		:	fclean all
