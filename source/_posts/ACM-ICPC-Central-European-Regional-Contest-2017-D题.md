---
title: ACM ICPC Central European Regional Contest 2017 D题
tags:
  - OI
  - codeforces
date: 2020-11-24 11:41:49
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101620)

考虑维护 $h_x$ 表示在 $(x,1)$ 处，走 $C$ 步到哪里。如果维护了这个，就可以轻松算出答案。

对于一次修改，如果修改了 $(x,y)$，那么先重新统计 $(x-1,y-1),(x,y-1),(x+1,y-1)$ 走到最右边一列的哪里，再统计最左边的哪些位置可以走到 $(x-1,y-1),(x,y-1),(x+1,y-1)$，这可以通过维护分界点来做到。

时间复杂度 $O(m\max(R,C))$。

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
const int N = 2020;
int a[N][N],R,C,vis[N],h[N],X,Y;
char typ[N];
int nxt(int x){return (x+1)%R;}
int pre(int x){return (x+R-1)%R;}
int get_step(int x,int y){
	int mx=max(a[nxt(x)][(y+1)%C],max(a[x][(y+1)%C],a[pre(x)][(y+1)%C]));
	if(a[nxt(x)][(y+1)%C]==mx) return nxt(x); 
	if(a[x][(y+1)%C]==mx) return x; 
	return pre(x); 
}
int getf(int x,int y){
	while(y+1<C){
		x=get_step(x,y);
		y++;
	}
	return x;
}
int getw(int x,int y){
	while(y>0){
		int k1=get_step((x%R+R)%R,y-1),k2=get_step((x%R+R+1)%R,y-1);
		if(k1==nxt((x%R+R)%R)) x--;
		else if(k2==(x%R+R)%R) x++;
		y--;
	}
	return x;
}
void Move(int k){
	if(k>=C-Y){
		k-=C-Y;
		X=get_step(getf(X,Y),C-1);Y=0;
	}
	memset(vis,0,sizeof(vis));
	int len=-1,tim=0;
	while(k>=C){
		if(vis[X]&&len<0){
			len=tim-vis[X]+1;
			k%=len*C;
			if(k<C) break;
		}
		vis[X]=++tim;
		k-=C;
		X=get_step(h[X],C-1);
	}
	while(k--){
		X=get_step(X,Y);Y=(Y+1)%C;
	}
	printf("%d %d\n",X+1,Y+1);
}
int main(){
	read(R);read(C);
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			read(a[i][j]);
	for(int i=0;i<R;i++)
		h[i]=getf(i,0);
	int m;read(m);
	while(m--){
	//	for(int i=0;i<R;i++) 
	//		cerr<<i<<' '<<h[i]<<'\n';
		scanf(" %s",typ);
		if(typ[0]=='m'){
			int k;read(k);Move(k);
		}
		else{
			int x,y,k;read(x);read(y);read(k);
			x--;y--;
			a[x][y]=k;
			if(y==0) continue;
			int p1=getw(x-2,y-1),p2=getw(x-1,y-1),p3=getw(x,y-1),p4=getw(x+1,y-1);
	//		cerr<<"p"<<' '<<p1<<' '<<p2<<' '<<p3<<' '<<p4<<'\n';
			int f1=getf(pre(x),y-1),f2=getf(x,y-1),f3=getf(nxt(x),y-1);
	//		cerr<<"f"<<' '<<f1<<' '<<f2<<' '<<f3<<'\n';
			for(int i=p1+1;i<=p2;i++)
				h[(i%R+R)%R]=f1;
			for(int i=p2+1;i<=p3;i++)
				h[(i%R+R)%R]=f2;
			for(int i=p3+1;i<=p4;i++)
				h[(i%R+R)%R]=f3;
		/*	for(int i=0;i<R;i++)
				if(h[i]!=getf(i,0)){
					cerr<<"!!"<<' '<<i<<' '<<h[i]<<' '<<getf(i,0)<<'\n';
					return 1;
				}*/
		}
	}
	return 0;
}
```

