---
title: ACM ICPC Central European Regional Contest 2015 G题
tags:
  - OI
  - codeforces
date: 2020-11-30 12:01:52
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101480)

可以发现，如果相邻两个位置的高度一样了，那么它们的高度以后必定一直一样。

所以可以将相邻相同高度的位置合并。

用堆维护会合并的时间，分为从左照差距变小，从右照差距变小，从两边照差距都变小维护。

可以发现，一个间隙的情况只和相邻的最多4个位置有关，在一次合并后暴力更新即可。

时间复杂度 $O(n\log n)$。

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
const int N = 301000;
int n,m,nxt[N],pre[N],L,R,z[N],lst0[N],lst1[N];
ll h[N],val[N];
char c[N];
struct Heap{
	priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > p,q;
	void emplace(ll x,int y){p.emplace(x,y);}
	void erase(ll x,int y){q.emplace(x,y);}
	void maintain(){while(p.size()&&q.size()&&p.top()==q.top()) q.pop(),p.pop();}
	pair<ll,int> top(){
		maintain();return p.top();
	}
	int size(){
		maintain();return p.size();
	}
}hp[2][2];
int Lg(int x){return pre[x]&&h[x-1]>h[x];}
int Rg(int x){return nxt[x]&&h[nxt[x]]>h[nxt[x]-1];}
void add(int x){
	int p0=Lg(x),p1=Rg(x);
	int q0=Lg(nxt[x]),q1=Rg(nxt[x]);
	int k0=p0+q0==1,k1=p1+q1==1;
	if(k0) val[x]+=L;
	if(k1) val[x]+=R;
//	lst0[x]=k0;lst1[x]=k1;
//	cerr<<x<<' '<<k0<<' '<<k1<<' '<<val[x]<<' '<<L<<' '<<R<<endl;
	hp[k0][k1].emplace(val[x],x);
}
void del(int x){
	int p0=Lg(x),p1=Rg(x);
	int q0=Lg(nxt[x]),q1=Rg(nxt[x]);
	int k0=p0+q0==1,k1=p1+q1==1;
//	assert(lst0[x]==k0&&lst1[x]==k1);
	hp[k0][k1].erase(val[x],x);
	if(k0) val[x]-=L;
	if(k1) val[x]-=R;
}
void merge_s(int x){
	if(pre[x]) del(pre[x]);
	if(pre[pre[x]]) del(pre[pre[x]]);
	if(nxt[nxt[x]]) del(nxt[x]);
	if(nxt[nxt[nxt[x]]]) del(nxt[nxt[x]]);
	del(x);
}
void merge_g(int x){
	int y=nxt[x];
	val[x]=val[y];
	nxt[x]=nxt[y];if(nxt[y])pre[nxt[y]]=x;
	if(pre[x]) add(pre[x]);
	if(pre[pre[x]]) add(pre[pre[x]]);
	if(nxt[x]) add(x);
	if(nxt[nxt[x]]) add(nxt[x]);
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)
		read(h[i]);
	scanf(" %s",c+1);
	for(int i=1;i<=n;){
		int p=i+1;
		while(p<=n&&h[p]==h[i]) p++;
		if(p<=n) nxt[i]=p,pre[p]=i;
		i=p;
	}
	for(int i=1,j=1;i<=n;i=j){
		j=nxt[i]?nxt[i]:n+1;
		if(j<=n) val[i]=abs(h[i]-h[j]),add(i);
	}
	for(int i=1;i<=m;i++) z[i]=1;
	ll H=h[1];
	for(int t=1;t<=m;t++){
again:;
		ll nt=1e18;int w=0;
		if(hp[1][1].size()&&hp[1][1].top().first<nt)
			nt=hp[1][1].top().first,w=hp[1][1].top().second;
		if(c[t]=='A'){
			nt-=R;
			if(hp[1][0].size()&&hp[1][0].top().first<nt)
				nt=hp[1][0].top().first,w=hp[1][0].top().second;
			if(L+z[t]>=nt){
				z[t]-=nt-L;L=nt;
				merge_s(w);
				merge_g(w);
				goto again;
			}
			L+=z[t];
		}
		else{
			nt-=L;
			if(hp[0][1].size()&&hp[0][1].top().first<nt)
				nt=hp[0][1].top().first,w=hp[0][1].top().second;
			if(R+z[t]>=nt){
				if(h[nxt[1]]>h[nxt[1]-1]) H+=nt-R;
				z[t]-=nt-R;R=nt;
				merge_s(w);
				merge_g(w);
				goto again;
			}
			R+=z[t];
		}
		if(c[t]=='B'&&nxt[1]&&h[nxt[1]]>h[nxt[1]-1]) H+=z[t];
	}
	for(int i=1,j=1;i<=n;i=j){
		j=nxt[i];
		if(!j) j=n+1;
		for(int k=i;k<j;k++)
			cout<<H<<' ';
		if(j>n) break;
		del(i);
		if(h[j-1]>h[j]) H-=val[i];
		else H+=val[i];
	}
	cout<<'\n';
	return 0;
}
```

