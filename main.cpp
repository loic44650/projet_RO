#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

#include "fonctions_tries_ensembles.hpp"

using namespace std;


/* structures et fonctions de mesure du temps CPU */

struct timeval start_utime, stop_utime;

void crono_start()
{
    struct rusage rusage;
    
    getrusage(RUSAGE_SELF, &rusage);
    start_utime = rusage.ru_utime;
}

void crono_stop()
{
    struct rusage rusage;
    
    getrusage(RUSAGE_SELF, &rusage);
    stop_utime = rusage.ru_utime;
}

double crono_ms()
{
    return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}



/* Structure contenant les données du problème */

typedef struct {
    vector<int> lieu;                   /* Nombre de lieux (incluant le dépôt) */
    int capaciteDrone;                  /* Capacité du véhicule de livraison */
    vector<int> capacite;               /* Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
    vector<vector<int>> distancier;     /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
} donnees;



/* lecture des donnees */

void lecture_data(char *file, donnees *p)
{
    FILE *fin;
    
    int val;
    fin = fopen(file, "rt");
    
    /* Lecture du nombre de villes */

    int nblieux;  

    fscanf(fin, "%d", &val);
    nblieux = val;

    for (int k = 1; k <= nblieux; ++k)
    {
        p->lieu.push_back(k);
    }

    cout << "1" << endl;

    /* Lecture de la capacité */
    
    fscanf(fin, "%d", &val);
    p->capaciteDrone = val;
    
    /* Lecture des demandes des clients */
    
    for(int i = 1; i < nblieux; ++i)
    {
        fscanf(fin, "%d", &val);
        p->capacite.push_back(val);
    }
 
     cout << "2" << endl;
    p->distancier.resize(nblieux);
    for (int i = 0; i < nblieux; i++)
        p->distancier[i].resize(nblieux);
    /* Lecture du distancier */
    
    for(int i = 0; i < nblieux; ++i)
    {    
        for(int j = 0; j < nblieux; ++j)
        {
            cout << "bob" << endl;
            fscanf(fin, "%d", &val);
            cout << val;
         
            p->distancier[i][j] = val;
//          

        }
    }

    cout << "3" << endl;


    fclose(fin);
}



/*********************************************************************/
//                              Main
/*********************************************************************/


int main(int argc, char *argv[])
{
    
    /* Déclarations des variables (à compléter) */

    donnees p; 
    double temps;
        
    /* Chargement des données à partir d'un fichier */
    
    lecture_data(argv[1],&p);
    
    /* Lancement de la résolution... */

    crono_start(); // .. et donc du chronomètre

    /* .... */







    // ptite verif a rajouter ??? lecture des données depuis un fichier
    //assert(p.capacite.size() == p.lieu.size());


    // vector<vector<int>> regroupement;
    // vector<vector<int>> regroupementPossible;
    // vector<vector<int>> regroupementPermutesPossible;


    // regroupement = ensembleDesParties(lieu);
    // cout << "Tout les regroupements : " << endl;
    // affiche(regroupement);
    // cout << endl;


    // regroupementPossible = ensembleDesPartiesPossibles(regroupement, capacite, capaciteDrone);
    // cout << "Tout les regroupements possibles : " << endl;
    // affiche(regroupementPossible);
    // cout << endl;


    // regroupementPermutesPossible = ensembleDesPermutationsPossibles(regroupementPossible);
    // cout << "Tout les regroupements permutes possibles : " << endl;
    // affiche(regroupementPermutesPossible);
    // cout << endl;









    /* ... */



    /* Problème résolu, arrêt du chrono */
    
    crono_stop();
    temps = crono_ms()/1000,0;
    
    /* Affichage des résultats (à compléter) */
    
    printf("Temps : %f\n",temps);   
    



    return 0;
}
