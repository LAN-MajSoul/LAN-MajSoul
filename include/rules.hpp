#ifndef _RULES_HPP_
#define _RULES_HPP_

#include <array>
#include <string>
#include <vector>

// 在这里添加声明

constexpr int deckLimit = 25;

/* Name: Card
 * Brief: 牌
 */
class Card {
  public:
	// Brief: 类型 万 筒 索 字 东南西北白发中
	enum : int { w=1, p=2, s=3, z=4 } type;
	int val;
	// Brief: 副露状态 手牌 暗杠 吃碰杠
	enum : int { inHand=1, hidden=2, visiable=3 } state;

	explicit operator std::string() const;
};

/* Name: Deck
 * Brief: 牌组
 */
class Deck:std::vector<Card>{
public:
	void sort()
	{
		sort(this->begin(),this->end(),[&](Card x,Card y){

		});
	}//整理 Deck
	int redCount();//将所有红宝牌替换为普通牌，并且返回红宝牌数量
};
/* Name: Checker
 * Brief: 实现
 */
class Checker {
  public:
	// 传入一套已经和的牌 算役满和番数
	auto getYakuman(const Deck &) -> std::vector<Card>;
	auto getScore(const Deck &) -> std::vector<Card>;
	// 传入一套牌 获取正在听的牌
	auto getListening(const Deck &) -> std::vector<Card>;
};

/* Name: Player
 * Brief: 玩家
 */
class Player{
public:
	Deck inHand,hidden,visiable;// 玩家手牌，暗杠，副露中的所有牌
	int lizhi;
	/* 玩家的立直状态：
	0 没有立直 (000)2
	1 立直 (001)2
	3 立直，且可以一发 (011)2
	5 两立直 (101)2
	7 两立直，且可以一发 (111)2
	bit 下 2^0 位标记是否立直
	2^1 位标记是否一发
	2^2 位标记是否两立直
	*/
	Card feng;//玩家的场风
	int beiCount;//玩家拔北的数量
	//备注：拔北的宝牌别忘了算
	void throwCard(const Card &);// 玩家打出了一张牌
	void bei();// （仅三麻）玩家拔了一张北
	void peng(const Card &);// 玩家碰了一张牌
	void visablegang();// 玩家明杠一张牌
	void hiddengang();// 玩家暗杠一张牌
	void getCard();// 玩家获得了一张牌
	void getLing();// 玩家获得了一张岭上牌
	Player();// 构造函数，用于初始化玩家的牌
};
class GameParameters{//游戏参数的设定，用于初始化（而不是游戏进行时的参数）
public:
	int playerCount;//人数，默认为 3。
	bool red;//是否有红宝牌，默认为 1（有）。
	int startPoint;//初始点数，默认为 35000。
	int endPoint;//结束点数（1位必要点数），默认为 40000。
	bool duan;//有无食断，默认为 1（有）。
	GameParameters();//构造函数。
};
#endif
