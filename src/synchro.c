#include "synchro.h"
#include "ensitheora.h"

bool fini;
extern int tex_iwri;
extern int tex_iaff;
extern int tex_dispo;
extern int tex_pretes;

/* les variables pour la synchro, ici */

// Mutexes et Conditions initialisés statiquement
pthread_mutex_t mutex_hashmap = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_fenetre = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cons_fenetre = PTHREAD_COND_INITIALIZER;
pthread_cond_t prod_fenetre = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex_texture = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cons_texture = PTHREAD_COND_INITIALIZER;
pthread_cond_t prod_texture = PTHREAD_COND_INITIALIZER;

/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&mutex_fenetre);
    printf("\nsynchro.c ---> envoiTailleFenetre");
    
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;

    pthread_cond_signal(&cons_fenetre);
    
    pthread_mutex_unlock(&mutex_fenetre);
    
}

void attendreTailleFenetre() {
    pthread_mutex_lock(&mutex_fenetre);
    printf("\nattenteTailleFenetre");

    while (windowsx == 0 && windowsy == 0)
	pthread_cond_wait(&cons_fenetre,&mutex_fenetre);

    pthread_mutex_unlock(&mutex_fenetre);
}

void signalerFenetreEtTexturePrete() {
    pthread_mutex_lock(&mutex_fenetre);
    printf("\nsignalerFenetreEtTexturePrete");
 
    pthread_cond_signal(&prod_fenetre);

    pthread_mutex_unlock(&mutex_fenetre);

}

void attendreFenetreTexture() {
    pthread_mutex_lock(&mutex_fenetre);
    printf("\nattendreFenetreTexture");

    while (tex_pretes != 1)
	pthread_cond_wait(&prod_fenetre,&mutex_fenetre);

    pthread_mutex_unlock(&mutex_fenetre);
    
}

void debutConsommerTexture() {
    pthread_mutex_lock(&mutex_texture);
    printf("\ndebutConsommerTexture");
    
    while (tex_dispo == 0){
	pthread_cond_wait(&cons_texture,&mutex_texture);
    }
    
    pthread_mutex_unlock(&mutex_texture);
}

void finConsommerTexture() {
    pthread_mutex_lock(&mutex_texture);
    printf("\nfinConsommerTexture");
    
    pthread_cond_signal(&prod_texture);

    pthread_mutex_unlock(&mutex_texture);
}


void debutDeposerTexture() {
    pthread_mutex_lock(&mutex_texture);
    printf("\ndebutDeposerTexture");
    
    while (tex_dispo == NBTEX ){
	pthread_cond_wait(&prod_texture,&mutex_texture);
    }
    
    pthread_mutex_unlock(&mutex_texture);    
}

void finDeposerTexture() {
    pthread_mutex_lock(&mutex_texture);
    printf("\nfinDeposerTexture");
    
    pthread_cond_signal(&cons_texture);

    pthread_mutex_unlock(&mutex_texture);
}
