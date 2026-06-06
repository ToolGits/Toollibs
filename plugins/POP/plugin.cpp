#include <iostream>
#include "plugin.hpp"

namespace POP
{
    void Initialize()
    {
        std::cout << "[POP] Plugin initialized." << std::endl;
    }

    void Run()
    {
        std::cout << "[POP] Running automation checks..." << std::endl;
    }
}