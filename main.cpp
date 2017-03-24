#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

#include "fonctions_tries_ensembles.hpp"

using namespace std;

const vector<int> lieu = {1, 2, 3, 4, 5};
const vector<int> capacite = {2, 4, 2, 4, 2};
const int capaciteDrone = 10;


/*********************************************************************/
//                              Main
/*********************************************************************/


int main(int argc, char const *argv[])
{
    // lecture des données depuis un fichier
    assert(capacite.size() == lieu.size());


    vector<vector<int>> regroupement;
    vector<vector<int>> regroupementPossible;
    vector<vector<int>> regroupementPermutesPossible;


    regroupement = ensembleDesParties(lieu);
    cout << "Tout les regroupements : " << endl;
    affiche(regroupement);
    cout << endl;


    regroupementPossible = ensembleDesPartiesPossibles(regroupement, capacite, capaciteDrone);
    cout << "Tout les regroupements possibles : " << endl;
    affiche(regroupementPossible);
    cout << endl;


    regroupementPermutesPossible = ensembleDesPermutationsPossibles(regroupementPossible);
    cout << "Tout les regroupements permutes possibles : " << endl;
    affiche(regroupementPermutesPossible);
    cout << endl;


    return 0;
}
