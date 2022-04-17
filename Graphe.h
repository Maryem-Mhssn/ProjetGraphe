#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <iostream>
#include <vector>

class Sommet;

class Graphe{
public:
    Graphe() = default;
    virtual void ajoutSommet(const Sommet& s) = 0;
    virtual void supprimeSommet(int s) = 0;
    virtual Sommet getSommet(int s) const = 0;
    virtual int  nbSommets() const = 0;
    virtual void printSommets() const = 0;
};


#endif // GRAPHE_H_INCLUDED
