priority_queue<int> pq;
ll ans = 0;
forn(i, n) {
	a[i] -= i;
	ans -= a[i]; pq.push(a[i]); pq.push(a[i]); // add the function of the current point
	ans += pq.top(); pq.pop(); // remove the 1-slope
}