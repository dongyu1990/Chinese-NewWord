#include <iostream>
#include "TreeData.h"
#include "GSTSuffixTree.h"
#include "str_function.h"
#include "pris_utility.h"
#include "TreeData.h"
#include "Trie.h"
#include "function.h"
#include <fstream>
#include <sstream>
#include "GST.h"
#include <fstream>
#include <sstream>
#include "Type.h"
#include <stdint.h> 
using namespace std;
namespace Seg
{
bool cmpstr(const pair<string,winf1>& x,const pair<string,winf1>& y)
{
	return x.first.size()>y.first.size();		;
}
str_vector getallsonstr(bool if_utf8,string str)
{
	str_vector vec;
	Unicode vecint;
	if(str.size()<=4)
	{
		return vec;
	}
	bool ok=strTovec(if_utf8,str,vecint);
	if((0==ok)||(vecint.size()<=2))
	{
		return vec;
	}
	for(int i=0;i<vecint.size();++i)
	{
		int j=i;
		while(j+1<vecint.size())
		{
			string temp=vecTostr(if_utf8,vecint,i,j+2);
			if((0==i)&&(vecint.size()==j+2))
				break;;
			vec.push_back(temp);
			j++;
		}

	}
	return vec;
	
}
string CharReverse(bool if_utf8,string p)
{
  vector<uint16_t>temp;
  bool ifok=strTovec(if_utf8,p,temp);
  if(false==ifok)
  {   
	  cout<<p<<endl;
	  cout<<"error3";
  }
  vector<uint16_t>temp3;
  for(int i=temp.size();i>0;--i)
  {
	  temp3.push_back(temp[i-1]);
  }
  

  string restr=vecTostr(if_utf8,temp3,0,temp3.size());
  return restr;
}

WordList GetWordList(bool if_utf8, const char * const filePath)
{   
	WordList reWlist;
	ifstream dict("E:\\labotery\\gaolunwen\\dicts\\wordsfre.txt");
	string line;
	vector<string> temp;
	TrieNodeInfo nodeInfo;
	wfinfo wf;
	while(getline(dict, line))
	{
		temp.clear();
		//切分每一行
		Seg::split(line, temp);
		if(4 < temp.size())
		{
			cout<<"false"<<endl;
		}
		//切分每一行		
		wf.wordf=atoi(temp[1].c_str());
		wf.LeftCh=atoi(temp[2].c_str());
		wf.RightCh=atoi(temp[3].c_str());
		reWlist.insert(pair<string,wfinfo>(temp[0],wf));

	
	}          
	

    
	GST * gst_z = new GST();
	GST * gst_f = new GST();
	ifstream fout(filePath);
	int i=0;
	int linenum=0;
	string str;
	string str1;
	while((getline(fout, str))&&(linenum<2000))
	{  
		       gst_z->put1(if_utf8,str,i);
		       gst_f->put1(if_utf8,CharReverse(if_utf8,str),i);
		       i++;	
	        
		linenum++;
	}
	

	gst_z->GetFreqWord(if_utf8);
	gst_f->GetFreqWord(if_utf8);
	str2freq::iterator mit;
	
	for (mit = gst_z->m_candidateWord.begin();mit != gst_z->m_candidateWord.end();++mit)
	{
		
		if ((mit->second.first >1)&&(mit->second.second >1) && (mit->first.size()>2))//first词频 second 直接孩子数
		{
			//cout<<mit->first<<"    "<<mit->second.first<<endl;

			str2freq::iterator fit = gst_f->m_candidateWord.find(CharReverse(if_utf8,mit->first));
			if (fit != gst_f->m_candidateWord.end())
			{
				//cout<<mit->first<<"    "<<mit->second<<"    "<<fit->second<<"    "<<mit->first.length()<<endl;
				
				if(fit->second.first>1)
				{   
				   wfinfo temp;
				   temp.wordf=mit->second.first;
				   temp.RightCh=mit->second.second;
				   temp.LeftCh=fit->second.second;
				   ////////////////////////////////
				   if(reWlist.end()!=reWlist.find(mit->first))
				   {
					   WordList::iterator gt=reWlist.find(mit->first);
					   gt->second.wordf+=temp.wordf;
					   gt->second.LeftCh+=temp.LeftCh;
					   gt->second.RightCh+=temp.RightCh;

				   }
				   else
				   {
					   reWlist.insert(pair<string,wfinfo>(mit->first,temp));
				   }			   	 
					
				}
				
				
			}
			//WordList reWlist[mit->first]+=mit->second;
			
		}
				
	}
	
	cout<<"*************************************"<<"过滤前后"<<endl;

	ofstream fout1;
	fout1.open("E:\\labotery\\gaolunwen\\dicts\\wordsfrenew1.txt");
	for(map<string,wfinfo>::iterator it=reWlist.begin();it!=reWlist.end();++it)
	{
	
		stringstream ss;  
		ss<<it->second.wordf;  
		string w_str1=ss.str();
		ss.str("");
		ss<<it->second.LeftCh; 
		string w_str2=ss.str();
		ss.str("");
		ss<<it->second.RightCh; 
		string w_str3=ss.str();
		string temp=it->first+" "+w_str1+" "+w_str2+" "+w_str3+"\n";
		fout1<<temp;
		//cout<<vecToGbk(vec1,0,1)<<"    "<<it->second<<endl;

	}
	fout1.close();
	//cout<<namestr<<endl;

	return  reWlist;
}
wordlist1 GetnewWord(bool if_utf8, const char * const dictPath)
{
	ifstream endfre("E:\\labotery\\gaolunwen\\dicts\\jieba.dict.gbk");
	string line;
	vector<string>ttmp;
	map<string,int>endfretemp;
	while(getline(endfre, line))
	{

		//切分每一行
		ttmp.clear();
		Seg::split(line, ttmp);
		if(3 < ttmp.size())
		{
			cout<<"hehe6";
		}
		//切分每一行
		Unicode ttpp1;
		bool tr=strTovec(0,ttmp[0],ttpp1);
		if(false==tr)
		{
			cout<<"hehe4";
		}
		if(ttpp1.size()<2)
		{

		}
		else
		{
			string str=vecTostr(0,ttpp1,ttpp1.size()-1,ttpp1.size());
			++endfretemp[str];
		}
	}
	/*
	ofstream endlist;
	endlist.open("G:\\C++\\dicts\\endlist.txt");
	map<string,int>::iterator et=endfretemp.begin();
	for(;et!=endfretemp.end();++et)
	{

		stringstream ss;  
		ss<<et->second;  
		string w_str1=ss.str();
		ss.str("");
		string temp=et->first+" "+w_str1+"\n";
		//cout<<temp<<endl;
		endlist<<temp;
		//cout<<vecToGbk(vec1,0,1)<<"    "<<it->second<<endl;

	}
	endlist.close();
	*/








	/***********************词缀量词统计***************************/
	/*************分词测试******************************************************************/
	//string str ="陈光高去打球了,唐波在建湘路动不了";
	//cout<<Seg::segment(1,0,str)<<endl;;
	/*************分词测试******************************************************************/
	/*************新词发现******************************************************************/

	wordlist1 W;
	Trie mytree; 
	//const char * filePath="G:\\C++\\dicts\\jieba.dict.gbk";
	bool OK=Seg::Loaddict(mytree,0,dictPath);
	if(false==OK)
	{
		cout<<"hehe2"<<endl;
	}
	WordList D=Seg::GetWordList(0,"E:\\labotery\\gaolunwen\\dicts\\out.txt");
	WordList::iterator it=D.begin();
	for(;it!=D.end();++it)
	{
		winf1 temp;
		temp.f=geteverywordfre(0,mytree,it->first);
		temp.LeftCh=it->second.LeftCh;
		temp.RightCh=it->second.RightCh;
		temp.wordf=it->second.wordf;
		Unicode ed;
		ed.clear();
		bool edw=strTovec(0,it->first,ed);
		if(false==edw)
		{
			cout<<"hehe5";
		}
		if(endfretemp.end()==endfretemp.find(vecTostr(0,ed,0,1)))
		{
			temp.endfre=1;
		}
		else
		{
			map<string,int>::iterator endit=endfretemp.find(vecTostr(0,ed,0,1));
			temp.endfre=endit->second;
		}
		W.insert(pair<string,winf1>(it->first,temp));		
		//cout<<it->first<<"   "<<it->second.wordf<<"  "<<it->second.LeftCh<<" "<<it->second.RightCh<<endl;
	}

	//互斥串过滤
	//sort(W.begin(),W.end(),Seg::cmpstr);vector才能排序
	map<string,winf1>::iterator tp=W.begin();
	while(tp!=W.end())
	{  
		bool flg=false;
		str_vector tem=getallsonstr(0,tp->first);
		for(int ii=0;ii<tem.size();++ii)
		{   

			if(W.end()==W.find(tem[ii]))
			{

			}
			else
			{
				map<string,winf1>::iterator tpp=W.find(tem[ii]);
				if(tpp->second.wordf/tp->second.wordf>=6)
				{
					W.erase(tp++);
					flg=true;
					break;
				}

			}
		}
		if(false==flg)
		{
			tp++;
		}

	}
	//量词过滤
	map<string,winf1>::iterator qt=W.begin();
	while(qt!=W.end())
	{

		if(qt->first.size()<4)
		{
			qt++;
		}
		else
		{
			Unicode ttttpp;
			bool ttpt=strTovec(0,qt->first,ttttpp);
			string strtp=vecTostr(0,ttttpp,0,1);
			if(true==ifMeasureword(strtp))
			{
				W.erase(qt++);
			}
			else
			{
				qt++;
			}
		}

	}

	//量词过滤
	map<string,winf1>::iterator it1=W.begin();
	while(it1!=W.end())
	{   
		int freflg=0;
		if(it1->second.endfre<=100)
		{
			freflg=1;
		}
		else if((100<it1->second.endfre)&&(it1->second.endfre<=200))
		{
			freflg=2;
		}
		else if((200<it1->second.endfre)&&(it1->second.endfre<=400))
		{
			freflg=3;
		}
		else if((400<it1->second.endfre)&&(it1->second.endfre<=600))
		{
			freflg=5;
		}
		else
		{
			freflg=7;
		}
		TrieNodeInfo* p=mytree.find(0,it1->first);
		if(mytree.find(0,it1->first)!=NULL)
		{
			W.erase(it1++);
		}
		else if((it1->second.f>10000)||(it1->second.LeftCh+it1->second.RightCh<40)||(it1->second.LeftCh<8)||(it1->second.RightCh<8)||(it1->second.LeftCh/it1->second.RightCh>=3)||(it1->second.RightCh/it1->second.LeftCh>=3)||(it1->second.wordf/freflg<30))
		{
			W.erase(it1++);
		}
		else
		{
			++it1;
		}
	}
	ofstream fout2;
	fout2.open("E:\\labotery\\gaolunwen\\dicts\\newfinish1.txt");
	it1=W.begin();
	for(;it1!=W.end();++it1)
	{

		stringstream ss;  
		ss<<it1->second.wordf;  
		string w_str1=ss.str();
		ss.str("");
		ss<<it1->second.LeftCh; 
		string w_str2=ss.str();
		ss.str("");
		ss<<it1->second.RightCh; 
		string w_str3=ss.str();
		ss.str("");
		ss<<it1->second.f; 
		string w_str4=ss.str();
		ss.str("");
		ss<<it1->second.endfre; 
		string w_str5=ss.str();
		string temp=it1->first+" "+w_str1+" "+w_str2+" "+w_str3+" "+w_str4+" "+w_str5+"\n";
		//cout<<temp<<endl;
		fout2<<temp;
		//cout<<vecToGbk(vec1,0,1)<<"    "<<it->second<<endl;

	}
	fout2.close();
	return W;
}

}