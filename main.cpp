#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <climits>
#include <algorithm>
#include <string>
#include <fstream>

#include <cstdio>
#include <cstdlib>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */


using namespace std;


/* Structure contenant les données du problème */

struct donnees
{
    vector<int> lieu;                   /* Nombre de lieux (incluant le dépôt) */
    int capaciteDrone;                  /* Capacité du véhicule de livraison */
    vector<int> capacite;               /* Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
    vector<vector<int>> distancier;     /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
};


#include "fonction_lecture.cpp"
#include "fonctions_tries_ensembles.cpp"
//#include "fonction_glpk.cpp"


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



/*********************************************************************/
//                              Main
/*********************************************************************/

int main(int argc, char *argv[])
{
    
    /* Déclarations des variables (à compléter) */

    donnees p; 
    double temps;
        
    /* Chargement des données à partir d'un fichier */
    
    lecture_data(argv[1], &p);
    
    /* On vérifie que l'on a bien une capacitée pour chaque point de pompage */

    assert(p.capacite.size() == p.lieu.size());    
    
    /* Lancement de la résolution... */

    crono_start(); // .. et donc du chronomètre




    /* .... */




    /* Déclaration des variables necéssaires au calcul des tournées possibles */
    vector<vector<int>> tournees;
	vector<int> longueurTournee;
    vector<int> nbOccu;



    tournees = ensembleDesParties(&p);
    //cout << "Tout les regroupements : " << endl;
    //affiche(tournees);
    //cout << endl;
    
    /* PLUS NECESSAIRE
    tournees = ensembleDesPartiesPossibles(tournees, &p);
    cout << "Tout les regroupements possibles : " << endl;
    affiche(tournees);
    cout << endl;
    */

    tournees = ensembleDesPermutationsPossibles(tournees, &p);
    //cout << "Tout les regroupements permutes possibles : " << endl;
    //affiche(tournees);
    //cout << endl;
    tournees = permutationLesPlusPetites(tournees, longueurTournee, &p);
    //cout << "Les plus courtes tournées : " << endl;
    //affiche(tournees);
    //cout << endl;

    nbOccu = nombreOccurencePuitTournee(tournees, &p);
    // cout << "Nombre d'occurence de chaques villes dans nos tournée possibles : " << endl;
    // for (int k = 0; k < nbOccu.size(); ++k)
    // {
    // 	cout << nbOccu[k] << ";";
    // }



    resolutionGLPK(tournees, longueurTournee, nbOccu, &p);




    /* ... */




    /* Problème résolu, arrêt du chrono */
    
    crono_stop();
    temps = crono_ms()/1000,0;
    
    /* Affichage des résultats (à compléter) */
    
    printf("Temps : %f\n",temps);   
    
    return 0;
}
