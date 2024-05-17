#ifndef MACROSGTK_H_INCLUDED
#define MACROSGTK_H_INCLUDED
#include <gtk/gtk.h>
#define MAX_LENGTH1 8

/**==============================================================================================================================**/
/**===========================================================Structures=========================================================**/
/**==============================================================================================================================**/

/**
 * Structure de la position et de la dimension d'un Widget
**/
typedef struct
{
    gint x;//abscisse
    gint y;//ordonne
}position,dimension;

/**
 * Structure de tout les types des boutons
**/
typedef struct Button
{
    GtkWidget *button; // le widget bouton
    GtkWidget *pere; // le conteneur
    GtkWidget *membre_grp;// membre du gorupe pour le bouton radio
    gint type;/* * 1: simple
                 * 2: checkbox
                 * 3: radio
                 * 4: toggle
             */
    gchar *label; // label
    gchar *nom; // nom
    gint mnemonic ; // mnemonic
    const gchar *stock_id;//pour bouton du stock
    gchar *image; // image
    dimension *dim;// dimension
    position *pos;// position
}bouton;

/**
 * Structure de Widget GTK_BOX
**/
typedef struct
{
    GtkWidget *box; /// le widget box
    GtkWidget *pere; /// le conteneur dont on va métre le box
    gchar type; /** type: * H :horizontal
                          * V :vertical
                **/
    gchar *nom; /// nom
    gboolean homogene; /// l'homogénéité des fils du box (TRUE or FALSE)
    gint spacing; /// nombre de pixels entre les fils du box
    guint bord;/// bordure
    dimension *dim; ///dimension du box
    position *pos;/// position
}Box;

/**
 * Structure de Widget GTK_GRID
**/
typedef struct
{
    GtkWidget *grid; // le widget Grid
    GtkWidget *pere; // le conteneur
    gchar *nom; // nom
    gboolean homogene_Lg; // l'homogénéité des lignes de la grid
    gboolean homogene_Col; // l'homogénéité des colonnes de la grid
    gint spacing_Lg; // nombre de pixels entre les lignes de la grid
    gint spacing_Col; // nombre de pixels entre les colonnes de la grid
    guint bord;// bordure
    dimension *dim; //dimension du box
    position *pos;// position
}Grid;

/**
 * Structure de Widget GTK_FRAME
**/
typedef struct
{
    GtkWidget *frame; // le widget Frame
    GtkWidget *pere; // le conteneur
    gchar *nom; // nom
    gchar *label; // label
    /* alignement du label le long du bord supérieur du widget */
    float label_xalign; //l’alignement x de l’étiquette
    float label_yalign; //l’alignement y de l’étiquette
    gint type_shadow;/* * 0: GTK_SHADOW_NONE
                        * 1: GTK_SHADOW_IN
                        * 2: GTK_SHADOW_OUT
                        * 3: GTK_SHADOW_ETCHED_IN
                        * 4: GTK_SHADOW_ETCHED_OUT
                     */
    dimension *dim; //dimension du box
    position *pos;// position
}Frame;

/**
 * Structure About Dialog
**/
typedef struct
{
    GtkWidget *aboutDialog;
    gchar *titre;//le titre du dialogue
    gchar *version;//la verdion du dialogue
    gchar *Copyright;//Cpyright a ecrire
    gchar *commentaire;//les commentaire du dialogue
    gchar *license;//Message des license
    gboolean licenseDimension;//les dimensions du texte du liscence
    gchar *website;//le lien du site web
    gchar *website_label;//le nom du qui conduit au lien
    gchar **authors;//Nom des auteurs
    gchar **artists;//Nom des artistes
    gchar **documenters;//les documenters
    gchar *section;//la section a ajouté
    gchar **people;//Nom desles personnes
    gchar *image;//Nom d image
    gchar *image_texte;//Texte qui s'affiche au dessous de l'image
    gchar *image_title;//Titre de l'image
    gchar *icon_name;//L'icone qui saffiche dans le dialogue
    gboolean picture;//Si l'image existe
}aboutdialogue;

/**
 * Structure Dialog
**/
typedef struct
{
	gchar *titre;//le titre du dialogue
	GtkWidget *contain;//le dialogue
	gboolean *button_yes;//button Yes
	gboolean *button_no;//Button NO
	gboolean *button_cancel;//Button cancel
	//gboolean *button_ok;
	gboolean *show_dialog;//voir le dialog plusieur fois
	gboolean *use_header_bar;//L'utilisation du header bar
	gint posx;//position du dialogue
	gint posy;//position du dialogue
	gint width;//largeur
    gint height;//longeur

}dialogue;

/**
 * Structure Entry
**/
typedef struct
{
    GtkWidget *entry;
    //dimension dim;
    gboolean visible; //le texte est visible ou pas.
    gchar invisible_car; //le caractère d&#39;un texte invisible.
    gchar *placeholder;
    gint posx;
    gint posy;
    gfloat alignment;
    int MAX_LENGTH;
    int longeur;
    gchar *css;
    gchar *icon_name;
    gboolean *icone_place;
}Entry;

//Structure de Menu
typedef struct It
{
	GMenuItem* item;
	const gchar* label;
	const gchar *action;
	const gchar* icon;
	const gchar* accel;
	const gchar* target;
	const gchar* target_genre;
	gint posIt;
	struct It* suiv;
}Item;

typedef struct sm
{
	gint pos;
	GMenu* mn;
	const gchar *Smenu_genre;
	const gchar *name;
	Item* Itm;
	struct sm* desc;
	struct sm* pere;
}SubSecMenu;

typedef struct
{
	GMenu* menubar;
	SubSecMenu* menu;
}GtMenu;

typedef struct
{
  GtkWidget *window;
  const char *title_window;
  int height_window;
  int width_window;
  GtkWindowType type_window;
  GtkWindowPosition position_window;
  const char *icon;
  const char *css;

}Wind;

//structure de scroll
typedef struct
{
      GtkWidget *scrolled_window;
      guint border_width;
      GtkWidget* child;

}scroll_wind;

/*
* structure du scale
*/
typedef struct
{
    GtkWidget *scale; // objet scale
    GtkWidget *container; // contenaire
    GtkOrientation type; // type de scale : H ou V
    GtkPositionType posDig;/* le position dans laquelle la valeur actuelle est
                            Afficher*/
    gchar *titre;// titre qu'on va afficher
    gboolean *draw_value;
    gdouble Min; // valeur minimale
    gdouble Max; //valeur maximale
    gdouble step; //le pas de déplacement
    gint domDig; // domain des valeur (1:reels,0:entiers)
}Scale;

/*
* structure du scale
*/
typedef struct
{
    GtkWidget *align;// widget Align
    float x;// alignement horizonatl
    float y;// alignement vertical
}Align;


/**==============================================================================================================================**/
/**===========================================================Prototypes=========================================================**/
/**==============================================================================================================================**/
Frame *initialiser_Frame( GtkWidget *conteneur,
                        gchar *label,gchar *nom,
                        float label_X_align,float label_Y_align,
                        gint shadow_type,
                        gint hauteur, gint largeur,
                        gint pos_x, gint pos_y
                      );

Frame *create_Frame(Frame *F);

Grid *initialiser_Grid(GtkWidget *conteneur,gchar *nom,
                       gboolean homo_lignes, gboolean homo_colonnes,
                       gint spacing_lignes,gint spacing_colonnes,
                       guint bordure,
                       gint hauteur, gint largeur,
                       gint pos_x, gint pos_y
                     );

Grid *create_Grid(Grid *G);

Box *initialiser_Box(GtkWidget *conteneur,gchar *nom,
                     gchar type, gboolean homo,
                     gint spacing,guint bordure,
                     gint hauteur, gint largeur,
                     gint pos_x, gint pos_y
                     );

Box *create_Box(Box *B);

bouton *initialiser_Bouton( gint type,GtkWidget *conteneur,
                            GtkWidget *membre_grp,const gchar* stock_id,
                            gchar *label,gchar *nom,
                            gint mnemonic,gchar *image,
                            gint hauteur, gint largeur,
                            gint pos_x, gint pos_y
                            );

bouton *create_simpleButton(bouton *butt);
bouton *create_checkButton(bouton *butt);
bouton *create_radioButton(bouton *butt);
bouton *create_toggleButton(bouton *butt);

aboutdialogue *Allouer_aboutdialogue();
dialogue *Allouer_Dialogue();
Entry *Allouer_Entry();
void createEntry(Entry *pentry);
void print_entry_text(GtkWidget *widget, gpointer *entry);
void insert_text_callback(Entry *pentry);


/**==============================================================================================================================**/
/**===========================================================FONCTIONS==========================================================**/
/**==============================================================================================================================**/
void allocation_test(void *pointeur, char *nom)
{
    if(!pointeur)
    {
        printf("\nErreur d'allocation du <%s>\n", nom);
        exit(-1);
    }
}
/**------------------------------------------------------------------------------------------------------------------
Entrée: - Le container dans le quelle on va mettre notre Frame
        - Le nom pour mémoriser notre Frame
        - Le texte "label" du Frame
        - L’alignement des abscisses X de l’étiquette le long du bord supérieur du widget
        - L’alignement des abscisses Y de l’étiquette
        - Un entier pour spécifier le type du shadow:
        * 0: GTK_SHADOW_NONE: pas de contour.
        * 1: GTK_SHADOW_IN: le contour est biseauté vers l’intérieur.
        * 2: GTK_SHADOW_OUT: le contour est biseauté vers l'intérieur comme un bouton.
        * 3: GTK_SHADOW_ETCHED_IN:  le contour a une apparence 3D enfoncée.
        * 4: GTK_SHADOW_ETCHED_OUT:  le contour a une apparence 3D en relief.
        - Hauteur et largeur du Grid
        - Position X et Y par rapport au contenaire
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur de type Frame après l’allocation et l’initialisation
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de faire l'allocation de la structure du Frameet initialiser leur
             champs.
---------------------------------------------------------------------------------------------------------------------**/
Frame *initialiser_Frame( GtkWidget *conteneur,
                        gchar *label,gchar *nom,
                        float label_X_align,float label_Y_align,
                        gint shadow_type,
                        gint hauteur, gint largeur,
                        gint pos_x, gint pos_y
                      )
{
    Frame *F =NULL;
    /** allocation dynamique et initialisation des différents  champs **/
    F=(Frame *) g_malloc(sizeof(Frame));
    //allocation et vérification
    allocation_test(F,"Frame");
    F->dim=(dimension *) g_malloc(sizeof(dimension));
    allocation_test(F->dim,"Frame->dimension");
    F->pos=(position *) g_malloc(sizeof(position));
    allocation_test(F->pos,"Frame->position");
    //Widget parent
    F->pere=conteneur;
    //label
    if(label)
    {
        F->label=(gchar*)g_malloc((int)(strlen(label)+1) * sizeof(gchar));
        allocation_test(F->label,"Frame->label");
        strcpy(F->label,label);
    }
    else F->label = NULL;
    //nom
    if(nom)
    {
        F->nom=(gchar*)g_malloc((int)(strlen(nom)+1) * sizeof(gchar));
        allocation_test(F->nom,"Frame->Nom");
        strcpy(F->nom,nom);
    }
    else F->nom=NULL;
    //alignement du label
    F->label_xalign=label_X_align;
    F->label_yalign=label_Y_align;
    //type du shadow
    F->type_shadow=shadow_type;
    //taille
    F->dim->x=hauteur;
    F->dim->y=largeur;
    //position
    F->pos->x=pos_x;
    F->pos->y=pos_y;
    return((Frame *)F);
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur la Frame
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le Frame bien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer le conteneur Frame avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/
Frame *create_Frame(Frame *F)
{
    if(!F)
    {
        return ((Frame*)NULL);
    }
    F->frame=gtk_frame_new(F->label);
    //Alignement du label
    gtk_frame_set_label_align(GTK_FRAME(F->frame),F->label_xalign,F->label_yalign);
    //type du shadow
    switch (F->type_shadow) {
        case 1:
            gtk_frame_set_shadow_type(GTK_FRAME(F->frame),GTK_SHADOW_IN);
            break;
        case 2:
            gtk_frame_set_shadow_type(GTK_FRAME(F->frame),GTK_SHADOW_OUT);
            break;
        case 3:
            gtk_frame_set_shadow_type(GTK_FRAME(F->frame),GTK_SHADOW_ETCHED_IN);
            break;
        case 4:
            gtk_frame_set_shadow_type(GTK_FRAME(F->frame),GTK_SHADOW_ETCHED_OUT);
            break;
        default:
            gtk_frame_set_shadow_type(GTK_FRAME(F->frame),GTK_SHADOW_NONE);
            break;
    }
    //affecter le nom
    gtk_widget_set_name(F->frame,F->nom) ;
    //affecter la dimension
    gtk_widget_set_size_request(F->frame,F->dim->x,F->dim->y);
    // metre le box dans son conteneur s'il existe
    if(F->pere)
    {
        gtk_container_add(GTK_CONTAINER(F->pere),F->frame);
    }
    return ((Frame *)F) ;
}//fin


/**----------------------------------------------------------------------------------------------------------------------
Entrée: - Le container dans le quelle on va mettre notre Grid
        - Le nom pour mémoriser notre Grid
        - Un booléen pour dire si sa création avec homogénéité des lignes ou pas (0 ou 1)
        - Un booléen pour dire si sa création avec homogénéité des colonnes ou pas (0 ou 1)
        - Nombre de pixels entre les lignes
        - Nombre de pixels entre les colonnes
        - Le type de positionnement (V:Vertical ou H:Horizontal)
        - Hauteur et largeur du Grid
        - Position X et Y par rapport au contenaire
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur de type Grid après l’allocation et l’initialisation
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de faire l'allocation de la structure du Grid et initialiser leur
             champs.
---------------------------------------------------------------------------------------------------------------------**/
Grid *initialiser_Grid(GtkWidget *conteneur,gchar *nom,
                       gboolean homo_lignes, gboolean homo_colonnes,
                       gint spacing_lignes,gint spacing_colonnes,
                       guint bordure,
                       gint hauteur, gint largeur,
                       gint pos_x, gint pos_y
                     )
{
    Grid *G=NULL ;//déclaration du pointeur de type Box
    /** allocation dynamique et initialisation des différents champs **/
    G=(Grid *) g_malloc(sizeof (Grid )) ;
    //allocation et vérification
    allocation_test(G,"Grid");
    G->dim=(dimension *) g_malloc(sizeof(dimension));
    allocation_test(G->dim,"Grid->dimension");
    G->pos=(position *) g_malloc(sizeof(position));
    allocation_test(G->pos,"Grid->position");
    //Widget Parent
    G->pere=conteneur;
    //nom
    if(nom)
    {
        G->nom=(gchar*)g_malloc((int)(strlen(nom)+1) * sizeof(gchar));
        allocation_test(G->nom,"Grid->Nom");
        strcpy(G->nom,nom);
    }
    else G->nom=NULL;
    //homoginité des lignes et colonnes
    G->homogene_Lg=homo_lignes;
    G->homogene_Col=homo_colonnes;
    //Espace entre les lignes et colonnes
    G->spacing_Lg=spacing_lignes;
    G->spacing_Col=spacing_colonnes;
    //Bordure
    G->bord=bordure;
    //Hauteur et largeur
    G->dim->x=hauteur;
    G->dim->y=largeur;
    //position
    G->pos->x=pos_x;
    G->pos->y=pos_y;
    return ((Grid *)G) ;
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur le Grid
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le Grid bien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer le conteneur Grid avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/
Grid *create_Grid(Grid *G)
{
    if(!G)
    {
        return ((Grid*)NULL);
    }
    G->grid=gtk_grid_new();
    //affecter l’homogénéité des lignes
    gtk_grid_set_row_homogeneous(GTK_GRID(G->grid),G->homogene_Lg);

    //affecter l’homogénéité des colonnes
    gtk_grid_set_column_homogeneous(GTK_GRID(G->grid),G->spacing_Col);

    //affecter l’espace entre les lignes
    gtk_grid_set_row_spacing(GTK_GRID(G->grid),G->spacing_Lg);
    //affecter l’espace entre les colonnes
    gtk_grid_set_column_spacing(GTK_GRID(G->grid),G->spacing_Col);
    gtk_widget_set_size_request(G->grid,G->dim->x,G->dim->y);
    //affecter le nom
    gtk_widget_set_name(G->grid,G->nom) ;
    //affecter le bordure
    gtk_container_set_border_width (GTK_CONTAINER (G->grid), G->bord);
    // metre le box dans son conteneur s'il existe
    if(G->pere)
    {
        gtk_container_add(GTK_CONTAINER(G->pere),G->grid);
    }
    return ((Grid *)G) ;
}//fin

/**----------------------------------------------------------------------------------------------------------------------
Entrée: - Le container dans le quelle on va mettre notre Box
        - Le nom pour mémoriser le Box
        - Le type de positionnement (V:Vertical ou H:Horizontal)
        - Un booléen pour dire si sa création avec homogénéité ou pas (0 ou 1)
        - Nombre de pixels entre les fils du box
        - Hauteur et largeur du Box
        - Position X et Y par rapport au contenaire
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur de type Box après l’allocation et l’initialisation
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de faire l'allocation de la structure du Box et initialiser leur
             champs.
---------------------------------------------------------------------------------------------------------------------**/
Box *initialiser_Box(GtkWidget *conteneur,gchar *nom,
                     gchar type, gboolean homo,
                     gint spacing,guint bordure,
                     gint hauteur, gint largeur,
                     gint pos_x, gint pos_y
                     )
{
    Box *B=NULL ;//déclaration du pointeur de type Box
    /** allocation dynamique et initialisation des différents  champs **/
    B=(Box *) g_malloc(sizeof (Box )) ;
    //allocation et vérification
    allocation_test(B,"Box");
    B->dim=(dimension *) g_malloc(sizeof(dimension));
    allocation_test(B->dim,"Box->dimension");
    B->pos=(position *) g_malloc(sizeof(position));
    allocation_test(B->pos,"Box->position");
    //Widget parent
    B->pere=conteneur;
    //nom
    if(nom)
    {
        B->nom=(gchar*)g_malloc((int)(strlen(nom)+1) * sizeof(gchar));
        allocation_test(B->nom,"Box->Nom");
        strcpy(B->nom,nom);
    }
    else B->nom=NULL;
    //type
    B->type=type;
    //homoginité
    B->homogene=homo;
    //Espace entre les fils
    B->spacing=spacing;
    //Bordure
    B->bord=bordure;
    //Hauteur et largeur
    B->dim->x=hauteur;
    B->dim->y=largeur;
    //position
    B->pos->x=pos_x;
    B->pos->y=pos_y;
    return ((Box *)B) ;
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur le Box
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le Box bien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer le conteneur Box avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/
Box *create_Box(Box *B)
{
    if(!B)
    {
        return ((Box*)NULL);
    }
    //si le box est horizontal
    if((B->type)=='h'|| (B->type)=='H')
        B->box= gtk_box_new(GTK_ORIENTATION_HORIZONTAL,B->spacing) ;
        //sinon si c’est vertical ( ou par défaut ça sera vertical)
    else B->box= gtk_box_new(GTK_ORIENTATION_VERTICAL,B->spacing) ;
    /*else
    {
        printf("\nType du Box inconnu!"); exit(-1);
    }*/
    //affecter l’homogénéité
    gtk_box_set_homogeneous(GTK_BOX(B->box),B->homogene);
    //affecter le nom
    gtk_widget_set_name(B->box,B->nom) ;
    //affecter le bordure
    gtk_container_set_border_width (GTK_CONTAINER (B->box), B->bord);
    //affecter les dimensions
    gtk_widget_set_size_request(B->box,B->dim->x,B->dim->y);
    // metre le box dans son conteneur s'il existe
    if(B->pere)
    {
        gtk_container_add(GTK_CONTAINER(B->pere),B->box);
    }
    return ((Box*)B) ;
}//fin

/**----------------------------------------------------------------------------------------------------------------------
Entrée: - Type du boutton
        - Le container dans le quelle on va mettre notre bouton
        - Le texte "label" du bouton
        - Le nom du bouton pour mémoriser le boutton
        - Un booléen pour dire si sa création avec mnemonic ou pas
        - Le nom d'image si on veut la mettre
        - Hauteur et largeur du boutton
        - Position X et Y par rapport au contenaire
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur de type Bouton après l’allocation et l’initialisation
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de faire l'allocation de la structure du bouton et initialiser leur
             champs.
---------------------------------------------------------------------------------------------------------------------**/
bouton *initialiser_Bouton( gint type,GtkWidget *conteneur,
                            GtkWidget *membre_grp,const gchar* stock_id,
                            gchar *label,gchar *nom,
                            gint mnemonic,gchar *image,
                            gint hauteur, gint largeur,
                            gint pos_x, gint pos_y
                            )
{
    bouton *butt =NULL;
    /** allocation dynamique et initialisation des différents  champs **/
    butt=(bouton*) g_malloc(sizeof(bouton));
    //allocation et vérification
    allocation_test(butt,"Bouton");
    butt->pos=(position *) g_malloc(sizeof(position));
    allocation_test(butt->pos,"Bouton->position");
    butt->dim=(dimension *) g_malloc(sizeof(dimension));
    allocation_test(butt->dim,"Bouton->dimension");
    //Widget parent
    butt->pere=conteneur;
    //label
    if(label)
    {
        butt->label=(gchar*)g_malloc((int)(strlen(label)+1) * sizeof(gchar));
        allocation_test(butt->label,"Bouton->label");
        strcpy(butt->label,label);
    }
    else butt->label = NULL;
    //nom
    if(nom)
    {
        butt->nom=(gchar*)g_malloc((int)(strlen(nom)+1) * sizeof(gchar));
        allocation_test(butt->nom,"Bouton->nom");
        strcpy(butt->nom,nom);
    }
    else butt->nom=NULL;
    //image
    if(image)
    {
        butt->image=(gchar*)g_malloc((int)(strlen(image)+1) * sizeof(gchar));
        allocation_test(butt->image,"Bouton->image_titre");
        strcpy(butt->image,image);
    }
    else butt->image=NULL;
    //type
    butt->type=type;
    //boutton groupe pour bouton radio
    butt->membre_grp=membre_grp;
    //mnemonic
    butt->mnemonic=mnemonic;
    //stock_ud pour bouton du stock
    butt->stock_id=stock_id;
    //taille
    butt->dim->x=hauteur;
    butt->dim->y=largeur;
    //position
    butt->pos->x=pos_x;
    butt->pos->y=pos_y;
    return((bouton*)butt);
}//fin de la fonction


/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur le bouton de type simple
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le bouton de type simple bien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer un bouton simple avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/
bouton *create_simpleButton(bouton *butt)
{
    GtkImage *img = NULL;
    if(!butt)
    {
        printf("\nBouton Radio inexistant!");
        return ((bouton*)NULL);
    }
    /** affectation de l’ensemble des caractéristiques selon l’initialisation faite **/
    else if(butt->type==1)
    {
        if(butt->stock_id)
        {
            butt->button= gtk_button_new_from_stock(butt->stock_id);
        }
        else
        {
            //bouton avec label
            if(butt->label)
            {
                //bouton avec mnemonic
                if(butt->mnemonic)
                    butt->button=gtk_button_new_with_mnemonic((butt->label));
                //bouton sans mnemonic
                else
                    butt->button=gtk_button_new_with_label((butt->label));
            }
            else
                //bouton sans label
                butt->button=gtk_button_new();
        }
        //nom
        if(butt->nom) gtk_widget_set_name(butt->button,butt->nom);
        //image
        if(butt->image)
        {
            img = gtk_image_new_from_file(butt->image);
            gtk_image_set_pixel_size(img,15);
            gtk_button_set_image(GTK_BUTTON(butt->button),GTK_WIDGET(img));
        }
        //dimension
        if(butt->dim)
        {
            gtk_widget_set_size_request(butt->button,
                                        butt->dim->x,
                                        butt->dim->y);
        }
        //dimension par défaut
        else
            gtk_widget_set_size_request(butt->button,10,10);
        return((bouton*)butt);
    }
    printf("\nErreur! create_fonction usée pour le mal type du bouton!");
    return ((bouton*)NULL);
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur le bouton de type checkBox
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le bouton de type checkBox bien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer un bouton checkBox avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/
bouton *create_checkButton(bouton *butt)
{
    if(!butt)
    {
        printf("\nBouton Radio inexistant!");
        return ((bouton*)NULL);
    }
    /** affectation de l’ensemble des caractéristiques selon l’initialisation faite **/
    else if(butt->type==2)
    {
        //bouton avec label
        if(butt->label)
        {
            //bouton avec mnemonic
            if(butt->mnemonic)
            {
                butt->button=gtk_check_button_new_with_mnemonic((butt->label));
            }
            //bouton sans mnemonic
            else
                butt->button=gtk_check_button_new_with_label((butt->label));
        }
        //bouton sans label
        else
            butt->button=gtk_check_button_new();
        //nom
        if(butt->nom) gtk_widget_set_name(butt->button,butt->nom);
        //dimension
        if(butt->dim)
        {
            gtk_widget_set_size_request(butt->button,
                                        butt->dim->x,
                                        butt->dim->y);
        }
            //dimension par défaut
        else
            gtk_widget_set_size_request(butt->button,10,10);
        return((bouton*)butt);
    }
    printf("\nErreur! create_fonction usée pour le mal type du bouton!");
    return ((bouton*)NULL);
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur le bouton de type radio
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le bouton de type chackBoxbien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer un bouton checkBox avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/

bouton *create_radioButton(bouton *butt)
{
    if(!butt)
    {
        printf("\nBouton Radio inexistant!");
        return ((bouton*)NULL);
    }
    /** affectation de l’ensemble des caractéristiques selon l’initialisation faite **/
    else if(butt->type==3)
    {
        //creation sans membre du groupe
        if(!butt->membre_grp)
        {
            //bouton avec label
            if(butt->label)
            {
                //bouton avec mnemonic
                if(butt->mnemonic)
                {
                    butt->button=gtk_radio_button_new_with_mnemonic(NULL,(butt->label));
                }
                //bouton sans mnemonic
                else
                    butt->button=gtk_radio_button_new_with_label(NULL,(butt->label));
            }
            //bouton sans label
            else
                butt->button=gtk_radio_button_new(NULL);
        }
        //creation avec un membre du groupe
        else
        {
            //label
            if(butt->label)
            {
                //mnemonic
                if(butt->mnemonic)
                {
                    butt->button=gtk_radio_button_new_with_mnemonic_from_widget(GTK_RADIO_BUTTON(butt->membre_grp),
                                                                                (butt->label));
                }
                else
                    butt->button=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(butt->membre_grp),
                                                                                (butt->label));
            }
            else
                butt->button=gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(butt->membre_grp));
        }
        //nom
        if(butt->nom) gtk_widget_set_name(butt->button,butt->nom);
        //dimension
        if(butt->dim)
        {
            gtk_widget_set_size_request(butt->button,
                                        butt->dim->x,
                                        butt->dim->y);
        }
        //dimension par défaut
        else
            gtk_widget_set_size_request(butt->button,10,10);
        return((bouton*)butt);
    }
    printf("\nErreur! create_fonction usée pour le mal type du bouton!");
    return ((bouton*)NULL);
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur le bouton de type toggle
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le bouton de type toggle bien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer un toggle radio avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/
bouton *create_toggleButton(bouton *butt)
{
    if(!butt)
    {
        printf("\nBouton Radio inexistant!");
        return ((bouton*)NULL);
    }
    /** affectation de l’ensemble des caractéristiques selon l’initialisation faite **/
    else if(butt->type==4)
    {
        //bouton avec label
        if(butt->label)
        {
            //bouton avec mnemonic
            if(butt->mnemonic)
            {
                butt->button=gtk_toggle_button_new_with_mnemonic((butt->label));
            }
                //bouton sans mnemonic
            else
                butt->button=gtk_toggle_button_new_with_label((butt->label));
        }
        else
            //bouton sans label
            gtk_toggle_button_new();
        //nom
        if(butt->nom) gtk_widget_set_name(butt->button,butt->nom);
        //dimension
        if(butt->dim)
        {
            gtk_widget_set_size_request(butt->button,
                                        butt->dim->x,
                                        butt->dim->y);
        }
            //dimension par défaut
        else
            gtk_widget_set_size_request(butt->button,10,10);
        return((bouton*)butt);
    }
    printf("\nErreur! create_fonction usée pour le mal type du bouton!");
    return ((bouton*)NULL);
}//fin de la fonction

//initialisation de la fenetre
void init_window(Wind* fen,const char* title,const char* icon,const char *css,int height,int width,GtkWindowType type,GtkWindowPosition position)
{
	fen->title_window    = title;
	fen->height_window   = height;
	fen->width_window    = width;
	fen->type_window     = type;
	fen->position_window = position;
	fen->icon            = icon;
	fen->css             = css;
}

//creation de la fenetre
GtkWidget *create_window(Wind fen,GtkApplication *app)
{
    GdkPixbuf *pixbuf, *scaled_pixbuf;
    GtkWidget *image;
    //creation avec gtk application
    if(app)
    {
        fen.window = gtk_application_window_new(app);
    }
    else
    {
        fen.window =gtk_window_new(fen.type_window);
    }
    // type de fenetre:
    //fen.window=gtk_window_new(fen.type_window);
    // Title de la fenetre:
    gtk_window_set_title (GTK_WINDOW (fen.window),fen.title_window);
    // Taille de la fenetre:
    gtk_window_set_default_size (GTK_WINDOW (fen.window),fen.width_window, fen.height_window);
    // Position de la fenetre:
    gtk_window_set_position(GTK_WINDOW(fen.window), fen.position_window);
    //icon window
    gtk_window_set_icon_from_file(GTK_WINDOW(fen.window), fen.icon,NULL);

    //*****header bar
	GtkWidget* headerbar;
	//create headerbar
	headerbar = gtk_header_bar_new();
	//title
	gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), fen.title_window);
	//close button
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar),TRUE);

	//Add the header bar to the window
    gtk_window_set_titlebar(GTK_WINDOW(fen.window), headerbar);
    //icon window
    pixbuf = gdk_pixbuf_new_from_file(fen.icon, NULL);
    scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 25, 25, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(scaled_pixbuf);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar),image);
    //css
    add_css(fen.window,fen.css);

    return ((GtkWidget*)fen.window);
}

//initialisation de scroll
void init_scrol(scroll_wind *curseur)
{
     curseur->border_width=10;
     curseur->child;
}

//creation du scrol
GtkWidget *create_scrol(scroll_wind scrol)
{
    // creer scroll window:
    scrol.scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    // Set the border width
    gtk_container_set_border_width (GTK_CONTAINER (scrol.scrolled_window),  scrol.border_width);
    // Set the policy of the horizontal and vertical scrollbars to automatic.
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrol.scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    return ((GtkWidget*)scrol.scrolled_window);
}

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur de type Frame
* ----------------------------------------------------------------------------------------------------------------------
Sortie:
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet libérer la mémoire pour les différents champs dont l'allocation dynamique
            est faite avant
---------------------------------------------------------------------------------------------------------------------**/
void free_frame(Frame *frame) {
    if (frame)
    {
        if (frame->frame) {
            gtk_widget_destroy(frame->frame);
        }
        g_free(frame->nom);
        g_free(frame->label);
        g_free(frame->dim);
        g_free(frame->pos);
        g_free(frame);
        //Définir le pointeur sur NULL pour éviter toute réutilisation accidentelle
        frame=NULL;
    }
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur de type Box
* ----------------------------------------------------------------------------------------------------------------------
Sortie:
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet libérer la mémoire pour les différents champs dont l'allocation dynamique
            est faite avant
---------------------------------------------------------------------------------------------------------------------**/
void free_box(Box *box) {
    if (box)
    {
        if (box->box) {
            gtk_widget_destroy(box->box);
        }
        g_free(box->nom);
        g_free(box->dim);
        g_free(box->pos);
        g_free(box);
        //Définir le pointeur sur NULL pour éviter toute réutilisation accidentelle
        box=NULL;
    }
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur de type Grid
* ----------------------------------------------------------------------------------------------------------------------
Sortie:
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet libérer la mémoire pour les différents champs dont l'allocation dynamique
            est faite avant
---------------------------------------------------------------------------------------------------------------------**/
void free_grid(Grid *grid) {
    if (grid)
    {
        if (grid->grid) {
            gtk_widget_destroy(grid->grid);
        }
        g_free(grid->nom);
        g_free(grid->dim);
        g_free(grid->pos);
        g_free(grid);
        //Définir le pointeur sur NULL pour éviter toute réutilisation accidentelle
        grid=NULL;
    }
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur de type Bouton
* ----------------------------------------------------------------------------------------------------------------------
Sortie:
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet libérer la mémoire pour les différents champs dont l'allocation dynamique
            est faite avant
---------------------------------------------------------------------------------------------------------------------**/
void free_bouton(bouton *butt) {
    if (butt)
    {
        if (butt->button) {
            gtk_widget_destroy(butt->button);
        }
        g_free(butt->image);
        g_free(butt->nom);
        g_free(butt->label);
        g_free(butt->dim);
        g_free(butt->pos);
        g_free(butt);
        //Définir le pointeur sur NULL pour éviter toute réutilisation accidentelle
        butt=NULL;
    }
}//fin de la fonction

/**----------------------------------------------------------------------------------------------------------------------
Entrée: - Type du scale
        - Le container dans le quelle on va mettre notre scale
        - Le texte "label" du scale
        - Position du texte
        - Valeur minimale du scale
        - Valeur maximale du scale
        - Offset du step
        - domaine des valeurs (entier / float)
        - domaine des valeurs (entier / float)
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur de type scale après l’allocation et l’initialisation
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de faire l'allocation de la structure du scale et initialiser leur
             champs.
---------------------------------------------------------------------------------------------------------------------**/

Scale *init_scale( GtkWidget*container,
                   gchar*titre,
                   GtkOrientation type,
                   GtkPositionType posD,
                   gdouble min,
                   gdouble max,
                   gdouble step,
                   gint domD,
                   gboolean *draw
                   )
{
    //déclaration et allocation de la mémoire pour un pointeur de type MonScale
    Scale* S=(Scale*) malloc(sizeof (Scale)) ;
    allocation_test(S,"Scale");
   // test_allocation(S, "scale") ;//vérifier l’allocation
    if(titre)//affectation du titre s’il existe
    {
        S->titre=(gchar*) malloc((int)(strlen(titre)+1) *sizeof(gchar)) ;
        //test_allocation(S->scale.titre, "titre scale") ;
        strcpy(S->titre,titre) ;
    }
    S->container=container ;//affectation du conteneur
    S->type=type ;//affectation du type de scale
    S->posDig=posD ;//affectation du positionnement de la valeur du Scale
    S->Max=max ;//valeur maximale
    S->Min=min ;//valeur minimale
    S->step=step ;//pas de variation
    S->draw_value=draw;
    S->draw_value=draw;
    S->domDig=domD ;//domaine des valeurs
    return ((Scale*) S) ;
}//fin

/**----------------------------------------------------------------------------------------------------------------------
Entrée: Un pointeur sur le scale de type Scale
* ----------------------------------------------------------------------------------------------------------------------
Sortie: Un pointeur sur le scale de type Scale bien créée
* ----------------------------------------------------------------------------------------------------------------------
Déscription:Cette fonction nous permet de créer un scale avec les paramètres initialisés
---------------------------------------------------------------------------------------------------------------------**/
Scale *create_scale(Scale *scale,const char *labels[],int taille)
{
    int i;
    int values[3]={0,2,4};
    scale->scale = gtk_scale_new_with_range(scale->type,scale->Min, scale->Max, scale->step);
    gtk_scale_set_draw_value(GTK_SCALE(scale->scale),scale->draw_value);
    gtk_scale_set_digits(GTK_SCALE(scale),0) ;
    gtk_scale_set_value_pos(GTK_SCALE(scale->scale), GTK_POS_TOP);

    for ( i = 0; i <= taille; i++)
    {
        gtk_scale_add_mark(GTK_SCALE(scale->scale),i+1, GTK_POS_TOP, labels[i]);
    }
    return ((Scale*) scale) ;
}

/**------------------------------------------------------------------------------------
Entrée: - Le widget
        - X et Y pour le centrage
* -------------------------------------------------------------------------------------
Sortie: Un Widget de type align
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet de center le widget dans align
------------------------------------------------------------------------------------**/

GtkWidget *centrer_widget(GtkWidget *widget,float x,float y)
 {
     GtkWidget *align = gtk_alignment_new(x, y, 0, 0);
     gtk_container_add(GTK_CONTAINER(align), widget);
     return (GtkWidget*)align;
 }


/**------------------------------------------------------------------------------------
Entrée: -
* -------------------------------------------------------------------------------------
Sortie: Un pointeur de type aboutdialogue après l’allocation et l’initialisation
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet de faire l'allocation de la structure du Box et   initialiser leur champs.
------------------------------------------------------------------------------------**/

aboutdialogue *Allouer_aboutdialogue()
{
    aboutdialogue *aboutdialog;
    aboutdialog=(aboutdialogue*)malloc(sizeof(aboutdialogue));
    aboutdialog->artists=NULL;
    aboutdialog->authors=NULL;
    aboutdialog->documenters=NULL;
    aboutdialog->image=NULL;
    aboutdialog->image_texte=NULL;
    aboutdialog->image_title=NULL;
    aboutdialog->people=NULL;
    aboutdialog->section=NULL;
    aboutdialog->titre=NULL;
    aboutdialog->version=NULL;
    aboutdialog->Copyright=NULL;
    aboutdialog->commentaire=NULL;
    aboutdialog->license=NULL;
    aboutdialog->licenseDimension=0;
    aboutdialog->picture=0;
    aboutdialog->website=NULL;
    aboutdialog->website_label=NULL;
    aboutdialog->icon_name=NULL;

    if(!aboutdialog)
    {
        g_print("\n Memory Probleme");
        exit(-1);
    }
    return((aboutdialogue*)aboutdialog);
}
/**------------------------------------------------------------------------------------
Entrée:
* -------------------------------------------------------------------------------------
Sortie: -Un pointeur de type dialogue
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet de faire l'allocation de la structure du dialogue et   initialiser leur champs.
------------------------------------------------------------------------------------**/

dialogue *Allouer_Dialogue()
  {
      dialogue *dialog;
      dialog=(dialogue*)g_malloc(sizeof(dialogue));
      if(!dialog)
      {
          g_print("\n memory probleme");
          exit(-1);
      }
   dialog->titre=NULL;
	 dialog->contain=NULL;
	dialog->button_cancel=0;
	dialog->button_no=0;
	dialog->button_yes=0;
	//dialog->fixe=0;
	dialog->posx=-1;
	dialog->posy=-1;
	dialog->show_dialog=1;
	dialog->use_header_bar=0;
	dialog->width=300;
	dialog->height=200;

      return((dialogue*)dialog);
}

Entry *Allouer_Entry()
{
    Entry *pentry;
    pentry=(Entry*)g_malloc(sizeof(Entry));
    if(!pentry)
    {
        g_print("\n Memory Problem");
        exit(-2);
    }
    pentry->entry=NULL;
    pentry->visible=0;
    pentry->invisible_car=NULL;
    pentry->placeholder=NULL;
    pentry->posx=500;
    pentry->posy=300;
    pentry->alignment=0;
    pentry->MAX_LENGTH=8;
    pentry->css=NULL;
    pentry->icon_name=NULL;
    pentry->icone_place=1;
    pentry->longeur=8;

    return((Entry*)pentry);
}

/**------------------------------------------------------------------------------------
Entrée: -Un pointeur sur la structure
* -------------------------------------------------------------------------------------
Sortie:
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet de changer l'icone lors du saisie et lors du depacement da la longeur maximal avec un message de dépacement
------------------------------------------------------------------------------------**/

void insert_text_callback(Entry *pentry)
{
    guint16 text_length = gtk_entry_get_text_length(GTK_ENTRY(pentry->entry));

    /**Position de l'icone*/
    if(pentry->icone_place)
    {   /**Depassement du longeur maximal*/
            if( text_length < pentry->MAX_LENGTH )
    {
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_PRIMARY,"media-seek-forward");
        gtk_entry_set_progress_fraction(GTK_ENTRY(pentry->entry),text_length /10.0);
    }
    else
    {
        gtk_entry_set_progress_fraction(GTK_ENTRY(pentry->entry),text_length /10.0);
        g_print("Maximal msg Length was reached\n");
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_PRIMARY,"media-playback-stop");
        gtk_main();
    }
    }
    else
    {
        if( text_length < pentry->MAX_LENGTH )
    {
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_SECONDARY,"media-seek-forward");
        gtk_entry_set_progress_fraction(GTK_ENTRY(pentry->entry),text_length /10.0);
    }
    else
    {
        gtk_entry_set_progress_fraction(GTK_ENTRY(pentry->entry),text_length /10.0);
        g_print("Maximal msg Length was reached\n");
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_SECONDARY,"media-playback-stop");
        gtk_main();
    }
        }
}



/**==============================================================================================================================**/
/**===========================================================SIGNALS============================================================**/
/**==============================================================================================================================**/
/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
            elle emmet un signal que le bouton de type simple est clické
---------------------------------------------------------------------------------------------------------------------**/
void clicked_callback(GtkWidget *widget,gpointer data)
{
    (void)widget;
    (void)data;
    g_print("\nButton was clicked");
}

/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
           elle emmet un signal "Quitté" et il quitte le programme
---------------------------------------------------------------------------------------------------------------------**/
void quit_callback(GtkWidget *widget,gpointer data,GApplication* application)
{
    (void)widget;
    g_print("\nQuitted");
    //gtk_main_quit();
    g_application_quit(application);
}

/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
            elle emmet un signal que la souris est dans la zone du bouton
---------------------------------------------------------------------------------------------------------------------**/
gboolean enter_callback(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    (void)widget;
    (void)data;
    if(event->type == GDK_ENTER_NOTIFY)
    {
        g_print("\nMouse enters the button area");
        return TRUE;
    }
    return FALSE;
}

/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
            elle emmet un signal que la souris a sortit de la zone du bouton
---------------------------------------------------------------------------------------------------------------------**/
gboolean leave_callback(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    (void)widget;
    (void)data;
    if(event->type == GDK_LEAVE_NOTIFY)
    {
        g_print("\nMouse leaves the button area");
        return TRUE;
    }
    return FALSE;
}

/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
           elle emmet un signal que:
           * Le bouton droit de la souris est pressé
           * Le bouton milieu de la souris est pressé
           * Le bouton gauche de la souris est pressé
---------------------------------------------------------------------------------------------------------------------**/
gboolean pressed_callback(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    (void)widget;
    (void)data;
    if( event->type == GDK_BUTTON_PRESS)
    {
        switch(event->button.button)
        {
            case 1:
                g_print("\nLeft button was clicked");
                return FALSE;
            case 2:
                g_print("\nMiddle button was clicked");
                return FALSE;
            case 3:
                g_print("\nRight button was clicked");
                return FALSE;
            default:
                return TRUE;
        }
    }
    return TRUE;
}

/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
 elle emmet un signal que:
           * Le bouton droit de la souris est laché
           * Le bouton milieu de la souris est laché
           * Le bouton gauche de la souris est laché
---------------------------------------------------------------------------------------------------------------------**/
gboolean released_callback(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    (void)widget;
    (void)data;
    if( event->type == GDK_BUTTON_RELEASE)
    {
        switch(event->button.button)
        {
            case 1:
                g_print("\n\tLeft button was released");
                return FALSE;
            case 2:
                g_print("\n\tMiddle button was released");
                return FALSE;
            case 3:
                g_print("\n\tRight button was released");
                return FALSE;
            default:
                return TRUE;
        }
    }
    return TRUE;
}

/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
            elle emmet un signal que le bouton de type Checkbox est soit coché ou n'est plus coché
---------------------------------------------------------------------------------------------------------------------**/
void toggled_check_callback(GtkToggleButton *button)
{
    if(gtk_toggle_button_get_active(button))
    {
        g_print("\nCheckButton is checked");
    }
    else
    {
        g_print("\nCheckButton is unchecked");
    }
}

/**----------------------------------------------------------------------------------------------------------------------
Déscription:Lors du passage de cette fonction dans G_CALLBACK() parametre de la fonction g_signal_connect_swapped
            elle emmet un signal que le bouton de type Checkbox est soit pressé ou n'est plus pressé
---------------------------------------------------------------------------------------------------------------------**/
void toggled_callback(GtkToggleButton *button)
{
    if(gtk_toggle_button_get_active(button))
    {
        g_print("\nToggle button is toggled");
    }
    else
    {
        g_print("\nToggle button is untoggled");
    }
}

/**------------------------------------------------------------------------------------
Entrée: -un pointeur sur le dialogue
        -l'identifiant du button
        -un pointeur sur la fenetre
* -------------------------------------------------------------------------------------
Sortie:
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet d'afficher un message lors du click d'un button donnée
------------------------------------------------------------------------------------**/
void response_callback(GtkWidget *dialog,gint response_id,GtkWidget *window)
{
       if(!GTK_IS_DIALOG(dialog) && !GTK_IS_WINDOW(window))
    {
        g_print("The expected parameter should be GTKWindow\n");
        return;
    }

    switch(response_id)
    {
    case 1:
        g_print("The YES button was pressed\n");
        g_print("Closing the Window...\n");
        break;

    case 2:
        g_print("The NO button was pressed\n");
        g_print("Closing the dialog...\n");
        gtk_widget_destroy(dialog);
        break;

    case 3:
        g_print("The Cancel button was pressed\n");
        gtk_widget_destroy(dialog);
        break;
    default:
        g_print("Something else happened...  \n");
        break;
    }
  }
void add_css(GtkWidget *Widget, const char *CSSCode)
{
	GtkCssProvider *Provider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(Provider, CSSCode, -1, NULL);

	GtkStyleContext *Context = gtk_widget_get_style_context(Widget);
	gtk_style_context_add_provider(Context, GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	g_object_unref(Provider);
}

void icon_press_callback(GtkEntry *entry,GtkEntryIconPosition icon_pos,GdkEvent *event,gpointer user_data)
{
    (void)entry;
    (void)icon_pos;
    (void)event;
    (void)user_data;
    g_print("The Icon was pressed\n");
}

void icon_release_callback(GtkEntry *entry,GtkEntryIconPosition icon_pos,GdkEvent *event,gpointer user_data)
{
    (void)entry;
    (void)icon_pos;
    (void)event;
    (void)user_data;
    g_print("The Icon was released\n");
}


/**Fonction callback execute lors du signal "activate"**/
void on_activate_entry(GtkWidget *pEntry, gpointer data)
{
    const gchar *sText;

    /** Recuperation du texte contenu dans le GtkEntry **/
    sText = gtk_entry_get_text(GTK_ENTRY(pEntry));

    /** Modification du texte contenu dans le GtkLabel **/
    gtk_label_set_text(GTK_LABEL((GtkWidget*)data), sText);
}

void backspace_callback(GtkWidget *widget)
{
    (void)widget;
    g_print("\n backspace was pressed");
}

void copy_clipboard_callback(GtkWidget *widget)
{
    (void)widget;
    g_print("\n CTRL + C was pressed");
}

void cut_clipboard_callback(GtkWidget *widget)
{
    (void)widget;
    g_print("\n CTRL + X was pressed");
}

void paste_clipboard_callback(GtkWidget *widget)
{
    (void)widget;
    g_print("\n CTRL + V was pressed");
}

/** Fonction callback executee lors du signal "clicked" **/
void on_copier_button(GtkWidget *pButton, gpointer *data,const gchar *sText)
{
    GtkWidget *pTempEntry;
    GtkWidget *pTempLabel;
    GList *pList;

   g_print("\n 1");
    /** Récupération de la liste des éléments que contient la GtkVBox **/
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
    g_print("\n 2");
    /** Le premier élément est le GtkEntry **/
    pTempEntry = GTK_WIDGET(pList->data);
    g_print("\n 3");
    /** Passage à l élément suivant : le GtkButton **/
    pList = g_list_next(pList);
    g_print("\n 4");
    /** Passage à l élément suivant : le GtkLabel **/
    ///pList = g_list_next(pList);
    g_print("\n 5");
    /** Cet élément est le GtkLabel **/
    pTempLabel = GTK_WIDGET(pList->data);
    g_print("\n 6");
    /** Recuperation du texte contenu dans le GtkEntry **/
    sText = gtk_entry_get_text(GTK_ENTRY(pTempEntry));
    g_print("\n 7");
    /** Modification du texte contenu dans le GtkLabel **/
    gtk_label_set_text(GTK_LABEL(pTempLabel), sText);
    g_print("\n 8");
    /** Libération de la mémoire utilisée par la liste **/
    g_list_free(pList);
    g_print("\n 9");
}


void on_entry_activate(GtkEntry *entry, gpointer user_data)
{
    // Get the text from the entry widget
    const gchar *text = gtk_entry_get_text(entry);

    // Print the text to the console
    g_print("Text entered: %s\n", text);
}

/**------------------------------------------------------------------------------------
Entrée: -Un pointeur sur entry et un ponteur
* -------------------------------------------------------------------------------------
Sortie:
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet d'afficher le  texte saisie par l'utilisateur
------------------------------------------------------------------------------------**/

void print_entry_text(GtkWidget *widget, gpointer *entry)
{
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    printf("Entry Text: %s\n", text);
}

/**------------------------------------------------------------------------------------
Entrée: -Un pointeur sur la structure et un pointeur de type GtkFixed
* -------------------------------------------------------------------------------------
Sortie:
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet d'afficher la zone du texte avec tout ces paramétre
------------------------------------------------------------------------------------**/


void createEntry(Entry *pentry)
{



    pentry->entry=gtk_entry_new();


        //gtk_fixed_put(GTK_FIXED(fixed),pentry->entry,pentry->posx,pentry->posy);


    gtk_widget_set_name(pentry->entry,"NewName");

    add_css(pentry->entry,pentry->css);
    g_signal_connect_swapped(pentry->entry,"activate", G_CALLBACK(on_activate_entry),pentry->entry);

    gtk_entry_set_max_length(GTK_ENTRY(pentry->entry),pentry->MAX_LENGTH);
    gtk_entry_set_width_chars(GTK_ENTRY(pentry->entry),pentry->longeur);
    gtk_entry_set_max_width_chars(GTK_ENTRY(pentry->entry),pentry->MAX_LENGTH);

        ///*******alignement du texte
    gtk_entry_set_alignment(GTK_ENTRY(pentry->entry),pentry->alignment);
       /**message par defaut **/
    gtk_entry_set_placeholder_text(GTK_ENTRY(pentry->entry),pentry->placeholder);
    if(pentry->visible)
    {
    /**Visibilite du texte entrée**/
    gtk_entry_set_visibility(GTK_ENTRY(pentry->entry),TRUE);
    }
    else
    {
       gtk_entry_set_visibility(GTK_ENTRY(pentry->entry),FALSE);
       /**Caractere visible**/
    gtk_entry_set_invisible_char(GTK_ENTRY(pentry->entry),pentry->invisible_car);
    }

    if(pentry->icone_place)
    {
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_PRIMARY,pentry->icon_name);
    gtk_entry_set_icon_activatable(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_PRIMARY,TRUE);
    }
    else
    {
     gtk_entry_set_icon_from_icon_name(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_SECONDARY,pentry->icon_name);
    gtk_entry_set_icon_activatable(GTK_ENTRY(pentry->entry),GTK_ENTRY_ICON_SECONDARY,TRUE);
    }


    g_signal_connect_swapped(pentry->entry,"insert-text",G_CALLBACK(insert_text_callback),pentry);
    g_signal_connect_swapped(pentry->entry,"icon-press",G_CALLBACK(icon_press_callback),pentry->entry);
    g_signal_connect_swapped(pentry->entry,"icon-release",G_CALLBACK(icon_release_callback),pentry->entry);
   // gtk_entry_set_icon_tooltip_text(GTK_ENTRY(entry),GTK_ENTRY_ICON_SECONDARY,"Click The Icon");

    g_signal_connect_swapped(pentry->entry,"backspace",G_CALLBACK(backspace_callback),pentry->entry);
    g_signal_connect_swapped(pentry->entry,"copy-clipboard",G_CALLBACK(copy_clipboard_callback),pentry->entry);
    g_signal_connect_swapped(pentry->entry,"cut-clipboard",G_CALLBACK(cut_clipboard_callback),pentry->entry);
    g_signal_connect_swapped(pentry->entry,"paste-clipboard",G_CALLBACK(paste_clipboard_callback),pentry->entry);

}

/**------------------------------------------------------------------------------------
Entrée: -Un pointeur sur le dialogue
* -------------------------------------------------------------------------------------
Sortie:
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet d'afficher un message lors du click sur echap
------------------------------------------------------------------------------------**/

void close_callback(GtkDialog *dialog )
{
    if(!GTK_IS_DIALOG(dialog))
    {
        return;
    }
    g_print("ESCAPE Key was pressed -The dialog was closed\n");

}


  /**------------------------------------------------------------------------------------
Entrée: -Un pointeur sur la fenetre
* -------------------------------------------------------------------------------------
Sortie:
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet de creer le dialogue avec tout leur configuration
------------------------------------------------------------------------------------**/


void run_dialog_callback(GtkWindow *window)
{
  dialogue *dialog;


    GtkWidget *label;
    GtkWidget *container;
    GtkWidget *box,*image;
    gint reponse;

    dialog=Allouer_Dialogue();

  ///***Initialisation des valeurs pour le test

    dialog->titre="reponse";
    dialog->button_yes=1;
    dialog->button_no=1;
    dialog->button_cancel=1;
    dialog->use_header_bar=0;
    dialog->show_dialog=1;
    dialog->width=200;
    dialog->height=100;
    dialog->posx=-1;
    dialog->posy=-1;

    ///Pour tester le parametre entree

   if(!GTK_IS_WINDOW(window))
    {
        g_print("The expected parameter should be GTKWindow\n");
        return;
    }

    /**Creation du dialogue**/
    if(dialog->use_header_bar)
            dialog->contain=g_object_new(GTK_TYPE_DIALOG,"transient-for",window,"use-header-bar",TRUE,NULL);
    else
    dialog->contain=gtk_dialog_new();

    g_signal_connect(dialog->contain, "response", G_CALLBACK(response_callback), window);
    g_signal_connect(dialog->contain, "close", G_CALLBACK(close_callback), NULL);


    if(dialog->show_dialog)
        gtk_window_set_modal(GTK_WINDOW(dialog->contain),FALSE);
    else
        gtk_window_set_modal(GTK_WINDOW(dialog->contain),TRUE);

    gtk_window_set_title(dialog->contain,dialog->titre);


        ///Fixer la position du dialogue
        if(	(dialog->posx==-1) && (dialog->posy==-1))
        gtk_window_set_position(GTK_WINDOW(dialog->contain),GTK_WIN_POS_CENTER);
        else///Positionner le dialogue
            gtk_window_move(GTK_WINDOW(dialog->contain),dialog->posx,dialog->posy);

        ///difinir la taille du dialogue
     gtk_widget_set_size_request(dialog->contain,dialog->width,dialog->height);



    /**Creation des buttons*/
    if(dialog->button_yes)
        gtk_dialog_add_button(GTK_DIALOG(dialog->contain),"OUI",1);
    if(dialog->button_no)
        gtk_dialog_add_button(GTK_DIALOG(dialog->contain),"Non",2);
    if(dialog->button_cancel)
        gtk_dialog_add_button(GTK_DIALOG(dialog->contain),"Annuler",3);


         GdkPixbuf *pixbuf;
    GdkPixbuf *scaled_pixbuf;

    box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    /**Création du label*/
    label=gtk_label_new("Voulez vous afficher une image?");
    g_object_set(label,"margin",20,NULL);
    /**Création du image*/
    pixbuf = gdk_pixbuf_new_from_file("alert.png", NULL);
    scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 50, 50, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(scaled_pixbuf);
    gtk_box_pack_start(box,image,FALSE,FALSE,0);
    gtk_box_pack_start(box,label,FALSE,FALSE,0);
    container=gtk_dialog_get_content_area(GTK_DIALOG(dialog->contain));
    gtk_container_add(GTK_CONTAINER(container),box);

    ///Press enter to work
    gtk_dialog_set_default_response(GTK_DIALOG(dialog->contain),1);
    ///kill a button
//    gtk_dialog_set_response_sensitive(GTK_DIALOG(dialog->contain),3,FALSE);

    ///affichage du dialogue
    gtk_widget_show_all(dialog->contain);


///liberation de la zone memeoire
free(dialog);
}


void Dialogue_Main(GtkWidget *window,GtkWidget *button)
{
	g_signal_connect_swapped(button,"clicked",G_CALLBACK(run_dialog_callback),window);
    g_object_set(button,"margin",50,NULL);
    //gtk_container_add(GTK_CONTAINER(window),button);
}

/**------------------------------------------------------------------------------------
Entrée: -Un pointeur sur le window
* -------------------------------------------------------------------------------------
Sortie:
* -------------------------------------------------------------------------------------
Déscription: Cette fonction nous permet de creer le dialog avec tout leur configuration
------------------------------------------------------------------------------------**/


void run_about_dialog_callback(GtkWindow *window)
{
    //test si le parametre entrée est de type window

   if(!GTK_IS_WINDOW(window))
    {
        g_print("The expected parameter should be GTKWindow\n");
        return;
    }
     ///Initialisation des champs pour le test
    aboutdialogue *aboutDialo;
    aboutDialo=Allouer_aboutdialogue();
    aboutDialo->authors= (gchar *[]){"Saleh Amimi","Achraf Rhazi", "Douae Chebila", "Hajar Elfallaki-Idrissi", NULL};
    aboutDialo->artists=(gchar *[]){"Saleh Amimi","Achraf Rhazi","Douae Chebila ","Hajar Elfallaki-Idrissi",NULL};
    aboutDialo->documenters=(gchar *[]){"Saleh Amimi","Achraf Rhazi","Douae Chebila","Hajar Elfallaki-Idrissi",NULL};
    aboutDialo->people=(gchar *[]){"Saleh Amimi","Achraf Rhazi","Douae Chebila ","Hajar Elfallaki-Idrissi",NULL};
    aboutDialo->section="My section";
    aboutDialo->titre="My programName";
    aboutDialo->version="1.0.0.0";
    aboutDialo->Copyright="My Copyright";
    aboutDialo->commentaire="Here you can put a Set of comments";
    aboutDialo->license="This is the part where you need to set your Liscence Information....................................";
    aboutDialo->licenseDimension=0;
    aboutDialo->picture=1;
    aboutDialo->website="https://www.youtube.com";
    aboutDialo->website_label="Youtube";
    aboutDialo->image="youtube.png";
    aboutDialo->image_texte="ExampleCode";
    aboutDialo->image_title="About ExampleCode";
    aboutDialo->icon_name="media-playback-start";
                //afectation du nom d'image dans une variable de type GdkPixbuf
     GdkPixbuf *exemplelogo=gdk_pixbuf_new_from_file(aboutDialo->image,NULL);

    ///*****
    /**Creation*/
    aboutDialo->aboutDialog=gtk_about_dialog_new();
    gtk_window_set_transient_for(GTK_WINDOW( aboutDialo->aboutDialog),GTK_WINDOW(window));
    /**Ajout du titre*/
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->titre);///-------------
    /**la Version*/
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->version);
    /**Copyright*/
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->Copyright);
    /**Commentaire*/
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->commentaire);
    /**License*/
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->license);


    ///FAlse change les dimension du texte
    if(aboutDialo->licenseDimension)
        gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),TRUE);
        else
    gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),FALSE);
    //gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(aboutDialog),GTK_LICENSE_AGPL_3_0);
    gtk_about_dialog_get_license_type(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog));
    /**Link*/
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->website);
    /**Le nom du Link*/
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->website_label);
    /**authors*/
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->authors);
    /**artists*/
    gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->artists);
    /**documenters*/
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->documenters);
   // gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(aboutDialog),("translator-credits"));
   /**Image*/
   if(aboutDialo->picture)
   gtk_show_about_dialog(NULL,"program-name",aboutDialo->image_texte,"logo",exemplelogo,"title",aboutDialo->image_title,NULL);
   /**Icon*/
   gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog),aboutDialo->icon_name);
   /**ajout des Nom dans la section*/
   gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG( aboutDialo->aboutDialog), aboutDialo->section, aboutDialo->people);


    gtk_widget_show_all( aboutDialo->aboutDialog);
    //liberatin de la zone memoire
    free(aboutDialo);

}

void About_Dialogue_Main(GtkWidget *window,GtkWidget *button)
{

    /**Liaison du signal**/
    g_signal_connect_swapped(button,"clicked",G_CALLBACK(run_about_dialog_callback),window);
    g_object_set(button,"margin",50,NULL);
    //gtk_container_add(GTK_CONTAINER(window),button);
}

/*
void Entry_all(GtkWindow *window,GtkWidget *button)
{
    GtkWidget *dial;

    dial=gtk_dialog_new();
    gtk_window_set_modal(GTK_WINDOW(dial),TRUE);
    gtk_window_set_title(dial,"Entry");
    gtk_window_set_position(GTK_WINDOW(dial),GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(dial,200,100);
    Entry_Main(window);

}*/

void Entry_Main(GtkWidget *window)
{
    GtkWidget *pButton;
    GtkWidget *pVBox;
    GtkWidget *pLabel;
    GtkWidget *fixed;
    Entry *pentry;
    GtkGrid *grid;

    pentry=Allouer_Entry();

    pentry->visible=0;
    pentry->invisible_car='*';
    pentry->placeholder="Entry is here...";
    pentry->MAX_LENGTH=8;
    pentry->alignment=0;
    pentry->css="entry{background-color:brown;color:white;font-style:20px;} #NewName>progress{background-color:orange;} #NewName>selection{background-color:green;}#NewName>image{background-color:red;} #NewName:focus{background-color:purple;} #NewName:hover{background-color:yellow;}";
    pentry->icon_name="call-start";
    pentry->posx=290;
    pentry->posy=290;
    pentry->longeur=20;
    pentry->icone_place=0;



    grid=gtk_grid_new();
    pVBox = gtk_vbox_new(TRUE, 0);
    fixed=gtk_fixed_new();



    /**Insertion du GtkEntry dans la GtkVBox**/

    gtk_box_pack_start(GTK_BOX(pVBox), pentry->entry, TRUE, FALSE, 0);



    //gtk_box_pack_start(GTK_BOX(pVBox), pButton[2], TRUE, FALSE, 0);

    pLabel = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    //gtk_widget_set_size_request(pButton[2] 150, 50);
    //gtk_grid_attach(GTK_GRID(grid), pButton, 10, 10, 10, 10);
    //gtk_fixed_put(GTK_FIXED(fixed),pButton,10,90);



   // gtk_container_add(GTK_CONTAINER(fixed),pButton);
    gtk_fixed_put(GTK_FIXED(fixed), pVBox,250,250);

   // g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(on_copier_button),(GtkWidget*) pVBox);
  // g_signal_connect(pentry->entry, "activate", G_CALLBACK(on_entry_activate), NULL);
//   g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(print_entry_text), pentry->entry);


}

static void action_clbk(G_GNUC_UNUSED GSimpleAction* action, G_GNUC_UNUSED GVariant* parameter, G_GNUC_UNUSED gpointer data)
{
	g_print("\nL'action [%s] est activee !!", g_action_get_name(G_ACTION(action)));
}
static void state_clbk(GSimpleAction* action, GVariant* state, G_GNUC_UNUSED gpointer data)
{
	//ajouter une status pour une action
	g_simple_action_set_state(action, state);
}
static void activate_clbk(GSimpleAction* action, GVariant* parameter, G_GNUC_UNUSED gpointer data)
{
	GVariant* action_state = NULL;
	gchar* state_atr = NULL;
	//demande de changement de status à une valeur
	g_action_change_state(G_ACTION(action), parameter);
	//récupérer le status actuel
	action_state = g_action_get_state(G_ACTION(action));
	state_atr = g_variant_print(action_state, TRUE);

	g_print("\nle %s  a ete change a : %s", g_action_get_name(G_ACTION(action)), state_atr);
	g_free(state_atr);
	g_variant_unref(action_state);
}
static void quit_activated(GSimpleAction* action, GVariant* parameter, GApplication* application) {
	g_application_quit(application);
}

static void check_clbk(GSimpleAction* action, G_GNUC_UNUSED GVariant* parameter,  gpointer data)
{
	GVariant* action_stat;
	action_stat = g_action_get_state(G_ACTION(action));
	const gboolean flag = g_variant_get_boolean(action_stat);

	if (flag)
	{
		g_print("\n%s - OFF", g_action_get_name(G_ACTION(action)));
		g_simple_action_set_state(action, g_variant_new_boolean(FALSE));
	}
	else
	{
		g_print("\n%s - ON", g_action_get_name(G_ACTION(action)));
		g_simple_action_set_state(action, g_variant_new_boolean(TRUE));
	}
}

static void creer_actions(GtkApplication* app)
{
	static const GActionEntry entries[] =
	{
		//***Les actions
		{"new",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"open",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"save",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"saveas",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"quit",quit_activated,NULL,NULL,NULL,{0,0,0}},
		{"sec1",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"sec2",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"sectionItem2",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"copy",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"cut",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"paste",action_clbk,NULL,NULL,NULL,{0,0,0}},


		//****actions de volume
		{"volume",activate_clbk,"s","'haut'",state_clbk,{0,0,0}},
		{"bas",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"haut",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"medium",action_clbk,NULL,NULL,NULL,{0,0,0}},
		{"mute",action_clbk,NULL,NULL,NULL,{0,0,0}},

		//****actions pour video
		{"fullHD",check_clbk,NULL,"false",NULL,{0,0,0}},
		{"threeD",check_clbk,NULL,"true",NULL,{0,0,0}},
		{"fourK", check_clbk,NULL,"false",NULL,{0,0,0}}
	};
	g_action_map_add_action_entries(G_ACTION_MAP(app), entries, G_N_ELEMENTS(entries), app);
}


static void create_menu_item(GMenu* menu, Item* item1, GtkApplication* app)
{
	/****(NULL(1)=> pas de label pour le menu)
		 (NULL(2)=> pas d'action pour le menu)
	****/

		do {
			item1->item = g_menu_item_new(item1->label, item1->action);

				if (item1->icon)
				{
					//***meth2 pour inserer une icone
					GIcon* buffer_icone;
					buffer_icone = g_themed_icon_new(item1->icon);
					g_menu_item_set_icon(item1->item, buffer_icone);
				}

				if (item1->accel)
				{
					g_menu_item_set_attribute(item1->item, "accel", "s", item1->accel, NULL);
				}

				if (item1->target && item1->target_genre)
				{
					if (item1->target_genre=="checkbox")

						g_menu_item_set_attribute(item1->item, G_MENU_ATTRIBUTE_TARGET, NULL, TRUE, NULL);

					else g_menu_item_set_attribute(item1->item, G_MENU_ATTRIBUTE_TARGET, "s", item1->target, NULL);
				}
				g_menu_append_item(menu, item1->item);
				g_object_unref(item1->item);
				item1 = item1->suiv;
		} while (item1);
}



static void create_section(GMenu *pere,SubSecMenu *section, GtkApplication* app)
{
	section->mn = g_menu_new();
	create_menu_item(section->mn, section->Itm,app);
	g_menu_insert_section(pere, section->pos, section->name, G_MENU_MODEL(section->mn));
	g_object_unref(section->mn);
}

static void creer_menu( GMenu* menubar,SubSecMenu *menu1, GtkApplication *app)
{
	menu1->mn = g_menu_new();

	if(menu1->Itm)
	create_menu_item(menu1->mn, menu1->Itm,app);

	SubSecMenu* ptcrt = menu1->desc;

	while (ptcrt)
	{
		if (ptcrt->Smenu_genre == "Section")
		{
			create_section(ptcrt->pere->mn,ptcrt,app);
	    }
		else
		{
			ptcrt->mn = g_menu_new();
			create_menu_item(ptcrt->mn, ptcrt->Itm, app);
			g_menu_insert_submenu(ptcrt->pere->mn, ptcrt->pos, ptcrt->name, G_MENU_MODEL(ptcrt->mn));
		}
		ptcrt = ptcrt->desc;
	}
	g_menu_append_submenu(menubar, menu1->name, G_MENU_MODEL(menu1->mn));
	g_object_unref(menu1->mn);
}



static void create_action(GtkApplication* app, Item* item1)
{
	do {
		if (!item1->item) printf("\nERROOR");
		else
		{
			//***ajouter une action pour l'article
			if (item1->action[0] != '\0')
			{
				printf("\n l'action %s", item1->action);
				GSimpleAction* act = g_simple_action_new(item1->action,NULL);
				g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act));
				g_signal_connect(act, "activate", G_CALLBACK(action_clbk), NULL);
			}
			item1 = item1->suiv;
		}
	} while (item1);
}

Item* creer_cellule_item(const gchar* label, const gchar* icon,const gchar*action,
	                     const gchar *accel,const gchar *target,const gchar *target_genre
	)
{
	Item* nv = (Item*)g_malloc(sizeof(Item));

	if (!nv)
	{
		printf("\nErreur d'allocation mémoire ");
		exit(0);
	}
	nv->label = label;
	nv->icon = icon;
	nv->action = action;
	nv->accel = accel;
	nv->target = target;
	nv->target_genre = target_genre;
	nv->suiv = NULL;
	return ((Item*)nv);
}

SubSecMenu* creer_noeud_SubSecMenu(const gchar* name ,const gchar *sgenre, SubSecMenu * pere)
{
	SubSecMenu* nv = (SubSecMenu*)g_malloc(sizeof(SubSecMenu));

	if (!nv)
	{
		printf("\nErreur d'allocation mémoire ");
		exit(0);
	}
	nv->name = name;
	nv->Smenu_genre = sgenre;
	nv->pere = pere;
	nv->Itm = NULL;
	nv->desc = NULL;
	return ((SubSecMenu*)nv);
}


GtMenu* allocation_memoire_menu()
{
	GtMenu* nv = (GtMenu*)g_malloc(sizeof(GtMenu));
	if (!nv)
	{
		printf("\nErreur d'allocation mémoire ");
		exit(0);
	}

	nv->menu = NULL;
	return ((GtMenu*)nv);
}

Item* ajouter_cellule_item(Item* item1, const gchar* label, const gchar* icon, const gchar* action,
	const gchar* accel, const gchar* target, const gchar* target_genre)
{
	Item* nv = creer_cellule_item(label, icon, action, accel, target, target_genre);

	if (!item1)
		return ((Item*)nv);
	Item* ptcrt = item1;
	while (ptcrt->suiv)
		ptcrt = ptcrt->suiv;
	ptcrt->suiv = nv;
	return ((Item*)item1);
}

SubSecMenu* ajouter_subsecmenu(SubSecMenu *menu1, SubSecMenu* smenu)
{
	if (!menu1->desc)
	{
		menu1->desc = smenu;
		return ((SubSecMenu*)menu1);
	}
	SubSecMenu* ptcrt = menu1;
	while (ptcrt->desc)
		ptcrt = ptcrt->desc;
	ptcrt->desc = smenu;
	return ((SubSecMenu*)menu1);
}

void container_add(GtkContainer *contenaire,GtkWidget *widget)
{
    gtk_container_add(GTK_CONTAINER(contenaire), widget);
}

void box_add(GtkBox *box, GtkWidget *widget,gboolean expand,gboolean fill, guint padding)
{
    gtk_box_pack_start(GTK_BOX(box),widget,expand,fill,padding);
}

void cacher_fenetre(GtkWidget *widget)
{
    gtk_widget_hide(GTK_WIDGET(widget));
}

gchar *cssStartButton="button {font-family: Lucida Console; font-weight: 900;background-image: image(#cea152);color: black; border-width: 2px; border-color: white;}";
gchar *cssStartButtonHover="button:hover {font-family: Lucida Console; font-weight: 900;background-image: image(white); box-shadow: inset 5em 0 0 0 white, inset -5em 0 0 0 white; color: #cea152; border-width: 2px; border-color: black;}";
gchar *cssStartFrame="frame{background-image: image(#cea152);font-family: Lucida Console; font-weight: 900;color: black;border-style:solid; border-width: 2px; border-color:  white;padding: 5px;border-width: 5px;border-style: solid;border-radius: 4px;}";
gchar *cssWindowStart="window {background-image: url('images/background_start.png');background-size: cover;background-repeat: no-repeat;background-position: center;}";
gchar *cssWindowGame="window {background-image: url('images/background_wood.jpg');background-size: cover;background-repeat: no-repeat;background-position: center;}";
gchar *cssWindowGameOver="window {background-image: image(#cea152);font-family: Lucida Console; font-weight: 900;color: black;border-style:solid; border-width: 2px; border-color:  white;padding: 5px;border-width: 5px;border-style: solid;border-radius: 4px;}";
gchar *cssGridBrown="grid{box-shadow: inset 0px 5px 10px 0px rgba(0, 0, 0, 0.5);border-width:1px;border-color: black;background-color:saddlebrown}";
gchar *cssGridWhite="grid{box-shadow: inset 0px 5px 10px 0px rgba(0, 0, 0, 0.5);border-width:1px;border-color: black;background-color:NavajoWhite}";
gchar *cssKingBeige="button {background-image: url('images/checker_king_beige.png');background-size: contain;background-repeat: no-repeat;background-position: center;border-radius: 50px;box-shadow: inset 0px 5px 10px 0px rgba(0, 0, 0, 0.5);border-width:1px;border-color: black;}";
gchar *cssKingBlack="button {background-image: url('images/checker_king_black.png');background-size: contain;background-repeat: no-repeat;background-position: center;border-radius: 50px;box-shadow: inset 0px 5px 10px 0px rgba(0, 0, 0, 0.5);border-width:1px;border-color: black;}";
gchar *cssGrid="grid{background-color:#462100; margin:5px; padding: 10px; padding-color: black;}";
gchar *cssGridRed="grid{box-shadow: inset 0px 5px 10px 0px rgba(0, 0, 0, 0.5);border-width:1px;border-color: black;background-color: #FF3131}";
gchar *cssPionBlack="button {background-image: url('images/checker_black.png');background-size: contain;background-repeat: no-repeat;background-position: center;border-radius: 50px;box-shadow: inset 0px 5px 10px 0px rgba(0, 0, 0, 0.5);border-width:1px;border-color: black;}";
gchar *cssPionBeige="button {background-image: url('images/checker_beige.png');background-size: contain;background-repeat: no-repeat;background-position: center;border-radius: 50px;box-shadow: inset 0px 5px 10px 0px rgba(0, 0, 0, 0.5);border-width:1px;border-color: black;}";
gchar *YouWin="label {color: green; font-family: Lucida Console; font-weight: 900;font-size: 40px;text-align: center; animation: neonEffect 2s linear infinite;}";
gchar *YouLose="label {color: red; font-family: Lucida Console; font-weight: 900;font-size: 40px;}";

#endif // MACROSGTK_H_INCLUDED
