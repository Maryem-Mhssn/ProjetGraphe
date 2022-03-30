#include "graphe.h"

graphe::graphe(): d_fs{}, d_aps{}, d_matAdj{}, d_estOriente{true}, d_estValue{false}, d_estMatrice{false}
{

}
graphe::graphe(const vector <int> Fs, const vector <int> Aps): d_fs{Fs}, d_aps{Aps}, d_matAdj{}, d_estOriente{true}, d_estValue{false} , d_estMatrice{false}
{

}
graphe::graphe(const vector<vector <int>> &matAdj): d_fs{}, d_aps{}, d_matAdj{matAdj}, d_estOriente{false}, d_estValue{false} , d_estMatrice{true}
{

}
void graphe :: fsAps2matAdj()
{
    int j,k;
    int n = d_aps[0];
    int m = d_fs[0]-n;
    d_matAdj.resize(n);
    for (int i = 0; i <= n; i++)
        d_matAdj.resize(n);
    d_matAdj[0][0] = n;
    d_matAdj[0][1] = m;
    for (int i = 1; i <= n; i++)
     {
         for (int j = 1; j <= n; j++)
             d_matAdj[i][j] = 0;
     }
    for (int i = 1; i <= n; i++)
             {
                 k = d_aps[i];
                 while ( d_fs[k] != 0 )
                 {
                     d_matAdj[i][d_fs[k]] = 1;
                        k++;
                 }
             }
}
void graphe :: matAdj2fsAps()
{
    int n = d_matAdj[0][0];
    int m = d_matAdj[0][1];
    d_aps.resize(n+1);
    d_aps[0] = n;
    d_fs.resize(n+m+1);
    d_fs[0] = n+m;
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
             d_aps[i] = k;
             for (int j = 1; j <= n; j++)
                 if (d_matAdj[i][j] != 0)
                     d_fs[k++] = j;
             d_fs[k++] = 0;
    }
}
vector<int> graphe ::calculDDI()
{

}
vector<int> graphe :: calculDDE()
{

}
void graphe :: ajouterSommet(sommet s)
{

}
void graphe :: supprimerSommet(int)
{

}
void graphe :: ajouterArete(int)
{

}
void graphe :: supprimerArete(int,int)
{

}
bool graphe :: estValue()
{
    return d_estValue;
}
bool graphe :: estOriente()
{
    return d_estOriente;
}
vector<int> graphe :: rang()
{

}
