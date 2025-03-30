#pragma once

#include <cstddef>

namespace devilution {

/**
 * @brief Allocate memory conditionally based on available RAM
 * @param standardSize Size to allocate with standard 16MB RAM
 * @param doubleSize Size to allocate with 32MB RAM mod
 * @return Allocated memory pointer
 */
void* MemAlloc(size_t standardSize, size_t doubleSize);

} // namespace devilution 