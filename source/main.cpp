#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}