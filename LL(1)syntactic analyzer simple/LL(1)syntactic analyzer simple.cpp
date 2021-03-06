// LL(1)syntactic analyzer simple.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<stack>
#include<iomanip>
using namespace std;

char vn[10];            //非终结符号
char vt[10];            //终结符号
int num;                //产生式条数
int numvn = 1;              //非终结符号数
int numvt = 1;              //终结符号数
string grammar[100];      //产生式
int table[100][100];      //预测分析表
string sentence;          //句子

int if_vt(char c)       //判定终结符
{
	for (int i = 1; i < numvt; i++)
	{
		if (c == vt[i])
			return i;
	}
	return 0;
}

int if_vn(char c)       //判定终结符
{
	for (int i = 1; i < numvn; i++)
	{
		if (c == vn[i])
			return i;
	}
	return 0;
}

void init()
{
	int i = 1, j = 1;
	char c;
	/*cout << "输入文法条数:";
	cin >> num;*/
	cout << "输入所有终结符:";
	while ((c = getchar()) != '@')         //输入到*结束输入
	{
		if (c >= 33 && c <= 127)
		{
			numvt++;
			vt[i] = c;
			i++;
		}
	}
	vt[i] = '#';
	numvt++;
	//mv['$'] = i;      //空
	//vt[i] = '$';
	//cout << numvt << endl;
	//cout << mv['Q'];
	cout << "输入所有非终结符:";
	while ((c = getchar()) != '@')
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			numvn++;
			vn[j] = c;
			j++;
		}
	}
	/*map<char, int>::iterator iter;
	for (iter = mv.begin(); iter != mv.end(); iter++) {
	cout << iter->first << " : " << iter->second << endl;
	}*/
	/*for (i = 0; i < numvn; i++)
	cout << vn[i];*/
	cout << "输入产生式条数:";
	cin >> num;
	cout << "输入对应产生式:" << endl;
	for (i = 0; i < num; i++)
		cin >> grammar[i];
	cout << numvn << endl;
	cout << numvt << endl;
	cout << "输入预测分析表:" << endl;
	for (i = 1; i < numvn; i++)
	{
		for (j = 1; j < numvt; j++)
		{
			cin >> table[i][j];
		}
	}
	/*for (i = 1; i < numvn; i++)
		cout << vn[i] << " ";
	cout << endl;
	for (j = 1; j < numvt; j++)
		cout << vt[j] << " ";
	cout << endl;
	for (i = 0; i < num; i++)
		cout << grammar[i]<<endl;*/
	cout << setiosflags(ios::left);
	cout << setw(10) << " ";
	for (i = 1; i < numvt; i++)
		cout << setw(10) << vt[i] << " ";
	cout << endl;
	for (i = 1; i < numvn; i++)
	{
		cout << setw(10) << vn[i];
		for (j = 1; j < numvt; j++)
		{
			if (table[i][j] != 100)
				cout << setw(10) << grammar[table[i][j]];
			else if (table[i][j] == 100)
				cout << setw(10) <<" ";
		}
		cout << endl;
	}
	/*string s;
	for (i = 0; i < num; i++)
	{
		s = grammar[i][0];
		for (int j = 3; j < grammar[i].length(); j++)
		{
			if (grammar[i][j] == '|')
			{
				vg.push_back(s);
				s.clear();
				s = grammar[i][0];
			}
			else
			{
				s = s + grammar[i][j];
			}
		}
		vg.push_back(s);
	}*/
	/*for (int j = 0; j < vg.size(); j++)
	{
	cout << vg[j] << " ";
	}
	cout << endl;*/
	//cout << numvn << endl;
}

void analyze()
{
	cout << "请输入要分析的句子:";
	cin >> sentence;
	sentence = sentence + '#';
	stack<char> st;
	st.push('#');
	st.push(vn[1]);
	int i = 0;
	while (!st.empty())
	{
		char c = st.top();
		cout << c << " " << sentence[i] << endl;
		cout << if_vn(c) << endl;
		if (if_vt(c) && sentence[i] != '#')    //如果是终结符号
		{
			if (sentence[i] == c)    //匹配
			{
				st.pop();
				i++;
			}
			else
			{
				cout << "!!!";
				cout << "不是这个文法的句子" << endl;
				break;
			}
		}
		else if (if_vn(c))    //如果是非终结符
		{
			if (table[if_vn(c)][if_vt(sentence[i])] != 100)      //找到该产生式
			{
				cout << grammar[table[if_vn(c)][if_vt(sentence[i])]] << endl;
				if (grammar[table[if_vn(c)][if_vt(sentence[i])]][grammar[table[if_vn(c)][if_vt(sentence[i])]].size() - 1] == '$')
				{
					st.pop();
				}
				else
				{
					//cout << table[mv[c]][mv[sentence[i]]] << endl;
					st.pop();
					for (int j = grammar[table[if_vn(c)][if_vt(sentence[i])]].size() - 1; j >= 3; j--)   //逆序存入栈
					{
						//cout << vg[table[mv[c]][mv[sentence[i]]]];
						st.push(grammar[table[if_vn(c)][if_vt(sentence[i])]][j]);
					}
				}
			}
			/*else if (vg[table[mv[c]][mv[sentence[i]]]][1] == '$')
			{
				st.pop();
			}*/
			else if (table[if_vn(c)][if_vt(sentence[i])] == 100)     //无产生式，出错
			{
				cout << "没有该产生式";
				cout << "不是这个文法的句子" << endl;
				break;
			}
		}
		else if (sentence[i] == '#')      //分析成功
		{
			cout << "是这个文法的句子" << endl;
			break;
		}
		else
		{
			cout << "分析错误";
			cout << "不是这个文法的句子" << endl;
			break;
		}
	}
}

int main()
{
	init();
	analyze();
	system("pause");
    return 0;
}

