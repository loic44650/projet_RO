#ifndef FONCTION_TRIES_ENSEMBLES
#define FONCTION_TRIES_ENSEMBLES

using namespace std;


/*********************************************************************/
//                  Fonction && Procédures
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


vector<vector<int>> ensembleDesParties(vector<int> lieu)
{
    vector<vector<int>> subset;
    vector<int> empty;

    subset.push_back(empty);

    for (int i = 0; i < lieu.size(); ++i)
    {
        vector<vector<int>> subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); ++j)    
            subsetTemp[j].push_back(lieu[i]);

        for (int j = 0; j < subsetTemp.size(); ++j)
                subset.push_back(subsetTemp[j]);
    }

    subset.erase(subset.begin());

    return subset;
}


vector<vector<int>> ensembleDesPartiesPossibles(vector<vector<int>> regroupement,vector<int> capacite, int capaciteDrone)
{
    vector<vector<int>> subset;

    int cap;

    for (int i = 0; i < regroupement.size(); ++i)
    {
        cap = 0;
        
        for (int j = 0; j < regroupement[i].size(); ++j)
            cap +=  capacite[regroupement[i][j] - 1];

        if (cap <= capaciteDrone)
            subset.push_back(regroupement[i]);
    }

    return subset;  
}


vector<vector<int>> ensembleDesPermutationsPossibles(vector<vector<int>> regroupement)
{
    vector<vector<int>> subset;

    for (int i = 0; i < regroupement.size(); ++i)
    {
        do {
           subset.push_back(regroupement[i]);
        } while(next_permutation(regroupement[i].begin(),regroupement[i].end()));
    }
    
    return subset;  
}

#endif
