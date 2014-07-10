##
## Makefile for  in /home/maigna_j/cpp_bomberman/Menu
## 
## Made by jeremy maignan
## Login   <maigna_j@epitech.net>
## 
## Started on  Sun Jun  8 18:05:01 2014 jeremy maignan
## Last update Mon Jun  9 14:41:28 2014 jeremy maignan
##

NAME =			MENU

SRC =			../GameEngine/Settings/Settings.cpp\
			Menu.cpp \
			Intro.cpp \
			Welcome.cpp \
			Score.cpp \
			Credit.cpp \
			Player.cpp \
			Map.cpp \
			Opponent.cpp \
			Mode.cpp \
			Load.cpp \
			Option.cpp \
			Controls.cpp \
			Camera.cpp \
			Save.cpp \

CC = 			g++

OBJ =			$(SRC:.cpp=.o)


CXXFLAGS += 	 	-Wall -Wextra # Warning
CXXFLAGS +=		-I ./SFML -I../GameEngine/Header -I ../Lib/LibSerial/include # Include

LDFLAGS += 		-L./Library -lsfml-system -lsfml-graphics -lsfml-window -lGLEW -ljpeg

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)

re: fclean all

