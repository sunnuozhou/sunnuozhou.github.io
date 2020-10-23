---
title: ACM ICPC World Finals 2014 I题
tags:
  - OI
  - codeforces
  - 网络流
date: 2020-10-22 11:43:03
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101221)

枚举答案集合中相距最远的两个点 $A,B$，设这两个点之间的距离为 $D$，考虑其他的与这两个点距离都不超过 $D$ 的点，根据它在 $AB$ 的左右分类，同在一类中的点必不可能相距超过 $D$，所以可以建立二分图，距离超过 $D$ 的点对之间连边，用网络流求二分图最大独立集。

时间复杂度 $O(n^4\sqrt n)$。

强烈吐槽CF的编译器，`sqrt`的精度有问题，导致我本地一直拍不出错，但交上去就错。

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
struct point{
	int x,y;
	double len(){return sqrt(x*x+y*y);}
}p[110];
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
int operator * (point a,point b){return a.x*b.y-a.y*b.x;}
int n,D,tag[110];
vector<int> ans;
namespace Dinic{
	int head[110],cur[110],b[110],tot,T;
	struct edge{int nxt,v,w;}e[20100];
	void clear(){
		memset(head,0,sizeof(head));
		tot=1;T=n+1;
	}
	void add(int x,int y,int w){
		e[++tot]={head[x],y,w};
		head[x]=tot;
		e[++tot]={head[y],x,0};
		head[y]=tot;
	}
	bool bfs(){
		memset(b,0,sizeof(b));b[0]=1;
		queue<int> q;q.push(0);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt)
				if(e[i].w&&!b[e[i].v]){
					b[e[i].v]=b[u]+1;
					q.push(e[i].v);
				}
		}
		return b[T];
	}
	int dfs(int x,int flow){
		if(x==T||!flow) return flow;
		int tmp,f=flow;
		for(int&i=cur[x];i;i=e[i].nxt)
			if(b[e[i].v]==b[x]+1&&(tmp=dfs(e[i].v,min(e[i].w,f)))){
				f-=tmp;
				e[i].w-=tmp;e[i^1].w+=tmp;
				if(!f) break;
			}
		return flow-f;
	}
	int flow(){
		int ans=0;
		while(bfs()){
			memcpy(cur,head,sizeof(head));
			ans+=dfs(0,1e9);
		}
		return ans;
	}
}
vector<int> solve(int k1,int k2){
	double D=(p[k1]-p[k2]).len();
	for(int i=1;i<=n;i++) tag[i]=0;
	Dinic::clear();
	vector<int> ans({k1,k2});
	for(int i=1;i<=n;i++)
		if(i!=k1&&i!=k2){
			if((p[i]-p[k1]).len()>D||(p[i]-p[k2]).len()>D) continue;
			if((p[k2]-p[k1])*(p[i]-p[k1])>=0) tag[i]=1,Dinic::add(0,i,1);
			else tag[i]=2,Dinic::add(i,Dinic::T,1);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(tag[i]==1&&tag[j]==2&&(p[i]-p[j]).len()>D) Dinic::add(i,j,1e9);
	Dinic::flow();
	for(int i=1;i<=n;i++){
		if(!tag[i]) continue;
		if(tag[i]==1&&Dinic::b[i]||tag[i]==2&&!Dinic::b[i]) ans.push_back(i);
	}
	return ans;
}
int main(){
	read(n);read(D);
	for(int i=1;i<=n;i++){
		read(p[i].x);read(p[i].y);
	}
	ans.push_back(1);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if((p[i]-p[j]).len()<=D){
				auto now=solve(i,j);
				if(now.size()>ans.size()) ans=now;
			}
	cout<<ans.size()<<'\n';
	for(int x:ans) cout<<x<<' ';
	cout<<'\n';
	return 0;
}
```

