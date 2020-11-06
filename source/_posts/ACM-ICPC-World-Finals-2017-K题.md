---
title: ACM ICPC World Finals 2017 K题
tags:
  - OI
  - codeforces
  - KMP
  - 字符串
  - 容斥
date: 2020-11-02 12:18:30
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101471)

考虑如何算一个子串的出现概率，可以使用容斥：

$$P(T)=\sum\limits_{W}(-1)^{|W|}p(W)$$

其中 $W$ 是一个位置集合，$p(W)$ 表示以所有集合中的位置为开头的串都是 $T$ 的概率。

观察这个容斥，可以发现 $P(T)$ 只与 $T$ 的`border`有关，求出`border`后排序即可。

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
int n,m,nxt[N],p[15];
string S[15];
vector<int> f[15];
int find(string&st,int x,char ch){
	if(x<0) return ch==st[0]?0:-1;
	return ch==st[x+1]?x+1:find(st,nxt[x],ch);
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>S[i];
		int len=S[i].length();
		nxt[0]=-1;
		for(int j=1;j<len;j++)
			nxt[j]=find(S[i],nxt[j-1],S[i][j]);
		for(int j=len-1;~j;j=nxt[j]){
			if(len*2-j-1>n) continue;
			f[i].push_back(j);
		}
	}
	for(int i=1;i<=m;i++) p[i]=i;
	stable_sort(p+1,p+m+1,[&](int a,int b){return f[a]<f[b];});
	for(int i=1;i<=m;i++)
		cout<<S[p[i]]<<'\n';
	return 0;
}
```

