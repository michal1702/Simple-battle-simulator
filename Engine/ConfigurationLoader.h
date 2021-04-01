#pragma once

#include <string>

namespace RiD
{

	class ConfigurationLoader
	{
	public:

		/* 
		Returns datatype int from 'ini' config file.
		@param sectionName name od section
		@param dataName name of data
		*/
		static int getIntData(std::string sectionName, std::string dataName);
		/*
		Returns data type string from 'ini' config file.
		@param sectionName name od section
		@param dataName name of data
		*/
		static std::string getStringData(std::string sectionName, std::string dataName);
	};

}