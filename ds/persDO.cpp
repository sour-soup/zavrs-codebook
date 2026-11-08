struct node {
    pt mx;
    int l = -1, r = -1;
};

const int N = 5e5 + 10; // build
const int Q = 5e5 + 10; // queries
const int LIM = 4*N + 20*Q;
node buf[LIM]; // vector<node>buf(LIM);
int cur = 0;

int make(int x, int ind) {
    buf[cur].mx = {x, ind};
    return cur++;
}
int merge(int l, int r) {
    buf[cur].mx = max(buf[l].mx, buf[r].mx);
    buf[cur].l = l; buf[cur].r = r;
    return cur++;
}

int build(int l, int r, int val){
    if(l + 1 == r)
        return make(val, -1);
    int mid = (l + r) / 2;
    int L = build(l, mid, val);
    int R = build(mid, r, val);
    return merge(L, R);
}

int update(int v, int l, int r, int pos, int val) {
    if(l + 1 == r)
        return make(val, pos);
    int mid = (l + r) / 2;
    int L = buf[v].l;
    int R = buf[v].r;
    if (pos < mid)
        L = update(L, l, mid, pos, val);
    else
        R = update(R, mid, r, pos, val);
    return merge(L, R);
}

pt get(int v, int l, int r, int ql, int qr) {
    if(l == ql and r == qr)
        return buf[v].mx;
    int mid = (l + r) / 2;
    pt res = {-INF, -INF};
    if (ql < mid)
        res = max(res, get(buf[v].l, l, mid, ql, min(qr, mid)));
    if (qr > mid)
        res = max(res, get(buf[v].r, mid, r, max(ql, mid), qr));
    return res;
}