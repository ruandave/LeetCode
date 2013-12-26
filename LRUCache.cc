#include <iostream>
#include <unordered_map>
#include <climits>

using namespace std;

// Problem description: 
// http://oj.leetcode.com/problems/lru-cache/
// Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
// get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
// set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

class LRUCache
{
    public:
        // Hash (mapping "keys" to the ListNode ptr) + doubly-linked list (for recording access order)
        // Insert: O(1)
        // Delete: O(1)
        // Access: O(1)
        // Space: O(#keys)
        explicit LRUCache(int capacity) 
        {
            cap = capacity;
            cur_cap = 0;
            head = new ListNode(INT_MIN, INT_MIN); //psuedo node
            tail = new ListNode(INT_MAX, INT_MAX); //psuedo node
            head->next = tail;
            tail->prev = head;
            cache.clear();
        }
        int get(int key) 
        {
            if(cache.find(key) == cache.end())
                return -1;
            else
            {
                delNode(cache[key]); // LRU: delete and add to tail
                addToTail(cache[key]);
                return cache[key]->val;
            }
        }
        void set(int key, int value) 
        {
            if(cache.find(key) != cache.end()) // key found
            {
                cache[key]->val = value;
                delNode(cache[key]); // LRU: delete and add to tail
                addToTail(cache[key]); 
            }
            else
            {
                if(cur_cap >= cap) // exceeding the max. cap
                {
                    int tmp = head->next->key;
                    delNode(head->next);
                    delete cache[tmp];
                    cache.erase(tmp);
                }
                else
                    cur_cap++;

                ListNode *tmp = new ListNode(key, value);
                cache[key] = tmp;
                addToTail(cache[key]);
            }
        }
        void debug()
        {
            //unordered_map<ListNode *>::iterator it;
            for(ListNode *tmp = head->next; tmp != tail; tmp = tmp->next)
                cout << "Key: " << tmp->key << ", Val: " << tmp->val << "\n"; 
        }
    private:
        struct ListNode
        {
            int key;
            int val;
            ListNode *prev;
            ListNode *next;
            ListNode(int k, int x)
            {
                key = k;
                val = x;
                prev = next = NULL;
            }
        };

        int cap;
        int cur_cap;
        unordered_map<int, ListNode *> cache;
        ListNode *head; //oldest cache access
        ListNode *tail; //latest cache access

        void delNode(ListNode *t)
        {
            t->prev->next = t->next;
            t->next->prev = t->prev;
        }
        void addToTail(ListNode *t)
        {
            tail->prev->next = t;
            t->prev = tail->prev;
            t->next = tail;
            tail->prev = t;
        }
};

int main(int argc, char* argv[])
{
    // Small testbench.
    LRUCache c(2);
    c.set(1,1);
    c.set(2,2);
    c.set(3,3);
    c.get(3); 
    c.get(2);
    c.set(5,5); 
    c.debug();
    return 1;
}
