#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Node.h"

#include <utility>
#include <string>
#include <list>
#include <vector>
#include <functional>
using namespace std;

#define INITIAL_CAPACITY 16 // defined at compile at (more efficient)


class HashTable
{
private:
    std::vector<std::list<Node> > buckets;
    size_t currentSize;
    size_t capacity;

    int getIndex(const string &key);

public:
    HashTable(size_t capacity = INITIAL_CAPACITY);
    void insert(const string &key, const int &value);
    pair<string, int> find(const string &key);
};

#endif // HASHTABLE_H