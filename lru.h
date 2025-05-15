#include <iostream>
#include <unordered_map>


struct Node {

    int key, value;

    Node* prev,next;

    Node(int k, int v): key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {

    int capacity;
    std::unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void addToFront(Node* node) {

        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {

        Node *before = node->prev;
        Node *after = node->next;
        before->next = after;
        after->prev = before;
    }

    void moveToFront(Node* node) {

        removeNode(node);
        addToFront(node);
    }

public:

    LRUCache(int cap): capacity(cap) {

        head = new Node(0, 0);
        tail = new Node(0, 0);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {

        if (cache.find(key) == cache.end()) return -1;

        Node* node = cache[key];
        moveToFront(node);

        return node->value;
    }

    void put(int key, int value) {

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


