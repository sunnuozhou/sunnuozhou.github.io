---
title: ACM ICPC Northeastern European Regional Contest 2013 D题
tags:
  - OI
  - codeforces
  - 最小树形图
date: 2020-11-19 13:15:33
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100307)

考虑对所有前缀建点，跑最小树形图。首先一个点如果跟在原有前缀后面，那么连一条1权边，如果一个点是另一个前缀的后缀，连一条0权边。

可以发现最小树形图就是答案。

考虑求方案，dfs这些点，如果连父亲的是1权边，就新建一个点，否则就不建。

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
const int N = 10001000;
struct edge{int u,v,w,U,V,id;}e[N/10];
int n,lst[510],id[510],in[510],pre[510],tot,m,chs[510],vis[510],p[51][15],len[51],used[N],hs[510],deg[N],aeg[N];
char c[51][15],ch[510];
void add(int x,int y,int z){
//	cerr<<x<<' '<<y<<' '<<z<<'\n';
	++m;
	e[m]={x,y,z,x,y,m};
}
void solve(int n){
	for(int i=1;i<=n;i++) lst[i]=0,id[i]=i;
	int d=m;
	while(1){
		for(int i=1;i<=n;i++) in[i]=1e9,pre[i]=0,hs[i]=0;
		for(int i=1;i<=m;i++){
			int u=e[i].U,v=e[i].V;
			if(e[i].w<in[v]&&u!=v) in[v]=e[i].w,pre[v]=u,hs[v]=e[i].id;
		}
		memset(vis,0,sizeof(vis));
		memset(id,0,sizeof(id));
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(pre[i]) used[hs[i]]++;
			if(!vis[i]){
				int flag=0,x;
				for(x=i;x;x=pre[x]){
					if(vis[x]){flag=vis[x]==i;break;}
					vis[x]=i;
				}
				if(flag){
					id[x]=++cnt;
					for(int y=pre[x];y!=x;y=pre[y]) id[y]=cnt;
				}
			}
		}
		if(!cnt) break;
		for(int i=1;i<=n;i++)
			if(!id[i]) id[i]=++cnt;
		for(int i=1;i<=m;i++){
			e[i].w-=in[e[i].V];
			int p=hs[e[i].V];
			e[i].U=id[e[i].U];
			e[i].V=id[e[i].V];
			if(e[i].U!=e[i].V){
				deg[++d]=p;
				aeg[d]=e[i].id;
				e[i].id=d;
			}
		}
	//	cerr<<"**************\n";
	//	for(int i=1;i<=n;i++) cerr<<id[i]<<' ';cerr<<'\n';
	//	for(int i=1;i<=tot;i++) cerr<<i<<' '<<lst[i]<<'\n';
		n=cnt;
	}
	for(int i=d;i>m;i--)
		if(used[i]) used[deg[i]]--,used[aeg[i]]++;
	for(int i=1;i<=m;i++)
		if(used[i]) lst[e[i].v]=e[i].u;  
}
vector<pair<int,char> > ans;
int main(){
	freopen("dictionary.in","r",stdin);
	freopen("dictionary.out","w",stdout);
	read(n);
	tot=1;
	for(int i=1;i<=n;i++){
		cin>>c[i];len[i]=strlen(c[i]);
		for(int j=0;j<len[i];j++)
			p[i][j]=++tot;
		for(int j=1;j<len[i];j++)
			add(p[i][j-1],p[i][j],1),chs[p[i][j]]=p[i][j-1];
		add(1,p[i][0],1);chs[p[i][0]]=1;
		for(int j=0;j<len[i];j++) ch[p[i][j]]=c[i][j];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			for(int l1=0;l1<len[i];l1++)
				for(int l2=l1;l2<len[j];l2++){
					int flag=1;
					for(int k=0;flag&&k<=l1;k++)
						flag&=c[i][k]==c[j][k+l2-l1];
					if(flag) add(p[j][l2],p[i][l1],0);
				}
		}
	solve(tot);
	int cnt=0;
	memset(id,0,sizeof(id));
	memset(vis,0,sizeof(vis));
	id[1]=++cnt;
	vector<int> E[510];
	for(int i=2;i<=tot;i++)
		E[lst[i]].push_back(i);
	queue<int> q;q.push(1);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:E[u]){
			if(lst[v]==chs[v]) id[v]=++cnt,ans.emplace_back(id[u],ch[v]);
			else id[v]=id[u];
			q.push(v);
		}
	}
	cout<<ans.size()+1<<'\n';
	cout<<0<<'\n';
	for(auto&pr:ans) cout<<pr.first<<' '<<pr.second<<'\n';
//	for(int i=1;i<=tot;i++) cerr<<i<<' '<<lst[i]<<'\n';
	return 0;
}


```

