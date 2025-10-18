struct node {
	int x, y, val, cnt;
	ll sm = 0, add = 0;
	node* l = 0;
	node* r = 0;
	node(int x, int val) {
		this->x = x;
		this->val = val;
		y = mt();
		sm = val;
		cnt = 1;
		add = 0;
		l = r = 0;
	}
	node() {
		val = 0;
		x = y = 0;
		cnt = 0;
	}
};

using treap = node*;
const int N = 2e5 + 10;
node buf[N];
int siz = 0;

treap new_node(int x, int val) {
	buf[siz] = node(x, val);
	return &buf[siz++];
}
node get(treap t) {
	if (!t) return node();
	return *t;
}
treap fix(treap t) {
	if (!t) return 0;
	t->cnt = get(t->l).cnt + get(t->r).cnt + 1;
	t->sm = get(t->l).sm + get(t->r).sm + t->val + get(t->l).cnt * get(t->l).add + get(t->r).cnt * get(t->r).add;
	return t;
}
treap push(treap t) {
	if (!t) return 0;
	if (t->add) {
		t->val += t->add;
		t->sm += t->add * t->cnt;
		if (t->l) t->l->add += t->add;
		if (t->r) t->r->add += t->add;
		t->add = 0;
	}
	return t;
}
treap merge(treap a, treap b) {
	if (!a) return b;
	if (!b) return a;
	a = push(a), b = push(b);
	if (a->y > b->y) {
		a->r = merge(a->r, b);
		return fix(a);
	}
	else {
		b->l = merge(a, b->l);
		return fix(b);
	}
}

pair<treap, treap> split(treap t, int x) {
	if (!t) return { 0, 0 };
	t = push(t);
	if (t->x < x) {
		auto p = split(t->r, x);
		t->r = p.first;
		return { fix(t), p.second };
	}
	else {
		auto p = split(t->l, x);
		t->l = p.second;
		return { p.first, fix(t) };
	}
}

pair<treap, treap> splitK(treap t, int k) {
	if (!t) return { 0, 0 };
	t = push(t);
	int cntl = get(t->l).cnt;
	if (cntl < k) {
		auto p = split(t->r, k - cntl - 1);
		t->r = p.first;
		return { fix(t), p.second };
	}
	else {
		auto p = split(t->l, k);
		t->l = p.second;
		return { p.first, fix(t) };
	}
}
