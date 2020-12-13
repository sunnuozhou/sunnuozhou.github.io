---
title: ACM ICPC Central European Regional Contest 2014 J题
tags:
  - OI
  - codeforces
  - lct
  - 线段树
date: 2020-12-02 11:42:45
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100543)

按边权从小到大加入边，并用LCT维护最大生成树，求出每条边有贡献的范围，再用主席树回答询问即可。

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
struct edge{int u,v,w;}E[N];
struct node{int l,r,num;}q[N];
int n,m,h[N];
ll ans[N];
struct LCT{
	int rev[N],ch[N][2],fa[N],mn[N],val[N],w[N],num;
	bool nr(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
	bool r(int x){return ch[fa[x]][1]==x;}
	void pushup(int x){
		mn[x]=val[x];w[x]=x;
		if(ch[x][0]&&mn[ch[x][0]]<mn[x]) mn[x]=mn[ch[x][0]],w[x]=w[ch[x][0]];
		if(ch[x][1]&&mn[ch[x][1]]<mn[x]) mn[x]=mn[ch[x][1]],w[x]=w[ch[x][1]];
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=r(x);
		if(nr(y)) ch[z][r(y)]=x;fa[x]=z;
		ch[y][k]=ch[x][k^1];fa[ch[y][k]]=y;
		ch[x][k^1]=y;fa[y]=x;pushup(y);
	}
	void Rev(int x){swap(ch[x][0],ch[x][1]);rev[x]^=1;}
	void pushdown(int x){
		if(rev[x]) Rev(ch[x][0]),Rev(ch[x][1]),rev[x]=0;
	}
	void push_all(int x){
		if(nr(x)) push_all(fa[x]);
		pushdown(x);
	}
	void splay(int x){
		for(push_all(x);nr(x);rotate(x))
			if(nr(fa[x])) rotate(r(x)==r(fa[x])?fa[x]:x);
		pushup(x);
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y,pushup(x);
	}
	void makert(int x){
		access(x);splay(x);Rev(x);
	}
	int find(int x){
		access(x);splay(x);
		while(ch[x][0]) pushdown(x),x=ch[x][0];
		return x;
	}
	void link(int x,int y){
//		cerr<<"@"<<x<<' '<<y<<endl;
		makert(x);fa[x]=y;
	}
	void split(int x,int y){
		makert(x);access(y);splay(y);
	}
	void cut(int x,int y){
//		cerr<<"#"<<x<<' '<<y<<endl;
		split(x,y);fa[x]=ch[y][0]=0;pushup(y);
	}
	void clear(){
		for(int i=1;i<=num;i++) fa[i]=ch[i][0]=ch[i][1]=mn[i]=val[i]=w[i]=rev[i]=0;
	}
}t;
struct segment_tree{
	ll s[N*30];
	int lc[N*30],rc[N*30],tot,rt[N];
	void clear(){
		for(int i=1;i<=tot;i++) lc[i]=rc[i]=s[i]=0;
		for(int i=1;i<=n+m;i++) rt[i]=0;
		tot=0;
	}
	void insert(int&x,int y,int w,int k,int l=1,int r=1e6){
		x=++tot;
		lc[x]=lc[y];rc[x]=rc[y];s[x]=s[y]+k;
		if(l==r) return;
		int mid=l+r>>1;
		if(w<=mid) insert(lc[x],lc[y],w,k,l,mid);
		else insert(rc[x],rc[y],w,k,mid+1,r);
	}
	ll query(int x,int w,int l=1,int r=1e6){
		if(r<=w) return s[x];
		int mid=l+r>>1;
		if(w<=mid) return query(lc[x],w,l,mid);
		return query(lc[x],w,l,mid)+query(rc[x],w,mid+1,r);
	}
}tt;
int main(){
	int T;read(T);
	while(T--){
		read(n);read(m);
		t.num=n+m;
		for(int i=1;i<=n;i++) t.val[i]=1e9,t.pushup(i);
		for(int i=1;i<=m;i++){
			int x,y,z;read(x);read(y);read(z);
			E[i]={x,y,z};
		}
		sort(E+1,E+m+1,[](edge a,edge b){return a.w<b.w;});
		for(int i=1;i<=m;i++){
			t.val[i+n]=E[i].w;t.pushup(i+n);
			int u=E[i].u,v=E[i].v;
			if(t.find(u)!=t.find(v)) h[i]=0,t.link(u,i+n),t.link(v,i+n);
			else{
				t.split(u,v);
				int w=t.w[v];h[i]=w-n;
				t.cut(E[w-n].u,w);
				t.cut(E[w-n].v,w);
				t.link(u,i+n);
				t.link(v,i+n);
			}
		}
//		for(int i=1;i<=m;i++) cout<<i<<' '<<E[i].u<<' '<<E[i].v<<' '<<E[i].w<<' '<<h[i]<<'\n';
		for(int i=1;i<=m;i++){
			tt.insert(tt.rt[i],tt.rt[i-1],E[h[i]].w+1,E[i].w);
			tt.insert(tt.rt[i],tt.rt[i],E[i].w+1,-E[i].w);
		}
		int Q;read(Q);
		ll lst=0;
		while(Q--){
			int l,r;read(l);read(r);
			l-=lst;r-=lst;
			int k=upper_bound(E+1,E+m+1,edge{0,0,r},[](edge a,edge b){return a.w<b.w;})-E-1;
			cout<<(lst=tt.query(tt.rt[k],l))<<'\n';
		}
		tt.clear();
		t.clear();
	}
	return 0;
}


```

