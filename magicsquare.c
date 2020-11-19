/*
 * Pagès Louis-César 2018 CMI
 *
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <ctype.h>


/******************************************************************************
 * Gestion des erreurs
 */
void raler(int syserr, const char *fmt, ...)
{
    va_list ap ;

    va_start (ap, fmt) ;
    vfprintf (stderr, fmt, ap) ;
    fprintf (stderr, "\n") ;
    va_end (ap) ;

    if (syserr)
	perror ("") ;

    exit (EXIT_FAILURE) ;
}

/******************************************************************************
 *Fonctions du programme
 */

//Ma structure Carré.
typedef struct s_square{

    int ** quad1;
    int ** quad2;
    int ** quad3;
    int ** quad4;
    int size;

} * Square;
//initialise les quatres parties du carré.
Square initializeSquare( int n)
{
    int a = n/2, b = n/2;
    if(n>325002)
        exit(EXIT_FAILURE);
    //on initialise la première dimension
    Square res = malloc(sizeof(struct s_square));
    res->size = n;
    res->quad1 = malloc(sizeof(int *) * (a)); //on vérifie que la mémoire est
    if(res->quad1 == NULL)                  // bien allouée.
    {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    res->quad2 = malloc(sizeof(int *) * (a));
    if(res->quad2 == NULL)
    {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    res->quad3 = malloc(sizeof(int *) * (a));
    if(res->quad3 == NULL)
    {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    res->quad4 = malloc(sizeof(int *) * (a));
    if(res->quad4 == NULL)
    {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    //puis la deuxième.
    for(--a; a>=0; a--)
    {
        res->quad1[a] = malloc(sizeof(int) * b);
        if(res->quad1[a] == NULL)
        {
            perror("Couldn't allocate memory");
            exit(EXIT_FAILURE);
        }
        res->quad2[a] = malloc(sizeof(int) * b);
        if(res->quad2[a] == NULL)
        {
            perror("Couldn't allocate memory");
            exit(EXIT_FAILURE);
        }
        res->quad3[a] = malloc(sizeof(int) * b);
        if(res->quad3[a] == NULL)
        {
            perror("Couldn't allocate memory");
            exit(EXIT_FAILURE);
        }
        res->quad4[a] = malloc(sizeof(int) * b);
        if(res->quad4[a] == NULL)
        {
            perror("Couldn't allocate memory");
            exit(EXIT_FAILURE);
        }
    }

    return res;
}
//libère la mémoire occupé par la structure.
void freeSquare( Square q)
{
    int i;
    for(i=0; i< (q->size/2) ; i++) //deuxième dimension
    {
        free(q->quad1[i]);
        free(q->quad2[i]);
        free(q->quad3[i]);
        free(q->quad4[i]);
    }
    free(q->quad1); // première dimension
    free(q->quad2);
    free(q->quad3);
    free(q->quad4);

    free(q);
}
void freeMatrix( int ** mat, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        free(mat[i]);
    }
    free(mat);

}
//procède aux changements entre partie du carré.
void transformSquare(Square sq)
{
    int i, j, s = sq->size/2;
    int sup;

    for(i=s/2; i>=1; i--)
    {
        sup = sq->quad1[s/2][i];
        sq->quad1[s/2][i] = sq->quad3[s/2][i];
        sq->quad3[s/2][i] = sup;
    }
    for(i=(s/2)-1; i>=0; i--)
    {
        for(j=(s/2)-1; j>=0; j--)
        {
            sup = sq->quad1[i][j];
            sq->quad1[i][j] = sq->quad3[i][j];
            sq->quad3[i][j] = sup;
        }
    }
    for(i=(s/2)+1; i<s; i++)
    {
        for(j=0; j<(s/2); j++)
        {
            sup = sq->quad1[i][j];
            sq->quad1[i][j] = sq->quad3[i][j];
            sq->quad3[i][j] = sup;
        }
    }
    for(i=0;i<s;i++)
    {
        for(j=s-1; j>((s/2)+1); j--)
        {
            sup = sq->quad2[i][j];
            sq->quad2[i][j] = sq->quad4[i][j];
            sq->quad4[i][j] = sup;
        }
    }
}
// Permet de générer une partie de la struct Square.
void generateSquare(int n, int ** magicSquare)
{

    // Initialisation de la position
    int i = n/2;
    int j = n-1;
    int num;

    // Calcule de la valeur d'une case
    for (num=1; num <= n*n; )
    {
        if (i==-1 && j==n)
        {
            j = n-2;
            i = 0;
        }
        else
        {
            //vérifie si nous ne sommes pas sur le coté droit
            if (j == n)
                j = 0;

            // vérifie si nous ne sommes pas au dessus.
            if (i < 0)
                i=n-1;
        }
        if (magicSquare[i][j])
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = num++; //applique la valeur

        j++; i--;
    }
}
//affichage d'une matrice
void printMatrix(int ** matrix, int size)
{
    int i, j;
    int n = size;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}
//affichage de la structure Square
void printSquare(Square sq, int size)
{
    int i, j;
    int n = size;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf("%d ", sq->quad1[i][j]);
        for (j=0; j<n; j++)
            printf("%d ", sq->quad2[i][j]);
        printf("\n");
    }
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf("%d ", sq->quad3[i][j]);
        for (j=0; j<n; j++)
            printf("%d ", sq->quad4[i][j]);
        printf("\n");
    }
}
//transforme une Matrice (a.k.a tableau 2 dimensions) en un tableau
int * matrixToArray(int ** matrix, int size_m)
{
    int * array = malloc(sizeof(int) * (size_m*size_m) );
    int i, j;
    int n = size_m;

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            array[j+i*n] = matrix[i][j];
        }
    }

    return array;

}
//transforme un tableau en Matrice
int ** arrayToMatrix(int * array, int size_m)
{
    int ** matrix = malloc(sizeof(int *) * (size_m) );
    int i, j;
    int n = size_m;

    for(i=0 ;i<n ;i++ )
    {
        matrix[i] = malloc(sizeof(int) * n);
    }
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            matrix[i][j] = array[j+i*n] ;
        }
    }
    return matrix;
}

//multiplication par un scalaire du quadrant calculé
int * addScal(int v, int * m, int size){

    int i;
    for(i=0; i < size; i++)
    {
        m[i] = m[i] + v;
    }

  return m;
}

static int received = 0;
//fonction à exécuter lors d'un signal
static void handler(int sig)
{
    if (sig == SIGUSR1)
    {
        received ++;
    }
}

//*************************** main ********************************************

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf (stderr, "need one integer \n") ;
        exit (EXIT_FAILURE) ;
    }
    //obtenir la valeur de l'argument
    int arg;
    sscanf (argv[1],"%d",&arg);

    if( (arg % 4) == 0)
    {
        fprintf (stderr, "integer cannot be divided by 4 \n") ;
        exit (EXIT_FAILURE) ;
    }
    if( (arg % 2) != 0)
    {
        fprintf (stderr, "integer cannot be an odd \n") ;
        exit (EXIT_FAILURE) ;
    }
    if( arg < 0)
    {
        fprintf (stderr, "integer cannot be negative \n") ;
        exit (EXIT_FAILURE) ;
    }

    Square mySquare = initializeSquare( arg);

    int k;
    int n = arg / 2;

    int ** support = malloc(sizeof(int *) * n);

    if( support == NULL ) //si l'allocation échoue
    {
        perror("couldn't allocate memory \n");
        exit(1);
    }

    for(k=0; k<n; k++)
    {
        support[k]= malloc(sizeof(int) * n);

        if(support[k] == NULL)
        {
            perror("couldn't allocate memory \n");
            exit(1);
        }
    }

    int tube[2];

    if(pipe(tube) != 0)
    {
        raler (1, "initialise pipe failed");
    }

    struct sigaction sa;


    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        raler (1, "initialise sigaction failed");
    }

    int i;
    pid_t * f_pid = malloc(sizeof(pid_t)*4);

    for(i=0; i<4; i++)
    {
        f_pid[i] =  fork();

        switch (f_pid[i]) {
            case -1:                //erreur
                raler (1, "cannot fork child %d",
                f_pid[i]);

            case 0:                 //fils
                freeSquare(mySquare);

                if(close(tube[0]) == -1){
                    raler (1, "cannot close stdout of tube: %d",
                    tube[0]);
                }

                generateSquare(n, support);

                int * arr = matrixToArray(support, n);
                switch (i) {
                    case 0:
                        break;
                    case 1:
                        addScal(2*(n*n),arr,n*n);
                        break;
                    case 2:
                        addScal(3*(n*n),arr,n*n);
                        break;
                    case 3:
                        addScal(1*(n*n),arr,n*n);
                        break;
                }

                while(!received);
                //attend le signal du père
                int m = 0;
                for(m=1; m<=n; m++) //on découpe les envoies dans le tube
                {                  //pour pouvoir envoyer des quantités
                    received =0;   // importantes de données
                    write(tube[1], &arr[n*m-n], sizeof(int)*n);
                    while(!received);
                }

                for(k=0; k<n; k++) //libère la mémoire allouée du programme
                {
                    free(support[k]);
                }
                free(support);
                free(arr);
                free(f_pid);

                exit(getpid());
            default:
                break;
        }
    }
    //on libère la mémoire allouée pour support
    for(k=0; k<n; k++)
    {
        free(support[k]);
    }
    free(support);

    if(close(tube[1]) == -1)
    {
        raler (1, "cannot close stdin of tube: %d",
        tube[1]);
    }
    int raison;

    for(i=0; i<4; i++)
    {

        int * read_int = malloc(sizeof(int) * (n*n));

        if(kill(f_pid[i], SIGUSR1) == -1) //envoie du signal au fils
        {
            raler (1, "cannot send kill signal to child nb : %d",i);
        }

       for(k=1; k<=n; k++) //reception séparée des données dans le tube
       {
            read(tube[0], &read_int[n*k-n], sizeof(int)*n);
            if(kill(f_pid[i], SIGUSR1) == -1)
            {
                raler (1, "cannot send kill signal to child nb : %d",i);
            }
        }

        if(wait(&raison) == -1)
        {
            raler (1, "error while waiting for child nb: %d",i);
        }
        if (WIFEXITED (raison)){
         WEXITSTATUS (raison);
        }

        switch (i) {
            case 0:
                freeMatrix(mySquare->quad1, n); //on remplace le quad1 etc ..
                mySquare->quad1 = arrayToMatrix(read_int,n);
                break;
            case 1:
                freeMatrix(mySquare->quad2, n);
                mySquare->quad2 = arrayToMatrix(read_int,n);
                break;
            case 2:
                freeMatrix(mySquare->quad3, n);
                mySquare->quad3 = arrayToMatrix(read_int,n);
                break;
            case 3:
                freeMatrix(mySquare->quad4, n);
                mySquare->quad4 = arrayToMatrix(read_int,n);
                break;
        }
        free(read_int);
    }
    if(close(tube[0]) == -1){
        raler (1, "cannot close stdout of tube: %d", //on ferme le tube
        tube[0]);
    }

    transformSquare(mySquare); // on procède au changements entre cadrants

    printSquare(mySquare, n); //affiche notre structure

    freeSquare(mySquare); // libère la mémoire allouée
    free(f_pid);

    return 0;
}
