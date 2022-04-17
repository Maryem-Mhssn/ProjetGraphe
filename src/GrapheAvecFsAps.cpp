#include "../include/GrapheOrienteFsAps.h"
#include "../Graphe.h"
#include "../Sommet.h"
#include <vector>
#include <queue>
#include <stack>
using std::vector;

GrapheOrienteFsAps::GrapheOrienteFsAps() : Graphe{}, _aps{0}, _fs{0}, _sommets{1}
{

}

void GrapheOrienteFsAps::ajoutSommet(const Sommet& s)
{
    _aps.push_back(_fs.size());
    _fs.push_back(0);
    _aps[0]++;
    _fs[0]++;
    _sommets.push_back(s);
}


void GrapheOrienteFsAps::supprimeSommet(int s)
{
    if(s > nbSommets())
    {
        return;
    }
    for(int i = 1; i <= nbSommets(); ++i){
        supprimeArc(i, s);
    }
    if(s == nbSommets())
    {
        _fs.erase(_fs.begin() + _aps[s], _fs.end());
        _aps.erase(_aps.begin() + s);
    }
    else{
        int limite = _aps[s+1] - 1;
        int nbSuccDeS = limite - _aps[s];
        _fs.erase(_fs.begin() + _aps[s], _fs.begin() + limite);
        _aps.erase(_aps.begin() + s);
        for(unsigned i = s; i < _aps.size(); ++i){
            _aps[i] -= nbSuccDeS;
        }
    }
    _fs[0] = _fs.size() - 1;
    --_aps[0];
    _sommets.erase(_sommets.begin() + s);
    for(int i = _aps[1]; i <= _fs[0]; ++i){
        if(_fs[i] > s){
            --_fs[i];
        }
    }
}

Sommet GrapheOrienteFsAps::getSommet(int s) const
{
    return _sommets[s];
}

int  GrapheOrienteFsAps::nbSommets() const
{
    return _aps[0];
}

void GrapheOrienteFsAps::printSommets() const
{
    for(int i = 1; i <= nbSommets(); ++i){
        std::cout<<"Sommet : "<<i<<" => "<<" Adresse 1er element : "<<_aps[i]<<std::endl;
        std::cout<<"Successeurs : "<<std::endl;
        int j = _aps[i];
        std::cout<<"[";
        while(_fs[j] != 0){
            std::cout<<_fs[j++]<<" ,";
        }
        std::cout<<"]"<<std::endl;
    }
}

void GrapheOrienteFsAps::ajoutArc(int s, int t)
{
    if(s > nbSommets() || t > nbSommets())
    {
        return;
    }
    int i = _aps[s];
    while(_fs[i] != 0 && _fs[i] != t) ++i;
    if(_fs[i] == t)
        return;
    _fs.insert(_fs.begin() + i, t);
    ++_fs[0];
    for(int j = s + 1; j <= nbSommets(); ++j){
        ++_aps[j];
    }
}

void GrapheOrienteFsAps::supprimeArc(int s, int t)
{
    if(s > nbSommets() || t > nbSommets())
    {
        return;
    }
    int i = _aps[s];
    while(_fs[i] != 0 && _fs[i] !=t) ++i;
    if(_fs[i] == 0)
    {
        return;
    }
    _fs.erase(_fs.begin() + i);
    --_fs[0];
    for(int j = s + 1; j <= nbSommets(); ++j){
        --_aps[j];
    }
}

void GrapheOrienteFsAps::inverser()
{
    int n = _aps[0];
    //Calcul du DDI
    vector<int> ddi(n + 1, 0);
    for(int i = 1; i < _fs[0]; ++i){
        int s = _fs[i];
        if(s != 0) ++ddi[s];
    }
    //Calcul de app
    vector<int> app(n + 1);
    app[0] = n;
    app[1] = 1;
    for(int i = 2; i <= n; ++i){
        app[i] = app[i-1] + ddi[i-1] + 1;
    }
    //Calcul fp
    vector<int> fp(_fs[0] + 1);
    fp[0] = _fs[0];
    int k = 1;
    for(int i = 1; i < _fs[0]; ++i)
    {
        if(_fs[i] != 0){
            fp[app[_fs[i]]] = k;
            ++app[_fs[i]];
        }
        else{
            ++k;
        }
    }
    fp[app[n]] = 0;
    for(int i = 1; i <= n; ++i){
        fp[app[i]] = 0;
    }
    for(int i = n; i > 1; --i){
        app[i] = app[i-1] + 1;
    }
    app[1] = 1;
    //Inversion
    for(int i = 1; i <= fp[0]; ++i){
        _fs[i] = fp[i];
    }
    for(int i = 1; i <= app[0]; ++i){
        _aps[i] = app[i];
    }
}

void GrapheOrienteFsAps::matriceDesDistances(vector<vector<int>>& matDist) const
{
    matDist.resize(nbSommets()+1);
    for(int r = 1; r <= nbSommets(); ++r){
        descenteEnLarg(r, matDist[r]);
    }
}

void GrapheOrienteFsAps::descenteEnLarg(int r, vector<int>& distances) const
{
    int k = 0;
    std::queue<int> fileAttente{};
    fileAttente.push(r);
    distances.resize(nbSommets() + 1, -1);
    distances[0] = nbSommets();
    distances[r] = 0;
    while(!fileAttente.empty())
    {
        ++k;
        for(int i = 0, n = fileAttente.size(); i < n; ++i)
        {
            int s = fileAttente.front();
            fileAttente.pop();
            int t;
            for(int j = _aps[s]; (t =_fs[j]) != 0; ++j)
            {
                if(distances[t] == -1){
                    distances[t] = k;
                    fileAttente.push(t);
                }
            }
        }
    }
}

void GrapheOrienteFsAps::empiler(int x, vector<int>& pilch) const
{
    pilch[x] = pilch[0];
    pilch[0] = x;
}

void GrapheOrienteFsAps::rang(vector<int>& rang)
{
    rang.resize(nbSommets() + 1);
    vector<int> ddi(nbSommets() + 1, 0);
    vector<int> pilch(nbSommets() + 1);
    vector<int> prem(nbSommets() + 1);
    rang[0] = nbSommets();
    //CALCUL DE DDI
    ddi[0] = nbSommets();
    for(int i = 1; i < _fs[0]; ++i){
        int s = _fs[i];
        if(s != 0) ++ddi[s];
    }
    //CALCUL DU RANG
    pilch[0] = 0;
    for(int s = 1; s <= nbSommets(); ++s){
        rang[s] = -1;
        if(ddi[s] == 0){
            empiler(s, pilch);
        }
    }
    int k = -1;
    int s = pilch[0];
    prem[0] = s;
    while(pilch[0] > 0)
    {
        ++k;
        pilch[0] = 0;
        while(s > 0){
            rang[s] = k;
            int h = _aps[s];
            int t = _fs[h];
            while(t > 0){
                --ddi[t];
                if(ddi[t] == 0) empiler(t, pilch);
                ++h;
                t = _fs[h];
            }
            s = pilch[s];
        }
        s = pilch[0];
        prem[k+1] = s;
    }
}

void GrapheOrienteFsAps::traverse(int s, int& ns, int& nc, vector<int>& num, vector<int>& pilch, vector<int>& ro, vector<bool>& entarj, vector<int>& cfc,
                                   std::stack<int>& tarj, vector<int>& pred, vector<int>& prem) const
{
    num[s] = ro[s] = ++ns;
    tarj.push(s);
    entarj[s] = true;
    //int t;
    for(int k = _aps[s], t; (t = _fs[k]) != 0; ++k)
    {
        if(num[t] == 0){
            pred[t] = s;
            traverse(t, ns, nc, num, pilch, ro, entarj, cfc, tarj, pred, prem);
            if(ro[t] < ro[s])
                ro[s] = ro[t];
        }
        else{
            if(num[t] < ro[s] && entarj[t])
                ro[s] = num[t];
        }
    }
    if(ro[s] == num[s])
    {
        int u;
        ++nc;
        do{
            u = tarj.top();
            tarj.pop();
            entarj[u] = false;
            empiler(u, pilch);
            cfc[u] = nc;
        }while(u != s);
        prem[nc] = pilch[0];
        pilch[0] = 0;
    }
}

void GrapheOrienteFsAps::composantFortementConnexe(vector<int>& prem, vector<int>& cfc, vector<int>& pred, vector<int>& pilch) const
{
    prem.resize(nbSommets() + 1, 0);
    cfc.resize(nbSommets() + 1);
    pred.resize(nbSommets() + 1, 0);
    pilch.resize(nbSommets() + 1);

    std::stack<int> tarj{};
    vector<bool> entarj(nbSommets() + 1, false);
    vector<int> num(nbSommets() + 1, 0);
    vector<int> ro(nbSommets() + 1, 0);
    num[0] = nbSommets();
    ro[0] = nbSommets();
    int ns = 0, nc = 0;
    pilch[0] = 0;
    for(int s = 1; s <= nbSommets(); ++s){
        if(num[s] == 0)
            traverse(s, ns, nc, num, pilch, ro, entarj, cfc, tarj, pred, prem);
    }
    prem[0] = nc;
    cfc[0] = ns;
    /*std::cout<<"num : ";
    afficher(num);
    std::cout<<"ro : ";
    afficher(ro);
    std::cout<<"prem : ";
    afficher(prem);
    std::cout<<"pilch : ";
    afficher(pilch);
    std::cout<<"cfc : ";
    afficher(cfc);
    std::cout<<"pred : ";
    afficher(pred);*/

}

void GrapheOrienteFsAps::grapheReduit(vector<int>& fsr, vector<int>& apsr) const
{
    vector<int> prem{}, cfc{}, pred{}, pilch{};
    composantFortementConnexe(prem, cfc, pred, pilch);
    //
    int kr = 1, nbc = prem[0];
    vector<bool> deja_mis(nbc + 1);
    fsr.resize(_fs[0] + 1);
    apsr.resize(nbc + 1);
    apsr[0] = nbc;
    //
    for(int i = 1; i <= nbc; ++i)
    {
        apsr[i] = kr;
        for(int i = 1; i <= nbc; ++i){
            deja_mis[i] = false;
        }
        deja_mis[i] = true;
        int s = prem[i];
        while(s != 0)
        {
            for(int t = _aps[s]; _fs[t] != 0; ++t){
                if(deja_mis[cfc[_fs[t]]] == false){
                    fsr[kr++] = cfc[_fs[t]];
                    deja_mis[cfc[_fs[t]]] = true;
                }
            }
            s = pilch[s];
        }
        fsr[kr++] = 0;
    }
    fsr[0] = kr - 1;
    /*std::cout<<"apsr : ";
    afficher(apsr);
    std::cout<<"fsr : ";
    afficher(fsr);*/
}

void GrapheOrienteFsAps::baseReduit(vector<int>& br) const
{
    vector<int> fsr{}, apsr{};
    grapheReduit(fsr, apsr);
    int nr = apsr[0];
    br.resize(nr + 1);
    //ddir
    vector<int> ddir(nr + 1, 0);
    for(int kr = 1; kr <= fsr[kr]; ++kr){
        ++ddir[fsr[kr]];
    }
    int nb = 0;
    for(int c = 1; c <= nr; ++c){
        if(ddir[c] == 0)
            br[++nb] = c;
    }
    br[0] = nb;
    /*std::cout<<"base reduite : ";
    afficher(br);*/
}

void GrapheOrienteFsAps::editionBases() const
{
    vector<int> br{}, prem{}, cfc{}, pred{}, pilch{};
    composantFortementConnexe(prem, cfc, pred, pilch);
    baseReduit(br);

    int nb = br[0];
    vector<int> base(nb + 1);
    base[0] = nb;
    int p = 1, s = prem[br[1]];
    while(p >= 1)
    {
        if(p <= nb && s != 0)
        {
            base[p++] = s;
            if(p <= nb)
                s = prem[br[p]];
            else
                afficher(base);
        }
        else{
            --p;
            s = pilch[base[p]];
        }
    }
}

void GrapheOrienteFsAps::afficher(const vector<int> & tab) const
{
    for(unsigned i = 0; i< tab.size(); ++i){
        std::cout<<tab[i]<<" ";
    }
    std::cout<<std::endl;
}
