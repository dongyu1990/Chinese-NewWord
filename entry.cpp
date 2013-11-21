#include "entry.h"
#include <iostream>	// for getline
#include <fstream>
#include <string>
#include<ctime>
#include <sstream>
#include <string>
#include <vector>
#include "Trie.h"
#include "SegHMM.h"
#include "Interface.h"
#include<ctime>
#include <stdint.h>
using namespace std;
namespace Seg
{

	string segment(unsigned int Type,bool if_utf8,string str)
	{   
		switch(Type)

		{	
		case 1:
		{


			Trie mytree;
			const char * filePath="jieba.dict.gbk";
			bool OK=Seg::Loaddict(mytree,if_utf8,filePath);
			if(false==OK)
			{
				cout<<"loaddict error";
			}
			return Seg::segement(if_utf8,mytree,str);

		}
		case 2:
			{
				vector<string> res;
				HMMSeg hmm;
				ReSeg reviseSeg;
				cout<<"before load hmm :"; printtime();
				loadModel("hmm_model.utf8",hmm);
				cout<<"after load hmm :"; printtime();
				Trie mytree;   
				cout<<"before load dic :"; printtime();  
				bool OK=Seg::Loaddict(mytree,1,"jieba.dict.utf8");
				cout<<"after load dic :"; printtime();
				if(OK)
				{
					trim(str);
					if(str.size()!=0) //bo str_segementutf8tohmm内部没有进行空串的检测
					{
						reviseSeg = str_segementutf8tohmm(if_utf8,mytree,str);
						return segregate(if_utf8,hmm,reviseSeg);
					}

				}


			}
		}


	}

}
