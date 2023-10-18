#ifndef _RULES_HPP_
#define _RULES_HPP_

#include <array>
#include <string>
#include <vector>
#include <algorithm>
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

extern Card changfeng;

/* Name: Deck
 * Brief: 牌组
 */
class Deck : public std::vector<Card> {
	void sort();//整理牌组
	void redCount();//将所有红宝牌变为普通牌，并且返回数量
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
#endif
