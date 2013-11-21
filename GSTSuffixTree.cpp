#include "GSTSuffixTree.h"
#include <stdint.h> 
#include "str_function.h"
namespace Seg
{
GST::GST()
{
    lastid = 0;
    root = new TreeNode();
    activeleaf = root;
}

GST::~GST()
{
}
/*
void GST::put(char * onestr,int index)
{
	if(index < lastid)
		return;
	else
		lastid = index;

	activeleaf = root;
	char * remainder = onestr;
	TreeNode * s = root;
	edgepair text;
	text=make_pair(remainder,0);
	//string text = "";
	for (int i = 1; i <=int(strlen(remainder));i++)
	{
		char tempc = remainder[i-1];
		//char * text = remainder;
		text.second+=1;
		//text = make_pair(remainder,i);
		//text += tempc;
		Node2edge active = update(*s,text,remainder+i-1,index);
		//remainder+i-1为剩余后缀
		active = canonize(*active.first,active.second);
		s = active.first;
		text = active.second;
	}

	if (NULL == activeleaf->getsuffix() && activeleaf != root && activeleaf != s)
		activeleaf->setsuffix(*s);

}

*/
void GST::put1(bool if_utf8,string str,int index)
{
	if(index < lastid)
		return;
	else
		lastid = index;

	activeleaf = root;
	vector<uint16_t>line;
	bool ifok=strTovec(if_utf8,str,line);

	//char * remainder = onestr;
	TreeNode * s = root;
	//edgepair text;
	edgepair1 text1;
	//text=make_pair(remainder,0);
	text1=make_pair(line,0);
	//string text = "";
	vector<uint16_t>::iterator it=line.begin();
	for (;it!=line.end();++it)
	{
		//char tempc = remainder[i-1];
		uint16_t temp=*it;
		//char * text = remainder;
		text1.second+=1;
		//text = make_pair(remainder,i);
		//text += tempc;
		
        //取后缀
		vector<uint16_t> last;
		last.assign(it,line.end());

		Node2edge active = update1(if_utf8,*s,text1,last,index);
		//remainder+i-1为剩余后缀
		active = canonize(*active.first,active.second);
		s = active.first;
		text1 = active.second;
	}

	if (NULL == activeleaf->getsuffix() && activeleaf != root && activeleaf != s)
		activeleaf->setsuffix(*s);

}

Node2edge GST::update1(bool if_utf8,TreeNode & inputnode,edgepair1 text1,vector<uint16_t>vec,int value)
{
	TreeNode * s = &inputnode;
	//char newchar = text1.first[text.second-1];
	uint16_t newint=text1.first[text1.second-1];

	//char newchar = text.at(text.length()-1);

	TreeNode * oldroot = root;
	edgepair1 textsub;
	textsub = make_pair(text1.first,text1.second-1);
	//string textsub = text.substr(0,text.length()-1);
	bool2node ret = testAndSplit1(if_utf8,*s,textsub,newint,vec,value);
	TreeNode * r = ret.second;
	bool endpoint = ret.first;

	TreeNode * leaf = NULL;

	while(!endpoint)
	{
		TreeEdge * tempEdge = r->getEdge(newint);
		if(NULL != tempEdge)
		{
			leaf = tempEdge->dest;
		}
		else
		{
			leaf = new TreeNode();
			leaf->addRef(value);
			int remainlen = vec.size();
			TreeEdge * newedge = new TreeEdge(vec,remainlen,*leaf,value);
			r->addEdge(newint,*newedge);
		}

		if (activeleaf != root)
		{
			activeleaf->setsuffix(*leaf);
		}

		activeleaf = leaf;

		if (oldroot != root)
		{
			oldroot->setsuffix(*r);    
		}
		oldroot = r;
		//这里没有用assert！！
		//if (NULL == s->getsuffix())
		//edgepair newpair;
		if (NULL == s->getsuffix() && s == root)
		{
			//text1.first = text1.first+1;

			//text1.first.assign(text1.first.begin()+1,text1.first.end());
			vector<uint16_t>tempq;
			tempq.assign(text1.first.begin()+1,text1.first.end());

			text1.second = text1.second-1;
			text1.first=tempq;
			//char * newstart = text.first +1;
			//int newlenth = text.second-1;

			//newpair = make_pair(newstart,newlenth);
		}
		else
		{
			Node2edge canret = canonize(*(s->getsuffix()),safecutlastchar(text1));
			s = canret.first;
			text1.first = canret.second.first;

			//text1.first.assign(canret.second.first.begin(),text1.first.end());
			text1.second = canret.second.second +1;
			//int newlenth = canret.second+1;
			//edgepair newpair;
			//newpair = make_pair(canret.first,newlenth);

		}

		//line 7
		ret = testAndSplit1(if_utf8,*s,safecutlastchar(text1),newint,vec,value);
		r = ret.second;
		endpoint = ret.first;
	}

	//line 8
	if(oldroot != root)
	{
		oldroot->setsuffix(*r);
	}
	oldroot = root;


	Node2edge returnvalue;
	returnvalue = make_pair(s,text1);
	return returnvalue;

}

//////////////////////////////////////////////////////////////////////////////////////////////////

/*
Node2edge GST::update(TreeNode & inputnode,edgepair &text,char * remain,int value)
{
    TreeNode * s = &inputnode;
	char newchar = text.first[text.second-1];
    //char newchar = text.at(text.length()-1);
	//c
    TreeNode * oldroot = root;
	edgepair textsub;
	textsub = make_pair(text.first,text.second-1);
    //string textsub = text.substr(0,text.length()-1);(cacaocacao,0)
    bool2node ret = testAndSplit(*s,textsub,newchar,remain,value);
    TreeNode * r = ret.second;
    bool endpoint = ret.first;

    TreeNode * leaf = NULL;

    while(!endpoint)
    {
        TreeEdge * tempEdge = r->getEdge(newchar);
        if(NULL != tempEdge)
        {
            leaf = tempEdge->dest;
        }
        else
        {
            leaf = new TreeNode();
            leaf->addRef(value);
            int remainlen = strlen(remain);
            TreeEdge * newedge = new TreeEdge(remain,remainlen,*leaf,value);
            r->addEdge(newchar,*newedge);
        }

        if (activeleaf != root)
        {
            activeleaf->setsuffix(*leaf);
        }

        activeleaf = leaf;

        if (oldroot != root)
        {
            oldroot->setsuffix(*r);    
        }
        oldroot = r;
        //这里没有用assert！！
        //if (NULL == s->getsuffix())
		//edgepair newpair;
		if (NULL == s->getsuffix() && s == root)
		{
			text.first = text.first+1;
			text.second = text.second-1;

			//char * newstart = text.first +1;
			//int newlenth = text.second-1;
			
			//newpair = make_pair(newstart,newlenth);
		}
		else
		{
			Node2edge canret = canonize(*(s->getsuffix()),safecutlastchar(text));
			s = canret.first;
			text.first = canret.second.first;
			text.second = canret.second.second +1;
			//int newlenth = canret.second+1;
			//edgepair newpair;
			//newpair = make_pair(canret.first,newlenth);
			
		}
		
         //line 7
        ret = testAndSplit(*s,safecutlastchar(text),newchar,remain,value);
        r = ret.second;
        endpoint = ret.first;
    }

        //line 8
    if(oldroot != root)
    {
        oldroot->setsuffix(*r);
    }
    oldroot = root;

        
    Node2edge returnvalue;
    returnvalue = make_pair(s,text);
    return returnvalue;
   
}
*/


edgepair1 GST::safecutlastchar(edgepair1 ep)
{
    if(ep.second == 0)
        return ep;
	else
		ep.second = ep.second-1;
    return ep;
}
Node2edge GST::canonize(TreeNode & s,edgepair1 inputedgepair)
{
	if(0 == inputedgepair.second)
    {
        Node2edge newpair;
		newpair = make_pair(&s,inputedgepair);
        return newpair;
    }
    else
    {
        TreeNode * currentNode = &s;
		//string allstr = inputedgepair.first;
		vector<uint16_t>newstart = inputedgepair.first;
		int newlenth = inputedgepair.second;
		//string str(allstr,inputedgepair.second);
		TreeEdge * g = s.getEdge(newstart[0]);
        while(g != NULL && g->lenth <= newlenth)
        {
            //str = str.substr(g->GetLabel().length());
			//newstart=newstart+g->lenth;
			vector<uint16_t>temp2;
			temp2.assign(newstart.begin()+g->lenth,newstart.end());
			newstart=temp2;
			//newstart.assign(newstart.begin()+g->lenth,newstart.end());
			
			newlenth = newlenth-g->lenth;
            currentNode = g->dest;
            if (newlenth>0)
            {
                g = currentNode->getEdge(newstart[0]);
            }
        }
		edgepair1 newedgepair;
		newedgepair = make_pair(newstart,newlenth);
        Node2edge newpair;
        newpair = make_pair(currentNode,newedgepair);
        return newpair;

    }
}

bool GST::startwith(string a,string b)
{
    bool startw = a.compare(0,b.length(),b) == 0;
    return startw;
}
/*
bool2node GST::testAndSplit(TreeNode & input,edgepair & strpart,char t,char * remainder,int value)
{
    Node2edge ret = canonize(input,strpart);
    TreeNode * s = ret.first;
	char * newstart = ret.second.first;
	//cacaocacao
	int newlenth = ret.second.second;

    //string str = ret.second;
    if(newlenth > 0)
    {
        TreeEdge * g = s->getEdge(newstart[0]);
        //string label = g->GetLabel();
        if(g->lenth > newlenth &&  g->start[newlenth] == t)
        {
            bool2node retvalue;
            retvalue = make_pair(true,s);
            return retvalue;
        }
        else
        {
			char * newlabel = g->start+newlenth;
			TreeNode * r =  new TreeNode();
			TreeEdge * newedge = new TreeEdge(newstart,newlenth,*r,value);
			g->lenth =g->lenth-newlenth;
			g->start +=newlenth;
			r->addEdge(newlabel[0],*g);
			s->addEdge(newstart[0],*newedge);
			bool2node retvalue;
			retvalue = make_pair(false,r);
			return retvalue;
        }
    }
	else
	{
		TreeEdge * e = s->getEdge(t);
		if (NULL == e)
		{
			bool2node retvalue;
			retvalue = make_pair(false,s);
			return retvalue;
		}
		else
		{
			string Remainder = remainder;
			string Elabelall = e->start;
			string Elabel(Elabelall,0,e->lenth);
			if (Remainder == Elabel)
			{
				e->dest->addRef(value);
				bool2node retvalue;
				retvalue = make_pair(true,s);
				return retvalue;
			}
			else if (startwith(Remainder,Elabel))
			{
				bool2node retvalue;
				retvalue = make_pair(true,s);
				return retvalue;
			}
			else if (startwith(Elabel,Remainder))
			{
				TreeNode * newNode = new TreeNode();
				newNode->addRef(value);

				TreeEdge * newEdge = new TreeEdge(remainder,strlen(remainder),*newNode,value);
				e->start+=strlen(remainder);
				e->lenth -= strlen(remainder);
				newNode->addEdge(e->start[0],*e);
				s->addEdge(t,*newEdge);

				bool2node retvalue;
				retvalue = make_pair(false,s);//?
				return retvalue;
			}

			else
			{
				bool2node retvalue;
				retvalue = make_pair(true,s);
				return retvalue;
			}
						
			

		}
		

	}
}
*/	
bool2node GST::testAndSplit1(bool if_utf8,TreeNode & input,edgepair1  strpart,uint16_t t,vector<uint16_t>vec,int value)
{
	Node2edge ret = canonize(input,strpart);
	TreeNode * s = ret.first;
	vector<uint16_t>newstart = ret.second.first;
	//cacaocacao
	int newlenth = ret.second.second;

	//string str = ret.second;
	if(newlenth > 0)
	{
		TreeEdge * g = s->getEdge(newstart[0]);
		//string label = g->GetLabel();
		if(NULL!=g)
		{
			if((g->lenth > newlenth) &&( g->start[newlenth] == t))
			{
				bool2node retvalue;
				retvalue = make_pair(true,s);
				return retvalue;
			}
			else
			{
				//char * newlabel = g->start+newlenth;
				vector<uint16_t>newlabel;
				newlabel.assign(g->start.begin()+newlenth,g->start.end());

				TreeNode * r =  new TreeNode();
				TreeEdge * newedge = new TreeEdge(newstart,newlenth,*r,value);
				g->lenth =g->lenth-newlenth;
				//g->start +=newlenth;


				vector<uint16_t>temp3;
				temp3.assign(g->start.begin()+newlenth,g->start.end());
				//g->start.assign(g->start.begin()+newlenth,g->start.end());
				g->start=temp3;
				r->addEdge(newlabel[0],*g);
				s->addEdge(newstart[0],*newedge);
				bool2node retvalue;
				retvalue = make_pair(false,r);
				return retvalue;
			}
		}
	
	}
	else
	{
		TreeEdge * e = s->getEdge(t);
		if (NULL == e)
		{
			bool2node retvalue;
			retvalue = make_pair(false,s);
			return retvalue;
		}
		else
		{
			vector<uint16_t>Remainder = vec;
			//string Elabelall = e->start;
			vector<uint16_t>Elabelall= e->start;
			//string Elabel(Elabelall,0,e->lenth);
			vector<uint16_t>Elabel;
			Elabel.assign(Elabelall.begin(),Elabelall.begin()+e->lenth);
			if (Remainder == Elabel)
			{
				e->dest->addRef(value);
				bool2node retvalue;
				retvalue = make_pair(true,s);
				return retvalue;
			}
			else if (startwith(vecTostr( if_utf8,Remainder,0,Remainder.size()),vecTostr( if_utf8,Elabel,0,Elabel.size())))
			{
				bool2node retvalue;
				retvalue = make_pair(true,s);
				return retvalue;
			}
			else if (startwith(vecTostr( if_utf8,Elabel,0,Elabel.size()),vecTostr( if_utf8,Remainder,0,Remainder.size())))
			{
				TreeNode * newNode = new TreeNode();
				newNode->addRef(value);

				TreeEdge * newEdge = new TreeEdge(vec,vec.size(),*newNode,value);
				//e->start+=strlen(remainder);
				vector<uint16_t>temp4;
				temp4.assign(e->start.begin()+vec.size(),e->start.end());
				e->start=temp4;

				//e->start.assign(e->start.begin()+vec.size(),e->start.end());
				e->lenth -= vec.size();
				newNode->addEdge(e->start[0],*e);
				s->addEdge(t,*newEdge);

				bool2node retvalue;
				retvalue = make_pair(false,s);//?
				return retvalue;
			}

			else
			{
				bool2node retvalue;
				retvalue = make_pair(true,s);
				return retvalue;
			}



		}


	}
}
/****加入父串信息****/
bool GST::GetFreqWord(bool if_utf8)
{
	//TreeNode * currentnode = root;

	vector<string> vecstr;
	string str="";
	vecstr.push_back(str);
	int iii=0;
	queue<TreeNode *> nodeQueue;
	nodeQueue.push(root);
	TreeNode * currentnode;
	while(!nodeQueue.empty())
	{
		currentnode = nodeQueue.front();
		nodeQueue.pop();
		charToEdge::iterator cit;
		cit = currentnode->edges->values.begin();
		//string tstr=vecToGbk(cit->second->start,0,cit->second->lenth);
		for (cit = currentnode->edges->values.begin();cit != currentnode->edges->values.end();++cit)
		{   
			string tstr=vecTostr( if_utf8,cit->second->start,0,cit->second->lenth);
			string astr=vecstr[iii]+tstr;
			vecstr.push_back(astr);
			alledges.push(cit->second);
		    //这里加入父串信息

			nodeQueue.push(cit->second->dest);
		}
		iii++;		
	}
	TreeEdge * currentedge;
	TreeNode * tempnode;
	int y=1;
	while (!alledges.empty())
	{    //int y=1;
		currentedge = alledges.front();
		//string label = currentedge->start;
		vector<uint16_t>label = currentedge->start;
		//string newlabel(label,0,currentedge->lenth);
		vector<uint16_t>newlabel;
		newlabel.assign(label.begin(),label.begin()+currentedge->lenth);
		tempnode = currentedge->dest;
		alledges.pop();
		//str2freq::iterator fit = m_candidateWord.find(vecToGbk(newlabel,0,newlabel.size()));
		
		str2freq::iterator fit = m_candidateWord.find(vecstr[y]);
		if (fit == m_candidateWord.end())
		{
			//m_candidateWord[vecToGbk(newlabel,0,newlabel.size())] = StasticNode(tempnode);
			m_candidateWord[vecstr[y]] = StasticNode(tempnode);
			//这里需要改进，加上父串
			y++;
		}
        //这里就不能有ELSE
		//StasticNode(tempnode);
		//y++;
	}
	
	return true;
}
/*****加入父串信息**/


W_INT GST::StasticNode(TreeNode * node)
{
	W_INT count;
	count.first=0;
	count.second=node->edges->values.size();
	stack<TreeNode *> nodestack;
	nodestack.push(node);
	TreeNode * tempnode;
	while (!nodestack.empty())
	{
		tempnode = nodestack.top();
		int i = tempnode->data.size();
		count.first += i;
		nodestack.pop();
		charToEdge::iterator cit;
		for (cit = tempnode->edges->values.begin();cit != tempnode->edges->values.end();++cit)
		{
		
			//tempnode = cit->second->dest;
			//alledges.push(cit->second);
			//nodeQueue.push(cit->second->dest);
			nodestack.push(cit->second->dest);
		}

	}
	return count;
	
}

}
