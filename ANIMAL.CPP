#include "ANIMAL.h"
#include <time.h>
#include <random>
////////////////////////////////////////////////////////////////


animal::animal(){}
void animal::set_cell_animal(cell _cell_animal){
    cell_animal=_cell_animal;
}

cell animal::get_cell(){
    return cell_animal;
}


//matrix method for similarity of allels o(m*n):{longest common non-consecutive}
double animal::similarity_percentage_2string(string X, string Y, int m, int n)
{
	// Initializing a matrix of size (m+1)*(n+1)
	double L[m + 1][n + 1];

	// Following steps build L[m+1][n+1] in bottom up
	// fashion. Note that L[i][j] contains length of LCS of
	// X[0..i-1] and Y[0..j-1]
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				L[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;

			else
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}

	// L[m][n] contains length of LCS for X[0..n-1]
	// and Y[0..m-1]
	return L[m][n]/max(m,n);
}

double animal::similarity_percentage(animal a2) {
    vector<Genome>va1=cell_animal.get_chromosomes();
    int tedad_a1=cell_animal.get_tedad_chromosomes();
    vector<Genome>va2=a2.get_cell().get_chromosomes();
    int tedad_a2=a2.get_cell().get_tedad_chromosomes();

    str X=va1[0].get_RNA(),Y=va2[0].get_RNA(); 
    int m=X.length(),n=Y.length();
    double max_similarity=0;
    fr(i,tedad_a1){
        fr(j,tedad_a2){
            int previouse_max_similarity=max_similarity;
            str X=va1[i].get_RNA(),Y=va2[j].get_RNA(); int m=X.length(),n=Y.length();
            max_similarity=max(max_similarity,similarity_percentage_2string(X,Y,m,n));
            //A GLOBAL VALUEfor checking similarity of sexual_reproduction:
            if(previouse_max_similarity!=max_similarity){
                gen_max=va1[i];
            }
        }
    }   
    return max_similarity; 
}

bool animal::operator==(animal other) {
    if(cell_animal.get_tedad_chromosomes()==other.get_tedad_chromosomes() && similarity_percentage(other)>=0.7){
        return true;
    }
    return false;
}


animal animal::reproduction(){
    int n =cell_animal.get_tedad_chromosomes();
    vector<Genome>chromosomes=cell_animal.get_chromosomes();
    int i=0; 
    vector<Genome>rands;
    fr(i,n){
        rands.pb(chromosomes[i]);
        rands.pb(chromosomes[i]);
    }
    shuffle(rands.begin(), rands.end(), random_device());
    animal ans;
    vector<Genome>new_chromosomes;
    fr(i,n){
        new_chromosomes.pb(rands[i]);
    }
    cell c_child;
    c_child.set_tedad_chromosomes(n);
    c_child.set_chromosomes(new_chromosomes);
    ans.set_cell_animal(c_child);
    return ans;
}

animal animal::operator+(animal other) {
    animal new_animal;
    if((similarity_percentage(other)<0.4)||other.get_tedad_chromosomes()%2==1 || get_tedad_chromosomes()%2==1){
        cout<<"this 2 animal cant reproduce!\n"; 
        return new_animal;
    }
    vector<Genome>new_chromosomes;
    new_chromosomes.pb(gen_max);

    animal production1=reproduction();
    animal production2=other.reproduction();
    int n=get_tedad_chromosomes();
    srand(time(NULL));
    fr(i,n/2-1){
        int r=rand()%n;
        new_chromosomes.pb(cell_animal.get_chromosomes()[r]);
    }
    fr(i,n/2){
        int r=rand()%n;
        new_chromosomes.pb(other.get_chromosomes()[r]);
    }
    new_animal.set_tedad_chromosomes(n);
    new_animal.set_chromosomes(new_chromosomes);
    return new_animal;
}

void animal::cell_death(){
    bool is_alive=cell_animal.check_is_alive();
}
