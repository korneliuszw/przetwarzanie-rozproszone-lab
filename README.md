# przetwarzanie-rozproszone-lab

## Laboratorium 1

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Linux             |(zalecany) |
|2. | Interfejs powłoki:    | Terminal          |(zalecany) |
|3. | Interpreter poleceń:  | Bash              |(zalecany) |
|4. | Kompilator:           | gcc               |(zalecany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

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
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Linux             |(wymagany) |
|2. | Interfejs powłoki:    | Terminal          |(zalecany) |
|3. | Interpreter poleceń:  | Bash              |(zalecany) |
|4. | Kompilator:           | gcc               |(zalecany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

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
   
## Laboratorium 3

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Linux             |(wymagany) |
|2. | Interfejs powłoki:    | Terminal          |(zalecany) |
|3. | Interpreter poleceń:  | Bash              |(zalecany) |
|4. | Kompilator:           | gcc               |(zalecany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>WIELOPROCESOWOŚĆ W SYSTEMIE UNIX</b> w pliku `skrypt.pdf`
2. Przetestowanie w praktyce zawartych tam komend
3. Umiejętność odpowiedzi na pytania z puli pytań znajdujących się w pliku `lab3/README.md`
4. Są dwa sposoby na zdobycie punktów z tego laboratorium:
   1. Odpowiedź na 3 losowe pytania podczas zajęć, gdzie: jedna poprawna odpowiedź to 4 punkty, 2 poprawne to 7 punktów, 3 poprawne to 10 punktów. W takim wypadku nie jest wymaganie przesyłanie żadnego rozwiązania na E-Nauczanie.
   2. Napisanie odpowiedzi na pytania i przesłanie je na E-Nauczanie, wymóg jest jednak następujący: student musi odpowiedzieć na dowolne 10 z 15 pytań, każde pytanie jest oceniane za 1 punkt

## Laboratorium 4

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Windows           |(wymagany) |
|2. | Interfejs powłoki:    | PowerShell        |(wymagany) |
|3. | Interpreter poleceń:  | PowerShell        |(wymagany) |
|4. | Kompilator:           | MinGW             |(wymagany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>WIELOPROCESOWOŚĆ W SYSTEMIE MS WINDOWS</b> w pliku `skrypt.pdf`
2. Przetestowanie w praktyce zawartych tam komend
3. Umiejętność odpowiedzi na 3 losowe pytania z puli pytań znajdujących się w pliku `lab4/README.md`
4. Są dwa sposoby na zdobycie punktów z tego laboratorium:
   1. Odpowiedź na 3 losowe pytania podczas zajęć, gdzie: jedna poprawna odpowiedź to 4 punkty, 2 poprawne to 7 punktów, 3 poprawne to 10 punktów. W takim wypadku nie jest wymaganie przesyłanie żadnego rozwiązania na E-Nauczanie.
   2. Napisanie odpowiedzi na pytania i przesłanie je na E-Nauczanie, wymóg jest jednak następujący: student musi odpowiedzieć na dowolne 10 z 15 pytań, każde pytanie jest oceniane za 1 punkt

## Laboratorium 5

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Windows           |(wymagany) |
|2. | Interfejs powłoki:    | PowerShell        |(wymagany) |
|3. | Interpreter poleceń:  | PowerShell        |(wymagany) |
|4. | Kompilator:           | MinGW             |(wymagany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>KOMUNIKACJA MIĘDZYPROCESOWA W SYSTEMIE MS WINDOWS</b> w pliku `skrypt.pdf`
2. Przetestowanie w praktyce zawartych tam komend
3. Zapoznanie się z kodem, który znajduje się w katalogu `lab5`
4. Spróbować uruchomić kod oraz zapoznać się z jego działaniem
5. Jako zadanie do przesłania na E-Nauczanie, przesłać plik tekstowy, w którym znajduje się opis działania komunikacji międzyprocesowej w systemie Windows:
   1. Jaką rolę pełni nazwany potok `Named Pipe` w tym programie?
   2. Jak działa synchronizacja między klientem a serwerem?
   3. Jak serwer odczytuje dane od klienta i jak odpowiada?
   4. Jak klient i serwer kończą połączenie?
   5. Jakie błędy mogą wystąpić podczas uruchamiania tego programu?

## Laboratorium 6

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Windows           |(wymagany) |
|2. | Interfejs powłoki:    | PowerShell        |(wymagany) |
|3. | Interpreter poleceń:  | PowerShell        |(wymagany) |
|4. | Kompilator:           | MinGW             |(wymagany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>INTERFEJS GNIAZDEK W SYSTEMIE MS WINDOWS</b> w pliku `skrypt.pdf`
2. Przetestowanie w praktyce zawartych tam komend
3. Zapoznanie się z kodem, który znajduje się w katalogu `lab6`
4. Spróbować uruchomić kod oraz zapoznać się z jego działaniem
5. Jako zadanie do przesłania na E-Nauczanie, przesłać plik tekstowy, w którym znajduje się opis działania komunikacji za pomocą socket'ów w systemie Windows:
   1. Jakie zadanie realizuje ten program?
   2. Jakie kroki wykonuje klient, aby połączyć się z serwerem?
   3. Jakie funkcje wykorzystuje serwer do obsługi klientów?
   4. Jakie błędy mogą wystąpić podczas uruchamiania tego programu?
   5. Jak klient i serwer kończą połączenie?

## Laboratorium 7

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Linux             |(wymagany) |
|2. | Interfejs powłoki:    | Terminal          |(zalecany) |
|3. | Interpreter poleceń:  | Bash              |(zalecany) |
|4. | Kompilator:           | gcc               |(zalecany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>WĄTKI POSIX</b> w pliku `skrypt.pdf`
2. Przetestowanie w praktyce zawartych tam komend
3. Zapoznanie się z kodem, który znajduje się w katalogu `lab7`
4. Spróbować uruchomić kod oraz zapoznać się z jego działaniem
5. Jako zadanie do przesłania na E-Nauczanie, przesłać plik tekstowy, w którym znajduje się opis działania aplikacji:
   1. Jaki jest główny cel aplikacji?
   2. Jakie elementy kodu są odpowiedzialne za uruchamianie wątków?
   3. Czym zajmują się wątki potomne?
   4. Ile liczb pierwszych jest wyświetlonych z zadanego przedziału?
   5. Dlaczego używamy mutex'ów `pthread_mutex_t`?
   6. W jaki sposób kolejka priorytetowa `pqueue *buffer` jest używana w tym kodzie? Jaki priorytet ma pobierana przez konsumenta liczba?
   7. Jak zoptymalizowano funkcję `is_prime()` w porównaniu do prostego sprawdzania podzielników?
   8. Co się stanie, jeśli `current_number` przekroczy `MAX_NUMBER`?

## Laboratorium 8

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|---                    |---                |---        |
|1. | System operacyjny:    | Linux             |(wymagany) |
|2. | Interfejs powłoki:    | Terminal          |(zalecany) |
|3. | Interpreter poleceń:  | Bash              |(zalecany) |
|4. | Kompilator:           | gcc               |(zalecany) |
|5. | Edytor tekstowy:      | <i> dowolny </i>  |           |

<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>POTOKI W SYSTEMIE UNIX</b> w pliku `skrypt.pdf`
   1. Proszę nie sugerować się zawartym w tym skrypcie zadaniem, oficjalne wymagane zadanie znajduje się w punkcie 5 tej instrukcji. 
2. Przetestowanie w praktyce zawartych tam komend
3. Zapoznanie się z kodem, który znajduje się w katalogu `lab8`
4. Spróbować uruchomić kod oraz zapoznać się z jego działaniem
5. Jako zadanie do przesłania na E-Nauczanie, przesłać plik tekstowy, w którym znajduje się opis działania aplikacji:
   1. Co demonstruje zadany program?
   2. Z ilu procesów składa się zadany program? Co wykonuje każdy z nich?
   3. Co się dzieje z procesami po wykonaniu swojego zadania?
   4. Dlaczego program używa `fork()`?
   5. Jaką rolę pełni funkcja `pipe()` w programie?
   6. Co by się stało, gdyby program nie używał `waitpid()`?
   7. Jak program radzi sobie z usunięciem znaku nowej linii `\n`?
   8. Jaką zmianę w programie musielibyśmy wprowadzić, żeby zamiast zamiany na duże litery, otrzymywać zamiany na małe litery?

## Laboratorium 9

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|-----------------------|-------------------|-----------|
| 1. | System operacyjny:    | Linux             | (wymagany) |
| 2. | Interfejs powłoki:    | Terminal          | (zalecany) |
| 3. | Interpreter poleceń:  | Bash              | (zalecany) |
| 4. | JDK (Java Development Kit): | OpenJDK / Adoptium JDK | (wymagany) |
| 5. | Kompilator Java:      | `javac`           | (wymagany) |
| 6. | Środowisko uruchomieniowe: | JVM (Java Virtual Machine) | (wymagany) |
| 7. | Menedżer pakietów:    | Maven / Gradle    | (opcjonalny) |
| 8. | Edytor kodu / IDE:    | VS Code / IntelliJ IDEA / Vim / Nano | (zalecany) |
| 9. | Wtyczki do VS Code:   | Java Extension Pack | (zalecany) |


<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>WIELOWĄTKOWOŚĆ W JĘZYKU
JAVA</b> w pliku `skrypt.pdf`
2. Przetestowanie w praktyce zawartych tam komend
3. Zapoznanie się z kodem, który znajduje się w katalogu `lab9`
4. Spróbować uruchomić kod oraz zapoznać się z jego działaniem
   1. Kompilacja: `javac Main.java`
   2. Uruchomienie: `java Main`
5. Jako zadanie do przesłania na E-Nauczanie, przesłać plik tekstowy, w którym znajduje się opis działania aplikacji:
   1. Co wskazuje na to, że ten program jest wielowątkowy?
   2. Jaki model implementuje ten program?
   3. Kiedy mamy sytuację, gdzie wielu użytkowników dokonuje zakupu, jakie musi być zaimplementowane zabezpieczenie, żeby uniknąć wyścigów?
   4. Co jest warunkiem zakończenia się tego programu?
   5. Zaproponuj dwie zmiany (modyfikacje w kodzie) wcześniejszego zakończenia pracy programu:
      1. Magazyn został przepełniony
      2. Klient nie mógł dokonać zakupu z powodu braku towaru

## Laboratorium 10

### Co będzie potrzebne na zajęciach:
|   | Wymagania:            |                   |           |
|---|-----------------------|-------------------|-----------|
| 1. | System operacyjny:    | Linux             | (wymagany) |
| 2. | Interfejs powłoki:    | Terminal          | (zalecany) |
| 3. | Interpreter poleceń:  | Bash              | (zalecany) |
| 4. | JDK (Java Development Kit): | OpenJDK / Adoptium JDK | (wymagany) |
| 5. | Kompilator Java:      | `javac`           | (wymagany) |
| 6. | Środowisko uruchomieniowe: | JVM (Java Virtual Machine) | (wymagany) |
| 7. | Menedżer pakietów:    | Maven / Gradle    | (opcjonalny) |
| 8. | Edytor kodu / IDE:    | VS Code / IntelliJ IDEA / Vim / Nano | (zalecany) |
| 9. | Wtyczki do VS Code:   | Java Extension Pack | (zalecany) |


<b>Warunki zaliczenia:</b>

1. Zapoznanie się z tematem laboratorium <b>MONITORY</b> w pliku `skrypt.pdf`
2. Przetestowanie w praktyce zawartych tam komend
3. Zapoznanie się z kodem, który znajduje się w katalogu `lab10`
4. Spróbować uruchomić kod oraz zapoznać się z jego działaniem
   1. Kompilacja: `javac BinarySemaphore.java SemaphoreDemo.java`
   2. Uruchomienie: `java SemaphoreDemo`
5. Jako zadanie do przesłania na E-Nauczanie, przesłać plik tekstowy, w którym znajduje się opis działania aplikacji:
   1. Co implementuje podglądowy kod źródłowy?
   2. Ile wątków jest utworzonych w tym programie? Gdzie jest to zdefiniowane?
   3. Czym jest semafor? Jaką rolę spełnia w tym kodzie? Co by się stało, gdyby nie był zaimplementowany?
   4. Jaką rolę pełni klasa `BinarySemaphore` w projekcie?
   5. Gdzie znajduje się sprawdzenie, czy semafor jest aktualnie odblokowany?
   6. Jaka jest rola try() ... catch() w tym programie?
   7. Jaką rolę pełni `SemaphoreDemo`?
   8. Dlaczego `BinarySemaphore` używa `LinkedBlockingQueue` zamiast prostego licznika?
