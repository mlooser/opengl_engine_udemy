#pragma once

#include <filesystem>
#include <vector>

namespace eng {
    class FileSystem {
    public:
        std::filesystem::path GetExecutableFolder() const;

        std::filesystem::path GetAssetsFolder() const;

        std::vector<char> LoadFile(const std::filesystem::path& filePath);
        std::vector<char> LoadAssetFile(const std::filesystem::path& assetPath);
        std::string LoadAssetFileText(const std::filesystem::path& assetPath);

    };
}
