Implementare una rubrica telefonica seguendo le seguenti specifiche:

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
elemento (l'ultimo). Ricordarsi sempre di restituire il puntatore al vettore dinamico.