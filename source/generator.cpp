#include "generator.hpp"
#include<random>
// 在这里给出头文件中声明对应的定义
void gameStartInit(Deck &gameDeck,const GameParameter &gamePara)
{
	mt19937 rnd(random_device{}());
	for(int i=1;i<=9;i++)//生成万牌
	{
		if(i>=2&&i<=8&&gamePara.playerCount==3) continue;//三麻没有2到8万
		for(int j=1;j<=(i==5?3:4);j++)
		{
			gameDeck.push_back({1,i,0});
		}
		if(i==5)
		{
			if(gamePara.red) gameDeck.push_back({1,0,0});//生成红宝
			else gameDeck.push_back({1,5,0});
		}
	}
	for(int i=1;i<=9;i++) //生成筒牌
	{
		for(int j=1;j<=(i==5?3:4);j++)
		{
			gameDeck.push_back({2,i,0});
		}
		if(i==5)
		{
			if(gamePara.red) gameDeck.push_back({1,0,0});//生成红宝
			else gameDeck.push_back({2,5,0});
		}
	}
	for(int i=1;i<=9;i++) //生成条子
	{
		for(int j=1;j<=(i==5?3:4);j++)
		{
			gameDeck.push_back({3,i,0});
		}
		if(i==5)
		{
			if(gamePara.red) gameDeck.push_back({1,0,0});//生成红宝
			else gameDeck.push_back({3,5,0});
		}
	}
	for(int i=1;i<=7;i++) //生成字牌
	{
		for(int j=1;j<=4;j++)
		{
			gameDeck.push_back({4,i,0});
		}
	}
	shuffle(gameDeck.begin(),gameDeck.end(),rnd);//打乱牌
	deckFront=gameDeck.begin();
	deckLing=prev(gameDeck.end());
	deckBack=gameDeck.end();
	for(int i=1;i<=14;i++) deckBack--;//生成王牌的迭代器位置
	visiableBao=hiddenBao=deckBack;
	for(int i=1;i<=5;i++) hiddenBao++;//生成宝牌的迭达器位置
}
