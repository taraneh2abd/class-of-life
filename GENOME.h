#pragma once
#include <algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;
typedef string str;
#define pb push_back
#define fr(i,n) for(int i=0;i<int(n);i++)
////////////////////////////

class Genome{
protected:
    string RNA;
    string DNA[2];
    int RNA_SIZE;
public:
    Genome();
    //Genome(string _RNA, string* _DNA);
    char comp(char c);
    void set_RNA(string _RNA);
    void set_DNA(string* _DNA);
    str get_RNA();
    str get_DNA();
    int get_RNA_size();
    str complete(str s);
    void small_mutation(char c, char c1, int n);
    //kmp algorithm o(n):
    void replaceSubstring(string& str, int start, int length, const string& replacement);
    vector<int>longest_prefix_also_sufix(str s);
    void large_mutation(str pat,str exchange);
    void reverse_mutation(str s);
};