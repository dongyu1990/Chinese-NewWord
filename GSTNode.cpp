#include "GSTNode.h"
namespace Seg
{


TreeNode::TreeNode()
{
    lastIdx = 0;
    resultCount = 0;
    suffix = NULL;
	edges = new EdgeBag();
}

TreeNode::~TreeNode()
{
}

void TreeNode::addRef(int index)
{
	if (contains(index))
	{
		return;
	}
	
    addidx(index);
    TreeNode * iter = suffix;
    while(iter != NULL)
    {
        if (iter->contains(index))
        {
            break;
        }
        iter->addRef(index);
        iter = iter->suffix;
    }
}

bool TreeNode::contains(int id)
{
    intvec::iterator it = find(data.begin(),data.end(),id);
    if(it == data.end())
        return false;
    else
        return true;
}

void TreeNode::addEdge(uint16_t ch,TreeEdge &e)
{
    edges->put(ch,e);
}

TreeEdge * TreeNode::getEdge(uint16_t ch)
{
    return edges->get(ch);
}
void TreeNode::setsuffix(TreeNode & node)
{
    suffix = &node;
}

void TreeNode::addidx(int index)
{
    data.push_back(index);
}
TreeNode * TreeNode::getsuffix()
{
    return suffix;
}
}