#include "GrapheNonOrienteAdjacent.h"
#include "../Graphe.h"
#include "../Sommet.h"
#include <vector>

using std::vector;

GrapheNonOrienteAdjacent::GrapheNonOrienteAdjacent(bool estOriente )
    : d_adj{}, d_sommets{}, d_estOriente{estOriente}
{

}

void GrapheNonOrienteAdjacent::ajoutSommet(const Sommet& s){
    int n = nbSommets();
    d_adj.push_back(std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i)
        d_adj[i].push_back(0);
    d_sommets.push_back(s);
}
void GrapheNonOrienteAdjacent::supprimeSommet(int s){
  d_adj.erase(d_adj.begin() + s);
  int n = nbSommets();
  for (int i = 0; i <= n; ++i)
    d_adj[i].erase(d_adj[i].begin() + s);
}

Sommet GrapheNonOrienteAdjacent::getSommet(int s) const
{
  return d_sommets[s];
}

int GrapheNonOrienteAdjacent::nbSommets() const
{
  return d_adj.size();
}

void GrapheNonOrienteAdjacent::printSommets() const
{
  for (unsigned i = 0; i < d_adj.size(); ++i)
  {
    for (unsigned j = 0; j < d_adj[i].size(); ++j)
    {
      std::cout<< d_adj[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void GrapheNonOrienteAdjacent::ajoutArete(int s1, int s2, double poids)
{
    int taille = d_adj.size();
    if(s1 > taille || s2 > taille){
        return;
    }
    if(d_estOriente)
        d_adj[s1-1][s2-1] = poids;
    else
        d_adj[s1-1][s2-1] = d_adj[s2-1][s1-1] = poids;

}

void GrapheNonOrienteAdjacent::supprimeArete(int s1, int s2)
{
  int taille = d_adj.size();
    if(s1 > taille || s2 > taille){
        return;
    }
    if(d_estOriente)
        d_adj[s1-1][s2-1] = 0;
    else
        d_adj[s1-1][s2-1] = d_adj[s2-1][s1-1] = 0;
}

int GrapheNonOrienteAdjacent::nombreAretes() const
{
  int n = nbSommets();
  int m = 0;
  for (int i = 1; i < n; ++i)
  {
    for (int j = i+1; j <= n; ++j)
    {
      if (d_adj[i][j] == 1)
        ++m;
    }
  }
  return m;
}
//
void GrapheNonOrienteAdjacent::prufer(vector<int>& prf)
{
    vector<vector<int>> mat(d_adj.size(), vector<int>(d_adj.size()+1));

    for(unsigned i = 0; i < d_adj.size(); ++i){
        for(unsigned j = 0; j < d_adj[i].size(); ++j){
            mat[i][j+1] = d_adj[i][j];
        }
    }
    int n=mat.size();
    prf.resize(n-1);
    prf[0] = n-2;
    for(unsigned i = 0;i < mat.size(); i++)
    {
        mat[i][0] = 0;
        for(unsigned j = 1;j < mat[i].size(); j++)
        {
            mat[i][0] += mat[i][j];
        }
    }
    //
    std::cout<<"MATRICE ASSOCIEE"<<std::endl;
    for(unsigned i = 0; i < mat.size(); ++i){
        for(unsigned j = 0; j < mat[i].size(); ++j){
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    //
    for(int k = 1; k <= n-2; k++)
    {
        int i = 1;
        for(;mat[i][0] != 1; ++i);
        int j = 1;
        for(;mat[i][j] !=1 ; ++j);
        prf[k] = j;
        mat[i][j] = 0;
        mat[j][i] = 0;
        mat[i][0] = 0;
        mat[j][0]--;
    }
}

void GrapheNonOrienteAdjacent::decoprufer(const vector<int>& t)
{
    int m = t[0], n = m+2;
    vector<int> s(n+1);
    for (int i = 1; i <= n; i++) s[i] = 0;
    for (int i = 1; i <= m; i++) s[t[i]]++;
    for (int k = 1; k <= m; k++)
        for (int i = 1; i <= n; i++)
            if (s[i] == 0)
            {
                std::cout <<"[ "<<t[k]<<" "<<i<<" ]"<<std::endl;
                s[t[k]]--;
                s[i] = -1;
                break;
            }
    std::cout<<"[ ";
    for (int i = 1; i <= n; i++)
        if ( s[i] == 0 )
            std::cout <<i<<" ";
    std::cout << "]"<<std::endl;
}

void GrapheNonOrienteAdjacent::dantzig(vector<vector<double>>& dist)
{
    double x;
    int n = nbSommets();
    dist.resize(n);
    for(int i = 0; i < n; ++i) dist[i].resize(n);
    for(int k = 1; k < n; ++k)
    {
        for(int i = 1; i <= k; ++i)
        {
            for(int j = 1; j <= k; ++j)
            {
                if((x = d_adj[i][j] + d_adj[j][k+1]) < d_adj[k+1][i]){
                    dist[k+1][i] = x;
                }
            }
            if(d_adj[i][k+1] + d_adj[k+1][i] < 0){
                std::cout<<"Presence d'un circuit absorbant passant par "<<i<<" et "<<(k+1)<<std::endl;
            }
        }
        for(int i = 1; i <= k; ++i)
        {
            for(int j = 1; j <= k; ++j)
            {
                if((x = d_adj[i][k+1] + d_adj[k+1][j]) < d_adj[i][j]){
                    dist[i][j] = x;
                }
            }
        }
    }
}
