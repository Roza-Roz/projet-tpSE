#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_SIZE 10

// Matrices
int B[MAX_SIZE][MAX_SIZE];
int C[MAX_SIZE][MAX_SIZE];
int A[MAX_SIZE][MAX_SIZE];

// Tailles des matrices
int n1, m1, n2, m2;

// Tampon
int T[MAX_SIZE][MAX_SIZE];

// Sémaphores pour la synchronisation
sem_t sem_producteur, sem_consommateur;

// Fonction pour calculer une ligne de la matrice résultante A
void* producteur(void* arg) {
    int row = *(int*)arg;

    for (int i = 0; i < m1; ++i) {
        for (int j = 0; j < n2; ++j) {
            T[row][i] += B[row][j] * C[j][i];
        }
    }

    // Signaler au consommateur qu'une ligne est prête
    sem_post(&sem_consommateur);

    pthread_exit(NULL);
}

// Fonction pour consommer les résultats du tampon et les placer dans la matrice résultante A
void* consommateur(void* arg) {
    for (int i = 0; i < n1; ++i) {
        // Attendre que le producteur ait calculé une ligne
        sem_wait(&sem_consommateur);

        for (int j = 0; j < m1; ++j) {
            A[i][j] = T[i][j];
        }

        // Signaler au producteur que la ligne a été consommée
        sem_post(&sem_producteur);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    printf("Entrez les dimensions de la matrice B (n1 m1): ");
    scanf("%d %d", &n1, &m1);

    printf("Entrez les dimensions de la matrice C (n2 m2): ");
    scanf("%d %d", &n2, &m2);

    if (m1 != n2) {
        printf("Erreur: Les dimensions des matrices ne permettent pas le produit.\n");
        return 1;
    }

    // Initialisation des matrices B et C avec des valeurs aléatoires
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            B[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < m2; ++j) {
            C[i][j] = rand() % 10;
        }
    }

    // Initialisation du tampon T avec des valeurs nulles
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            T[i][j] = 0;
        }
    }

    // Initialisation des sémaphores
    sem_init(&sem_producteur, 0, n1);    // Le nombre initial de jetons pour le producteur est n1
    sem_init(&sem_consommateur, 0, 0);   // Le nombre initial de jetons pour le consommateur est 0

    // Création des threads producteurs
    pthread_t producteur_threads[n1];
    int rows[n1];
    for (int i = 0; i < n1; ++i) {
        rows[i] = i;
        pthread_create(&producteur_threads[i], NULL, producteur, &rows[i]);
    }

    // Création du thread consommateur
    pthread_t consommateur_thread;
    pthread_create(&consommateur_thread, NULL, consommateur, NULL);

    // Attente de la fin des threads producteurs
    for (int i = 0; i < n1; ++i) {
        pthread_join(producteur_threads[i], NULL);
    }

    // Attente de la fin du thread consommateur
    pthread_join(consommateur_thread, NULL);

    // Affichage des matrices
    printf("Matrice B:\n");
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrice C:\n");
    for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < m2; ++j) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrice Résultante A:\n");
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m1; ++j) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    // Destruction des sémaphores
    sem_destroy(&sem_producteur);
    sem_destroy(&sem_consommateur);

    return 0;
}
