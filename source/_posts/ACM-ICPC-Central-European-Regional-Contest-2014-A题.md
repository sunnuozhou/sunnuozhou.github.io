---
title: ACM ICPC Central European Regional Contest 2014 A题
tags:
  - OI
  - codeforces
  - DP
  - 树形DP
  - 状压DP
date: 2020-12-01 10:54:25
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100543)

记 $f_{x,y}$ 表示在 $x$ 的子树内，根和父亲的边被以 $y$ 为端点的路径占用的最大个数。

由于度数不超过 $10$，在转移时可以预处理两两之间匹配的价值，然后用状压DP来求最大价值即可。

时间复杂度 $O(n^2+nd2^d)$。

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
int f[1010][1010],g[11][1<<10],val[11][11],n,m,a[1010][1010];
vector<int> e[1010],p[1010];
void dfs(int x,int dad){
	p[x].push_back(x);
	vector<int> q;
	for(int v:e[x]) if(v!=dad){
		dfs(v,x);
		for(int X:p[v]) p[x].push_back(X);
		q.push_back(v);
	}
	for(int i=0;i<q.size();i++)
		for(int j=i+1;j<q.size();j++){
			val[i][j]=0;
			for(int&k1:p[q[i]])
				for(int&k2:p[q[j]])
					val[i][j]=max(val[i][j],f[q[i]][k1]+f[q[j]][k2]+a[k1][k2]);
			val[j][i]=val[i][j];
		}
	for(int i=0;i<q.size();i++){
		val[i][i]=0;
		for(int&k:p[q[i]])
			val[i][i]=max(val[i][i],f[q[i]][k]+a[k][x]);
	}
	memset(g,192,sizeof(g));g[0][0]=0;
	for(int i=0;i<q.size();i++){
		for(int j=0;j<1<<q.size();j++){
			if(g[j]<0) continue;
			g[i+1][j|1<<i]=max(g[i+1][j|1<<i],g[i][j]+val[i][i]);
			for(int k=0;k<i;k++)
				if(j>>k&1) g[i+1][j^1<<k]=max(g[i+1][j^1<<k],g[i][j]+val[i][k]-val[k][k]);
		}
	}
	for(int i=0;i<1<<q.size();i++)
		f[x][x]=max(f[x][x],g[q.size()][i]);
	for(int i=0;i<q.size();i++){
		int mx=0;
		for(int k=0;k<1<<q.size();k++)
			if(k>>i&1) mx=max(mx,g[q.size()][k]-val[i][i]);
		for(int k:p[q[i]]) f[x][k]=max(f[x][k],mx+f[q[i]][k]);
	}
	//for(int k:p[x]) cerr<<x<<' '<<k<<' '<<f[x][k]<<'\n';
}
int main(){
	int T;read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++) e[i].clear(),p[i].clear();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) a[i][j]=f[i][j]=0;
		for(int i=1;i<n;i++){
			int x,y;read(x);read(y);
			e[x].push_back(y);
			e[y].push_back(x);
		}
		read(m);
		while(m--){
			int x,y;read(x);read(y);a[x][y]=a[y][x]=1;
		}
		dfs(1,0);
		cout<<f[1][1]<<'\n';
	}
	return 0;
}


```

