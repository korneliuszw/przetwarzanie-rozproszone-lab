#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pqueue.h>
#include <stdbool.h>
#include <unistd.h>

// Maksymalna liczba do sprawdzenia
#define MAX_NUMBER 10000
// Liczba wątków producenta i konsumenta
#define N_PRODUCERS 1
#define N_CONSUMERS 5
// Rozmiar bufora
#define BUFFER_SIZE 100

// Mutex do synchronizacji dostępu do bufora
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
// Zmienne warunkowe do sygnalizacji stanu bufora
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

// Kolejka priorytetowa jako bufor
pqueue *buffer = NULL;
// Licznik elementów w buforze
int buffer_count = 0;
// Flaga zakończenia pracy
bool done = false;
// Aktualna liczba do sprawdzenia
int current_number = 2;

// Struktura elementu do sprawdzenia
typedef struct item item;
struct item {
    int number;
};

// Funkcja sprawdzająca, czy liczba jest pierwsza
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Funkcja producenta - generuje kolejne liczby do sprawdzenia
void* producer(void *p) {
    while (current_number <= MAX_NUMBER) {
        // Alokacja nowego elementu
        item *it = (item *)malloc(sizeof(item));
        if (it == NULL) {
            perror("Błąd alokacji pamięci");
            exit(EXIT_FAILURE);
        }
        
        pthread_mutex_lock(&buffer_mutex);
        
        // Czekaj, jeśli bufor jest pełny
        while (buffer_count >= BUFFER_SIZE && !done) {
            pthread_cond_wait(&buffer_not_full, &buffer_mutex);
        }
        
        // Jeśli zakończono pracę, zwolnij zasoby i zakończ
        if (done) {
            pthread_mutex_unlock(&buffer_mutex);
            free(it);
            return NULL;
        }
        
        // Przypisz liczbę do sprawdzenia
        it->number = current_number++;
        
        // Dodaj element do bufora
        qinsert(&buffer, it, it->number);
        buffer_count++;
        
        // Sygnalizuj, że bufor nie jest pusty
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&buffer_mutex);
    }
    
    // Oznacz zakończenie generowania liczb
    pthread_mutex_lock(&buffer_mutex);
    done = true;
    pthread_cond_broadcast(&buffer_not_empty);
    pthread_mutex_unlock(&buffer_mutex);
    
    return NULL;
}

// Funkcja konsumenta - sprawdza, czy liczba jest pierwsza
void* consumer(void *p) {
    int thread_id = *((int*)p);
    
    while (true) {
        pthread_mutex_lock(&buffer_mutex);
        
        // Czekaj, jeśli bufor jest pusty
        while (buffer_count == 0 && !done) {
            pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
        }
        
        // Jeśli bufor jest pusty i zakończono pracę, zakończ
        if (buffer_count == 0 && done) {
            pthread_mutex_unlock(&buffer_mutex);
            return NULL;
        }
        
        // Pobierz element z bufora
        pqueue *node = qpop(&buffer);
        item *it = (item*)node->data;
        int number = it->number;
        free(node);
        
        buffer_count--;
        
        // Sygnalizuj, że bufor nie jest pełny
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&buffer_mutex);
        
        // Sprawdź, czy liczba jest pierwsza
        if (is_prime(number)) {
            printf("Wątek %d: Liczba %d jest pierwsza\n", thread_id, number);
        }
        
        // Zwolnij pamięć
        free(it);
    }
    
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t producers[N_PRODUCERS];
    pthread_t consumers[N_CONSUMERS];
    int consumer_ids[N_CONSUMERS];
    
    // Utwórz wątki producenta
    for (int i = 0; i < N_PRODUCERS; i++) {
        if (pthread_create(&producers[i], NULL, producer, NULL) != 0) {
            perror("Błąd tworzenia wątku producenta");
            exit(EXIT_FAILURE);
        }
    }
    
    // Utwórz wątki konsumenta
    for (int i = 0; i < N_CONSUMERS; i++) {
        consumer_ids[i] = i;
        if (pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]) != 0) {
            perror("Błąd tworzenia wątku konsumenta");
            exit(EXIT_FAILURE);
        }
    }
    
    // Czekaj na zakończenie wątków producenta
    for (int i = 0; i < N_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    
    // Czekaj na zakończenie wątków konsumenta
    for (int i = 0; i < N_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    printf("Wszystkie liczby pierwsze z zakresu 2-%d zostały znalezione.\n", MAX_NUMBER);
    
    // Zniszcz mutex i zmienne warunkowe
    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&buffer_not_full);
    pthread_cond_destroy(&buffer_not_empty);
    
    return 0;
}

