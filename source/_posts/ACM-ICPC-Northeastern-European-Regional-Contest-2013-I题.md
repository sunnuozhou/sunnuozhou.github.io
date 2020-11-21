---
title: ACM ICPC Northeastern European Regional Contest 2013 I题
tags:
  - OI
  - codeforces
  - 交互
date: 2020-11-20 10:43:00
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100307/)

对于每一个速度维护当前火箭可能在的位置区间，每次询问时问总的火箭可能在的位置区间前一半（也就是二分），然后更新可能的位置区间。

如果可能的情况只剩下一个了就输出答案。

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
int n,l[N],r[N],tag[N];
int main(){
	int x;cin>>x>>x;
	n=1e5;
	for(int i=0;i<=n;i++) l[i]=0,r[i]=n;
	for(int t=0;;t++){
		int mn=1e9,mx=0;
		for(int i=0;i<=n;i++){
			if(tag[i]) continue;
			if(t*i+r[i]>mx) mx=t*i+r[i];
			if(t*i+l[i]<mn) mn=t*i+l[i];
			//cerr<<i<<' '<<l[i]<<' '<<r[i]<<'\n';
		}
		int mid=mn+mx>>1;
		cout<<"check"<<' '<<mn<<' '<<mid<<endl;
		string ans;cin>>ans;
		if(ans=="Yes") mx=mid;
		else mn=mid+1;
		ll cnt=0;
		for(int i=0;i<=n;i++){
			if(tag[i]) continue;
			if(mn-t*i>l[i]) l[i]=mn-t*i;
			if(mx-t*i<r[i]) r[i]=mx-t*i;
			if(l[i]>r[i]) tag[i]=1;
			else cnt+=r[i]-l[i]+1;
		}
		if(cnt==1){
			for(int i=0;i<=n;i++){
				if(tag[i]) continue;
				cout<<"answer"<<' '<<(t+1)*i+r[i]<<endl;
				return 0;
			}
		}
	}
	return 0;
}
```

