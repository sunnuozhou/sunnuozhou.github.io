---
title: ACM ICPC Central European Regional Contest 2014 E题
tags:
  - OI
  - codeforces
  - 搜索
  - DP
date: 2020-12-02 11:42:43
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100543)

可以发现，如果操作过程中如果出现序列不是先升再降（升和降的长度可以是0），那么一定不行。

于是考虑记忆化搜索，记 $f_{i,j}$ 表示放了前 $i$ 个，升的部分和为 $j$，是否可行。

直接搜索即可。

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
int vis[1010][(1<<13)+10],lg[(1<<13)+10],n,a[1010],s[1010],tim;
char ans[1010];
bool check(int x,int y){
	if(!x) return 1;
	if(y<=(x&-x)) return 1;
	return 0;
}
bool dfs(int x,int R){
	int L=s[x-1]-R;
	if(lg[L]>=lg[R]) R+=1<<lg[L],L-=1<<lg[L];
	if(x>n) return R==s[n];
	if(vis[x][R]==tim) return 0;
	vis[x][R]=tim;
	ans[x]='l';
	if(check(L,a[x])&&dfs(x+1,R)) return 1;
	ans[x]='r';
	if(((R&-R)==R||check(R,a[x]))&&dfs(x+1,(R&-R)==R?a[x]:R+a[x])) return 1;
	return 0;
}
int main(){
	int T;read(T);
	lg[1]=0;
	for(int i=2;i<=1<<13;i++) lg[i]=lg[i>>1]+1;
	while(T--){
		++tim;
		read(n);
		for(int i=1;i<=n;i++) read(a[i]),s[i]=s[i-1]+a[i];
		memset(ans,0,sizeof(ans));
		if(s[n]!=(1<<lg[s[n]])){puts("no");continue;}
		ans[1]='r';
		if(dfs(2,a[1])) puts(ans+1);
		else puts("no");
	}
	return 0;
}


```

