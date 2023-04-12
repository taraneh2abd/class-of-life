#pragma once
#include "CELL.h"
////////////////////////////

class animal:public cell{
protected:
    cell cell_animal;
public:
    //a public value for reproduction:
    Genome gen_max;
    animal();
    void set_cell_animal(cell _cell_animal);
    cell get_cell();

    //matrix method for similarity of allels
    double similarity_percentage_2string(string X, string Y,int m, int n);
    double similarity_percentage(animal a2);
    bool operator==(animal other);
    animal reproduction();
    animal operator+(animal other);
    void cell_death();
};