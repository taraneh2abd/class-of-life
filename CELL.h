#pragma once
#include "GENOME.h"
////////////////////////////

class cell:protected Genome{
    protected:
    int tedad_chromosome;
    vector<Genome>chromosomes;
    public:
        cell(); 
        vector<Genome> get_chromosomes();
        int get_tedad_chromosomes();
        void set_chromosomes(vector<Genome>_chromosomes);
        void set_tedad_chromosomes(int _tedad);
        void print_cell();
        bool check_is_alive();
        void large_mutation_chromosomes(str s1, str s2, int n);
        void small_mutation_chromosomes(char c, char c2,int n,int m);
        void reverse_mutation_chromosomes(str s,int n);
        void printAllPalindromeSubstr(string s);
        void find_chromosome_pallindromes(int i);
};