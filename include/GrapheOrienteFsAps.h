#ifndef GRAPHEORIENTEFSAPS_H
#define GRAPHEORIENTEFSAPS_H
#include "../Graphe.h"
#include "../Sommet.h"
#include <vector>
#include <queue>
#include <stack>

using std::vector;


class GrapheOrienteFsAps : public Graphe
{
public:
    GrapheOrienteFsAps();
    virtual void ajoutSommet(const Sommet& s) override;
    virtual void supprimeSommet(int s) override;
    virtual Sommet getSommet(int s) const override;
    virtual int  nbSommets() const override;
    virtual void printSommets() const override;
    //
    void ajoutArc(int s, int t);
    void supprimeArc(int s, int t);
    //Changement d'orientation des arcs
    void inverser();
    //Calcul des distances
    void matriceDesDistances(vector<vector<int>>& matDist) const;
    void descenteEnLarg(int r, vector<int>& distances) const;
    //Rang
    void rang(vector<int>& rang);
    //Tarjan
    void composantFortementConnexe(vector<int>& prem, vector<int>& cfc, vector<int>& pred, vector<int>& pilch) const;
    void grapheReduit(vector<int>& fsr, vector<int>& apsr) const;
    void baseReduit(vector<int>& br) const;
    void editionBases() const;


private:
    vector<int> _aps;
    vector<int> _fs;
    vector<Sommet> _sommets;
    //
    void traverse(int s, int& ns, int& nc, vector<int>& num, vector<int>& pilch, vector<int>& ro, vector<bool>& entarj, vector<int>& cfc,
                                   std::stack<int>& tarj, vector<int>& pred, vector<int>& prem) const;
    void empiler(int x, vector<int>& pilch) const;
    void afficher(const vector<int> & tab) const;
};

#endif // GRAPHEORIENTEFSAPS_H
