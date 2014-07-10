#!/bin/sh
## run.sh for  in /home/lelabo_m/rendu/cpp_bomberman/Leapd
## 
## Made by Marc Le Labourier
## Login   <lelabo_m@epitech.net>
## 
## Started on  Tue Jun 10 21:30:01 2014 Marc Le Labourier
## Last update Tue Jun 10 21:39:16 2014 Marc Le Labourier
##

g++  -I ../GameEngine/Header/ -I ../Lib/LibLeap/include/ main.c ../GameEngine/Event/LeapManager.cpp \
-L ../Lib/LibLeap/ -lLeap
LD_LIBRARY_PATH=../Lib/LibLeap/ ./a.out
rm a.out
