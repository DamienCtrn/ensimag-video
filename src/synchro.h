#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdbool.h>
#include <pthread.h>
#include "ensitheora.h"

extern bool fini;


/* Les extern des variables pour la synchro ici */

extern pthread_mutex_t mutex_hashmap;

extern pthread_mutex_t mutex_fenetre;
extern pthread_cond_t cond_fenetre;

extern pthread_mutex_t mutex_texture;
extern pthread_cond_t cond_texture;

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
