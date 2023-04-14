#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "GENOME.h"
#include "CELL.h"
#include "ANIMAL.h"
using namespace std;
class virus:protected Genome{
    protected:
    string RNA;
    public:
        virus(){}
        void set_RNA(string _RNA){
            RNA=_RNA;
        }
        bool is_virus_dangerous(animal a){
        map<string,int> Just4Sort;
        vector<string> LS;
        int n=(a.get_cell()).get_tedad_chromosomes(), value, quantity=0, check=0, j, t=0;
        string chrome, sub, subha[50]={};
        bool b=0;
        for(int i=0; i<n; i++)
        {
            chrome=a.get_cell().get_chromosomes()[i].get_RNA();
            chrome=chrome+to_string(i);
            for(int j=chrome.length()-1; j>=0; j--)
            {
                sub=chrome[j]+sub;
                Just4Sort.insert(pair<string,int>(sub, i));
            }
        }
        for (auto pair : Just4Sort)
        {
            chrome={};
            if(subha[pair.second].length()==0)
                check++;
            subha[pair.second]= pair.first;
            if(check!=n) 
                continue;
            for(int i=0; i<subha[0].length();i++)
            {   
                for(j=0; j< n-1; j++)
                {
                    if(subha[j][i]!=subha[j+1][i])
                    {
                        b=1;
                        break;
                    }
                }
                if(i==subha[0].length()-1)
                    i++;
                if(b || i==subha[0].length())
                {
                    if(i-1>t)
                    {
                        t=i-1;
                        LS.clear();
                        LS.push_back(chrome);
                        quantity=1;
                    }
                    else if(i-1==t)
                    {
                        LS.push_back(chrome);
                        quantity++;
                    }
                    b=0;
                    chrome={};
                    break;
                }
                chrome=chrome+ subha[0][i];
            }
        }
        cout<< "chromosomes have "<< quantity<< "common string(s)\n";
        for (int q=0; q<quantity;q++)
        {
            cout<< q+1<<"= "<<LS[q]<<":\n";
            size_t found = RNA.find(LS[q]);
            if (found != string::npos){
                cout<<"virus is dangerous!!"<<endl;
                return true;
            }
        }
        cout<<"virus is NOT dangerous!!"<<endl;
        return false;
    }
    friend class animal; 
};
