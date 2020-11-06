---
title: ACM ICPC World Finals 2016 F题
tags:
  - OI
  - codeforces
  - dfs
date: 2020-10-28 12:26:16
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101242)

先考虑暴力，对于一条河 $x$，一定是每个 $x$ 的祖先都选 $x$，其他点如果儿子长度都不超过 $x$ 的长度，就选最短的，不然选最长的。

考虑从长到短枚举河流（比较最长长度），记录每个节点往父亲流的河长度为 $g_i$，按 $g_i$ 排序，每次把 $g_i>len_x$ 的 $i$ 变为选最长就可以了，时间复杂度 $O(n\log n)$。

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
const int N = 1001000;
int n,m,fa[N],fw[N],c[N],p[N],q[N],dfn[N],s[N],sum,vis[N],tag[N],tim,ans[N];
ll dep[N],g[N];
vector<int> e[N];
string Name[N];
void modify(int x,int tag){
	sum+=tag;
	for(int i=dfn[x];i<=n+m;i+=i&-i) c[i]+=tag;
	for(int i=dfn[x]+s[x];i<=n+m;i+=i&-i) c[i]-=tag;
}
int query(int x){
	int ans=0;
	for(int i=dfn[x];i;i-=i&-i) ans+=c[i];
	return ans;
}
void dfs(int x){
	ll mn=1e18;
	dfn[x]=++tim;
	for(int v:e[x]) dep[v]=dep[x]+fw[v],dfs(v),mn=min(mn,g[v]),s[x]++;
	if(mn>1e17) mn=0;
	g[x]=mn+fw[x];
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>Name[i]>>fa[i]>>fw[i];
		if(fa[i]) fa[i]+=n;
		e[fa[i]].push_back(i);
	}
	for(int i=1;i<=m;i++){
		cin>>fa[n+i]>>fw[n+i];
		if(fa[i+n]) fa[n+i]+=n;
		e[fa[i+n]].push_back(i+n);
	}
	dfs(0);
	for(int i=1;i<=n;i++) p[i]=i;
	sort(p+1,p+n+1,[&](int a,int b){return dep[a]>dep[b];});
	for(int i=1;i<=n+m;i++) q[i]=i;
	sort(q+1,q+n+m+1,[&](int a,int b){return g[a]>g[b];});
	int k=1;
	for(int i=1;i<=n;i++){
		while(k<=n+m&&g[q[k]]>dep[p[i]]){
			int x=q[k++];
			if(vis[x]) continue;
			modify(x,1);tag[x]=1;
			while(x&&!vis[x]) vis[x]=1,x=fa[x];
			if(x&&tag[x]) modify(x,-1),tag[x]=0;
		}
		ans[p[i]]=sum-query(p[i])+1;
	}
	for(int i=1;i<=n;i++)
		cout<<Name[i]<<' '<<ans[i]<<'\n';
	return 0;
}
```

