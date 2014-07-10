##
## Makefile for  in /home/lelabo_m/rendu/cpp_abstractvm
## 
## Made by Marc Le Labourier
## Login   <lelabo_m@epitech.net>
## 
## Started on  Sat Feb 22 18:12:31 2014 Marc Le Labourier
## Last update Mon May 26 15:17:19 2014 Marc Le Labourier
##


NAME    =       test-engine

REP_SRC =       ../

SRCS    =	../../Event/Event.cpp \
		../../Event/EventDispatcher.cpp \
		../../Event/KeyboardManager.cpp \
		../../Event/SysEvent.cpp \
		../Engine.cpp \
		../../Settings/Settings.cpp \
		../../Graphic/GraphicContext.cpp \
		../../../Thread/Mutex.cpp \
		../../../Thread/Thread.cpp \
		main.cpp \

OBJS    =	$(SRCS:.cpp=.o)

CXXFLAGS	+=	-I ../../Header/ -I ../../../Pattern/ -I ../../../Thread/Header
CXXFLAGS	+=	-I ../../../Lib/LibGDL/includes/
CXXFLAGS	+=	-W -Wall -Wextra -g

LDFLAGS         +=      -L../../../Lib/LibGDL/libs/ -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2
LDFLAGS         +=      -lm -ldl  -lpthread

CC      =       g++

RM      =       rm -f

$(NAME) :	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)

all     :	$(NAME)

clean   :
		$(RM) $(OBJS)

fclean  :       clean
		$(RM) $(NAME)

re      :       fclean all
