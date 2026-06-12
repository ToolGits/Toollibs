#ifdef _WIN32
#include <windows.h>
#endif

#include "fs/fs.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

using namespace toollibs::fs;
namespace fsys = std::filesystem;

#ifdef _WIN32
void enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}
#endif

// =========================
// COLORS
// =========================
#define GREEN "\033[32m"
#define RED   "\033[31m"
#define CYAN  "\033[36m"
#define RESET "\033[0m"

// =========================
// SPLIT INPUT
// =========================
std::vector<std::string> split(const std::string& input)
{
    std::vector<std::string> out;
    std::string temp;

    for (char c : input)
    {
        if (c == ' ')
        {
            if (!temp.empty())
            {
                out.push_back(temp);
                temp.clear();
            }
        }
        else temp += c;
    }

    if (!temp.empty())
        out.push_back(temp);

    return out;
}

// =========================
// GET PATH
// =========================
std::string getPath()
{
    return fsys::current_path().string();
}

// =========================
// MAIN
// =========================
int main()
{
#ifdef _WIN32
    enableANSI();
#endif

    std::string input;

    std::cout << "=====================================\n";
    std::cout << " Toollibs FS Emulated CMD\n";
    std::cout << "=====================================\n";
    std::cout << "Type 'help' for commands\n\n";

    while (true)
    {
        std::cout << CYAN << "fs:" << getPath() << "> " << RESET;

        std::getline(std::cin, input);

        auto cmd = split(input);
        if (cmd.empty()) continue;

        // =========================
        // HELP
        // =========================
        if (cmd[0] == "help")
        {
            std::cout <<
            "\nCommands:\n"
            " mkdir <path>\n"
            " list <path>\n"
            " remove <path>\n"
            " copy <from> <to>\n"
            " paste <from> <to>\n"
            " rename <old> <new>\n"
            " move <from> <to>\n"
            " read <file>\n"
            " write <file> <text>\n"
            " cd <path>\n"
            " clear\n"
            " exit\n\n";
        }

        // =========================
        // MKDIR
        // =========================
        else if (cmd[0] == "mkdir" && cmd.size() >= 2)
        {
            if (mkdir(cmd[1]))
                std::cout << GREEN << "[OK] Directory created\n" << RESET;
            else
                std::cout << RED << "[FAIL] Cannot create directory\n" << RESET;
        }

        // =========================
        // LIST
        // =========================
        else if (cmd[0] == "list" && cmd.size() >= 2)
        {
            auto items = listDir(cmd[1]);
            for (auto& i : items)
                std::cout << i << "\n";
        }

        // =========================
        // REMOVE
        // =========================
        else if (cmd[0] == "remove" && cmd.size() >= 2)
        {
            if (remove(cmd[1]))
                std::cout << GREEN << "[OK] Removed\n" << RESET;
            else
                std::cout << RED << "[FAIL] Cannot remove\n" << RESET;
        }

        // =========================
        // READ
        // =========================
        else if (cmd[0] == "read" && cmd.size() >= 2)
        {
            std::cout << readFile(cmd[1]) << "\n";
        }

        // =========================
        // WRITE
        // =========================
        else if (cmd[0] == "write" && cmd.size() >= 3)
        {
            std::string data;

            for (size_t i = 2; i < cmd.size(); i++)
            {
                data += cmd[i];
                if (i + 1 < cmd.size()) data += " ";
            }

            if (write(cmd[1], data))
                std::cout << GREEN << "[OK] File written\n" << RESET;
            else
                std::cout << RED << "[FAIL] Cannot write file\n" << RESET;
        }

        // =========================
        // COPY
        // =========================
        else if (cmd[0] == "copy" && cmd.size() >= 3)
        {
            std::cout << (copy(cmd[1], cmd[2]) ? "[OK]\n" : "[FAIL]\n");
        }

        // =========================
        // PASTE
        // =========================
        else if (cmd[0] == "paste" && cmd.size() >= 3)
        {
            std::cout << (paste(cmd[1], cmd[2]) ? "[OK]\n" : "[FAIL]\n");
        }

        // =========================
        // RENAME
        // =========================
        else if (cmd[0] == "rename" && cmd.size() >= 3)
        {
            std::cout << (rename(cmd[1], cmd[2]) ? "[OK]\n" : "[FAIL]\n");
        }

        // =========================
        // MOVE
        // =========================
        else if (cmd[0] == "move" && cmd.size() >= 3)
        {
            std::cout << (move(cmd[1], cmd[2]) ? "[OK]\n" : "[FAIL]\n");
        }

        // =========================
        // CD
        // =========================
        else if (cmd[0] == "cd" && cmd.size() >= 2)
        {
            if (cd(cmd[1]))
                std::cout << GREEN << "[OK] Changed directory\n" << RESET;
            else
                std::cout << RED << "[FAIL] Invalid path\n" << RESET;
        }

        // =========================
        // CLEAR
        // =========================
        else if (cmd[0] == "clear")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }

        // =========================
        // EXIT
        // =========================
        else if (cmd[0] == "exit")
        {
            break;
        }

        // =========================
        // UNKNOWN
        // =========================
        else
        {
            std::cout << RED << "Unknown command. type 'help'\n" << RESET;
        }
    }

    return 0;
}