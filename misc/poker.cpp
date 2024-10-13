char suit[4]={'C','D','H','S'},ranks[13]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
int rk[256];
// forn(i, 13) rk[ranks[i]]=i;
// forn(i, 4) rk[suit[i]]=i;
struct cards{
	vector<pt> v;
	int suit_cnt[4], hands;
	void reset(){ v.clear(), memset(suit_cnt,0, sizeof(suit_cnt)), hands=-1; }
	void insert(char a, char b) { //suit,rank
		++suit_cnt[rk[a]];
		bool flag = 0;
		for (auto &i: v) if (i.y == rk[b]) {
			++i.x, flag = true;
			break;
		}
		if (!flag) v.pb(mp(1, rk[b]));
	}
	void insert(string s){ insert(s[0], s[1]); }
	void ready(){
		bool Straight = 0, Flush = (*max_element(suit_cnt, suit_cnt + 4) == 5);
		sort(all(v), greater<pt>());
		if(sz(v) == 5 && v[0].y == v[1].y + 1 && v[1].y == v[2].y + 1 && v[2].y == v[3].y + 1 && v[3].y == v[4].y + 1)
			Straight = true;
		else if (sz(v) == 5 && v[0].y == 12 && v[1].y == 3 && v[2].y == 2 && v[3].y == 1 && v[4].y == 0)
			v[0].y = 3, v[1].y = 2, v[2].y = 1, v[3].y = 0, v[4].y = -1, Straight = true;
		if (Straight && Flush) hands = 1;
		else if (v[0].x == 4) hands = 2;
		else if (v[0].x == 3 && v[1].x == 2) hands = 3;
		else if (Flush) hands = 4;
		else if (Straight) hands = 5;
		else if (v[0].x == 3) hands = 6;
		else if (v[0].x == 2 && v[1].x == 2) hands = 7;
		else if (v[0].x == 2) hands = 8;
		else hands = 9;
	}
	bool operator>(const cards &a)const{
		if (hands == a.hands) return v > a.v;
		return hands < a.hands;
	}
};