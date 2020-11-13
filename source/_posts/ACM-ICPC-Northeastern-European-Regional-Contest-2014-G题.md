---
title: ACM ICPC Northeastern European Regional Contest 2014 G题
tags:
  - OI
  - codeforces
  - 搜索
  - 乱搞
date: 2020-11-12 16:30:04
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100553)

很有意思的题，我写了个估价函数+对抗搜索来做它。每天写了一点，一共写了3天。

估价函数除了题面里的算法提到的东西，还考虑了活3和活4的情况，并且降低了防守的优先级，在只使用估价函数的情况下，对题面里的算法有后手88/100的胜率。

再加上对抗搜索，搜了5层，对题目里的算法有98/100的胜率，在把对面下的位置由自己算变成由对面的算法算后，就可以有100/100的后手胜率了。

没有搜很多次，一局的平均用时为0.15s。

upd:在多搜几层后就可以不针对对方获得100/0了，用时2.8s。

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
int LEN=19;
struct game{
	int a[20][20],tag,s[20][20][4][2],mxx,mnx,mxy,mny;
	void clear(){
		memset(s,0,sizeof(s));
		memset(a,0,sizeof(a));tag=0;
		mnx=mxx=mny=mxy=10;
	}
	game(){
		clear();
	}
	void print(){
		cerr<<"********************************************\n";
		cerr<<"  ";
		for(int i=1;i<=LEN;i++) cerr<<' '<<i%10;cerr<<'\n';
		for(int i=1;i<=LEN;i++){
			cerr<<i%10<<' ';
			for(int j=1;j<=LEN;j++)
				cerr<<' '<<".#@"[a[i][j]];
			cerr<<'\n';
		}
	}
	void set(int x,int y){
		assert(a[x][y]==0);
		a[x][y]=tag+1;
		mxx=max(mxx,x);mnx=min(mnx,x);
		mxy=max(mxy,y);mny=min(mny,y);
		int tx=x,ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][0][tag]++;
			tx--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][1][tag]++;
			ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][2][tag]++;
			tx--;ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty>LEN) break;
			s[tx][ty][3][tag]++;
			tx--;ty++;
		}
		tag^=1;
	}
	void reset(int x,int y){
		//not back up mn mx
		assert(a[x][y]==(tag^1)+1);
		a[x][y]=0;tag^=1;	
		int tx=x,ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][0][tag]--;
			tx--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][1][tag]--;
			ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty<1) break;
			s[tx][ty][2][tag]--;
			tx--;ty--;
		}
		tx=x;ty=y;
		for(int i=1;i<=5;i++){
			if(tx<1||ty>LEN) break;
			s[tx][ty][3][tag]--;
			tx--;ty++;
		}
	}
	int finish(){
		for(int i=1;i<=LEN;i++)
			for(int j=1;j<=LEN;j++)
				for(int k=0;k<4;k++){
					if(s[i][j][k][1]==5) return 2;
					if(s[i][j][k][0]==5) return 1;
				}
		return 0;
	}
};
class opponent_AI{
	double p[20][20];
	double calc(game&G){
		double ans=0;
		double P[11];P[0]=1;
		for(int i=1;i<=10;i++) P[i]=P[i-1]*50;
		for(int i=1;i<=LEN;i++)
			for(int j=1;j<=LEN-4;j++){
				if(G.s[i][j][1][0]&&G.s[i][j][1][1]) continue;
				if(G.s[i][j][1][G.tag^1]) ans+=P[G.s[i][j][1][G.tag^1]*2-1];
				else ans-=P[G.s[i][j][1][G.tag]*2];
			}
		for(int i=1;i<=LEN-4;i++)
			for(int j=1;j<=LEN;j++){
				if(G.s[i][j][0][0]&&G.s[i][j][0][1]) continue;
				if(G.s[i][j][0][G.tag^1]) ans+=P[G.s[i][j][0][G.tag^1]*2-1];
				else ans-=P[G.s[i][j][0][G.tag]*2];
			}
		for(int i=1;i<=LEN-4;i++)
			for(int j=1;j<=LEN-4;j++){
				if(G.s[i][j][2][0]&&G.s[i][j][2][1]) continue;
				if(G.s[i][j][2][G.tag^1]) ans+=P[G.s[i][j][2][G.tag^1]*2-1];
				else ans-=P[G.s[i][j][2][G.tag]*2];
			}
		for(int i=1;i<=LEN-4;i++)
			for(int j=5;j<=LEN;j++){
				if(G.s[i][j][3][0]&&G.s[i][j][3][1]) continue;
				if(G.s[i][j][3][G.tag^1]) ans+=P[G.s[i][j][3][G.tag^1]*2-1];
				else ans-=P[G.s[i][j][3][G.tag]*2];
			}
		return ans;
	}
	public:
	vector<pair<int,int> > get_nxts(game G){
		memset(p,0,sizeof(p));
		vector<pair<int,int> > V;
		for(int i=max(1,G.mnx-1);i<=min(G.mxx+1,LEN);i++)
			for(int j=max(1,G.mny-1);j<=min(G.mxy+1,LEN);j++){
				if(G.a[i][j]) continue;
				G.set(i,j);
				p[i][j]=calc(G)+rand()%2500;
				V.emplace_back(i,j);
				G.reset(i,j);
			}
		sort(V.begin(),V.end(),[&](pair<int,int> a,pair<int,int> b){
			return p[a.first][a.second]>p[b.first][b.second];
		});
		return V;
	}
};
class my_AI{
	int Debug,h[20][20];
	double p[20][20];
	public:
	double calc(game&G){
		double mP[6]={0,10,20000,50000,9e5,1e100};
		double oP[6]={0,-100,-49990,-2e6,-1e40,-1e100};
		double ans=0;
		int mC=0,oC=0,dx=0,dy=-1,tag=1;
		memset(h,0,sizeof(h));
		for(int i=1;i<=LEN;i++){
			for(int j=1;j<=LEN-4;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		memset(h,0,sizeof(h));
		dx=-1;dy=0;tag=0;
		for(int i=1;i<=LEN-4;i++){
			for(int j=1;j<=LEN;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		memset(h,0,sizeof(h));
		dx=-1;dy=-1;tag=2;
		for(int i=1;i<=LEN-4;i++){
			for(int j=1;j<=LEN-4;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		memset(h,0,sizeof(h));
		dx=-1;dy=1;tag=3;
		for(int i=1;i<=LEN-4;i++){
			for(int j=5;j<=LEN;j++){
				if(G.s[i][j][tag][0]&&G.s[i][j][tag][1]) continue;
				int mS=G.s[i][j][tag][G.tag^1],oS=G.s[i][j][tag][G.tag];
				if(mS) ans+=mP[mS];
				else ans+=oP[oS];
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=4&&G.s[i+dx][j+dy][tag][G.tag^1]>=4&&!G.s[i+dx][j+dy][tag][G.tag]) ans+=1e30;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=4&&G.s[i+dx][j+dy][tag][G.tag]>=4&&!G.s[i+dx][j+dy][tag][G.tag^1]) ans-=1e50;
				if(i+dx>0&&j+dy>0&&j+dy<20&&mS>=3&&G.s[i+dx][j+dy][tag][G.tag^1]>=3&&!G.s[i+dx][j+dy][tag][G.tag]&&!h[i+dx][j+dy]) mC++,h[i][j]=1;
				if(i+dx>0&&j+dy>0&&j+dy<20&&oS>=3&&G.s[i+dx][j+dy][tag][G.tag]>=3&&!G.s[i+dx][j+dy][tag][G.tag^1]&&!h[i+dx][j+dy]) oC++,h[i][j]=1;
			}
		}
		if(Debug) cerr<<oC<<' '<<mC<<'\n';
		if(oC>0) ans-=1e13;
		if(oC>1) ans-=1e25;
		if(mC>0) ans+=2e7;
		if(mC>1) ans+=1e10;
		return ans;
	}
	my_AI(){Debug=0;}
	vector<pair<int,int> > get_nxts(game G){
		memset(p,0,sizeof(p));
		vector<pair<int,int> > V;
		int lx=max(1,G.mnx-1),rx=min(G.mxx+1,LEN);
		int ly=max(1,G.mny-1),ry=min(G.mxy+1,LEN);
		for(int i=lx;i<=rx;i++)
			for(int j=ly;j<=ry;j++){
				if(G.a[i][j]) continue;
				G.set(i,j);
				p[i][j]=calc(G);
				V.emplace_back(i,j);
				G.reset(i,j);
			}
		sort(V.begin(),V.end(),[&](pair<int,int> a,pair<int,int> b){
			return p[a.first][a.second]>p[b.first][b.second];
		});
		return V;
	}
	double debug(int x,int y,game G){
		G.set(x,y);
		Debug=1;
		double ans=calc(G);
		Debug=0;
		return ans;
	}
};
my_AI p;
opponent_AI q;
game G;
const int limits[]={0,4,3,2,1};
double search(game G,int x,int y,int dep,double A,double B){
	G.set(x,y);
	if(dep==5) return p.calc(G);
	if(dep&1){
		if(G.finish()) return 1e100;
		auto v=p.get_nxts(G);//将这里的p改为q就变成了针对题目的搜索
		int cnt=0;
		double mn=1e200;
		for(auto&pr:v){
			if(++cnt>limits[dep]) break;
			mn=min(mn,search(G,pr.first,pr.second,dep+1,A,B));
			B=min(B,mn);
			if(B<=A) break;
		}
		return mn;
	}
	else{
		if(G.finish()) return -1e100;
		auto v=p.get_nxts(G);
		int cnt=0;
		double mx=-1e200;
		for(auto&pr:v){
			if(++cnt>limits[dep]) break;
			mx=max(mx,search(G,pr.first,pr.second,dep+1,A,B));
			A=max(A,mx);
			if(B<=A) break;
		}
		return mx;
	}
}
pair<int,int> Search_for_next(game G){
	auto v=p.get_nxts(G);
	int cnt=0;
	double A=-1e200,B=1e200;
	pair<int,int> nxt;double val=-1e200;
	for(auto&pr:v){
		if(++cnt>5) break;
		double vl=search(G,pr.first,pr.second,1,A,B);
	//	printf("%d %d %.1lf\n",pr.first,pr.second,vl);
		if(vl>val) val=vl,nxt=pr;
		A=max(A,vl);
	}
	return nxt;
}
int main(){
	int x,y;
	while(cin>>x>>y){
		if(x<0) break;
		G.set(x,y);
		auto pr=Search_for_next(G);
		cout<<pr.first<<' '<<pr.second<<'\n';
		G.set(pr.first,pr.second);
	}
	return 0;
}


```

