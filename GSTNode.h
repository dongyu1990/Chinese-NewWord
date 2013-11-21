#ifndef GSTNODE_H
#define GSTNODE_H

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "GSTEdges.h"
#include <stdint.h> 
using namespace std;
namespace Seg
{


typedef vector<int> intvec;
typedef set<int> intset;
//typedef vector<unsigned char> ucharvec;
//typedef vector<unsigned char *> pucharvec;

class TreeNode
{
public:
    intvec data;
    int lastIdx;
    EdgeBag * edges;
    TreeNode * suffix;

    //don't know the exact meaning
    int resultCount;
public:
    TreeNode();
    ~TreeNode();
    void addRef(int);
    bool contains(int);
    void addEdge(uint16_t,TreeEdge &);
	TreeEdge* getEdge(uint16_t ch);
    void setsuffix(TreeNode &);
    TreeNode * getsuffix();
    void addidx(int);
};
}
#endif