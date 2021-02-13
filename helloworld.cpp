#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}

class solution{
    public:
        //1010. Pairs of Songs With Total Durations Divisible by 60
        int numPairsDivisibleBy60(vector<int> & time)
        {
            int res =0;
            int hash[60] = {};
            for(int t : time)
            {
                int m = t%60;
                if(m==0)
                {
                    res += hash[0];
                }
                else
                {
                    res += hash[60-m];
                }
                hash[m]++;
            }
            return res;
        }
}