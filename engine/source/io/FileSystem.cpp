//
// Created by Marcin Lusa on 19/12/2025.
//

#include "FileSystem.h"

#include <config.h>
#include <vector>

#if defined _WIN32
#include <windows.h>
#elif defined (__APPLE__)
#include <mach-o/dyld.h>
#elif defined (__linux__)
#include <unistd.h>
#include <limits.h>
#endif

#include <fstream>

std::filesystem::path eng::FileSystem::GetExecutableFolder() const {
#if defined _WIN32
    wchar_t buf[MAX_PATH];
    GetModuleFileNameW(NULL, buf, MAX_PATH);
    return std::filesystem::path(buf).remove_filename();
#elif defined(APPLE)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::string tmp(size, '\0');
    _NSGetExecutablePath(tmp.data(), &size);
    return std::filesystem::weakly_canonical(std::filesystem::path(tmp)).remove_filename();
#elif defined(linux)
    return std::filesystem::weakly_canonical(std::filesystem::read_symlink("/proc/self/exe")).remove_filename();
#else
    return std::filesystem::current_path();
#endif
}

std::filesystem::path eng::FileSystem::GetAssetsFolder() const {
#if defined (ASSETS_ROOT)
    auto path = std::filesystem::path(std::string(ASSETS_ROOT));
    if (std::filesystem::exists(path))
    {
        return path;
    }
#endif
    return std::filesystem::weakly_canonical(GetExecutableFolder() / "assets");
}

std::vector<char> eng::FileSystem::LoadFile(const std::filesystem::path &filePath) {
    std::ifstream ifs(filePath.string(), std::ios::binary| std::ios::ate);

    if (!ifs.is_open()) {
        //TODO ML exceptions
        return {};
    }

    auto size = ifs.tellg();
    ifs.seekg(0);

    std::vector<char> buffer(size);

    if (!ifs.read(buffer.data(), size)) {
        //TODO ML exceptions
        return {};
    }

    return buffer;
}

std::vector<char> eng::FileSystem::LoadAssetFile(const std::filesystem::path &assetPath) {
    return LoadFile(GetAssetsFolder() / assetPath );
}

std::string eng::FileSystem::LoadAssetFileText(const std::filesystem::path &assetPath) {
    auto buffer = LoadAssetFile(assetPath);

    return {buffer.begin(), buffer.end()};
}
