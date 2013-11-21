#ifndef GSTEDGES_H
#define GSTEDGES_H
#include <stdint.h> 
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "str_function.h"
using namespace std;
namespace Seg
{



//#include "GSTNode.h"
typedef vector<int> intvec;
//typedef vector<unsigned char> ucharvec;
//typedef vector<unsigned char *> pucharvec;

class TreeNode;
struct TreeEdge
{
    //the index of the strings
    int index;
    //the start position of the exact string
    vector<uint16_t>start;
    //lenth of the string
    int lenth;
    //the dest node 
    TreeNode * dest;

    TreeEdge(vector<uint16_t>vec,int remainlen,TreeNode & node,int value):start(vec),lenth(remainlen),dest(&node),index(value)
    {
    }
    inline void SetIndex(int ind)
    {
        index = ind;
    }
    inline void SetStart(vector<uint16_t>  p)
    {
        start = p;
    }
    inline void SetLength(int len)
    {
        lenth = len;
    }
    inline void SetDest(TreeNode & de)
    {
        dest = &de;
    }
    inline string GetLabel()
    {    
		string line=vecToGbk(start,0,start.size());
		 //string line = start;
        string newline(line,0,lenth);
        return newline;
    }
};

typedef vector<TreeEdge *> TEvec;
typedef map<uint16_t,TreeEdge *> charToEdge;

class EdgeBag
{
public:
    //ucharvec chars;
    //TEvec values;
    //the THRESHOLD of binary search
	charToEdge values;
    int BSTH;
public:
    EdgeBag();
    ~EdgeBag();
    void put(uint16_t c,TreeEdge &);
	//void put1(string str,int index);
	TreeEdge* get(uint16_t c);

};
}
#endif