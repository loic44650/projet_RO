#ifndef FONCTION_LECTURE 	
#define FONCTION_LECTURE

using namespace std;


/*********************************************************************/
/*                 Fonction de lecture                               */
/*********************************************************************/


void lecture_data(char *file, donnees *p)
{

    ifstream fichier(file);

    if(fichier)
    {
        int val;
        int nblieux;  

        fichier >> val;
        nblieux = val;

        for (int k = 1; k < nblieux; ++k)
        {
            p -> lieu.push_back(k);
        }

        /* Lecture de la capacité */
        
        fichier >> val;
        p -> capaciteDrone = val;
        
        /* Lecture des demandes des clients */
        
        for(int i = 1; i < nblieux; ++i)
        {
            fichier >> val;
            p -> capacite.push_back(val);
        }
     
        /* Lecture du distancier */
     
        p -> distancier.resize(nblieux);

        for (int i = 0; i < nblieux; ++i)
            p -> distancier[i].resize(nblieux);
        
        for(int i = 0; i < nblieux; ++i)
        {    
            for(int j = 0; j < nblieux; ++j)
            {
                fichier >> val;
                p -> distancier[i][j] = val;
            }
        }

    }   
    else
        cerr << "Impossible d'ouvrir le fichier : " << file << endl;

}


#endif
