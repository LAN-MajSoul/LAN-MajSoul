#ifndef _GENERATOR_HPP_
#define _GENERATOR_HPP_
#include"rules.hpp"
// 在这里添加声明
extern Deck::iterator deckFront,deckBack,deckLing,visiableBao,hiddenBao;//迭代器，分别表示牌山的头，王牌的头，岭上牌，宝牌翻到了哪张，里宝牌翻到了哪张。
//back 后为宝牌，里宝牌，岭上牌的顺序
extern Deck visiableBaoDeck,hiddenBaoDeck;//用来存放翻出来的宝牌
extern int gangCount,lingCount;
int gameStartInit(Deck &,const GameParameter &); //游戏开始时生成牌山，若返回值为 0 则为正常生成
Card getNormalCard(); //取出牌山的一张牌
Card getLingCard(); //取出岭上的一张牌
void getVisiableBao(); //翻出一张表宝牌
void getHiddenBao(); //翻出一张里宝牌
int cardCount(); //返回牌山中的非王牌数量，当为 0 时应流局
#endif