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
priority_queue<pair<int,string>,vector<pair<int,string> >,greater<pair<int,string> > > H;
vector<char> C;
int L;
int main(){
	for(int i=0;i<26;i++) C.push_back('a'+i);
	for(int i=0;i<26;i++) C.push_back('A'+i);
	for(int i=0;i<10;i++) C.push_back('0'+i);
	for(int i=0;i<62;i++){
		cout<<"? ";
		pair<int,string> pr;
		for(int j=0;j<128;j++)
			pr.second+=C[i];
		cout<<pr.second<<endl;
		int x;cin>>x;
		pr.first=128-x;
		for(int j=0;j<x;j++) pr.second.pop_back();
		if(pr.first) H.push(pr);
		L+=pr.first;
	}
	while(H.size()>1){
		auto p1=H.top();H.pop();
		auto p2=H.top();H.pop();
		string st;
		int k=0;
		for(int i=0;i<p1.first;i++){
			while(k<p2.first){
				string out=st;
				out+=p2.second[k];
				for(int j=i;j<p1.first;j++)
					out+=p1.second[j];
				cout<<"? "<<out<<endl;
				int x;cin>>x;
				if(L-x!=out.length()) break;
				else st+=p2.second[k++];
			}
			st+=p1.second[i];
		}
		while(k<p2.first) st+=p2.second[k++];
		H.push(make_pair(p1.first+p2.first,st));
	}
	cout<<"! "<<H.top().second<<endl;
	return 0;
}

