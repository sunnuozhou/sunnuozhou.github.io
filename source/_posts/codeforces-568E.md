---
title: codeforces 568E
tags:
  - OI
  - codeforces
  - DP
date: 2020-01-19 14:27:52
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/568/problem/E)

先像普通的最长上升子序列一样，对于每一个确定的位置求出$len_i$和$pre_i$，表示以$i$结尾的最长上升子序列有多长，和该子序列的上一个位置在哪。

对于不确定的位置，由于一个数被使用多次不会是答案增大，可以直接从大到小枚举用什么数字在填充这个位置，用$two-pointer$来维护答案。

然后考虑还原整个序列。从后往前考虑，记录$now$表示当前填到哪里，$L$表示最长子序列还有多长。如果位置$now$是确定的，直接跳到$pre_{now}$。

否则该位置填上比后一个数小的最大数字，令其为$p$。检查在$1\le i<now$中是否存在一个确定的位置满足$a_i<p$并且$len_i=L-1$。如果有，跳到该位置。如果没有，跳到前一个未确定的位置。

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
int a[N],f[N],w[N],pre[N],len[N],ans[N],b[N],n,m,used[N];
int main(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	memset(f,63,sizeof(f));f[0]=0;
	a[++n]=1e9+1;
	read(m);
	for(int i=1;i<=m;i++) read(b[i]);
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++)
		if(~a[i]){
			int k=lower_bound(f+1,f+n+1,a[i])-f;
			len[i]=k;pre[i]=w[k-1];
			f[k]=a[i];w[k]=i;
		}
		else{
			for(int j=m,now=n;j;j--){
				while(b[j]<=f[now]) now--;
				f[now+1]=b[j];w[now+1]=i;
			}
		}
	int now=n,L=len[n],lst=n;
	while(L){
		if(~a[now]){
			ans[now]=a[now];
			lst=now;
			now=pre[now];
			L--;
		}
		else{
			int p=m;
			while(b[p]>=ans[lst]||used[p]) p--;
			used[p]=1;
			ans[now]=b[p];lst=now;L--;
			if(!L) break;
			p=0;
			for(int i=1;i<now;i++)
				if(~a[i]&&len[i]==L&&a[i]<ans[now]){p=i;break;}
			if(p){now=p;continue;}
			now--;
			while(~a[now]) now--;
		}
	}
	//cerr<<len[n]-1<<'\n';
	for(int i=1;i<n;i++)
		if(ans[i]) cout<<ans[i]<<" \n"[i==n-1];
		else{
			if(~a[i]) cout<<a[i]<<" \n"[i==n-1];
			else{
				int p=m;
				while(used[p]) p--;
				used[p]=1;
				cout<<b[p]<<" \n"[i==n-1];
			}
		}
	return 0;
}


```

