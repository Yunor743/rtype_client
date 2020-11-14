#include <functional>
#include <unordered_map>
#include <filesystem>
#include <optional>

#ifndef _STORAGE_HPP_
#define _STORAGE_HPP_

class Storage {
    public:
        Storage(const std::string &base, std::function<bool(std::filesystem::path)> selector);
        ~Storage();
        std::optional<long> getIdFromPath(const std::string &path);
        std::optional<std::string> getPathFromId(const long id);
        const std::unordered_map<std::string, long> &getStorage()const;

    private:
        long base_id = 0;
        std::string base_path;
        std::unordered_map<std::string, long> storage_map;
};
#endif //_STORAGE_HPP_
