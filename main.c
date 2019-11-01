/* Implementare una rubrica telefonica seguendo le seguenti specifiche:

0) Definire una enumerazione 'TipologiaContatto' che permetta di utilizzare i seguenti valori: lavoro, famiglia, amici,
 altri.
1) Definire una struttura 'Contatto' contenente:
- nome, cognome, numero di telefono, indirizzo email, tipologia contatto
2) Implementare una funzione o procedura che acquisisca i campi di un Contatto e restituisca tale contatto. Effettuare
 i controlli sull'input:
- nome (non vuoto, non deve contenere cifre)
- cognome (non vuoto, non deve contenere cifre)
- numero di telefono (non vuoto, non deve contenere simboli o lettere)
- indirizzo email (deve contenere almeno un carattere prima della chiocciola, almeno un carattere chiocciola, almeno un
 carattere dopo la chiocchiola, un punto e un dominio come com o it)
- tipologia (deve essere richiesto in modo semplice per l'utente, ad esempio usando un menu)
3) Implementare una procedura che stampi in modo chiaro e ordinato tutti i dati del contatto
4) Implementare una funzione o procedura che permetta la modifica di un contatto. Riceverà come parametro un contatto,
 lo stamperà e chiederà quale campo deve essere modificato. Una volta inserito il nuovo valore, a seconda dei casi il
 contatto dovrà essere restituito al chiamante o meno (dipende se si utilizza una procedura o una funzione).
5) Implementare una funzione che inizializzi un vettore dinamico. Essa dovrà allocare lo spazio per un contatto e
 restituire l'indirizzo di memoria relativo se l'allocazione è andata a buon fine. Altrimenti il programma terminerà
 comunicando all'utente tale malfunzionamento.
6) Implementare la funzione di inserimento seguendo la logica seguente: passo il contatto, aumento lo spazio del
 vettore dinamico per contenere un nuovo elemento e a questo punto inserisco il nuovo contatto seguendo l'ordine
 alfabetico. Si possono presentare due casi: inserimento in coda, inserimento non in coda. Se in coda non dovremo
 far altro che inserire il contatto nell'ultima (e nuova) posizione, altrimenti una volta trovato il contatto
 successivo in ordine alfabetico dovremo far scorrere tutti i contatti di una posizione e inserire il nuovo contatto
 nella corretta posizione. Al termine delle operazioni ricordarsi di tenere traccia dell'eventuale cambio di valore del
 puntatore al vettore dinamico.
7) Implementare la funzione di eliminazione offrendo le seguenti possibilità:
- eliminare tutta la rubrica
- eliminare un contatto con un certo indice
- eliminare tutti i contatti con un certo nome o cognome
- elininare una categoria di contatti
 8) Aggiungere alle funzionalità del programma la ricerca dei contatti offrendo le seguenti possibilità:
- ricerca mediante nome (o parte del nome)
- ricerca mediante cognome (o parte del cognome)
- ricerca mediante mail (o parte del mail)
- ricerca mediante numero
- ricerca mediante categoria

In tutti i casi dovremo sempre stare attenti a modificare lo spazio occupato dal vettore, se ad esempio abbiamo un
 vettore di 3 contatti A, B e C e dobbiamo eliminare B sposteremo C in B e riallocheremo lo spazio eliminando un
 elemento (l'ultimo). Ricordarsi sempre di restituire il puntatore al vettore dinamico. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 30

typedef enum {LAVORO, FAMIGLIA, AMICI, ALTRO} TipologiaContatto;
typedef enum {NOME, TELEFONO, EMAIL};

typedef struct {
    char nome[LENGTH + 1];
    char cognome[LENGTH + 1];
    char telefono[LENGTH + 1];
    char email[LENGTH + 1];
    TipologiaContatto gruppo;
} Contatto;

void inserisciContatto(Contatto *nuovo);
int validator(char str[], int ctrl);
void readLine(char str[], int length);
void ignoreInputUntil(char endCh);
void toLowercase(char str[]);

int main() {

    Contatto nuovoContatto;

    inserisciContatto(&nuovoContatto);

    return 0;
}

void inserisciContatto(Contatto *nuovo) {

    printf("\nNome: ");
    readLine(nuovo->nome, LENGTH + 1);
    printf("%s", nuovo->nome);
    printf("\n%d", validator(nuovo->nome, NOME));

    printf("\nCognome: ");
    readLine(nuovo->cognome, LENGTH + 1);
    printf("%s", nuovo->cognome);
    printf("\n%d", validator(nuovo->cognome, NOME));

    printf("\nTelefono: ");
    readLine(nuovo->telefono, LENGTH + 1);
    printf("%s", nuovo->telefono);
    printf("\n%d", validator(nuovo->telefono, TELEFONO));

    printf("\nE-mail: ");
    readLine(nuovo->email, LENGTH + 1);
    printf("%s", nuovo->email);
    printf("\n%d", validator(nuovo->email, EMAIL));

    printf("\nGruppo: ");
    scanf("%d", &nuovo->gruppo);
    printf("%d", nuovo->gruppo);

}

/**
 * La funzione popola una stringa di carattere inserendo il terminatore alla fine di essa quando viene premuto il
 * carattere '\n' o quando si raggiunge la sua fine. Vengono effettuati controlli sulla lunghezza della stringa per
 * evitare di riempire il buffer con input indesiderati.
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

    do{
        ch=getchar();
    } while(ch != endCh);
}

int validator(char str[], int ctrl) {
    int i, j, k;
    char strLocal[strlen(str)]; // Stringa locale dove verrà copiata la stringa ricevuta come parametro per essere elaborata dai controlli.

    strcpy(strLocal, str); // Copia della stringa ricevuta come parametro.
    toLowercase(strLocal); // strLocal viene convertita il lowercase per facilitare i controlli

    i = 0;
    j = strlen(strLocal);

    /* Se la stringa inizia con '\n' o ' ', viene restituito il codice di errore -1: il campo non può essere vuoto o
     * iniziare con uno spazio. */
    if (strLocal[i] == ' ' || strLocal[i] == '\0')
        return -1;

    switch(ctrl) {

        case NOME:
            while(strLocal[i] != '\0') {
                /* Se all'interno della stringa del nome o del cognome sono presenti caratteri diversi dalle lettere
                 * dell'alfabeto latino, viene restituito il codice di errore -2. */
                if(strLocal[i] < 'a' || strLocal[i] > 'z')
                    return -2;
                i++;
            }
            break;

        case TELEFONO:
            while(strLocal[i] != '\0') {
                /* Se all'interno della stringa del numero di telefono sono presenti caratteri diversi dalle cifre,
                 * viene restituito il codice di errore -3. */
                if(strLocal[i] < '0' || strLocal[i] > '9')
                    return -3;
                i++;
            }
            break;

        case EMAIL:
            while(strLocal[i] != '@' || i == strlen(strLocal)) // Cicla fino a trovare la posizione del carattere '@'.
                i++;
            while(strLocal[j] != '.' || i == 0) // Cicla fino a trovare la posizione del carattere '.'.
                j--;

            /* Se il carattere '.' si trova prima del carattere '@' viene restituito il codice di errore -4. */
            if (i > j)
                return -4;

            /* Controlla che il nome utente non inizi e non finisca con un carattere diverso da una lettera o una
             * cifra. Se lo fa restituisce il codice di errore -5. */
            if (((strLocal[0] < 'a' || strLocal[0] > 'z') && (strLocal[0] < '0' || strLocal[0] > '9')) || (strLocal[i - 1] < 'a' || strLocal[i - 1] > 'z') && (strLocal[i - 1] < '0' || strLocal[i - 1] > '9'))
                return -5;

            /* Controlla che il dominio di secondo livello non inizi e non finisca con un carattere diverso da una
             * lettera o una cifra. Se lo fa restituisce il codice di errore -6. */
            if (((strLocal[i + 1] < 'a' || strLocal[i + 1] > 'z') && (strLocal[i + 1] < '0' || strLocal[i + 1] > '9')) || (strLocal[j - 1] < 'a' || strLocal[j - 1] > 'z') && (strLocal[j - 1] < '0' || strLocal[j - 1] > '9'))
                return -6;

            /* Controlla che non siano presenti caratteri invalidi nel nome utente. Se presenti restituisce il
             * codice di errore -7. */
            for(k = 0; k < i; k++)
                if((strLocal[k] < 'a' || strLocal[k] > 'z') && (strLocal[k] < '0' || strLocal[k] > '9') && strLocal[k] != '-' && strLocal[k] != '.' && strLocal[k] != '_')
                    return -7;

            /* Controlla che non siano presenti caratteri invalidi nel dominio di secondo livello. Se presenti
             * restituisce il codice di errore -8. */
            for(k = i + 1; k < j; k++)
                if((strLocal[k] < 'a' || strLocal[k] > 'z') && (strLocal[k] < '0' || strLocal[k] > '9') && strLocal[k] != '-' && strLocal[k] != '.' && strLocal[k] != '_')
                    return -8;

            /* Controlla che non siano presenti caratteri invalidi nel dominio di primo livello. Se presenti
             * restituisce il codice di errore -9. */
            for(k = j + 1; k < strlen(strLocal); k++)
                if(strLocal[k] < 'a' || strLocal[k] > 'z')
                    return -9;
            break;
    }

    /* Se all'interno della stringa non è presente alcun errore, viene restituito il valore 0 */
    return 0;

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