
#include "experiments.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{

    srand(time(NULL));


    printf("iniciando experimentos base...\n");

    runBaseExperiments();

    printf("experimentos base finalizados.\n");


    printf("iniciando experimento sequential access...\n");

    runSequentialExperiment();

    printf("experimento sequential finalizado.\n");


    printf("iniciando experimento working set...\n");

    runWorkingSetExperiment();

    printf("experimento working set finalizado.\n");


    printf("todos los experimentos terminaron correctamente.\n");


    return 0;
}