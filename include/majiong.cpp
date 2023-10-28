#include<bits/stdc++.h>
#include "rules.hpp"
using namespace std;
bool cmp(Card q,Card w){
	if(q.type==w.type) return q.val<w.val;
	return q.type<w.type;
}
int s[10][20];
void GET_S(vector<Card> q){
	memset(s,0,sizeof(s));
	for(int i=0;i<q.size();i++) s[q[i].type][q[i].val]++;
}
bool solve(int x,int s1,int s2){
	if(!x) return 1;
	if(x==2){
		for(int i=1;i<=3;i++){
			for(int j=1;j<=9;j++){
				if(s[i][j]==2) return 1;
			}
		}
		for(int i=1;i<=7;i++) if(s[4][i]==2) return 1;
	}
	if(s1){
		bool f=0;
		for(int i=1;i<=3;i++){
			for(int j=1;j<=7;j++){
				if(s[i][j]&&s[i][j+1]&&s[i][j+2]){
					s[i][j]--;
					s[i][j+1]--;
					s[i][j+2]--;
					f=f|(solve(x-3,s1-1,s2));
					s[i][j]++;
					s[i][j+1]++;
					s[i][j+2]++;
					if(f) return 1;
				}
			}
		}
		return 0;
	}
	if(s2){
		bool f=0;
		for(int i=1;i<=3;i++){
			for(int j=1;j<=9;j++){
				if(s[i][j]>=3){
					s[i][j]-=3;
					f=f|(solve(x-3,s1,s2-1));
					s[i][j]+=3;
					if(f) return 1;
				}
			}
		}
		for(int i=1;i<=7;i++){
			if(s[4][i]>=3){
				s[4][i]-=3;
				f=f|(solve(x-3,s1,s2-1));
				s[4][i]+=3;
				if(f) return 1;
			}
		}
		return 0;
	}



	bool f=0;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=7;j++){
			if(s[i][j]&&s[i][j+1]&&s[i][j+2]){
				s[i][j]--;
				s[i][j+1]--;
				s[i][j+2]--;
				f=f|(solve(x-3,s1-1,s2));
				s[i][j]++;
				s[i][j+1]++;
				s[i][j+2]++;
				if(f) return 1;
			}
		}
	}
	for(int i=1;i<=3;i++){
		for(int j=1;j<=9;j++){
			if(s[i][j]>=3){
				s[i][j]-=3;
				f=f|(solve(x-3,s1,s2-1));
				s[i][j]+=3;
				if(f) return 1;
			}
		}
	}
	for(int i=1;i<=7;i++){
		if(s[4][i]>=3){
			s[4][i]-=3;
			f=f|(solve(x-3,s1,s2-1));
			s[4][i]+=3;
			if(f) return 1;
		}
	}
	return 0;
}
/*bool check(vector<Card> q,int s1,int s2){
	sort(q.begin(),q.end(),cmp);
	memset(s,0,sizeof(s));
	for(int i=0;i<q.size();i++) s[q.type][q.val]++;
	return solve(q.size(),s1,s2);
}*/
vector<Card> GET_Ting(vector<Card> q){
	GET_S(q);
	vector<Card> kep;
	for(auto i=1;i<=4;i++){
		for(int j=1;j<=9;j++){
			s[i][j]++;
			bool f=solve(q.size()+1,0,0);
			s[i][j]--;
			if(f) kep.push_back((Card){(decltype(Card::w))i,j,Card::inHand});
		}
	}return kep;
}
bool duanyao_check(Player pl){
	for(int i=0;i<pl.inHand.size();i++){
		if(pl.inHand[i].type==4||(pl.inHand[i].val==1||pl.inHand[i].val==9)) return 0;
	}
	for(int i=0;i<pl.hidden.size();i++){
		if(pl.hidden[i].type==4||(pl.hidden[i].val==1||pl.hidden[i].val==9)) return 0;
	}
	for(int i=0;i<pl.visiable.size();i++){
		if(pl.visiable[i].type==4||(pl.visiable[i].val==1||pl.visiable[i].val==9)) return 0;
	}
	return 1;
}
bool yibeikou_check(int x,int sum){
	if(!sum) return solve(x,0,0);
	for(int i=1;i<=3;i++){
		for(int j=1;j<=7;j++){
			if(s[i][j]>=2&&s[i][j+1]>=2&&s[i][j+2]>=2){
				s[i][j]-=2;
				s[i][j+1]-=2;
				s[i][j+2]-=2;
				bool f=yibeikou_check(x-6,sum-1);
				s[i][j]+=2;
				s[i][j+1]+=2;
				s[i][j+2]+=2;
				if(f) return 1;
			}
		}
	}
	return 0;
}
bool sanse_check(){
	for(int i=1;i<=9;i++){
		if(s[1][i]>=3&&s[2][i]>=3&&s[3][i]>=3){
			s[1][i]-=3;
			s[2][i]-=3;
			s[3][i]-=3;
			bool f=solve(5,0,0);
			s[1][i]+=3;
			s[2][i]+=3;
			s[3][i]+=3;
			if(f) return 1;
		}
	}return 0;
}
void GET_ALL_S(Player pl){
	memset(s,0,sizeof(s));
	for(int i=0;i<pl.hidden.size();i++) s[pl.hidden[i].type][pl.hidden[i].val]++;
	for(int i=0;i<pl.visiable.size();i++) s[pl.visiable[i].type][pl.visiable[i].val]++;
	for(int i=1;i<=3;i++) for(int j=1;j<=9;j++) if(s[i][j]==4) s[i][j]--;
	for(int i=1;i<=7;i++) if(s[4][i]==4) s[4][i]--;
	for(int i=0;i<pl.inHand.size();i++) s[pl.inHand[i].type][pl.inHand[i].val]++;
	//s[Long.type][Long.val]++;
}
bool sananke_check(Player pl){
	if(pl.hidden.size()/4*3+pl.inHand.size()<11) return 0;
	GET_S(pl.inHand);
	int needs=3-pl.hidden.size()/4*3;
	if(needs<=0) return 1;
	return solve(pl.inHand.size(),0,needs);
}
bool xiaosanyuan_check(Player pl){
	GET_ALL_S(pl);
	int s1=0,s2=0;
	if(s[4][5]>=3) s1++;
	else if(s[4][5]==2) s2++;
	if(s[4][6]>=3) s1++;
	else if(s[4][6]==2) s2++;
	if(s[4][7]>=3) s1++;
	else if(s[4][7]==2) s2++;
	if(s1==2&&s2==1) return 1;
	return 0;
}
bool hunlaotou_check(Player pl){
	GET_ALL_S(pl);
	for(int i=1;i<=3;i++){
		for(int j=2;j<=8;j++) if(s[i][j]) return 0;
	}return 1;
}
bool qidui_check(Player pl){
	if(pl.visiable.size()>0||pl.hidden.size()>0) return 0;
	GET_S(pl.inHand);
	int s1=0;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=9;j++){
			if(s[i][j]==2) s1++;
			else if(s[i][j]!=0) return 0;
		}
	}
	if(s1==7) return 1;
	return 0;
}
bool hunquan_check2(int x,int fla){
	if(x==2){
		for(int i=1;i<=3;i++){
			if(s[i][1]==2) return 1;
			if(s[i][9]==2) return 1;
		}
		if(fla==2) return 0;
		for(int i=1;i<=7;i++) if(s[4][i]==2) return 1;
		return 0;
	}
	for(int i=1;i<=3;i++){
		if(s[i][1]&&s[i][2]&&s[i][3]){
			s[i][1]--;
			s[i][2]--;
			s[i][3]--;
			bool f=hunquan_check2(x-3,fla);
			s[i][1]++;
			s[i][2]++;
			s[i][3]++;
			if(f) return 1;
		}
		if(s[i][7]&&s[i][8]&&s[i][9]){
			s[i][7]--;
			s[i][8]--;
			s[i][9]--;
			bool f=hunquan_check2(x-3,fla);
			s[i][7]++;
			s[i][8]++;
			s[i][9]++;
			if(f) return 1;
		}
	}
	for(int i=1;i<=3;i++){
		if(s[i][1]>=3){
			s[i][1]-=3;
			bool f=hunquan_check2(x-3,fla);
			s[i][1]+=3;
			if(f) return 1;
		}
		if(s[i][9]>=3){
			s[i][9]-=3;
			bool f=hunquan_check2(x-3,fla);
			s[i][9]+=3;
			if(f) return 1;
		}
	}
	if(fla==2) return 0;
	for(int i=1;i<=7;i++){
		if(s[4][i]>=3){
			s[4][i]-=3;
			bool f=hunquan_check2(x-3,fla);
			s[4][i]+=3;
			if(f) return 1;
		}
	}
	return 0;
}
bool hunquan_check(Player pl,int fla){
	for(int i=0;i<pl.hidden.size();i++) if(pl.hidden[i].type!=4&&(pl.hidden[i].val>1&&pl.hidden[i].val<9)) return 0;
	for(int i=0;i<pl.visiable.size();i++) if(pl.visiable[i].type!=4&&(pl.visiable[i].val>1&&pl.visiable[i].val<9)) return 0;
	if(fla==2){
		for(int i=0;i<pl.hidden.size();i++) if(pl.hidden[i].type==4) return 0;
		for(int i=0;i<pl.visiable.size();i++) if(pl.visiable[i].type==4) return 0;
	}
	GET_S(pl.inHand);
	return hunquan_check2(pl.inHand.size(),fla);
}
bool yiqi_check(Player pl){
	GET_ALL_S(pl);
	for(int i=1;i<=3;i++){
		bool f=1;
		for(int j=1;j<=9;j++) if(!s[i][j]) f=0;
		if(f){
			for(int j=1;j<=9;j++) s[i][j]--;
			bool fl=solve(5,0,0);
			for(int j=1;j<=9;j++) s[i][j]++;
			if(fl) return 1;
		}
	}
	return 0;
}
bool sansetongshun_check(Player pl){
	GET_ALL_S(pl);
	for(int i=1;;i<=7;i++){
		if(s[1][i]&&s[2][i]&&s[3][i]&&s[1][i+1]&&s[2][i+1]&&s[3][i+1]&&s[1][i+2]&&s[2][i+2]&&s[3][i+2]){
			s[1][i]--;
			s[2][i]--;
			s[3][i]--;
			s[1][i+1]--;
			s[2][i+1]--;
			s[3][i+1]--;
			s[1][i+2]--;
			s[2][i+2]--;
			s[3][i+2]--;
			bool f=solve(5,0,0);
			s[1][i]++;
			s[2][i]++;
			s[3][i]++;
			s[1][i+1]++;
			s[2][i+1]++;
			s[3][i+1]++;
			s[1][i+2]++;
			s[2][i+2]++;
			s[3][i+2]++;
			if(f) return 1;
		}
	}
	return 0;
}
bool zipai_check(Player pl){
	GET_ALL_S(pl);
	for(int i=1;i<=7;i++) if(s[4][i]) return 0;
	return 1;
}
bool hun_check(Player pl){
	for(int i=1;i<=3;i++){
		bool f=1;
		for(int j=1;j<=3;j++){
			if(i==j) continue;
			for(int k=1;k<=9;k++){
				if(s[j][k]){
					f=0;
					break;
				}
			}
		}
		if(f) return 1;
	}return 0;
}
int calc(Player pl,int lys,Card Long){
	int sum=0;//役
	int add=0;//奖励
	vector<Card> ting=GET_Ting(pl.inHand);
	vector<Card> finish;
	for(int i=0;i<pl.inHand.size();i++) finish.push_back(pl.inHand[i]);
	finish.push_back(Long);
	GET_S(finish);
	if(pl.visiable.size()==0&&pl.hidden.size()==0&&solve(finish.size(),4,0)&&ting.size()>=2) sum++;//平和
	
	pl.inHand.push_back(Long);//将铳牌加入手牌中
	if(lys&1) sum++;
	if(duanyao_check(pl)) sum++;//断幺九
	if(pl.visiable.size()==0&&lys&2) sum++;//门前清自摸
	int s[5][10];
	bool qidui_flag=0;
	if(qidui_check(pl)){
		sum+=2;
		qidui_flag=1;
	}//七对子

	sort(pl.hidden.begin(),pl.hidden.end(),cmp);
	for(int i=0;i<pl.inHand.size();i++) s[pl.inHand[i].type][pl.inHand[i].val]++;
	for(int i=0;i<pl.visiable.size();i++) s[pl.visiable[i].type][pl.visiable[i].val]++;
	for(int i=0;i<pl.hidden.size();i+=3){
		s[pl.inHand[i].type][pl.inHand[i].val]++;
		s[pl.inHand[i+1].type][pl.inHand[i+1].val]++;
		s[pl.inHand[i+2].type][pl.inHand[i+2].val]++;
	}
	if(s[pl.feng.type][pl.feng.val]>=3) sum++;//自风
	if(s[changfeng.type][changfeng.val]>=3) sum++;//场风
	if(s[4][5]>=3) sum++;//白
	if(s[4][6]>=3) sum++;//发
	if(s[4][7]>=3) sum++;//中
	if(pl.visiable.size()==0&&qidui_flag==0){
		GET_S(finish);
		if(finish.size()>=8&&yibeikou_check(finish.size(),1)) sum++;//一杯口
		GET_S(finish);
		if(finish.size()>=14&&yibeikou_check(finish.size(),2)) sum+=3;//二杯口
	}
	if(lys&4) sum++;//抢杠
	if(lys&8) sum++;//岭上开花
	if(lys&16) sum++;//海底
	if(lys&32) sum++;//河底
	if(lys&64) sum++;//一发
	add=add+pl.beiCount;//拔北
	if(lys&128) sum++;//两立直
	GET_ALL_S(pl);
	if(sanse_check()) sum+=2;//三色同刻
	if(pl.hidden.size()>=12) sum+=2;//三杠子
	GET_ALL_S(pl);
	if(solve(14,0,4)) sum+=2;//对对和
	if(sananke_check(pl)) sum+=2;//三暗刻
	if(xiaosanyuan_check(pl)) sum+=2;//小三元
	if(hunlaotou_check(pl)) sum+=2;//混老头
	//GET_ALL_S(pl);
	if(hunquan_check(pl,1)){
		if(pl.visiable.size()==0) sum+=2;
		else sum++;//副露-1番
	}//混全带幺九
	if(yiqi_check(pl)){
		if(pl.visiable.size()==0) sum+=2;
		else sum++;//副露-1番
	}//一气通贯
	if(sansetongshun_check(pl)){
		if(pl.visiable.size()==0) sum+=2;
		else sum++;//副露-1番
	}//三色同顺
	if(hunquan_check(pl,2)){
		if(pl.visiable.size()==0) sum+=3;
		else sum+=2;//副露-1番
	}//纯全带幺九
	if(hun_check(pl)){
		int del=0;
		if(pl.visiable.size()!=0) del=1;//副露-1
		sum-=del;
		if(zipai_check(pl)) sum+=6;
		else sum+=3;
	}
}
signed main(){
	int a,b;
	cin>>a>>b;
	cout<<a+b;
}