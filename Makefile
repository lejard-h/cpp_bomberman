##
## Makefile for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
##
## Made by hadrien lejard         
## Login   <lejard_h@epitech.net>
##
## Started on  mer. mai  21 12:47:57 2014 hadrien lejard         
##

SRCDIR	=	Sources/

GAMEENGINE	=	$(SRCDIR)GameEngine/
MENU		=	$(SRCDIR)Menu/
THREAD		=	$(SRCDIR)Thread/
FMOD		=	$(SRCDIR)Audio/
GAME		=	$(SRCDIR)Bomberman/
SCORES		=	$(SRCDIR)Score/
PATTERN		=	$(SRCDIR)Pattern/

SRC	=	$(MENU)Menu.cpp \
		$(MENU)Intro.cpp \
		$(MENU)Welcome.cpp \
		$(MENU)Score.cpp \
		$(MENU)Credit.cpp \
		$(MENU)Player.cpp \
		$(MENU)Map.cpp \
		$(MENU)Opponent.cpp \
		$(MENU)Mode.cpp \
		$(MENU)Load.cpp \
		$(MENU)Option.cpp \
		$(MENU)Controls.cpp \
		$(MENU)Camera.cpp \
		$(MENU)Save.cpp \
		$(MENU)Podium.cpp

SRC	+=	$(GAMEENGINE)Game/Component.cpp \
		$(GAMEENGINE)Game/GameObject.cpp \
		$(GAMEENGINE)Game/SysGame.cpp \
		$(GAMEENGINE)Event/Event.cpp \
		$(GAMEENGINE)Event/EventDispatcher.cpp \
		$(GAMEENGINE)Event/KeyboardManager.cpp \
		$(GAMEENGINE)Event/LeapManager.cpp \
		$(GAMEENGINE)Event/XboxManager.cpp \
		$(GAMEENGINE)Event/SysEvent.cpp \
		$(GAMEENGINE)Engine/Engine.cpp \
		$(GAMEENGINE)Graphic/GraphicContext.cpp \
		$(GAMEENGINE)Graphic/ScreenShot.cpp \
		$(GAMEENGINE)Settings/Settings.cpp \
		$(GAMEENGINE)Audio/SysAudio.cpp \
		$(GAMEENGINE)Graphic/Renderer.cpp \
		$(GAMEENGINE)Exception/Exception.cpp \


SRC	+=	$(THREAD)Mutex.cpp \
		$(THREAD)ScopedLock.cpp \
		$(THREAD)Thread.cpp \
		$(THREAD)CondVar.cpp \
		$(PATTERN)Timer.cpp \
		$(FMOD)srcs/Playlist.cpp \
		$(FMOD)srcs/Sound.cpp \

SRC	+=	$(GAME)MapComponent.cpp \
		$(GAME)GraphicComponent.cpp \
		$(GAME)LifeComponent.cpp \
		$(GAME)PositionComponent.cpp \
		$(GAME)UndestructibleBox.cpp \
		$(GAME)DestructibleBox.cpp \
		$(GAME)PhysicComponent.cpp \
		$(GAME)InputComponent.cpp \
		$(GAME)PlayerInputComponent.cpp \
		$(GAME)CamInputComponent.cpp \
		$(GAME)IaComponent.cpp \
		$(GAME)Player.cpp \
		$(GAME)Image.cpp \
		$(GAME)Menu.cpp \
		$(GAME)World.cpp \
		$(GAME)FireAnim.cpp \
		$(GAME)Cam.cpp \
		$(GAME)BombComponent.cpp \
		$(GAME)ExplodeComponent.cpp \
		$(GAME)TimerComponent.cpp \
		$(GAME)Bomb.cpp \
		$(GAME)AudioComponent.cpp \
		$(GAME)DamageEvent.cpp \
		$(GAME)BonusAddBomb.cpp \
		$(GAME)CollideEvent.cpp \
		$(GAME)DropBonusComponent.cpp \
		$(GAME)BonusSpeedPlayer.cpp \
		$(GAME)BonusSizeBomb.cpp \
		$(GAME)ScoreComponent.cpp \
		$(GAME)ScoreEvent.cpp \
		$(GAME)IA/Astar.cpp \
		$(GAME)ClassicMode.cpp \
		$(GAME)LoaderSettings.cpp \
		$(GAME)IA/IAactions.cpp \
		$(GAME)Launch.cpp \

OBJ	=	$(SRC:.cpp=.o)

CC	=	g++

CXXFLAGS        +=      -I $(GAME)Header -I $(PATTERN) -I $(THREAD)Header
CXXFLAGS	+=	-I $(GAMEENGINE)Header -I $(MENU) -I $(FMOD)Header
CXXFLAGS	+=	-I Lib/LibSfml/Include
CXXFLAGS        +=      -I Lib/LibGDL/includes/
CXXFLAGS	+=	-I Lib/LibSerial/include
CXXFLAGS        +=      -I Lib/LibLeap/include
CXXFLAGS        +=      -Wall -Wextra -g3

LDFLAGS         +=      -L Lib/LibGDL/libs/ -lgdl_gl -lGL -lGLEW  -lfbxsdk -lSDL2
LDFLAGS		+=	$(FMOD)libs/libfmodex64.so
LDFLAGS		+=	-L Lib/LibLeap/ -lLeap
LDFLAGS         +=      -L Lib/LibSerial -lboost_serialization
LDFLAGS		+= 	-L Lib/LibSfml -lsfml-system -lsfml-graphics -lsfml-window -ljpeg -lGLEW
LDFLAGS		+=	-lm -ldl -lrt -lpthread

RM	=	rm -f

#########################
#                       #
#     Compilation :     #
#                       #
#########################

NAME	=	bomberman

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
