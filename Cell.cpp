#include<iostream>
#include<string>
#include<vector>

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
    Genome(string _RNA){
        RNA = _RNA;
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
        RNA=_RNA; 
        RNA_SIZE=RNA.length(); 
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
        fr( i, RNA_SIZE){
            new_s+=comp(s[i]);
        }
        return new_s;
    }
    void set_DNA(){
        DNA[0]= RNA;
        DNA[1]=complete(RNA);  
    }
    void print_complement(){
        cout<<"complement is :\n"<<DNA[0]<<endl<<DNA[1]<<endl<<"___________";
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
        void large_mutation(str pat,str exchange){
            int q, i, index=0, second[2];
            q=pat.length();
            second[0]=0;
            second[1]=0;
            for(i=1;i<q;i++)
            {
                if(pat[i]==pat[second[0]])
                    second[0]++;
                else if(second[0]>second[1])
                {
                    second[1]=second[0];//tedad horof dorost
                    second[0]=0;
                    index=i;
                } 
            }
            if(index>=q-2)
                second[0]= index;//payan akharin harf dorost dovom
            else
                second[0]=index+8;
            index =0;
            for(i=0; i<get_RNA_size(); i++)
            {
                if(index==q)
                    break;
                if(RNA[i]==pat[index])
                    index++;
                else
                {
                    if(index>=second[0])
                    {
                        i=i-index+second[0]-1;
                        index=second[1];
                    }
                    else
                        index=0;
                }
            }
            if(index==q)
                for( ; q>-1;q--)
                    DNA[1][i-1-q]=comp(DNA[0][i-1-q]);
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
        void small_mutation_chromosomes(char s1, char s2, int n, int m){
            small_mutation();
        }
        void large_mutation_chromosomes(str s1){
        }
        void find_all_pallindromes(){
            string RNA=chromosomes[0].get_RNA();
            int n=chromosomes[0].get_RNA_SIZE();
            int index[3];
            index[2]=1;
            index[0]=index[2];
            for( ; index[0]<n; index[0]++)
            {
                cout<<endl<<index[0]<<":";
                if(RNA[index[0]]==comp(RNA[index[0]+1]))
                    {
                        cout<<"If "; 
                        index[2]=index[0]+2;
                        index[1]=index[0]-(index[2]-index[0])+1;
                        for( ; index[1]>= 0 && index[2]<n;)
                        {
                            cout<< index[2]<< " "<< index[1]<<" //";
                            if(RNA[index[1]]!=comp(RNA[index[2]]))
                            {
                                cout<<"Break\n";
                                break;
                            }
                            if(index[2]-index[1]>=3)
                            {
                                for(int i=index[1] ; i<=index[2]; i++)
                                    cout<<RNA[i];
                                cout<<endl;
                            }
                            index[2]++;
                            index[1]=index[0]-(index[2]-index[0])+1;
                        }
                    }
            }
        }
};
//////////////////////////////////////

int main(){
    cout<<"___________start_____________\n";
    /*
    //example of genomeL
    str RNA="AAGTCTCTTC";
    str DNA[2]={"AAGTCTCTTC","TTCAGAGAAG"};
    Genome g(RNA,DNA);
    g.large_mutation("TTC","CCC");
    */
    str RNA, DNA[2];
    int n;
    cout<<"Welcome to our not AI program.\n Please insert RNA.\n";
    cin>> RNA;
    cin>> DNA[0]>> DNA[1];
    Genome g(RNA);//DNA ro k ghaedatan nabayad bedan k, bayad besazim
    cell c();
    cout<<"What to you want to do? Don't be shy, mesle barname khodetone.\n1.Gene: Small mutation    2.Gene: Large mutation    3.Gene: Reverse mutation\n4.Cell: Cell death    5.Cell: Large mutation    6.Cell: Reverse mutation    7.Cell: Fine palindormes";
    again:
    cin>> n;
    switch(n)
    {
        case 1:

        break;
        case 2:

        break;
        case 3:

        break;
        case 4:

        break;
        case 5:

        break;
        case 6:

        break;
        case 7:

        break;
        default:
            cout<<"Dash doroste ke goftam rahat bash, vali hadaghal ye farmani bede ke mojod bashe\ntry again\n";
            goto again;
    }



//


    //example of cell:
}