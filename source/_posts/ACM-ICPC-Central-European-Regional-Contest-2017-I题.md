---
title: ACM ICPC Central European Regional Contest 2017 I题
tags:
  - OI
  - codeforces
  - 线段树
  - 单调队列
date: 2020-11-25 10:48:15
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101620)

一个连续子序列合法的条件是 $(max-min)-(r-l)=0$，并且对于任何连续子序列 $(max-min)-(r-l)\ge 0$，于是可以通过右移右端点，用单调栈和线段树维护每个左端点的 $(max-min)-(r-l)$，并通过线段树上二分来找到合法的区间。

可以证明，合法的区间要么不交要么包含，所以可以将询问离线，在右端点处插入询问，当出现一个包含询问区间的合法区间时，就查询该询问，这时查到的答案一定是最优的。

时间复杂度 $O(n\log n)$。

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
int n,a[N],Q;
pair<int,int> ans[N];
vector<pair<int,int> > q[N];
set<pair<int,int>,greater<pair<int,int> > > S;
struct segment_tree{
	int tag[N*4],mn[N*4];
	void modify(int ql,int qr,int k,int x=1,int l=1,int r=n){
		if(ql<=l&&qr>=r){
			tag[x]+=k;mn[x]+=k;
			return;
		}
		int mid=l+r>>1;
		if(ql<=mid) modify(ql,qr,k,x<<1,l,mid);
		if(qr>mid) modify(ql,qr,k,x<<1|1,mid+1,r);
		mn[x]=min(mn[x<<1],mn[x<<1|1])+tag[x];
	}
	int queryL(int ql,int qr,int k,int x=1,int l=1,int r=n){
		if(mn[x]>k) return n+1;
		if(l==r) return l;
		k-=tag[x];
		int mid=l+r>>1,tmp;
		if(ql<=mid&&(tmp=queryL(ql,qr,k,x<<1,l,mid))<=n) return tmp;
		return queryL(ql,qr,k,x<<1|1,mid+1,r);
	}
	int queryR(int ql,int qr,int k,int x=1,int l=1,int r=n){
		if(mn[x]>k) return -1;
		if(l==r) return l;
		k-=tag[x];
		int mid=l+r>>1,tmp;
		if(qr>mid&&(tmp=queryR(ql,qr,k,x<<1|1,mid+1,r))>=0) return tmp;
		return queryR(ql,qr,k,x<<1,l,mid);
	}
}t;
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]),t.modify(i,i,i);
	read(Q);
	for(int i=1;i<=Q;i++){
		int l,r;read(l);read(r);
		q[r].emplace_back(l,i);
	}
	stack<int> q1,q2;
	for(int i=1;i<=n;i++){
		while(q1.size()&&a[q1.top()]<a[i]){
			int k=q1.top();q1.pop();
			t.modify(q1.size()?q1.top()+1:1,k,-a[k]);
		}
		t.modify(q1.size()?q1.top()+1:1,i,a[i]);
		q1.push(i);
		while(q2.size()&&a[q2.top()]>a[i]){
			int k=q2.top();q2.pop();
			t.modify(q2.size()?q2.top()+1:1,k,a[k]);
		}
		t.modify(q2.size()?q2.top()+1:1,i,-a[i]);
		q2.push(i);
		for(auto&pr:q[i]) S.insert(pr);
		int w=t.queryL(1,i,i);
		while(S.size()&&S.begin()->first>=w){
			ans[S.begin()->second].second=i;
			ans[S.begin()->second].first=t.queryR(1,S.begin()->first,i);
			S.erase(S.begin());
		}
	}
	for(int i=1;i<=Q;i++)
		cout<<ans[i].first<<' '<<ans[i].second<<'\n';
	return 0;
}


```

