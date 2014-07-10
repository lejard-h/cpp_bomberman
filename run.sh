#!/bin/sh
## run.sh for  in /home/lelabo_m/rendu/cpp_bomberman/Bomberman
##
## Made by Marc Le Labourier
## Login   <lelabo_m@epitech.net>
##
## Started on  Thu Jun  5 20:31:01 2014 Marc Le Labourier
## Last update Sun Jun 15 21:17:01 2014 Marc Le Labourier
##

make
LD_LIBRARY_PATH=Lib/LibGDL/libs/:Lib/LibSerial:Lib/LibSfml:Lib/LibLeap ./bomberman $1
./.log.sh
