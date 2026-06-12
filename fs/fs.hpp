#pragma once

#include <string>
#include <vector>

namespace toollibs {
namespace fs {

bool exists(const std::string& path);

std::string readFile(const std::string& path);
bool write(const std::string& path, const std::string& data);

bool mkdir(const std::string& path);

std::vector<std::string> listDir(const std::string& path);

bool remove(const std::string& path);

bool copy(const std::string& from, const std::string& to);

bool paste(const std::string& from, const std::string& to);

bool rename(const std::string& oldPath, const std::string& newPath);
bool move(const std::string& from, const std::string& to);

bool cd(const std::string& path);

}
}