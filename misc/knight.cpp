li get_dist(li dx, li dy) {
	if (++(dx = abs(dx)) > ++(dy = abs(dy))) swap(dx, dy);
	if (dx == 1 && dy == 2) return 3;
	if (dx == 3 && dy == 3) return 4;
	li lb = max(dy / 2, (dx + dy) / 3);
	return ((dx ^ dy ^ lb) & 1) ? ++lb : lb;
}