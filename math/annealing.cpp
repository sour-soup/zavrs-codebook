const ld t0 = 1e5; // or 1e9
const ld chg = 0.99999;
ld temp = t0;
int cur = calc();
int ans = cur;
while (temp causes updates || clock) {
	// save the current state
	// make temp / t0 fraction of updates
	int tmp = calc();
	ans = min(ans, tmp);
	if (tmp < cur) {
		cur = tmp;
	}
	else{
		if (rnd_ld(0, 1) <= exp((cur - tmp) / temp))
			cur = tmp;
		else
			// restore the saved state
	}
	temp *= chg;
}