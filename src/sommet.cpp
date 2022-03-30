#include "sommet.h"

sommet::sommet(int num, string nom) : d_num{num}, d_nom{nom}
{

}
string sommet :: getNom() const
{
    return d_nom;
}
int sommet :: getNum() const
{
    return d_num;
}
void sommet :: setNum(int num)
{
    d_num = num;
}
