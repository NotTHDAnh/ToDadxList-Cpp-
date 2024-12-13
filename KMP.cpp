#include <string>
#include <iostream>

using namespace std;

const int mxN = 1e5;

class KMP{
private:
    int lps[mxN];
public:
    void assignLps(string pattern){
        int n = (int)pattern.size();
        lps[0] = 0;
        int i = 1, j = 0;
        for(;i < n;){
            if(pattern[i] == pattern[j]){
                ++j;
                lps[i] = j;
                ++i;
            }
            else if(j != 0) j = lps[j - 1];
            else ++i;
        }
    }

    bool find(string s,string pattern){
        int i = 0, j = 0, n = (int)s.size(), m = (int)pattern.size();
        for(;i < n;){
            if(s[i] == pattern[j]){
                ++j;
                ++i;
                if(j == m) return 1;
            }
            else if (j != 0) j = lps[j - 1];
            else ++i;
        }
        return 0;
    }
};
