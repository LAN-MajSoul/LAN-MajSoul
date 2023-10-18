#include "generator.hpp"
#include<random>
#include<cassert>
// 在这里给出头文件中声明对应的定义
Deck::iterator deckFront,deckBack,deckLing,visiableBao,hiddenBao;//迭代器，分别表示牌山的头，王牌的头，岭上牌，宝牌翻到了哪张，里宝牌翻到了哪张。
//back 后为宝牌，里宝牌，岭上牌的顺序
Deck visiableBaoDeck,hiddenBaoDeck;//用来存放翻出来的宝牌
int gangCount,lingCount;
int gameStartInit(Deck &gameDeck,const GameParameter &gamePara)
{
	std::mt19937 rnd(std::random_device{}());
	for(int i=1;i<=9;i++)//生成万牌
	{
		if(i>=2&&i<=8&&gamePara.playerCount==3) continue;//三麻没有2到8万
		for(int j=1;j<=(i==5?3:4);j++)
		{
			gameDeck.push_back({Card::w,i,Card::inHand});
		}
		if(i==5)
		{
			if(gamePara.red) gameDeck.push_back({Card::w,0,Card::inHand});//生成红宝
			else gameDeck.push_back({Card::w,5,Card::inHand});
		}
	}
	for(int i=1;i<=9;i++) //生成筒牌
	{
		for(int j=1;j<=(i==5?3:4);j++)
		{
			gameDeck.push_back({Card::p,i,Card::inHand});
		}
		if(i==5)
		{
			if(gamePara.red) gameDeck.push_back({Card::p,0,Card::inHand});//生成红宝
			else gameDeck.push_back({Card::p,5,Card::inHand});
		}
	}
	for(int i=1;i<=9;i++) //生成条子
	{
		for(int j=1;j<=(i==5?3:4);j++)
		{
			gameDeck.push_back({Card::s,i,Card::inHand});
		}
		if(i==5)
		{
			if(gamePara.red) gameDeck.push_back({Card::s,0,Card::inHand});//生成红宝
			else gameDeck.push_back({Card::s,5,Card::inHand});
		}
	}
	for(int i=1;i<=7;i++) //生成字牌
	{
		for(int j=1;j<=4;j++)
		{
			gameDeck.push_back({Card::z,i,Card::inHand});
		}
	}
	shuffle(gameDeck.begin(),gameDeck.end(),rnd);//打乱牌
	deckFront=gameDeck.begin();
	deckLing=prev(gameDeck.end());
	deckBack=gameDeck.end();
	for(int i=1;i<=gamePara.playerCount==3?18:14;i++) deckBack--;//生成王牌的迭代器位置
	visiableBao=hiddenBao=deckBack;
	for(int i=1;i<=5;i++) hiddenBao++;//生成宝牌的迭达器位置
	return 0;
}
Card getNormalCard()
{
	assert((deckFront!=deckBack));//你牌没了
	/*上述情况不应该出现*/
	Card result=*deckFront;
	deckFront++;
	return result;
}
Card getLingCard()
{
	assert((lingCount!=8));//您岭上没了（
	assert((deckFront!=deckBack));//你流局了
	/*上述情况不应该出现*/
	deckBack--;
	Card result=*deckLing;
	deckLing--;
	return result;
}
void getVisiableBao()
{
	visiableBaoDeck.emplace_back(*visiableBao);
	visiableBao++;
	return ;
}
void getHiddenBao()
{
	hiddenBaoDeck.emplace_back(*hiddenBao);
	hiddenBao++;
	return ;
}
int cardCount()
{
	return (int)(deckBack-deckFront);
}