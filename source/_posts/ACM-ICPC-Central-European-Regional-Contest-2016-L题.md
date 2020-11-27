---
title: ACM ICPC Central European Regional Contest 2016 L题
tags:
  - OI
  - codeforces
  - 构造
date: 2020-11-27 10:22:36
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101173)

记第二行相较于第一行变化的集合为 $S1$，记第三行相较于第一行变化的集合为 $S2$

如果 $S1\cap S2\neq \varnothing$ 并且 $S1 \cup S2\neq S1$，$S1\cup S2\neq S2$，那么无解。

否则如果 $S1\cap S2=\varnothing$，将 $S1$ 中的位置连成联通块，将 $S2$ 中的位置连成联通块，再让这两个集合互相排斥即可。

否则假设 $S1\subset S2$，将 $S1$ 中的位置连成联通块，将在 $S2$ 中不在 $S1$ 中的位置连成联通块，再将 $S2$ 连向 $S1$ 即可。

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
int n,a[3][110];
set<int> s1,s2;
vector<string> ANS;
void out(int x,int tg1,int y,int tg2){
	if(x==y&&tg1==tg2) return;
	string ans;
	ans+=tg1^a[0][x]?"x":"!x";
	ans+=to_string(x);
	ans+=" -> ";
	ans+=tg2^a[0][y]?"x":"!x";
	ans+=to_string(y);
	ANS.push_back(ans);
}
int main(){
	read(n);
	for(int k=0;k<3;k++)
	for(int i=1;i<=n;i++)
		read(a[k][i]);
	for(int i=1;i<=n;i++){
		if(a[1][i]^a[0][i]) s1.insert(i);
		if(a[2][i]^a[0][i]) s2.insert(i);
	}
	if(s1.size()>s2.size()) swap(a[1],a[2]),swap(s1,s2);
	int flag1=0,flag2=1;
	for(int x:s1)
		if(s2.count(x)) flag1=1;
		else flag2=0;
	if(flag1&&!flag2){cout<<-1<<'\n';return 0;}
	int X=*s1.begin(),Y;
	for(int x:s2) if(!s1.count(x)) Y=x;
	for(int i=1;i<=n;i++){
		if(!s2.count(i)&&!s1.count(i)) out(i,1,i,0);
		else if(s1.count(i)) out(X,1,i,1),out(i,1,X,1);
		else out(Y,1,i,1),out(i,1,Y,1);
	}
	if(flag2) out(Y,1,X,1);
	else out(X,1,Y,0),out(Y,1,X,0);
	cout<<ANS.size()<<'\n';
	for(auto&s:ANS) puts(s.data());
	return 0;
}


```

