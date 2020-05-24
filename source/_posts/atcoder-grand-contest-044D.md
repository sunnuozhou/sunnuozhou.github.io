---
title: atcoder grand contest 044D
tags:
  - OI
  - atcoder
  - 交互
date: 2020-05-24 17:23:21
categories: 解题报告
top:
---

[题目链接](https://atcoder.jp/contests/agc044/tasks/agc044_d)

对每一个字符 $c$ 询问一个长为128，字符全是 $c$ 的字符串，可以知道这个字符出现了几次。

记 $f(s)$，表示在 $S$ 中，所有字符都在字符集 $s$ 中的最长子序列是什么。

显然答案为 $f(\{a,b,\cdots,0,1,\cdots,Y,Z\})$。

我们现在已经得到了所有的 $f(\{c\})$，考虑如何合并答案。

观察到以下结论：

对于 $|T|\le |S|$，询问 $T$ 的结果是 $|S|-|T|$ 当且仅当 $T$ 是 $S$ 的子序列。

对于不相交的集合 $s1,s2$，可以从前往后依次枚举 $f(s2)$ 中的每一个字符在哪里，最坏要消耗 $|f(s1)|+|f(s2)|-1$ 次询问。

每次找两个长度最小的合并，总次数是 $L\log 62$ 级别的，实际最多要769次，可以通过此题。

<!--more-->

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lld long double
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 101000;
priority_queue<pair<int,string>,vector<pair<int,string> >,greater<pair<int,string> > > H;
vector<char> C;
int L;
int main(){
	for(int i=0;i<26;i++) C.push_back('a'+i);
	for(int i=0;i<26;i++) C.push_back('A'+i);
	for(int i=0;i<10;i++) C.push_back('0'+i);
	for(int i=0;i<62;i++){
		cout<<"? ";
		pair<int,string> pr;
		for(int j=0;j<128;j++)
			pr.second+=C[i];
		cout<<pr.second<<endl;
		int x;cin>>x;
		pr.first=128-x;
		for(int j=0;j<x;j++) pr.second.pop_back();
		if(pr.first) H.push(pr);
		L+=pr.first;
	}
	while(H.size()>1){
		auto p1=H.top();H.pop();
		auto p2=H.top();H.pop();
		string st;
		int k=0;
		for(int i=0;i<p1.first;i++){
			while(k<p2.first){
				string out=st;
				out+=p2.second[k];
				for(int j=i;j<p1.first;j++)
					out+=p1.second[j];
				cout<<"? "<<out<<endl;
				int x;cin>>x;
				if(L-x!=out.length()) break;
				else st+=p2.second[k++];
			}
			st+=p1.second[i];
		}
		while(k<p2.first) st+=p2.second[k++];
		H.push(make_pair(p1.first+p2.first,st));
	}
	cout<<"! "<<H.top().second<<endl;
	return 0;
}
```

