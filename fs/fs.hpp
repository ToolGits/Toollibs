#pragma once

#include <string>
#include <vector>

namespace toollibs {
namespace fs {

struct Entry {
    std::string name;
    bool isDir;
};

// basic
bool exists(const std::string& path);

// file ops
std::string readFile(const std::string& path);
bool write(const std::string& path, const std::string& data);
bool append(const std::string& path, const std::string& data);

// dir ops
bool mkdir(const std::string& path);
std::vector<Entry> listDir(const std::string& path);

// file system ops
bool remove(const std::string& path);
bool copy(const std::string& from, const std::string& to);
bool paste(const std::string& from, const std::string& to);
bool rename(const std::string& oldPath, const std::string& newPath);
bool move(const std::string& from, const std::string& to);

// navigation
std::string currentPath();
bool setCurrentPath(const std::string& path);

// security
bool isSafePath(const std::string& path);

}
}