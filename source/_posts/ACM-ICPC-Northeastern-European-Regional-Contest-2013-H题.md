---
title: ACM ICPC Northeastern European Regional Contest 2013 H题
tags:
  - OI
  - codeforces
date: 2020-11-20 10:42:55
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100307)

考虑维护每个位置的前缀异或和异或自己再异或上当前的区间and值，记为 $val_i$。

每次暴力更新会变动的 $val_i$，并在哈希表中查询前缀异或和即可。

时间复杂度 $O(n\log V)$，$V$ 是值域，常数巨大。

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
int n,a[N],val[N],lst[50];
ll ans;
unordered_map<int,int> mp;
int main(){
	freopen("hack.in","r",stdin);
	freopen("hack.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int j=0;j<31;j++) lst[j]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<31;j++)
			if(~a[i]>>j&1){
				for(int k=lst[j];k<i;k++)
					mp[val[k]]--,val[k]^=1<<j,mp[val[k]]++;
				lst[j]=i+1;
			}
		a[i]^=a[i-1];val[i]=a[i];mp[val[i]]++;
//		for(int j=0;j<i;j++) cerr<<val[j]<<' ';cerr<<'\n';
//		cerr<<a[i]<<'\n';
		ans+=mp[a[i]];
	}
	cout<<ans<<'\n';
	return 0;
}


```

