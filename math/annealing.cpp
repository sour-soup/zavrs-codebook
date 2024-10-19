const ld t0 = 1e5; // or 1e9; init temp
const ld chg = 0.99999;
ld temp = t0;
int cur = random_state(); // any random valid state
int ans = cur;
// find minimum of function f
while (temp > END_TEMP && elapsed_time() <= time_limit) {
	// save the current state
	// make temp / t0 fraction of updates
	int next = neighbor(s);
	if (func(ans) > func(next)) {
		cur = tmp;
	}
	else{
		// Probability to go to worse state
		if (rnd_ld(0, 1) <= exp((cur - tmp) / temp))
			cur = tmp;
		else
			// restore the saved state
	}
	temp *= chg;
}