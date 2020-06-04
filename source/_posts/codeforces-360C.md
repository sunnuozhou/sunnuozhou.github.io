---
title: codeforces 360C
tags:
  - OI
  - codeforces
  - DP
date: 2020-06-03 13:55:51
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/360/problem/C)

有显然的3方暴力DP，记 $f_{i,j,p}$ 表示前 $i$ 个，现有 $j$ 个子串比原串大，连着 $p$ 个字符和原串相同，转移时枚举当前位置与 $S_i$ 的大小关系。

考虑如何优化。

如果不把 $p$ 记在状态中，而是在转移时枚举 $p$，那么如果下一个字符比原串大，转移时 $j\rightarrow j+(p+1)\times(n-i-p+2)$，分析一下可得这种转移的总次数是 $O(nk\log k)$ 级别的，可以暴力实现。如果下一个字符比原串小，转移时 $j$ 不变，可以前缀和优化。

时间复杂度 $O(nk\log k)$。

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
int n,k;
char c[2010];
int f[2010][2010],s[2010];
void upd(int&a,ll b){a=(a+b)%mod;}
int main(){
	read(n);read(k);
	cin>>c+1;
	f[1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++) upd(s[j],f[i][j]);
		for(int j=0;j<=k;j++){
			upd(f[i+1][j],1ll*s[j]*(c[i]-'a'));
			if(!f[i][j]) continue;
			int lst=0;
			for(int p=1;i+p<=n+1&&p*(n-i-p+2)+j<=k;p++){
				lst=p;
				if(p*(n-i-p+2)+j<=k) upd(f[i+p][j+p*(n-i-p+2)],1ll*('z'-c[i+p-1])*f[i][j]);
			}
			for(int p=n+1-i;p>lst&&p*(n-i-p+2)+j<=k;p--){
				upd(f[i+p][j+p*(n-i-p+2)],1ll*('z'-c[i+p-1])*f[i][j]);
			}
		}
	}
	ll ans=0;
	for(int i=0;i<=n+1;i++) ans=(ans+f[i][k])%mod;
	cout<<ans<<'\n';
	return 0;
}
```

