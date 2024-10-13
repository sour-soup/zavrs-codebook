default_random_engine gen;
uniform_real_distribution<ld> distr(l, r);
ld rnd_ld(){ return distr(gen); }