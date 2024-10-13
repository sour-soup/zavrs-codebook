string find_fraction(li a, li b){
	string path;
	while (a > 1 || b > 1) {
		if (a > b) {
			path += to_string((a - 1) / b) + "A";
			a -= ((a - 1) / b) * b;
		}
		else {
			path += to_string((b - 1) / a) + "B";
			b -= ((b - 1) / a) * a;
		}
	}
	return path;
}