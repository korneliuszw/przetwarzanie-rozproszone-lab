/**
 * Program demonstracyjny potoków w systemie UNIX
 * 
 * Program składa się z trzech procesów połączonych potokami:
 * 1. Pierwszy proces wczytuje ciąg znaków z konsoli
 * 2. Drugi proces zamienia małe litery na duże
 * 3. Trzeci proces wyświetla wynik na ekranie
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe1[2]; // Potok między procesem 1 i 2
    int pipe2[2]; // Potok między procesem 2 i 3
    pid_t pid1, pid2;
    
    // Tworzenie potoków
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Błąd tworzenia potoku");
        exit(EXIT_FAILURE);
    }
    
    // Tworzenie pierwszego procesu potomnego
    pid1 = fork();
    
    if (pid1 < 0) {
        perror("Błąd tworzenia procesu");
        exit(EXIT_FAILURE);
    }
    
    if (pid1 == 0) { // Proces 1 (dziecko)
        // Zamykanie nieużywanych końców potoków
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        
        char buffer[BUFFER_SIZE];
        printf("Wprowadź ciąg znaków: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        
        // Usunięcie znaku nowej linii
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        
        // Zapisanie danych do potoku
        write(pipe1[1], buffer, strlen(buffer) + 1);
        
        // Zamknięcie używanego końca potoku
        close(pipe1[1]);
        
        exit(EXIT_SUCCESS);
    }
    
    // Tworzenie drugiego procesu potomnego
    pid2 = fork();
    
    if (pid2 < 0) {
        perror("Błąd tworzenia procesu");
        exit(EXIT_FAILURE);
    }
    
    if (pid2 == 0) { // Proces 2 (dziecko)
        // Zamykanie nieużywanych końców potoków
        close(pipe1[1]);
        close(pipe2[0]);
        
        char buffer[BUFFER_SIZE];
        
        // Odczytanie danych z pierwszego potoku
        read(pipe1[0], buffer, BUFFER_SIZE);
        
        // Zamiana małych liter na duże
        for (int i = 0; buffer[i] != '\0'; i++) {
            buffer[i] = toupper(buffer[i]);
        }
        
        // Zapisanie danych do drugiego potoku
        write(pipe2[1], buffer, strlen(buffer) + 1);
        
        // Zamknięcie używanych końców potoków
        close(pipe1[0]);
        close(pipe2[1]);
        
        exit(EXIT_SUCCESS);
    }
    
    // Proces główny (rodzic) - będzie działać jako proces 3
    // Zamykanie nieużywanych końców potoków
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);
    
    char buffer[BUFFER_SIZE];
    
    // Odczytanie danych z drugiego potoku
    read(pipe2[0], buffer, BUFFER_SIZE);
    
    // Wyświetlenie wyniku
    printf("Wynik: %s\n", buffer);
    
    // Zamknięcie używanego końca potoku
    close(pipe2[0]);
    
    // Oczekiwanie na zakończenie procesów potomnych
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return 0;
} 