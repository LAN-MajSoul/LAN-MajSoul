#include "rules.hpp"

#include <string>
#include <map>

Card changfeng, menfeng;
std::vector<Pairs> PP;
int Hu, Lizhi_Chong, Zimo, Last, Lingshang, GangZhen;

Card::operator std::string() const {
    return std::to_string(val) + (type == w ? "w"
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

int duanyaojiu_check(const std::vector<Pairs> &res) {
    for (auto u : res) {
        Card now = u.val;
        if (u.type != 1) {
            if (now.type == 4 || now.val == 1 || now.val == 9) return 0;
        }
        else {
            if (now.val == 1 || now.val == 7) return 0;
        }
    }

    return 1;
}

int xiaosanyuan_check(const std::vector<Pairs> &res) {
    int cnt = 0;

    for (auto u : res) {
        Card now = u.val;
        if (now.type == 4 && now.val > 4) cnt++;
    }

    return cnt > 1;
}

int bai_check(const std::vector<Pairs> &res) {
    for (auto u : res) {
        Card now = u.val;
        if (now.type == 4 && now.val == 5) return 1;
    }

    return 0;
}

int fa_check(const std::vector<Pairs> &res) {
    for (auto u : res) {
        Card now = u.val;
        if (now.type == 4 && now.val == 6) return 1;
    }

    return 0;
}

int zhong_check(const std::vector<Pairs> &res) {
    for (auto u : res) {
        Card now = u.val;
        if (now.type == 4 && now.val == 7) return 1;
    }

    return 0;
}

int pinghu_check(const std::vector<Pairs> &res, const Ting &chong) {
    for (auto u : res) {
        if (u.type != 1) return 0;
    }

    if (chong.type != 1) return 0;
    return 1;
}

int changfeng_check(const std::vector<Pairs> &res) {
    for (auto u : res) {
        Card now = u.val;
        if (now == changfeng) return 1;
    }

    return 0;
}

int menfeng_check(const std::vector<Pairs> &res) {
    for (auto u : res) {
        Card now = u.val;
        if (now == menfeng) return 1;
    }

    return 0;
}

int yibeikou_check(const std::vector<Pairs> &res) {
    auto K = res;

    for (auto u : PP) {
        K.push_back(u);
    }

    int P[4][9];

    for (auto u : K) {
        if (u.type != 1) continue;
        Card now = u.val;
        if (P[now.type - 1][now.val - 1]) return 1;
        P[now.type - 1][now.val - 1] = 1;
    }

    return 0;
}

int Sansetongke_check(const std::vector<Pairs> &res) {
    int P[4][9];

    for (auto u : res) {
        Card now = u.val;
        if (u.type != 1) {
            P[now.type - 1][now.val - 1]++;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (P[0][i] && P[1][i] && P[2][i]) return 1;
    }

    return 0;
}

int Sangangzi_check(const std::vector<Pairs> &res) {
    int cnt = 0;

    for (auto u : res) {
        if (u.type == 2) cnt++;
    }

    return cnt > 2;
}

int duiduihu_check(const std::vector<Pairs> &res) {
    for (auto u : res) {
        if (u.type == 1) return 0;
    }

    return 1;
}

void solve(const std::vector<Pairs> &res, const Card &A, int p, const Ting &ting) {
    if (duanyaojiu_check(res)) Now.p[1] = 1;
    if (p && Zimo) Now.p[2] = 1;
    if (menfeng_check(res)) Now.p[3] = 1;
    if (changfeng_check(res)) Now.p[4] = 1;
    if (bai_check(res)) Now.p[5] = 1;
    if (fa_check(res)) Now.p[6] = 1;
    if (zhong_check(res)) Now.p[7] = 1;
    if (p && pinghu_check(res, ting)) Now.p[8] = 1;
    if (!Now.p[23] && yibeikou_check(res)) Now.p[9] = 1;
    if (Lizhi_Chong) Now.p[18] = 1;
    if (Sansetongke_check(res)) Now.p[21] = 2;
    if (Sangangzi_check(res)) Now.p[22] = 2;
    if (duiduihu_check(res)) Now.p[24] = 2;
    if ((A.type == 3 && A.val > 4) && xiaosanyuan_check(res)) Now.p[25] = 2;
}

void check(const std::vector<Pairs> &res, const std::vector<Card> &now, int p, const Ting &ting) {
    if (now.size() == 2) {
        if (now[0] == now[1]) {
            solve(res, now[0], p, ting);
        }
        return;
    }

    int P[4][9];

    for (auto u : now) {
        P[u.type - 1][u.val - 1]++;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            if (P[i][j] > 2) {
                std::vector<Card> A;
                int cnt = 0;
                A.clear();
				Card C;
				C.type = decltype(Card::type)(i + 1);
				C.val = decltype(Card::val)(j + 1);
				Pairs B;
				B.type = decltype(Pairs::type)(0);
				B.val = C;
                for (auto u : now) {
                    if (u.type - 1 == i && u.val - 1 == j) {
                        if (cnt > 2) A.push_back(u);
                        cnt++;
                    }
                    else {
                        A.push_back(u);
                    }
                }
				auto D = res;
				D.push_back(B);
				check(D, A, p, ting);
            }
        }
    }
    for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			if (P[i][j] && P[i][j + 1] && P[i][j + 2]) {
                std::vector<Card> A;
                A.clear();
                int cnt[3];
                cnt[0] = cnt[1] = cnt[2] = 0;
                Card C;
                C.type = decltype(Card::type)(i + 1);
                C.val = decltype(Card::val)(j + 1);
                Pairs B;
                B.type = decltype(Pairs::type)(1);
                B.val = C;
                for (auto u : now) {
                    if (u.type - 1 == i && (u.val - 1 >= j && u.val - 1 <= j + 2)) {
                        if (cnt[u.val - j - 1]) A.push_back(u);
                        cnt[u.val - 1 - j]++;
                    }
                    else {
                        A.push_back(u);
                    }
                }
                auto D = res;
                D.push_back(B);
                check(D, A, p, ting);
            }
		}
    }
}

int check_hu(const std::vector<Card> &now) {
    int P[4][9];

    for (auto u : now) {
        P[u.type - 1][u.val - 1]++;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            if (P[i][j] > 2) {
                P[i][j] -= 3;
            }
            if (j < 7) {
                while (P[i][j] && P[i][j + 1] && P[i][j + 2]) {
                    P[i][j]--;
                    P[i][j + 1]--;
                    P[i][j + 2]--;
                }
            }
            if (P[i][j]) return 0;
        }
    }

    return 1;
}

int Check(const std::vector<Card> &now, const Card &A) {
    auto B = now;
    B.push_back(A);

    int P[4][9];

    for (auto u : B) {
        P[u.type - 1][u.val - 1]++;
    }

    int p = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            if (P[i][j] > 1) {
                P[i][j] -= 2;
                int cnt = 0;

                std::vector<Card> C;
                C.clear();

                for (auto u : B) {
                    if (u.type - 1 == i && u.val - 1 == j) {
                        if (cnt > 1) C.push_back(u);
                        cnt++;
                    }
                    else C.push_back(u);
                }

                int x = check_hu(C);

                if (x) {
                    if (A.type - 1 == i && A.val - 1 == j) return 3;

                    std::vector<Card> D;

                    if (P[A.type - 1][A.val - 1] > 2) {
                        D.clear();
                        cnt = 0;

                        for (auto u : C) {
                            if (A.type == u.type && u.val == A.val) {
                                if (cnt > 2) D.push_back(u);
                                cnt++;
                            }
                            else D.push_back(u);
                        }

                        if (check_hu(D)) p = 1;
                    }
                    else if (A.type < 4 && A.val > 1 && A.val < 9 && P[A.type - 1][A.val - 2] && P[A.type - 1][A.val - 1] && P[A.type - 1][A.val]) {
                        D.clear();
                        int Cnt[3];
                        Cnt[0] = Cnt[1] = Cnt[2] = 0;

                        for (auto u : C) {
                            if (A.type == u.type && (A.val - 1 <= u.val && A.val + 1 >= u.val)) {
                                if (Cnt[A.val + 1 - u.val]) D.push_back(u);
                                Cnt[A.val + 1 - u.val]++;
                            }
                            else D.push_back(u);
                        }

                        if (check_hu(D)) p = 1;
                    }
                    else {
                        if (!p) p = 2;
                    }
                }
                P[i][j] += 2;
            }
        }
    }

    return p;
}

Yi getScore(const Player &A, const Card &B, const int &hu) {
    Player C = A;
    Card D = B;
    C.inHand.Insert(D);

    Hu = hu;

    menfeng = C.feng;

    std::vector<Card> G;
    std::vector<Ting> ting;
    std::vector<Pairs> P;
    PP = P;

    for (auto u : C.hidden) P.push_back(u);
    for (auto u : C.visiable) P.push_back(u);
    for (auto u : C.inHand) G.push_back(u);

    if (C.hidden.empty() && C.visiable.empty() && seven_pair_check(C.inHand)) Now.p[27] = 2;

    if (C.lizhi & 4) Now.p[20] = 2;
    else if (C.lizhi & 1) Now.p[0] = 1;
    if (C.lizhi & 2) Now.p[14] = 1;
    if (Lingshang) Now.p[11] = 1;
    if (Last) {
        if (Zimo) Now.p[12] = 1;
        else Now.p[13] = 1;
    }
    Now.p[15] = C.baoCount;
    Now.p[16] = C.resCount;
    Now.p[17] = C.beiCount;
    if (GangZhen) Now.p[19] = 1;

    int p = 0;

    if (C.visiable.size() == 0) p = 1;

    std::vector<Card> K;
    K.clear();

    for (int i = 1; i < 5; i++) {
        for (int j = 1; j < ((i < 4) ? 10 : 8); j++) {
            Card L;
            L.type = decltype(Card::type)(i);
            L.val = j;
            K.push_back(L);
        }
    }

    Ting L;

    for (auto u : K) {
        int x = Check(C.inHand, u);
        if (x) {
            Ting y;
            y.type = decltype(Ting::type)(x - 1);
            y.val = u;
            if (u == B) L = y;
            ting.push_back(y);
        }
    }

    check(P, G, p, L);
}