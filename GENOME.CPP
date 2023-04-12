#include "GENOME.h"
#include <algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;
typedef string str;
#define pb push_back
#define fr(i,n) for(int i=0;i<int(n);i++)
////////////////////////////////////////////////////////////////

Genome::Genome(){}
char  Genome::comp(char c){
    switch (c)
    {
    case 'A':
        return 'T';
        break;
    case 'T':
        return 'A';
        break;
    case 'C':
        return 'G';
        break;
    case 'G':
        return 'C';
        break;
    }
    return '?';
}
void  Genome::set_RNA(string _RNA){
    RNA=_RNA; 
    DNA[0]=RNA;
    RNA_SIZE=RNA.size(); 
    fr(i,RNA_SIZE)
        DNA[1]+=comp(RNA[i]);
}
void  Genome::set_DNA(string* _DNA){
    DNA[0]=_DNA[0];
    RNA=DNA[0];
    DNA[1]=_DNA[1];  
    RNA_SIZE=DNA[0].size();     
}
str  Genome::get_RNA(){
    return RNA;
}
str  Genome::get_DNA(){
    return DNA[1];
}
int  Genome::get_RNA_size(){
    return RNA_SIZE;
}
str  Genome::complete(str s){
    str new_s="";
    for(char i:s){
        new_s+=comp(i);
    }
    return new_s;
}
void  Genome::small_mutation(char c, char c1, int n){
    int number=0;
    fr(i,RNA.length()){

        if(DNA[0][i]==c){
            DNA[0][i]=c1;
            DNA[1][i]=comp(c1);
            number++;
        }
        else if(DNA[1][i]==c){
            DNA[1][i]=c1;
            DNA[0][i]=comp(c1);
            number++;
        }
        if(number==n){
            break;
        }            
    }
    cout<<"\nafter small_mutation ";
    cout<<"DNA is :\n"<<DNA[0]<<"\n"<<DNA[1]<<"\n";
    cout<<"___________\n";
}
//a new function for KMP algorithm :
vector<int>  Genome::longest_prefix_also_sufix(str s){
    int n=s.size();
    int first=0; int second=1;
    int till_now=0;
    vector<int>lps(n);
    while(second<n){
        if(s[first]==s[second]){
            till_now++;
            lps[second] =till_now;
            first++;second++;
        }
        else{
            lps[second]=0;
            first=0; second++;
        }
    }
    return lps;
}
        void Genome::replaceSubstring(string& str, int start, int length, const string& replacement) {
        str.replace(start, length, replacement);
    }

    void  Genome::large_mutation(str pat,str exchange){
    int n_exchange_str=pat.length();
    vector<int>lps=longest_prefix_also_sufix(pat); 
    int M = pat.size();
    int N = RNA.size();
    int ind_found;
    int i0 = 0; // index for DNA[0]
    int i1 = 0; // index for DNA[1]
    int j0 = 0; // index for pat[] in DNA[0]
    int j1 = 0; // index for pat[] in DNA[1]
    int found_in_wich_string=-1;
    while ((N - i0) >= (M - j0) && (N - i1) >= (M - j1)) {
        ///for DNA[1]:
        if (pat[j1] == DNA[1][i1]) {
            j1++;
            i1++;
        }
        if (j1 == M) {
            ind_found=i1 - j1;
            j1 = lps[j1 - 1];
            found_in_wich_string=1;
            //if you want to change all paterns remove this break:
            break;
        }
        else if (i1 < N && pat[j1] != DNA[1][i1]) {
            if (j1 != 0)
                j1 = lps[j1 - 1];
            else
                i1 = i1 + 1;
        }
    }
    if(found_in_wich_string==-1){
            i0=0;i1=0;
            while ((N - i0) >= (M - j0) && (N - i1) >= (M - j1)) {
            // /for DNA[0]:
            if (pat[j0] == DNA[0][i0]) {
                j0++;
                i0++;
            }
            if (j0 == M) {
                ind_found=i0 - j0;
                j0 = lps[j0 - 1];
                found_in_wich_string=0;
                //if you want to change all paterns remove this break:
                break;
            }
            else if (i0 < N && pat[j0] != DNA[0][i0]) {
                if (j0 != 0)
                    j0 = lps[j0 - 1];
                else
                    i0 = i0 + 1;
            }
        }
    }
    cout<<"founded in index:"<<ind_found;
    if(found_in_wich_string==1){
        cout<<" in DNA[1]"<<"\n";
        replaceSubstring(DNA[1], ind_found, n_exchange_str, exchange);
        replaceSubstring(DNA[0], ind_found, n_exchange_str, complete(exchange));
    }
    else{
        cout<<" in DNA[0]"<<"\n";
        replaceSubstring(DNA[0], ind_found, n_exchange_str, exchange);
        replaceSubstring(DNA[1], ind_found, n_exchange_str, complete(exchange));
    }
    RNA=DNA[0];
    cout<<"after large_mutation ";
    cout<<"DNA is :\n"<<DNA[0]<<"\n"<<DNA[1]<<"\n";
    cout<<"___________\n";   
}
void  Genome::reverse_mutation(str s){
    str rev=s; reverse(rev.begin(),rev.end());
    large_mutation(s,rev);
}
