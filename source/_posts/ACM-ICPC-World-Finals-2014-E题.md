---
title: ACM ICPC World Finals 2014 E题
tags:
  - OI
  - codeforces
  - 哈希
date: 2020-10-21 10:51:58
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101221)

初始时，给每种不同度数的点分配一个随机权值。

记录 $f_{t,u,v}$ 表示在房间 $u$，上一个房间是 $v$ ，转移 $t$ 次后的哈希值，转移方式为将 $f_{t-1,x,u}$，以 $f_{t-1,v,u}$ 为起点按顺序结合起来 。

由于最长的路径不超过 $n$，所以转移 $n$ 次就够了。

最后对于一个点 $u$，其哈希值为将所有 $f_{n,u,v}$ 无序结合起来。

时间复杂度 $O(n^4)$，可以优化到 $O(n^3)$ 但没必要。

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
const int N = 101000,mod = 1e9+9,K = 12347;
mt19937 rd(3824);
int n,hsh[110],f[110][110][110],e[110][110],d[110];
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(d[i]);
		for(int j=1;j<=d[i];j++){
			int x;read(x);
			e[i][j]=x;
		}
	}
	for(int i=0;i<=n;i++) hsh[i]=rd()%mod;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d[i];j++){
			ll ans=0;
			for(int k=j+1;k<=d[i];k++) ans=(ans*K+hsh[d[e[i][k]]])%mod;
			for(int k=1;k<=j;k++) ans=(ans*K+hsh[d[e[i][k]]])%mod;
			f[0][i][e[i][j]]=(ans*ans+hsh[d[i]])%mod;
		}
	}
	for(int t=1;t<=n;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=d[i];j++){
				ll ans=0;
				for(int k=j+1;k<=d[i];k++) ans=(ans*K+f[t-1][e[i][k]][i])%mod;
				for(int k=1;k<=j;k++) ans=(ans*K+f[t-1][e[i][k]][i])%mod;
				f[t][i][e[i][j]]=(ans*ans+f[t-1][i][e[i][j]])%mod;
			}
		}
	}
	map<int,vector<int> > mp;
	for(int i=1;i<=n;i++){
		hsh[i]=0;
		for(int j=1;j<=d[i];j++)
			hsh[i]=(hsh[i]+1ll*f[n][i][e[i][j]]*f[n][i][e[i][j]])%mod;
	}
	for(int i=1;i<=n;i++)
		mp[hsh[i]].push_back(i);
	vector<vector<int> > V;
	for(auto p:mp){
		sort(p.second.begin(),p.second.end());
		V.push_back(p.second);
	}
	sort(V.begin(),V.end());
	int flag=1;
	for(auto&p:V){
		if(p.size()==1) continue;
		for(auto&x:p) cout<<x<<' ';
		cout<<'\n';
		flag=0;
	}
	if(flag) cout<<"none\n";
	return 0;
}
```

