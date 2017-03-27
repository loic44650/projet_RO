#ifndef FONCTION_TRIES_ENSEMBLES
#define FONCTION_TRIES_ENSEMBLES
#include "climits"

using namespace std;


/*********************************************************************/
/*                 Fonctions de tries d'ensembles                    */
/*********************************************************************/


void affiche(vector<vector<int>> storage)
{
    for (int i = 0; i < storage.size(); ++i)
    {   
        cout << "{";;
        for (int j = 0; j < storage[i].size(); ++j)
        {
            if (j == 0)
                cout << storage[i][j];
            else
                cout << "," << storage[i][j];
        }
        cout << "}" << endl;
    }
}


vector<vector<int>> ensembleDesParties(donnees *p)
{
    vector<vector<int>> subset;
    vector<int> empty;

    subset.push_back(empty);

    for (int i = 0; i < p -> lieu.size(); ++i)
    {
        vector<vector<int>> subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); ++j)    
            subsetTemp[j].push_back(p -> lieu[i]);

        for (int j = 0; j < subsetTemp.size(); ++j)
                subset.push_back(subsetTemp[j]);
    }

    subset.erase(subset.begin());

    return subset;
}


vector<vector<int>> ensembleDesPartiesPossibles(vector<vector<int>> regroupement, donnees *p)
{
    vector<vector<int>> subset;

    int cap;

    for (int i = 0; i < regroupement.size(); ++i)
    {
        cap = 0;
        
        for (int j = 0; j < regroupement[i].size(); ++j)
            cap +=  p -> capacite[regroupement[i][j] - 1];

        if (cap <= p -> capaciteDrone)
            subset.push_back(regroupement[i]);
    }

    return subset;  
}


vector<vector<int>> ensembleDesPermutationsPossibles(vector<vector<int>> regroupement, donnees *p)
{
    vector<vector<int>> subset;
    vector<int> levecapush;
    for (int i = 0; i < regroupement.size(); ++i)
    {
        do {
            subset.push_back(regroupement[i]);
        } while(next_permutation(regroupement[i].begin(),regroupement[i].end()));
        vector<int> v; v.push_back(-10);
        subset.push_back(v);
    }
    return subset;  
}

vector<vector<int>> permutationLesPlusPetites(vector<vector<int>> allpermut, donnees *p)
{
    vector<vector<int>> subset;
    int c = 0;
    vector<int> tmp;
    int smin = INT_MAX;

    while(c < allpermut.size())
    {
        int s = 0;
        int t = -10;
        smin = INT_MAX;
        

        if( allpermut[c][0] != t )
        {
            s += p->distancier[0][allpermut[c][0]];
            for (int i = 0; i < allpermut[c].size()-1; ++i)
            {
                s += p->distancier[allpermut[c][i]][allpermut[c][i+1]];
            }
            s += p->distancier[allpermut[c].back()][0];
            if(s < smin)
            {
                tmp = allpermut[c];
                smin = s;
            }
            //cout << "s = " << s << endl;
        }
        else
        {
            subset.push_back(tmp);
            cout << "s = " << s << endl;
            tmp.clear();
        }
        ++c;
    }
    return subset;
}


#endif