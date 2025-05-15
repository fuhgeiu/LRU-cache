#include "lru.h"


int main() {

    LRUCache<std::string, std::string> cache(2);

    cache.put("a", "apple");
    cache.put("b", "banana");

    std::cout << cache.get("a") << std::endl;

    cache.put("c", "cherry");

    std::cout << cache.get("b") << std::endl;
    std::cout << cache.get("c") << std::endl;
}
