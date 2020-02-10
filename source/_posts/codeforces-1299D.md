---
title: codeforces 1299D
tags:
  - OI
  - codeforces
  - 线性基
  - DP
  - dfs
date: 2020-02-10 14:11:23
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/1299/problem/D)

<center>我现在越来越菜了，想题+写题就花了40分钟还要花半小时卡常。</center>

对于把1号点删去后的图，考虑每一个连通块。每个连通块只会有1个或2个点和1号点相连。对于每一个连通块，暴力枚举最终结果里删了那些边，并求出此时从1号点走进来绕一圈可以异或出什么数。

然后就可以转移了，记录$f_{i,j}$表示考虑了前$i$个连通块，能表示的状态为$j$（一个线性基）时删边的方案数。其中大小为5的线性基只有374个。转移时枚举当前连通块的删边情况，转移到的状态为两个线性基合并的结果。

但直接这么写是会T的，还有进行一些优化：给每个线性基标一个号，预处理两个线性基合并的结果。

时间复杂度$O(nS(V)+S(V)^2V^2)$，其中$S(V)$表示线性基个数，$V$表示线性基大小。

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
const int N = 101000,mod = 1e9+7;
int n,m,tag[N],fw[N],cnt,in[N],d[N],g[400][400];
struct edge{int v,w;};
vector<edge> e[N];
vector<int> C;
vector<pair<int,int> > P;
struct Lbase{
	int tag;
	int b[5];
	Lbase (){
		tag=0;
		memset(b,0,sizeof(b));
	}
	void insert(int x){
		for(int i=4;~i;i--)
			if(x>>i&1){
				if(!b[i]){
					b[i]=x;
					for(int j=i-1;~j;j--)
						if(b[j]&&b[i]>>j&1) b[i]^=b[j];
					for(int j=i+1;j<5;j++)
						if(b[j]&&b[j]>>i&1) b[j]^=b[i];
					return;
				}
				else x^=b[i];
			}
		tag=1;
	}
	bool chk(int x){
		for(int i=4;~i;i--)
			if(x>>i&1){
				if(!b[i]) return 0;
				x^=b[i];
			}
		return 1;
	}
}b[N][4];
void dfs(int x,int dad,Lbase&B,int w){
	if(dad==1){
		for(int p:C) in[p]=0;
		C.clear();
	}
	in[x]=1;d[x]=w;
	C.push_back(x);
	for(auto v:e[x]) if(v.v!=dad&&v.v!=1){
		if(in[v.v]){
			if(v.v<x) B.insert(d[x]^d[v.v]^v.w);
		}
		else dfs(v.v,x,B,w^v.w);
	}
}
int main(){
	read(n);read(m);
	for(int i=1;i<=m;i++){
		int x,y,z;read(x);read(y);read(z);
		if(x>y) swap(x,y);
		e[x].push_back({y,z});
		e[y].push_back({x,z});
		if(x==1) tag[y]=1,fw[y]=z;
	}
	for(int i=1;i<=n;i++)
		if(tag[i]){
			int flag=0;
			for(edge v:e[i])
				if(tag[v.v]){
					flag=1;
					if(v.v<i) P.emplace_back(v.v,i);
					break;
				}
			if(!flag) P.emplace_back(i,0);
		}
	for(auto pr:P){
		++cnt;
		if(pr.second){
			dfs(pr.first,1,b[cnt][0],fw[pr.first]);
			int w=0;
			for(edge v:e[pr.first])
				if(v.v==pr.second) w=v.w;
			b[cnt][0].insert(w^fw[pr.first]^fw[pr.second]);
			dfs(pr.first,1,b[cnt][1],fw[pr.first]);
			dfs(pr.second,1,b[cnt][2],fw[pr.second]);
		}
		else{
			dfs(pr.first,1,b[cnt][0],fw[pr.first]);
			b[cnt][2].tag=b[cnt][3].tag=1;
		}
	}
	unordered_set<unsigned> S,nx;
	unordered_map<unsigned,int> id;
	S.insert(1);nx.insert(1);
	for(int i=1;i<32;i++){
		for(auto x:S){
			unsigned p=0;
			for(int j=0;j<32;j++)
				if(x>>j&1) p|=1u<<(j^i);
			nx.insert(p|x);
		}
		S=nx;
	}
	int tim1=0,tim2=0;
	for(auto x:S) id[x]=++tim2;
	for(auto x:S){
		++tim1;tim2=0;
		for(auto y:S){
			++tim2;
			unsigned res=0,flag=0;
			for(int i=0;i<32;i++)
				for(int j=0;j<32;j++)
					if(x>>i&1&&y>>j&1){
						if(res>>(i^j)&1) flag=1;
						res|=1u<<(i^j);
					}
			if(!flag) g[tim1][tim2]=id[res];
		}
	}
	int now[400],nxt[400];
	memset(now,0,sizeof(now));
	now[id[1]]=1;
	for(int i=1;i<=cnt;i++){
		int D[4];
		for(int x:{0,1,2,3}){
			if(b[i][x].tag) continue;
			unsigned res=0;
			for(int j=0;j<32;j++)
				if(b[i][x].chk(j)) res|=1u<<j;
			D[x]=id[res];
		}
		memset(nxt,0,sizeof(nxt));
		for(int j=1;j<=id.size();j++){
			for(int x=0;x<4;x++)
				if(!b[i][x].tag&&g[j][D[x]]) (nxt[g[j][D[x]]]+=now[j])%=mod;
		}
		memcpy(now,nxt,sizeof(now));
	}
	ll ans=0;
	for(int i=1;i<=id.size();i++)
		ans=(ans+now[i])%mod;
	cout<<ans<<'\n';
	return 0;
}
```

