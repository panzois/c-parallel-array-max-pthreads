/*
Author: Panagiotis Zois
Project: Parallel Maximum Computation using POSIX Threads
Description: Demonstrates workload partitioning and mutex synchronization
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadData
{
    int ID;
    int *Mat;
    int From;
    int To;
    pthread_mutex_t *Mutex;
};

void *Func (void *);
void MatFull (int [], int);

int total_max;

int main (int argc, char **argv)
{
    int n;      // μέγεθος πίνακα
    int t;      // πόσα thread θα δημιουργηθούν
    int i, r;   // μετρητές
    long H;     // χρόνος εκτέλεσης

    clock_t T1, T2;
    pthread_t *ThreadMat; // πίνακες για τα threads
    struct ThreadData *D; // δομή για τα δεδομένα των threads
    pthread_mutex_t M; // mutex για συγχρονισμό
    int *X;
    total_max = -1;

    do
    {
        printf ("Δώστε το μέγεθος του πίνακα (n)  : ");
        scanf ("%d", &n);
        printf ("Δώστε τον αριθμό των threads (t) : ");
        scanf ("%d", &t);
    }
    while (n % t != 0); // διασφαλίζουμε ότι το μέγεθος του πίνακα διαιρείται από τον αριθμό των threads

    X = (int *) malloc (n * sizeof (int));
    MatFull (X, n); // γέμισμα του πίνακα με τυχαίους αριθμούς
    
    pthread_mutex_init (&M, NULL); // αρχικοποίηση του mutex

    D = (struct ThreadData *) malloc (t * sizeof (struct ThreadData));
    int Step;
    int Start=0; // αρχικοποίηση του σημείου εκκίνησης για τα threads
    Step = n / t; // υπολογισμός του βήματος για κάθε thread

    for (i=0;i<t;i++)
    {
        D[i].ID = i+1; // αναθέτουμε ID σε κάθε thread
        D[i].Mat = X; // αναθέτουμε τον πίνακα σε κάθε thread
        D[i].From = Start; // καθορίζουμε το σημείο εκκίνησης για κάθε thread
        /*if (i == t - 1) // για το τελευταίο thread, παίρνουμε το υπόλοιπο του πίνακα
            D[i].To = n;
        else*/ //από την στιγμή που το n είναι διαιρετό από t, δεν χρειάζεται αυτή η συνθήκη
        D[i].To = Start + Step; // καθορίζουμε το σημείο τερματισμού για κάθε thread
        D[i].Mutex = &M;  // αναθέτουμε το mutex σε κάθε thread
        Start = Start + Step;   // ενημερώνουμε το σημείο εκκίνησης για το επόμενο thread
    }
    
    ThreadMat = (pthread_t *) malloc (t * sizeof (pthread_t));
    T1 = clock(); // αρχή μέτρησης χρόνου
    for (i = 0; i < t; i++)
    {
        r = pthread_create (&ThreadMat[i], NULL, Func, &D[i]); // δημιουργία των thread
    }
    for (i=0; i<t; i++)
    {
        pthread_join (ThreadMat[i], NULL); // περιμένουμε να τελειώσουν όλα τα threads
    }
    T2 = clock(); // τέλος μέτρησης χρόνου
    H = T2 - T1; // υπολογισμός του χρόνου εκτέλεσης

    printf ("Χρόνος εκτέλεσης: %ld\n", H);  // εκτύπωση του χρόνου εκτέλεση

    printf ("Μέγιστος αριθμός: %d\n", total_max); // εκτύπωση του μέγιστου αριθμού

    free (X); // απελευθέρωση της μνήμης
    return 0;
}

void MatFull (int Pinakas[], int size)
{
    int i;
    srand(time(NULL)); // αρχικοποίηση του γεννήτρια τυχαίων αριθμών
    int k=-1;
    for (i = 0; i < size; i++)
    {
        Pinakas[i] = rand();
        if (Pinakas[i] > k)
        {
            k = Pinakas[i];
        }
    }
}

void *Func (void *ptr)
{
    struct ThreadData *data;
    int i;
    int local_max= -1; // τοπικό μέγιστο για κάθε thread
    data = (struct ThreadData *) ptr; // μετατροπή του ptr σε δομή ThreadData

    for (i = data->From; i < data->To; i++)
    {
        if (data->Mat[i] > local_max) // έλεγχος για τοπικό μέγιστο
        {
            local_max = data->Mat[i];
        }
    }

    pthread_mutex_lock(data->Mutex); // κλείδωμα του mutex
    if (local_max > total_max) // έλεγχος και ενημέρωση του συνολικού μέγιστου
    {
        total_max = local_max;
    }
    pthread_mutex_unlock(data->Mutex); // ξεκλείδωμα του mutex

    return NULL; // επιστροφή NULL για να δηλώσουμε ότι το thread ολοκληρώθηκε
}