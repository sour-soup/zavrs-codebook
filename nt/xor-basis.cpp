const int K = 60;
 
struct base
{
	array<long long, K> b;
	int size;
 
	long long reduce(long long x)
	{
		for (int i = K - 1; i >= 0; i--)
			if ((x >> i) & 1)
				x ^= b[i];
		return x;
	}
 
	bool check(long long x)
	{
		// выражается ли число через базис?
		return reduce(x) == 0ll;
	}
 
	bool add(long long x)
	{
		// добавить число в базис
		x = reduce(x);
		if (x == 0) return false;
		size++;
		for(int i = K - 1; i >= 0; i--)
			if ((x >> i) & 1)
			{
				b[i] = x;
				return true;
			}
		return true;
	}
 
	base()
	{
		size = 0;
		for (int i = 0; i < K; i++) b[i] = 0ll;
	}
};