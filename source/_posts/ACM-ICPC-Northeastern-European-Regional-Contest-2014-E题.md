---
title: ACM ICPC Northeastern European Regional Contest 2014 E题
tags:
  - OI
  - codeforces
  - dfs
  - 构造
date: 2020-11-18 11:00:47
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100553)

考虑对手可能在的节点，记该集合为 $v$，如果集合内的点出的东西一样，那么我方的节点就出能赢它的，否则随便出。然后按 $v$ 中每个节点出的东西，将后继节点变成3份，分别递归处理。

如果集合内的点出的东西一直一样，那么就可以赢了，如果不一样，那么这个集合就一定会被分裂。

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
map<vector<int>,int> mp;
struct machine{
	int n,e[N][3],typ[N];
	void init(){
		read(n);
		for(int i=1;i<=n;i++){
			char c;scanf(" %c",&c);
			read(e[i][0]);read(e[i][1]);read(e[i][2]);
			typ[i]=c=='R'?0:(c=='P'?1:2);
		}
	}
	void print(){
		printf("%d\n",n);
		for(int i=1;i<=n;i++){
			printf("%c %d %d %d\n","RPS"[typ[i]],e[i][0],e[i][1],e[i][2]);
		}
	}
	int nxt(int x,int k){return e[x][k];}
}M1,M2;
int win(int k){return (k+1)%3;}
int dfs(vector<int> v){
	if(v.empty()) return 1;
	if(mp.count(v)) return mp[v];
	mp[v]=++M2.n;
	int x=M2.n;
	M2.typ[x]=win(M1.typ[v[0]]);
	vector<int> nxt[3];
	for(int p:v) nxt[M1.typ[p]].push_back(M1.nxt(p,M2.typ[x]));
	for(int i=0;i<3;i++)
		M2.e[x][i]=dfs(nxt[i]);
	return x;
}
int main(){
	freopen("epic.in","r",stdin);
	freopen("epic.out","w",stdout);
	M1.init();
	vector<int> now;
	for(int i=1;i<=M1.n;i++)
		now.push_back(i);
	dfs(now);
	M2.print();
	return 0;
}


```

