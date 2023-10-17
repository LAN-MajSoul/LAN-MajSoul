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
	enum { w, p, s, z } type;
	int val;
	// Brief: 副露状态 手牌 暗杠 吃碰杠
	enum { inHand, hidden, visiable } state;

	explicit operator std::string() const;
};

/* Name: Deck
 * Brief: 牌组
 */
class Deck {
  private:
	std::array<Card, deckLimit> data;
	int cardCount;

  public:
	[[nodiscard]] auto operator[](int index) const -> const Card & {
		return data[index];
	}
	[[nodiscard]] auto operator[](int index) noexcept -> Card & {
		return data[index];
	}
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
	void throwCard(const Card &);// 玩家打出了一张牌
	void bei();// （仅三麻）玩家拔了一张北
	void peng(const Card &);// 玩家碰了一张牌
	void visablegang();// 玩家明杠一张牌
	void hiddengang();// 玩家暗杠一张牌
	void getCard();// 玩家获得了一张牌
	void getLing();// 玩家获得了一张岭上牌
};
#endif
