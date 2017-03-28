void resolutionGLPK(donnees *p)
{ 
    glp_prob *prob; // déclaration d'un pointeur sur le problème
    
    int *ia;
    int *ja;
    double *ar; // déclaration des 3 tableaux servant à définir la matrice "creuse" des contraintes
    
    /* variables récupérant les résultats de la résolution du problème (fonction objectif et valeur des variables) */  
    double z; 
    double *x; 
    
    /* autres déclarations */ 
    int nbcreux; // nombre d'éléments de la matrice creuse
    int pos; // compteur utilisé dans le remplissage de la matrice creuse
    int nbcontr = p -> lieu.size();
    int nbvar = lieu.size() * p -> lieu.size();     

    /* Transfert de ces données dans les structures utilisées par la bibliothèque GLPK */
    prob = glp_create_prob(); /* allocation mémoire pour le problème */ 
    glp_set_prob_name(prob, "optmisation tournée"); /* affectation d'un nom (on pourrait mettre NULL) */
    glp_set_obj_dir(prob, GLP_MIN); /* Il s'agit d'un problème de minimisation, on utiliserait la constante GLP_MAX dans le cas contraire */
    
    /* Déclaration du nombre de contraintes (nombre de lignes de la matrice des contraintes) : p.nbcontr */
    glp_add_rows(prob, nbcontr); 

    /* On commence par préciser les bornes sur les constrainte, les indices commencent à 1 (!) dans GLPK */
    for (int i = 1; i <= nbcontr; ++i)
    {
        /* partie indispensable : les bornes sur les contraintes */
        glp_set_row_bnds(prob, i, GLP_FX, p.droite[i - 1], 1.0); 
        /* Avec GLPK, on peut définir simultanément deux contraintes, si par exemple, on a pour une contrainte i : "\sum x_i >= 0" et "\sum x_i <= 5",
           on écrit alors : glp_set_row_bnds(prob, i, GLP_DB, 0.0, 5.0); la constante GLP_DB signifie qu'il y a deux bornes sur "\sum x_i" qui sont ensuite données
           Ici, nous n'avons qu'une seule contrainte du type "\sum x_i >= p.droite[i-1]" soit une borne inférieure sur "\sum x_i", on écrit donc glp_set_row_bnds(prob, i, GLP_LO, p.droite[i-1], 0.0); le paramètre "0.0" est ignoré. 
           Les autres constantes sont GLP_UP (borne supérieure sur le membre de gauche de la contrainte) et GLP_FX (contrainte d'égalité).   
         Remarque : les membres de gauches des contraintes "\sum x_i ne sont pas encore saisis, les variables n'étant pas encore déclarées dans GLPK */ 
    }   

    /* Déclaration du nombre de variables : p.nbvar */
    glp_add_cols(prob, nbvar); 
        
    /* On précise le type des variables, les indices commencent à 1 également pour les variables! */
    
    for (int i = 1; i <= p.nbvar; ++i)
    {
        /* partie obligatoire : bornes éventuelles sur les variables, et type */
        glp_set_col_bnds(prob, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
        glp_set_col_kind(prob, i, GLP_BV);  /* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */    
    } 

    /* définition des coefficients des variables dans la fonction objectif */

    for(int i = 1; i <= p.nbvar; ++i) glp_set_obj_coef(prob,i,p.couts[i - i]);  
    
    /* Définition des coefficients non-nuls dans la matrice des contraintes, autrement dit les coefficients de la matrice creuse */
    /* Les indices commencent également à 1 ! */

    nbcreux = 0;
    for(int i = 0; i < p.nbcontr; ++i) nbcreux += p.sizeContr[i];
    
    ia = (int *) malloc ((1 + nbcreux) * sizeof(int));
    ja = (int *) malloc ((1 + nbcreux) * sizeof(int));
    ar = (double *) malloc ((1 + nbcreux) * sizeof(double));
    
    pos = 1;
    for(int i = 0; i < p.nbcontr; ++i)
    {
        for(int j = 0; j < p.sizeContr[i]; ++j)
        {
            ia[pos] = i + 1;
            ja[pos] = p.contr[i][j];
            ar[pos] = 1.0;
            pos++;
        }
    }
    
    /* chargement de la matrice dans le problème */
    
    glp_load_matrix(prob,nbcreux,ia,ja,ar); 
    
    /* Optionnel : écriture de la modélisation dans un fichier (utile pour debugger) */

    glp_write_lp(prob,NULL,"musee.lp");

    /* Résolution, puis lecture des résultats */
    
    glp_simplex(prob,NULL); glp_intopt(prob,NULL); /* Résolution */
    z = glp_mip_obj_val(prob); /* Récupération de la valeur optimale. Dans le cas d'un problème en variables continues, l'appel est différent : z = glp_get_obj_val(prob);*/
    x = (double *) malloc (p.nbvar * sizeof(double));
    for(int i = 0; i < p.nbvar; ++i) x[i] = glp_mip_col_val(prob,i+1); /* Récupération de la valeur des variables, Appel différent dans le cas d'un problème en variables continues : for(i = 0;i < p.nbvar;i++) x[i] = glp_get_col_prim(prob,i+1);  */

    printf("z = %lf\n",z);
    for(int i = 0; i < p.nbvar; ++i) printf("x%c = %d, ",'B'+i,(int)(x[i] + 0.5)); /* un cast est ajouté, x[i] pourrait être égal à 0.99999... */ 
    puts("");

    /* libération mémoire */
    glp_delete_prob(prob); 
    free(p.couts);
    free(p.sizeContr);
    free(p.droite);
    for(int i = 0; i < p.nbcontr; ++i) free(p.contr[i]);
    free(p.contr);
}