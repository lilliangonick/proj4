#ifndef NODE_H
#define NODE_H

#include <utility>
#include <string>

using namespace std;

class Node
{
private:
    pair<string, int> data;
public:
    Node(const string &key, const int &value); 
    pair<string, int> getPair();
};

#endif // NODE_H