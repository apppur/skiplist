#include <string>
#include <fstream>
#include "SkipNode.h"
#include "SkipList.h"

using namespace std;

int main (int argc, char** argv)
{
    string* max = new string("Z9999");
    SkipList<string, Node>* skiplist_p = new SkipList<string, Node> ((float)0.5, 4, max);
    string* akey = new string("Y8792");
    Node* anode = new Node;
    skiplist_p->Insert(akey, anode);
    string* bkey = new string("X8888");
    Node* bnode = new Node;
    skiplist_p->Insert(bkey, bnode);
    string* ckey = new string("A2888");
    Node* cnode = new Node;
    skiplist_p->Insert(ckey, cnode);

    ofstream ofs("test.txt", std::ofstream::out);
    skiplist_p->Dump(ofs);
    skiplist_p->Dump();

    return 0;
}
