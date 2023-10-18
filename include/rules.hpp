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
 * Display:
 *   🀇🀈🀉🀊🀋🀌🀍🀎🀏
 *   🀙🀚🀛🀜🀝🀞🀟🀠🀡
 *   🀐🀑🀒🀓🀔🀕🀖🀗🀘
 *   🀀🀁🀂🀃🀆🀅🀄
 *   🀫
 */
class Card {
  public:
	// Brief: 类型 万 筒 索 字 东南西北白发中
	enum : int { w=1, p=2, s=3, z=4 } type;
	int val;
	// Brief: 副露状态 手牌 暗杠 吃碰杠
	enum : int { inHand=1, hidden=2, visiable=3 } state;

	explicit operator std::string() const;
	bool operator <(const Card&) const;
};

extern Card changfeng;

/* Name: Deck
 * Brief: 牌组
 */
class Deck : public std::vector<Card> {
  public:
	void Sort();//整理牌组
	void Insert(const Card &);//加入新牌
	void redCount();//将所有红宝牌变为普通牌，并且返回数量
};

/* Name: Yi
 * Brief: 役种
 */
class Yi {
  public: 
    int p[39];
	/*
	0 立直
	1 断幺九
	2 门前清自摸和
	3 役牌：自风牌
	4 役牌：场风牌
	5 役牌：中
	6 役牌：发
	7 役牌：白
	8 平和
	9 一杯口
	10 抢杠
	11 岭上开花
	12 海底摸月
	13 河底捞鱼
	14 一发
	15 宝牌
	16 赤宝牌
	17 北宝牌
	18 古役：燕返
	19 古役：杠振
	20 两立直
	21 三色同刻
	22 三杠子
	23 对对和
	24 三暗刻
	25 小三元
	26 混老头
	27 七对子
	28 混全带幺九
	29 一气通贯
	30 古役：五门齐
	31 古役：三连刻
	32 二杯口
	33 纯全带幺九
	34 混一色
	35 古役：一色三同顺
	36 古役：一筒摸月
	37 古役：九筒捞鱼
	38 清一色
	*/
};

/* Name: Pairs
 * Brief: 刻/顺/杠
 */
class Pairs {
  public: 
	enum : int { k = 0, s = 1, g = 2 } type;
	Card val;
};

/* Name: Ting
 * Brief: 听牌类型
 */
class Ting {
  public: 
	enum : int { nqnlr = 0, lr = 1, q = 2 } type;
	Card val;
};

/* Name: Result
 * Brief: Vector <- Pairs
 */
class Result : public std::vector<Pairs> {
};

/* Name: Player
 * Brief: 玩家
 */
class Player{
public:
	Deck inHand;
	Result hidden,visiable;// 玩家手牌，暗杠，副露中的所有牌
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
	Card feng;//玩家的门风
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
/* Name: Checker
 * Brief: 实现
 */
class Checker {
  public:
	// 传入一套已经和的牌 算役满
	auto getYakuman(const Player &) -> std::vector<Card>;
	// 传入一套牌 获取正在听的牌
	auto getListening(const Player &) -> std::vector<Card>;
	// 传入一套已经和的牌 算番数
	auto getScore(const Player &, const Card &, const int &) -> Yi;
};
/* Name: GameParameter
 * Brief: 游戏参数
 */
class GameParameter{
public:
	int playerCount;//人数，默认为 3
	bool red;//有无红宝，默认为 1（有）
};
#endif
