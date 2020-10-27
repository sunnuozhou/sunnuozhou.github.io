---
title: ACM ICPC World Finals 2015 L题
tags:
  - OI
  - codeforces
  - 贪心
date: 2020-10-26 10:39:11
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101239)

首先枚举每种天气出现的次数，可以发现，所有每种天气出现的次数但顺序不同的是等价的。也就是现在有 $O(n^4)$ 个等价类，每个等价类有一个出现概率和一个总个数。

接下来使用哈夫曼编码就可以解决，时间复杂度 $O(n^4\log{n^4})$。

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
int n;
double ans,p[4];
priority_queue<pair<double,ll>,vector<pair<double,ll> >,greater<pair<double,ll> > > q;
ll calc(int k0,int k1,int k2,int k3){
	ll ans=1;
	for(int i=1;i<=n;i++) ans=ans*i;
	for(int i=1;i<=k0;i++) ans=ans/i;
	for(int i=1;i<=k1;i++) ans=ans/i;
	for(int i=1;i<=k2;i++) ans=ans/i;
	for(int i=1;i<=k3;i++) ans=ans/i;
	return ans;
}
int main(){
	read(n);
	for(int i=0;i<4;i++)
		scanf("%lf",p+i);
	for(int k1=0;k1<=n;k1++)
		for(int k2=0;k1+k2<=n;k2++)
			for(int k3=0;k1+k2+k3<=n;k3++){
				int k0=n-k1-k2-k3;
				q.emplace(pow(p[0],k0)*pow(p[1],k1)*pow(p[2],k2)*pow(p[3],k3),calc(k0,k1,k2,k3));
			}
	while(!q.empty()){
		double P=q.top().first;
		ll S=q.top().second;
		q.pop();
		if(S>1){
			ans+=P*2*(S/2);
			q.emplace(P*2,S/2);
		}
		if(S&1){
			if(q.empty()){break;}
			double Q=q.top().first;
			ll Z=q.top().second-1;
			q.pop();
			ans+=P+Q;
			q.emplace(P+Q,1);
			if(Z) q.emplace(Q,Z);
		}
	}
	printf("%.8lf\n",ans);
	return 0;
}
```

