#ifndef GRAPHE_H
#define GRAPHE_H
#include "sommet.h"
#include<iostream>
#include <vector>
using std :: cout;
using std :: cin;
using std :: vector;

class graphe
{
    public:
        graphe();
        graphe(const vector <int> fs, const vector <int>Aps);
        graphe(const vector<vector<int>> &matAdj);
        void fsAps2matAdj();
        void matAdj2fsAps();
        vector<int> calculDDI();
        vector<int> calculDDE();
        void ajouterSommet(sommet s);
        void supprimerSommet(int);
        void ajouterArete(int);
        void supprimerArete(int,int);
        bool estValue();
        bool estOriente();
        vector<int> rang();


    private:
        vector<int> d_fs;
        vector<int> d_aps;
        vector<vector<int>> d_matAdj;
        bool d_estValue;
        bool d_estOriente;
        vector<sommet> d_sommets;
        bool d_estMatrice;

};

#endif // GRAPHE_H
