/*
** LoaderSettings.cpp for Bomberman in /home/lejard_h/cpp_bomberman/Bomberman
**
** Made by hadrien lejard         
** Login   <lejard_h@epitech.net>
**
** Started on  mer. juin  11 16:54:38 2014 hadrien lejard         
** Last update mer. juin  11 16:54:38 2014 hadrien lejard         
*/

#include <exception>
#include <fstream>
#include "LoaderSettings.hh"

Settings::LoaderSettings::LoaderSettings(std::string const &fileName) : _settings(0), _file(fileName)
{
	try
	{
		std::ifstream ofile(fileName.c_str());
		boost::archive::binary_iarchive iTextArchive(ofile);

		iTextArchive.register_type(static_cast<Settings::GameContext *>(0));
		iTextArchive.register_type(static_cast<Settings::Map *>(0));
		iTextArchive.register_type(static_cast<Settings::Player *>(0));
		iTextArchive.register_type(static_cast<Settings::InputConf *>(0));
		iTextArchive.register_type(static_cast<Settings::SavePlayer *>(0));

		iTextArchive >> this->_settings;
		this->_settings->launchtype = Settings::NEWGAME;
	}
	catch (std::exception &e)
	{
		this->_settings = 0;
		std::cerr << "Impossible to deserialize Settings : " << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

Settings::LoaderSettings::~LoaderSettings()
{
	try
	{
		std::ofstream ofile(this->_file.c_str());
		boost::archive::binary_oarchive oTextArchive(ofile);

		oTextArchive.register_type(static_cast<Settings::GameContext *>(0));
		oTextArchive.register_type(static_cast<Settings::Map *>(0));
		oTextArchive.register_type(static_cast<Settings::Player *>(0));
		oTextArchive.register_type(static_cast<Settings::InputConf *>(0));
		oTextArchive.register_type(static_cast<Settings::SavePlayer *>(0));

		oTextArchive << this->_settings;
	}
	catch (std::exception &e)
	{
		std::cerr << "Impossible to serialize Settings : " << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

void	Settings::LoaderSettings::SetSettings(GameContext *set)
{
	this->_settings = set;
}

Settings::GameContext	*Settings::LoaderSettings::GetSettings()
{
	return this->_settings;
}