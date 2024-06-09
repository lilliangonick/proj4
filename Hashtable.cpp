#include "Hashtable.h"
#include "Node.h"
#include <iostream>

using namespace std;

HashTable::HashTable(size_t capacity) : capacity(capacity), currentSize(0)
{
    buckets.resize(capacity); // makes buckets the size of our capacity
}

int HashTable::getIndex(const string &key)
{
    hash<string> hasher;
    int hashValue = hasher(key);
    int index = hashValue % capacity; // put value into a specific bucket
    return index;
}

void HashTable::insert(const string &key, const int &value)
{
    int index = getIndex(key);

    // find the correct bucket and add to the list
    buckets[index].push_front(Node(key, value));
}

pair<string, int> HashTable::find(const string &key)
{
    int index = getIndex(key);
    list<Node> bucket = buckets[index];
    cout << bucket.size();
    // travese the list to find the value
    for (Node &node : bucket)
    {
        pair<string, int> bucketPair = node.getPair();
        cout << "first pair: " << bucketPair.first << " " << "second pair: " << bucketPair.second << endl;
        if (bucketPair.first == key)
        {
            return bucketPair;
        }
    }
    cerr << "Couldn't find value" << endl;
    return pair<string, int>("", -1); // returns a pair with "" and -1
}
