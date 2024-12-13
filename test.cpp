#include "bits/stdc++.h"

using namespace std;
   
int main(){
    ifstream fi("data.txt");
    string data;
    while(getline(fi,data)){
        string tmp = "";
        vector<string> row;
        for(char c : data){
            if(c == '|'){
                row.push_back(tmp);
                tmp = "";
                continue;
            }
            tmp += c;
        }
        // tmp += data[data.size() - 1];
        row.push_back(tmp);
        for(auto x : row ){
            cout << x << endl;
        }
    }
}
