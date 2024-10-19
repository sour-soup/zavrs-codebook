struct node {
	int y, val, cnt = 0, rev = 0;
	node* l = 0;
	node* r = 0;
	node(int val) {
		this->val = val;
		y = mt();
		cnt = 1;
	}
	node() {}
};
using treap = node*;
 
const int N = 2e5 + 10;
node buf[N];
int siz = 0;
treap new_node(int val) {
	buf[siz] = node(val);
	return &buf[siz++];
}
node get(treap t) {
	if (!t) return node();
	return *t;
}
treap fix(treap t) {
	if (!t) return 0;
	t->cnt = get(t->l).cnt + get(t->r).cnt + 1; 
	return t;
}
treap push(treap t) {
	if (!t) return 0;
	if (t->rev) {
		swap(t->l, t->r);
		if (t->l) t->l->rev ^= 1;
		if (t->r) t->r->rev ^= 1;
		t->rev = 0;
	}
	return t;
}
treap merge(treap a, treap b) {
	if (!a) return b;
	if (!b) return a;
	a = push(a); b = push(b);
	if (a->y > b->y) {
		a->r = merge(a->r, b);
		return fix(a);
	}
	else {
		b->l = merge(a, b->l);
		return fix(b);
	}
}
pair<treap, treap> split(treap t, int k) {
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