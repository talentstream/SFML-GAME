#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/application.h"

int main()
{
    try
    {
        Application application;
        application.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}