// This is equivalent to calculating lower_bound on prefix sums array
// LOGN = log(N)
int fenwick[N]; // fenwick array
int fenwick_search(int v) {
	int sum = 0;
	int pos = 0;
	for(int i=LOGN; i>=0; i--) {
		if(pos + (1 << i) < N and sum + fenwick[pos + (1 << i)] < v) {
			sum += fenwick[pos + (1 << i)];
			pos += (1 << i);
		}
	}
	return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
}