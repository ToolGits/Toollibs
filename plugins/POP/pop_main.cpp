#include "plugin.hpp"
#include <iostream>

int main()
{
    std::cout << "[POP] Starting Toollibs POP..." << std::endl;

    POP::Initialize();
    POP::Run();

    std::cout << "[POP] Finished." << std::endl;

    return 0;
}