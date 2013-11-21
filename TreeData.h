#ifndef TREEDATA_H
#define TREEDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "pris_utility.h"

using namespace std;
/* use char ** to denote the strings that in the GST*/
namespace Seg
{


class CTreeData
{
private:
    vector<char *> m_Pdatas;

public:
    int m_nstringnum;

public:
    /* use a file to initialize the class*/
    CTreeData(char *);
    ~CTreeData();

    /*********************************************
    read the file to generate strings,only use simple 
     only use the simply way for fast develop 
     to be continue..
     *********************************************/
    bool InitTreeData(char *);

    /*********************************************
    return the ith string in the m_Pdatas
    *********************************************/
    char * Getstring(int);




};
}
#endif