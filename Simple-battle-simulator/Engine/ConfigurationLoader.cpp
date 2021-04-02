#include <stdexcept>
#include <iostream>
#include "ConfigurationLoader.h"
#include "../simpleini-master/SimpleIni.h"


int RiD::ConfigurationLoader::getIntData(std::string sectionName, std::string dataName)
{
	CSimpleIniA ini;
	ini.SetUnicode();

	char* section = &sectionName[0];
	char* data = &dataName[0];

	try
	{
		if (ini.LoadFile("RiDconfig.ini") == NULL)
		{
			const char* pVal = ini.GetValue(section, data);

			if (pVal == NULL)
			{
				throw std::invalid_argument("Failed to load configuration data from 'RiDconfig.ini'");
			}
			else
			{
				return atoi(pVal);
			}
		}
		else
		{
			throw std::invalid_argument("Failed to load configuration data from 'RiDconfig.ini'");
		}
	}
	catch (std::invalid_argument & error)
	{
		std::cout << "Data error. " << error.what() << std::endl;
	}
}

std::string RiD::ConfigurationLoader::getStringData(std::string sectionName, std::string dataName)
{
	CSimpleIniA ini;
	ini.SetUnicode();

	char* section = &sectionName[0];
	char* data = &dataName[0];

	try
	{
		if (ini.LoadFile("RiDconfig.ini") == NULL)
		{
			const char* pVal = ini.GetValue(section, data);

			if (pVal == NULL)
			{
				throw std::invalid_argument("Failed to load configuration data from 'RiDconfig.ini'");
			}
			else
			{
				return pVal;
			}
		}
		else
		{
			throw std::invalid_argument("Failed to load configuration data from 'RiDconfig.ini'");
		}
	}
	catch (std::invalid_argument & error)
	{
		std::cout << "Data error. " << error.what() << std::endl;
	}
}
