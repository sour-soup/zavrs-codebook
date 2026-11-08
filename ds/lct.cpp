struct node {
	node *ch[2], *fa;
	node *pfa;
	int sum, v, rev, id;
	node(int s, int id): id(id), v(s), sum(s), rev(0), fa(nullptr), pfa(nullptr) {
		ch[0] = nullptr;
		ch[1] = nullptr;
	}
	int relation() {
		return this == fa->ch[0] ? 0 : 1;
	}
	// с некоммутативными операциями apply_rev будет менять ответ, поэтому нужно хранить два агрегата, в прямом и обратном порядке
	void apply_rev() { swap(ch[0], ch[1]); rev ^= 1; }
	void push() {
		if (!rev) return;
		if (ch[0]) ch[0]->apply_rev();
		if (ch[1]) ch[1]->apply_rev();
		rev = false;
	}
	void pull() { // меняем для других запросов
		sum = v;
		if (ch[0]) sum += ch[0]->sum;
		if (ch[1]) sum += ch[1]->sum;
	}
	void rotate() {
		if (fa->fa) fa->fa->push();
		fa->push(), push(), swap(pfa, fa->pfa);
		int d = relation();
		node *t = fa;
		if (t->fa) t->fa->ch[t->relation()] = this;
		fa = t->fa, t->ch[d] = ch[d ^ 1];
		if (ch[d ^ 1]) ch[d ^ 1]->fa = t;
		ch[d ^ 1] = t, t->fa = this;
		t->pull(), pull();
	}
	void splay() { // поднимает узел в корень splay дерева
		while (fa) {
			if (!fa->fa) {
				rotate();
				continue;
			}
			fa->fa->push(), fa->push();
			if (relation() == fa->relation()) fa->rotate(), rotate();
			else rotate(), rotate();
		}
	}
	void expose() { // splay + отрезаем путь, что был глубже
		splay(), push();
		if (ch[1]) {
			ch[1]->fa = nullptr, ch[1]->pfa = this;
			ch[1] = nullptr, pull();
		}
	}
	bool splice() { // приклеиваем текущий путь к путю-родителю (pfa)
		splay();
		if (!pfa) return false;
		pfa->expose(), pfa->ch[1] = this, fa = pfa;
		pfa = nullptr, fa->pull();
		return true;
	}
	void access() { // делает путь от корня дерева до узла одним splay-деревом
		expose();
		while (splice());
	}
	void evert() { access(), splay(), apply_rev(); } // делаем узел корнем всего дерева
	int query() { return sum; } 
};

namespace lct {
node *sp[maxn];
void make(int ind, int val) {
	sp[u] = new node(val, ind);
}
void link(int u, int v) { // u - родитель v
	sp[v]->evert();
	sp[v]->pfa = sp[u];
}
void cut(int u, int v) { // u - родитель v
	sp[u]->evert();
	sp[v]->access(), sp[v]->splay(), sp[v]->push();
	sp[v]->ch[0]->fa = nullptr;
	sp[v]->ch[0] = nullptr;
	sp[v]->pull();
}
void modify(int u, int v) {
	sp[u]->splay();
	sp[u]->v = v;
	sp[u]->pull();
}
int query(int u, int v) {
	sp[u]->evert(), sp[v]->access(), sp[v]->splay();
	return sp[v]->query();
}
int find(int u) { // находим корень дерева, через него можно проверить связность
	sp[u]->access();
	sp[u]->splay();
	node *p = sp[u];
	while (true) {
		p->push();
		if (p->ch[0]) p = p->ch[0];
		else break;
	}
	p->splay(); // добавил недавно, не проверял
	return p->id;
}} 