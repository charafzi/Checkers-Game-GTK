#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Interface.h"
#include <stdio.h>
#include <glib.h>
#include <stdbool.h>
#define NbElem 10
#define INFINITY 9999

//Structure Pion
typedef struct PN
{
	int x;           //position horizontale
	int y;           //position verticale
	int type;        //type du pion (pion normale/double)
	GtkWidget *pion; //pointeur sur le bouton qui représente le pion
	struct PN* suiv; //pointeur sur suivant
}pion;

//Structure Joueur
typedef struct
{
	unsigned char couleur;  //la Couleur de la liste des pions
	unsigned char genre;    //le genre du joueur (machine/joueur)
	pion* liste;            //liste des pions
}Player;

//structure de liste d'un chemin de déplacement d'un pion
typedef struct CH
{
    position pos;       //position de la case
    gboolean manger;    /*  true  : càd manger le pion d'adversaire situé dans cette case
                            false : càd ne pas manger, juste se déplacer vers cette case
                        */
    struct CH *derniere_cel; //pointeur sur derniere cellule de la liste
    struct CH *svt;          //pointeur suivant
    struct CH *pred;         //pointeur precedent
}chemin;

//stucture d'arbre des chemins
typedef struct ND
{
    chemin *liste_chemin;   // pointeur sur la liste du chemin
    struct ND *fils;        // pinteur sur le noeud fils
}arbre_chemins;

/*
structure pour passer les informations associé à un pion
à la fonction g_signal_connect
*/
typedef struct
{
    GtkWidget *grid;         // grid principal
    pion **liste_joueur1;     // Adresse de la liste des pions Joueur
    pion **liste_joueur2;    // Adresse de la liste des pions Machine
    int type_J;              // Type joueur (Joueur1 == 0 / Joueur2 == 1)
    pion *Checker;           // la cellule du pion qui contient les infos sur le pion
    arbre_chemins *arbre;    // pointeur sur la racine d'arbre des chemins

}CheckerData;

//structure de liste des widgets
typedef struct LCD
{
    CheckerData *CD;    //pointeur sur structure checker data
    struct LCD *svt;    //pointeur sur suivant
}Liste_CheckerData;

//structure de liste des widgets
typedef struct LW
{
    GtkWidget *widget;  //pointeur sur widget
    struct LW *svt;     //pointeur sur suivant
}Liste_wdgt;

//structure de liste des positions
typedef struct cl
{
    position pos;
    struct cl* svt;
}liste_pos;

/*
Structure qui regroupe toutes les informations sur le jeu
*/
typedef struct
{
    Player *Joueur1;     // Joueur
    Player *Joueur2;    // Machine
    GtkWidget* grid;    //grid princiaple qui représente la table du jeu
    GtkApplication *app;// Application qui contient le jeu
    GtkWidget *window;  // Fenetre du jeu
    char couleurJ;      //couleur joueur 1
    char couleurM;      //couleur joueur 2
    int diff;           //difficulté choisie par joueur 1
    int choix;          /* 1: Joueur VS Joueur
                           2:  Machine VS Joueur
                           3: Machine VS Machine
                         */
}Game;

/*
Structure de l'arbre MiniMax pour décision du mouvement pour la machine
*/
typedef struct Noeud
{
    int tab_simulation[NbElem][NbElem];// tableau copie pour la simulation du jeu
    float score;                       // score
    position pos;                      // position du pion
    chemin *lst;                       // liste du chemin du déplacement
    struct Noeud *frere;                //pointeur sur frere
    struct Noeud *fils;                 //pointeur sur fils
}ArbMinMax;

/*
  //***Code Contenu de la matrice du jeu de Dames

   0 : libre
   1 : Occupé Blanc Joueur (pion simple)
   2 : Occupé Blanc Machine(pion simple)
   3 : Occupé Noir  Joueur (pion simple)
   4 : Occupé Noir Machine (pion simple)

   5 : Occupé Blanc Joueur (pion double)
   6 : Occupé Blanc Machine(pion double)
   7 : Occupé Noir  Joueur (pion double)
   8 : Occupé Noir Machine (pion double)
*/

/*
    Matrice du jeu
*/
int table[NbElem][NbElem];

//***Fonction signal qui chnage le curseur de la souris en curseur pointeur
gboolean cursor_to_pointer(GtkWidget *widget, GdkEvent *event, gpointer data)
{
  GdkWindow *window = gtk_widget_get_window(widget);
  GdkCursor *cursor = gdk_cursor_new(GDK_HAND2);
  gdk_window_set_cursor(window, cursor);
  return FALSE;
}

//***Fonction signal qui chnage le curseur de la souris en curseur par défaut
gboolean cursor_to_default(GtkWidget *widget, GdkEvent *event, gpointer data) {
  GdkWindow *window = gtk_widget_get_window(widget);
  GdkCursor *cursor = gdk_cursor_new(GDK_LEFT_PTR);
  gdk_window_set_cursor(window, cursor);
  return FALSE;
}

 /**
 -Entree        : tableau du jeu
 -Sortie        :
 -Description   :Cette fonction permet de l'initialisation de la matrice du jeu de Dames
 **/
void initialisation_matrice(int table[NbElem][NbElem])
{
    int i,j;
    for(i=0;i<NbElem;i++)
    {
        for(j=0;j<NbElem;j++)
        {
            if(i%2==0)
            {
                if(j%2==0)
                    table[i][j]=-1;
                else
                    table[i][j]=0;
            }
            else
            {
                if(j%2==0)
                    table[i][j]=0;
                else
                    table[i][j]=-1;
            }
        }
    }
}

void afficher_matrice(int table[NbElem][NbElem])
{
    int i,j;
    printf("\n      Matrice:     \n");
    for(i=0;i<NbElem;i++)
    {
        for(j=0;j<NbElem;j++)
            printf("%d\t",table[i][j]);
        printf("\n");
    }
    printf("\n");
}

/**
 -Entree        : grid principal qui contient les cases
 -Sortie        :
 -Description   : Cette fonction permet de recolorer les cases par leur couleur par défaut (marron et blanc)
 **/
void set_grids_color(GtkWidget *mainGrid)
{
    int indi,indj;
    GtkWidget *event_box,*child_grid;
    GList *children;
    for (indi = 0; indi < 10; indi++)
	{
		for (indj = 0; indj < 10; indj++)
		{
		    //récuperer le contenaire event box qui contient childGrid
		    event_box = gtk_grid_get_child_at(GTK_GRID(mainGrid),indj, indi);
		    //récuperer childGrid
            children  =gtk_container_get_children(GTK_CONTAINER(event_box));
            child_grid=children->data;
            //colorer selon la position de la cases (claire / foncée)
			if (indi % 2 == 0)
			{
				if (indj % 2 == 0)
				{
					add_css(child_grid, cssGridWhite);
				}
				else
				{
					add_css(child_grid, cssGridBrown);
				}
			}
			else
			{
				if (indj % 2 == 0)
				{
					add_css(child_grid,cssGridBrown);
				}
				else
				{
					add_css(child_grid, cssGridWhite);
				}
			}
		}
	}
}

/**
 -Entree        : position x et y de la case
 -Sortie        : booléan (0|1)
 -Description   : Cette fonction permet de vérifier l'existence de la case
                  dans la table du jeu
 **/
int case_existe(int table[NbElem][NbElem],int x,int y)
{
    if(x>=0 && y>=0 && x<NbElem && y<NbElem) return (int)1;
    return (int)0;
}

/**
 -Entree        : position x et y de la case
 -Sortie        : booléan (0|1)
 -Description   : Cette fonction permet de vérifier que la case est vide
 **/
int case_vide(int table[NbElem][NbElem],int x,int y)
{
    if(table[y][x]==0) return (int)1;
    return (int)0;
}


/**
 -Entree        : position x et y de la case
 -Sortie        : booléan (0|1)
 -Description   : Cette fonction permet de vérifier si la case est occupé
                  par un pion du joueur
 **/
int case_occupe_joueur(int table[NbElem][NbElem],int x,int y)
{
    if(table[y][x]==1 || table[y][x]==3 || table[y][x]==5 || table[y][x]==7) return (int)1;
    return (int)0;
}

/**
 -Entree        : position x et y de la case
 -Sortie        : booléan (0|1)
 -Description   : Cette fonction permet de vérifier si la case est occupé
                  par un pion de la machine
 **/
int case_occupe_machine(int table[NbElem][NbElem],int x,int y)
{
    if(table[y][x]==2 || table[y][x]==4 || table[y][x]==6 || table[y][x]==8) return (int)1;
    return (int)0;
}


/**
-Entrée         :Pointeur sur la cellule du pion
-Sortie         :Retourne: -1 :si le pion est NULL
                            1 :si le pion devient Dame
                            0 :sinon.
-Description    : Cette fonction verifie si le pion arrive a
                  l'autre extrémité de l'adversaire, si oui il le change en dame
**/
pion *Is_King(pion *liste,int x,int y)
{
    pion *crt=liste;
    if(!liste)
    {
        printf("\n Le Pion passé en parametre est NULL dans la fonction IS_King");
        return((pion*)NULL);
    }
    // Pour le cas du pion joueur
    if(y==0)
    {
        // vérifier que c'est un pion simple
        if(table[y][x]==1 || table[y][x]==3)
        {
            // chercher le pion dans la liste du joueur
            while(crt)
            {
                if(crt->x==x && crt->y==y) break;
                crt=crt->suiv;
            }
            // vérifier qu'on a trouvé le pion
            if(crt->x==x && crt->y==y)
            {
                // changer le type en dame
                crt->type=1;
                // changer le pion en dame dans le jeu
                if(table[y][x]==1)
                {
                    add_css(crt->pion,cssKingBeige);                }
                if(table[y][x]==3)
                {
                    add_css(crt->pion,cssKingBlack);
                }
                // changer indice dans la table
                table[y][x]+=4;
            }
        }
    }
    //meme traitement pour le cas machine
    if(y==9)
    {
        if(table[y][x]==2 || table[y][x]==4)
        {
            while(crt)
            {
                if(crt->x==x && crt->y==y) break;
                crt=crt->suiv;
            }
            if(crt->x==x && crt->y==y)
            {
                crt->type=1;
                if(table[y][x]==2)
                {
                    add_css(crt->pion,cssKingBeige);
                }
                if(table[y][x]==4)
                {
                    add_css(crt->pion,cssKingBlack);
                }
                // changer indice dans la table
                table[y][x]+=4;
            }
        }
    }
    return (pion*)liste;
}

/**
 -Entree        : * Couleur (B: Blanc / N: Noir)
                  * Type    (M: machine / J: joueur)
 -Sortie        : Pointeur sur structure joueur
 -Description   : Cette fonction alloue de l'espace memoire pour le player et l'initialise
 **/
Player  *Creer_joueur(unsigned char col,unsigned char type)
{
    Player *P1;
    P1=(Player*)malloc(sizeof(Player));
    P1->liste=(pion*)malloc(sizeof(pion));
    if(!P1 || !P1->liste)
    {
        printf("\n Erreur d allocation dans la fonction Creer_Joueur");
        exit(-1);
    }

    P1->couleur=col;
    P1->genre=type;
    P1->liste=NULL;
    return ((Player*)P1);
}

 /**
 -Entree        : position x et y du pion
                  orientation Vertical  : H -> Haut
                                          B -> Bas
                  orientation Horizontal: D -> Droit
                                          G -> Gauche
 -Sortie        : 1 si la dame peut manger dont la diagonale
                  0 sinon
 -Description   : cette fonction permet de vérifier si une dame du joueur peut manger une dame
                  adversaire dans la diagonale passé en argument
 **/

 int dame_peut_manger(int table[NbElem][NbElem],int x,int y,int type_joueur,char orientationV, char orientationH)
 {
    int dx = 0, dy = 0;
    if (orientationV == 'H') dy = -1;
    else if (orientationV == 'B') dy = 1;
    if (orientationH == 'D') dx = 1;
    else if (orientationH == 'G') dx = -1;
    int nx = x + dx,ny = y + dy;
     // si la case existe
    if(case_existe(table,x,y))
    {
        if(type_joueur==0)
        {
            if(case_occupe_machine(table,nx,ny))
            {
                // si oui
                if(case_existe(table,nx+dx,ny+dy) && case_vide(table,nx+dx,ny+dy)) return (int)1;
                //si non
                else return (int)0;
            }
            // vérifier si la case est occupé par joueur
            else if(case_occupe_joueur(table,nx,ny)) return (int)0;
            //sinon (la case est vide) on vérifie récursivement
            else return (int)dame_peut_manger(table,nx,ny,type_joueur,orientationV,orientationH);
        }
        else
        {
            if(case_occupe_joueur(table,nx,ny))
            {
                // si oui
                if(case_existe(table,nx+dx,ny+dy) && case_vide(table,nx+dx,ny+dy)) return (int)1;
                //si non
                else return (int)0;
            }
            // vérifier si la case est occupé par joueur
            else if(case_occupe_machine(table,nx,ny)) return (int)0;
            //sinon (la case est vide) on vérifie récursivement
            else return (int)dame_peut_manger(table,nx,ny,type_joueur,orientationV,orientationH);
        }
    }
    // si la case n'existe pas
    else return(int)0;
}
/**
 -Entree        : *position (x,y) du pion
                  *Type du pion
                  * Le widget bouton (pion)
 -Sortie        : Pointeur sur du type pion
 -Description   : Cette fonction permet de créer un cellule de type pion

 **/
pion *creer_cel_pion(int x,int y,int type,GtkWidget *btn)
{
    pion *ne;
    ne=(pion*)malloc(sizeof(pion));
    if(!ne)
    {
        printf("\nErreur allocation mémoire");
        exit(-1);
    }
    ne->x=x;
    ne->y=y;
    ne->type=type;
    ne->pion=btn;
    ne->suiv=NULL;
    return (pion*)ne;
}

/**
 -Entree        : *position (x,y) du pion
                  *Type du pion
                  * Le widget bouton (pion)
 -Sortie        : Pointeur sur du type pion
 -Description   : Cette fonction permet de créer un cellule et de l'ajouter
                  à la liste du Player

 **/
pion *ajouter_cel_pion(pion *lst,int x,int y,int type,GtkWidget *btn)
{
    pion *ne=creer_cel_pion(x,y,type,btn);
    if(!lst) // la liste est vide
    {
        lst=ne;
        return (pion*)lst;
    }
    // la liste contient déjà des éléments
    ne->suiv=lst;
    lst=ne;
    return (pion*)lst;
}

 /**
 -Entree        : * Position de la case
                  * Boolean (true|false) pour indiquer de manger le pion située dans cette case ou non
 -Sortie        : pointeur de type chemin
 -Description   : cette fonction permet de creer une cellule de type chemin
 **/
 chemin *creer_cel_chemin(position pos,gboolean manger_ce_pion)
 {
     chemin *ne;
     ne=(chemin*)malloc(sizeof(chemin));
     if(!ne)
     {
         printf("\nErreur allocation memoire (cellule chemin)!");
         exit(-1);
     }
     ne->pos=pos;
     ne->manger=manger_ce_pion;
     ne->derniere_cel=NULL;
     ne->svt=NULL;
     ne->pred=NULL;
     return (chemin*)ne;
 }

 /**
 -Entree        : * Liste du chemin
                  * Position x et y de la case
                  * Boolean (true|false) pour indiquer de manger le pion située dans cette case ou non
 -Sortie        : pointeur de type chemin
 -Description   : cette fonction permet de creer une cellule de type chemin et de
                  l'ajouter à la liste du chemin
 **/
 chemin *ajouter_cel_chemin(chemin *lst,int x,int y,gboolean manger_ce_pion)
 {
     position pos={x,y};
     chemin *ne=creer_cel_chemin(pos,manger_ce_pion), *crt=lst;
     // si liste est vide
     if(!lst)
     {
         lst=ne;
         // la derniere cellule est celle ajouté
         lst->derniere_cel=ne;
         return (chemin*)lst;
     }
     //chercher fin liste
     while(crt->svt)
        crt=crt->svt;
     // ajout de la cellule à la fin
     crt->svt=ne;
     ne->pred=crt;
     //pointer sur la derniere cellule
     lst->derniere_cel=ne;
     return (chemin*)lst;
 }

/**
 -Entree        : Liste du chemin à copier
 -Sortie        : pointeur de type chemin
 -Description   : cette fonction permet de faire une copie d'une liste d' un chemin
                  et de la retourner
 **/
 chemin *copier_chemin(chemin *chemin_origin)
 {
     chemin *crt=chemin_origin, *copie=NULL;
     position pos;
     // on copie toutes les cellules du chemin_origin
     while(crt)
     {
         copie=ajouter_cel_chemin(copie,crt->pos.x,crt->pos.y,crt->manger);
         crt=crt->svt;
     }
     return (chemin*)copie;
 }

/**
 -Entree        : Liste du chemin
 -Sortie        : pointeur de type arbre_chemins
 -Description   : cette fonction permet de creer un noeud de type arbre_chemins
                  et d'ajouter la liste passé en argument à ce noeud
**/
 arbre_chemins *creer_noeud_arbre_chemin(chemin *lst)
 {
     arbre_chemins *ne;
     ne=(arbre_chemins*)malloc(sizeof(arbre_chemins));
     if(!ne)
     {
         printf("\nErreur allocation memoire (Noeud arbre_chemin)!");
         exit(-1);
     }
     ne->liste_chemin=lst;
     ne->fils=NULL;
     return (arbre_chemins*)ne;
}

/**
 -Entree        : * Racine de l'arbre
                  * Noeud à ajouter
 -Sortie        : pointeur de type arbre_chemins
 -Description   : cette fonction permet d'ajouter un noeud à l'arbre de type arbre_chemin
 **/
 arbre_chemins *ajouter_noeud_arbre_chemin(arbre_chemins *racine,arbre_chemins *noeud)
 {
     // si la racine n'existe pas
     if(!racine)
     {
         racine=noeud;
         return (arbre_chemins*)racine;
     }
     else
     {
         // si la racine n'a pas un fils
        if(!racine->fils)
            racine->fils=noeud;
        else // sinon passer à ce fils
            racine->fils=ajouter_noeud_arbre_chemin(racine->fils,noeud);
        return (arbre_chemins*)racine;
     }
 }

   /**
 -Entree        : -racine de l'arbre des chemin
                  -liste du chemin
                  -orientation Verticale
                  -orientation horizontal
 -Sortie        : pointeur de type  arbre_chemins
 -Description   : cette fonction permet d'ajouter toutes les cases disponibles pour
                  le déplacement dans la diagonale  pour la dame en se basant
                  sur la derniere case qui exsite dans la liste chemin
 **/
 arbre_chemins *ajouter_tt_cases_diagonale(arbre_chemins *racine,
                                           chemin *lst,
                                           char orientationV,
                                           char orientationH
                                           )
 {
    int dx = 0, dy = 0,x,y;
    if (orientationV == 'H') dy = -1;
    else if (orientationV == 'B') dy = 1;
    if (orientationH == 'D') dx = 1;
    else if (orientationH == 'G') dx = -1;
     // pointer initialement sur la liste du chemin
     chemin *pred=lst;
    // recuperer les coordonnes de la deriniere case du chemin
    x=lst->derniere_cel->pos.x+dx, y=lst->derniere_cel->pos.y+dy;
    /* tant que il ya une case existe et qui est vide on l'ajoute
            on copie le chemin et on ajoute cette case
    */
    while(case_existe(table,x,y) && case_vide(table,x,y))
    {
        // copier le chemin
        chemin *copie=NULL;
        copie=copier_chemin(pred);
        // ajouter la case vide
        copie=ajouter_cel_chemin(copie,x,y,FALSE);
        // ajouter un nouveau chemin dans l'arbre
        arbre_chemins* nv_nd = creer_noeud_arbre_chemin(copie);
        nv_nd=creer_noeud_arbre_chemin(copie);
        racine=ajouter_noeud_arbre_chemin(racine,nv_nd);
        // pointer sur la liste copié
        pred=copie;
        // passer à la case suivante
        x+=dx;
        y+=dy;
    }
     return (arbre_chemins*)racine;
 }

  /**
 -Entree        : liste du chemin
 -Sortie        :
 -Description   : Cette fonctoin fait affichage d'une liste
 **/
 void afficher_chemin(chemin *lst)
 {
     chemin *crt;
     if(!lst) printf("\nListe du chemin vide!");
     else
     {
         crt=lst;
         while(crt)
         {
             printf("\nCase(%d,%d) manger=%d",crt->pos.x,crt->pos.y,crt->manger);
             crt=crt->svt;
         }
     }
 }
  /**
 -Entree        :   * racine de l'arbre
                    * un entier intialement on passe 1
 -Sortie        :
 -Description   : Cette fonction fait l'affichage de l'arbre des chemins
 **/
 void afficher_arbre_chemin(arbre_chemins *arbre, int nombre_chemin)
 {
     if(!arbre) printf("\nArbre des chemins vide!");
     else
     {
         printf("\nChemin N°%d",nombre_chemin);
         afficher_chemin(arbre->liste_chemin);
         if(arbre->fils) afficher_arbre_chemin(arbre->fils,nombre_chemin+1);
     }
 }

 /**
 -Entree        : racine de l'arbre
 -Sortie        : un entier
 -Description   : cette fonction retourne la taille de l'arbre
 **/

 int taille_arbre_chemin(arbre_chemins *arb)
 {
     if(arb)
     {
         return (int)taille_arbre_chemin(arb->fils)+1;
     }
 }

  pion *detruire_liste_pions(pion *lst)
 {
     pion *esup;
     if(!lst) return(pion*)NULL;
     else
     {
         while(lst)
         {
             esup=lst;
             lst=lst->suiv;
             free(esup);
         }
         return(pion*) NULL;
     }
 }

 /**
 -Entree        : liste d'un chemin
 -Sortie        : liste null
 -Description   : cette fonction fait la destruction d'une liste
 **/
 chemin *detruire_liste_chemin(chemin *lst)
 {
     chemin *esup;
     if(!lst) return(chemin*)NULL;
     else
     {
         while(lst)
         {
             esup=lst;
             lst=lst->svt;
             free(esup);
         }
         return(chemin*) NULL;
     }
 }
/**
 -Entree        : racine de l'arbre
 -Sortie        : arbre null
 -Description   : cette fonction fait la destruction d'une arbre
 **/
arbre_chemins *detruire_arbre_chemin(arbre_chemins *arbre)
 {
     // si un fils existe, supprimer le fils d'abord
    if(arbre->fils) arbre->fils=detruire_arbre_chemin(arbre->fils);
    //sinon detruire ce noeud
    arbre->liste_chemin=detruire_liste_chemin(arbre->liste_chemin);
    free(arbre);
    return (arbre_chemins*)NULL;
 }

 /**
 -Entree        :   * position x et y du pion
                    * type du pion
                    * pionteur sur le pointeur du chemin initialement passé avec NULL
                    * entier : 1 désigne premier appel du fonction
                               0 sinon
                    * orientation vertical pour la dame initialement passé à NULL
                    * orientation horizontal pour la dame initialement passé à NULL
 -Sortie        : pointeur de type arbre_chemins
 -Description   : cette fonction fait la construction de l'arbre de tout les chemins possible
                  de déplacement pour une pion/dame passé en argument
 **/
 arbre_chemins *prise_pion(int table[NbElem][NbElem],int x,int y,
                           int type_pion,int type_joueur,
                           arbre_chemins *racine,
                           chemin **path,
                           int premier_appel,
                           char orientationV,
                           char orientationH

                           )
 {
     arbre_chemins *arbre=NULL;
     int peut_manger[4]={0,0,0,0},/* chaque indice represente une diagonale
                                     0: on peut manger / 1: on ne peut pas
                                  */

        i,j,        // variable de parcours
        posx,posy,  //pour stocker les coordonnes de la case
        directions[4][2]={ {-1,1} ,{-1,-1} ,{1,1} ,{1,-1} };/* matrice pour présenter les pas pour chaque diagnole
                                                            directions[0][]: Un pas vers diagonale Haut Droit
                                                            directions[1][]: Un pas vers diagonale Haut Gauche
                                                            directions[2][]: Un pas vers diagonale Bas Droit
                                                            directions[3][]: Un pas vers diagonale Bas Gauche
                                                            */

     char directionsDiag[4][2] = { {'H', 'D'}, {'H', 'G'}, {'B', 'D'}, {'B', 'G'} };
     chemin         *chemins[4]={NULL};
     arbre_chemins  *noeuds[4] = {NULL};

     if(case_existe(table,x,y))
     {
         // si pion simple
         if(type_pion==0)
         {
             //si premier appel de cette fonction
            if(premier_appel)
            {
                if(type_joueur==0)
                {
                    //on teste sur le haut gauche et le haut droit
                     for(i=0;i<2;i++)
                     {
                         if(case_existe(table,x + directions[i][1], y + directions[i][0]))
                         {
                             //haut occupé par machine
                             if(case_occupe_machine(table,x + directions[i][1], y + directions[i][0]))
                             {
                                 //case au dessus est vide
                                 if(case_existe(table,x + directions[i][1]*2,y + directions[i][0]*2) && case_vide(table,x + directions[i][1]*2,y + directions[i][0]*2))
                                 {
                                    //ajouter case et marquer de la manger
                                    chemins[i]  =ajouter_cel_chemin(chemins[i],x + directions[i][1],y + directions[i][0],TRUE);
                                    //ajouter case et marquer de ne la pas manger
                                    chemins[i]  =ajouter_cel_chemin(chemins[i],x + directions[i][1]*2,y + directions[i][0]*2,FALSE);
                                    //ajout du noeud a l'arbre
                                    noeuds[i]=creer_noeud_arbre_chemin(chemins[i]);
                                    arbre=ajouter_noeud_arbre_chemin(arbre,noeuds[i]);
                                    //appel recursive sur la case vide pour tester la possibilité de nouveaux prises
                                    arbre=prise_pion(table,x + directions[i][1]*2,y + directions[i][0]*2,0,0,arbre,&chemins[i],0,NULL,NULL);
                                 }
                             }
                             else if(case_vide(table,x + directions[i][1], y + directions[i][0]))
                             {
                                //ajouter case a la liste et declarer de ne pas manger
                                chemins[i]  =ajouter_cel_chemin(chemins[i],x + directions[i][1],y + directions[i][0],FALSE);
                                //ajouter noeud a l'arbre
                                noeuds[i]=creer_noeud_arbre_chemin(chemins[i]);
                                arbre=ajouter_noeud_arbre_chemin(arbre,noeuds[i]);
                             }

                         }
                     }
                     return (arbre_chemins*)arbre;
                }
                else
                {
                    //on teste sur le haut gauche et le haut droit
                     for(i=2;i<4;i++)
                     {
                         if(case_existe(table,x + directions[i][1], y + directions[i][0]))
                         {
                             //haut occupé par machine
                             if(case_occupe_joueur(table,x + directions[i][1], y + directions[i][0]))
                             {
                                 //case au dessus est vide
                                 if(case_existe(table,x + directions[i][1]*2,y + directions[i][0]*2) && case_vide(table,x + directions[i][1]*2,y + directions[i][0]*2))
                                 {
                                    //ajouter case et marquer de la manger
                                    chemins[i]  =ajouter_cel_chemin(chemins[i],x + directions[i][1],y + directions[i][0],TRUE);
                                    //ajouter case et marquer de ne la pas manger
                                    chemins[i]  =ajouter_cel_chemin(chemins[i],x + directions[i][1]*2,y + directions[i][0]*2,FALSE);
                                    //ajout du noeud a l'arbre
                                    noeuds[i]=creer_noeud_arbre_chemin(chemins[i]);
                                    arbre=ajouter_noeud_arbre_chemin(arbre,noeuds[i]);
                                    //appel recursive sur la case vide pour tester la possibilité de nouveaux prises
                                    arbre=prise_pion(table,x + directions[i][1]*2,y + directions[i][0]*2,0,1,arbre,&chemins[i],0,NULL,NULL);
                                 }
                             }
                             else if(case_vide(table,x + directions[i][1], y + directions[i][0]))
                             {
                                //ajouter case a la liste et declarer de ne pas manger
                                chemins[i]  =ajouter_cel_chemin(chemins[i],x + directions[i][1],y + directions[i][0],FALSE);
                                //ajouter noeud a l'arbre
                                noeuds[i]=creer_noeud_arbre_chemin(chemins[i]);
                                arbre=ajouter_noeud_arbre_chemin(arbre,noeuds[i]);
                             }
                         }
                     }
                     return (arbre_chemins*)arbre;
                }
            }
            else// si ce n'est pas premier appel de cette fonction
            {
                chemin *copie=NULL;/* Pour copier une liste du chemin.
                                      c'est pour le cas ou il ya possibilité de manger à gauche et à droite.
                                    */
                arbre_chemins *nv_noeud;
                if(type_joueur==0)
                {
                    //si il ya possibilité de manger à gauche
                    if(case_existe(table,x-1,y-1) && case_occupe_machine(table,x-1,y-1))
                    {
                        if(case_existe(table,x-2,y-2) && case_vide(table,x-2,y-2)) peut_manger[1]=1;
                    }
                    //si il ya possibilité de manger à droite
                    if(case_existe(table,x+1,y-1) && case_occupe_machine(table,x+1,y-1))
                    {
                        if(case_existe(table,x+2,y-2) && case_vide(table,x+2,y-2)) peut_manger[0]=1;
                    }
                    // si on peut manger soit à droite soit à gauche
                    if (peut_manger[0] || peut_manger[1])
                    {
                        chemin *copie = copier_chemin(*path);
                        //si on peut manger a gauche
                        if (peut_manger[1])
                        {
                            copie = ajouter_cel_chemin(copie, x-1, y-1, TRUE);
                            copie = ajouter_cel_chemin(copie, x-2, y-2, FALSE);
                            racine = prise_pion(table,x-2, y-2, 0,0, racine, &copie,0, NULL, NULL);
                        }
                        //si on peut manger a droite
                        if (peut_manger[0])
                        {
                            *path = ajouter_cel_chemin(*path, x+1, y-1, TRUE);
                            *path = ajouter_cel_chemin(*path, x+2, y-2, FALSE);
                            racine = prise_pion(table,x+2, y-2, 0,0, racine, path,0, NULL, NULL);
                        }

                        arbre_chemins *nv_noeud = creer_noeud_arbre_chemin(copie);
                        racine = ajouter_noeud_arbre_chemin(racine, nv_noeud);
                    }
                    /* si aucun de ces tests cad les cases sont vides ou occupes par joueur et on peut rien faire */
                    return (arbre_chemins*)racine;
                }
                else
                {
                    //si il ya possibilité de manger à gauche
                    if(case_existe(table,x-1,y+1) && case_occupe_joueur(table,x-1,y+1))
                    {
                        if(case_existe(table,x-2,y+2) && case_vide(table,x-2,y+2)) peut_manger[1]=1;
                    }
                    //si il ya possibilité de manger à droite
                    if(case_existe(table,x+1,y+1) && case_occupe_joueur(table,x+1,y+1))
                    {
                        if(case_existe(table,x+2,y+2) && case_vide(table,x+2,y+2)) peut_manger[0]=1;
                    }
                    // si on peut manger soit à droite soit à gauche
                    if (peut_manger[0] || peut_manger[1])
                    {
                        chemin *copie = copier_chemin(*path);
                        //si on peut manger a gauche
                        if (peut_manger[1])
                        {
                            copie = ajouter_cel_chemin(copie, x-1, y+1, TRUE);
                            copie = ajouter_cel_chemin(copie, x-2, y+2, FALSE);
                            racine = prise_pion(table,x-2, y+2, 0,1, racine, &copie, 0, NULL, NULL);
                        }
                        //si on peut manger a droite
                        if (peut_manger[0])
                        {
                            *path = ajouter_cel_chemin(*path, x+1, y+1, TRUE);
                            *path = ajouter_cel_chemin(*path, x+2, y+2, FALSE);
                            racine = prise_pion(table,x+2, y+2, 0,1, racine, path, 0, NULL, NULL);
                        }

                        arbre_chemins *nv_noeud = creer_noeud_arbre_chemin(copie);
                        racine = ajouter_noeud_arbre_chemin(racine, nv_noeud);
                    }
                    /* si aucun de ces tests cad les cases sont vides ou occupes par joueur et on peut rien faire */
                    return (arbre_chemins*)racine;
                }
            }
         }
         else// si c'est pion double (dame)
         {
           if(dame_peut_manger(table,x,y,type_joueur,'H','D')) peut_manger[0]=1;// tester si on peut manger dans la diagonale haut droite
            if(dame_peut_manger(table,x,y,type_joueur,'H','G')) peut_manger[1]=1;// tester si on peut manger dans la diagonale haut gauche
            if(dame_peut_manger(table,x,y,type_joueur,'B','D')) peut_manger[2]=1;// tester si on peut manger dans la diagonale bas droite
            if(dame_peut_manger(table,x,y,type_joueur,'B','G')) peut_manger[3]=1;// tester si on peut manger dans la diagonale bas gauche
             // si premier appel de cette fonction
             if(premier_appel)
             {
                 // tester sur la 4 diagonales la possibilité de manger
                 for(i=0;i<4;i++)
                 {
                     //si je ne peux pas manger dans la diagonale
                     if(peut_manger[i]==0)
                     {
                         // si la case juste a cote est vide
                         if(case_existe(table,x + directions[i][1],y + directions[i][0]) && case_vide(table,x + directions[i][1],y + directions[i][0]))
                        {
                            //j'ajoute cette case et je declare de ne la manger pas
                            chemins[i]=ajouter_cel_chemin( chemins[i],x + directions[i][1],y + directions[i][0],FALSE);
                            //j'ajoute le chemin a mon arbre
                            noeuds[i]=creer_noeud_arbre_chemin( chemins[i]);
                            arbre=ajouter_noeud_arbre_chemin(arbre,noeuds[i]);
                        }
                     }
                     else
                     {
                         posx=x + directions[i][1]; posy=y + directions[i][0];
                        // je cherche la case du pion à manger
                       if(type_joueur==0)
                       {
                            while(!case_occupe_machine(table,posx,posy))
                            {
                            posx+=directions[i][1];
                            posy+=directions[i][0];
                            }
                       }
                       else
                       {
                           while(!case_occupe_joueur(table,posx,posy))
                            {
                            posx+=directions[i][1];
                            posy+=directions[i][0];
                            }
                       }
                        // j'ajoute cette derniere et je décalre de la manger
                         chemins[i]=ajouter_cel_chemin( chemins[i],posx,posy,TRUE);
                        // j'ajoute la case au dessus et je décalre ne pas manger (case vide)
                        chemins[i]=ajouter_cel_chemin( chemins[i],posx + directions[i][1],posy + directions[i][0],FALSE);
                        noeuds[i]=creer_noeud_arbre_chemin( chemins[i]);
                        arbre=ajouter_noeud_arbre_chemin(arbre,noeuds[i]);
                        arbre=prise_pion(table,posx + directions[i][1],posy + directions[i][0],1,0,arbre,&chemins[i],0,directionsDiag[i][0],directionsDiag[i][1]);
                     }

                 }
                 return (arbre_chemins*)arbre;
             }
             else// si ce n'est pas premier appel de la fonction
             {
                int testDiag[3]={0,0,0};/* pour stocker juste les 3 diagonales convenables qu'on veut tester la possibilité de la prise
                                           en fontion de quelle diagonale le pion est venu
                                        */
                //si la dame arrive dans le sens du diagonale Haut/Droit
                if(orientationV=='H' && orientationH=='D')
                {
                    testDiag[0]=0;
                    testDiag[1]=1;
                    testDiag[2]=2;
                }
                //si la dame arrive dans le sens du diagonale Haut/Gauche
                if(orientationV=='H' && orientationH=='G')
                {
                    testDiag[0]=0;
                    testDiag[1]=1;
                    testDiag[2]=3;
                }
                //si la dame arrive dans le sens du diagonale Bas/Droit
                if(orientationV=='B' && orientationH=='D')
                {
                    testDiag[0]=0;
                    testDiag[1]=2;
                    testDiag[2]=3;
                }
                //si la dame arrive dans le sens du diagonale Bas/Gauche
                if(orientationV=='B' && orientationH=='G')
                {
                    testDiag[0]=1;
                    testDiag[1]=2;
                    testDiag[2]=3;
                }
                // si je ne peux pas manger dans les 3 trois diagonales on arrete
                if(   !peut_manger[testDiag[0] ]
                    && !peut_manger[testDiag[1] ]
                    && !peut_manger[testDiag[2] ]
                  ) return (arbre_chemins*)racine;
                  //tester la possibilite de manger dans un diagonale, si oui on créée le chemin
                for(j=0;j<3;j++)
                {
                    if(peut_manger[testDiag[j]])
                    {
                        chemins[j]=copier_chemin(*path);
                        posx= x + directions[ testDiag[j] ][1];
                        posy= y + directions[ testDiag[j] ][0];
                        if(type_joueur==0)
                        {
                            while(!case_occupe_machine(table,posx,posy))
                            {
                                posx+=directions[ testDiag[j] ][1];
                                posy+=directions[ testDiag[j] ][0];
                            }
                        }
                        else
                        {
                            while(!case_occupe_joueur(table,posx,posy))
                            {
                                posx+=directions[ testDiag[j] ][1];
                                posy+=directions[ testDiag[j] ][0];
                            }
                        }
                        chemins[j]   =   ajouter_cel_chemin( chemins[j],posx,posy,TRUE);
                        chemins[j]   =   ajouter_cel_chemin( chemins[j],posx + directions[ testDiag[j] ][1],posy + directions[ testDiag[j] ][0],FALSE);
                        noeuds[j]    =   creer_noeud_arbre_chemin( chemins[j]);
                        racine       =   ajouter_noeud_arbre_chemin(racine, noeuds[j]);
                        racine       =   prise_pion( table,posx + directions[ testDiag[j] ][1], posy + directions[ testDiag[j] ][0],1,type_joueur, racine ,& chemins[j],0,directionsDiag[ testDiag[j] ][0],directionsDiag[ testDiag[j] ][1]);
                    }
                }

             return (arbre_chemins*)racine;
         }
      }
    }
 }

 /**
 -Entree        :   * pointeur sur le bouton (pion)
                    * mainGrid (la grid qui contient les cases)
                    * Position actuelle de ce pion (pos1)
                    * Position prochaine de ce pion (pos2)
 -Sortie        :
 -Description   :Cette fonction permet de déplacer le widget bouton (pion) d'une position à une autre
 **/
 void move_checker(GtkWidget *checker,GtkWidget *mainGrid,position pos1,position pos2)
 {
    GtkWidget *child_grid1,*child_grid2,*event_box1,*event_box2;
    GList *children1,*children2;

    //***Recuperation des deux cases selon les 2 positions
    //recupérer event_box qui contient le childGrid dans la positon pos1
    event_box1 = gtk_grid_get_child_at(GTK_GRID(mainGrid),pos1.y, pos1.x);
    //recupérer le childGrid dans la positon pos1
    children1  =gtk_container_get_children(GTK_CONTAINER(event_box1));
    child_grid1=children1->data;

    //recupérer event_box qui contient le childGrid dans la positon pos2
    event_box2 = gtk_grid_get_child_at(GTK_GRID(mainGrid), pos2.y, pos2.x);
    //recupérer le childGrid dans la positon pos2
    children2  =gtk_container_get_children(GTK_CONTAINER(event_box2));
    child_grid2=children2->data;

    // récupérer le bouton (pion) dans la case (childGrid) position pos1
    GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(child_grid1), 0, 0);

    // si le bouton existe dans cette case
    if (button != NULL && GTK_IS_BUTTON(button))
    {
        // Incrémenter le nombre de référence du bouton
        g_object_ref(button);
       // Enlever le bouton de la case pos1
        gtk_container_remove(GTK_CONTAINER(child_grid1), button);
        // Ajouter le bouton dans la case pos2
       container_add(GTK_CONTAINER(child_grid2), button);
        // Décrémenter le nombre de référence du bouton
        g_object_unref(button);
    }
    else
        g_print("\nNo checker in the desired case!");
 }

/**
 -Entree        : *liste du player
                  * position x et y
 -Sortie        : Pointeur sur le bouton (pion)
 -Description   : Cette fonction permet de retourner le pion du'une position donné à partir de liste player
 **/
GtkWidget *rechercher_pion_lst(pion *lst,int x, int y)
{
    pion *crt=lst;
    if(!lst)
    {
        printf("\nListe des pions vide (rechercher_pion_lst)!");
        return (GtkWidget*)NULL;
    }
    while(crt)
    {
        //si position (x,y)==position passé en argument
        if(crt->x==x && crt->y==y)
            return (GtkWidget*)crt->pion;//retourner le pion
        crt=crt->suiv;
    }
    // pion non trouvé
    return (GtkWidget*)NULL;
}

/**
 -Entree        : *liste du player
                  * grid qui contient toutes les cases
                  *position (x,y) du pion
 -Sortie        : Pointeur sur du type pion
 -Description   : Cette fonction permet de supprimer un pion de la liste player selon la position donnée
 **/
pion *supprimer_pion_lst(pion *lst,int x, int y)
{
    pion *crt,*esup;
     if(!lst)
     {
         printf("Liste des pions vide (fct supprimer_pion_lst)! ");
         return (pion*)NULL;
     }
     // si c'est au début de la liste
     if(lst->x==x && lst->y==y)
     {
         //printf("\n1supprimer_pion_lst<%d><%d>",lst->x,lst->y);
         esup=lst;
         lst=lst->suiv;
         //detruire le bouton
         gtk_widget_destroy(esup->pion);
         //libération de l'espace mémoire
         free(esup);
         return (pion*)lst;
     }
     // sinon
     crt=lst;
     while(crt->suiv)
     {
         // pion trouvé
         if(crt->suiv->x==x && crt->suiv->y==y)
         {
             esup=crt->suiv;
             crt->suiv=crt->suiv->suiv;
             //detruire le bouton
             gtk_widget_destroy(esup->pion);
            //libération de l'espace mémoire
             free(esup);
             return (pion*)lst;
         }
         crt=crt->suiv;
     }
    printf("\nPion non supprimé <%d><%d> (supprimer_pion_lst)!",x,y);
     return(pion*)lst;
}

/**
 -Entree        : *liste du player
                  * grid qui contient toutes les cases
                  *position (x,y) du pion
 -Sortie        : Pointeur sur du type pion
 -Description   : Cette fonction permet la suppression du pion selon sa position du:
                  * la liste du player
                  * la table
                  * la grid (destrucution du widget bouton)

 **/
pion *supprimer_pion(pion *lst,GtkWidget *mainGrid,int x, int y)
{
    // vérifier que la case existe
    if(case_existe(table,x,y))
    {
        //supprimer pion de la liste du player
        lst=supprimer_pion_lst(lst,x,y);
        //libérere l'espace table
        table[y][x]=0;
        return (pion*)lst;
    }
    else
        printf("\nCase n'existe pas [%d][%d] (supprimer_pion)",x,y);
        return (pion*)lst;
}

/**
 -Entree        : *liste du player
                  *position (x,y) actuelle du pion
                  *position (x,y) nouvelle du pion
 -Sortie        : Pointeur sur du type pion
 -Description   : Cette fonction permet la mise à jour de la position du pion

 **/
pion *MAJ_position_liste(pion *lst,int x, int y, int nv_x,int nv_y)
{
    pion *crt=lst;
    if(!lst)
    {
        printf("\nListe des pions vide (MAJ_position_liste)!");
        return (pion*)NULL;
    }
    while(crt)
    {
        //si pion trouvé
        if(crt->x==x && crt->y==y)
        {
            //mise à jour de sa position
            crt->x=nv_x;
            crt->y=nv_y;
            return (pion*)lst;
        }
        crt=crt->suiv;
    }
    printf("\nPion non trouvé [%d][%d] (MAJ_position_liste)! ",x,y);
    return (pion*)lst;
}

/**
 -Entree        : *liste du player
                  *position (x,y) actuelle du pion
                  *position (x,y) nouvelle du pion
 -Sortie        : Pointeur sur du type pion
 -Description   : Cette fonction permet le déplacement du pion dans la grid et la mise à jour
                de ces cordonnées dans la table et liste player

 **/
pion *deplacer_pion(pion *lst,GtkWidget *mainGrid,int x,int y,int nv_x,int nv_y)
{
    //récupérer l'état du pion dans la table
    int c=table[y][x];
    //recuperer le pion
    GtkWidget *monpion=rechercher_pion_lst(lst,x,y);
    //deplacer le pion
    position pos1={y,x}, pos2={nv_y,nv_x};
    move_checker(monpion,mainGrid,pos1,pos2);
    //Mettre à jour sa nouvelle position
    lst=MAJ_position_liste(lst,x,y,nv_x,nv_y);
    //mettre a jour la table
    table[y][x]=0; //libérer sa case ancienne
    table[nv_y][nv_x]=c;
    return (pion*)lst;
}

/**
 -Entree        : pointeur sur le widget
 -Sortie        : pointeur de type liste_wdgt
 -Description   : Cette fonction permet la création de la cellule widget et de l'initialiser

 **/
Liste_wdgt *creer_cel_wdgt(GtkWidget *wdgt)
{
    Liste_wdgt *ne;
    ne=(Liste_wdgt*)malloc(sizeof(Liste_wdgt));
    if(!ne)
    {
        g_print("\nErreur d'allocation mémoire (creer_cel_wdgt)!");
        exit(-1);
    }
    ne->widget=wdgt;
    ne->svt=NULL;
    return (Liste_wdgt*)ne;
}

/**
 -Entree        : * liste des widgets
                  * le widget
 -Sortie        : pointeur de type liste_wdgt
 -Description   : Cette fonction permet d'ajouter un widget à la liste des widgets

 **/
Liste_wdgt *ajouter_wdgt_liste(Liste_wdgt *lst,GtkWidget *wdgt)
{
    Liste_wdgt *ne=creer_cel_wdgt(wdgt);
    if(!lst)
    {
        lst=ne;
        return (Liste_wdgt*)lst;
    }
    ne->svt=lst;
    lst=ne;
    return (Liste_wdgt*)lst;
}

/**
 -Entree        : pointeur de type CheckerData
 -Sortie        : pointeur de type Liste_CheckerData
 -Description   : Cette fonction permet la création d'une cellule de type CheckerData et de
                  l'ajouter à la liste

 **/
Liste_CheckerData *creer_cel_CD(CheckerData *cd)
{
    Liste_CheckerData *ne;
    ne=(Liste_CheckerData*)malloc(sizeof(Liste_CheckerData));
    if(!ne)
    {
        g_print("\nErreur d'allocation mémoire (creer_cel_wdgt)!");
        exit(-1);
    }
    ne->CD=cd;
    ne->svt=NULL;
    return (Liste_CheckerData*)ne;
}

/**
 -Entree        : liste de type checkerData, pointeur de type CheckerData
 -Sortie        : liste de type checkerData
 -Description   : Cette fonction permet d'ajouter une CheckerData à la liste

 **/
Liste_CheckerData *ajouter_CD_liste(Liste_CheckerData *lst,CheckerData *CD)
{
    Liste_CheckerData *ne=creer_cel_CD(CD);
    if(!lst)
    {
        lst=ne;
        return (Liste_CheckerData*)lst;
    }
    ne->svt=lst;
    lst=ne;
    return (Liste_CheckerData*)lst;
}


/**
 -Entree        : * positon (x,y) du pion
                  * type du pion
 -Sortie        : pointeur de type liste_pos
 -Description   : Cette fonction permet de retourner les positons des cases valables pour déplacer pour un pion donné

 **/
void afficher_lst(pion *lst)
{
    pion *crt=lst;
    if(!lst) g_print("\nListe des pions vide (afficher_lst)!");
    else
    {
        while(crt)
        {
            g_print("\nPos:<%d><%d> type: <%d>",crt->x,crt->y,crt->type);
            crt=crt->suiv;
        }
    }
}

/**
 -Entree        : liste de type Liste_CheckerData

 -Sortie        :
 -Description   : Cette fonction l'affichage d'une liste

 **/
void afficher_lst_CD(Liste_CheckerData *lst)
{
    Liste_CheckerData *crt=lst;
    if(!lst) g_print("\nListe CheckerData vide!");
    else
    {
        printf("\nLISTE CD::");
        while(crt)
        {
            g_print("\npos: <%d><%d> type: <%d>",lst->CD->Checker->x,lst->CD->Checker->y,lst->CD->Checker->type);
            crt=crt->svt;
        }
    }
}

/**
 -Entree        : liste de type pion

 -Sortie        :
 -Description   : Cette fonction permet de retoutner la taille de la liste

 **/
int taille_pion_lst(pion *lst)
{
    pion *crt=lst;
    int taille=0;//initialisation de la taille avec
    if(!lst) return (int)taille;
    while(crt)
    {
        taille++;//incrementer la taille
        crt=crt->suiv;
    }
    return (int)taille;
}

/**
 -Entree        : liste de type chemin

 -Sortie        :
 -Description   : Cette fonction permet de retourner la taille du chemin

 **/
int taille_chemin_lst(chemin *lst)
{
    chemin *crt=lst;
    int taille=0;//initialisation de la taille avec
    if(!lst) return (int)taille;
    while(crt)
    {
        taille++;//incrementer la taille
        crt=crt->svt;
    }
    return (int)taille;
}

/**
 -Entree        : liste de type chemin

 -Sortie        :
 -Description   : Cette fonction permet de retourner le nombre de prises dans le chemin
                  passé en argument

 **/
 int nb_prises(chemin *lst)
{
    int prises=0;//initialisation de nombre de prises avec 0
    chemin *crt=lst;
    while(crt)
    {
        // si on peut manger
        if(crt->manger==TRUE) prises++;// incrementer nombre de prises
        crt=crt->svt;
    }
    return (int)prises;
}

/**
 -Entree        : arbre des chemins

 -Sortie        : un entier
 -Description   : Cette fonction permet de retourner le nombre maximal de prises parmis
                  tout les chemins de l'arbre

 **/
int max_prises(arbre_chemins *arb)
{
    int Max,Prise;
    arbre_chemins *crt;
    // arbre vide
    if(!arb) return(int)-1;
    else
    {
        //chercher le maximum
        Max=nb_prises(arb->liste_chemin);
        crt=arb->fils;
        while(crt)
        {
            Prise=nb_prises(crt->liste_chemin);
            if(Prise>=Max) Max=Prise;
            crt=crt->fils;
        }
        return(int)Max;
    }
}

///la fonction qui retourne les pions qu’on peut déplacer
/***************************************
 entreé:une liste de type pion,
        un table de deux dimension
sortie:liste des pions deplaçable
****************************************/

 pion* Liste_pion_Deplacer(pion* liste,int genre_Joueur)
{
    pion*  pions_jouables = NULL,* p = liste;
    int ip,jp,tp,k, type;

    while(p)
    {
        ip = p->x;
        jp = p->y;
        tp = p->type;

    /// Vérification de la possibilité de déplacement vers les 2 directions :

    //pion simple
    if(tp == 0)
    {
        type=0;
        //si c'est un joueur
        if(genre_Joueur==0)
        {
            //verifier que c'est un pion joueur simple dans la table
            if(table[jp][ip]==1 || table[jp][ip]==3)
            {
                k=0;
                //haut droit libre
                if(case_existe(table,ip+1,jp-1) && case_vide(table,ip+1,jp-1)) k++;

                //haut gauche libre
                if(case_existe(table,ip-1,jp-1) && case_vide(table,ip-1,jp-1)) k++;

                //haut droit occupé par adverse
                if(case_existe(table,ip+1,jp-1) && case_occupe_machine(table,ip+1,jp-1))
                {
                    if(case_existe(table,ip+2,jp-2) && case_vide(table,ip+2,jp-2)) k++;
                }

                 //haut gauche occupé par adverse
                 if(case_existe(table,ip-1,jp-1) && case_occupe_machine(table,ip-1,jp-1))
                {
                    if(case_existe(table,ip-2,jp-2) && case_vide(table,ip-2,jp-2)) k++;
                }

                 if(k!=0) //si k est different de 0
                {
                    pions_jouables = ajouter_cel_pion(pions_jouables,ip,jp,0,p->pion);
                }
            }
        }
        else
        {
            //verifier que c'est un pion machine simple dans la table
            if(table[jp][ip]==2 || table[jp][ip]==4)
            {
                k=0;
                //bas droit libre
                if(case_existe(table,ip+1,jp+1) && case_vide(table,ip+1,jp+1)) k++;

                //bas gauche libre
                if(case_existe(table,ip-1,jp+1) && case_vide(table,ip-1,jp+1)) k++;

                //bas droit occupé par adverse
                if(case_existe(table,ip+1,jp+1) && case_occupe_joueur(table,ip+1,jp+1))
                {
                    if(case_existe(table,ip+2,jp+2) && case_vide(table,ip+2,jp+2)) k++;
                }

                //bas gauche occupé par adverse
                 if(case_existe(table,ip-1,jp+1) && case_occupe_joueur(table,ip-1,jp+1))
                {
                    if(case_existe(table,ip-2,jp+2) && case_vide(table,ip-2,jp+2)) k++;
                }
            }
        }
    }
    else//pion double
    {
        type=1;
        // verifier que c'est une dame
        if(table[jp][ip]==5 || table[jp][ip]==7 || table[jp][ip]==6 || table[jp][ip]==8)
        {
            k=0;
            //haut droit libre
            if(case_existe(table,ip+1,jp-1) && case_vide(table,ip+1,jp-1)) k++;

            //haut gauche libre
            if(case_existe(table,ip-1,jp-1) && case_vide(table,ip-1,jp-1)) k++;

            //bas gauche libre
            if(case_existe(table,ip-1,jp+1) && case_vide(table,ip-1,jp+1)) k++;

            //bas droit libre
            if(case_existe(table,ip+1,jp+1) && case_vide(table,ip+1,jp+1)) k++;

            //haut droit occupé par adverse
            if(case_existe(table,ip+1,jp-1) && case_occupe_machine(table,ip+1,jp-1))
            {
                if(case_existe(table,ip+2,jp-2) && case_vide(table,ip+2,jp-2)) k++;
            }

            //haut gauche occupé par adverse
             if(case_existe(table,ip-1,jp-1) && case_occupe_machine(table,ip-1,jp-1))
            {
                if(case_existe(table,ip-2,jp-2) && case_vide(table,ip-2,jp-2)) k++;
            }
            //bas droit occupé par adverse
            if(case_existe(table,ip+1,jp+1) && case_occupe_machine(table,ip+1,jp+1))
            {
                if(case_existe(table,ip+2,jp+2) && case_vide(table,ip+2,jp+2)) k++;
            }
            //bas gauche occupé par adverse
            if(case_existe(table,ip-1,jp+1) && case_occupe_machine(table,ip-1,jp+1))
            {
                if(case_existe(table,ip-2,jp+2) && case_vide(table,ip-2,jp+2)) k++;
            }
        }
    }
    //si on peut deplacer ce pion
    if(k!=0)  pions_jouables = ajouter_cel_pion(pions_jouables,ip,jp,type,p->pion);

    p = p->suiv;
    }

    return ((pion*)pions_jouables);
}

int round = 0; // variable globale pour le tour actuelle (0: Player, 1: Machine)

/**variables golable qui pointe sur la liste des cases
(c'est obligatoire pour la possibilité de déconnecter les signals associés à ces cases)
*/
Liste_wdgt *liste_grids=NULL;

/**variables golable qui pointe sur la liste des pions
(c'est obligatoire pour la possibilité de déconnecter les signals associés à ces pions)
*/
Liste_wdgt *Liste_pions=NULL;

/**
variables golable qui pointe sur la liste des CheckerData
(c'est obligatoire pour la possibilité de libérer la mémoire occupé par les checkerData
 aprés que le tour du joueur est finit)
**/
Liste_CheckerData *liste_CD=NULL;


/**
 -Entree        : * le pointeur sur le widget
                  * la fonction signal qu'on veut la déconnecter de ce widget
 -Sortie        :
 -Description   : Cette fonction permet de déconnecter la fonction signal du widget

 **/
void disconnect_signal(GtkWidget *widget,gpointer callback_function)
{
    gulong handler_id = 0;
    //récupérer l 'id du signal
    handler_id = g_signal_handler_find(widget, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)callback_function, NULL);
    // déconnecter le signal du widget
    g_signal_handler_disconnect(widget, handler_id);
}

/**
 -Entree        : * le pointeur sur la liste des widgets
                  * la fonction signal qu'on veut la déconnecter de ces widget
 -Sortie        : pointeur de type liste_wdgt
 -Description   : Cette fonction permet de déconnecter la fonction signal de chaque widget de la liste

 **/
Liste_wdgt *disconnect_signal_widgets(Liste_wdgt *lst,gpointer callback_function)
{
    Liste_wdgt *crt=lst;
    if(!lst) return (Liste_wdgt*)NULL;
    while(crt)
    {
        //déconnecter le signal
        disconnect_signal(crt->widget,callback_function);
        //passé au suivant
        crt=crt->svt;
    }
    return (Liste_wdgt*)lst;
}

/**
 -Entree        : * le pointeur sur la liste des widgets
 -Sortie        : pointeur de type liste_wdgt
 -Description   : Cette fonction permet de détruire une liste des widgets

 **/
Liste_wdgt *detruire_wdgt_lst(Liste_wdgt *lst)
{
    Liste_wdgt *crt=lst,*esup;
    if(!lst) return (Liste_wdgt*)NULL;
    while(crt)
    {
        esup=crt;
        crt=crt->svt;
        free(esup);
    }
    return (Liste_wdgt*)NULL;
}

 /**
 -Entree        :   * le pointeur sur pointeur de la liste des pions joueurs
                    * le pointeur sur pointeur de la liste des pions machine
                    * le widget grid principal qui contient les caes
 -Sortie        :
 -Description   : Cette fonction permet de déplacer le pion selon le chemin choisit

 **/
void deplacer_selon_chemin( pion **liste_joueur,
                            pion **liste_machine,
                            GtkWidget *mainGrid,
                            arbre_chemins *arbre,
                            int pos_pion_x,int pos_pion_y,
                            int case_x,int case_y
                            )
{
    arbre_chemins *crt_arb=arbre;
    chemin *crt_chemin=NULL;
    int prise,max_prise=max_prises(arbre);
    //checher le noeud des chemins
    while(crt_arb)
    {
        prise=nb_prises(crt_arb->liste_chemin);
        if(prise== max_prise && crt_arb->liste_chemin->derniere_cel->pos.x==case_x && crt_arb->liste_chemin->derniere_cel->pos.y==case_y)
        break;
        crt_arb=crt_arb->fils;
    }
    //si chemin trouvé
    if(crt_arb)
    {
        //recuperer position actuelle du pion
        position actual_pos={pos_pion_x,pos_pion_y};
        //deplacer le pion vers la case finale
        *liste_joueur=deplacer_pion(*liste_joueur,mainGrid,pos_pion_x,pos_pion_y,crt_arb->liste_chemin->derniere_cel->pos.x,crt_arb->liste_chemin->derniere_cel->pos.y);
        // manger toutes les pion de la machines qui existe dans le chemin
        crt_chemin=crt_arb->liste_chemin;
        while(crt_chemin)
        {
            if(crt_chemin->manger==TRUE)
            {
                *liste_machine=supprimer_pion(*liste_machine,mainGrid,crt_chemin->pos.x,crt_chemin->pos.y);
            }
            crt_chemin=crt_chemin->svt;
        }
    }
    else
        g_print("\nChemin pour la case désiré est introuvé!");
}

void checker_clicked(GtkWidget *widget,gpointer user_data);


 /** fonction Signal
 -Entree        :  - pointeur sur le bouton (pion)
                   - données passé par la fonction g_signal_connect
 -Sortie        :
 -Description   :Cette fonction permet de déplacer le pion vers la case clickée
                 en prenant en considération les prises des pions d'adversaire
 **/
gboolean grid_clickee(GtkWidget *widget,GdkEventButton *event, gpointer user_data)
 {
    int i,j;
    position pos_of_clicked_grid;
    //récupérer les données passé dans la fonction g_signal_connect
    CheckerData *data = (CheckerData *)user_data;
    GtkWidget *grid=data->grid;// grid
    pion *monpion=data->Checker; // cellule pion
    pion **liste_joueur1=data->liste_joueur1; //listes des pions joueur
    pion **liste_joueur2=data->liste_joueur2;//listes des pions machine
    arbre_chemins *arbre=data->arbre;// arbre des chemins
    int typeJ=data->type_J;

    //recupérer le nom de la case
    gchar *name=gtk_widget_get_name(widget);
    //récuperer les coordonnées de la cases stockés dans nom
    sscanf(name, "grid_%d_%d", &i,&j);
    // initialiser la variable position
    pos_of_clicked_grid.x=i;
    pos_of_clicked_grid.y=j;

    //déplacer le pion vers cette case
    deplacer_selon_chemin(liste_joueur1,liste_joueur2,grid,arbre,monpion->x,monpion->y,j,i);
    //changer le pion en dame si possible
    *liste_joueur1=Is_King(*liste_joueur1,j,i);

    //déconnecter tout les signals initialement connectés à tout les pions
    Liste_pions=disconnect_signal_widgets(Liste_pions,checker_clicked);
    Liste_pions=disconnect_signal_widgets(Liste_pions,cursor_to_pointer);
    Liste_pions=disconnect_signal_widgets(Liste_pions,cursor_to_default);
    //detruire l'arbre
    arbre=detruire_arbre_chemin(arbre);
    //détruire la liste des pions
    Liste_pions=detruire_wdgt_lst(Liste_pions);
    //recolorer les cases par défaut
    set_grids_color(grid);
    //passé le tour à l'autre joueur
    if(typeJ==0)
        round=1;
    else
        round=0;
    return TRUE;
 }

  /** fonction Signal
 -Entree        :  - pointeur sur le bouton (pion)
                   - données passé par la fonction g_signal_connect
 -Sortie        :
 -Description   :Cette fonction permet de colorer les cases valables pour le pion clické
 **/
void checker_clicked(GtkWidget *widget,gpointer user_data)
{
    //récupérer les données passé à la fonction g_signal_connect
    CheckerData *data = (CheckerData *) user_data;
    GtkWidget *grid = data->grid,   *event_box,     *child_grid;
    pion *checker=data->Checker;// cellule du pion
    pion **liste_joueur1=data->liste_joueur1; // liste des pions joueurs
    pion **liste_joueur2=data->liste_joueur2; // liste des pions machine
    GList *children; // pour récupérer le contenaire
    char OV,OH; // pour déterminer orientation
    arbre_chemins *crt,*arbre=NULL;// initialiser l'arbre des chemins avec NULL
    int ind,taille, lg_taille, taille_arb, max_prise, prise, dx, dy, type_J=data->type_J;

    //recupérer tout les chemins possibles pour le pion
    arbre=prise_pion(table,checker->x,checker->y,checker->type,type_J,NULL,NULL,1,NULL,NULL);

    //recolorer les cases de la table en couleur par défaut
    set_grids_color(grid);

    /*
    Déconnecter le signal <<  on_grid_button_press  >>  et destruction de la liste qui contient ces cases
    C'est pour le cas ou il ya des cases qui sont déjà colorés précédement
    */
    liste_grids=disconnect_signal_widgets(liste_grids,grid_clickee);
    liste_grids=detruire_wdgt_lst(liste_grids);

    //**** ajout des cases de la diagonale disponibles pour le déplacement dans le cas de la dame
    if(checker->type==1)
    {
        crt=arbre;
        taille=taille_arbre_chemin(arbre);
        for(ind=0;ind<taille;ind++)
        {
            lg_taille=taille_chemin_lst(crt->liste_chemin);
            if (lg_taille == 1)
            {
                dx = crt->liste_chemin->derniere_cel->pos.x - checker->x;
                dy = crt->liste_chemin->derniere_cel->pos.y - checker->y;
            }
            else
            {
                dx = crt->liste_chemin->derniere_cel->pos.x - crt->liste_chemin->derniere_cel->pred->pos.x;
                dy = crt->liste_chemin->derniere_cel->pos.y - crt->liste_chemin->derniere_cel->pred->pos.y;
            }
            OH = (dx > 0) ? 'D' : (dx < 0) ? 'G' : OH;
            OV = (dy < 0) ? 'H' : (dy > 0) ? 'B' : OV;

            arbre=ajouter_tt_cases_diagonale(arbre,crt->liste_chemin,OV,OH);
            crt=crt->fils;
        }
    }
    //***colorer les positions des cases valables pour le déplacement
    /*
    recuperer le chemin ou il ya plus grand nombre de prises
    C'est pour la prise majoritaire!
    */
    max_prise=max_prises(arbre);

    //colorer la derniere case de chaqu'un des chemins dont le nombre de prises egale au nombre de prises maximal
    crt=arbre;
    while(crt)
    {
        prise=nb_prises(crt->liste_chemin);
        if(max_prise==prise)
        {
            //recupérer le contenaire event_box qui contient childGrid
            event_box = gtk_grid_get_child_at(GTK_GRID(grid), crt->liste_chemin->derniere_cel->pos.x,  crt->liste_chemin->derniere_cel->pos.y);
            //recupérer le childGrid
            children=gtk_container_get_children(GTK_CONTAINER(event_box));
            child_grid=children->data;
            //conneceter le signal de déplacement lorsqu'on appuie sur cette case
            data->arbre=arbre;

            g_signal_connect(event_box, "button_press_event", G_CALLBACK(grid_clickee), data);
            // ajouter cette case à la liste liste_grids (pour déconnecter ce signal après)
            liste_grids=ajouter_wdgt_liste(liste_grids,event_box);
            //colorer la case en rouge
            add_css(child_grid ,cssGridRed);
        }
        crt=crt->fils;
    }
}

/** fonction Signal
 -Entree        :  - liste du joueur
                   - grid principal qui contient toutes les cases
 -Sortie        :
 -Description   :Cette fonction permet de connecter les signals de déplacement et le déplacement
                 pour les pions valables pour le déplacement du joueur
 **/
void connecter_deplacement_des_pions(pion **liste_joueur1,
                                     pion **liste_joueur2,
                                     GtkWidget *mainGrid,
                                     int genreJ
                                     )
 {
    // recuperer la sous liste des pions valables à déplacer
    pion *s_liste=Liste_pion_Deplacer(*liste_joueur1,genreJ);
    int taille=taille_pion_lst(s_liste),// taille de la liste du pion
     i=0;// pour le parcours
    // déclaration de la variable structure CheckerData  qui contient les infos associes à un pion
    CheckerData *data[taille];
    pion *crt=s_liste;

    while(crt)
    {
        // initialisation de la variable
        data[i]=(CheckerData*) g_malloc(sizeof(CheckerData));
        data[i]->grid=mainGrid;
        data[i]->Checker=crt;
        data[i]->liste_joueur1=liste_joueur1;
        data[i]->liste_joueur2=liste_joueur2;
        data[i]->type_J=genreJ;

        //conneceter les signals et passer les infos de ce
        g_signal_connect(G_OBJECT(crt->pion), "clicked", G_CALLBACK(checker_clicked), data[i]);
        g_signal_connect(G_OBJECT(crt->pion), "enter-notify-event", G_CALLBACK(cursor_to_pointer), NULL);
        g_signal_connect(G_OBJECT(crt->pion), "leave-notify-event", G_CALLBACK(cursor_to_default), NULL);
        //ajouter ce pion à la liste Liste_pions (pour déconnecter ces signals plus tard après qu'on finit le tour)
        Liste_pions=ajouter_wdgt_liste(Liste_pions,crt->pion);
        crt=crt->suiv;
        i++;
    }
 }


 /** fonction Signal
 -Entree        :  - tableau original
                   - tableau copie
 -Sortie        :
 -Description   :Cette fonction permet de faire une copie du tabelau
 **/
void copier_tab_to_tabSimul(int tab[NbElem][NbElem], int copie[NbElem][NbElem])
{
    for (int i = 0; i < NbElem; i++)
        for (int j = 0; j < NbElem; j++)
            copie[i][j] = tab[i][j];
}

/**
 -Entree        :  - tableau du jeu
                   - Position x et y du pion
 -Sortie        : pointeur ArbMinMax
 -Description   :Cette fonction permet de crééer un noeud de type ArbMinMax
 **/
ArbMinMax *creerArbMM(int tab[NbElem][NbElem],int x,int y)
{
    ArbMinMax *nd;
    nd=(ArbMinMax*)malloc(sizeof(ArbMinMax));
    if(!nd)
    {
        printf("\nErreur Allocation mémoire (ArbMinMax)!");
        exit(-1);
    }
    copier_tab_to_tabSimul(tab,nd->tab_simulation);
    nd->score=-INFINITY;
    nd->lst=NULL;
    nd->fils=nd->frere=NULL;
    nd->pos.x=x;
    nd->pos.y=y;
    return(ArbMinMax*)nd;
}

void afficherArbMinMax(ArbMinMax *arb,int niv)
{
    ArbMinMax *crt;
    int i=0;
    if(arb)
    {
        if(arb->fils) afficherArbMinMax(arb->fils,niv+1);
        crt=arb;
        printf("\n\n\n********************NIVEAU = %d****************\n",niv);
        while(crt)
        {
            printf("\n\t\tNOEUD %d:\n",i);
            printf("\nLISTE:");
            afficher_chemin(crt->lst);
            printf("\nMATRICE:\n");
            afficher_matrice(crt->tab_simulation);
            printf("\nSCORE = %.2f",crt->score);
            crt=crt->frere;
            i++;
        }
    }
}

int nb_pion_joueur1(int table[NbElem][NbElem])
{
    int i,j,nb=0;
    for(i=0;i<NbElem;i++)
    {
        for(j=0;j<NbElem;j++)
            if(table[i][j]==1 || table[i][j]==3) nb++;
    }
    return(int)nb;
}

int nb_pion_joueur2(int table[NbElem][NbElem])
{
    int i,j,nb=0;
    for(i=0;i<NbElem;i++)
    {
        for(j=0;j<NbElem;j++)
            if(table[i][j]==2 || table[i][j]==4) nb++;
    }
    return(int)nb;
}

int nb_king_joueur1(int table[NbElem][NbElem])
{
    int i,j,nb=0;
    for(i=0;i<NbElem;i++)
    {
        for(j=0;j<NbElem;j++)
            if(table[i][j]==5 || table[i][j]==7) nb++;
    }
    return(int)nb;
}

int nb_king_joueur2(int table[NbElem][NbElem])
{
    int i,j,nb=0;
    for(i=0;i<NbElem;i++)
    {
        for(j=0;j<NbElem;j++)
            if(table[i][j]==6 || table[i][j]==8) nb++;
    }
    return(int)nb;
}

/**
 -Entree        :  - tableau du jeu
                   - Genre du joueur 0: Joueur1
                                     1: Joueur2
 -Sortie        : Liste de type pion
 -Description   :Cette fonction permet de retourer les pions valables pour le déplacement pour un joueur donné
 **/
pion* liste_pion_Deplacer_table(int table[NbElem][NbElem],int genre_Joueur)
{
    pion*  pions_jouables = NULL;
    int ip,jp,tp,k, type,i,j;

    for(jp=0;jp<NbElem;jp++)
    {
        for(ip=0;ip<NbElem;ip++)
        {
            if(genre_Joueur==0)
            {
                if(table[jp][ip]==1 || table[jp][ip]==3)
                {
                    k=0;
                    //haut droit libre
                    if(case_existe(table,ip+1,jp-1) && case_vide(table,ip+1,jp-1)) k++;

                    //haut gauche libre
                    if(case_existe(table,ip-1,jp-1) && case_vide(table,ip-1,jp-1)) k++;

                    //haut droit occupé par adverse
                    if(case_existe(table,ip+1,jp-1) && case_occupe_machine(table,ip+1,jp-1))
                    {
                        if(case_existe(table,ip+2,jp-2) && case_vide(table,ip+2,jp-2)) k++;
                    }

                    //haut gauche occupé par adverse
                    if(case_existe(table,ip-1,jp-1) && case_occupe_machine(table,ip-1,jp-1))
                    {
                        if(case_existe(table,ip-2,jp-2) && case_vide(table,ip-2,jp-2)) k++;
                    }

                    if(k!=0) //si k est different de 0
                    {
                          pions_jouables = ajouter_cel_pion(pions_jouables,ip,jp,0,NULL);
                    }
                }
                else if(table[jp][ip]==5 || table[jp][ip]==7)
                {
                    k=0;
                    //haut droit libre
                    if(case_existe(table,ip+1,jp-1) && case_vide(table,ip+1,jp-1)) k++;

                     //haut gauche libre
                    if(case_existe(table,ip-1,jp-1) && case_vide(table,ip-1,jp-1)) k++;

                    //bas gauche libre
                    if(case_existe(table,ip-1,jp+1) && case_vide(table,ip-1,jp+1)) k++;

                    //bas droit libre
                    if(case_existe(table,ip+1,jp+1) && case_vide(table,ip+1,jp+1)) k++;

                    //haut droit occupé par adverse
                    if(case_existe(table,ip+1,jp-1) && case_occupe_machine(table,ip+1,jp-1))
                    {
                        if(case_existe(table,ip+2,jp-2) && case_vide(table,ip+2,jp-2)) k++;
                    }

                    //haut gauche occupé par adverse
                    if(case_existe(table,ip-1,jp-1) && case_occupe_machine(table,ip-1,jp-1))
                    {
                        if(case_existe(table,ip-2,jp-2) && case_vide(table,ip-2,jp-2)) k++;
                    }
                    //bas droit occupé par adverse
                    if(case_existe(table,ip+1,jp+1) && case_occupe_machine(table,ip+1,jp+1))
                    {
                        if(case_existe(table,ip+2,jp+2) && case_vide(table,ip+2,jp+2)) k++;
                    }
                    //bas gauche occupé par adverse
                    if(case_existe(table,ip-1,jp+1) && case_occupe_machine(table,ip-1,jp+1))
                    {
                        if(case_existe(table,ip-2,jp+2) && case_vide(table,ip-2,jp+2)) k++;
                    }
                    if(k!=0) //si k est different de 0
                    {
                        pions_jouables = ajouter_cel_pion(pions_jouables,ip,jp,1,NULL);
                    }
                }
        }
        else
        {
                if(table[jp][ip]==2 || table[jp][ip]==4)
                {
                    k=0;
                    //haut droit libre
                    if(case_existe(table,ip+1,jp+1) && case_vide(table,ip+1,jp+1)) k++;

                    //haut gauche libre
                    if(case_existe(table,ip-1,jp+1) && case_vide(table,ip-1,jp+1)) k++;

                    //haut droit occupé par adverse
                    if(case_existe(table,ip+1,jp+1) && case_occupe_joueur(table,ip+1,jp+1))
                    {
                        if(case_existe(table,ip+2,jp+2) && case_vide(table,ip+2,jp+2)) k++;
                    }

                    //haut gauche occupé par adverse
                    if(case_existe(table,ip-1,jp+1) && case_occupe_joueur(table,ip-1,jp+1))
                    {
                        if(case_existe(table,ip-2,jp+2) && case_vide(table,ip-2,jp+2)) k++;
                    }

                    if(k!=0) //si k est different de 0
                    {
                          pions_jouables = ajouter_cel_pion(pions_jouables,ip,jp,0,NULL);
                    }
                }
                else if(table[jp][ip]==6 || table[jp][ip]==8)
                {
                    k=0;
                    //haut droit libre
                    if(case_existe(table,ip+1,jp-1) && case_vide(table,ip+1,jp-1)) k++;

                     //haut gauche libre
                    if(case_existe(table,ip-1,jp-1) && case_vide(table,ip-1,jp-1)) k++;

                    //bas gauche libre
                    if(case_existe(table,ip-1,jp+1) && case_vide(table,ip-1,jp+1)) k++;

                    //bas droit libre
                    if(case_existe(table,ip+1,jp+1) && case_vide(table,ip+1,jp+1)) k++;

                    //haut droit occupé par adverse
                    if(case_existe(table,ip+1,jp-1) && case_occupe_joueur(table,ip+1,jp-1))
                    {
                        if(case_existe(table,ip+2,jp-2) && case_vide(table,ip+2,jp-2)) k++;
                    }

                    //haut gauche occupé par adverse
                    if(case_existe(table,ip-1,jp-1) && case_occupe_joueur(table,ip-1,jp-1))
                    {
                        if(case_existe(table,ip-2,jp-2) && case_vide(table,ip-2,jp-2)) k++;
                    }
                    //bas droit occupé par adverse
                    if(case_existe(table,ip+1,jp+1) && case_occupe_joueur(table,ip+1,jp+1))
                    {
                        if(case_existe(table,ip+2,jp+2) && case_vide(table,ip+2,jp+2)) k++;
                    }
                    //bas gauche occupé par adverse
                    if(case_existe(table,ip-1,jp+1) && case_occupe_joueur(table,ip-1,jp+1))
                    {
                        if(case_existe(table,ip-2,jp+2) && case_vide(table,ip-2,jp+2)) k++;
                    }
                    if(k!=0) //si k est different de 0
                    {
                        pions_jouables = ajouter_cel_pion(pions_jouables,ip,jp,1,NULL);
                    }
                }
        }
      }
    }

    return ((pion*)pions_jouables);
}

/**
 -Entree        :  - tableau de simulation
                   - liste du déplacement
                   - Position du pion X et Y
 -Sortie        :
 -Description   :Cette fonction permet de simuler le déplacement pour un pion donné
 **/
void simuler_Dep(int tab[NbElem][NbElem],chemin *lst,int x,int y)
{
    chemin *crt=lst;
    int current;
    //mémoriser l'indice du pion dans la table
    current=tab[y][x];
    tab[y][x]=0;
    //véridier si le pion arrive en extrémité et le changer en Dame
    if( (current==1 || current==3) && lst->derniere_cel->pos.y==0) current+=4;
    if( (current==2 || current==4) && lst->derniere_cel->pos.y==9) current+=4;
    tab[lst->derniere_cel->pos.y][lst->derniere_cel->pos.x]=current;
    //enlever les pions mangé de la table
    while(crt)
    {
        if(crt->manger==TRUE) tab[crt->pos.y][crt->pos.x]=0;
        crt=crt->svt;
    }
}

/** fonction Signal
 -Entree        :  - tableau de simulation
                   - Booléan qui répresente Maximisation ou minimisation dun score
 -Sortie        :
 -Description   :Cette fonction permet de retourner le score selon le joueur
 **/
float score(int tab[NbElem][NbElem],int genreJ)
{
    int nb1,nb2,nb3,nb4;
    nb1=nb_pion_joueur1(tab);
    nb2=nb_pion_joueur2(tab);
    nb3=nb_king_joueur1(tab);
    nb4=nb_king_joueur2(tab);
    if(genreJ==1)
        return (float)(nb2-nb1)+(0.5*nb4 - 0.5*nb3);
    else
        return (float)(nb1-nb2)+(0.5*nb3 - 0.5*nb4);
}

/**
 -Entree        :  - racine
                   - Position x et y du pion
                   - Type du pion
                   - Type du joueur
                   - Profondeur
                   - Booléan qui represente Maximiser==True ou Minimiser==False
                   - entier qui représente: 0 cad on fait appel de cette fonction en premier
                                            1 sinon

 -Sortie        :
 -Description   :Cette fonction permet de construire l'arbre de simulation pour un pion
 **/
ArbMinMax* get_Arb_MiniMax(ArbMinMax* arbre, int x, int y, int type_pion,int typeJ, int depth, bool maximize, int premier_appel)
{
    ArbMinMax* crt;             // pour parcourir l'arbre
    int maxPrise, prise;        // pour stocker nombre de prise dans un chemin
    float bestScore = -INFINITY;// initialisation du score
    int t;

    //si premier appel de cette fonction
    if (premier_appel == 1)
    {
        //construire l'arbre de touts les chemins possibles pour ce pion
        arbre_chemins* arb = prise_pion(arbre->tab_simulation, x, y, type_pion,typeJ, NULL, NULL, 1, NULL, NULL), *crt_arb;
        maxPrise = max_prises(arb);
        crt_arb = arb;

        //recuperer seulement le chemin ou il ya la prise obligatoire
        while (crt_arb)
        {
            prise = nb_prises(crt_arb->liste_chemin);

            if (prise == maxPrise)
            {
                ArbMinMax* nd = creerArbMM(arbre->tab_simulation,x,y);
                nd->lst = copier_chemin(crt_arb->liste_chemin);
                simuler_Dep(nd->tab_simulation, nd->lst, x, y);
                nd->score = score(nd->tab_simulation,typeJ);

                //ajouter le noeud à l'arbre de simulation
                if (!arbre->fils)
                {
                    arbre->fils = nd;
                }
                else
                {
                    crt = arbre->fils;
                    while (crt->frere)
                        crt = crt->frere;
                    crt->frere = nd;
                }

                //passer à la profendeur suivante
                nd = get_Arb_MiniMax(nd, NULL, NULL, NULL,typeJ, depth - 1, maximize, 0);
            }

            crt_arb = crt_arb->fils;
        }
        //destruction de l'arbre
        arb = detruire_arbre_chemin(arb);
        return arbre;
    }
    else
    {
        int nbPJ1=nb_pion_joueur1(arbre->tab_simulation);
        int nbKJ1=nb_king_joueur1(arbre->tab_simulation);
        int nbPJ2=nb_pion_joueur2(arbre->tab_simulation);
        int nbKJ2=nb_king_joueur2(arbre->tab_simulation);
        // si le jeu est finir pas la peine de continuer
        if(nbPJ1==0 && nbKJ1==0)
        {
            return arbre;
        }
        if(nbPJ2=0 && nbKJ2==0)
        {
            return arbre;
        }
        // si la profondeur == 0 on arrete
        if (depth == 0)
        {
            arbre->score = score(arbre->tab_simulation,maximize);
            return arbre;
        }
        // determiner le sens du mouvement des pions selon le type du joueur et aussi selon maximisation
        if(typeJ==0)
        {
            if(maximize==true) t=0;
            else t=1;
        }
        else
        {
            if(maximize==true) t=1;
            else t=0;
        }

        pion* crt_p;
        //liste des pion valables à deplacer
        pion* list_dep = liste_pion_Deplacer_table(arbre->tab_simulation, t);
        crt_p = list_dep;
        arbre_chemins *crt_arb;

        //si on maximise le score pour gagner
        if (maximize == true)
        {

            while (crt_p)
            {
                arbre_chemins* arb = prise_pion(arbre->tab_simulation, crt_p->x, crt_p->y, crt_p->type,t, NULL, NULL, 1, NULL, NULL);
                maxPrise = max_prises(arb);
                crt_arb = arb;

                while (crt_arb)
                {
                    prise = nb_prises(crt_arb->liste_chemin);

                    if (prise == maxPrise)
                    {
                        ArbMinMax* nd = creerArbMM(arbre->tab_simulation,crt_p->x, crt_p->y);
                        nd->lst = crt_arb->liste_chemin;
                        simuler_Dep(nd->tab_simulation, nd->lst, crt_p->x, crt_p->y);
                        nd->score = score(nd->tab_simulation,typeJ);
                       // if(nd->score>bestScore) bestScore=nd->score;

                        if (!arbre->fils)
                        {
                            arbre->fils = nd;
                        }
                        else
                        {
                            crt = arbre->fils;
                            while (crt->frere)
                                crt = crt->frere;
                            crt->frere = nd;
                        }

                        nd = get_Arb_MiniMax(nd, crt_p->x, crt_p->y, crt_p->type,typeJ, depth - 1, false, 0);
                    }

                    crt_arb = crt_arb->fils;
                }

                arb = detruire_arbre_chemin(arb);
                crt_p = crt_p->suiv;
            }
            list_dep=detruire_liste_pions(list_dep);

            return arbre;
        }
        else
        {

            while (crt_p)
            {
                arbre_chemins* arb = prise_pion(arbre->tab_simulation, crt_p->x, crt_p->y, crt_p->type, t, NULL, NULL, 1, NULL, NULL);
                maxPrise = max_prises(arb);
                crt_arb = arb;

                while (crt_arb)
                {
                    prise = nb_prises(crt_arb->liste_chemin);

                    if (prise == maxPrise)
                    {
                        ArbMinMax* nd = creerArbMM(arbre->tab_simulation,crt_p->x, crt_p->y);
                        nd->lst = crt_arb->liste_chemin;
                        simuler_Dep(nd->tab_simulation, nd->lst, crt_p->x, crt_p->y);
                        nd->score = score(nd->tab_simulation,!typeJ);


                        if (!arbre->fils)
                        {
                            arbre->fils = nd;
                        }
                        else
                        {
                            crt = arbre->fils;
                            while (crt->frere)
                                crt = crt->frere;
                            crt->frere = nd;
                        }

                       nd = get_Arb_MiniMax(nd, crt_p->x, crt_p->y, crt_p->type,typeJ,depth - 1, true, 0);
                    }

                    crt_arb = crt_arb->fils;
                }

                arb = detruire_arbre_chemin(arb);
                crt_p = crt_p->suiv;
            }

            list_dep=detruire_liste_pions(list_dep);

            return arbre;
        }
    }
}

void detruire_arbre_minmax(ArbMinMax *arbre) {
    if (arbre == NULL)
        return;

   // printf(" %p\n", (void *)arbre);

    detruire_arbre_minmax(arbre->fils);
    detruire_arbre_minmax(arbre->frere);

    printf("%p\n", (void *)arbre);
    //arbre->lst = detruire_liste_chemin(arbre->lst);

    printf(": %p\n", (void *)arbre);
    free(arbre);
}

/**
 -Entree        :  - racine
                   - Booléan qui represente Maximiser==True ou Minimiser==False

 -Sortie        : pointeur de type ArbMinMax
 -Description   :Cette fonction permet de déterminer le score dans une arbre et le stocker dans la racine
                pour faire ensuite la décision
 **/
ArbMinMax* getScore(ArbMinMax* arb, bool maximize)
{
    ArbMinMax* crt;
    float bestscore = maximize ? -INFINITY : INFINITY;

    if(!arb->fils) return arb;
    if (arb->fils)
    {
        crt = arb->fils;
        while (crt)
        {
            crt = getScore(crt, !maximize);

            if (maximize)
            {
                if (bestscore < crt->score)
                    bestscore = crt->score;
            }
            else
            {
                if (bestscore > crt->score)
                    bestscore = crt->score;
            }

            crt = crt->frere;
        }

        arb->score = bestscore;
    }

    return arb;
}

 /**
 -Entree        : * scroll window
 -Sortie        : Pointeur sur structure GameData
 -Description   :Cette fonction permet de faire l'initialisation du jeu:
                 -> initialisation du board (allocation mémoire et coloration du board)
                 -> placement des pions dans le borad,
                 -> initialisation des players(machine et joueur) selon le choix de couleur du joueur,
                 et retourne la structure du joueur, de la machine et la grid qui contient les pions
 **/

Game *create_checkersBoard(scroll_wind scrol,char couleur,gdouble difficulte,int mode)
{
    Player *Joueur1,*Joueur2;
    Align align; align.x=0.5,align.y=0.5;
	Grid *grid,                             // grid princiapl qui contient les cases (board)
         *child[NbElem][NbElem];            //les cases (10x10)
	GtkEventBox *event_box[NbElem][NbElem];/* contenaire de type eventbox pour mettre child  (la case) dedans
	                                          afin de permettre connecter les signals au child (la case)
                                            */
	int indi, indj;// variables de parcours
    Game *game=(Game*)malloc(sizeof(Game));
    if(!game)
    {
        printf("Erreur d'allocation memoire pour Game!");
        exit(-1);
    }


	//initialisation de la matrice du jeu de Dames
	initialisation_matrice(table);


    ///initialisation le choix du joueur
	if(couleur=='B')
    {
        round=0;
        game->couleurJ  =    'B';
        game->couleurM  =    'N';
        Joueur1=Creer_joueur('B','J');
        Joueur2=Creer_joueur('N','M');
    }
    else
    {
        round=1;
        game->couleurJ  =   'N';
        game->couleurM  =   'B';
        Joueur1=Creer_joueur('N','J');
        Joueur2=Creer_joueur('B','M');
    }
    game->choix=mode;
    game->diff=(int)difficulte;
    printf("******************************************************DIFFICULTE = %d",game->diff);



    /// initialisation et creation de la grid principal
	grid = initialiser_Grid(NULL, "grid", TRUE, TRUE, 0, 0, 0, 0, 0, 0, 0);
	grid = create_Grid(grid);
	add_css(grid->grid, cssGrid);

	/// centrer la grid dans la fenetre
    align.align=centrer_widget(grid->grid,align.x,align.y);
	container_add(scrol.scrolled_window,align.align);

	///Initialistation de la grid
	for (indi = 0; indi < 10; indi++)
	{
		for (indj = 0; indj < 10; indj++)
		{
		    //nom pour childGrid
		    gchar *name=g_strdup_printf("grid_%d_%d",indi,indj);
		    //initialiser et creer childGrid
			child[indi][indj] = initialiser_Grid(NULL,NULL, TRUE, TRUE, 0, 0, 0, 60, 60, 0, 0);
			child[indi][indj] = create_Grid(child[indi][indj]);
			//initialiser event box pour recuperer les signals associé à childGrid
            event_box[indi][indj] = gtk_event_box_new();
            gtk_widget_set_name(event_box[indi][indj],name);
            //ajouter childGrid à event_box
			container_add(GTK_CONTAINER(event_box[indi][indj]), child[indi][indj]->grid);
			//ajouter event_box à la main Grid
			gtk_grid_attach(GTK_GRID(grid->grid), event_box[indi][indj], indj, indi, 1, 1);
			free(name);

			if (indi % 2 == 0)
			{
				if (indj % 2 == 0)
				{
					add_css(child[indi][indj]->grid,cssGridWhite);
				}
				else
				{
					add_css(child[indi][indj]->grid, cssGridBrown);
				}
			}
			else
			{
				if (indj % 2 == 0)
				{
					add_css(child[indi][indj]->grid, cssGridBrown);
				}
				else
				{
					add_css(child[indi][indj]->grid, cssGridWhite);
				}
			}
		}
	}

	///Colorer les pions et et remplissage de la table selon le choix du joueur
	///initialisation pions machine
    for(indi=0;indi<4;indi++)
        {
            for(indj=0;indj<10;indj++)
            {
                //initialisation et création du bouton qui représente le pion
                bouton *butt=initialiser_Bouton(1,NULL,NULL,NULL,NULL,NULL,0,NULL,60,60,0,0);
                butt=create_simpleButton(butt);
                if(indi%2==0 && indj%2!=0)
                {
                    //ajouter le pion dans la case convenable
                    container_add(child[indi][indj]->grid,butt->button);
                    //insertion du pion dans la liste des pions de la machine
                    Joueur2->liste=ajouter_cel_pion(Joueur2->liste,indj,indi,0,butt->button);
                    //changer le code dans la matrice
                    if(couleur=='B')
                    {
                        table[indi][indj]=4;
                        //affecter couleur convenable
                        add_css(butt->button,cssPionBlack);
                    }
                    else
                    {
                        table[indi][indj]=2;
                        //affecter couleur convenable
                        add_css(butt->button,cssPionBeige);
                    }
                }
                else if(indi%2!=0 && indj%2==0)
                {
                    //ajouter le pion dans la case convenable
                    container_add(child[indi][indj]->grid,butt->button);
                    //insertion du pion dans la liste des pions de la machine
                    Joueur2->liste=ajouter_cel_pion(Joueur2->liste,indj,indi,0,butt->button);
                    if(couleur=='B')
                    {
                        //changer le code dans la matrice
                        table[indi][indj]=4;
                        add_css(butt->button,cssPionBlack);
                    }
                    else
                    {
                        table[indi][indj]=2;
                        //affecter couleur convenable
                        add_css(butt->button,cssPionBeige);
                    }
                }
            }
        }
        ///initialisation pions joueur
        for(indi=6;indi<10;indi++)
        {
            for(indj=0;indj<10;indj++)
            {
                //initialisation et création du bouton qui représente le pion
                bouton *butt=initialiser_Bouton(1,NULL,NULL,NULL,NULL,NULL,0,NULL,60,60,0,0);
                butt=create_simpleButton(butt);
                if(indi%2!=0 && indj%2==0)
                {
                    //ajouter le pion dans la case convenable
                    container_add(child[indi][indj]->grid,butt->button);
                    //insertion du pion dans la liste des joueurs
                    Joueur1->liste=ajouter_cel_pion(Joueur1->liste,indj,indi,0,butt->button);
                    //changer le code dans la matrice
                    if(couleur=='B')
                    {
                        table[indi][indj]=1;
                        //affecter couleur convenable
                        add_css(butt->button,cssPionBeige);

                    }
                    else
                    {
                         table[indi][indj]=3;
                         //affecter couleur convenable
                        add_css(butt->button,cssPionBlack);
                    }
                }
                else if(indi%2==0 && indj%2!=0)
                {
                    container_add(child[indi][indj]->grid,butt->button);
                    Joueur1->liste=ajouter_cel_pion(Joueur1->liste,indj,indi,0,butt->button);
                    if(couleur=='B')
                    {
                        table[indi][indj]=1;
                        //affecter couleur convenable
                        add_css(butt->button,cssPionBeige);
                    }
                    else
                    {
                        table[indi][indj]=3;
                        //affecter couleur convenable
                        add_css(butt->button,cssPionBlack);
                    }
                }
            }
        }

    game->Joueur1=Joueur1;
    game->Joueur2=Joueur2;
    game->grid=grid->grid;
    return (Game*)game;

}

/**
 -Entree        :  - Liste des pions Joueur 1
                   - Liste des pions Joueur 2
 -Sortie        : 0: jeu pas encore terminé
                  1: Joueur 1 a perdu
                  2: Joueur 2 a perdu
 -Description   :Cette fonction permet de déterminer si le jeu est terminé ou non
                pour faire ensuite la décision
 **/
int game_over(pion *listeJ, pion *listeM)
{
    pion *sous_listeM=NULL,*sous_listeJ=NULL;
    sous_listeM=Liste_pion_Deplacer(listeM,1);
    sous_listeJ=Liste_pion_Deplacer(listeJ,0);
    if(!sous_listeJ || !listeJ)
    {
        sous_listeJ=detruire_liste_pions(sous_listeJ);
        sous_listeM=detruire_liste_pions(sous_listeM);
        return(int) 1;
    }
    else if(!sous_listeM || !listeM)
    {
        sous_listeJ=detruire_liste_pions(sous_listeJ);
        sous_listeM=detruire_liste_pions(sous_listeM);
        return(int) 2;
    }
    else
    {
        sous_listeJ=detruire_liste_pions(sous_listeJ);
        sous_listeM=detruire_liste_pions(sous_listeM);
        return(int)0;
    }
}

/** fonction Signal
    fonction qui fait le tour entre les deux joueurs
 **/
gboolean tour_signal(gpointer data)
{
    Game *game=(Game*) data;
    int gameover=game_over(game->Joueur1->liste,game->Joueur2->liste);
    int J1=0,J2=1;

    // si jeu est terminé
    if (gameover!=0)
    {
        gtk_widget_hide(game->window);

        Wind gameOver;

        init_window(&gameOver,"Jeu de Dame","images/icon.png",cssWindowGameOver,400,400,GTK_WINDOW_TOPLEVEL,GTK_WIN_POS_CENTER);
        gameOver.window=create_window(gameOver,NULL);
        // Create a label widget
        GtkWidget *label;

        if(gameover==2)
        {
            switch(game->choix)
            {
            case 1:
                label= gtk_label_new("Joueur 1 a gagne!");
                break;
            case 2:
                label= gtk_label_new("Vous avez a gagne!");
                break;
            case 3:
                label= gtk_label_new("Machine 1 a gagne!");
                break;
            }
            add_css(label,YouWin);
        }
        else
        {
            switch(game->choix)
            {
            case 1: label= gtk_label_new("Joueur 2 a gagne!");
                    break;
            case 2: label= gtk_label_new("Vous avez a perdu!");
                    break;
            case 3: label= gtk_label_new("Machine 2 a gagne!");
                    break;
            }
            add_css(label,YouLose);
        }
        container_add(GTK_CONTAINER(gameOver.window), label);
        gtk_widget_show_all(gameOver.window);
        return FALSE;
    }

     // si c'est le tour du joueur
    if (round == 0)
    {
        if(game->choix==1 || game->choix==2)
        {
            g_print("\n*********\tPLAYER ROUND\t*********\n");

            /* appler à la fonction qui permet au jouer faire sans mouvement
            ( au sein se la fonction lorsque le joueur fait son mouvement la variable < isPlayerMoveComplete >
             est changé à < true >)
             */
            connecter_deplacement_des_pions(&(game->Joueur1->liste),&(game->Joueur2->liste),game->grid,J1);

        }
        else
        {
                g_print("\n*********\tMACHINE ROUND\t*********\n\n");

                pion *sous_liste=Liste_pion_Deplacer(game->Joueur1->liste,J1),*crt;
                int taille=taille_pion_lst(sous_liste), i;
                float maxscore = -INFINITY, score;

                ArbMinMax *arb[taille], *maxscore_arb = NULL;
                crt = sous_liste;

                for(i=0;i<taille;i++)
                {
                    arb[i]=creerArbMM(table,crt->x,crt->y);
                    arb[i]=get_Arb_MiniMax(arb[i],crt->x,crt->y,crt->type,J1,game->diff,true,1);

                    arb[i]=getScore(arb[i],true);
                    score=arb[i]->score;
                    //printf("\nPION [%d][%d]  SCORE = %f\n",arb[i]->pos.x,arb[i]->pos.y,arb[i]->score);

                    if (score > maxscore)
                    {
                        maxscore = score;
                        maxscore_arb = arb[i];
                    }

                    crt=crt->suiv;
                }

                 ArbMinMax *crtArb = maxscore_arb->fils;

                while (crtArb)
                {
                    if (crtArb->score == maxscore )   break;
                    crtArb = crtArb->frere;
                }


                // deplacer le pion choisit qui a le maximum du score
                 deplacer_pion(game->Joueur1->liste,game->grid,crtArb->pos.x,crtArb->pos.y,crtArb->lst->derniere_cel->pos.x,crtArb->lst->derniere_cel->pos.y);
                 // le changer en dame si possible
                 game->Joueur1->liste=Is_King(game->Joueur1->liste,crtArb->lst->derniere_cel->pos.x,crtArb->lst->derniere_cel->pos.y);
                 chemin *crt_chemin=crtArb->lst;
                 //manger les pions dans le chemin s'ils existent
                 while(crt_chemin)
                {
                    if(crt_chemin->manger==TRUE)
                    {
                        game->Joueur2->liste=supprimer_pion(game->Joueur2->liste,game->grid,crt_chemin->pos.x,crt_chemin->pos.y);
                    }
                    crt_chemin=crt_chemin->svt;
                }
                //destruction de la liste des pions et l'arbre de décision
                sous_liste=detruire_liste_pions(sous_liste);
                for(i=0;i<taille;i++)
                {
                    printf("DETRUIRE %d\n",i);
                    detruire_arbre_minmax(arb[i]);
                }
                //passer le tour à l'autre joeur
                round = 1;
                if(game->choix==3) g_timeout_add_seconds(20, tour_signal, game);
                else tour_signal(game);
            }
    }
    else // si c'est le tour du joueur
    {
        if(game->choix==1)
        {
            g_print("\n*********\tPLAYER ROUND2\t*********\n");

            /* appler à la fonction qui permet au jouer faire sans mouvement
            ( au sein se la fonction lorsque le joueur fait son mouvement la variable < isPlayerMoveComplete >
             est changé à < true >)
             */
            connecter_deplacement_des_pions(&(game->Joueur2->liste),&(game->Joueur1->liste),game->grid,J2);
        }
        else if(game->choix==2 || game->choix==3)
        {
            g_print("\n*********\tMACHINE ROUND\t*********\n\n");

            pion *sous_liste=Liste_pion_Deplacer(game->Joueur2->liste,J2),*crt;
            int taille=taille_pion_lst(sous_liste) ,i;
            float maxscore = -INFINITY, score;
            ArbMinMax *arb[taille], *maxscore_arb = NULL;;
            crt = sous_liste;

            for(i=0;i<taille;i++)
            {
                arb[i]=creerArbMM(table,crt->x,crt->y);
                arb[i]=get_Arb_MiniMax(arb[i],crt->x,crt->y,crt->type,J2,game->diff,true,1);
                arb[i]=getScore(arb[i],true);
                score=arb[i]->score;
               // printf("\nPION [%d][%d]  SCORE = %f\n",arb[i]->pos.x,arb[i]->pos.y,arb[i]->score);

                if (score > maxscore)
                {
                    maxscore = score;
                    maxscore_arb = arb[i];
                }

                crt=crt->suiv;
            }

             ArbMinMax *crtArb = maxscore_arb->fils;

            while (crtArb)
            {
                if (crtArb->score == maxscore ) break;
                crtArb = crtArb->frere;
            }


             deplacer_pion(game->Joueur2->liste,game->grid,crtArb->pos.x,crtArb->pos.y,crtArb->lst->derniere_cel->pos.x,crtArb->lst->derniere_cel->pos.y);
             game->Joueur2->liste=Is_King(game->Joueur2->liste,crtArb->lst->derniere_cel->pos.x,crtArb->lst->derniere_cel->pos.y);
             chemin *crt_chemin=crtArb->lst;
             while(crt_chemin)
            {
                if(crt_chemin->manger==TRUE)
                {
                    game->Joueur1->liste=supprimer_pion(game->Joueur1->liste,game->grid,crt_chemin->pos.x,crt_chemin->pos.y);
                }
                crt_chemin=crt_chemin->svt;
            }
            sous_liste=detruire_liste_pions(sous_liste);
            for(i=0;i<taille;i++)
            {
                printf("DETRUIRE %d\n",i);
                detruire_arbre_minmax(arb[i]);
            }
            //passer le tour à l'autre joueur

            round = 0;
            if(game->choix==3) g_timeout_add_seconds(20, tour_signal, game);
            else tour_signal(game);
        }
    }

    return TRUE;
}

#endif // GAME_H_INCLUDED
