#include "SFML/Graphics.hpp"
#include "Engine/RiDGame.h"
#include "Engine/ConfigurationLoader.h"

int main()
{

   RiD::RiDGame window(RiD::ConfigurationLoader::getIntData("video settings", "screenWidth"), RiD::ConfigurationLoader::getIntData("video settings", "screenHeight"), RiD::ConfigurationLoader::getStringData("video settings", "screenTitle"));
    return 0;
}