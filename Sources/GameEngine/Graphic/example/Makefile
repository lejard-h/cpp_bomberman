##
## Makefile for  in /home/lelabo_m/rendu/cpp_abstractvm
## 
## Made by Marc Le Labourier
## Login   <lelabo_m@epitech.net>
## 
## Started on  Sat Feb 22 18:12:31 2014 Marc Le Labourier
## Last update Fri May 23 17:02:15 2014 Marc Le Labourier
##


NAME    =       test-event

REP_SRC =       ../

SRCS    =	$(REP_SRC)GraphicContext.cpp \
		main.cpp \
#		KeyboardManager.cpp \

OBJS    =	$(SRCS:.cpp=.o)

CXXFLAGS	+=	-I ../../Header/ -I ../../../Lib/LibGDL/includes/
CXXFLAGS	+=	-W -Wall -Wextra -g

LDFLAGS		+=	-L../../../Lib/LibGDL/libs/ -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2
LDFLAGS		+=	-lm -ldl  -lpthread

CC      =       g++

RM      =       rm -f

$(NAME) :	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS) -g

all     :	$(NAME)

clean   :
		$(RM) $(OBJS)

fclean  :       clean
		$(RM) $(NAME)

re      :       fclean all
