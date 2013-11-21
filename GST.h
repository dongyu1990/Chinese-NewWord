#include <iostream>
#include "TreeData.h"
#include "GSTSuffixTree.h"
#include "str_function.h"
#include "pris_utility.h"
#include "TreeData.h"
#include <fstream>
#include <sstream>
#include "Type.h"
using namespace std;
namespace Seg
{

	WordList GetWordList(bool if_utf8, const char * const filePath);

	bool cmpstr(const pair<string,winf1> x,const pair<string,winf1> y);
	str_vector getallsonstr(bool if_utf8,string str);
	wordlist1 GetnewWord(bool if_utf8, const char * const dictPath);

}