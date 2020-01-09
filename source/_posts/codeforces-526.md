---
title: codeforces 526
date: 2020-01-09 16:53:02
tags:
- OI
- codeforces
- 解题报告
categories: 解题报告
---

## F.Pudding Monsters

[题目链接](https://codeforces.com/contest/526/problem/F)

​	一个区间$[l,r]$合法等价于$max-min-r+l=0$，从小到大枚举$r$，用线段树维护对于每一个$l$的$max-min-r+l$，当$r$增大的时候，首先对区间$[1,n]$减去1。

<!--more-->

​	用2个单调栈分别维护最大值和最小值，每次最大值和最小值会改变的都是一个后缀，修改单调栈时维护线段树。

​	因为$max-min-r+l$的值不会为负，线段树可以直接记录最小值以及最小值的个数，时间复杂度$O(n \log n)$。

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
const int N = 301000;
struct node{int l,r,num;};
int n,h[N];
struct segment_tree{
	int mn[N*4],s[N*4],tag[N*4];
	void build(int x=1,int l=1,int r=n){
		if(l==r){mn[x]=l;s[x]=1;return;}
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		mn[x]=l;s[x]=1;
	}
	void modify(int ql,int qr,int k,int x=1,int l=1,int r=n){
		if(ql<=l&&qr>=r){
			mn[x]+=k;tag[x]+=k;return;
		}
		int mid=l+r>>1;
		if(ql<=mid) modify(ql,qr,k,x<<1,l,mid);
		if(qr>mid) modify(ql,qr,k,x<<1|1,mid+1,r);
		mn[x]=mn[x<<1];s[x]=s[x<<1];
		if(mn[x<<1|1]<mn[x]) mn[x]=mn[x<<1|1],s[x]=s[x<<1|1];
		else if(mn[x<<1|1]==mn[x]) s[x]+=s[x<<1|1];
		mn[x]+=tag[x];
	}
	int query(){
		if(mn[1]==0) return s[1];
		return 0;
	}
}t;
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		int x,y;read(x);read(y);
		h[x]=y;
	}
	t.build();
	stack<node> s1,s2;
	ll ans=0;
	for(int i=1;i<=n;i++){
		t.modify(1,n,-1);
		while(!s1.empty()&&s1.top().num<=h[i]){
			t.modify(s1.top().l,s1.top().r,-s1.top().num);
			s1.pop();
		}
		while(!s2.empty()&&s2.top().num>=h[i]){
			t.modify(s2.top().l,s2.top().r,s2.top().num);
			s2.pop();
		}
		int k=s1.empty()?1:s1.top().r+1;
		t.modify(k,i,h[i]);
		s1.push({k,i,h[i]});
		k=s2.empty()?1:s2.top().r+1;
		t.modify(k,i,-h[i]);
		s2.push({k,i,h[i]});
		ans+=t.query();
	}
	cout<<ans<<'\n';
	return 0;
}
```

