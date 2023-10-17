#ifndef _RULES_HPP_
#define _RULES_HPP_

#include <array>
#include <string>
#include <vector>

// 在这里添加声明

constexpr int deckLimit = 25;

/* Name: Card
 * Brief: 手牌
 */
class Card {
	// Brief: 类型 万 筒 索 字 东南西北白发中
	enum { w, p, s, z } type;
	int val;

  public:
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
	// 传入一套已经和的牌 算番数
	auto getScore(const Deck &) -> std::vector<Card>;
	// 传入一套牌 获取正在听的牌
	auto getListening(const Deck &) -> std::vector<Card>;
};

#endif
