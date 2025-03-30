#include "utils/memory.h"
#include "diablo.h"

namespace devilution {

/**
 * @brief Allocate memory conditionally based on available RAM
 * @param standardSize Size to allocate with standard 16MB RAM
 * @param doubleSize Size to allocate with 32MB RAM mod
 * @return Allocated memory pointer
 */
void* MemAlloc(size_t standardSize, size_t doubleSize)
{
    if (DBL_MEM) {
        return malloc(doubleSize);
    }
    return malloc(standardSize);
}

} // namespace devilution 