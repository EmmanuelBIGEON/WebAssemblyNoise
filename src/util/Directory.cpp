#include "Directory.h"

#include <Logger.h> // printjs()

#include <filesystem>

namespace fs = std::filesystem;

void DisplayDirectoryContents(const std::string& directoryPath)
{
    Logger::Log("DisplayDirectoryContents");
    try {

        // Check if the provided path exists and is a directory
        if (!fs::exists(directoryPath)) {
            Logger::Log("Error: Directory does not exist: ");
            return;
        }

        if (!fs::is_directory(directoryPath)) {
            Logger::Log("Error: Path is not a directory: ");
            return;
        }

        // Iterate through the directory entries
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            std::string entryType;

            if (fs::is_regular_file(entry.status())) {
                entryType = "File";
            } else if (fs::is_directory(entry.status())) {
                entryType = "Directory";
            } else if (fs::is_symlink(entry.status())) {
                entryType = "Symlink";
            } else {
                entryType = "Other";
            }

            // Log the entry path and its type
            Logger::Log(entryType + ": " + entry.path().string());
        }
    } catch (const fs::filesystem_error& e) {
        Logger::Log("Filesystem error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        Logger::Log("General error: " + std::string(e.what()));
    }
}