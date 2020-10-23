---
title: ACM ICPC World Finals 2014 H题
tags:
  - OI
  - codeforces
  - 高斯消元
date: 2020-10-22 11:43:00
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101221)

记录 $f_{i,j}$ 表示在所有有限步结束的状态中，$(i,j)$ 这个位置被经过的次数的期望，并强制走到"T"位置后结束。那么对于一个"T"位置，$f_{i,j}$ 就是第一次访问到的是它的概率。

有 $f_{i,j}=p_u\times f_{i-1,j}+p_d\times f_{i+1,j}+p_l\times f_{i,j-1}+p_r\times f_{i,j+1}$，可以高斯消元解决。

考虑到高斯消元的时候，一个方程中最多只有 $O(m)$ 个未知数的系数非零，所以暴力高斯消元的复杂度是 $O(nm^3)$，可以通过本题。

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
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
int n,m;
double p[4],ans[N];
char mp[10100][25];
unordered_map<int,double> a[N];
int id(int x,int y){return x*m+y-m;}
int main(){
	read(m);read(n);
	for(int i=0;i<4;i++) read(p[i]),p[i]/=100;
	for(int i=1;i<=n;i++)
		scanf(" %s",mp[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='X') continue;
			int now=id(i,j);a[now][now]=1;
			if(mp[i][j]=='T') continue;
			double tot=0;
			for(int k=0;k<4;k++){
				int tx=i+dx[k],ty=j+dy[k];
				if(tx<1||ty<1||tx>n||ty>m||mp[tx][ty]=='X') continue;
				tot+=p[k];
			}
			for(int k=0;k<4;k++){
				int tx=i+dx[k],ty=j+dy[k];
				if(tx<1||ty<1||tx>n||ty>m||mp[tx][ty]=='X') continue;
				a[id(tx,ty)][now]-=p[k]/tot;
			}
		}
	int tot=0;
	for(int i=1;i<=m;i++) tot+=mp[1][i]!='X';
	for(int i=1;i<=m;i++) if(mp[1][i]!='X') a[id(1,i)][n*m+1]=1./tot;
	for(int i=1;i<=n*m;i++){
		if(fabs(a[i][i])<1e-12)
			for(int j=i+1;j<=n*m&&j-i<=m;j++)
				if(fabs(a[j][i])>1e-12){
					swap(a[i],a[j]);
					break;
				}
		if(fabs(a[i][i])<1e-12) continue;
		for(int j=i+1;j<=n*m&&j-i<=m;j++){
			double r=a[j][i]/a[i][i];
			if(fabs(r)<1e-12) continue;
			for(auto&pr:a[i])
				if(fabs(pr.second)>1e-12)
				a[j][pr.first]-=pr.second*r;
		}
	}
	for(int i=n*m;i;i--){
		ans[i]=a[i][n*m+1];
		for(auto&pr:a[i])
			if(pr.first<=n*m&&pr.first>i) ans[i]-=pr.second*ans[pr.first];
		ans[i]/=a[i][i];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]=='T') printf("%.9lf\n",ans[id(i,j)]);
	return 0;
}
```

