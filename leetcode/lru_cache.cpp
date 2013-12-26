#include <unordered_map>
using namespace std;

class CacheEntry {
public:
    CacheEntry():
        key(-1),
        value(-1),
        m_prev(NULL),
        m_next(NULL)
    {}

    CacheEntry(int v):
        key(-1),
        value(v),
        m_prev(NULL),
        m_next(NULL)
    {}

    void removeFromList() {
        if (m_prev)
            m_prev->m_next = m_next;
        if (m_next)
            m_next->m_prev = m_prev;
    }

    void insertToList(CacheEntry *prev, CacheEntry *next) {
        if (prev)
            prev->m_next = this;
        if (next)
            next->m_prev = this;

        m_prev = prev;
        m_next = next;
    }

    int         key;
    int         value;
    CacheEntry* m_prev;
    CacheEntry* m_next;
};

class LRUCache{
public:
    LRUCache(int capacity):
        CAP(capacity)
    {
        m_oldest = new CacheEntry(-1);
        m_newest = new CacheEntry(-1);
        m_oldest->m_next = m_newest;
        m_newest->m_prev = m_oldest;
    }
    
    ~LRUCache() {
        if (m_oldest)
            delete m_oldest;
        if (m_newest)
            delete m_newest;
    }

    int get(int key) {
        int ret = -1;
        if (m_hash.count(key) > 0) {
            auto& entry = m_hash[key];
            ret = entry.value;
            entry.removeFromList();
            entry.insertToList(m_newest->m_prev, m_newest);
        }
        return ret;
    }
    
    void set(int key, int value) {
        m_hash[key].key   = key;
        m_hash[key].value = value;
        m_hash[key].removeFromList();
        m_hash[key].insertToList(m_newest->m_prev, m_newest);
        if (m_hash.size() > CAP) {
            m_hash.erase(m_oldest->m_next->key);
            m_oldest->m_next->removeFromList();
        }
    }

private:
    const int CAP;
    CacheEntry *m_oldest;
    CacheEntry *m_newest;
    unordered_map<int, CacheEntry> m_hash;
};

int main() {
    LRUCache lc(2);
    return 0;
}
