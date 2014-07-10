NAME		=	playList

SRC		=	srcs/main.cpp \
			srcs/Playlist.cpp \
			srcs/Sound.cpp \
			../Thread/Thread.cpp \
			../Thread/Mutex.cpp \
			../Thread/CondVar.cpp \

OBJ		=	$(SRC:.cpp=.o)

RM 		=	rm -f

CC 		=	g++

CPPFLAGS 	=	-Wall -Wextra
CPPFLAGS	+= 	-I./Header -I ../Thread/Header

LDFLAGS 	= 	libs/libfmodex64.so -lpthread

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
