class LRUCache {
    struct CacheNode {
        CacheNode *prev, *next;
        int key;
    };

  public:
    LRUCache(int capacity) {
        head.next = &tail;
        tail.prev = &head;
        this->capacity = capacity;
        size = 0;
    }

    int get(int key) {
        if (key2Node.count(key) == 0) {
            return -1;
        }
        CacheNode *cur = key2Node[key];
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        CacheNode *second = head.next;
        second->prev = cur;
        cur->next = second;
        head.next = cur;
        cur->prev = &head;

        return key2Value[key];
    }

    void put(int key, int value) {

        if (get(key) == -1) {
            if (size == capacity) {
                // remove the last one;
                CacheNode *cur = tail.prev;
                CacheNode *secondlast = cur->prev;
                secondlast->next = &tail;
                tail.prev = secondlast;
                int curkey = cur->key;
                delete cur;
                cur = nullptr;
                key2Node.erase(curkey);
                key2Value.erase(curkey);
                size--;
            }
            // insert the key after front;
            CacheNode *cur = new CacheNode;
            cur->key = key;
            cur->prev = &head;
            cur->next = head.next;
            head.next = cur;
            cur->next->prev = cur;
            key2Value[key] = value;
            key2Node[key] = cur;
            size++;
        } else {
            key2Value[key] = value;
        }
        return;
    }

  private:
    CacheNode head, tail;
    unordered_map<int, CacheNode *> key2Node;
    unordered_map<int, int> key2Value;
    int capacity;
    int size;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */