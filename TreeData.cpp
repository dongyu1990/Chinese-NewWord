#include "TreeData.h"
#include "str_function.h"
namespace Seg
{



CTreeData:: CTreeData(char * filename)
{
    InitTreeData(filename);
}

CTreeData::~CTreeData()
{
}

bool CTreeData::InitTreeData(char * filename)
{
   ifstream fin(filename);
   string line;
   vector<string> pieces;
   while(getline(fin,line))
   {
       pieces.push_back(line);
   }

   m_nstringnum = pieces.size();
   int i = 0;
   vector<string>::iterator it;
   for(it = pieces.begin();it != pieces.end();++it)
   {
      int lenth = it->length();
      char * temp = new char[lenth+1];
      string tempstr = *it;
      char * transfer = Seg::Str2Char(tempstr);
      memcpy(temp,transfer,lenth);
      memset(temp+lenth,0,1);
      m_Pdatas.push_back(temp);
      i++;

   }

   return true;

}

char * CTreeData::Getstring(int i)
{
    if(i>m_nstringnum)
        return 0;
    else
    {
		char * newc = m_Pdatas[i-1];
        return newc;
    }
}
}