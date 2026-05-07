#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <unordered_map>
using namespace std;

//  Data Structures 

struct Point  { double x, y; };
struct IPoint { int x, y; };

struct Segment {
    Point start, end;
    string str() const {
        ostringstream o;
        o << fixed << setprecision(2)
          << "(" << start.x << "," << start.y << ")->(" << end.x << "," << end.y << ")";
        return o.str();
    }
};

struct Solution {
    bool found=false, optimal=false, allCovered=false;
    int  n=0, linesUsed=0;
    double solveTime=0;
    string method="DP-Backtracking";
    vector<Segment> segments;
};

//  Geometry Helpers 

bool onSeg(const Point& A, const Point& B, const Point& P) {
    double cross = (B.x-A.x)*(P.y-A.y)-(B.y-A.y)*(P.x-A.x);
    if (fabs(cross)>1e-9) return false;
    return min(A.x,B.x)-1e-9<=P.x && P.x<=max(A.x,B.x)+1e-9 &&
           min(A.y,B.y)-1e-9<=P.y && P.y<=max(A.y,B.y)+1e-9;
}

vector<int> latticeOnSeg(int x1,int y1,int x2,int y2,int n) {
    vector<int> pts;
    int dx=x2-x1, dy=y2-y1;
    int g=__gcd(abs(dx),abs(dy));
    if (g==0) {
        if (x1>=0&&x1<n&&y1>=0&&y1<n) pts.push_back(y1*n+x1);
        return pts;
    }
    int sx=dx/g, sy=dy/g;
    for (int t=0;t<=g;t++) {
        int cx=x1+t*sx, cy=y1+t*sy;
        if (cx>=0&&cx<n&&cy>=0&&cy<n) pts.push_back(cy*n+cx);
    }
    return pts;
}

//  DP + Backtracking 

static int G_N, G_TARGET, G_BEST;
static vector<Segment> G_BEST_SOL, G_PATH;
static unordered_map<long long,int> G_MEMO;
static vector<IPoint> G_CANDS;

void buildCands(int n) {
    G_CANDS.clear();
    for (int x=-1;x<=n;x++)
        for (int y=-1;y<=n;y++)
            G_CANDS.push_back({x,y});
}

long long encState(int cx,int cy,int mask) {
    return ((long long)mask<<16)|((cx+1)<<8)|(cy+1);
}

void backtrack(int cx,int cy,int covered,int left) {
    if (covered==G_TARGET) {
        int used=(int)G_PATH.size();
        if (G_BEST==-1||used<G_BEST) {
            G_BEST=used;
            G_BEST_SOL=G_PATH;
        }
        return;
    }
    if (left==0) return;

    long long key=encState(cx,cy,covered);
    auto it=G_MEMO.find(key);
    if (it!=G_MEMO.end()&&it->second>=left) return;

    for (auto& ep:G_CANDS) {
        if (ep.x==cx&&ep.y==cy) continue;

        auto pts=latticeOnSeg(cx,cy,ep.x,ep.y,G_N);
        int nm=covered;
        bool anyNew=false;

        for (int p:pts)
            if (!(covered&(1<<p))) {
                nm|=(1<<p);
                anyNew=true;
            }

        if (!anyNew) continue;

        G_PATH.push_back({{(double)cx,(double)cy},{(double)ep.x,(double)ep.y}});
        backtrack(ep.x,ep.y,nm,left-1);
        G_PATH.pop_back();
    }
    G_MEMO[key]=left;
}

Solution dpSolve(int n) {
    Solution sol;
    sol.n=n;

    G_N=n;
    G_TARGET=(1<<(n*n))-1;
    buildCands(n);

    int maxL=2*n-2;
    auto t0=chrono::steady_clock::now();

    for (auto& st:G_CANDS) {
        G_MEMO.clear();
        G_PATH.clear();
        G_BEST=-1;
        G_BEST_SOL.clear();

        backtrack(st.x,st.y,0,maxL);

        if (!G_BEST_SOL.empty()) {
            sol.found=true;
            sol.allCovered=true;
            sol.segments=G_BEST_SOL;
            sol.linesUsed=G_BEST;
            sol.optimal=(G_BEST==maxL);
            break;
        }

        if (chrono::duration<double>(chrono::steady_clock::now()-t0).count()>30.0)
            break;
    }

    sol.solveTime=
        chrono::duration<double>(chrono::steady_clock::now()-t0).count();

    return sol;
}

// Verification 

bool verify(const Solution& sol) {
    int n=sol.n;
    vector<bool> cov(n*n,false);

    for (auto& seg:sol.segments)
        for (int x=0;x<n;x++)
            for (int y=0;y<n;y++)
                if (onSeg(seg.start,seg.end,{(double)x,(double)y}))
                    cov[y*n+x]=true;

    for (bool v:cov) if (!v) return false;
    return true;
}

// Printing

void printSol(const Solution& sol) {
    int n=sol.n;

    cout<<"\n===== "<<n<<"x"<<n<<" Lattice =====\n";
    cout<<"Lines used: "<<sol.linesUsed<<" (target "<<2*n-2<<")\n";
    cout<<"Optimal: "<<(sol.optimal?"YES":"NO")<<"\n";
    cout<<"Time: "<<fixed<<setprecision(4)<<sol.solveTime<<" s\n";

    cout<<"\nSegments:\n";
    for (int i=0;i<(int)sol.segments.size();i++)
        cout<<"["<<i+1<<"] "<<sol.segments[i].str()<<"\n";

    cout<<"\nVerification: "
        <<(verify(sol)?"PASS":"FAIL")<<"\n";
}

//Main

int main() {
    cout<<"DP Solver Only \n";

    int n;
    cout<<"Enter n (>2, 0 to quit): ";

    while (cin>>n && n!=0) {
        if (n<=2) {
            cout<<"n must be >2\n";
            continue;
        }

        if (n >= 5) {
            cout<<"\n[WARNING]\n";
            cout<<"For n >= 5, the DP + backtracking approach becomes\n";
            cout<<"computationally infeasible (exponential explosion).\n";
            cout<<"This case is NOT practical to run.\n\n";
            continue;
        }

        Solution sol = dpSolve(n);

        if (!sol.found) {
            cout<<"No solution found within limits.\n";
        } else {
            printSol(sol);
        }

        cout<<"\nEnter n: ";
    }

    return 0;
}
