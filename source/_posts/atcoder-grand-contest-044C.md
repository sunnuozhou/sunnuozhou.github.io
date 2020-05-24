---
title: atcoder grand contest 044C
tags:
  - OI
  - atcoder
  - 分块
date: 2020-05-24 16:22:23
categories: 解题报告
top:
---

[题目链接](https://atcoder.jp/contests/agc044/tasks/agc044_c)

### 解法1

考虑将 $3^n$ 的位置分块，每 $3^k$ 分一块。

对于操作S，每个块内元素顺序会改变，块之间的顺序也会改变。

对于操作$R$，每个块内会循序移动，一个块的开头会变成上个块的末尾。

考虑对于块与块之间的操作数量都是 $3^{n-k}$ 级别的，可以暴力。

两个操作对于每个块内的效果都是相同的，记录一个块内的映射，每次暴力修改，次数是 $3^k$ 级别的。

当 $k=n/2$ 时，时间复杂度为 $O(|T|\times 3^{\frac n2})$，可以通过。

<!--more-->

### 解法2

令 $P_i^n$ 表示有 $3^n$ 个人时，最终第 $i$ 个位置是谁。

令 $W_k^n$ 表示有 $3^n$ 个人时，在第 $k$ 首歌后，标号为 $3^n-1$ 的位置上是谁。

观察可得以下结论：

- $P_i^{n+1}\equiv P_{i+3^n}^{n+1}\equiv P_{i+2\times 3^n}^{n+1}\equiv P_i^n\mod 3^n$

- $W_k^{n+1}\equiv W_k^n\mod 3^n$

显然 $P^0,W^0$ 可以快速求出。

现在考虑我们已经知道了 $P^n,W^n$，如何求 $P^{n+1},W^{n+1}$。

根据上述结论，我们只要求出 $P^{n+1},W^{n+1}$ 的最高位就可以求出 $P^{n+1},W^{n+1}$。

记 $D_i$ 表示 $i$ 号人所在的位置的最高位是什么，考虑如何维护 $D$。

对于操作S，所有 $D$ 中的1和2交换。

对于操作R，只有下标为 $W_k^n,W_k^n+3^n,W_k^n+2\times3^n$ 的值会变。

对于每一个时刻，$W_k^{n+1}$ 都是 $D_{W_k^n},D_{W_k^n+3^n},D_{W_k^n+2\times3^n}$ 中值为2的那个的下标。

对于操作S，可以打懒标记，因为每次要用到的只有 $D_{W_k^n},D_{W_k^n+3^n},D_{W_k^n+2\times3^n}$。

对于操作R，暴力即可。

时间复杂度 $O(3^n+n|T|)$。

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
const int N = 1001000;
string T;
int P[N],W[N],nP[N],nW[N],n,tag[N],D[N];
void solve(int n){
	int siz=pow(3,n-1)+0.5;
	for(int i=0;i<3;i++)
		for(int j=0;j<siz;j++)
			D[i*siz+j]=i,tag[i*siz+j]=0;
	int Tag=0;
	auto upd =[&](int x){
		if(tag[x]!=Tag&&D[x]) D[x]=3-D[x];
		tag[x]=Tag;
	};
	for(int i=0;i<T.size();i++){
		for(int j=0;j<3;j++){
			int w=j*siz+W[i];
			upd(w);
			if(D[w]==2) nW[i]=w;
		}
		if(T[i]=='S') Tag^=1;
		else{
			for(int j=0;j<3;j++){
				int w=j*siz+W[i];
				D[w]=(D[w]+1)%3;
			}
		}
	}
	for(int i=0;i<3;i++)
		for(int j=0;j<siz;j++){
			upd(i*siz+j);
			nP[i*siz+j]=D[i*siz+j]*siz+P[j];
		}
	memcpy(P,nP,sizeof(P));
	memcpy(W,nW,sizeof(W));
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>T;
	for(int i=1;i<=n;i++) solve(i);
	int siz=pow(3,n)+0.5;
	for(int i=0;i<siz;i++) cout<<P[i]<<' ';
	cout<<'\n';
	return 0;
}


```

