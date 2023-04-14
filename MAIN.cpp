#include "GENOME.cpp"
#include "CELL.cpp"
#include "ANIMAL.cpp"
#include "virus.cpp"


void setCell(vector<Genome> &v,cell &c)
{
    Genome forV;
    int number;
    string DNA[2];
    cout<<"Insert the quantity of chromosomes of your cell: ";
    cin>>number;
    cout<<"Insert "<<number<<" DNA:\na";
    for(int i=1; i<number +1; i++)
    {
        cout<<i<<":\n";
        cin>>DNA[0]>> DNA[1];
        forV.set_DNA(DNA);
        v.push_back(forV);
    }
    c.set_chromosomes(v);  
    c.set_tedad_chromosomes(number);
}


int main(){
    cout<<"___________start_____________\n";

    vector<Genome> v;
    cell c, cA;
    animal a, aC;
    animal child_from_2,child_from_1;
    virus vir;
    str first, second, DNA[2];
    int command, number, adad;
    bool cellFirst=1, genFirst=1, animalFirst=1, virFirst=1;
    Genome g;
    while (true)
    {
    cout<<"\nWhat you want to study about?\n1.Genome  2.Cell  3.Animal  4.Exit\n";
    cin>>command;
    switch(command)
    {
        case 1:
            if(genFirst)
            {
                cout<<"Insert your RNA: ";
                cin>>DNA[0];
                g.set_RNA(DNA[0]);
                genFirst=0;
            }
            cout<<"\nChoose your working area:\n1.get DNA  2.Small mutation  3.Large mutation  4.Reverse_mutation  5. Create new RNA\n";
            cin>>command;
            switch(command)
            {
                case 1:
                    cout<<"\nDNA= \n"<<g.get_RNA()<<endl<<g.get_DNA()<<endl;
                    cout<<"___________\n";
                break;
                case 2:
                    cout<<"type 2 char and number of times you want to change it:\n";
                    cin>> first>> second>> number;
                    g.small_mutation(first[0], second[0], number);
                break;
                case 3:
                cout<<"type 2 string which you want to change and the string you want to change to:\n";
                    cin>> first>> second;
                    g.large_mutation(first,second);
                break;
                case 4:
                    cout<<"type a string wich you want to change to reverse: \n";
                    cin>>first;
                    g.reverse_mutation(first);
                break;
                case 5: 
                    cout<<"Insert your new RNA: ";
                    cin>>DNA[0];
                    g.set_RNA(DNA[0]);
                break;
                default:
                    cout<<"INCORECT INPUT!!!";
            }
        break;
        case 2:
            if(cellFirst)
            {
                setCell(v,c);
                cellFirst=0;
            }
            cout<<"Choose your working area:\n1.Is it alive? 2.Small mutation  3.Large mutation  4.Reverse_mutation  5.Find pallindromes  6.Create new cell 7.print cell\n";
            cin>>command;
            switch(command)
            {
                case 1:
                    c.check_is_alive();
                break;
                case 2:
                    cout<<"type 2 char and number of times you want to change it and number of chromosom:\n";
                    cin>> first>> second>> number>> adad;
                    c.small_mutation_chromosomes(first[0], second[0], number, adad-1);
                break;
                case 3:
                    cout<<"type 2 string which you want to change and the string you want to change to and number:\n";
                    cin>> first>> second>> number;
                    c.large_mutation_chromosomes(first,second, number-1);
                break;
                case 4:
                    cout<<"type a string wich you want to change to reverse and number of chromosom: \n";
                    cin>> first>> number;
                    c.reverse_mutation_chromosomes(first, number-1);
                break;
                case 5:
                    cout<<"Do you need pallindromes of which chromosomes?";
                    cin>> number;
                    c.find_chromosome_pallindromes(number-1);
                break;
                case 6:
                    setCell(v,c);
                break;
                case 7:
                    c.print_cell();
                break;
                default:
                    cout<<"INCORECT INPUT!!!";
            }
        break;
        case 3:
            if(cellFirst)
            {
                cout<<"Insert your first cell(animal):\n";
                setCell(v,c);
                cellFirst=0;
            }
            if(animalFirst)
            {
                cout<<"Insert your second cell(animal)\n";
                a.set_cell_animal(c);
                v.clear();
                setCell(v,cA);
                animalFirst=0;
                aC.set_cell_animal(cA);
            }    
            cout<<"\nChoose your working area:\n1.Similarity percentage 2.Species identification  3.Reproduction  4.Reproduction(+) 5. VIRUS!!\n";
            cin >> command;
            switch(command)
            {
                case 1:
                    cout<<"\n similirity of these 2 is:\n"<<a.similarity_percentage(aC)<<endl;
                break;
                case 2:
                    if(a==aC){
                        cout<<"they are from same specie\n";
                    }
                    else{
                        cout<<"they are from different specie\n";
                    }
                break;
                case 3:
                    child_from_1=a.reproduction();
                    cout<<"child is : \n";
                    child_from_1.get_cell().print_cell();
                break;
                case 4:
                    child_from_2=a+aC;
                    cout<<"child is : \n";
                    child_from_2.get_cell().print_cell();
                break;
                case 5:\
                    cout<<"What is the RNA of virus?\n";
                    cin>>DNA[0];
                    vir.set_RNA(DNA[0]);
                    vir.is_virus_dangerous(a);
                break;
            }
            break;
            case 4:
                cout<<" END";return 0;
            break;
        }
    }
}
/*
3
2
ATCGGC          
TAGCCG
GCTACA
CGATGT
2
CATCGT
GTAGCA
CTGTTA
GACAAT
4
*/
