---
title: ACM ICPC Northeastern European Regional Contest 2014 H题
tags:
  - OI
  - codeforces
  - DP
date: 2020-11-18 11:00:49
categories: 解题报告
top:

---

[题目链接](https://codeforces.com/gym/100553)

先考虑对一条边求答案，将边权大于它的边权值变为1，小于等于它的变为-1，记录 $f_{i,j}$ 表示 $i$ 号点，子树内路径边权值和为 $j$ 的点的个数。

如果一个以 $x$ 为LCA的路径 $(u,v)$ 包含这条边，并且 $f_{x,val_u}+f_{x,val_v}=-1$，那么这条路径就是可行的。

注意到如果按照边权排序后，每次DP数组的修改是很少的，直接修改DP数组并重新计算答案即可。

我本来一个这个做法的复杂度是 $O(n\log^2n)$，但听说好像是 $O(n\sqrt n)$ 的。

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
const int N = 31000;
int _f[N][1010],*f[N],mx[N],DEP[2],fw[N],fa[N],n,VAL;
ll ans;
map<int,int> mp;
vector<int> e[N];
struct node{int x,y,w;};
vector<node> V;
void dfs(int x,int dad,int dep=0){
	DEP[dep&1]++;
	mx[x]=0;fa[x]=dad;
	for(int v:e[x]) if(v!=dad){
		dfs(v,x,dep+1);mx[x]=max(mx[x],mx[v]+1);
		for(int i=-mx[v];i<=mx[v];i++)
			f[x][i+fw[v]]+=f[v][i];
	}
	f[x][0]++;
}
void get_son(int x,int dep){
	mp[dep]++;
	for(int v:e[x]) if(v!=fa[x]) get_son(v,dep+fw[v]);
}
void update(int x,int del){
	for(auto&pr:mp){
		f[x][pr.first+del+2]-=pr.second;
		f[x][pr.first+del]+=pr.second;
	}
	for(auto&pr:mp){
		ans+=1ll*f[x][-1-(pr.first+del)]*pr.second*VAL;
		if(fa[x]) ans-=1ll*f[x][-1-2*fw[x]-(pr.first+del)]*pr.second*VAL;
	}
	if(fa[x]) update(fa[x],del+fw[x]);
}
int main(){
	freopen("hidden.in","r",stdin);
	freopen("hidden.out","w",stdout);
	read(n);
	for(int i=1;i<n;i++){
		int x,y,z;read(x);read(y);read(z);
		e[x].push_back(y);
		e[y].push_back(x);
		V.push_back(node{x,y,z});
	}
	for(int i=1;i<=n;i++) f[i]=_f[i]+500,fw[i]=1;
	dfs(1,0);
	sort(V.begin(),V.end(),[](node a,node b){return a.w<b.w;});
	for(auto P:V){
		if(fa[P.y]==P.x) swap(P.x,P.y);
		VAL=P.w;
		fw[P.x]=-1;
		mp.clear();
		get_son(P.x,0);
		for(auto&pr:mp) ans-=1ll*f[P.x][-1-2*fw[P.x]-pr.first]*pr.second*VAL;
		update(P.y,-1);
	//	cerr<<P.x<<' '<<P.y<<' '<<P.w<<' '<<ans<<'\n';
	}
	printf("%.12lf\n",1.*ans/DEP[0]/DEP[1]);
	return 0;
}


```



