#ifndef RUBRICA_TELEFONICA_PHONEBOOK_H
#define RUBRICA_TELEFONICA_PHONEBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 30 // Lunghezza massima dei campi nome e cognome.
#define TEL_LENGTH 15 // Lunghezza massima per il numero di telefono.
#define MESSAGE 100 // Lunghezza massima dei messaggi di errore.
#define MODIF_MIN 1 // Valore minimo per la scelta durante la modifica del contatto.
#define MODIF_MAX 5 // Valore massimo per la scelta durante la modifica del contatto.
#define MENU_MIN 1 // Valore minimo per la scelta nel menu.
#define MENU_MAX 6 // Valore massimo per la scelta nel menu.
#define SEARCH_MIN 1 // Valore minimo per la scelta nel menu di ricerca.
#define SEARCH_MAX 5 // Valore massimo per la scelta nel menu di ricerca.
#define REM_MIN 1 // Valore minimo per la scelta nel menu di rimozione.
#define REM_MAX 5 // Valore massimo per la scelta nel menu di rimozione.

/* Definizione delle label per l'inserimento dei vari campi in maniera tale da poterle modificare senza dover
 * andare a toccare il codice. */
#define NAME_LABEL "Nome"
#define SRNAME_LABEL "Cognome"
#define TEL_LABEL "Telefono"
#define EMAIL_LABEL "E-mail"
#define GROUP_LABEL "Gruppo:\n1) Lavoro\n2) Famiglia\n3) Amici\n4) Altro\n"

typedef enum {NULLCAT, LAVORO, FAMIGLIA, AMICI, ALTRO} TipologiaContatto;
typedef enum {NOME, COGNOME, TELEFONO, EMAIL} Controllo; // Enum utilizzata dalla funzione validator

typedef struct {
    char nome[LENGTH + 1];
    char cognome[LENGTH + 1];
    char telefono[TEL_LENGTH + 1];
    char email[LENGTH + 1];
    TipologiaContatto gruppo;
} Contatto;

/* Struttura per ritornare un messaggio di errore e un codice ad esso associato. Il codice non si è poi rivelato
 * utile a fini di implementazione. */
typedef struct {
    int code;
    char message[MESSAGE];
} Response;

/* Struttura utile nella funzione di rimozione di contatti dall'array dinamico. Vengono ritornati il numero dei record
 * eliminati e una variabile di flag nel caso in cui l'array sia stato svuotato totalmente. A seguito dell'aggiunta
 * del flag *is_empty nella funzione start, alert risulta ridondante. */
typedef struct {
    int counter;
    _Bool alert;
} Delete;

void start();

#endif //RUBRICA_TELEFONICA_PHONEBOOK_H