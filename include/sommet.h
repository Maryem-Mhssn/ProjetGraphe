#ifndef SOMMET_H
#define SOMMET_H
#include <string>
using std::string;
class sommet
{
    public:
        sommet(int num, string nom);
        string getNom() const;
        int getNum() const;
        void setNum(int num);


    private:
        int d_num;
        string d_nom;
};

#endif // SOMMET_H
