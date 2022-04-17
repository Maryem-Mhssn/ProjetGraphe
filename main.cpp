#include <iostream>
#include "include/GrapheAvecFsAps.h"
//#include "GrapheNonOrienteAdjacent.h"
#include <vector>
#include <stack>
#include "Sommet.h"

using namespace std;

void testAjoutSuppression()
{
    Sommet s1{1, "Mulhouse"},
           s2{2, "Paris"},
           s3{3, "Strasbourg"},
           s4{4, "Toulouse"};
    GrapheOrienteFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.printSommets();
    cout<<"APRES AJOUT D'UN SUCCESSEUR"<<endl;
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(1, 4);
    graph.ajoutArc(2, 1);
    graph.ajoutArc(2, 3);
    graph.ajoutArc(3, 1);
    graph.ajoutArc(3, 2);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(4, 3);
    graph.ajoutArc(4, 2);
    graph.ajoutArc(4, 1);
    //
    /*graph.supprimeArc(3, 2);//milieu
    graph.supprimeArc(1, 2);//debut
    graph.supprimeArc(3, 4);//fin
    graph.supprimeArc(4, 6);//arc inexistant*/
    //
    graph.supprimeSommet(4);
    //
    graph.printSommets();
}

void testDistance()
{
    Sommet s1{1, "Mulhouse"},
           s2{2, "Paris"},
           s3{3, "Strasbourg"},
           s4{4, "Toulouse"},
           s5{5, "Bordeaux"},
           s6{6, "Rennes"},
           s7{7, "Grenoble"};
    GrapheOrienteFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    //
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(1, 5);
    graph.ajoutArc(2, 3);
    graph.ajoutArc(3, 3);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(4, 5);
    graph.ajoutArc(4, 6);
    graph.ajoutArc(5, 3);
    graph.ajoutArc(7, 4);
    graph.ajoutArc(7, 6);
    //
    graph.printSommets();
    //
    cout<<endl;
    cout<<"MATRICE DE DISTANCES"<<endl;
    vector<vector<int>> matDist{};
    graph.matriceDesDistances(matDist);
    for(unsigned i = 0; i < matDist.size(); ++i){
        for(unsigned j = 1; j < matDist[i].size(); ++j){
            cout<<matDist[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void afficher(const vector<int>& tab)
{
    for(unsigned i = 0; i< tab.size(); ++i){
        std::cout<<tab[i]<<" ";
    }
    std::cout<<std::endl;
}

void testRang()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"},
       s6{6, "Rennes"},
       s7{7, "Grenoble"},
       s8{8, "Nantes"};

    GrapheOrienteFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    graph.ajoutSommet(s8);
    //
    graph.ajoutArc(1, 8);
    graph.ajoutArc(2, 1);
    graph.ajoutArc(2, 4);
    graph.ajoutArc(2, 5);
    graph.ajoutArc(2, 6);
    graph.ajoutArc(2, 7);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(3, 5);
    graph.ajoutArc(4, 1);
    graph.ajoutArc(4, 5);
    graph.ajoutArc(5, 7);
    graph.ajoutArc(6, 1);
    graph.ajoutArc(6, 4);
    graph.ajoutArc(6, 8);

    //
    graph.printSommets();
    cout<<endl;
    cout<<"RANG DES SOMMETS"<<endl;
    vector<int> rg{};
    graph.rang(rg);
    for(unsigned i = 0; i < rg.size(); ++i){
        cout<<rg[i]<<" ";
    }
    cout<<endl;
}

void testEditionBase()
{
   Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"},
       s6{6, "Rennes"},
       s7{7, "Grenoble"},
       s8{8, "Nantes"};
    GrapheOrienteFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    graph.ajoutSommet(s8);
    //
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(1, 4);
    graph.ajoutArc(3, 6);
    graph.ajoutArc(4, 7);
    graph.ajoutArc(5, 2);
    graph.ajoutArc(5, 1);
    graph.ajoutArc(5, 6);
    graph.ajoutArc(6, 3);
    graph.ajoutArc(6, 4);
    graph.ajoutArc(6, 7);
    graph.ajoutArc(6, 8);
    graph.ajoutArc(7, 4);
    graph.ajoutArc(8, 7);
    //
    graph.printSommets();
    cout<<"Composant fortement connexe"<<endl;
    vector<int> prem{}, cfc{}, pred{}, pilch{};
    graph.composantFortementConnexe(prem, cfc, pred, pilch);
    cout<<"EDITION BASE"<<endl;
    vector<int> apsr{}, fsr{}, br{};
    //graph.grapheReduit(fsr, apsr);
    //graph.baseReduit(br);
    graph.editionBases();
}

void testInverserGraphe()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"};
       GrapheOrienteFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    //
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(2, 5);
    graph.ajoutArc(2, 4);
    graph.ajoutArc(3, 2);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(4, 5);
    //
    cout<<"GRAPHE INITIAL"<<endl;
    graph.printSommets();
    cout<<endl;
    cout<<"GRAPHE INVERSE"<<endl<<endl;
    graph.inverser();
    graph.printSommets();
}

int main()
{
    //testAjoutSuppression();
    //testDistance();
    //testRang();
    //testEditionBase();
    testInverserGraphe();
    return 0;
}
