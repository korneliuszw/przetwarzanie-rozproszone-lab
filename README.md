# przetwarzanie-rozproszone-lab

## Laboratorium 1

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |
|---|---                    |---                |
|1. | System operacyjny:    | Linux (zalecany)  |
|2. | Kompilator:           | gcc               |
|3. | Edytor tekstowy:      | <i> dowolny </i>  |

### Zadanie do wykonania:

Zaimplementować wybraną dynamiczną strukturę danych w C i pokazać jej działanie, np. Stack, Single Linked List, Doubly Linked List, Binary Tree. Należy pamiętać o dynamicznej alokacji pamięci (funkcje `malloc()` i `free()`) Rozwiązaniem zadania jest plik z kodem źródłowym (nie sam plik binarny) i (jeśli jest to potrzebne) odpowiednimi plikami nagłówkowymi.

Implementujemy tylko jedną wybraną stukturę - nie ma potrzeby implementowania wszystkich wyżej wymienionych.

Wymagania co do kodu:

1. Kod ma zawierać odpowiednie dyrektywy preprocesora/biblioteki.
2. Kod ma mieć zaimplementowaną strukturę danych, odpowiadającą konkretnemu wybranemu przykładowi (np. StackNode, LinkedListNode, TreeNode, itp.).
3. Kod ma mieć zaimplementowane funkcje, które będą prowadzić działania na tej strukturze, (przykładowo dla Stack'a będą to funkcje `push()` i `pop()`).
4. Kod ma mieć funkcję, która będzie wyświetlać dane znajdujące się w zaimplementowanej strukturze (dla Stack'a -> LIFO, dla Linked List: head -> tail, dla Binary Tree -> inorder traversal).
5. W funkcji `main()` proszę zainicjować zaimplementowaną strukturę i napisać przykładowe use case'y, żeby pokazać działanie kodu.
6. W kodzie należy pamiętać o dynamicznej alokacji pamięci z użyciem funkcji `malloc()` i `free()` (za wycieki pamięci będą odejmowane punkty).
7. Do kompilacji i uruchomienia pogramu zachęcam do skorzystania z następującej instrukcji:
    ```bash
    gcc -Wall -fsanitize=leak -pedantic -o stack stack.c && ./stack
    ```

Snippet kodu, jak to ma wyglądać w przypadku struktury typu Stack jest zamieszczony w ścieżce `lab1/stack.c` i zachęcam do skorzystania z niego.

## Laboratorium 2

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                           |
|---|---                    |---                        |
|1. | System operacyjny:    | Linux (<b>wymagany</b>)   |
|2. | Kompilator:           | gcc                       |
|3. | Edytor tekstowy:      | <i> dowolny </i>          |

### Zadania do wykonania:

W tym ćwiczeniu laboratoryjnym będzie wykorzystany kod napisany w <b>Laboratorium 1</b> - zostanie on rozbity na pliki źródłowe i nagłówkowe
oraz umieszczony w odpowiednich dla nich miejscach w katalogu projektu. Następnie zostaną utworzone poszczególne biblioteki.

1. Utworzenie biblioteki statycznej (archiwum)
   1. Zmieniamy katalog na `przetwarzanie-rozproszone-lab/lab2/static`
   2. Uzupełniamy poszczególne pliki źródłowe i nagłówkowe według zawartych w nich instrukcji
   3. Tworzymy pliki objektów na podstawie plików źródłowych z katalogu `/src` za pomocą komendy: 
        `gcc -c src/stack.c -o src/stack.o -Iinclude`. Powtarzamy ten krok odpowiednio dla pliku `utils.c`
   4. Tworzymy archiwum ze wcześniej utworzonych plików objektowych za pomocą komendy:
        `ar r libstack.a src/stack.o src/utils.o`
   5. Tworzymy plik objektu z pliku źródłowego `main.c`
   6. Linkujemy plik objektowy `main.o` ze wskazaniem archiwum za pomocą komendy:
        `gcc main.o libstack.a -o main`
   7. Sprawdzamy funkcjonalność programu za pomocą `./main`
