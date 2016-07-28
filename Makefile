##
## Makefile for my_script in /u/all/sarazi_t/cu/rendu/c/my_select
##
## Made by tugdual sarazin
## Login   <sarazi_t@epitech.net>
##
## Started on  Tue Dec  2 14:31:51 2008 tugdual sarazin
## Last update Sun Mar  8 04:41:18 2009 christophe sundas
##

##export OSTYPE=FreeBSD

CC_FreeBSD	=	gcc
CC_solaris	=	/usr/sfw/bin/gcc
#OSTYPE		=	${uname -s}
TRUC2		=	$(CC_$(uname -s)
##CC		=	$(CC_${uname -s})
CCTMP		=	gcc

NAME		=	my_testmalloc
SRC		=	testmalloc.c \
			mymalloc.c

OBJS		=	$(SRC:.c=.o)
TMP		=	$(SRC:.c=.c~)

LIB             =       -L. -lmy
INC		=	-I.

CFLAGS		=	$(INC) -g -W -Wall -ansi -pedantic
RM		=	rm -f



$(NAME)		:	$(OBJS)
			$(CCTMP) -o $(NAME) $(OBJS) $(LIB)

real		:	

test		:	$(OBJS)
			$(TRUC2) -o $(NAME) $(OBJS) $(LIB)


all		:	$(NAME)

clean		:
			$(RM) $(OBJS)
			$(RM) $(TMP)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re