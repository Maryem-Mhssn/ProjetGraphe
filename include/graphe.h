#ifndef GRAPHE_H
#define GRAPHE_H
#include "sommet.h"

class graphe
{
    public:
        graphe();
        graphe(fs,Aps);
        graphe(matAdj);
        void fsAps2matAdj();
        void matAdj2fsAps();
        vector<int> calculDDI();
        vector<int> calculDDE();
        void ajouterSommet(Sommet);
        void supprimerSommet(int);
        void ajouterArete(int);
        void supprimerArete(int,int);
        bool estValue();
        bool estOriente();
        vector<int> rang();


    private:
        vector<int> d_fs;
        vector<int> d_aps;
        vector<int>* d_matAdj;
        bool d_estValue;
        bool d_estOriente;
        vector<sommet> d_sommets;

};

#endif // GRAPHE_H
