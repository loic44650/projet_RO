#ifndef FONCTION_TRIES_ENSEMBLES
#define FONCTION_TRIES_ENSEMBLES

using namespace std;


/*********************************************************************/
/*                 Fonctions de tries d'ensembles                    */
/*********************************************************************/


void affiche(vector<vector<int>> storage)
{
    for (unsigned int i = 0; i < storage.size(); ++i)
    {   
        cout << "{";;
        for (unsigned int j = 0; j < storage[i].size(); ++j)
        {
            if (j == 0)
                cout << storage[i][j];
            else
                cout << "," << storage[i][j];
        }
        cout << "}" << endl;
    }
}


vector<vector<int>> ensembleDesPartiesPossibles(donnees *p)
{
    vector<vector<int>> subset;
    vector<int> empty;

    vector<int> poid;
    poid.push_back(0);
    
    subset.push_back(empty);

    for (unsigned int i = 0; i < p -> lieu.size(); ++i)
    {
        vector<vector<int>> subsetTemp = subset;
        vector<int> poids = poid;

        for (unsigned int j = 0; j < subsetTemp.size(); ++j)    
        {    
            poids[j] += p -> capacite[i];

            if (poids[j] <= p -> capaciteDrone)
            {
                subsetTemp[j].push_back(i + 1);
                subset.push_back(subsetTemp[j]);
                poid.push_back(poids[j]);
            }

        }
    }

    subset.erase(subset.begin());

    return subset;
}


vector<vector<int>> ensembleDesPermutationsPossibles(vector<vector<int>> regroupement, donnees *p)
{
    vector<vector<int>> subset;
    vector<int> levecapush;
 
    for (unsigned int i = 0; i < regroupement.size(); ++i)
    {
        do {
            subset.push_back(regroupement[i]);
        } while(next_permutation(regroupement[i].begin(),regroupement[i].end()));

        vector<int> v; v.push_back(-10);
        subset.push_back(v);
    }
 
    return subset;  
}


vector<vector<int>> permutationLesPlusPetites(vector<vector<int>> regroupement, vector<int> &longueurTournee, donnees *p)
{
    vector<vector<int>> subset;
    
    unsigned int c = 0;
    int s = 0;
	vector<int> tmp;
    int min = INT_MAX;
    
    while (c < regroupement.size())
    {
    	
    	s = 0;

        if (regroupement[c][0] != (-10))
        {   
            s += p -> distancier[0][regroupement[c][0]];

            for (unsigned int i = 0; i < regroupement[c].size() - 1; ++i)
            {
            	s += p -> distancier[regroupement[c][i]][regroupement[c][i + 1]];
            	
            }
    
            s += p -> distancier[regroupement[c].back()][0];
           	
           	if (min > s)
           	{
           		min = s;
           		tmp = regroupement[c];
           	}
        }
        else
        {	
        	subset.push_back(tmp);
            longueurTournee.push_back(min);
        	tmp.clear();
    		min = INT_MAX;
        }

        ++c;
    }

    return subset;
}


vector<vector<int>> indiceVecteurOccu(vector<vector<int>> tournee, donnees *p)
{
    vector<vector<int>> occu;

    occu.resize(p -> lieu.size());

    for (unsigned int i = 0; i < tournee.size(); ++i)
        for (unsigned int j = 0; j < tournee[i].size(); ++j)
            occu[tournee[i][j] - 1].push_back(i);

    return occu;
}

#endif
