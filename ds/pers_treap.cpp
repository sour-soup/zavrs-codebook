mt19937 rnd(42);
struct node {
    node* l, * r;
    int siz, val;
    node() : l(NULL), r(NULL), val(0), siz(0) {}
    node(int c) : l(NULL), r(NULL), val(c), siz(1) {}
};

typedef node* treap;
typedef pair<treap, treap> ptt;

int getsiz(treap t) {
    return t ? t->siz : 0;
}

treap create(int val) {
    //можно заменить на буфер
    return new node(val);
}
treap create() {
    return new node();
}
treap ncopy(treap t) {
    if (!t) return t;
    treap nw = create();
    nw->l = t->l;
    nw->r = t->r;
    nw->val = t->val;
    nw->siz = t->siz;
    return nw;
}
treap fix(treap t) {
    if (!t) return t;
    t->siz = getsiz(t->l) + getsiz(t->r) + 1;
    return t;
}

treap merge(treap a, treap b) {
    a = fix(a);
    b = fix(b);
    if (!a || !b) return a ? ncopy(a) : ncopy(b);
    if (int(rnd() % (getsiz(a) + getsiz(b))) >= getsiz(a)) {
        treap nw = ncopy(b);
        nw->l = merge(a, b->l);
        return fix(nw);
    }
    else {
        treap nw = ncopy(a);
        nw->r = merge(a->r, b);
        return fix(nw);
    }
}

ptt split(treap t, int siz) {
    t = fix(t);
    if (!t) return ptt(NULL, NULL);
    if (getsiz(t->l) >= siz) {
        ptt p = split(t->l, siz);
        treap nw = ncopy(t);
        nw->l = p.second;
        return ptt(p.first, fix(nw));
    }
    else {
        ptt p = split(t->r, siz - getsiz(t->l) - 1);
        treap nw = ncopy(t);
        nw->r = p.first;
        return ptt(fix(nw), p.second);
    }
}

void dfs(treap t, vector<int>& a) {
    if (t->l) dfs(t->l, a);
    a.push_back(t->val);
    if (t->r) dfs(t->r, a);
}

treap build(int l, int r, const vector<int>& a) {
    if (l == r)
        return NULL;
    if (l == r - 1)
        return new node(a[l]);
    int m = (l + r) / 2;
    treap t = new node(a[m]);
    t->l = build(l, m, a);
    t->r = build(m + 1, r, a);
    return fix(t);
}

//нужно делать раз в несколько тысяч операций.
treap rebuild(treap t) {
    vector<int> a;
    dfs(t, a);
    //здесь можно обнулить buf_size
    return build(0, a.size(), a);
}