#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

#pragma region
class solution
{
public:
    int numPairsDivisibleBy60(vector<int> &time);
    vector<int> partitionLabels(string S);
};

//1010. Pairs of Songs With Total Durations Divisible by 60
int solution ::numPairsDivisibleBy60(vector<int> &time)
{
    int res = 0;
    int hash[60] = {};
    for (int t : time)
    {
        int m = t % 60;
        if (m == 0)
        {
            res += hash[0];
        }
        else
        {
            res += hash[60 - m];
        }
        hash[m]++;
    }
    return res;
}

//763. Partition Labels
vector<int> solution ::partitionLabels(string S)
{
    map<char, tuple<int, int>> intervals;
    vector<tuple<int, int>> v;
    vector<int> res;
    for (int i = 0; i < S.length(); i++)
    {
        auto index = intervals.find(S[i]);
        int start = i, end = i;
        if (index != intervals.end())
        {
            start = get<0>(intervals[S[i]]);
        }
        get<0>(intervals[S[i]]) = start;
        get<1>(intervals[S[i]]) = end;
    }

    for (auto const &i : intervals)
    {
        v.push_back(i.second);
    }
    sort(v.begin(), v.end(), [](const tuple<int, int> &a, const tuple<int, int> &b) -> bool {
        return get<0>(a) < get<0>(b);
    });
    int start = 0;
    int end = get<1>(v[0]);
    for (auto it = next(v.begin()); it != v.end(); ++it)
    {
        int s = get<0>(*it);
        if (s > end)
        {
            res.push_back(end - start + 1);
            start = s;
        }
        end = max(end, get<1>(*it));
    }
    res.push_back(end - start + 1);
    return res;
}
#pragma endregion

#pragma region //200. Number of Islands
class solution200
{
public:
    int numIslands(vector<vector<char>> &grid);
    void bfs(int x, int y, bool **visited, vector<vector<char>> &grid);
};

int solution200::numIslands(vector<vector<char>> &grid)
{
    int res=0;
    bool **visited = new bool *[grid.size()];
    for (int i = 0; i < grid.size(); i++)
        visited[i] = new bool[grid[0].size()]{false};

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == '1' && !visited[i][j])
            {
                res++;
                bfs(i, j, visited, grid);
            }
        }
    }
    return res;
}

void solution200::bfs(int x, int y, bool **visited, vector<vector<char>> &grid)
{
    queue<pair<int, int>> bfsqueue;
    bfsqueue.push({x, y});
    visited[x][y] = true;

    tuple<int, int> directions[4] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}};

    while (!bfsqueue.empty())
    {
        auto cur = bfsqueue.front();
        bfsqueue.pop();
        for (auto &d : directions)
        {
            int newx = get<0>(d) + cur.first;
            int newy = get<1>(d) + cur.second;
            if (newx >= 0 && newx < grid.size() && newy >= 0 && newy < grid[0].size() && grid[newx][newy]=='1' && !visited[newx][newy])
            {
                bfsqueue.push({newx, newy});
                visited[newx][newy] = true;
            }
        }
    }
}
#pragma endregion

int main()
{
    solution200 s;
    vector<vector<char>> grid
    {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };

    auto r = s.numIslands(grid);
    cout<<r<<endl;

}