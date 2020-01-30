---
title: codeforces 671E
tags:
  - OI
  - codeforces
  - 线段树
  - 贪心
date: 2020-01-30 12:37:30
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/671/problem/E)

### 题目大意

给定一条$n$个点的赛道，从$i$号点到$i+1$号点要使用$w_i$升油，每当你经过$i$号点，可以获得$g_i$升的油，油箱没有上限。

现在你可以增加$g_i$的值，但总增加量不能超过$K$。

你要找到一个最长的区间$l,r$，使得在初始没有油的情况下，既可以从$l$不转向走到$r$，也可以从$r$不转向走到$l$。



### 数据范围

$n\le 100000,K,w_i,g_i\le10^9$



### 解题过程

先求出$K=0$情况下只考虑向右走，第$i$个点能走到的最右的点$nxt_i$。如果你从$i$出发，当你想增加$g_i$的时候，一定会增加$g_{nxt_i}$的值使得$i\to nxt_i+1$，持续此过程，因为如果在$nxt_i$右边的点添加，$i$并不能走到，没有贡献，如果在$nxt_i$左边添加，需要的油量不会减少，但是以后从右向左走的时候会变得困难。

建一棵以$n+1$为根的树，$i$号点的父亲是$nxt_i+1$。因为每一次添加油都是在$nxt_i$处修改，并且以没有剩余油量的状态走到$nxt_i+1$，所以考虑一边$dfs$一边解决问题，做到$x$时，所有$x$的祖先以及$x$自己的$nxt$位置上$g$的值已经被添加过了，而其他位置不变，记为$g'$。

现在先记录一个前缀和数组$pre$。

$pre_i=pre_{i-1}+g_i-w_i$

那么$i\to nxt_i+1$的时候，需要在$nxt_i$添加的油量就是$pre_{nxt_i}-pre_{i-1}$。

<!--more-->

可以推断出从$a$向右走到$b$需要的额外油量是$max(pre_j,a\le j<b)-pre_{a-1}$，假设当前在树上$dfs$到了$x$点，记录$cost_{i,i\ge x}$表示从$x$向右走到$i$需要的额外油量。

再记录一个前缀和数字$suf$。

$suf_i=suf_{i-1}+g'_i-w_{i-1}$。

假设当前做到$x$，那么右端点可行等价于$max(suf_j,x\le j< i)-（suf_i-g'_i+g_i）+cost_{i-1}\le K$且$cost_{i-1}\le K$。

现在我们要考虑维护这个东西。首先令$p_i=(suf_i-g'_i+g_i)+cost_{i-1}$，这个值是不会随着$g'$的变化而改变的。建立一棵线段树，每一个节点维护下面3个东西：

$minp$，表示最小的$p_i,l\le i\le r$。

$maxs$，表示最大的$suf_i,l\le i \le r$

$h$,表示$min(max(suf_j,l\le j< i)+p_i,l\le i\le r)$。

其中$minp$是不变的，对$maxs$的修改相当于区间加。而最关键的部分是维护$h$，这里可以采用李超线段树来完成。对于一个区间的$h_x$，考虑递归计算它。

```cpp
long long calc(int x,int l,int r,long long left_maxs){
    //其中left_maxs表示区间左边的suf最大值
    if(l==r) return minp[x]+maxs;
	if(left_maxs>=maxs[lson]) return min(h[x],calc(lson,l,mid,left_maxs));
    else return min(left_maxs+minp[x],calc(rson,mid+1,r,left_maxs))
}
```

通过比较左侧$maxs$的影响，只递归一侧来在$O(\log n)$时间算出$h_x$。

求答案的时候可以在线段树上二分来完成。

总时间复杂度$O(n \log^2 n)$。

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
int st[N],top,n,w[N],g[N],nxt[N];
ll pre[N],suf[N],K,ans;
vector<int> e[N];
struct segment_tree{
	ll ms[N*4],mp[N*4],h[N*4],tag[N*4];
	void add(int x,ll k){
		ms[x]+=k;
		tag[x]+=k;
		h[x]+=k;
	}
	void pushdown(int x){
		if(!tag[x]) return;
		add(x<<1,tag[x]);
		add(x<<1|1,tag[x]);
		tag[x]=0;
	}
	ll calc(int x,int l,int r,ll k){
		if(l==r) return k+mp[x];
		pushdown(x);
		int mid=l+r>>1;
		if(k<=ms[x<<1]) return min(h[x],calc(x<<1,l,mid,k));
		else return min(k+mp[x],calc(x<<1|1,mid+1,r,k));
	}
	void pushup(int x,int l,int r){
		ms[x]=max(ms[x<<1],ms[x<<1|1]);
		int mid=l+r>>1;
		h[x]=calc(x<<1|1,mid+1,r,ms[x<<1]);
	}
	void build(int x=1,int l=1,int r=n){
		if(l==r){
			mp[x]=-suf[l];
			ms[x]=suf[l];
			return;
		}
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		mp[x]=min(mp[x<<1],mp[x<<1|1]);
		pushup(x,l,r);
	}
	void modify(int ql,int qr,ll k,int x=1,int l=1,int r=n){
		if(ql<=l&&qr>=r){
			add(x,k);return;
		}
		int mid=l+r>>1;
		pushdown(x);
		if(ql<=mid) modify(ql,qr,k,x<<1,l,mid);
		if(qr>mid) modify(ql,qr,k,x<<1|1,mid+1,r);
		pushup(x,l,r);
	}
	ll query(ll k=-1e17,int x=1,int l=1,int r=n){
		if(l==r) return k+mp[x]<=K?l:0;
		int mid=l+r>>1;
		pushdown(x);
		ll tmp=k<=ms[x<<1]?h[x]:calc(x<<1|1,mid+1,r,k);
		if(tmp<=K) return query(max(ms[x<<1],k),x<<1|1,mid+1,r);
		return query(k,x<<1,l,mid);
	}
}t;
void dfs(int x,int dad){
	st[++top]=x;
	if(dad){
		t.modify(dad-1,n,-pre[dad-1]+pre[x-1]);
		int l=1,r=top+1;
		while(l+1<r){
			int mid=l+r>>1;
			if(pre[x-1]-pre[st[mid]-1]<=K) r=mid;
			else l=mid;
		}
		if(x>1) t.modify(1,x-1,-1e17);
		if(st[l]<=n) t.modify(st[l],n,1e17);
		ans=max(ans,t.query()-x+1);
		if(x>1) t.modify(1,x-1,1e17);
		if(st[l]<=n) t.modify(st[l],n,-1e17);
	}
	for(int v:e[x]) if(v!=dad) dfs(v,x);
	if(dad) t.modify(dad-1,n,-pre[x-1]+pre[dad-1]);
	top--;
}
int main(){
	read(n);read(K);
	for(int i=1;i<n;i++) read(w[i]);
	for(int i=1;i<=n;i++) read(g[i]);
	for(int i=1;i<=n;i++)
		pre[i]=pre[i-1]-w[i]+g[i],suf[i]=suf[i-1]-w[i-1]+g[i];
	t.build();
	for(int i=n;i;i--){
		nxt[i]=i;
		while(nxt[i]<n&&pre[nxt[i]]-pre[i-1]>=0) nxt[i]=nxt[nxt[i]+1];
		e[nxt[i]+1].push_back(i);
	}
	dfs(n+1,0);
	cout<<ans<<'\n';
	return 0;
}
 
```

