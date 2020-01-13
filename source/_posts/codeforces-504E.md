---
title: codeforces 504E
tags:
  - OI
  - codeforces
  - 后缀数组
  - 树链剖分
  - 解题报告
date: 2020-01-13 13:42:32
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/504/problem/E)

先树链剖分，将每一条重链上的字符串的正串和反串放在一起跑SA。对于一个询问，两个串都只被分成了$\log n$段，用SA直接求$lcp$即可。

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
int n,m,bg1[N],bg2[N],hs[N],tp[N],s[N],fa[N],dep[N];
vector<int> e[N];
char ch[N];
struct SA{
	int n,tot,tp[N],rnk[N],sa[N],f[22][N],lg[N],hgt[N],h[N];
	int c[N];
	SA(){tot=256;}
	int push(char ch){
		c[++n]=ch;
		return n;
	}
	void push_next(){
		c[++n]=++tot;
	}
	void Tsort(){
		for(int i=0;i<=m;i++) h[i]=0;
		for(int i=1;i<=n;i++) h[rnk[i]]++;
		for(int i=1;i<=m;i++) h[i]+=h[i-1];
		for(int i=n;i;i--) sa[h[rnk[tp[i]]]--]=tp[i];
	}
	void Ssort(){
		m=tot;
		for(int i=1;i<=n;i++) rnk[i]=c[i],tp[i]=i;
		Tsort();
		for(int w=1,p=0;p<n;w<<=1){
			p=0;
			for(int i=n-w+1;i<=n;i++) tp[++p]=i;
			for(int i=1;i<=n;i++)
				if(sa[i]>w) tp[++p]=sa[i]-w;
			Tsort();
			for(int i=1;i<=n;i++) tp[i]=rnk[i];
			rnk[sa[1]]=p=1;
			for(int i=2;i<=n;i++)
				rnk[sa[i]]=tp[sa[i]]==tp[sa[i-1]]&&sa[i]+w<=n&&sa[i-1]+w<=n&&tp[sa[i]+w]==tp[sa[i-1]+w]?p:++p;
			m=p;
		}
		int k=1;
		for(int i=1;i<=n;i++){
			if(--k<0) k=0;
			int j=sa[rnk[i]-1];
			while(i+k<=n&&j+k<=n&&c[i+k]==c[j+k]) k++;
			hgt[rnk[i]]=k;
			f[0][rnk[i]]=k;
		}
		for(int j=1;j<=20;j++)
			for(int i=1;i<=n;i++)
				if(i+(1<<j)-1<=n)
					f[j][i]=min(f[j-1][i],f[j-1][i+(1<<j-1)]);
		lg[0]=-1;
		for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	}
	int query(int k1,int k2){
		if(k1==k2) return n;
		int l=rnk[k1],r=rnk[k2];
		if(l>r) swap(l,r);l++;
		int k=lg[r-l+1];
		return min(f[k][l],f[k][r-(1<<k)+1]);
	}
}S;
void dfs(int x,int dad){
	s[x]=1;fa[x]=dad;dep[x]=dep[dad]+1;
	for(int v:e[x]) if(v!=dad){
		dfs(v,x);s[x]+=s[v];
		if(!hs[x]||s[v]>s[hs[x]]) hs[x]=v;
	}
}
void dfs2(int x,int top){
	tp[x]=top;
	if(hs[x]) dfs2(hs[x],top);
	for(int v:e[x]) if(v!=fa[x]&&v!=hs[x])
		dfs2(v,v);
}
void build(int x){
	bg1[x]=S.push(ch[x]);
	if(hs[x]) build(hs[x]);
	else S.push_next();
	bg2[x]=S.push(ch[x]);
}
vector<pair<int,int> > getv(int x,int y){
	vector<pair<int,int> > v1,v2;
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]>=dep[tp[y]])
			v1.emplace_back(bg2[x],dep[x]-dep[tp[x]]+1),x=fa[tp[x]];
		else
			v2.emplace_back(bg1[tp[y]],dep[y]-dep[tp[y]]+1),y=fa[tp[y]];
	}
	if(dep[x]>=dep[y]) v1.emplace_back(bg2[x],dep[x]-dep[y]+1);
	else v1.emplace_back(bg1[x],dep[y]-dep[x]+1);
	reverse(v2.begin(),v2.end());
	for(auto&p:v2) v1.push_back(p);
	return v1;
}
int main(){
	read(n);
	cin>>ch+1;
	for(int i=1;i<n;i++){
		int x,y;read(x);read(y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		if(i==tp[i]) build(i),S.push_next();
	S.Ssort();
	read(m);
	while(m--){
		int a,b,c,d;
		read(a);read(b);read(c);read(d);
		auto v1=getv(a,b);
		auto v2=getv(c,d);
		int ans=0;
		for(int k1=0,k2=0,w1=0,w2=0;k1<v1.size()&&k2<v2.size();){
			int lcp=S.query(v1[k1].first+w1,v2[k2].first+w2);
			lcp=min(lcp,min(v1[k1].second-w1,v2[k2].second-w2));
			ans+=lcp;
			if(lcp<min(v1[k1].second-w1,v2[k2].second-w2)) break;
			w1+=lcp;w2+=lcp;
			if(w1==v1[k1].second) w1=0,k1++;
			if(w2==v2[k2].second) w2=0,k2++;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

