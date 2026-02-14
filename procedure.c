#include <stdio.h>

#include "procedure.h"

void inizializza(MonitorPortafoglio * m, int quantita_iniziale, int valore_iniziale) {

    /* TBD: Inizializzare l'oggetto monitor */

    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->acquisto, NULL);
    pthread_cond_init(&m->vendita, NULL);

    m->quantita = quantita_iniziale;
    m->valore = valore_iniziale;

}

void termina(MonitorPortafoglio * m) {

    /* TBD: De-inizializzare l'oggetto monitor */

    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->acquisto);
    pthread_cond_destroy(&m->vendita);

}

void acquisto(MonitorPortafoglio * m, int quantita, int prezzo) {

    /* TBD: Aggiungere la sincronizzazione */

    pthread_mutex_lock(&m->mutex);

    while(prezzo < m->valore){

        pthread_cond_wait(&m->acquisto, &m->mutex);

    }

    m->quantita += quantita;

    pthread_cond_broadcast(&m->vendita);

    pthread_mutex_unlock(&m->mutex);

}

void vendita(MonitorPortafoglio * m, int quantita, int prezzo) {

    /* TBD: Aggiungere la sincronizzazione */

    pthread_mutex_lock(&m->mutex);

    while(prezzo > m->valore || m->quantita < quantita){

        pthread_cond_wait(&m->vendita, &m->mutex);

    }

    m->quantita -= quantita;

    pthread_mutex_unlock(&m->mutex);

}

void aggiorna(MonitorPortafoglio * m, int valore) {

    /* TBD: Aggiungere la sincronizzazione */

    pthread_mutex_lock(&m->mutex);

    m->valore = valore;

    pthread_cond_broadcast(&m->acquisto);
    pthread_cond_broadcast(&m->vendita);

    pthread_mutex_unlock(&m->mutex);
}

int leggi(MonitorPortafoglio * m) {

    /* TBD: Aggiungere la sincronizzazione */

    pthread_mutex_lock(&m->mutex);

    int valore;

    valore = m->valore;

    pthread_mutex_unlock(&m->mutex);

    return valore;
}
