#ifndef GRAPHENONORIENTEADJACENT_H
#define GRAPHENONORIENTEADJACENT_H
#include "../Graphe.h"
#include "../Sommet.h"
#include <vector>

using std::vector;

class GrapheNonOrienteAdjacent : public Graphe
{
public:
    GrapheNonOrienteAdjacent(bool estOriente = true);
    virtual void ajoutSommet(const Sommet& s) override;
    virtual void supprimeSommet(int s) override;
    virtual Sommet getSommet(int s) const override;
    virtual int nbSommets() const override;
    virtual void printSommets() const override;

    void ajoutArete(int s1, int s2, double poids = 1);
    void supprimeArete(int s1, int s2);
    int nombreAretes() const;
    //
    void prufer(vector<int>& prf);
    void decoprufer(const vector<int>& t);
    void dantzig(vector<vector<double>>& dist);

private:
    vector<std::vector<int>> d_adj;
    vector<Sommet> d_sommets;
    bool d_estOriente;
};

#endif // GRAPHENONORIENTEADJACENT_H
