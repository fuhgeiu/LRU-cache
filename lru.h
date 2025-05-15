#include <iostream>
#include <unordered_map>


template <typename K, typename V>

class LRUCache {

    struct Node {

        K key;
        V value;
        Node* prev;
        Node* next;

        Node(const K& k, const V& v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    std::unordered_map<K, Node*> cache;
    Node* head;
    Node* tail;

    void addToFront(Node* node) {

        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {

        Node* before = node->prev;
        Node* after = node->next;
        before->next = after;
        after->prev = before;
    }

    void moveToFront(Node* node) {

        removeNode(node);
        addToFront(node);
    }

public:

    LRUCache(int cap) : capacity(cap) {

        head = new Node(K(), V());
        tail = new Node(K(), V());
        head->next = tail;
        tail->prev = head;
    }

    V get(const K& key) {

        if (cache.find(key) == cache.end())  return V();

        Node* node = cache[key];
        moveToFront(node);

        return node->value;
    }

    void put(const K& key, const V& value) {

        if (cache.find(key) != cache.end()) {

            Node* node = cache[key];
            node->value = value;
            moveToFront(node);

        } else {

            if (cache.size() == capacity) {

                Node* lru = tail->prev;
                removeNode(lru);
                cache.erase(lru->key);
                delete lru;
            }

            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToFront(newNode);
        }
    }

    ~LRUCache() {

        Node* curr = head;

        while (curr) {

            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};
