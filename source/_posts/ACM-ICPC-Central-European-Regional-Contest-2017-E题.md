---
title: ACM ICPC Central European Regional Contest 2017 E题
tags:
  - OI
  - codeforces
  - DP
  - 树形DP
date: 2020-11-24 11:41:51
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101620)

考虑最基本的DP，记 $f_{x,k}$ 表示填充 $x$ 的子树，另一行往前有 $k$ 个空位，然后转移即可，这是 $O(n^2)$ 的。

考虑令 $k\le 1$，将 $k>1$ 的情况在转移时讨论掉就可以，这样时间复杂度就是 $O(n)$ 了。

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
const int N = 301000,mod = 1e9+7;
int f[N][2],dep[N],tp[N],n,d[N],ch[N][2];
vector<int> v[N],e[N];
int get_last(int x){
	return v[tp[x]][0];
}
int check(int x,int y){
	int fg0=d[get_last(x)]==2,L0=dep[get_last(x)]-dep[x];
	int fg1=d[get_last(y)]==2,L1=dep[get_last(y)]-dep[y];
	if(L0<L1) swap(L0,L1),swap(fg0,fg1),swap(x,y);
	if(fg1) return -1;
	if(L0==L1&&fg0) return -1;
	if(L0==L1) return 0;
	return v[tp[x]][L0-L1-1];
}
void dfs(int x,int dad){
	dep[x]=dep[dad]+1;
	for(int v:e[x]) if(v!=dad){
		if(d[x]==2){puts("0");exit(0);}
		dfs(v,x);ch[x][d[x]++]=v;
	}
	if(d[x]==1) v[x].swap(v[ch[x][0]]);
	v[x].push_back(x);
}
void dp(int x,int top){
	tp[x]=top;
	if(d[x]==0){f[x][0]=f[x][1]=1;return;}
	if(d[x]==1){
		dp(ch[x][0],top);
		f[x][0]=f[ch[x][0]][1];
		f[x][1]=(f[ch[x][0]][0]+f[ch[x][0]][1])%mod;
		if(d[get_last(top)]==0){
			int len=dep[get_last(top)]-dep[x];
			if(len&1&&len>1) f[x][1]=(f[x][1]+1)%mod;
		}
		else{
			int u=get_last(top),len=dep[u]-dep[x];
			int fg0=d[get_last(ch[u][0])]==0,L0=v[ch[u][0]].size();
			int fg1=d[get_last(ch[u][1])]==0,L1=v[ch[u][1]].size();
			if(fg0&&L0==len-1&&len>1){
				f[x][1]=(f[x][1]+f[ch[u][1]][1])%mod;
			}
			if(fg1&&L1==len-1&&len>1){
				f[x][1]=(f[x][1]+f[ch[u][0]][1])%mod;
			}
			int L;
			if(d[ch[u][0]]){
				L=dep[get_last(ch[ch[u][0]][0])]-dep[u]-1;
				if(L==len&&d[get_last(ch[ch[u][0]][0])]==0){
					if(d[ch[u][0]]==2){
						int k=check(ch[ch[u][0]][1],ch[u][1]);
						if(k==0) f[x][1]=(f[x][1]+1)%mod;
						if(k>0) f[x][1]=(f[x][1]+f[k][1])%mod;
					}
					else f[x][1]=(f[x][1]+f[ch[u][1]][1])%mod;
				}
				if(d[ch[u][0]]==2){
					 L=dep[get_last(ch[ch[u][0]][1])]-dep[u]-1;
					 if(L==len&&d[get_last(ch[ch[u][0]][1])]==0){ 
						int k=check(ch[ch[u][0]][0],ch[u][1]);
						if(k==0) f[x][1]=(f[x][1]+1)%mod;
						if(k>0) f[x][1]=(f[x][1]+f[k][1])%mod;
					 }
				}
			}
			swap(ch[u][0],ch[u][1]);
			if(d[ch[u][0]]){
				L=dep[get_last(ch[ch[u][0]][0])]-dep[u]-1;
				if(L==len&&d[get_last(ch[ch[u][0]][0])]==0){
					if(d[ch[u][0]]==2){
						int k=check(ch[ch[u][0]][1],ch[u][1]);
						if(k==0) f[x][1]=(f[x][1]+1)%mod;
						if(k>0) f[x][1]=(f[x][1]+f[k][1])%mod;
					}
					else f[x][1]=(f[x][1]+f[ch[u][1]][1])%mod;
				}
				if(d[ch[u][0]]==2){
					 L=dep[get_last(ch[ch[u][0]][1])]-dep[u]-1;
					 if(L==len&&d[get_last(ch[ch[u][0]][1])]==0){ 
						int k=check(ch[ch[u][0]][0],ch[u][1]);
						if(k==0) f[x][1]=(f[x][1]+1)%mod;
						if(k>0) f[x][1]=(f[x][1]+f[k][1])%mod;
					 }
				}
			}
			swap(ch[u][0],ch[u][1]);
		}
	//	cerr<<x<<' '<<f[x][0]<<' '<<f[x][1]<<'\n';
		return;
	}
	dp(ch[x][0],ch[x][0]);dp(ch[x][1],ch[x][1]);
	f[x][0]=0;
	if(d[ch[x][0]]==0) f[x][1]=(f[x][1]+f[ch[x][1]][1])%mod;
	if(d[ch[x][1]]==0) f[x][1]=(f[x][1]+f[ch[x][0]][1])%mod;
	if(d[ch[x][0]]==1){
		int k=check(ch[ch[x][0]][0],ch[x][1]);
		if(k==0) f[x][1]=(f[x][1]+1)%mod;
		if(k>0) f[x][1]=(f[x][1]+f[k][1])%mod;
	}
	if(d[ch[x][1]]==1){
		int k=check(ch[ch[x][1]][0],ch[x][0]);
		if(k==0) f[x][1]=(f[x][1]+1)%mod;
		if(k>0) f[x][1]=(f[x][1]+f[k][1])%mod;
	}
	//	cerr<<x<<' '<<f[x][0]<<' '<<f[x][1]<<'\n';
}
int main(){
	read(n);
	for(int i=1;i<n;i++){
		int x,y;read(x);read(y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,0);
	dp(1,1);
	cout<<f[1][1]<<'\n';
	return 0;
}


```

