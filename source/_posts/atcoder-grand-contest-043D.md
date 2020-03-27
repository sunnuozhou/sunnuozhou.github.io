---
title: atcoder grand contest 043D
tags:
  - OI
  - atcoder
  - DP
date: 2020-03-27 14:42:14
categories: 解题报告
top:
---

[题目链接](https://atcoder.jp/contests/agc043/tasks/agc043_d)

对于一个序列$(x1,x2,x3)$，如果$x_i$不是前缀最大值，那么在选完它的前一个后就会立即选它。因此我们可以把所有不是前缀最大值的数和在它前面的那个前缀最大值合并，形成一个组，组的权值是第一个数的大小。

可以发现，排列$P$就是若干个组按权值从小到大排序的结果，并且有以下限制：

- 每一个组里的元素个数都不超过3
- 如果元素个数为1的组贡献为1，元素个数为2的组贡献为-1，元素个数为3的组贡献为0，那么排列$P$合法要求共贡献非负且为3的倍数。

然后就可以DP了，记录$f_{i,j,k}$表示当前已经处理了$i$个位置，当前的组元素个数为$j$，共贡献为$k$。转移时枚举这个位置是不是一个组的开头即可。

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
const int N = 2010;
int f[3*N][3][6*N],n,mod;
void upd(int &a,ll b){a=(a+b)%mod;}
int main(){
	read(n);read(mod);
	f[1][0][0]=1;
	for(int i=1;i<3*n;i++)
		for(int j=0;j<3;j++)
			for(int k=-i;k<=i;k++)
				if(f[i][j][k]){
					if(j<2){
						upd(f[i+1][j+1][k],1ll*f[i][j][k]*i);
					}
					upd(f[i+1][0][k+(j==0)-(j==1)],f[i][j][k]);
				}
	ll ans=0;
	for(int k=0;k<=3*n;k+=3)
		ans=(ans+f[3*n][0][k-1]+f[3*n][1][k+1]+f[3*n][2][k])%mod;
	cout<<ans<<'\n';
	return 0;
}


```

