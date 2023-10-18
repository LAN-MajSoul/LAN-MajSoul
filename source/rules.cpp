#include "rules.hpp"

#include <string>
#include <map>

Card::operator std::string() const {
    return std::to_string(val) + (type == w      ? "w"
                                  : type == p ? "p"
                                  : type == s ? "s"
                                              : "z");
}

void Deck::Sort() {
    sort(Deck::begin(), Deck::end());
}

void Deck::Insert(const Card &A) {
    push_back(A);
    Deck::Sort();
}

int seven_pair_check(const std::vector<Card> &A) {
    int Map[4][9];
    for (auto u : A) {
        Map[u.type - 1][u.val - 1]++;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            if (Map[i][j] != 0 && Map[i][j] != 2) {
                return 0;
            }
        }
    }

    return 1;
}

bool operator == (const Card &x, const Card &y) {
	return x.val == y.val && x.type == y.type;
}

Yi Now;

void solve(const std::vector<Pairs> &res) {
}

void check(const std::vector<Pairs> &res, const std::vector<Card> &now) {
	if (now.size() == 2) {
		if (now[0] == now[1]) {
			solve(res);
		}
		return;
	}

	int P[4][9];
}

Yi getScore(const Player &A, const Card &B) {
    Player C = A;
    Card D = B;
    C.inHand.Insert(D);

    std::vector<Card> G;
	std::vector<Pairs> P;

    for (auto u : C.hidden) P.push_back(u);
    for (auto u : C.visiable) P.push_back(u);
    for (auto u : C.inHand) G.push_back(u);

    int calc_sum = 0, sp = 0;

    if (C.hidden.empty() && C.visiable.empty() && seven_pair_check(C.inHand)) calc_sum += 2, Now.p[27] = 1;

	if (C.lizhi == 1) Now.p[0] = 1;

    check(P, G);
}