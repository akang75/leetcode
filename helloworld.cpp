#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

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
    vector<tuple<int,int>> v;
    vector<int> res;
    for (int i = 0; i < S.length(); i++)
    {
        auto index = intervals.find(S[i]);
        int start=i, end = i;
        if(index != intervals.end())
        {
            start = get<0>(intervals[S[i]]);
        }
        get<0>(intervals[S[i]]) = start;
        get<1>(intervals[S[i]]) = end;
    }

    for(auto const& i :intervals)
    {
        v.push_back(i.second);
    }
    sort(v.begin(), v.end(), [](const tuple<int, int> & a, const tuple<int,int> &b) -> bool
    {
        return get<0>(a) < get<0>(b);
    });
    int start = 0;
    int end = get<1>(v[0]);
    for(auto it = next(v.begin());it!=v.end();++it)
    {
        int s = get<0>(*it);
        if(s>end)
        {
            res.push_back(end - start + 1);
            start = s;
        }
        end = max(end, get<1>(*it));
    }
    res.push_back(end-start+1);
    return res;
}

int main()
{
    solution s;
    auto r = s.partitionLabels("eccbbbbdec");
    for(int i=0;i<r.size();i++)
        cout<< r.at(i) << " ";
}