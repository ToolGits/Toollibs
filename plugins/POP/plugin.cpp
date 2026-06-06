#include "plugin.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstdlib>

namespace fs = std::filesystem;

namespace POP
{
    void Initialize()
    {
        std::cout << "[POP] Initialized." << std::endl;
    }

    void GenerateGitKeeps(const char* rootPath)
    {
        for (const auto& entry : fs::recursive_directory_iterator(rootPath))
        {
            if (!entry.is_directory())
                continue;

            bool empty = fs::is_empty(entry.path());

            if (empty)
            {
                fs::path gitkeep = entry.path() / ".gitkeep";

                if (!fs::exists(gitkeep))
                {
                    std::ofstream file(gitkeep);
                    file.close();

                    std::cout
                        << "[POP] Created "
                        << gitkeep.string()
                        << std::endl;
                }
            }
        }
    }

    void GitAdd()
    {
        std::cout << "[POP] Running git add ." << std::endl;
        std::system("git add .");
    }
}