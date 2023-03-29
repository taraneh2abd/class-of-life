#include <bits/stdc++.h>
using namespace std;
typedef string str;
#define pb push_back
#define fr(i,n) for(int i=0;i<int(n);i++)


//////////////////////////////////////
class Genome{
protected:
    string RNA;
    string DNA[2];
    int RNA_SIZE=RNA.size();
public:
    Genome(){
        RNA = "";
        DNA[2] = {"",""};
        RNA_SIZE=0;
    }
    Genome(string _RNA, string* _DNA){
        RNA=_RNA; RNA_SIZE=RNA.size(); 
        DNA[0]=_DNA[0];
        DNA[1]=_DNA[1];
    }
    char comp(char c){
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
    void set_RNA(string _RNA){
        RNA=_RNA; RNA_SIZE=RNA.size(); 
    }
    void set_DNA(string* _DNA){
        DNA[0]=_DNA[0];
        DNA[1]=_DNA[1];  
        RNA_SIZE=DNA[0].size();     
    }
    str get_RNA(){
        return RNA;
    }
    str* get_DNA(){
        return DNA;
    }
    int get_RNA_size(){
        return RNA_SIZE;
    }
    str complete(str s){
        str new_s="";
        for(char i:s){
            new_s+=comp(i);
        }
        return new_s;
    }
    void make_and_print_complement(){
        cout<<"complement is :\n";
        DNA[0]=RNA;DNA[1]="";
        fr(i,RNA_SIZE){
            DNA[1]+=comp(RNA[i]);
            cout<<DNA[1][i];
        }
        cout<<"___________";
    }
    void small_mutation(char c, char c1, int n){
        int number=0;
        fr(i,RNA.length()){

            //////////RNA:
            if(RNA[i]==c){
                RNA[i]=c1;
                number++;
            }
            if(number==n){
                break;
            }

            /////////DNA:
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
        cout<<"after small_mutation ";
        cout<<"DNA is :\n"<<DNA[0]<<"\n"<<DNA[1]<<"\n\n";
        cout<<"___________\n";
    }
    //a new function for KMP algorithm :
    vector<int>longest_prefix_also_sufix(str s){
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
        void large_mutation(str pat,str exchange){
        vector<int>lps=longest_prefix_also_sufix(pat); 
        int M = pat.size();
        int N = RNA.size();
        int ind_found;
        int i0 = 0; // index for DNA[0]
        int i1 = 0; // index for DNA[1]
        int j0 = 0; // index for pat[] in DNA[0]
        int j1 = 0; // index for pat[] in DNA[1]
        int found_in_wich_string;
        while ((N - i0) >= (M - j0) && (N - i1) >= (M - j1)) {
            //for DNA[0]:
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
        cout<<"founded in index:"<<ind_found<<endl;
        if(found_in_wich_string==1){
            DNA[1]=DNA[1].substr(0,ind_found)+exchange+DNA[1].substr(ind_found,DNA[1].size()-1);
            DNA[0]=DNA[0].substr(0,ind_found)+complete(exchange)+DNA[0].substr(ind_found,DNA[0].size()-1);
        }
        else{
            DNA[1]=DNA[1].substr(0,ind_found)+complete(exchange)+DNA[1].substr(ind_found,DNA[1].size()-1);
            DNA[0]=DNA[0].substr(0,ind_found)+exchange+DNA[0].substr(ind_found,DNA[0].size()-1);
        }
        RNA=DNA[0];
        cout<<"after large_mutation ";
        cout<<"DNA is :\n"<<DNA[0]<<"\n"<<DNA[1]<<"\n";
        cout<<"___________\n";
    }
    void reverse_mutation(str s){
        str rev=s; reverse(rev.begin(),rev.end());
        large_mutation(s,rev);
    }
};

///////////////////////////////////////
class cell:public Genome{
    int tedad_chromosome;
    vector<Genome>chromosomes;
    public:
        cell(){
            tedad_chromosome=0;
            cout<<RNA;
        }
        void set_chromosomes(vector<Genome>_chromosomes){
            chromosomes=_chromosomes;
        }
        void set_tedad_chromosomes(int _tedad){
            tedad_chromosome=_tedad;
        }
        bool check_is_alive(){
            fr(i,chromosomes.size()){
                int tedad_peivand_bad=0;
                fr(j,chromosomes[i].get_RNA_SIZE()){
                    if(chromosomes[i].get_DNA()[0][j]!=chromosomes[i].get_DNA()[1][j]){
                        tedad_peivand_bad++;
                    }
                    if(tedad_peivand_bad==5){
                        ~cell(){
                            cout<<"cell had more than 5 wrong connection so it diead"<<"\n";
                        }
                        return false;
                    }
                }
            }
            return true;
        }
        // void small_mutation_chromosomes(str s1, int n,str s2, int m){
        //     small_mutation()
        // }
        // void large_mutation_chromosomes(str s1){
        // }
        // void find_all_pallindromes(){
        //     string RNA=chromosomes[0].get_RNA();
        //     int n=chromosomes[0].get_RNA_SIZE();
        //     int index[3];
        //     index[2]=1;
        //     index[0]=index[2];
        //     for( ; index[0]<n; index[0]++)
        //     {
        //         cout<<endl<<index[0]<<":";
        //         if(RNA[index[0]]==comp(RNA[index[0]+1]))
        //             {
        //                 cout<<"If "; 
        //                 index[2]=index[0]+2;
        //                 index[1]=index[0]-(index[2]-index[0])+1;
        //                 for( ; index[1]>= 0 && index[2]<n;)
        //                 {
        //                     cout<< index[2]<< " "<< index[1]<<" //";
        //                     if(RNA[index[1]]!=comp(RNA[index[2]]))
        //                     {
        //                         cout<<"Break\n";
        //                         break;
        //                     }
        //                     if(index[2]-index[1]>=3)
        //                     {
        //                         for(int i=index[1] ; i<=index[2]; i++)
        //                             cout<<RNA[i];
        //                         cout<<endl;
        //                     }
        //                     index[2]++;
        //                     index[1]=index[0]-(index[2]-index[0])+1;
        //                 }
        //             }
        //     }
        // }

};
//////////////////////////////////////

int main(){
    cout<<"___________start_____________\n";
    
    //example of genomeL
    str RNA="AAGTCTCTTC";
    str DNA[2]={"AAGTCTCTTC","TTCAGAGAAG"};
    Genome g(RNA,DNA);
    g.large_mutation("TTC","CCC");


    //example of cell:
    cell c;

}