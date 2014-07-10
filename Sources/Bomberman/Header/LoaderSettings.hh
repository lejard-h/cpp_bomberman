/*
** LoaderSettings.hh for  in /home/lejard_h/cpp_bomberman/Bomberman/Header
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mer. juin  11 16:52:30 2014 hadrien lejard         
** Last update mer. juin  11 16:52:30 2014 hadrien lejard         
*/

#ifndef __LOADERSETTINGS_HH__
#define __LOADERSETTINGS_HH__

#include "Settings.hpp"

namespace Settings
{
	class LoaderSettings
	{
	public:
		LoaderSettings(std::string const &);
		GameContext	*GetSettings();
		~LoaderSettings();
		void	SetSettings(GameContext *);

	private:
		GameContext	*_settings;
		std::string	_file;
	};
}

#endif