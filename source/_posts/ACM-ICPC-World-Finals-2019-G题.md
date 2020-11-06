---
title: ACM ICPC World Finals 2019 G题
tags:
  - OI
  - codeforces
  - AC自动机
  - 字符串
date: 2020-11-04 11:49:14
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102511/problem/G)

将姓名建成AC自动机，求出fail树的子树和 $sum$，那么对于一个询问 $S$，记其反串在AC自动机上的位置为 $w$，那么答案就是 $sum_w$。

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
const int N = 2001000;
int n,k;
char s[N];
struct Trie{
	int ch[N][26],s[N],fl[N],tot,w[N];
	int Q[N];
	void insert(int dad,int tmp,int id){
		dad=w[dad];
		if(!ch[dad][tmp]) ch[dad][tmp]=++tot;
		w[id]=ch[dad][tmp];s[w[id]]++;
	}
	void query(char *s,int len,int id){
		int now=0;
		for(int i=0;i<len;i++){
			int tmp=s[i]-'A';
			if(!ch[now][tmp]) ch[now][tmp]=++tot;
			now=ch[now][tmp];
		}
		Q[id]=now;
	}
	void solve(){
		queue<int> q;
		for(int i=0;i<26;i++)
			if(ch[0][i]) q.push(ch[0][i]);
		vector<int> V;
		while(!q.empty()){
			int u=q.front();q.pop();
			V.push_back(u);
			for(int i=0;i<26;i++)
				if(!ch[u][i]) ch[u][i]=ch[fl[u]][i];
				else{
					fl[ch[u][i]]=ch[fl[u]][i];
					q.push(ch[u][i]);
				}
		}
		reverse(V.begin(),V.end());
		for(int&x:V) s[fl[x]]+=s[x];
	}
}T;
int main(){
	read(n);read(k);
	for(int i=1;i<=n;i++){
		char c;int fa;scanf(" %c",&c);read(fa);
		T.insert(fa,c-'A',i);
	}
	for(int i=1;i<=k;i++){
		scanf(" %s",s);
		int len=strlen(s);
		reverse(s,s+len);
		T.query(s,len,i);
	}
	T.solve();
	for(int i=1;i<=k;i++) cout<<T.s[T.Q[i]]<<'\n';
	return 0;
}

```

