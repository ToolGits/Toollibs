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
        std::cout
            << "[POP] Initialized."
            << std::endl;
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
        std::cout
            << "[POP] Running git add ."
            << std::endl;

        std::system("git add .");
    }

    void GitCommit()
    {
        std::cout
            << "[POP] Creating commit..."
            << std::endl;

        std::system(
            "git commit -m \"POP automated update\""
        );
    }

    void GitPushPrompt()
    {
        char choice;

        std::cout
            << "[POP] Push changes to remote? [y/N]: ";

        std::cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            std::cout
                << "[POP] Running git push..."
                << std::endl;

            std::system("git push");
        }
        else
        {
            std::cout
                << "[POP] Push cancelled."
                << std::endl;
        }
    }

    void Run()
    {
        std::cout
            << "[POP] Starting workflow..."
            << std::endl;

        GenerateGitKeeps(".");

        GitAdd();

        GitCommit();

        GitPushPrompt();

        std::cout
            << "[POP] Workflow completed."
            << std::endl;
    }
}