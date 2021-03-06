#include<iostream>
#include<string>
#include <vector>
#include <sstream>
#include <iterator>
#include"Trie.h"
#include "function.h"
#include <stdlib.h>
using namespace std;
namespace Seg

{
	
	//using namespace pris;
Trie::Trie()
{
	root = NULL;
}
/*
Trie::~Trie()
{
	//dispose();
}	
*/
bool Trie::init()
{
	return true;
}


/////////////////////////////////////////////原有代码，在win7上运行速度较慢.../////
bool Trie::loadDict(bool if_utf8,const char * const filePath)//加载字典，读入字典 A const pointer to const data
{
	
	try
	{
		root = new TrieNode;
	}
	catch(const bad_alloc& e)
	{
		return false;
	}	
		
	//检查目录等等
	ifstream ifile(filePath);
	string line;
	vector<string> temp;

    TrieNodeInfo nodeInfo;
	while(getline(ifile, line))
	{
		temp.clear();
		//切分每一行
 		Seg::split(line, temp);
		if(3 < temp.size())
		{
			return false;
		}
		//切分每一行
		nodeInfo.word = temp[0];//读入词语
		nodeInfo.freq = atoi(temp[1].c_str());
		nodeInfo.wLen=nodeInfo.word.size()/2;	

		if(3 == temp.size())
		{
			nodeInfo.tag = temp[2];
		}	
		//insert node
		if(!insert(if_utf8,nodeInfo))
		{
			cout<<"insert error"<<endl;
		}
	}
	return true;
}
/////////////////////////////////////////////原有代码，在win7上运行速度较慢.../////












bool Trie::insert(bool if_utf8,TrieNodeInfo& nodeInfo)//插入节点
{ 
	const string& word = nodeInfo.word;//

	//拆分词语
	Unicode intVec;
	 bool retFlag;
	if(0==if_utf8)
	{
	  retFlag = Seg::gbkToVec(word, intVec);//将word读入intvec（B超----》66,-19540)
	}
	else
	{
	   retFlag = Seg::utf8ToVec(word, intVec);
	}
	
	//拆分词语	
	if(!retFlag)
	{
		cout<<"转码错误"<<endl;
		return false;
	}
	
	
	TrieNode* p =root;
	for(unsigned int i = 0; i < intVec.size(); i++)
	{
		uint16_t cu = intVec[i];//取得ASICLL码
		if(NULL == p)
		{
			return false;
		}
		if(p->node_map.end() == p->node_map.find(cu))//没有找到
		{
			TrieNode * next = NULL;
			next = new TrieNode;
			if(NULL == next)
			{
				return false;
			}

			p->if_Leaf = false;
			p->node_map[cu] = next;
			p = next;
			p->if_Leaf=true;

		}
		else
		{  
			p = p->node_map[cu];
		}
	}
	if(NULL == p)
	{
		return false;
	}

	node_infomation.push_back(nodeInfo);
	p->nodeInfo_pos = node_infomation.size() - 1;
	p->if_wors=true;
	return true;
}

bool Trie::deleteNode(TrieNode* node)
{   TrieNodeMap::iterator it;
    if(node->node_map.size()>0)
	{
		for( it= node->node_map.begin(); it != node->node_map.end(); it++)
		{
			//TrieNode* next = it->second;
			deleteNode(it->second);
		}
		if(root!=node)
		{
           
			delete node;
		}
		
	}

	return true;
}

 void Trie::dispose()
{  
	bool ret = deleteNode(root);
	if(!ret)
	{
		cout<<"deleteNode failed!"<<endl;
		//return false;
	}
	root = NULL;
	node_infomation.clear();
	//return ret;
}

/////////////////////////////////
// 查找词语，返回节点信息
TrieNodeInfo* Seg::Trie::find(bool if_utf8,string str)
{
	Unicode intVec;
	bool retFlag = Seg::strTovec(if_utf8,str, intVec);
	if(!retFlag)
	{
		return NULL;
	}
	//////按字查询////////////////
	if(intVec.empty())
	{
		return NULL;
	}
	
	Unicode::const_iterator begin=intVec.begin();
	Unicode::const_iterator end=intVec.end();
	if(begin >= end)
	{
		return NULL;
	}
	TrieNode* p = root;
	for(Unicode::const_iterator it = begin; it != end; it++)
	{
		uint16_t chUni = *it;
		if(p->node_map.find(chUni) == p->node_map.end())
		{
			return NULL;
		}
		else
		{
			p = p->node_map[chUni];
		}
	}
	if(p->if_wors==true)
	{
		int pos = p->nodeInfo_pos;
		if(pos < node_infomation.size())
		{
			return &(node_infomation[pos]);
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
	
   }
}



