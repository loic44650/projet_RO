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


/* Sous-fichiers du programme */

#include "fonction_lecture.cpp"
#include "fonctions_tournees.cpp"
#include "fonction_glpk.cpp"


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

    /* Déclaration des variables necéssaires au calcul des tournées possibles */
    vector<vector<int>> tournees;
	vector<int> longueurTournee;
    vector<vector<int>> occu;

    tournees = ensembleDesPartiesPossibles(&p);
    //cout << "Toutes les tournées : " << endl;
    //affiche(tournees);
    //cout << endl;
    
    tournees = ensembleDesPermutationsPossibles(tournees, &p);
    //cout << "Toutes les permutations de tournée possibles : " << endl;
    //affiche(tournees);
    //cout << endl;
    
    tournees = permutationLesPlusPetites(tournees, longueurTournee, &p);
    //cout << "Les plus courtes tournées : " << endl;
    //affiche(tournees);
    //cout << endl;

    occu = indiceVecteurOccu(tournees, &p);
    //cout << "Indice des vecteur contenant le lieu i : " << endl;
    //affiche(occu);
    //cout << endl;

    resolutionGLPK(tournees, longueurTournee, occu, &p);

    /* Problème résolu, arrêt du chrono */
    crono_stop();
    temps = crono_ms()/1000.0;
    
    /* Affichage des résultats (à compléter) */
    cout << "Temps : " << temps << " secondes." << endl;   
    
    return 0;
}
