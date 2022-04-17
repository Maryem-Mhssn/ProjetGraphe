#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include "iostream"
#include <vector>

class Sommet{
public:
    Sommet();
    Sommet(int numero, const std::string& nom);
    int getNumero() const;
    std::string getNom() const;
    void setNumero(int numero);
    void setNom(std::string nom);

private:
    int _numero;
    std::string _nom;
};

#endif // SOMMET_H_INCLUDED
