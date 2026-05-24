#include "magnetar/filesystem/file_system.h"

std::unordered_map<std::type_index, magnetar::UniqueRef<magnetar::FileSystem>> magnetar::FileSystem::s_filesystems;