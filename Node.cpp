#include "Node.h"

Node::Node(const string &key, const int &value) : data(key, value) {}

pair<string, int> Node::getPair() {
    return data;
}