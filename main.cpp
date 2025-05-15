#include "lru.h"


int main() {

    LRUCache cache(2);
    cache.put(1, 100);
    cache.put(2, 200);
    std::cout << cache.get(1) << std::endl;
    cache.put(3, 300);
    std::cout << cache.get(2) << std::endl;
    cache.put(4, 400);
    std::cout << cache.get(1) << std::endl;
    std::cout << cache.get(3) << std::endl;
    std::cout << cache.get(4) << std::endl;

    return 0;
}