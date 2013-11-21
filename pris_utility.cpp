//#include "StdAfx.h"
#include "pris_utility.h"
#include <string>
//using std::string;


namespace pris
{

	using namespace std;  // it's ok to do this in .cpp file


	/*****************************
	功能: 去除string前后的空白字符
	说明: 空白字符包括'\n''\t'' '
	*****************************/
	string& strip(string &s)
	{
		string::size_type beg, end;
		string::size_type length = s.size();
		for(beg=0; isspace(s[beg])&&beg!=length; ++beg);

		if(beg == length) 
		{
			s.clear();
			return s;
		}

		for(end=beg; !isspace(s[end])&&end!=length; ++end);

		s = s.substr(beg, end-beg);
		return s;
	}

	/**************************
	功能: int整型转string
	**************************/
	string itos(int n)
	{
		string s;
		int sign = 0;
		if( (sign=n) < 0)
			n = -n;
		do
		{
			s.push_back(n%10 + '0');
		}while((n/=10) > 0);

		if(sign < 0) s.push_back('-');

		string::size_type i = 0, j = s.size()-1;
		char c;
		for(; i<j; ++i, --j)
		{
			c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
		return s;
	}

	/**************************
	功能: long整型转string
	**************************/
	string ltos(long n)
	{
		return tos(n);
	}

	/******************************
	功能: string转int
	说明: 基于模板函数ston(...)实现
	******************************/
	int stoi(const string &s)
	{
		return ston<int>(s);
	}
    float stof(const string &s)
    {
        float f;
        f = atof(s.c_str());
        return f;
    }
	/******************************
	功能: string转long
	说明: 基于模板函数ston(...)实现
	******************************/
	long stol(const string &s)
	{
		return ston<long>(s);
	}
	
	/******************************
	功能: Cstring转String
	说明: 
	******************************/
	/*
	string CStr2Str(CString cstr)
	{  
		char *chr=new char[cstr.GetLength()];
		WideCharToMultiByte(CP_ACP,0,cstr.GetBuffer(),-1,chr,cstr.GetLength(),NULL,NULL);
		string str = chr;
		return str;
	}
	*/

//	string CStr2Str(CString cstr)
//	{  
//		string str(cstr.GetBuffer());
//		cstr.ReleaseBuffer();
//		return str;
//	}

	/******************************
	功能: String转CString
	说明: 
	******************************/
//	CString Str2CStr(string str)
//	{
//		
//		CString cstr=str.c_str();
//		return cstr;
//	}
	/******************************
	功能: String转char*
	说明: 
	******************************/
	char * Str2Char(string str)
	{
		const char * cpcr = str.c_str();
        int lenth = strlen(cpcr);
		char * pcr = new char[strlen(cpcr) + 1];
		strcpy(pcr,cpcr);
		return pcr;

	}
	/******************************
	功能: CString转int
	说明: 
	******************************/
//	int CStr2int(CString str)
//	{
//		int i=_ttoi(str);
//		return i;
//	}
}
