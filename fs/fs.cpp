#include "fs.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>

namespace fsys = std::filesystem;

namespace toollibs {
namespace fs {

static bool hasParentTraversal(const fsys::path& path)
{
    for (const auto& component : path.lexically_normal())
    {
        if (component == "..")
            return true;
    }

    return false;
}

bool isSafePath(const std::string& path)
{
    try
    {
        fsys::path p(path);

        if (hasParentTraversal(p))
            return false;

        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool exists(const std::string& path)
{
    try
    {
        return fsys::exists(path);
    }
    catch (...)
    {
        return false;
    }
}

std::string readFile(const std::string& path)
{
    if (!isSafePath(path))
        return "";

    try
    {
        std::ifstream file(path);

        if (!file.is_open())
            return "";

        std::string content;
        std::string line;

        while (std::getline(file, line))
            content += line + "\n";

        return content;
    }
    catch (...)
    {
        return "";
    }
}

bool write(const std::string& path, const std::string& data)
{
    if (!isSafePath(path))
        return false;

    try
    {
        std::ofstream file(path);

        if (!file.is_open())
            return false;

        file << data;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool append(const std::string& path, const std::string& data)
{
    if (!isSafePath(path))
        return false;

    try
    {
        std::ofstream file(path, std::ios::app);

        if (!file.is_open())
            return false;

        file << data;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool mkdir(const std::string& path)
{
    if (!isSafePath(path))
        return false;

    try
    {
        return fsys::create_directories(path);
    }
    catch (...)
    {
        return false;
    }
}

std::vector<Entry> listDir(const std::string& path)
{
    std::vector<Entry> items;

    if (!isSafePath(path))
        return items;

    try
    {
        if (!fsys::exists(path))
            return items;

        for (const auto& entry :
             fsys::directory_iterator(path))
        {
            Entry e;
            e.name = entry.path().filename().string();
            e.isDir = entry.is_directory();
            items.push_back(e);
        }
    }
    catch (...)
    {
        return {};
    }

    return items;
}

bool remove(const std::string& path)
{
    if (!isSafePath(path))
        return false;

    try
    {
        if (!fsys::exists(path))
            return false;

        return fsys::remove_all(path) > 0;
    }
    catch (...)
    {
        return false;
    }
}

bool copy(const std::string& from, const std::string& to)
{
    if (!isSafePath(from) || !isSafePath(to))
        return false;

    try
    {
        if (!fsys::exists(from))
            return false;

        fsys::copy(
            from,
            to,
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

bool rename(
    const std::string& oldPath,
    const std::string& newPath
)
{
    if (!isSafePath(oldPath) || !isSafePath(newPath))
        return false;

    try
    {
        if (!fsys::exists(oldPath))
            return false;

        fsys::rename(oldPath, newPath);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool move(
    const std::string& from,
    const std::string& to
)
{
    return rename(from, to);
}

std::string currentPath()
{
    try
    {
        return fsys::current_path().string();
    }
    catch (...)
    {
        return "";
    }
}

bool setCurrentPath(const std::string& path)
{
    if (!isSafePath(path))
        return false;

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
