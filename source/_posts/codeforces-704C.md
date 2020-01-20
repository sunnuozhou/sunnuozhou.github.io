---
title: codeforces 704C
tags:
  - OI
  - codeforces
  - DP
date: 2020-01-20 09:53:26
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/704/problem/C)

将变量看成点。对于一个有2个变量的语句，连一条边。对于一个只有1个变量的语句，连一个自环。接着对每一个环或者链分别DP。

记$f_{i,0/1,0/1}$表示第$i-1$个变量取值为$0/1$,当前布尔值为$0/1$的方案数，枚举$i$的值来转移。

时间复杂度$O(n+m)$。

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
struct edge{int v;pair<int,int> w;};
vector<edge> e[N];
vector<pair<int,int> > V;
int tag[N][2],f[N][2][2],vis[N],d[N],Lst,n,m;
ll ans[2];
void upd(int&a,int b){a+=b;if(a>=mod) a-=mod;}
int cir(int x,int k){
	int ans=0;
	if(tag[x][0]&1&&k) ans^=1;
	if(tag[x][1]&1&&!k) ans^=1;
	return ans;
}
int calc(pair<int,int> p,int k1,int k2){
	return p.first==k1||p.second==k2;
}
void add(int x,int y,int k1,int k2){
	d[x]++;d[y]++;
	e[x].push_back({y,make_pair(k1,k2)});
	e[y].push_back({x,make_pair(k2,k1)});
}
void dfs(int x){
	vis[x]=1;Lst=x;
	for(auto v:e[x]) 
		if(!vis[v.v]){V.push_back(v.w);dfs(v.v);}
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++){
		int k,x,y;
		read(k);
		if(k==1){
			read(x);
			if(x>0) tag[x][0]++;
			else tag[-x][1]++;
		}
		else{
			read(x);read(y);
			add(abs(x),abs(y),x<0?0:1,y<0?0:1);
		}
	}
	ans[0]=1;
	for(int x=1;x<=m;x++)
		if(!vis[x]&&d[x]==0){
			vis[x]=1;
			ll res[2]={ans[0],ans[1]};
			ans[0]=ans[1]=0;
			ans[cir(x,0)]=(ans[cir(x,0)]+res[0])%mod;
			ans[cir(x,0)^1]=(ans[cir(x,0)^1]+res[1])%mod;
			ans[cir(x,1)]=(ans[cir(x,1)]+res[0])%mod;
			ans[cir(x,1)^1]=(ans[cir(x,1)^1]+res[1])%mod;
		}
	for(int x=1;x<=m;x++)
		if(!vis[x]&&d[x]==1){
			V.clear();
			dfs(x);
			for(int i=0;i<=V.size();i++)
				f[i][0][0]=f[i][0][1]=f[i][1][0]=f[i][1][1]=0;
			f[0][0][cir(x,0)]=1;
			f[0][1][cir(x,1)]=1;
			for(int i=1;i<=V.size();i++)
				for(int j:{0,1})
					for(int k:{0,1}){
						upd(f[i][0][k^calc(V[i-1],j,0)],f[i-1][j][k]);
						upd(f[i][1][k^calc(V[i-1],j,1)],f[i-1][j][k]);
					}
			int nxt[2]={};
			upd(nxt[cir(Lst,1)],f[V.size()][1][0]);
			upd(nxt[cir(Lst,1)^1],f[V.size()][1][1]);
			upd(nxt[cir(Lst,0)],f[V.size()][0][0]);
			upd(nxt[cir(Lst,0)^1],f[V.size()][0][1]);
			ll res[2]={ans[0],ans[1]};
			ans[0]=(res[1]*nxt[1]+res[0]*nxt[0])%mod;
			ans[1]=(res[1]*nxt[0]+res[0]*nxt[1])%mod;
		}
	for(int x=1;x<=m;x++)
		if(!vis[x]){
			V.clear();
			dfs(x);
			pair<int,int> P;
			for(auto v:e[Lst])
				if(v.v==x) P=v.w;
			int nxt[2]={};
			for(int p:{0,1}){
				for(int i=0;i<=V.size();i++)
					f[i][0][0]=f[i][0][1]=f[i][1][0]=f[i][1][1]=0;
				f[0][p][0]=1;
				for(int i=1;i<=V.size();i++)
					for(int j:{0,1})
						for(int k:{0,1}){
							upd(f[i][0][k^calc(V[i-1],j,0)],f[i-1][j][k]);
							upd(f[i][1][k^calc(V[i-1],j,1)],f[i-1][j][k]);
						}
				upd(nxt[calc(P,1,p)],f[V.size()][1][0]);
				upd(nxt[calc(P,1,p)^1],f[V.size()][1][1]);
				upd(nxt[calc(P,0,p)],f[V.size()][0][0]);
				upd(nxt[calc(P,0,p)^1],f[V.size()][0][1]);
			}
			ll res[2]={ans[0],ans[1]};
			ans[0]=(res[1]*nxt[1]+res[0]*nxt[0])%mod;
			ans[1]=(res[1]*nxt[0]+res[0]*nxt[1])%mod;
		}
	cout<<(ans[1]+mod)%mod<<'\n';
	return 0;
}
```

