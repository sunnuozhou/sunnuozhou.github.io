---
title: ACM ICPC Northeastern European Regional Contest 2015 D题
tags:
  - OI
  - codeforces
  - 分治
date: 2020-11-13 12:28:29
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100851)

可以证明一定有一个对角线把 $n$ 个点分为了少的一部分至少 $n/3$ 。

所以可以分治为 $O(\log n)$ 层，每次求出分割点到这块中每个点的最短路。

考虑求答案，如果询问的点在分割线同侧，递推那一侧，否则最短路一定经过分割点，直接输出即可。

时间复杂度 $O((n+q)\log n)$。

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
const int N = 51000;
int dis[50][2][N],lc[N*50],rc[N*50],fa[N*50],in[N];
pair<int,int> ed[N*50];
int n,cnt,SS;
vector<int> e[N];
int calc_sum(vector<pair<int,int> >&v,int l,int r){
	if(l>r) return calc_sum(v,l,n)+calc_sum(v,1,r);
	int ans=0;
	for(auto&pr:v)
		ans+=max(0,min(r,pr.second)-max(l,pr.first)+1);
	return ans;
}
void bfs(int x,int*b){
	queue<int> q;q.push(x);
	b[x]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		SS+=e[u].size();
		int nxt=u%n+1;
		if(in[nxt]&&b[nxt]>1e9) b[nxt]=b[u]+1,q.push(nxt);
		nxt=u-1==0?n:u-1;
		if(in[nxt]&&b[nxt]>1e9) b[nxt]=b[u]+1,q.push(nxt);
		for(int v:e[u])
			if(in[v]&&b[v]>1e9) b[v]=b[u]+1,q.push(v);
	}
}
int solve(vector<pair<int,int> >&v,int dep=0){
	int x=++cnt;
	//cerr<<"**********\n";
	//cerr<<x<<' '<<dep<<'\n';
	//for(auto&pr:v) cerr<<pr.first<<' '<<pr.second<<'\n';
	int mx=0,pos1=0,pos2=0,S=0;
	for(auto&pr:v)
		for(int i=pr.first;i<=pr.second;i++)
			in[i]=1;
	for(auto&pr:v)
		for(int i=pr.first;i<=pr.second;i++){
			for(int nx:e[i]){
				int s=min(calc_sum(v,i,nx),calc_sum(v,nx,i));
				if(s>mx) mx=s,pos1=i,pos2=nx; 
			}
		}
	if(pos1>pos2) swap(pos1,pos2);
	ed[x]=make_pair(pos1,pos2);
	for(int i=fa[x];i;i=fa[i]) dis[dep][0][ed[i].first]=dis[dep][0][ed[i].second]=2e9;
	for(int i=fa[x];i;i=fa[i]) dis[dep][1][ed[i].first]=dis[dep][1][ed[i].second]=2e9;
	SS=0;
	bfs(ed[x].first,dis[dep][0]);
	bfs(ed[x].second,dis[dep][1]);
	//cerr<<SS<<' '<<S<<' '<<dep<<'\n';
	if(mx<=2){
		for(auto&pr:v)
			for(int i=pr.first;i<=pr.second;i++)
				in[i]=0;
		return x;
	}
	vector<int> q1,q2;
	vector<pair<int,int> > v1,v2;
	vector<int> ed1=e[ed[fa[x]].first];
	vector<int> ed2=e[ed[fa[x]].second];
	//cerr<<ed[fa[x]].first<<' '<<ed[fa[x]].second<<'\n';
	e[ed[fa[x]].first].clear();
	e[ed[fa[x]].second].clear();
	for(int v:ed1) if(in[v]) e[ed[fa[x]].first].push_back(v);
	for(int v:ed2) if(in[v]) e[ed[fa[x]].second].push_back(v);
	for(auto&pr:v)
		for(int i=pr.first;i<=pr.second;i++){
			in[i]=0;
			if(ed[x].first<=i&&i<=ed[x].second) q1.push_back(i);
			if(ed[x].first>=i||i>=ed[x].second) q2.push_back(i);
		}
	for(int i=0,j=0;i<q1.size();i=++j){
		while(j+1<q1.size()&&q1[j+1]-q1[i]==j-i+1) j++;
		v1.emplace_back(q1[i],q1[j]);
	}
	for(int i=0,j=0;i<q2.size();i=++j){
		while(j+1<q2.size()&&q2[j+1]-q2[i]==j-i+1) j++;
		v2.emplace_back(q2[i],q2[j]);
	}
	fa[1+cnt]=x;
	lc[x]=solve(v1,dep+1);
	fa[1+cnt]=x;
	rc[x]=solve(v2,dep+1);
	e[ed[fa[x]].first]=ed1;
	e[ed[fa[x]].second]=ed2;
	return x;
}
int query(int now,int x,int y,int dep=0){
	if(ed[now].first==x) return dis[dep][0][y];
	if(ed[now].first==y) return dis[dep][0][x];
	if(ed[now].second==x) return dis[dep][1][y];
	if(ed[now].second==y) return dis[dep][1][x];
	int tg1=ed[now].first<=x&&x<=ed[now].second;
	int tg2=ed[now].first<=y&&y<=ed[now].second;
	if(tg1&&tg2) return query(lc[now],x,y,dep+1);
	if(!tg1&&!tg2) return query(rc[now],x,y,dep+1);
	return min(dis[dep][0][x]+dis[dep][0][y],dis[dep][1][x]+dis[dep][1][y]);
}
int main(){
	freopen("distance.in","r",stdin);
	freopen("distance.out","w",stdout);
	read(n);
	for(int i=1;i<=n-3;i++){
		int x,y;read(x);read(y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	memset(dis,63,sizeof(dis));
	vector<pair<int,int> > v;
	v.emplace_back(1,n);
	int rt=solve(v);
	int Q;read(Q);
	while(Q--){
		int x,y;read(x);read(y);
		if(abs(x-y)<2) cout<<abs(x-y)<<'\n';
		else{
			cout<<query(rt,x,y)<<'\n';
		}
	}
	return 0;
}


```

