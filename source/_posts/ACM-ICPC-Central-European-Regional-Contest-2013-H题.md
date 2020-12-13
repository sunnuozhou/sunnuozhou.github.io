---
title: ACM ICPC Central European Regional Contest 2013 H题
tags:
  - OI
  - codeforces
  - 计算几何
date: 2020-12-04 11:04:44
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100299)

将平面上的框按平行的平面分为3类，同一类的一定在一个集合。

于是就可以枚举划分的方案并检查了。

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
struct node{int a[2][3];};
int n;
vector<node> v[3];
int get_d(node p){
	for(int i:{0,1,2}) if(p.a[0][i]==p.a[1][i]) return i;
	cerr<<"error\n";return -1;
}
int check(vector<node>&a,vector<node>&b){
	if(a.empty()||b.empty()) return a.empty()^b.empty();
	int mx,mn;
	for(int k:{0,1,2}){
		mx=-1e9;mn=1e9;
		for(auto&p:a) mx=max(mx,p.a[0][k]),mn=min(mn,p.a[1][k]);
		for(auto&p:b) if(p.a[0][k]>=mn||p.a[1][k]<=mx) return 0;
	}
	return 1;
}
int main(){
	int T;read(T);
	while(T--){
		read(n);
		for(int i:{0,1,2}) v[i].clear();
		while(n--){
			node p;
			for(int i:{0,1})
				for(int j:{0,1,2})
					read(p.a[i][j]);
			for(int i:{0,1,2})
				if(p.a[0][i]>p.a[1][i]) swap(p.a[0][i],p.a[1][i]);
			v[get_d(p)].push_back(p);
		}
		int s=check(v[0],v[1])+check(v[0],v[2])+check(v[1],v[2]);
		puts(s>=2+(v[0].empty()||v[1].empty()||v[2].empty())?"YES":"NO");
	}
	return 0;
}


```

