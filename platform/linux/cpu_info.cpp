#include <iostream>
#include "cpu.hpp"

using namespace Toollibs::Platform::Linux;

int main()
{
    std::cout << "=== TOOLLIBS CPU INFO ===\n\n";

    std::cout << "CPU: " << CPU::GetName() << "\n";
    std::cout << "Vendor: " << CPU::GetVendor() << "\n";
    std::cout << "Cores: " << CPU::GetCores() << "\n";

    return 0;
}
