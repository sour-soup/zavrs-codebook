struct SVG {
	FILE* out;
	ld sc = 50;
	void open() {
		out = fopen("image.svg", "w");
		fprintf(out, "<svg xmlns='http://www.w3.org/2000/svg' viewBox='-1000 -1000 2000 2000'>\n");
	}
	void line(vec a, vec b) {
		a = a * sc, b = b * sc;
		fprintf(out, "<line x1='%Lf' y1='%Lf' x2='%Lf' y2='%Lf' stroke='black'/>\n", a.x, -a.y, b.x, -b.y);
	}
	void circle(vec a, ld r = -1, string fill_col = "none") {
		r = (r == -1 ? 10 : sc * r);
		a = a * sc;
		fprintf(out, "<circle cx='%Lf' cy='%Lf' r='%Lf' fill='%s' stroke='black' stroke-width='1'/>\n", a.x, -a.y, r, fill_col.c_str());
	}
	void text(vec a, string s) {
		a = a * sc;
		fprintf(out, "<text x='%Lf' y='%Lf' font-size='10px'>%s</text>\n", a.x, -a.y, s.c_str());
	}
	void close() {
		fprintf(out, "</svg>\n");
		fclose(out);
		out = 0;
	}
	~SVG() {
		if (out)
			close();
	}
} svg;