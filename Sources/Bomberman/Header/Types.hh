/*
** Enum.hh for Bomberman in /home/lejard_h/rendu/cpp_bomberman/GameEngine
**
** Made by hadrien lejard
** Login   <lejard_h@epitech.net>
**
** Started on  mer. mai  21 12:57:46 2014 hadrien lejard
// Last update Fri Jun 13 11:49:41 2014 Marc Le Labourier
*/

#ifndef __TYPES_HH__
# define __TYPES_HH__

namespace Bomb
{
  enum ComponentType	{ Input_c, Physics_c, Map_c, Position_c, Life_c, Undefined_c,
			  Audio_c , Ia_c, PlayerInput_c, Render_c, Timer_c, Explode_c,
			  Bomb_c, CamInput_c, Anim_c, Score_c };

  enum GameObjectTag	{ Undefined_o, Player_o, DefaultBomb_o, NormalBomb_o, World_o,
			  DestructibleBox_o, UndestructibleBox_o, Cam_o, Image_o, BonusSizeBomb_o,
			  BonusSpeed_o, BonusAddBomb_o, FireAnim_o, ClassicMode_o, Menu_o };
}

#endif
