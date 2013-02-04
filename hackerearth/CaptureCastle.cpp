#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

string solve() {
    int M, N;
    cin>>M>>N;
    int buffer;
    vector<vector<int> > grid;
    vector<vector<int> > dp (M, vector<int>(N));
    for (int i=0; i<M; i++) {
        vector<int> row;
        for (int j=0; j<N; j++) {
            cin>>buffer;
            row.push_back(buffer);
        }
        grid.push_back(row);
    }
    int x, y, t;
    cin>>x>>y>>t;
    
    dp[0][0]=grid[0][0];
    for (int i=1; i<M; i++) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    for (int j=1; j<N; j++) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }
    
    for (int i=1; i<x; i++) {
        for (int j=1; j<y; j++) {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }
    
    if (dp[x-1][y-1]<t) {
        stringstream ss;
        ss<<"YES\n"<<(t-dp[x-1][y-1]);
        return ss.str();
    } else {
        stringstream ss;
        ss<<"NO"<<endl<<dp[x-1][y-1];
        return ss.str();
    }
    
}

int main()
{
    int T;
    cin>>T;
    
    for (int i=0; i<T; i++) {
        cout<<solve()<<endl;
    }
    return 0;
}

