mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
clock_t startTime;
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}