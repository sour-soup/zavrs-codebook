void push(int v, int l, int r){
	if (upd[v].x > mn[v]){
		if (l != r - 1){
			upd[v * 2].x = max(upd[v * 2].x, upd[v].x - upd[v * 2].y);
			upd[v * 2 + 1].x = max(upd[v * 2 + 1].x, upd[v].x - upd[v * 2 + 1].y);
		}
		t[v] += cnt[v] * (upd[v].x - mn[v]);
		mn[v] = upd[v].x;
	}
	if (upd[v].y){
		if (l != r - 1){
			upd[v * 2].y += upd[v].y;
			upd[v * 2 + 1].y += upd[v].y;
		}
		t[v] += (r - l) * upd[v].y;
		mn[v] += upd[v].y;
		mn2[v] = min(INF64, mn2[v] + upd[v].y);
	}
	upd[v] = mp(-INF64, 0);
}

void merge(int v){
	t[v] = t[v * 2] + t[v * 2 + 1];
	mn[v] = min(mn[v * 2], mn[v * 2 + 1]);
	if (mn[v * 2] < mn[v * 2 + 1]){
		mn2[v] = min(mn2[v * 2], mn[v * 2 + 1]);
		cnt[v] = cnt[v * 2];
	}
	else if (mn[v * 2 + 1] < mn[v * 2]){
		mn2[v] = min(mn2[v * 2 + 1], mn[v * 2]);
		cnt[v] = cnt[v * 2 + 1];
	}
	else{
		mn2[v] = min(mn2[v * 2], mn2[v * 2 + 1]);
		cnt[v] = cnt[v * 2] + cnt[v * 2 + 1];
	}
}

void build(int v, int l, int r){
	upd[v] = mp(-INF64, 0);
	if (l == r - 1){
		t[v] = a[l];
		cnt[v] = 1;
		mn[v] = a[l];
		mn2[v] = INF64;
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m, r);
	merge(v);
}

void add(int v, int l, int r, int L, int R, int val){
	push(v, l, r);
	if (L >= R)
		return;
	if (l == L && r == R){
		upd[v].y += val;
		push(v, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(v * 2, l, m, L, min(m, R), val);
	add(v * 2 + 1, m, r, max(m, L), R, val);
	merge(v);
}

void cutmx(int v, int l, int r, int L, int R, int val){
	push(v, l, r);
	if (L >= R || mn[v] >= val)
		return;
	if (l == L && r == R && mn2[v] > val){
		upd[v].x = val;
		push(v, l, r);
		return;
	}
	int m = (l + r) / 2;
	cutmx(v * 2, l, m, L, min(m, R), val);
	cutmx(v * 2 + 1, m, r, max(m, L), R, val);
	merge(v);
}

li get(int v, int l, int r, int L, int R){
	push(v, l, r);
	if (L >= R)
		return 0;
	if (l == L && r == R)
		return t[v];
	int m = (l + r) / 2;
	li res = get(v * 2, l, m, L, min(m, R)) + get(v * 2 + 1, m, r, max(m, L), R);
	merge(v);
	return res;
}