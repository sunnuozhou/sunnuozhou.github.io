---
title: codeforces 521E
date: 2020-01-10 12:50:44
tags:
- OI
- codeforces
- 解题报告
- dfs
categories: 解题报告
---

[题目链接](https://codeforces.com/contest/521/problem/E)

求出一棵dfs树，如果题目有解，一定有一个解的起点和终点是祖先后代关系，并且3条路径中包含恰好2个返祖边。

对于一个点$x$，假设该点自身有$s1$条返祖边，有$s2$个儿子的子树中有返祖边连向$x$的祖先。

如果$s1+s2\ge2$，那么必有一个起点为$x$的解。

假设终点为$y$，第一条路径为一直走父亲边走到$y$，第二条路径为走若干条儿子边，再走一条到$y$的返祖边，第三条路径为若干条儿子边，再走一条到$y$的祖先的返祖边，最后走若干条儿子边到$y$。

直接实现即可，时间复杂度$O(n)$。

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
const int N = 201000;
int n,dep[N],f[N],fa[N],vis[N],m;
vector<int> e[N],p1[N],p2[N];
void find(int x,int pos,vector<int>&P){
	for(int v:p1[x]) if(dep[v]==pos){
		P.push_back(v);
		return;
	}
	for(int v:p2[x]) if(f[v]==f[x]){
		P.push_back(v);
		find(v,pos,P);
		return;
	}
}
void pushin(int x,int pos,vector<int>&P){
	if(pos==x) return;
	pushin(x,fa[pos],P);
	P.push_back(pos);
}
void print(vector<int>&v1,vector<int>&v2,vector<int>&v3){
	puts("YES");
	cout<<v1.size()<<' ';
	for(int x:v1) cout<<x<<' ';
	cout<<'\n';
	cout<<v2.size()<<' ';
	for(int x:v2) cout<<x<<' ';
	cout<<'\n';
	cout<<v3.size()<<' ';
	for(int x:v3) cout<<x<<' ';
	cout<<'\n';
	exit(0);
}
void dfs(int x,int dad){
	vis[x]=1;dep[x]=dep[dad]+1;fa[x]=dad;
	f[x]=dep[x];
	int flag=0,mn=dep[x];
	for(int v:e[x]){
		if(!flag&&v==dad){flag=1;continue;}
		if(vis[v]&&dep[v]>dep[x]) continue;
		if(vis[v]) f[x]=min(f[x],dep[v]),p1[x].push_back(v),mn=min(mn,dep[v]);
		else dfs(v,x),p2[x].push_back(v),f[x]=min(f[x],f[v]);
	}
	int s=0;
	for(int v:p2[x]) if(f[v]<dep[x]) s++;
	if(s>1){
		int k=2,mx=0;
		vector<int> v1,v2,v3;
		v1.push_back(x);
		v2.push_back(x);
		v3.push_back(x);
		for(int v:p2[x]) if(f[v]<dep[x]){
			k--;mx=max(mx,f[v]);
			if(v2.size()==1) v2.push_back(v);
			else v3.push_back(v);
			if(!k) break;
		}
		for(int y=fa[x];dep[y]>=mx;y=fa[y]) v1.push_back(y);
		find(v2.back(),f[v2.back()],v2);
		find(v3.back(),f[v3.back()],v3);
		if(dep[v2.back()]<dep[v3.back()]) pushin(v2.back(),v1.back(),v2);
		else pushin(v3.back(),v1.back(),v3);
		print(v1,v2,v3);
	}
	if(s==1&&mn<dep[x]){
		int mx=0;
		vector<int> v1,v2,v3;
		v1.push_back(x);
		v2.push_back(x);
		v3.push_back(x);
		mx=dep[p1[x].back()];
		v2.push_back(p1[x].back());
		for(int v:p2[x]) if(f[v]<dep[x]){
			mx=max(mx,f[v]);
			v3.push_back(v);
			break;
		}
		for(int y=fa[x];dep[y]>=mx;y=fa[y]) v1.push_back(y);
		find(v3.back(),f[v3.back()],v3);
		if(dep[v2.back()]<dep[v3.back()]) pushin(v2.back(),v1.back(),v2);
		else pushin(v3.back(),v1.back(),v3);
		print(v1,v2,v3);
	}
	s=0;
	for(int v:p1[x]) if(dep[v]<dep[x]) s++;
	if(s>=2){
		int k=2,mx=0;
		vector<int> v1,v2,v3;
		v1.push_back(x);
		v2.push_back(x);
		v3.push_back(x);
		for(int v:p1[x]) if(dep[v]<dep[x]){
			k--;mx=max(mx,dep[v]);
			if(v2.size()==1) v2.push_back(v);
			else v3.push_back(v);
			if(!k) break;
		}
		for(int y=fa[x];dep[y]>=mx;y=fa[y]) v1.push_back(y);
		if(dep[v2.back()]<dep[v3.back()]) pushin(v2.back(),v1.back(),v2);
		else pushin(v3.back(),v1.back(),v3);
		print(v1,v2,v3);
	}
}
int main(){
	read(n);read(m);
	for(int i=1;i<=m;i++){
		int x,y;read(x);read(y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]) dfs(i,0);
	puts("NO");
	return 0;
}


```

