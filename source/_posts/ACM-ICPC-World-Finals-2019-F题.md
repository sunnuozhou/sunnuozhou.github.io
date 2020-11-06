---
title: ACM ICPC World Finals 2019 F题
tags:
  - OI
  - codeforces
  - DP
  - 线段树
date: 2020-11-04 11:49:09
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102511/problem/F)

首先存在一个顺序，满足水一定不会从前面的线段落到后面的线段上。可以用扫描线求出这个顺序。

接着考虑DP，记 $f_x$ 表示水从 $x$ 处落下，到目标区间需要几个洞。转移的形式是一次区间加和一个从左到右或从右到左的 $\operatorname{chkmin}$。使用线段树维护即可。

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
const int N = 1001000,inf = 1e9;
struct node{int lx,ly,rx,ry,num;}p[N];
int B[N*2],cnt,tot,n,L,R,nowX,nxt[N];
pair<int,int> b[N];
double get_val(const node&a){
	double l=nowX-a.lx,r=a.rx-nowX;
	return (a.ry*l+a.ly*r)/(l+r);
}
bool operator < (const node&a,const node&b){
	return get_val(a)>get_val(b);
}
struct segment_tree{
	int ad[N*8],tag[N*8],mn[N*8],val,d[N*8];
	void build(int x,int l=1,int r=tot){
		tag[x]=inf;
		mn[x]=r<L||l>R?inf:0;
		if(l==r) return;
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
	}
	void do_add(int x,int k){
		mn[x]+=k;
		ad[x]+=k;
		if(tag[x]<inf) tag[x]+=k;
	}
	void mdy(int x,int k,int D){
		mn[x]=min(mn[x],k);
		if(tag[x]>=inf){tag[x]=k;d[x]=D;return;}
		if(D!=d[x]) tag[x]=mn[x];
		else tag[x]=min(tag[x],k);
	}
	void pushdown(int x){
		if(ad[x]){
			do_add(x<<1,ad[x]);
			do_add(x<<1|1,ad[x]);
			ad[x]=0;
		}
		if(tag[x]!=inf){
			if(d[x]){
				mdy(x<<1,tag[x],d[x]);
				mdy(x<<1|1,mn[x<<1],d[x]);
			}
			else{
				mdy(x<<1|1,tag[x],d[x]);
				mdy(x<<1,mn[x<<1|1],d[x]);
			}
			tag[x]=inf;
		}
	}
	void modify_L(int ql,int qr,int x=1,int l=1,int r=tot){
		if(ql<=l&&qr>=r){
			mdy(x,val,1);
			val=mn[x];
			return;
		}
		pushdown(x);
		int mid=l+r>>1;
		if(ql<=mid) modify_L(ql,qr,x<<1,l,mid);
		if(qr>mid) modify_L(ql,qr,x<<1|1,mid+1,r);
		mn[x]=min(mn[x<<1],mn[x<<1|1]);
	}
	void modify_R(int ql,int qr,int x=1,int l=1,int r=tot){
		if(ql<=l&&qr>=r){
			mdy(x,val,0);
			val=mn[x];
			return;
		}
		pushdown(x);
		int mid=l+r>>1;
		if(qr>mid) modify_R(ql,qr,x<<1|1,mid+1,r);
		if(ql<=mid) modify_R(ql,qr,x<<1,l,mid);
		mn[x]=min(mn[x<<1],mn[x<<1|1]);
	}
	void add(int ql,int qr,int k,int x=1,int l=1,int r=tot){
		if(ql<=l&&qr>=r){
			do_add(x,k);
			return;
		}
		pushdown(x);
		int mid=l+r>>1;
		if(qr>mid) add(ql,qr,k,x<<1|1,mid+1,r);
		if(ql<=mid) add(ql,qr,k,x<<1,l,mid);
		mn[x]=min(mn[x<<1],mn[x<<1|1]);
	}
	int query(int ql,int qr,int x=1,int l=1,int r=tot){
		if(ql<=l&&qr>=r) return mn[x];
		pushdown(x);
		int mid=l+r>>1,ans=1e9;
		if(ql<=mid) ans=query(ql,qr,x<<1,l,mid);
		if(qr>mid) ans=min(ans,query(ql,qr,x<<1|1,mid+1,r));
		return ans;
	}
}t;
int main(){
	read(L);read(R);read(n);
	for(int i=1;i<=n;i++){
		int x1,y1,x2,y2;read(x1);read(y1);read(x2);read(y2);
		if(x1>x2) swap(x1,x2),swap(y1,y2);
		p[i]={x1,y1,x2,y2,i};
		b[++cnt]=make_pair(x1,-i);
		b[++cnt]=make_pair(x2,i);
		B[++tot]=x1*2;
		B[++tot]=x2*2;
		B[++tot]=x2*2+1;
	}
	B[++tot]=L*2;B[++tot]=R*2;
	sort(b+1,b+cnt+1);
	sort(B+1,B+tot+1);
	tot=unique(B+1,B+tot+1)-B-1;
	set<node> S;
	nowX=0;
	for(int i=1;i<=cnt;i++){
		nowX=b[i].first;
		if(b[i].second<0){
			auto k=S.upper_bound(p[-b[i].second]);
			int now=k==S.end()?n+1:k->num;
			nxt[-b[i].second]=nxt[now];
			nxt[now]=-b[i].second;
			S.insert(p[-b[i].second]);
		}
		else S.erase(p[b[i].second]);
	}
	for(int i=1;i<=n;i++){
		p[i].lx=lower_bound(B+1,B+tot+1,p[i].lx*2)-B;
		p[i].rx=lower_bound(B+1,B+tot+1,p[i].rx*2)-B;
	}
	L=lower_bound(B+1,B+tot+1,L*2)-B;
	R=lower_bound(B+1,B+tot+1,R*2)-B;
	t.build(1);
	for(int i=nxt[n+1];i;i=nxt[i]){
		if(p[i].ly<p[i].ry){
			t.add(p[i].lx+1,p[i].rx,1);
			t.val=1e7;
			t.modify_L(p[i].lx,p[i].rx);
		}
		else{
			t.add(p[i].lx,p[i].rx-1,1);
			t.val=1e7;
			t.modify_R(p[i].lx,p[i].rx);
		}
	//	for(int j=1;j<=tot;j++) cerr<<t.query(j,j)<<' ';
	//	cerr<<'\n';
	}
	cout<<t.query(L,R)<<'\n';
	return 0;
}
```

