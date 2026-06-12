#include "fs.hpp"

#include <filesystem>
#include <fstream>

namespace fsys = std::filesystem;

namespace toollibs {
namespace fs {

// ---------------- BASIC ----------------

bool exists(const std::string& path) {
    return fsys::exists(path);
}

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return "";

    std::string content, line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    return content;
}

bool write(const std::string& path, const std::string& data) {
    std::ofstream file(path);
    if (!file.is_open()) return false;

    file << data;
    return true;
}

// ---------------- DIR ----------------

bool mkdir(const std::string& path) {
    return fsys::create_directories(path);
}

std::vector<std::string> listDir(const std::string& path) {
    std::vector<std::string> items;

    if (!fsys::exists(path)) return items;

    for (auto& entry : fsys::directory_iterator(path)) {
        items.push_back(entry.path().string());
    }

    return items;
}

// ---------------- REMOVE ----------------

bool remove(const std::string& path) {
    if (!fsys::exists(path)) return false;

    return fsys::remove_all(path) > 0;
}

// ---------------- COPY / PASTE ----------------

bool copy(const std::string& from, const std::string& to) {
    if (!fsys::exists(from)) return false;

    try {
        fsys::copy(from, to,
            fsys::copy_options::recursive |
            fsys::copy_options::overwrite_existing
        );
        return true;
    } catch (...) {
        return false;
    }
}

bool paste(const std::string& from, const std::string& to) {
    return copy(from, to);
}

// ---------------- RENAME ----------------

bool rename(const std::string& oldPath, const std::string& newPath) {
    if (!fsys::exists(oldPath)) return false;

    try {
        fsys::rename(oldPath, newPath);
        return true;
    } catch (...) {
        return false;
    }
}

// ---------------- MOVE ----------------

bool move(const std::string& from, const std::string& to) {
    if (!fsys::exists(from)) return false;

    try {
        fsys::rename(from, to);
        return true;
    } catch (...) {
        return false;
    }
}

std::string currentPath()
{
    return fsys::current_path().string();
}

bool setCurrentPath(const std::string& path)
{
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