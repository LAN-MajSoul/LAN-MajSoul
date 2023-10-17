#ifndef _GENERATOR_HPP_
#define _GENERATOR_HPP_
#include"rules.hpp"
// 在这里添加声明

int GameStartInit(Deck &GameDeck); //游戏开始时生成牌山，若返回值为 0 则为正常生成
Card NormalCard(); //取出牌山的一张牌
Card LingCard(); //取出岭上的一张牌
Card BiaoBao(); //翻出一张表宝牌
Card LiBao(); //翻出一张里宝牌
int CardCount(); //返回牌山中的非王牌数量，当为 0 时应流局
#endif
