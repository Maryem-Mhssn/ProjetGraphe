#include "Sommet.h"

Sommet::Sommet()
{}

Sommet::Sommet(int numero, const std::string& nom)
    : _numero{numero}, _nom{nom}
{

}

int Sommet::getNumero() const
{
    return _numero;
}

std::string Sommet::getNom() const
{
    return _nom;
}

void Sommet::setNumero(int numero)
{
    _numero = numero;
}

void Sommet::setNom(std::string nom)
{
    _nom = nom;
}
