#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#include "stream_common.h"
#include "oggstream.h"
#include "synchro.h"

pthread_t *taffichage = NULL;

int main(int argc, char *argv[]) {
    int res;

    pthread_t *taudio = NULL , *tvideo = NULL;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);

    // start the two stream readers
    pthread_create(taudio, NULL, vorbisStreamReader, argv[1]);
    pthread_create(tvideo, NULL, theoraStreamReader, argv[1]);

    // wait audio thread
    pthread_join(*taudio, NULL);

    // 1 seconde de garde pour le son,
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués
    pthread_cancel(*taffichage);
    pthread_cancel(*tvideo);

    // attendre les 2 threads videos
    pthread_join(*taffichage, NULL);
    pthread_join(*tvideo, NULL);

    exit(EXIT_SUCCESS);
}
