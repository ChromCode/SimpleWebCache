#include "FileCache.h"
// Default Constructor setting the cache root directory
FileCache::FileCache(string p_root) { root = p_root; }
// Get the most updated version of the Cache File Item with p_file_name 
FileCacheItem * FileCache::getFile(string p_file_name)
{
    string file_name = root+p_file_name; // Add the root directory to the file
    if ( cache[file_name] == NULL) { // file does not exit in the cache
        // Create a new file item
        FileCacheItem * fileCacheItem = new FileCacheItem(file_name);
        cache[file_name] = fileCacheItem; // Add to Map
        return fileCacheItem;// return a pointer 
    }
    return cache[file_name]; // return a pointer to the FileCacheItem object
}
FileCache::~FileCache () { // Destructor
    // Loop through iterator to delete all FileCacheItem objects
    for_each (cache.begin(),cache.end(),[](const std::pair<string,FileCacheItem *>& it) -> bool {
            FileCacheItem * fileCacheItem = std::get<1>(it); // Fetch Pair value: FileCacheItem *
            delete(fileCacheItem); // delete FileCacheItem object
            return true; // return true for lambda
       });
}
