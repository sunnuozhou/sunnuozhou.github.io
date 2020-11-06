---
title: ACM ICPC World Finals 2019 J题
tags:
  - OI
  - codeforces
date: 2020-11-05 13:06:52
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102511/problem/J)

考虑对每个人求他的最优排名，那么其他人就有一些不劣于他的区间，求出这些区间，然后差分求出被覆盖次数的最小值就是答案。

时间复杂度 $O(n^2h)$

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
int n,m;
ll a[510][510];
int cnt,pos[510],p[510],ans[510],w[510];
struct node{int k1,k2;ll t;}b[1001000];
ll sum[510];
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			read(a[i][j]);
		}
	for(int i=1;i<=n;i++){
		ans[i]=n;
		pos[i]=1;
		for(int j=1;j<=m;j++)
			sum[i]+=a[i][j];
		sort(a[i]+1,a[i]+m+1,greater<int>());
	}
	for(int i=1;i<=n;i++){
		vector<pair<int,int> > V;
		int now=0;
		for(int j=1;j<=n;j++)
			if(i!=j){
				int k1=1,k2=1,lst=max(a[i][1],a[j][1]);
				ll S1=sum[i],S2=sum[j];
				if(S2<=S1) now++,V.emplace_back(lst,-1);
				while(k1<=m||k2<=m){
					int lim;
					if(k2>m||k1<=m&&a[i][k1]>=a[j][k2]) lim=a[i][k1++],S1+=lst-lim;
					else lim=a[j][k2++],S2+=lst-lim;
					S1-=1ll*(lst-lim)*(k1-1);
					S2-=1ll*(lst-lim)*(k2-1);
					lst=lim;
					if(lim==max(a[i][k1],a[j][k2])) continue;
					if(k1!=k2){
						if(S2<=S1){
							ll nxt=(S1-S2)/(k1-k2);
							if(k1<k2) nxt=1e9;
				//			if(i==1) cerr<<j<<' '<<lim<<' '<<max(lim-nxt-1,max(a[i][k1],a[j][k2]))<<'\n';
							V.emplace_back(lim,1);
							V.emplace_back(max(lim-nxt-1,max(a[i][k1],a[j][k2])),-1);
						}
						else{
							ll nxt=(S2-S1+k2-k1-1)/(k2-k1);
							if(k2<k1||lim-nxt<=max(a[i][k1],a[j][k2])) continue;
				//			if(i==1) cerr<<j<<' '<<lim-nxt<<' '<<max(a[i][k1],a[j][k2])<<'\n';
							V.emplace_back(lim-nxt,1);
							V.emplace_back(max(a[i][k1],a[j][k2]),-1);
						}
					}
					else if(S2<=S1){
				//		if(i==1) cerr<<j<<' '<<lim<<' '<<max(a[i][k1],a[j][k2])<<'\n';
						V.emplace_back(lim,1);
						V.emplace_back(max(a[i][k1],a[j][k2]),-1);
					}
				}
			}
		sort(V.begin(),V.end(),greater<pair<int,int>>());
		int mn=now;
		for(auto&pr:V){
			if(pr.first<1) break;
			now+=pr.second,mn=min(mn,now);
		}
		ans[i]=mn+1;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
 
```

