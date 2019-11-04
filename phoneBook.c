#include "phoneBook.h"

Delete remFromArray(Contatto *cont_arr, int *curr_al, _Bool *is_empty);
void printThemAll(Contatto *cont_arr, int *curr_al);
void searchContact(Contatto *cont_arr, int *curr_al);
void searchByCategory(Contatto *cont_arr, int *curr_al);
void sortArray(Contatto *cont_arr, int *curr_al);
void concat(char *conc_here, char *p_str1, char *p_str2);
int menu(char str[], int min, int max);
Contatto *allocate(int *curr_al, int *upd_al, Contatto *cont_arr, _Bool flag);
void checkAlloc(Contatto *p_alloc);
void checkIntAlloc(int *p_alloc);
void newContact(Contatto *p_new, _Bool *is_empty);
void readLine(char str[], int length);
void ignoreInputUntil(char endCh);
Response validator(char str[], Controllo ctrl);
void toLowercase(char str[]);
void getInput(char *in_str, int length, Controllo ctrl, char label[]);
TipologiaContatto getGroup(char label[]);
_Bool checkRange(int toCheck, int min, int max, char msg[MESSAGE]);
void printContact(Contatto *p_cont);
void modifyContact(Contatto *p_cont);
void modInArray(Contatto *cont_arr, int *curr_al);

/**
 * Avvia il programma e gestisce la scelta effettuata nel menu.
 */
void start() {
    Contatto *contacts_array = NULL;
    Delete removed;
    int currentAlloc; // Numero di record correntemente allocati (lunghezza attuale dell'array).
    int updateAlloc; // Numero di record alla prossima modifica dell'array.
    int choice;
    _Bool isEmpty = true; // Flag di verifica array pieno/vuoto

    contacts_array = allocate(&currentAlloc, &updateAlloc, contacts_array, false); // Inizializza l'array dinamico allocando lo spazio per un contatto.

    do {
        choice = menu("\nRUBRICA TELEFONICA\n"
                      "1) Aggiungi\n"
                      "2) Modifica\n"
                      "3) Rimuovi\n"
                      "4) Ricerca\n"
                      "5) Stampa tutti\n"
                      "6) Esci\n",
                      MENU_MIN, MENU_MAX);

        switch (choice) {
            case 1:
                contacts_array = allocate(&currentAlloc, &updateAlloc, contacts_array, true);
                newContact(&contacts_array[currentAlloc - 1], &isEmpty);
                sortArray(contacts_array, &currentAlloc);
                break;
            case 2:
                if (!isEmpty)
                    modInArray(contacts_array, &currentAlloc);
                else {
                    printf("Non è presente alcun contatto nella rubrica.");
                    ignoreInputUntil('\n');
                }

                break;
            case 3:
                if (!isEmpty) {
                    removed = remFromArray(contacts_array, &currentAlloc, &isEmpty);
                    if (removed.alert) {
                        free(contacts_array);
                        contacts_array = allocate(&currentAlloc, &updateAlloc, contacts_array, false);
                    } else {
                        updateAlloc = currentAlloc - removed.counter;
                        contacts_array = allocate(&currentAlloc, &updateAlloc, contacts_array, true);
                    }
                } else {
                    printf("Non è presente alcun contatto nella rubrica.");
                    ignoreInputUntil('\n');
                }
                break;
            case 4:
                if (!isEmpty) {
                    searchContact(contacts_array, &currentAlloc);
                } else {
                    printf("Non è presente alcun contatto nella rubrica.");
                    ignoreInputUntil('\n');
                }
                break;
            case 5:
                if (!isEmpty)
                    printThemAll(contacts_array, &currentAlloc);
                else {
                    printf("Non è presente alcun contatto nella rubrica.");
                    ignoreInputUntil('\n');
                }
                break;
        }
    } while(choice != MENU_MAX);
}

/**
 * Gestisce l'eliminazione di uno o più contatti secondo diversi criteri. Attenzione: la funzione si occupa solamente
 * di eliminare i campi desiderati dall'array senza effettuare alcuna riallocazione. La riallocazione verrà fatta
 * all'interno della funzione start in base ai valori di ritorno di questa funzione.
 *
 * NB: nella funzione sono presenti ripetizioni che si sarebbero potute evitare implementando funzioni apposite. Così
 * non piace nemmeno a me, se poi ho tempo per il refactoring la sistemo.
 *
 * @param cont_arr Array dei contatti.
 * @param curr_al Dimensione attuale dell'array dei contatti.
 * @param isEmpty Puntatore al flag che indica se l'array è vuoto o meno.
 * @return Viene ritornata una variabile di tipo Delete. Int counter indica il numero di record che sono stati
 * eliminati mentre il flag alert indica se tutti i campi dell'array sono stati eliminati o meno (true sì, false no).
 */
Delete remFromArray(Contatto *cont_arr, int *curr_al, _Bool *is_empty) {
    int i, j;
    int choice, remIndx;
    char remStr[LENGTH + 1];
    Delete removed;

    removed.alert = false;
    removed.counter = 0;

    choice = menu("\nRIMUOVI\n"
                  "1) Rimuovi contatti con un certo nome\n"
                  "2) Rimuovi contatti con un certo cognome\n"
                  "3) Rimuovi una categoria di contatti\n"
                  "4) Rimuovi un contatto con un certo indice\n"
                  "5) Elimina tutta la rubrica\n",
                  REM_MIN, REM_MAX);

    switch (choice) {
        case 1:
            printf("Inserisci il nome dei contatti che vuoi eliminare: ");
            readLine(remStr, LENGTH + 1);
            for(i = 0; i < *curr_al; i++) {
                if (strcmp(remStr, cont_arr[i].nome) == 0) {
                    for (j = i; j < *curr_al; j++)
                        cont_arr[j] = cont_arr[j + 1];
                    removed.counter++;
                    i--;
                }
            }

            /* Se la differenza tra la dimensione dell'array e il numero dei campi eliminati è uguale a 0 viene
             * mandato un segnale di allerta e, nella funzione start, al posto che una riallocazione si procederà
             * a liberare la memoria allocata per l'array dinamico (free) e ad una nuova allocazione (malloc). */
            if (*curr_al - removed.counter == 0) {
                removed.alert = true;
                *is_empty = true;
            }

            return removed;
        case 2:
            printf("Inserisci il cognome dei contatti che vuoi eliminare: ");
            readLine(remStr, LENGTH + 1);
            for(i = 0; i < *curr_al; i++) {
                if (strcmp(remStr, cont_arr[i].cognome) == 0) {
                    for (j = i; j < *curr_al; j++)
                        cont_arr[j] = cont_arr[j + 1];
                    removed.counter++;
                    i--;
                }
            }

            if (*curr_al - removed.counter == 0) {
                removed.alert = true;
                *is_empty = true;
            }

            return removed;
        case 3:
            choice = menu("Quale categoria?\n"
                          "1) Lavoro\n"
                          "2) Famiglia\n"
                          "3) Amici\n"
                          "4) Altro\n",
                          LAVORO, ALTRO);

            for(i = 0; i < *curr_al; i++) {
                if (cont_arr[i].gruppo == choice) {
                    for (j = i; j < *curr_al; j++)
                        cont_arr[j] = cont_arr[j + 1];
                    removed.counter++;
                    i--;
                }
            }

            if (*curr_al - removed.counter == 0) {
                removed.alert = true;
                *is_empty = true;
            }

            return removed;
        case 4:
            printThemAll(cont_arr, curr_al);
            printf("Inserisci l'indice del contatto che vuoi eliminare: ");
            scanf("%d", &remIndx);
            ignoreInputUntil('\n');

            remIndx--;

            /* Questo ciclo potrebbe essere ottimizzato o addirittura rimosso per evitare di dover scorrere tutto
             * l'array. Per ora lo lascio così, poi se ho tempo per il refactoring lo sistemo. */
            for(i = 0; i < *curr_al; i++) {
                if (i == remIndx) {
                    for (j = i; j < *curr_al; j++) {
                        cont_arr[j] = cont_arr[j + 1];
                    }
                    removed.counter++;
                }
            }

            if (*curr_al - removed.counter == 0) {
                removed.alert = true;
                *is_empty = true;
            }

            return removed;
        case 5:
            removed.alert = true;
            *is_empty = true;
            return removed;
    }
}

/**
 * Stampa a schermo tutti i contatti presenti nell'array dei contatti in ordine alfabetico.
 *
 * @param cont_arr Array dei contatti.
 * @param curr_al Dimensione dell'array dei contatti.
 * @param isEmpty Flag che indica se l'array è vuoto o meno.
 */
void printThemAll(Contatto *cont_arr, int *curr_al) {
    int i;

    printf("LISTA DEI CONTATTI:\n");

    for (i = 0; i < *curr_al; i++) {
        printf("[%d]\n", i + 1);
        printContact(&cont_arr[i]);
    }
}

/**
 * Gestisce la ricerca di uno o più contatti in base a diversi criteri.
 *
 * @param cont_arr Array dei contatti.
 * @param curr_al Dimensione dell'array dei contatti.
 */
void searchContact(Contatto *cont_arr, int *curr_al) {
    int choice, i;
    char searchString[LENGTH + 1];

    choice = menu("\nRICERCA PER\n"
                  "1) Nome\n"
                  "2) Cognome\n"
                  "3) E-mail\n"
                  "4) Telefono\n"
                  "5) Categoria\n",
                  SEARCH_MIN, SEARCH_MAX);

    switch (choice) {
        case 1:
            printf("Inserisci il nome o parte di esso: ");
            readLine(searchString, LENGTH + 1);

            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (strstr(cont_arr[i].nome, searchString))
                    printContact(&cont_arr[i]);
            break;
        case 2:
            printf("Inserisci il cognome o parte di esso: ");
            readLine(searchString, LENGTH + 1);

            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (strstr(cont_arr[i].cognome, searchString))
                    printContact(&cont_arr[i]);
            break;
        case 3:
            printf("Inserisci l'e-mail o parte di essa: ");
            readLine(searchString, LENGTH + 1);

            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (strstr(cont_arr[i].email, searchString))
                    printContact(&cont_arr[i]);
            break;
        case 4:
            printf("Inserisci il numero di telefono o parte di esso: ");
            readLine(searchString, LENGTH + 1);

            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (strstr(cont_arr[i].telefono, searchString))
                    printContact(&cont_arr[i]);
            break;
        case 5:
            searchByCategory(cont_arr, curr_al);
            break;
    }
}

/**
 * Gestisce la ricerca per categoria.
 *
 * @param cont_arr Array dei contatti.
 * @param curr_al Dimensione dell'array dei contatti.
 */
void searchByCategory(Contatto *cont_arr, int *curr_al) {
    int choice, i;

    choice = menu("Per quale categoria desideri ricercare?\n"
                  "1) Lavoro\n"
                  "2) Famiglia\n"
                  "3) Amici\n"
                  "4) Altro\n",
                  LAVORO, ALTRO);

    switch (choice) {
        case LAVORO:
            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (cont_arr[i].gruppo == LAVORO)
                    printContact(&cont_arr[i]);
            break;
        case FAMIGLIA:
            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (cont_arr[i].gruppo == FAMIGLIA)
                    printContact(&cont_arr[i]);
            break;
        case AMICI:
            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (cont_arr[i].gruppo == AMICI)
                    printContact(&cont_arr[i]);
            break;
        case ALTRO:
            printf("\nRECORD TROVATI:\n");
            for(i = 0; i < *curr_al; i++)
                if (cont_arr[i].gruppo == ALTRO)
                    printContact(&cont_arr[i]);
            break;
    }
}

/**
 * Ordina alfabeticamente l'array dei contatti: prima il nome, poi il cognome.
 *
 * @param cont_arr Puntatore all'array dei contatti.
 * @param currAl Lunghezza dell'array dei contatti.
 */
void sortArray(Contatto *cont_arr, int *curr_al) {
    Contatto tmp; // Variabile d'appoggio per lo swap
    char nameSurname1[LENGTH * 2 + 1], nameSurname2[LENGTH * 2 + 1];
    int i, j;

    /* Algoritmo di ordinamento sulle stringhe concatenate di nome e cognome per ogni elemento nell'array
     * dei contatti. L'intero array dei contatti viene visto come una matrice dove le righe sono i contatti e le
     * colonne le stringhe concatenate di nome e cognome di ogni contatto. Ad ogni ciclo for esterno, ogni elemento
     * dell'array viene comparato con tutti quelli seguenti e, se alfabeticamente successivo a qualcuno di questi,
     * viene effettuato uno swap. */
    for(i = 0; i < *curr_al; i++) {
        concat(nameSurname1, cont_arr[i].nome, cont_arr[i].cognome);
        for(j = i + 1; j < *curr_al; j++) {
            concat(nameSurname2, cont_arr[j].nome, cont_arr[j].cognome);
            // Swap
            if (strcmp(nameSurname1, nameSurname2) > 0) {
                tmp = cont_arr[i];
                cont_arr[i] = cont_arr[j];
                cont_arr[j] = tmp;
            }
        }
    }
}

/**
 * Inserisce in una stringa vuota la concatenazione di altre due stringhe.
 *
 * @param conc_here Stringa vuota.
 * @param p_str1 Stringa da concatenare in prima posizione.
 * @param p_str2 Stringa da concatenare in seconda posizione.
 */
void concat(char *conc_here, char *p_str1, char *p_str2) {
    strcpy(conc_here, p_str1);
    strcat(conc_here, p_str2);
}

/**
 * Visualizza un menu e chiede all'utente quale operazione effettuare.
 *
 * @param str Contenuto del menu.
 * @param min Valore minimo accettato.
 * @param max Valore massimo accettato.
 * @return Scelta dell'utente.
 */
int menu(char str[], int min, int max) {
    int choice;
    _Bool isOk;

    do {
        printf("%s", str);
        scanf("%d", &choice);
        ignoreInputUntil('\n');

        isOk = checkRange(choice, min, max, "Errore: scelta non valida.");
    } while(!isOk);

    return choice;
}

/**
 * Gestisce l'allocazione e la riallocazione di un array dinamico di tipo Contatto.
 *
 * @param curr_al Puntatore alla variabile che indica la lunghezza attuale dell'array dinamico.
 * @param upd_al Puntatore alla variabile che indica la nuova lunghezza desiderata dell'array dinamico.
 * @param cont_arr Puntatore all'array dinamico, utile in caso di riallocazione.
 * @param flag Se false alloca, se true rialloca.
 * @return Puntatore all'array dinamico allocato o riallocato.
 */
Contatto *allocate(int *curr_al, int *upd_al, Contatto *cont_arr, _Bool flag) {
    Contatto *new_alloc = NULL;
    int buffer;

    switch (flag) {
        /* Allocazione */
        case false:
            *upd_al = 1;
            *curr_al = *upd_al;
            new_alloc = (Contatto *) malloc (*curr_al * sizeof(Contatto));
            checkAlloc(new_alloc);
            return new_alloc;
            /* Riallocazione */
        case true:
            if (*upd_al > *curr_al) {
                buffer = *upd_al - *curr_al;
                *curr_al += buffer;
                new_alloc = (Contatto *) realloc (cont_arr, *curr_al * sizeof(Contatto));
                checkAlloc(new_alloc);
                *upd_al += 1; // Incrementa la conta dei record di 1 per il prossimo inserimento.
                return new_alloc;
            } else if (*upd_al < *curr_al) {
                buffer = *curr_al - *upd_al;
                *curr_al -= buffer;
                new_alloc = (Contatto *) realloc (cont_arr, *curr_al * sizeof(Contatto));
                *upd_al += 1; // Incrementa la conta dei record di 1 per il prossimo inserimento.
                checkAlloc(new_alloc);
                return new_alloc;
            } else {
                *upd_al += 1; // Incrementa la conta dei record di 1 per il prossimo inserimento.
                return cont_arr;
            }
    }
}

/**
 * Controlla se l'allocazione di memoria per un array di tipo Contatto è andata a buon fine. Se così non fosse
 * termina il programma.
 *
 * @param p_alloc Puntatore alla nuova allocazione.
 */
void checkAlloc(Contatto *p_alloc) {
    if (p_alloc == NULL) {
        printf("Errore: allocazione non riuscita.");
        exit(-1);
    }
}

/**
 * Controlla se l'allocazione di memoria per un array di tipo int è andata a buon fine. Se così non fosse termina
 * il programma.
 *
 * @param p_alloc Puntatore alla nuova allocazione.
 */
void checkIntAlloc(int *p_alloc) {
    if (p_alloc == NULL) {
        printf("Errore: allocazione non riuscita.");
        exit(-1);
    }
}

/**
 * Prende in ingresso un nuovo contatto e acquisisce in input tutti i campi.
 *
 * @param p_new Puntatore al nuovo contatto.
 * @param isEmpty Puntatore al flag che indica se l'array è vuoto o meno.
 */
void newContact(Contatto *p_new, _Bool *is_empty) {
    getInput(p_new->nome, LENGTH + 1, NOME, NAME_LABEL);
    getInput(p_new->cognome, LENGTH + 1, COGNOME, SRNAME_LABEL);
    getInput(p_new->telefono, TEL_LENGTH + 1, TELEFONO, TEL_LABEL);
    getInput(p_new->email, LENGTH + 1, EMAIL, EMAIL_LABEL);
    p_new->gruppo = getGroup(GROUP_LABEL);
    *is_empty = false;
}

/**
 * Popola una stringa di caratteri inserendo il terminatore alla fine di essa quando viene premuto il carattere '\n'
 * o quando si raggiunge la sua fine. Vengono effettuati controlli sulla lunghezza della stringa per evitare di
 * riempire il buffer con input indesiderati.
 *
 * @param str Stringa da popolare.
 * @param length Lunghezza della stringa.
 */
void readLine(char str[], int length) {
    int i = 0; // Indice.
    char ch; // Variabile di buffer.

    /* Il ciclo viene ripetuto finché non viene premuto il carattere '\n' */
    do {
        /* Se */
        if (i != length) {
            ch = getchar();
            str[i] = ch;
            i++;
            /* Se si arriva alla fine della stringa, ogni nuovo carattere digitato viene ignorato dalla funzione
             * ignoreInputUntil e viene inserito il carattere '\n' nella variabile di buffer ch in maniera tale da
             * causare l'uscita dal ciclo do-while. */
        } else {
            ignoreInputUntil('\n');
            ch = '\n';
            str[i] = ch;
            i++;
        }
    } while(ch != '\n');

    str[i - 1] = '\0'; // Inserimento del terminatore dopo l'ultimo carattere digitato in input.
}

/**
 * Ignora tutti i caratteri digitati finché non viene digitato il carattere endCh.
 *
 * @param endCh Quando viene digitato il carattere endCh la funzione termina.
 */
void ignoreInputUntil(char endCh) {
    char ch;

    do {
        ch=getchar();
    } while(ch != endCh);
}

/**
 * Riceve in ingresso la stringa da validare ed un intero che indica il tipo di validazione.
 *
 * @param str Stringa da validare.
 * @param ctrl Tipo di validazione.
 * @return 0 e il messaggio "OK" se la stringa è valida, altrimenti un codice di errore e il relativo messaggio.
 */
Response validator(char str[], Controllo ctrl) {
    Response res;
    int i, j, k;

    /* Stringa locale dove verrà copiata la stringa ricevuta come parametro per essere elaborata dai controlli.
     * Inizialmente si è pensato di implementare la funzione in questo modo per permettere all'utente di inserire i
     * campi dei contatti sia utilizzando le maiuscole che le minuscole. Successivamente, per ragioni di ordinamento,
     * si è deciso di convertire tutti gli input in lowercase, pertanto questa stringa di supporto come anche le
     * successive chiamate a strcpy e toLowercase risultano ora ridondanti. */
    char strLocal[strlen(str) + 1];

    strcpy(strLocal, str); // Copia della stringa ricevuta come parametro.
    toLowercase(strLocal); // strLocal viene convertita il lowercase per facilitare i controlli

    i = 0;
    j = strlen(strLocal);

    /* Se la stringa inizia con '\n' o ' ', viene restituito il codice di errore -1: il campo non può essere vuoto o
     * iniziare con uno spazio. */
    if (strLocal[i] == ' ' || strLocal[i] == '\0') {
        strcpy(res.message, "Errore, il campo non può essere vuoto o iniziare con uno spazio.");
        res.code = -1;
        return res;
    }

    switch(ctrl) {

        case NOME:
        case COGNOME:
            while(strLocal[i] != '\0') {
                /* Se all'interno della stringa del nome o del cognome sono presenti caratteri diversi dalle lettere
                 * dell'alfabeto latino, viene restituito il codice di errore -2. */
                if (strLocal[i] < 'a' || strLocal[i] > 'z') {
                    strcpy(res.message, "Errore, il nome e il cognome possono contenere solo lettere.");
                    res.code = -2;
                    return res;
                }
                i++;
            }
            break;

        case TELEFONO:
            while(strLocal[i] != '\0') {
                /* Se all'interno della stringa del numero di telefono sono presenti caratteri diversi dalle cifre,
                 * viene restituito il codice di errore -3. */
                if (strLocal[i] < '0' || strLocal[i] > '9'){
                    strcpy(res.message, "Errore, il numero di telefono può contenere solamente cifre.");
                    res.code = -3;
                    return res;
                }
                i++;
            }
            break;

        case EMAIL:
            while(strLocal[i] != '@' && i != j) // Cicla fino a trovare la posizione del carattere '@' o, nel caso non fosse presente, fino alla fine della stringa.
                i++;
            while(strLocal[j] != '.' && j != -1) // Cicla fino a trovare la posizione del carattere '.' o, nel caso non fosse presente, fino all'inizio della stringa.
                j--;

            /* Se l'indirizzo email termina con il carattere '.' viene restituito il codice di errore -4. */
            if (strLocal[j + 1] == '\0') {
                strcpy(res.message, "Errore, l'indirizzo email non può terminare con un punto.");
                res.code -4;
                return res;
            }

            /* Se il carattere '.' si trova prima del carattere '@' viene restituito il codice di errore -5. */
            if (i > j) {
                strcpy(res.message, "Errore, il formato dell'email non è valido.");
                res.code = -5;
                return res;
            }

            /* Controlla che il nome utente non inizi e non finisca con un carattere diverso da una lettera o una
             * cifra. Se lo fa restituisce il codice di errore -6. */
            if (((strLocal[0] < 'a' || strLocal[0] > 'z') && (strLocal[0] < '0' || strLocal[0] > '9')) || ((strLocal[i - 1] < 'a' || strLocal[i - 1] > 'z') && (strLocal[i - 1] < '0' || strLocal[i - 1] > '9'))) {
                strcpy(res.message, "Errore, il nome utente deve iniziare e terminare con una lettera o un numero.");
                res.code = -6;
                return res;
            }

            /* Controlla che il dominio di secondo livello non inizi e non finisca con un carattere diverso da una
             * lettera o una cifra. Se lo fa restituisce il codice di errore -7. */
            if (((strLocal[i + 1] < 'a' || strLocal[i + 1] > 'z') && (strLocal[i + 1] < '0' || strLocal[i + 1] > '9')) || ((strLocal[j - 1] < 'a' || strLocal[j - 1] > 'z') && (strLocal[j - 1] < '0' || strLocal[j - 1] > '9'))) {
                strcpy(res.message, "Errore, il dominio deve iniziare e terminare con una lettera o un numero.");
                res.code = -7;
                return res;
            }

            /* Controlla che non siano presenti caratteri invalidi nel nome utente. Se presenti restituisce il
             * codice di errore -8. */
            for(k = 0; k < i; k++)
                if ((strLocal[k] < 'a' || strLocal[k] > 'z') && (strLocal[k] < '0' || strLocal[k] > '9') && strLocal[k] != '-' && strLocal[k] != '.' && strLocal[k] != '_') {
                    strcpy(res.message, "Errore, sono presenti caratteri non validi nel nome utente.");
                    res.code = -8;
                    return res;
                }

            /* Controlla che non siano presenti caratteri invalidi nel dominio di secondo livello. Se presenti
             * restituisce il codice di errore -9. */
            for(k = i + 1; k < j; k++)
                if ((strLocal[k] < 'a' || strLocal[k] > 'z') && (strLocal[k] < '0' || strLocal[k] > '9') && strLocal[k] != '-' && strLocal[k] != '.' && strLocal[k] != '_') {
                    strcpy(res.message, "Errore, sono presenti caratteri non validi nel dominio.");
                    res.code = -9;
                    return res;
                }

            /* Controlla che non siano presenti caratteri invalidi nel dominio di primo livello. Se presenti
             * restituisce il codice di errore -10. */
            for(k = j + 1; k < strlen(strLocal); k++)
                if (strLocal[k] < 'a' || strLocal[k] > 'z') {
                    strcpy(res.message, "Errore, sono presenti caratteri non validi nel dominio.");
                    res.code = -10;
                    return res;
                }
            break;
    }

    /* Se all'interno della stringa non è presente alcun errore, viene restituito il valore 0 */
    strcpy(res.message, "OK");
    res.code = 0;
    return res;
}

/**
 * Converte una stringa in lettere minuscole.
 *
 * @param str Stringa da convertire.
 */
void toLowercase(char str[]) {
    int i = 0;

    while(str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        i++;
    }
}

/**
 * Prende in ingresso un input e esegue un controllo su di esso.
 *
 * @param in_str Stringa di input.
 * @param length Lunghezza della stringa di input.
 * @param ctrl Tipo di controllo da eseguire.
 * @param label Label da visualizzare nella printf.
 */
void getInput(char *in_str, int length, Controllo ctrl, char label[]) {
    Response check;

    do {
        printf("%s: ", label);
        readLine(in_str, length);
        toLowercase(in_str);
        check = validator(in_str, ctrl);

        if (check.code != 0) {
            printf("%s", check.message);
            ignoreInputUntil('\n');
        }
    } while(check.code != 0);
}

/**
 * Acquisisce l'input relativo al gruppo di contatti.
 *
 * @return Gruppo di contatti.
 */
TipologiaContatto getGroup(char label[]) {
    TipologiaContatto gruppo;
    _Bool isOk;

    do {
        printf("%s", label);
        scanf("%d", &gruppo);
        ignoreInputUntil('\n');

        isOk = checkRange(gruppo, LAVORO, ALTRO, "Errore, scelta non valida.");
    } while(!isOk);
    return gruppo;
}

/**
 * Controlla se un valore è compreso all'interno di un certo intervallo. Se lo è restituisce true, altrimenti
 * restituisce false e stampa un messaggio di errore.
 *
 * @param toCheck Valore da controllare.
 * @param min Minimo valore dell'intervallo.
 * @param max Massimo valore dell'intervallo.
 * @param msg Messaggio da stampare nel caso in cui il valore non sia compreso nell'intervallo.
 * @return false se non è compreso, true se è compreso.
 */
_Bool checkRange(int toCheck, int min, int max, char msg[MESSAGE]) {
    if (toCheck < min || toCheck > max) {
        printf("%s", msg);
        ignoreInputUntil('\n');

        return false;
    }

    return true;
}

/**
 * Prende in ingresso un contatto e lo stampa a video.
 *
 * @param p_cont Puntatore al contatto da stampare a video.
 */
void printContact(Contatto *p_cont) {
    printf("%s %s\n%s - %s\nGruppo: ", p_cont->nome, p_cont->cognome, p_cont->telefono, p_cont->email);

    switch (p_cont->gruppo) {
        case LAVORO:
            printf("Lavoro\n");
            break;
        case FAMIGLIA:
            printf("Famiglia\n");
            break;
        case AMICI:
            printf("Amici\n");
            break;
        case ALTRO:
            printf("Altro\n");
            break;
    }

    printf("\n");
}

/**
 * Prende in ingresso un contatto e ne modifica un campo dopo aver chiesto all'utente quale campo vuole modificare.
 *
 * @param p_cont Puntatore al contatto da modificare.
 */
void modifyContact(Contatto *p_cont) {
    int choice;
    _Bool isOk;

    do {
        printf("\n");
        printContact(p_cont);

        printf("Quale campo vuoi modificare?\n"
               "1) Nome\n"
               "2) Cognome\n"
               "3) Telefono\n"
               "4) E-mail\n"
               "5) Gruppo\n");
        scanf("%d", &choice);
        ignoreInputUntil('\n');

        isOk = checkRange(choice, MODIF_MIN, MODIF_MAX, "Errore: scelta non valida.");
    } while(!isOk);

    switch (choice) {
        case 1:
            getInput(p_cont->nome, LENGTH + 1, NOME, NAME_LABEL);
            break;
        case 2:
            getInput(p_cont->cognome, LENGTH + 1, COGNOME, SRNAME_LABEL);
            break;
        case 3:
            getInput(p_cont->telefono, LENGTH + 1, TELEFONO, TEL_LABEL);
            break;
        case 4:
            getInput(p_cont->email, LENGTH + 1, EMAIL, EMAIL_LABEL);
            break;
        case 5:
            p_cont->gruppo = getGroup(GROUP_LABEL);
            break;
    }
}

/**
 * Gestisce la modifica di un contatto nell'array cercandolo per il cognome.
 *
 * @param cont_arr Array dei contatti.
 * @param curr_al Lunghezza dell'array dei contatti.
 * @param isEmpty Flag che indica se l'array dei contatti è vuoto o meno.
 */
void modInArray(Contatto *cont_arr, int *curr_al) {
    char searchString[LENGTH + 1];
    int i = 0, j = 0;
    int choice;
    int size = 1, target;
    int *index_array; // Array dove verranno memorizzati gli indici dei record trovati.
    int *search_array; // Array dove verranno memorizzati gli indici visualizzati all'utente dei record trovati.
    _Bool isOk;

    index_array = (int *) malloc(size * sizeof(int));
    checkIntAlloc(index_array);
    search_array = (int *) malloc(size * sizeof(int));
    checkIntAlloc(search_array);

    printf("Inserisci parte del cognome del contatto da modificare: ");
    readLine(searchString, LENGTH + 1);

    printf("\nRECORD TROVATI:\n");
    for (i = 0; i < *curr_al; i++)
        if (strstr(cont_arr[i].cognome, searchString)) {
            j++;
            printf("[%d]\n", j);
            printContact(&cont_arr[i]);
            search_array = (int *) realloc(search_array, j + 1 * sizeof(int));
            checkIntAlloc(search_array);
            index_array = (int *) realloc(index_array, j + 1 * sizeof(int));
            checkIntAlloc(index_array);
            search_array[j - 1] = j;
            index_array[j - 1] = i;
        }

    printf("Inserisci l'indice del contatto da modificare: ");
    scanf("%d", &choice);
    isOk = checkRange(choice, search_array[0], search_array[j - 1], "L'indice non identifica alcun contatto tra quelli trovati.\n");

    if (isOk) {
        for (i = 0; i < j; i++) {
            if (search_array[i] == choice)
                target = index_array[i];
        }

        modifyContact(&cont_arr[target]);
    }

    free(search_array);
    free(index_array);
}