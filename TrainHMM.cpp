#include <iostream>	// for getline
#include <fstream>
#include <stdlib.h> // for exit(1)
#include "TrainHMM.h"
#include "str_function.h"
#define DELTA 0.001
namespace Seg
{
	void RawDicProcess(const char* const filePath)
	{
		ifstream ifile(filePath);//
		if(!ifile)
		{
			cout<<"open "<<filePath<<" error!"<<endl;
			exit(1); 
		}
		string line;
		while(!ifile.eof())
		{
			getline(ifile,line);
			if(strExtract(line))
			{
				cout<<line<<endl;
			}
			else
				continue;
			
		}
		


	}
}