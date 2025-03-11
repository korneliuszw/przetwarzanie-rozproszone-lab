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

<b>Warunki zaliczenia:</b>

1. Zaprezentowanie działania kodu z zaimplementowaną strukturą danych
2. Brak wycieków pamięci (za to będą odejmowane punkty)
3. Przesłanie pliku źródłowego na E-Nauczanie

## Laboratorium 2

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                           |
|---|---                    |---                        |
|1. | System operacyjny:    | Linux (<b>wymagany</b>)   |
|2. | Kompilator:           | gcc                       |
|3. | Edytor tekstowy:      | <i> dowolny </i>          |

### Teoria

<b>Biblioteka statyczna</b>

1. Linkowana w czasie kompilacji
2. Staje się częścią finalnego pliku wykonywalnego
3. Szybsze wykonywanie, ponieważ cały wymagany kod jest częścią binarki
4. Brak zależności od zewnętrznych plików w czasie działania
5. Większa przenośność, ponieważ plik wykonywalny zawiera wszystko, czego potrzebuje
6. Większy rozmiar pliku binarnego, ponieważ pełna biblioteka jest osadzona w każdym pliku wykonywalnym.
7. Konieczność rekompilacji w przypadku aktualizacji biblioteki (każdy program korzystający z niej musi zostać ponownie skompilowany).

<b>Biblioteka dynamiczna</b>

1. Linkowana w czasie działania
2. Pozostaje osobnym plikiem
3. Mniejszy rozmiar pliku wykonywalnego, ponieważ biblioteka pozostaje oddzielnym plikiem.
4. Aktualizacje nie wymagają ponownej kompilacji zależnych programów
5. Efektywne wykorzystanie pamięci, ponieważ wiele programów może współdzielić tę samą bibliotekę w pamięci.
6. Nieco wolniejsze wykonywanie ze względu na linkowanie w czasie działania.
7. Problemy z zależnościami (program nie uruchomi się, jeśli biblioteka jest brakująca lub niekompatybilna).


### Zadania do wykonania:

W tym ćwiczeniu laboratoryjnym będzie wykorzystany kod napisany w <b>Laboratorium 1</b> - zostanie on rozbity na pliki źródłowe i nagłówkowe
oraz umieszczony w odpowiednich dla nich miejscach w katalogu projektu. Następnie zostaną utworzone poszczególne biblioteki.

1. <b>Utworzenie biblioteki statycznej (archiwum)</b>
   1. Zmieniamy katalog na `przetwarzanie-rozproszone-lab/lab2/static` i tutaj uruchamiamy poniższe komendy
   2. Uzupełniamy poszczególne pliki źródłowe i nagłówkowe według zawartych w nich instrukcji
   3. Tworzymy katalog, gdzie będziemy trzymać pliki objektów za pomocą komendy: \
     `mkdir build`
   4. Tworzymy pliki objektów na podstawie plików źródłowych z katalogu `/src` za pomocą komendy: \
     `gcc -Wall -fsanitize=leak -pedantic -Iinclude -c src/stack.c -o build/stack.o` Powtarzamy ten krok odpowiednio dla pliku `utils.c`
   5. Tworzymy archiwum ze wcześniej utworzonych plików objektowych za pomocą komendy: \
     `ar r build/libstack.a build/stack.o build/utils.o`
   6. Tworzymy plik objektu z pliku źródłowego `main.c` (Patrz punkt 4)
   7. Linkujemy plik objektowy `main.o` ze wskazaniem archiwum za pomocą komendy: \
     `gcc build/main.o build/libstack.a -o main`
   8. Sprawdzamy funkcjonalność programu za pomocą `./main`
   9. Sprzątamy, usuwając pliki objektów za pomocą komendy: \
     `rm -r build/`
2. <b>Utworzenie biblioteki dynamicznej</b>
   1. Zmieniamy katalog na `przetwarzanie-rozproszone-lab/lab2/dynamic` i tutaj uruchamiamy poniższe komendy
   2. Uzupełniamy poszczególne pliki źródłowe i nagłówkowe według zawartych w nich instrukcji
   3. Tworzymy katalog, gdzie będziemy trzymać pliki objektów za pomocą komendy: \
     `mkdir build`
   4. Tworzymy pliki przesuwne na podstawie plików źródłowych z katalogu `/src` za pomocą komendy: \
     `gcc -Wall -fsanitize=leak -pedantic -Iinclude -fPIC -D_GNU_SOURCE -c src/stack.c -o build/stack.o`. Powtarzamy ten krok odpowiednio dla pliku utils.c
   5. Tworzymy bibliotekę dynamiczną ze wcześniej utworzonych plików przesuwnych za pomocą komendy: \
     `gcc -shared build/stack.o build/utils.o -o build/libstack.so`
   6. Tworzymy plik objektu z pliku źródłowego `main.c` (Patrz instrukcję biblioteki statycznej, punkt 4)
   7. Określamy położenie biblioteki, żeby dynamiczny program ładujący mógł ją odszukać, za pomocą komendy: \
     `export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:build/"`
   8. Linkujemy plik objektowy `main.o` ze wskazaniem biblioteki dynamicznej za pomocą komendy: \
     `gcc build/main.o -Lbuild -lstack -o main`
   9. Sprawdzamy funkcjonalność programu za pomocą `./main`
   10. Sprzątamy, usuwając pliki objektów za pomocą komendy: \
     `rm -r build/`

<b>Warunki zaliczenia:</b>

1. Zaprezentowanie działania kodu z zaimplementowanymi bibliotekami
2. Za każdą bibliotekę przyznawane jest 5 punktów 
3. Brak wycieków pamięci (za to będą odejmowane punkty)
4. Przesłanie skompresowanego katalogu z projektem (lab2.tar) na E-Nauczanie
   