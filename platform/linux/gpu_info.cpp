#include <iostream>
#include "gpu.hpp"

using namespace Toollibs::Platform::Linux;

int main()
{
    std::cout << "=== TOOLLIBS GPU INFO ===\n\n";

    std::cout << "GPU: " << GPU::GetName() << "\n\n";
    std::cout << "Driver Info:\n" << GPU::GetDriver() << "\n";

    return 0;
}
