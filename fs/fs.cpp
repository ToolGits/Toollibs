#include "fs.hpp"

#include <filesystem>
#include <fstream>
#include <algorithm>

namespace fsys = std::filesystem;

namespace toollibs {
namespace fs {

// =========================
// SAFE PATH CHECK
// =========================

bool isSafePath(const std::string& path)
{
    try
    {
        fsys::path p = fsys::weakly_canonical(path);

        // bloqueia path malicioso básico
        std::string str = p.string();

        if (str.find("..") != std::string::npos)
            return false;

        return true;
    }
    catch (...)
    {
        return false;
    }
}

// =========================
// BASIC
// =========================

bool exists(const std::string& path)
{
    return fsys::exists(path);
}

// =========================
// FILE OPS
// =========================

std::string readFile(const std::string& path)
{
    if (!isSafePath(path)) return "";

    std::ifstream file(path);
    if (!file.is_open()) return "";

    std::string content, line;
    while (std::getline(file, line))
        content += line + "\n";

    return content;
}

bool write(const std::string& path, const std::string& data)
{
    if (!isSafePath(path)) return false;

    std::ofstream file(path);
    if (!file.is_open()) return false;

    file << data;
    return true;
}

bool append(const std::string& path, const std::string& data)
{
    if (!isSafePath(path)) return false;

    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) return false;

    file << data;
    return true;
}

// =========================
// DIR OPS
// =========================

bool mkdir(const std::string& path)
{
    if (!isSafePath(path)) return false;
    return fsys::create_directories(path);
}

std::vector<Entry> listDir(const std::string& path)
{
    std::vector<Entry> items;

    if (!isSafePath(path)) return items;
    if (!fsys::exists(path)) return items;

    for (auto& entry : fsys::directory_iterator(path))
    {
        Entry e;
        e.name = entry.path().filename().string();
        e.isDir = entry.is_directory();
        items.push_back(e);
    }

    return items;
}

// =========================
// REMOVE
// =========================

bool remove(const std::string& path)
{
    if (!isSafePath(path)) return false;
    if (!fsys::exists(path)) return false;

    try
    {
        return fsys::remove_all(path) > 0;
    }
    catch (...)
    {
        return false;
    }
}

// =========================
// COPY / PASTE
// =========================

bool copy(const std::string& from, const std::string& to)
{
    if (!isSafePath(from) || !isSafePath(to)) return false;
    if (!fsys::exists(from)) return false;

    try
    {
        fsys::copy(from, to,
            fsys::copy_options::recursive |
            fsys::copy_options::overwrite_existing
        );
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool paste(const std::string& from, const std::string& to)
{
    return copy(from, to);
}

// =========================
// RENAME / MOVE
// =========================

bool rename(const std::string& oldPath, const std::string& newPath)
{
    if (!isSafePath(oldPath) || !isSafePath(newPath)) return false;
    if (!fsys::exists(oldPath)) return false;

    try
    {
        fsys::rename(oldPath, newPath);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool move(const std::string& from, const std::string& to)
{
    return rename(from, to);
}

// =========================
// NAVIGATION
// =========================

std::string currentPath()
{
    return fsys::current_path().string();
}

bool setCurrentPath(const std::string& path)
{
    if (!isSafePath(path)) return false;

    try
    {
        fsys::current_path(path);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

}
}