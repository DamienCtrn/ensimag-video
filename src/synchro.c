#include "synchro.h"
#include "ensitheora.h"

bool fini;

/* les variables pour la synchro, ici */

// Mutexes et Conditions initialisés statiquement
pthread_mutex_t mutex_hashmap = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_fenetre = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_fenetre = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex_texture = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_texture = PTHREAD_COND_INITIALIZER;

/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&mutex_fenetre);
}

void attendreTailleFenetre() {

}

void signalerFenetreEtTexturePrete() {
}

void attendreFenetreTexture() {
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
