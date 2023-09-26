#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 2
#define CANTIDAD_INICIAL_HAMBURGUESAS 20

int cantidad_restante_hamburguesas = CANTIDAD_INICIAL_HAMBURGUESAS;
int turno = 0;

void *comer_hamburguesa(void *tid) {
    int mi_turno = (int)tid;

    while (1) {
        while (turno != mi_turno) {
            // Espera hasta que sea su turno
        }

        if (cantidad_restante_hamburguesas > 0) {
            // Región crítica: Comer una hamburguesa
            printf("Hola! soy el hilo(comensal) %d, me voy a comer una hamburguesa! Quedan %d hamburguesas\n", mi_turno, cantidad_restante_hamburguesas);
            cantidad_restante_hamburguesas--;
        } else {
            printf("SE TERMINARON LAS HAMBURGUESAS :( \n");
            pthread_exit(NULL);
        }

        // Cambiar el turno
        turno = 1 - turno;

        // Región no crítica: Permitir que el otro hilo avance
        // Aquí podrías agregar algún tipo de espera para simular el cambio de turno
    }
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i, ret;

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        printf("Hola!, soy el hilo principal. Estoy creando el hilo %d\n", i);
        status = pthread_create(&threads[i], NULL, comer_hamburguesa, (void *)i);
        if (status != 0) {
            printf("Algo salió mal al crear el hilo. Código de error: %d\n", status);
            exit(-1);
        }
    }

    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        void *retval;
        ret = pthread_join(threads[i], &retval);
    }

    pthread_exit(NULL);
}