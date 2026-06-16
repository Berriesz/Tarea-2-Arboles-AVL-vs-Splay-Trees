//
// Created by fabia on 15/6/2026.
//


#include "experiments.h"

#include "avl_tree/avl.h"
#include "splay_tree/splay.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


/* valor escogido para la tarea */

#define C 1


/* cantidad de tamaños utilizados */

#define NUM_N 5


/* n grande para la sección 7.3 */

#define LARGE_N (1<<25)


/* tamaños solicitados en el enunciado */

int Ns[NUM_N] =
{
    1024,
    2048,
    4096,
    8192,
    16384
};


/**
 * obtiene el tiempo actual de ejecución.
 *
 * retorna:
 * - tiempo en segundos.
 */
double getTime()
{
    return (double) clock() / CLOCKS_PER_SEC;
}


/**
 * compara dos números enteros sin signo.
 *
 * parámetros:
 * - a: primer elemento.
 * - b: segundo elemento.
 *
 * retorna:
 * - -1 si a < b.
 * - 1 si a > b.
 * - 0 si son iguales.
 */
int compareUInt(
        const void* a,
        const void* b
){

    unsigned int x =
            *(unsigned int*) a;

    unsigned int y =
            *(unsigned int*) b;

    if(x < y)
    {
        return -1;
    }

    if(x > y)
    {
        return 1;
    }

    return 0;
}


/**
 * genera un dataset uniforme de n elementos.
 *
 * parámetros:
 * - data: arreglo donde se guardarán los datos.
 * - n: cantidad de elementos.
 *
 * retorna:
 * - no retorna ningún valor.
 */
void generateDataset(
        unsigned int* data,
        int n
){

    for(int i=0;i<n;i++)
    {
        unsigned int a = rand();

        unsigned int b = rand();

        data[i] = (a<<16)^b;
    }

}


/**
 * ordena un dataset de menor a mayor.
 *
 * parámetros:
 * - data: arreglo a ordenar.
 * - n: cantidad de elementos.
 *
 * retorna:
 * - no retorna ningún valor.
 */
void sortDataset(
        unsigned int* data,
        int n
){

    qsort(

        data,

        n,

        sizeof(unsigned int),

        compareUInt

    );

}


/**
 * construye una distribución acumulada
 * basada en una distribución exponencial.
 *
 * parámetros:
 * - cumulative: arreglo acumulado.
 * - n: cantidad de elementos.
 * - lambda: parámetro de sesgo.
 *
 * retorna:
 * - no retorna ningún valor.
 */
void buildBiasedDistribution(
        double* cumulative,
        int n,
        double lambda
){

    double total = 0;

    for(int i=0;i<n;i++)
    {
        total += exp(-lambda*i);
    }

    double accumulated = 0;

    for(int i=0;i<n;i++)
    {
        accumulated +=
            exp(-lambda*i)
            /
            total;

        cumulative[i] =
            accumulated;
    }

}


/**
 * selecciona un índice utilizando
 * una distribución sesgada.
 *
 * parámetros:
 * - cumulative: distribución acumulada.
 * - n: cantidad de elementos.
 *
 * retorna:
 * - índice seleccionado.
 */
int sampleBiased(
        double* cumulative,
        int n
){

    double r =

        (double)

        rand()

        /

        RAND_MAX;

    for(int i=0;i<n;i++)
    {
        if(r <= cumulative[i])
        {
            return i;
        }
    }

    return n-1;
}






/**
 * ejecuta uno de los cuatro escenarios base.
 *
 * parámetros:
 * - csv: archivo donde se guardarán los resultados.
 * - data: dataset asociado al n actual.
 * - n: tamaño del dataset.
 * - ordered: tipo de inserción.
 *      0 = aleatoria.
 *      1 = ordenada.
 * - biased: tipo de búsqueda.
 *      0 = uniforme.
 *      1 = sesgada.
 *
 * retorna:
 * - no retorna ningún valor.
 */
void runScenario(
        FILE* csv,

        unsigned int* data,

        int n,

        int ordered,

        int biased
){

    unsigned int* insertData =

            malloc(
            n*sizeof(unsigned int)
            );

    for(int i=0;i<n;i++)
    {
        insertData[i] = data[i];
    }


    if(ordered)
    {
        sortDataset(
                insertData,
                n
        );
    }


    AVLNode* avl = NULL;

    SPLAYNode* splay = NULL;


    double lambda = 0.01;


    double* cumulative =

            malloc(
            n*sizeof(double)
            );


    buildBiasedDistribution(

            cumulative,

            n,

            lambda

    );


    double avlInsert;

    double avlSearch;

    double splayInsert;

    double splaySearch;


    double t0;

    double t1;


    /*
     * inserción avl
     */

    t0 = getTime();

    for(int i=0;i<n;i++)
    {
        avl =

        insert_avl(

            avl,

            insertData[i]

        );
    }

    t1 = getTime();

    avlInsert =

            t1 - t0;


    /*
     * búsqueda avl
     */

    int m = 10*C*n;


    t0 = getTime();

    for(int i=0;i<m;i++)
    {
        int idx;


        if(biased)
        {
            idx =

            sampleBiased(

                cumulative,

                n

            );
        }

        else
        {
            idx =

            rand()%n;
        }


        search_avl(

            avl,

            insertData[idx]

        );

    }

    t1 = getTime();

    avlSearch =

            t1 - t0;


    /*
     * inserción splay
     */

    t0 = getTime();

    for(int i=0;i<n;i++)
    {
        splay =

        insert_splay(

            splay,

            insertData[i]

        );
    }

    t1 = getTime();

    splayInsert =

            t1 - t0;


    /*
     * búsqueda splay
     */

    t0 = getTime();

    for(int i=0;i<m;i++)
    {
        int idx;


        if(biased)
        {
            idx =

            sampleBiased(

                cumulative,

                n

            );
        }

        else
        {
            idx =

            rand()%n;
        }


        int found;


        splay =

        search_splay(

            splay,

            insertData[idx],

            &found

        );

    }

    t1 = getTime();

    splaySearch =

            t1 - t0;


    /*
     * guardar resultados
     */

    fprintf(

        csv,

        "%d,%d,%d,%lf,%lf,%lf,%lf\n",

        n,

        ordered,

        biased,

        avlInsert,

        avlSearch,

        splayInsert,

        splaySearch

    );


    /*
     * liberar memoria
     */

    freeAVL(avl);

    freeSplay(splay);

    free(cumulative);

    free(insertData);

}



/**
 * ejecuta los cuatro escenarios base
 * solicitados en la sección 7.2.
 *
 * retorna:
 * - no retorna ningún valor.
 */
void runBaseExperiments()
{

    FILE* csv =

    fopen(

        "base_results.csv",

        "w"

    );


    fprintf(

        csv,

"N,ordered,biased,avl_insert,avl_search,splay_insert,splay_search\n"

    );


    for(int i=0;i<NUM_N;i++)
    {

        int n = Ns[i];


        unsigned int* dataset =

        malloc(

            n*sizeof(unsigned int)

        );


        generateDataset(

            dataset,

            n

        );


        /*
         * escenario a
         */

        runScenario(

            csv,

            dataset,

            n,

            0,

            0

        );


        /*
         * escenario b
         */

        runScenario(

            csv,

            dataset,

            n,

            0,

            1

        );


        /*
         * escenario c
         */

        runScenario(

            csv,

            dataset,

            n,

            1,

            0

        );


        /*
         * escenario d
         */

        runScenario(

            csv,

            dataset,

            n,

            1,

            1

        );


        free(dataset);

    }


    fclose(csv);

}





/**
 * ejecuta el experimento asociado al
 * sequential access theorem.
 *
 * retorna:
 * - no retorna ningún valor.
 */
void runSequentialExperiment()
{

    FILE* csv =

    fopen(

        "sequential_results.csv",

        "w"

    );


    fprintf(

        csv,

        "m,avl_time,splay_time\n"

    );


    unsigned int* data =

    malloc(

        LARGE_N*sizeof(unsigned int)

    );


    generateDataset(

        data,

        LARGE_N

    );


    sortDataset(

        data,

        LARGE_N

    );


    AVLNode* avl = NULL;

    SPLAYNode* splay = NULL;


    for(int i=0;i<LARGE_N;i++)
    {

        avl =

        insert_avl(

            avl,

            data[i]

        );


        splay =

        insert_splay(

            splay,

            data[i]

        );

    }


    for(int k=1;k<=10;k++)
    {

        int m =

        (k*LARGE_N)

        /100;


        int step =

        LARGE_N

        /m;


        double t0;

        double t1;

        double avlTime;

        double splayTime;


        /*
         * búsquedas avl
         */

        t0 = getTime();


        int pos = 0;


        for(int i=0;i<m;i++)
        {

            search_avl(

                avl,

                data[pos]

            );


            pos += step;

        }


        t1 = getTime();

        avlTime =

        t1 - t0;


        /*
         * búsquedas splay
         */

        t0 = getTime();


        pos = 0;


        for(int i=0;i<m;i++)
        {

            int found;


            splay =

            search_splay(

                splay,

                data[pos],

                &found

            );


            pos += step;

        }


        t1 = getTime();

        splayTime =

        t1 - t0;


        fprintf(

            csv,

            "%d,%lf,%lf\n",

            m,

            avlTime,

            splayTime

        );

    }


    fclose(csv);

    freeAVL(avl);

    freeSplay(splay);

    free(data);

}








/**
 * ejecuta el experimento asociado al
 * working set theorem.
 *
 * retorna:
 * - no retorna ningún valor.
 */
void runWorkingSetExperiment()
{

    FILE* csv =

    fopen(

        "working_set_results.csv",

        "w"

    );


    fprintf(

        csv,

        "w,avl_time,splay_time\n"

    );


    unsigned int* data =

    malloc(

        LARGE_N*sizeof(unsigned int)

    );


    generateDataset(

        data,

        LARGE_N

    );


    AVLNode* avl = NULL;

    SPLAYNode* splay = NULL;


    for(int i=0;i<LARGE_N;i++)
    {

        avl =

        insert_avl(

            avl,

            data[i]

        );


        splay =

        insert_splay(

            splay,

            data[i]

        );

    }


    int values[6] =

    {

        10,

        100,

        1000,

        10000,

        100000,

        1000000

    };


    int M =

    10*C*LARGE_N;


    for(int k=0;k<6;k++)
    {

        int W = values[k];


        unsigned int* working =

        malloc(

            W*sizeof(unsigned int)

        );


        for(int i=0;i<W;i++)
        {

            working[i] =

            data[

            rand()%LARGE_N

            ];

        }


        double t0;

        double t1;

        double avlTime;

        double splayTime;


        /*
         * avl
         */

        t0 = getTime();


        for(int i=0;i<M;i++)
        {

            unsigned int key =

            working[

            rand()%W

            ];


            search_avl(

                avl,

                key

            );

        }


        t1 = getTime();

        avlTime =

        t1 - t0;


        /*
         * splay
         */

        t0 = getTime();


        for(int i=0;i<M;i++)
        {

            unsigned int key =

            working[

            rand()%W

            ];


            int found;


            splay =

            search_splay(

                splay,

                key,

                &found

            );

        }


        t1 = getTime();

        splayTime =

        t1 - t0;


        fprintf(

            csv,

            "%d,%lf,%lf\n",

            W,

            avlTime,

            splayTime

        );


        free(working);

    }


    fclose(csv);

    freeAVL(avl);

    freeSplay(splay);

    free(data);

}