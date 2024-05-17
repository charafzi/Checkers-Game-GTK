#include "Game.h"

static void start_game(GtkButton *button, gpointer user_data)
{
    ChoixJoueur *data = (ChoixJoueur *)user_data;
    GtkApplication *app = GTK_APPLICATION(data->app);
    cacher_fenetre(data->window);
    bouton *quitter;
    Wind fen;   // fenetre du jeu
    Game *game; //données du jeu


	/**Fentre du Jeu **/
	init_window(&fen,"Jeu de Dames","images/icon.png",cssWindowGame,700,700,GTK_WINDOW_TOPLEVEL,GTK_WIN_POS_CENTER);
	fen.window = create_window(fen,app);


	/**Fentre scroll**/
	scroll_wind scrol;
	init_scrol(&scrol);
	scrol.scrolled_window = create_scrol(scrol);


	quitter=initialiser_Bouton(1,NULL,NULL,NULL,"_Quitter","Q",1,NULL,20,40,0,0);
	quitter=create_simpleButton(quitter);
	//ajout du bouton au headerBar
    GtkWidget *window_header_bar = gtk_window_get_titlebar(GTK_WINDOW(fen.window));
    gtk_header_bar_pack_start(GTK_HEADER_BAR(window_header_bar), quitter->button);
    g_signal_connect(G_OBJECT(quitter->button),"clicked",G_CALLBACK(quit_callback2),fen.window);
	/**Creation de la table du jeu**/
	game=create_checkersBoard(scrol,data->choixCol,data->choixDiff,data->choixGame);
	game->window=fen.window;
	game->app=data->app;

	container_add(GTK_CONTAINER(fen.window), scrol.scrolled_window);
	gtk_widget_show_all(fen.window);

	//fonction du tour initialement c'est le tour du joueur (round==0)
    tour_signal(game);

    if(data->choixGame==3) g_timeout_add_seconds(8, tour_signal, game);
    else g_timeout_add_seconds(2, tour_signal, game);
    gtk_main();
}

static void activate(GtkApplication* app, gpointer user_data)
{
    bouton *jouer, *quitter, *radio[5];
    Box *box[5];
    Frame *frame[3];
    Align align; align.x=0.5,align.y=0.5;
    Scale *scale;
    Wind fen;
    const char *labels[] = {"Facile", "Moyen", "Difficile"};
    ChoixJoueur *data=(ChoixJoueur*)malloc(sizeof(ChoixJoueur));
    if(!data)
    {
        printf("\nErreur Allocation memoire pour ChoixJoueur");
        exit(-1);
    }

    /** Fenetre d'acceuil **/
	init_window(&fen,"Jeu de Dames","images/icon.png",cssWindowStart,700,700,GTK_WINDOW_TOPLEVEL,GTK_WIN_POS_CENTER);
	//fen.window = gtk_application_window_new(app);
	fen.window = create_window(fen,app);

	data->app=app;
	data->window=fen.window;

	jouer=initialiser_Bouton(1,NULL,NULL,NULL,"_Jouer","J",1,NULL,20,40,0,0);
	jouer=create_simpleButton(jouer);
	quitter=initialiser_Bouton(1,NULL,NULL,NULL,"_Quitter","Q",1,NULL,20,40,0,0);
	quitter=create_simpleButton(quitter);
	scale=init_scale(NULL,NULL,GTK_ORIENTATION_HORIZONTAL,GTK_POS_TOP,1,3,1,1,TRUE);
    scale=create_scale(scale,labels,3);

    frame[0] = initialiser_Frame(NULL,"Faire     le     choix   de  la   couleur     :\n","f1",0.5,0.5,2,0,0,0,0);
    frame[0] = create_Frame(frame[0]);
    frame[1] = initialiser_Frame(NULL,"Faire     le  choix   de  la  difficulte      :\n","f2",0.5,0.5,1,0,0,0,0);
    frame[1] = create_Frame(frame[1]);
    frame[2] = initialiser_Frame(NULL,"Faire     le  choix   du         mode         :\n","f2",0.5,0.5,1,0,0,0,0);
    frame[2] = create_Frame(frame[2]);

    box[0]  =   initialiser_Box(NULL,NULL,'V',FALSE,10,150,0,0,0,0);
	box[0]  =   create_Box(box[0]);
	box[1]  =   initialiser_Box(NULL,NULL,'V',TRUE,20,5,0,0,0,0);
	box[1]  =   create_Box(box[1]);
	box[2]  =   initialiser_Box(NULL,NULL,'H',TRUE,20,5,0,0,0,0);
	box[2]  =   create_Box(box[2]);
	box[3]  =   initialiser_Box(NULL,NULL,'H',TRUE,20,5,0,0,0,0);
	box[3]  =   create_Box(box[3]);
	box[4]  =   initialiser_Box(NULL,NULL,'H',TRUE,20,5,0,0,0,0);
	box[4]  =   create_Box(box[4]);

	radio[0] = initialiser_Bouton(3,NULL,NULL,NULL,"Noir","rb1",1,NULL,5,5,0,0);
    radio[0] = create_radioButton(radio[0]);
    radio[1] = initialiser_Bouton(3,NULL,radio[0]->button,NULL,"Blanc","rb2",1,NULL,5,5,0,0);
    radio[1] = create_radioButton(radio[1]);
    radio[2] = initialiser_Bouton(3,NULL,NULL,NULL,"Joueur VS Joueur","rb3",0,NULL,5,5,0,0);
    radio[2] = create_radioButton(radio[2]);
    radio[3] = initialiser_Bouton(3,NULL,radio[2]->button,NULL,"Machine VS Joueur","rb4",0,NULL,5,5,0,0);
    radio[3] = create_radioButton(radio[3]);
    radio[4] = initialiser_Bouton(3,NULL,radio[2]->button,NULL,"Machine VS Machine","rb5",0,NULL,5,5,0,0);
    radio[4] = create_radioButton(radio[4]);

    box_add(box[3]->box,radio[0]->button,FALSE,FALSE,0);
    box_add(box[3]->box,radio[1]->button,FALSE,FALSE,0);
    box_add(box[4]->box,radio[2]->button,FALSE,FALSE,0);
    box_add(box[4]->box,radio[3]->button,FALSE,FALSE,0);
    box_add(box[4]->box,radio[4]->button,FALSE,FALSE,0);
    container_add(GTK_CONTAINER(frame[0]->frame), box[3]->box);
    container_add(GTK_CONTAINER(frame[2]->frame), box[4]->box);
    container_add(GTK_CONTAINER(frame[1]->frame), scale->scale);


    add_css(jouer->button,cssStartButton);
    add_css(jouer->button,cssStartButtonHover);
    add_css(quitter->button,cssStartButton);
    add_css(quitter->button,cssStartButtonHover);
    add_css(frame[0]->frame,cssStartFrame);
    add_css(frame[1]->frame,cssStartFrame);
    add_css(frame[2]->frame,cssStartFrame);

    g_signal_connect(G_OBJECT(radio[0]->button), "toggled", G_CALLBACK(bouton_radio_signal), data);
    g_signal_connect(G_OBJECT(radio[1]->button), "toggled", G_CALLBACK(bouton_radio_signal), data);
    g_signal_connect(G_OBJECT(radio[2]->button), "toggled", G_CALLBACK(bouton_radio_choix), data);
    g_signal_connect(G_OBJECT(radio[3]->button), "toggled", G_CALLBACK(bouton_radio_choix), data);
    g_signal_connect(G_OBJECT(radio[4]->button), "toggled", G_CALLBACK(bouton_radio_choix), data);

    //choix par défaut
    data->choixDiff=1;
    data->choixCol=1;
    data->choixGame=1;
    g_signal_connect_swapped(G_OBJECT(quitter->button),"clicked",G_CALLBACK(quit_callback),app);
    g_signal_connect(G_OBJECT(jouer->button),"clicked",G_CALLBACK(start_game),data);
    g_signal_connect(scale->scale, "value-changed", G_CALLBACK(scale_value), data);

	box_add(box[0]->box,jouer->button,FALSE,FALSE,0);
	box_add(box[0]->box,frame[0]->frame,FALSE,FALSE,0);
	box_add(box[0]->box,frame[1]->frame,FALSE,FALSE,0);
	box_add(box[0]->box,frame[2]->frame,FALSE,FALSE,0);
	box_add(box[0]->box,quitter->button,FALSE,FALSE,0);

	box_add(box[2]->box,box[0]->box,FALSE,FALSE,0);

    align.align=centrer_widget(box[2]->box,align.x,align.y);
	container_add(fen.window,align.align);
	gtk_widget_show_all(fen.window);

}



int main(int argc, char** argv)
{
	GtkApplication* app;
	int status;

	app = gtk_application_new("org.gtk.example", 0);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);


	return status;
}

