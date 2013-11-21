#ifndef GSTSUFFIXTREE_H
#define GSTSUFFIXTREE_H

//#include<cstdlib>
#include <iostream>
#include "GSTNode.h"
#include <utility>
#include <stdint.h> 
#include <cstring>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include "GSTEdges.h"

using namespace std;
namespace Seg
{


//typedef pair<char *,int> edgepair;
typedef pair<vector<uint16_t>,int> edgepair1;
typedef pair<TreeNode *,edgepair1> Node2edge;
typedef pair<bool,TreeNode *> bool2node;
typedef pair<int,int>W_INT;
typedef map<string,W_INT> str2freq;
typedef queue<TreeEdge *> TreeEdgeQueue;
 
class GST
{
private:
    int lastid;
    TreeNode * root;
    TreeNode * activeleaf;

public:
	str2freq m_candidateWord;
	TreeEdgeQueue alledges;

public:
    GST();
    ~GST();
    //add one of the strings
   // void put(char *,int index);
	void put1(bool if_utf8,string str,int index);
    //update method
//    Node2edge update(TreeNode &,edgepair &,char *,int);

	Node2edge update1(bool if_utf8,TreeNode& ,edgepair1,vector<uint16_t>,int);
    Node2edge canonize(TreeNode&,edgepair1);
    bool2node testAndSplit(TreeNode&,edgepair1 ,uint16_t,vector<uint16_t>,int);
	bool2node testAndSplit1(bool if_utf8,TreeNode& input,edgepair1 strpart,uint16_t t,vector<uint16_t>vec,int value);
    edgepair1 safecutlastchar(edgepair1);
    bool startwith(string,string); 
	bool GetFreqWord(bool if_utf8);
	W_INT StasticNode(TreeNode *);

	
};
}
#endif