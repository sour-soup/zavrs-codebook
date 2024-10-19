vector<int>dp(n + 1, INF);
dp[0] = -INF;
for (int i = 0; i < n; i++) {
    int j = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    if (dp[j - 1] < a[i] && a[i] < dp[j])
        dp[j] = a[i];
}