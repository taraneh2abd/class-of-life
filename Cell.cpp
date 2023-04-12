#include "CELL.h"
///////////////////////////////////////////////////////////////


cell::cell(){
    tedad_chromosome=0;
    chromosomes.empty();
}
void cell::set_chromosomes(vector<Genome>_chromosomes){
    chromosomes=_chromosomes;
}
void cell::set_tedad_chromosomes(int _tedad){
    tedad_chromosome=_tedad;
}
vector<Genome> cell::get_chromosomes(){
    return chromosomes;
}
int cell::get_tedad_chromosomes(){
    return tedad_chromosome;
}
void cell::print_cell(){
    cout<<"CELL iS:\n";
    for(int i=0;i<tedad_chromosome;i++){
        cout<<"\nchromosoe num "<<i<<" 's DNA is : \n"<<chromosomes[i].get_RNA();
        cout<<"\n"<<chromosomes[i].get_DNA()<<"\n";
    }cout<<"___________\n";
}
void cell::large_mutation_chromosomes(str s1, str s2, int n){// in chie?
    chromosomes[n].large_mutation(s1,s2);
}   
void cell::small_mutation_chromosomes(char c, char c2,int n,int m){
    chromosomes[m].small_mutation(c,c2,n);
}
void cell::reverse_mutation_chromosomes(str s,int n){
    chromosomes[n].reverse_mutation(s);
}

//Manacher's algorithm o(n):
void cell::printAllPalindromeSubstr(string s) {
    int n = s.length();
    if (n == 0) return;
     // Preprocessing
    string t = "^#";
    for (int i = 0; i < n; i++) {
        t += s[i];
        t += "#";
    }
    t += "$";
    n = t.length();
     vector<int> P(n, 0);
    int center = 0, right = 0;
    for (int i = 1; i < n-1; i++) {
        int mirror = 2*center - i;
        if (right > i) P[i] = min(right-i, P[mirror]);
        while (t[i+(1+P[i])] == t[i-(1+P[i])]) P[i]++;
        if (i+P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }
     // Print all palindromic substrings
    for (int i = 1; i < n-1; i++) {
        int len = P[i];
        if (P[i] > 0 && len %2==0 && len>2) {
            int start = (i - 1 - len) / 2;
            cout << s.substr(start, len) << endl;
        }
    }
}
void cell::find_chromosome_pallindromes(int i){
    cout<<"\nchromosome's"<<i+1<<" all pallindromes:\n";
    string RNA=chromosomes[i].get_RNA();
    printAllPalindromeSubstr(RNA);
}

bool cell::check_is_alive(){
        for(auto &gen:chromosomes){
        str DNA_gen[2];
        DNA_gen[0]=gen.get_RNA();
        
    DNA_gen[1]=gen.get_DNA();
    int n=gen.get_RNA_size();
    int tedad_peivand_bad=0;
    int tedad_T_pair=0;
    int tedad_G_pair=0;
    fr(i,n){
        if(DNA_gen[0][i]=='T' || DNA_gen[0][i]=='A'){
            tedad_T_pair++;
            }
        else{
            tedad_G_pair++;
        }
        if(DNA_gen[0][i]!=comp(DNA_gen[1][i])){
            tedad_peivand_bad++;
        }
        if(tedad_peivand_bad>=5){
            cout<<"cell is dead.";
            delete this;
            return false;
        }
    }
    if(tedad_T_pair>tedad_G_pair*3){
        cout<<"cell is dead.";
        delete this;
        return false;
        }    
    }
    cout<<"cell is alive";
    return true;
}