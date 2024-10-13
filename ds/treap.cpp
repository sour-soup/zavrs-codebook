struct node {
	int key, prior;
	int siz;
	node *l, *r;
	node() {}
	node(int key, int prior) : key(key), prior(prior), siz(1), l(NULL), r(NULL) {}
};

typedef node* tnode;
typedef pair<tnode, tnode> ptt;

int getsiz(tnode v) {
	return v ? v->siz : 0;
}
tnode fix(tnode v) {
	if (!v) return v;
	v->siz = getsiz(v->l) + 1 + getsiz(v->r);
	return v;
}
ptt split(tnode t, int key) {
	if (!t)
		return mp(t, t);
	ptt p;
	if (key < t->key) {
		p = split(t->l, key);
		t->l = p.y;
		return mp(p.x, fix(t));
	} else {
		p = split(t->r, key);
		t->r = p.x;
		return mp(fix(t), p.y);
	}
}
tnode insert(tnode t, tnode it) {
	if (!t)
		return it;
	if (it->prior > t->prior) {
		ptt p = split(t, it->key);
		it->l = p.x, it->r = p.y;
		return fix(it);
	} else if (it->key < t->key) {
		t->l = insert(t->l, it);
		return fix(t);
	} else {
		t->r = insert(t->r, it);
		return fix(t);
	}
}
tnode merge(tnode l, tnode r) {
	if (!l || !r)
		return l ? l : r;
	if (l->prior > r->prior) {
		l->r = merge(l->r, r);
		return fix(l);
	} else {
		r->l = merge(l, r->l);
		return fix(r);
	}
}
tnode erase(tnode t, int key) {
	if (t->key == key)
		return merge(t->l, t->r);
	if (key < t->key) {
		t->l = erase(t->l, key);
		return fix(t);
	} else {
		t->r = erase(t->r, key);
		return fix(t);
	}
}
tnode unite(tnode l, tnode r) {
	if (!l || !r)
		return l ? l : r;
	if (l->prior < r->prior)
		swap(l, r);
	ptt p =	split(r, l->key);
	l->l = unite(l->l, p.x);
	l->r = unite(l->r, p.y);
	return fix(l);
}