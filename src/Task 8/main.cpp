#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

struct Result {
    long long weight = (1LL<<62);
    vector<int> side;          // 0 => S, 1 => T
    long long iterations = 0;  // local search iterations (moves)
    int restarts = 0;
};

static long long computeCutWeight(const vector<int>& side, const vector<Edge>& edges) {
    long long W = 0;
    for (const auto& e : edges) {
        if (side[e.u] != side[e.v]) W += e.w;
    }
    return W;
}

static pair<vector<int>, vector<int>> partitionFromSide(const vector<int>& side) {
    vector<int> S, T;
    for (int v = 0; v < (int)side.size(); v++) {
        if (side[v] == 0) S.push_back(v);
        else T.push_back(v);
    }
    return {S, T};
}

static vector<int> randomInitialCut(int n, mt19937_64& rng) {
    // Ensure both sides are nonempty.
    // Simple approach: assign random sides, then fix if all ended up same.
    vector<int> side(n, 0);
    uniform_int_distribution<int> bit(0, 1);

    while (true) {
        int countT = 0;
        for (int v = 0; v < n; v++) {
            side[v] = bit(rng);
            countT += side[v];
        }
        if (countT != 0 && countT != n) break;
    }
    return side;
}

static Result localImproveBestFlip(
    const vector<vector<pair<int,long long>>>& adj,
    const vector<Edge>& edges,
    vector<int> sideInit
) {
    int n = (int)sideInit.size();
    vector<int> side = std::move(sideInit);

    int countT = 0;
    for (int v = 0; v < n; v++) countT += side[v];
    int countS = n - countT;

    long long W = computeCutWeight(side, edges);

    long long iterations = 0;

    while (true) {
        long long bestDelta = 0; // we need delta < 0 to improve
        int bestV = -1;

        for (int v = 0; v < n; v++) {
            // enforce nonempty sides after flip
            if (side[v] == 0 && countS == 1) continue; // would empty S
            if (side[v] == 1 && countT == 1) continue; // would empty T

            long long delta = 0;
            for (auto [u, w_uv] : adj[v]) {
                if (side[u] == side[v]) delta += w_uv;
                else delta -= w_uv;
            }

            if (delta < bestDelta) {
                bestDelta = delta;
                bestV = v;
            }
        }

        if (bestV == -1) break; // no improving move

        // apply the best move
        if (side[bestV] == 0) { countS--; countT++; }
        else { countT--; countS++; }

        side[bestV] = 1 - side[bestV];
        W += bestDelta;
        iterations++;
    }

    Result res;
    res.weight = W;
    res.side = std::move(side);
    res.iterations = iterations;
    return res;
}

static Result multiStartLocalImprovement(
    const vector<vector<pair<int,long long>>>& adj,
    const vector<Edge>& edges,
    int R,
    unsigned long long seed
) {
    int n = (int)adj.size();
    mt19937_64 rng(seed);

    Result best;
    best.weight = (1LL<<62);
    best.restarts = R;

    for (int r = 1; r <= R; r++) {
        vector<int> init = randomInitialCut(n, rng);
        Result cur = localImproveBestFlip(adj, edges, init);
        if (cur.weight < best.weight) best = cur;
        best.iterations += cur.iterations; // total iterations across restarts (for reporting)
    }
    return best;
}

static Result bruteForceMinCut(int n, const vector<Edge>& edges) {
    // Brute force enumerates subsets of vertices 1..n-1.
    // side[0]=0 is fixed in S.
    // side[v]=1 means vertex v is in T.
    Result best;
    best.weight = (1LL<<62);
    best.side.assign(n, 0);

    if (n <= 1) {
        // No valid nontrivial cut exists; keep default.
        best.weight = 0;
        return best;
    }

    long long totalMasks = 1LL << (n - 1); // works for n-1 <= 62; brute force is anyway small-n
    vector<int> side(n, 0);
    side[0] = 0;

    for (long long mask = 0; mask < totalMasks; mask++) {
        if (mask == 0) continue; // would make T empty

        for (int v = 1; v < n; v++) {
            side[v] = (int)((mask >> (v - 1)) & 1LL);
        }

        long long W = computeCutWeight(side, edges);
        if (W < best.weight) {
            best.weight = W;
            best.side = side;
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    edges.reserve(m);

    vector<vector<pair<int,long long>>> adj(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Parameters (can be adjusted for experiments)
    int R = 50; // number of restarts for local improvement
    unsigned long long seed = 123456789ULL;

    // Run approximate method
    Result approx = multiStartLocalImprovement(adj, edges, R, seed);

    cout << "=== Iterative Improvement (Approx) ===\n";
    cout << "Best cut weight = " << approx.weight << "\n";
    auto [S1, T1] = partitionFromSide(approx.side);
    cout << "S: ";
    for (int v : S1) cout << v << " ";
    cout << "\nT: ";
    for (int v : T1) cout << v << " ";
    cout << "\nTotal local moves (across restarts) = " << approx.iterations << "\n";
    cout << "Restarts = " << approx.restarts << "\n\n";

    // Run exact brute force only for small n
    if (n <= 25) {
        Result exact = bruteForceMinCut(n, edges);
        cout << "=== Brute Force (Exact) ===\n";
        cout << "Minimum cut weight = " << exact.weight << "\n";
        auto [S2, T2] = partitionFromSide(exact.side);
        cout << "S: ";
        for (int v : S2) cout << v << " ";
        cout << "\nT: ";
        for (int v : T2) cout << v << " ";
        cout << "\n";
    } else {
        cout << "=== Brute Force (Exact) ===\n";
        cout << "Skipped (n too large for brute force enumeration).\n";
    }

    return 0;
}