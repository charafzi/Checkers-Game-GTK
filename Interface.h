#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "macrosGTK.h"

typedef struct
{
    GtkApplication *app; //Application du qui contient la fenetre du jeu
    GtkWindow *window;   //La fenetre du jeu
    char choixCol;       //Choix de la couleur du joueur
    gdouble  choixDiff;  //Choix de la difficulte
    gint choixGame;      /* 1: Joueur VS Joueur
                            2:  Machine VS Joueur
                            3: Machine VS Machine
                         */
}ChoixJoueur;

void quit_callback2(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = GTK_WIDGET(data);
    gtk_window_close(GTK_WINDOW(window));
}

static void bouton_radio_signal(GtkToggleButton *button, gpointer user_data)
{
    ChoixJoueur *data = (ChoixJoueur *)user_data;
    if (gtk_toggle_button_get_active(button))
    {
        const gchar *label = gtk_button_get_label(GTK_BUTTON(button));
        if (g_strcmp0(label, "Blanc") == 0)
        {
            data->choixCol= 'B';
        }
        else if (g_strcmp0(label, "Noir") == 0)
        {
            data->choixCol= 'N';
        }
        g_print("Choix : %c\n", data->choixCol);
    }
}

static void bouton_radio_choix(GtkToggleButton *button, gpointer user_data)
{
    ChoixJoueur *data = (ChoixJoueur *)user_data;
    if (gtk_toggle_button_get_active(button))
    {
        const gchar *label = gtk_button_get_label(GTK_BUTTON(button));
        if (g_strcmp0(label, "Joueur VS Joueur") == 0)
        {
            data->choixGame=1;
        }
        else if (g_strcmp0(label, "Machine VS Joueur") == 0)
        {
            data->choixGame=2;
        }
        else
        {
            data->choixGame=3;
        }
        g_print("Choix Mode : %d\n", data->choixGame);
    }
}

void scale_value(GtkRange *range, gpointer user_data)
{
    ChoixJoueur *data = (ChoixJoueur *)user_data;
    gdouble value = gtk_range_get_value(range);
    data->choixDiff=value;
    g_print("\nScale value: %.2f\n", data->choixDiff);
}


#endif // INTERFACE_H_INCLUDED
