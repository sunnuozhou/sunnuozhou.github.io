---
title: ACM ICPC World Finals 2014 B题
tags:
  - OI
  - codeforces
  - DP
  - 斜率优化
  - 贪心
date: 2020-10-19 12:04:00
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101221/attachments)

把`discrete dish`和`continuous dish`分开来做。

对于`discrete dish`，考虑背包。如果 $\Delta t=0$，那这就是个无限背包，但由于 $\Delta t$ 的影响，要改为用斜率优化来优化普通背包。

对于`continous dish`，考虑贪心。可以注意到最优策略一定是每次取最大的，于是就二分最大值被减小到多少时用到了 $W$ 的体积。

注意特判 $\Delta t=0$ 的情况。

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
int n,W;
struct solve_D{
	int n,val[310],d[310],a[310],q[10010];
	ll f[10010],g[10010];
	void push(int w,int t,int dt){
		n++;
		a[n]=w;val[n]=t;d[n]=dt;
	}
	ll get_v(int len,int T,int dT){
		return 1ll*(T+T-dT*(len-1))*len/2;
	}
	double get_t(int k1,int k2,int i,int res){
		return k2+1.*(f[k1*a[i]+res]+get_v(k2-k1,val[i],d[i])-f[k2*a[i]+res])/(d[i]*(k2-k1));
	}
	void solve(){
		memset(f,192,sizeof(f));f[0]=0;
		for(int i=1;i<=n;i++){
			for(int k=0;k<a[i];k++){
				int l=1,r=0;
				if(d[i]==0){
					for(int j=0;j*a[i]+k<=W;j++)
						if(j) g[j*a[i]+k]=f[j*a[i]+k]=max(f[j*a[i]+k],f[j*a[i]+k-a[i]]+val[i]);
						else g[j*a[i]+k]=f[j*a[i]+k];
					continue;
				}
				for(int j=0;j*a[i]+k<=W;j++){
					while(l+1<=r&&f[q[l]*a[i]+k]+get_v(j-q[l],val[i],d[i])<=f[q[l+1]*a[i]+k]+get_v(j-q[l+1],val[i],d[i])) l++;
					ll tmp;
					if(l<=r) tmp=f[q[l]*a[i]+k]+get_v(j-q[l],val[i],d[i]);
					else tmp=-1e18;
					while(l+1<=r&&get_t(q[r-1],q[r],i,k)>=get_t(q[r-1],j,i,k)) r--;
					q[++r]=j;
					g[j*a[i]+k]=max(f[j*a[i]+k],tmp);
				}
			}
			for(int j=0;j<=W;j++) f[j]=g[j];
		//	cerr<<"*********************\n";
		//	for(int j=0;j<=W;j++) cerr<<j<<' '<<f[j]<<'\n';
		}
	}
}SolD;
struct solve_C{
	pair<int,int> p[310];
	int n;
	void push(int T,int dT){
		n++;
		p[n]=make_pair(T,dT);
	}
	void solve(){
		sort(p+1,p+n+1,greater<pair<int,int> >());
		double now=0,ans=SolD.f[W],val=0;
		if(n)
		for(int i=0;i<=W;i++){
			double l=-100000000,r=p[1].first;
			for(int t=60;t;t--){
				double mid=(l+r)/2;
				double now=0;
				for(int j=1;j<=n;j++)
					if(p[j].first>=mid){
						if(p[j].second) now+=1.*(p[j].first-mid)/p[j].second;
						else now+=W;
					}
				if(now>=i) l=mid;
				else r=mid;
			}
			double now=0,siz=0;
			for(int j=1;j<=n;j++)
				if(p[j].first>=l){
					if(p[j].second){
						now+=1.*(p[j].first-l)*(p[j].first+l)/p[j].second/2,siz+=1.*(p[j].first-l)/p[j].second;
					}
				}
			now+=(i-siz)*l;
			ans=max(ans,now+SolD.f[W-i]);
		}
		if(ans<-1e16) puts("impossible");
		else printf("%.9lf\n",ans);
	}
}SolC;
int main(){
	read(n);read(W);
	for(int i=1;i<=n;i++){
		char typ;scanf(" %c",&typ);
		if(typ=='D'){
			int w,t,dt;read(w);read(t);read(dt);
			SolD.push(w,t,dt);
		}
		else{
			int t,dt;read(t);read(dt);
			SolC.push(t,dt);
		}
	}
	SolD.solve();
	SolC.solve();
	return 0;
}
```

