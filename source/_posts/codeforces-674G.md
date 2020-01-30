---
title: codeforces 674G
tags:
  - OI
  - codeforces
  - 线段树
date: 2020-01-30 12:31:20
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/674/problem/G)

### 题目大意

给一个长为$n$个数组，$Q$组操作：

- 区间赋值
- 求出一个集合，必须包含一个区间中占到$p\%$的所有数。



### 数据范围

$n,Q\le 150000$

$20\le p \le 100$



### 解题过程

先考虑区间绝对众数，可以使用消去算法完成。即在线段树上，对每一个区间记录数字$x$和出现次数$y$，叶子节点的$x$为序列上对应位置的数，$y$为1。合并两个区间的时候，如果$x$相同，那么$y$相加，否则保留$y$较大的$x$，$y$变为原来两个区间的$y$的差的绝对值。

那么如果一个序列有绝对众数，就一定是整个区间的$x$，因为每消去一个$x$，就要消耗一个其他的数，由于$x$的数量比其他数加起来还多，$x$一定会留下来。

现在我们回到原问题上，考虑拓展这个算法。令$q=\lfloor \frac{100}{p}\rfloor$，线段树上每一个区间记录$q$个数字以及其出现次数，来储存所有可能出现超过$p\%$次的数字。考虑合并两个区间，现将两个区间中相同的数值的元素合并，然后如果元素个数大于$q$，将所有元素的出现次数减去1，直到元素个数不超过$q$。输出答案时就输出对应区间维护的所有（$q$个）元素。

<!--more-->

现在我们要证明所有在区间中占到$p\%$的元素一定会被保留。考虑一次全体减一，一定会有至少$q+1$个元素一起减一。换句话说，使一个数减一，需要消耗至少$q$个其他元素。由于$q=\lfloor \frac{100}{p}\rfloor$，而答案数字至少出现了$\lceil \frac{(r-l+1)*p}{100}\rceil$次，其他数字并不能将所有答案数字消去，所有答案数字一定会存在于输出的集合中。

时间复杂度$O(nq^2\log n)$，其中$q$最大为5。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 201000;
int n,m,P,Q,a[N];
struct info{int val,siz;};
struct node{
	int n;info p[11];
	node (){n=0;}
	info& operator [](int x){
		return p[x];
	}
};
node operator + (node a,node b){
	node ans=a;
	for(int i=1;i<=b.n;i++){
		int flag=1;
		for(int j=1;j<=ans.n;j++) if(ans[j].val==b[i].val) flag=0,ans[j].siz+=b[i].siz;
		if(flag) ans[++ans.n]=b[i];
	}
	sort(ans.p+1,ans.p+ans.n+1,[](info a,info b){
		return a.siz>b.siz;
	});
	if(ans.n>=Q){
		for(int i=ans.n;i>=Q;i--)
			for(int j=1;j<=i;j++)
				ans[j].siz-=ans[i].siz;
		while(ans.n&&ans[ans.n].siz<=0) ans.n--;
	}
	return ans;
}
struct segment_tree{
	int tag[N*4];
	node p[N*4];
	void build(int x=1,int l=1,int r=n){
		if(l==r){p[x].n=1;p[x][1]={a[l],1};return;}
		int mid=l+r>>1;
		build(x<<1,l,mid);build(x<<1|1,mid+1,r);
		p[x]=p[x<<1]+p[x<<1|1];
	}
	void pushdown(int x,int ls,int rs){
		p[x<<1].n=1;p[x<<1][1]={tag[x],ls};tag[x<<1]=tag[x];
		p[x<<1|1].n=1;p[x<<1|1][1]={tag[x],rs};tag[x<<1|1]=tag[x];
		tag[x]=0;
	}
	void modify(int ql,int qr,int k,int x=1,int l=1,int r=n){
		if(ql<=l&&qr>=r){
			tag[x]=k;p[x].n=1;p[x][1]={tag[x],r-l+1};
			return;
		}
		int mid=l+r>>1;
		if(tag[x]) pushdown(x,mid-l+1,r-mid);
		if(ql<=mid) modify(ql,qr,k,x<<1,l,mid);
		if(qr>mid) modify(ql,qr,k,x<<1|1,mid+1,r);
		p[x]=p[x<<1]+p[x<<1|1];
	}
	node query(int ql,int qr,int x=1,int l=1,int r=n){
		if(ql<=l&&qr>=r) return p[x];
		int mid=l+r>>1;node now;
		if(tag[x]) pushdown(x,mid-l+1,r-mid);
		if(ql<=mid) now=query(ql,qr,x<<1,l,mid);
		if(qr>mid) now=now+query(ql,qr,x<<1|1,mid+1,r);
		return now;
	}
}t;
int main(){
	read(n);read(m);read(P);
	Q=1+100/P;
	for(int i=1;i<=n;i++) read(a[i]);
	t.build();
	while(m--){
		int opt;read(opt);
		if(opt==1){
			int l,r,k;read(l);read(r);read(k);
			t.modify(l,r,k);
		}
		else{
			int l,r;read(l);read(r);
			auto ans=t.query(l,r);
			cout<<ans.n<<' ';
			for(int i=1;i<=ans.n;i++) cout<<ans[i].val<<' ';
			cout<<'\n';
		}
	}
	return 0;
}
```

