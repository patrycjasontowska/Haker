//HAKER 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LW (5) // deklarowanie liczby wierszy w tablicy
#define LK (3) // deklarowanie kolumn wierszy w tablicy
#define DLUGOSCTABLICY (8) //stała długość tablic z hasłem
#define MOZLIWOSCI (10) //stała wykorzystana do funkcji wszystkieInneMozliwosci

// Funckcja sprawdzająca ilu znaków użytkownik użył do wpisania hasła

int dlugoscNapisu(char s[]) {
    int dlugosc = 0;
    while (s[dlugosc] != 0) {
        dlugosc ++;
    }
    return dlugosc;
}

// Funckcja sprawdzająca jakie znaki użytkownik wpisał podając hasło, użyto kodu ASCII po to żeby,
// w momencie kiedy użytkownik wpisze inny znak niż liczby z zakresu od 0 do 9

int czySaZnaki(char text[], int dlugosc) {
    for (int i = 0; i < dlugosc; i ++) {
        if (text[i] < 48 || text[i] > 57) {
            return 0;
        }
    }
    return 1;
}

int czyCyfraWTablicy(int liczba, int numbers[], int rozmiarTablicy) {

    for (int i = 0; i < rozmiarTablicy; i ++) {
        if (numbers[i] == liczba)
            return 1;
    }
    return 0;
}

//Funkcja generuje wszystkie pozostałe możłiwe hasła, jeśli nie zostało ono wcześniej odkryte

void wszystkieInneMozliwosci(int numbers[DLUGOSCTABLICY]) {
    // Zpis do pliku tekstowego
    FILE *plikKombinacji;
    plikKombinacji = fopen("pozostalekombinacje.txt", "w");

    int zliczPusteIndexy = 0;
    int pusteIndexy[DLUGOSCTABLICY];
    int liczbaMozliwosci = 1;

    // int i - do zliczenia wszystkich informacji ktorych potrzebujemy do wygenerowania pozostałych kombinacji
    // int j - generuje nam pozostale kombinacje
    // int k - wyświetla pozostale kombinacje

    //Pentla szuka w tablicy -1, które oznacza puste miejscie i je zlicza
    for (int i = 0; i < DLUGOSCTABLICY; i ++) {
        if (numbers[i] == - 1) { // -1 oznacza brak elementu w tablicy
            pusteIndexy[zliczPusteIndexy] = i;
            zliczPusteIndexy ++;

        }
    }

    // nie ma brakujących elementów, kończymy działanie funkcji
    if (zliczPusteIndexy == 0) {
        return;
    }



    // Wyświetdlugoscie ilości możliwych kombinacji
    for (int i = 0; i < zliczPusteIndexy; i ++) {
        liczbaMozliwosci *= MOZLIWOSCI;
    }


    printf("Liczba mozliwych kombinacji : %d \n", liczbaMozliwosci);

    printf("Wszystkie kombinacje mozesz sprawdzic w pliku: pozostalekombinacje.txt \n");

    for (int i = 0; i < liczbaMozliwosci; i ++) {
        int num = i;
        int tymczasowenumery[DLUGOSCTABLICY];

        // kopiujemy elementy z tablicy oryginalnej
        for (int j = 0; j < DLUGOSCTABLICY; j ++) {
            tymczasowenumery[j] = numbers[j];
        }

        // ustawiamy brakujące elementy
        for (int j = 0; j < zliczPusteIndexy; j ++) {
            int cyfra = num % MOZLIWOSCI;
            num /= MOZLIWOSCI;

            int index = pusteIndexy[j];
            tymczasowenumery[index] = cyfra;
        }
        for (int k = 0; k < DLUGOSCTABLICY; k ++) {

            fprintf(plikKombinacji, "%d", tymczasowenumery[k]);
        }
        fprintf(plikKombinacji, "\n");
    }



}

int main(int argc, char **argv) {

    printf("HACKER Patrycja Sontowska s195938 \n\n");

    char wpisaneHaslo[100];
    int dlugoscHasla;
    char numeryZHaslem[DLUGOSCTABLICY];

    // Tworzymy zapis do pliku
    FILE *plik;
    plik = fopen("generatorhasla.txt", "w");

    // Pentla pobiera od użytkownika hasło i sprawdza czy spełnia wszytkie określone warunki
    while (1) {
        printf("Podaj haslo, ktore sklada sie z 8 cyfr: ");
        scanf("%s", &wpisaneHaslo);
        if (wpisaneHaslo) {
            dlugoscHasla = dlugoscNapisu(wpisaneHaslo);
            if (czySaZnaki(wpisaneHaslo, dlugoscHasla) == 0) {
                printf("Podane haslo nie sklada sie z cyfr\n");
            } else if (dlugoscHasla == 8) {
                break;
            } else if (dlugoscHasla < 8) {
                printf("Podales mniej niz osiem cyfr.");
                printf("\n");
            } else {
                printf("Podales wiecej niz 8 cyfr.");
                printf("\n");
            }
        }
    }

    for (int i = 0; i < 8; i ++) {
        numeryZHaslem[i] = wpisaneHaslo[i];
    }

    srand(time(NULL));

    int zlicznumery5Prob = 0;
    int numbers5Prob[LW][LK];

    // Wygenerowanie 5 prób logowania
    while (zlicznumery5Prob < LW) {

        int zlicznumery3Cyfry = 0;
        int numery3Cyfry[3];

        // wylosowanie 3 miejsc z 8-cyfrowego hasła
        while (zlicznumery3Cyfry < 3) {
            int rezultat = rand() % 8;

            int jestWTablicy = czyCyfraWTablicy(rezultat, numery3Cyfry, 3);

            if (jestWTablicy) {
                continue;
            } else {
                numery3Cyfry[zlicznumery3Cyfry] = rezultat;
                ++ zlicznumery3Cyfry;
            }
        }

        for (int k = 0; k < LK; k ++) {
            numbers5Prob[zlicznumery5Prob][k] = numery3Cyfry[k];

        }


        ++ zlicznumery5Prob;
    }

    // zapis do pliku tekstowego
    for (int w = 0; w < LW; w ++) {
        for (int k = 0; k < LK; k ++) {
            fprintf(plik, "%d ", numbers5Prob[w][k]);

        }
        fprintf(plik, "\n");
    }
    fclose(plik);


    int numbers[LW * LK];
    int i;

    plik = fopen("generatorhasla.txt", "r"); // odczyt pliku

    if (plik == NULL) { // sprawdzenie czy plik udało się odtworzyć
        printf("Nie udało się otworzyć pliku.");

        return 1;
    }

    // odczyt pliku i wstawienie go do tablicy
    for (i = 0; i < LW * LK; i ++) {
        fscanf(plik, "%d", &numbers[i]);
    }

    fclose(plik); // zamknij plik

    printf("\n");



    //Sortowanie(numbers);
    int czasowa;
    for (int i = 0; i < (15 - 1); ++ i) {
        for (int j = 0; j < 15 - 1 - i; ++ j) {
            if (numbers[j] > numbers[j + 1]) {
                czasowa = numbers[j + 1];
                numbers[j + 1] = numbers[j];
                numbers[j] = czasowa;
            } else if (numbers[j] == numbers[j + 1])
                continue;
        }
    }

    // Funkcja ma na celu usunięcie powtarzających się indeksów w tablicy.
    int dlugosc = 15;

    for (int i = 0; i < dlugosc; i ++) {
        for (int j = i + 1; j < dlugosc;) {
            if (numbers[j] == numbers[i]) {
                for (int k = j; k < dlugosc; k ++) {
                    numbers[k] = numbers[k + 1];
                }
                dlugosc --;
            } else {
                j ++;
            }
        }
    }


    if (dlugosc == 8) {
        printf("Wszyskie cyfry hasla zostaly odkryte. Znaleziony PIN: ");
        for (int i = 0; i < 8; i ++) {
            printf("%c ", wpisaneHaslo[numbers[i]]);
        }
    } else {
        printf("Haslo nie zostalo znalezione.\n");
        printf("Wylosowane liczby mozesz sprawdzic w pliku generatorhasla.txt");
    }

    int tab[DLUGOSCTABLICY] = {};
    for (i = 0; i < DLUGOSCTABLICY; i ++) {
        tab[i] = - 1;
    }
    printf("\n");

    printf("\n");

    for (int i = 0; i < DLUGOSCTABLICY; i ++) {
        int indeksWTablicy = czyCyfraWTablicy(i, numbers, DLUGOSCTABLICY);
        if (indeksWTablicy) {
            printf("Cyfra pod indeksem ");
            printf("%d", i);
            printf(": ");
            printf("%c", wpisaneHaslo[i]);
            printf("\n");
            tab[i] = wpisaneHaslo[i] - '0';

        } else {
            printf("Cyfra pod indeksem ");
            printf("%d", i);
            printf(" BRAK");
            printf("\n");

        }
    }

    printf("\n");
    wszystkieInneMozliwosci(tab);
    printf("\n");


    return (0);
}

