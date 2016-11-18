#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdbool.h>
#include <pthread.h>
#include "ensitheora.h"

extern bool fini;

// Déclaration des variables globales windowsx et windowsy ????
// extern int windowsx;
// extern int windowsy;

/* Les extern des variables pour la synchro ici */

extern pthread_mutex_t mutex_hashmap;

extern pthread_mutex_t mutex_fenetre;
extern pthread_cond_t cons_fenetre;
extern pthread_cond_t prod_fenetre;

extern pthread_mutex_t mutex_texture;
extern pthread_cond_t cons_texture;
extern pthread_cond_t prod_texture;

/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

#endif
