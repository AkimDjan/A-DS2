#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;


bool comparator(pair<string,int> a, pair<string,int> b) {
    return a.second<b.second;
}

string code_huffman(const string& s) {
    unordered_set<char> st; for (char c : s) {st.emplace(c);} // нашли уникальные буквы
    unordered_map<char,string> ans; unordered_map<string,int> mp; 
    for (char c : st) {mp.emplace(string(1,c),0); ans.emplace(c,"");} 
    for (char c : s) {mp[string(1,c)]+=1;} // посчитали частоту букв
    vector<pair<string,int>> v;
    for (auto p : mp) {v.push_back(p);} // завели все в массив 
    if (v.size()==1) {
        char c=v[0].first[0];
        ans[c]="0";
    }
    while (v.size()>1) {
        sort(v.begin(), v.end(), comparator); 
        pair<string,int> p1=v[0]; pair<string,int> p2=v[1]; // взяли 2 минимальных
        pair<string,int> p_new; 
        p_new.first=p1.first+p2.first; 
        p_new.second=p1.second+p2.second; // сделали им одного родителя
        v.push_back(p_new);
        v.erase(v.begin()); v.erase(v.begin()); 
        for (char c : p1.first) {ans[c]='0'+ans[c];}
        for (char c : p2.first) {ans[c]='1'+ans[c];} 
    }
    string ans_str="";
    for (char c : s) {ans_str+=ans[c];}
    for (char c : st) {cout<<c<<": "<<ans[c]<<"\n";}
    return ans_str;
}

int main() { 
    string s; cin>>s;
    string ans = code_huffman(s);
    cout<<ans<<"\n";
    return 0;
}
