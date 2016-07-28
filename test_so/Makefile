##
## Makefile for  in /u/all/sundas_c/cu/public/malloc/test_so
##
## Made by christophe sundas
## Login   <sundas_c@epitech.net>
##
## Started on  Sun Mar  8 13:45:37 2009 christophe sundas
## Last update Sun Mar  8 17:01:50 2009 tugdual sarazin
##
NAME = libmy_malloc_$(HOSTTYPE).so
CC = gcc
SRC =       mymalloc.c \
		utils.c \
		utils2.c \
	show_list.c \
	list.c
OBJ     =       $(SRC:.c=.o)
TMP     =       $(OBJ:.c=.c~)
CFLAGS  +=     -W -Wall -ansi -pedantic
RM = rm -f
LIB = -L. -lmy_`uname -s` -I.
SHARED = -shared

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(SHARED)
	ln -fs $(NAME) libmy_malloc.so

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(TMP)
	$(RM) $(NAME)

re: fclean all

.PHONY	: all clean fclean re