#include "GSTEdges.h"
#include"GSTNode.h"
namespace Seg
{


EdgeBag::EdgeBag()
{
    BSTH = 6;
}
EdgeBag::~EdgeBag()
{
}
void EdgeBag::put(uint16_t c,TreeEdge & e)
{
    charToEdge::iterator it = values.find(c);
    if (it == values.end())
    {
        //chars.push_back(c);
        //here need to consider again!!
        //values.push_back(&e);
		values[c] = &e;
    }
    else
    {
        it->second = &e;
    }
}

//think again!

TreeEdge * EdgeBag::get(uint16_t c)
{
    charToEdge::iterator it = values.find(c);
    if(it == values.end())
    {
        return NULL;
    }
    else
    {
        return it->second;
    }

}


}