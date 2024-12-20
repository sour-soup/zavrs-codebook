#include "ext/pb_ds/assoc_container.hpp"
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

gp_hash_table<ll, int> h({},{},{},{}, {1 << 16});
// or less_equal<T>/pair<T,int> to get multiset!
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

// HOW TO USE ::
// -- order_of_key(10) returns the number of elements in set/map strictly less than 10
// -- *find_by_order(10) returns 10-th smallest element in set/map (0-based)