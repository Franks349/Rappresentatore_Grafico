#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>      //Per _getch();
#include <stdlib.h>     //Per exit();
#include <cctype>       //Per isdigit() - isalpha() - ispunct() - tolower();
using namespace std;

constexpr int MAX_X = 201;
constexpr int MAX_Y = 101;
constexpr double Unita_Matrice = 0.2;

struct DefFUNZIONE;
bool Controllo_CorrettezzaF(string equazione, bool corretto[]);
int Controllo_Esponente(string equazione, char incognita);
int Controllo_Coefficiente(string equazione, char incognita, int esponente);
void Controllo_TipoF(DefFUNZIONE& f);
void Risoluzione_Frazioni(DefFUNZIONE& f);
DefFUNZIONE Inserimento_Funzione();
int Conversione_Valore_Matrice(double x);
void Rappresentazione_Grafica(DefFUNZIONE f);

typedef struct DefFUNZIONE {

    string tipo = "";
    string equazione = "";
    struct S_CENTRO {
        double x = 0;
        double y = 0;
    }Coordinata_Centro;
    struct S_DATI {
        struct S_RETTA {
            int a = 0;
            int b = 0;
            int c = 0;
            double m = 0;
            double q = 0;
            void Calcolo_Dati(DefFUNZIONE& f) {
                if ((a != 0) && (b != 0)) {
                    a = Controllo_Coefficiente(f.equazione, 'x', 1);
                    b = Controllo_Coefficiente(f.equazione, 'y', 1);
                    c = Controllo_Coefficiente(f.equazione, '/', 0);
                    f.Coordinata_Centro.x = (-a * c) / (pow(a, 2) + pow(b, 2));
                    f.Coordinata_Centro.y = (-b * c) / (pow(a, 2) + pow(b, 2));
                    m = -a / (b + 0.0);
                    q = -c / (b + 0.0);
                }
                else {
                    cerr << "Errore logico. Arresto del programma, se si vuole riprovare si prega di riavviare manualmente" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }retta;
        struct S_PARABOLA {
            int a = 0;
            int b = 0;
            int c = 0;
            double x_Fuoco = 0;
            double y_Fuoco = 0;
            double Direttrice = 0;
            void Calcolo_Dati(DefFUNZIONE& f) {
                if (a != 0) {
                    if (f.equazione[0] == 'x') {
                        a = Controllo_Coefficiente(f.equazione, 'y', 2);
                        b = Controllo_Coefficiente(f.equazione, 'y', 1);
                        c = Controllo_Coefficiente(f.equazione, '/', 0);
                        f.Coordinata_Centro.x = -(b / (2.0 * a));
                        f.Coordinata_Centro.y = -(pow(b, 2) - (4 * a * c)) / (4.0 * a);
                        x_Fuoco = f.Coordinata_Centro.x;
                        y_Fuoco = (1 - (pow(b, 2) - (4 * a * c))) / (4.0 * a);
                        Direttrice = -(1 + (pow(b, 2) - (4 * a * c))) / (4.0 * a);
                    }
                    else if (f.equazione[0] == 'y') {
                        a = Controllo_Coefficiente(f.equazione, 'x', 2);
                        b = Controllo_Coefficiente(f.equazione, 'x', 1);
                        c = Controllo_Coefficiente(f.equazione, '/', 0);
                        f.Coordinata_Centro.x = -(pow(b, 2) - (4 * a * c)) / (4.0 * a);
                        f.Coordinata_Centro.y = -(b / (2.0 * a));
                        x_Fuoco = (1 - (pow(b, 2) - (4 * a * c))) / (4.0 * a);
                        y_Fuoco = f.Coordinata_Centro.x;
                        Direttrice = -(1 + (pow(b, 2) - (4 * a * c))) / (4.0 * a);
                    }
                }
                else {
                    cerr << "Errore logico. Arresto del programma, se si vuole riprovare si prega di riavviare manualmente" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }parabola;
        struct S_CIRCONFERENZA {
            int a = 0;
            int b = 0;
            int c = 0;
            double r = 0;
            void Calcolo_Dati(DefFUNZIONE& f) {
                a = Controllo_Coefficiente(f.equazione, 'x', 1);
                b = Controllo_Coefficiente(f.equazione, 'y', 1);
                c = Controllo_Coefficiente(f.equazione, '/', 0);
                r = sqrt((pow(a, 2) / 4.0) + (pow(b, 2) / 4.0) - c);
                if (r >= 0) {
                    int k = Controllo_Coefficiente(f.equazione, 'x', 2);
                    f.Coordinata_Centro.x = -(a / (2.0 * k));
                    f.Coordinata_Centro.y = -(b / (2.0 * k));
                }
                else {
                    cerr << "Errore logico. Arresto del programma, se si vuole riprovare si prega di riavviare manualmente" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }circonferenza;
        struct S_ELLISSE {
            int a = 0;
            int b = 0;
            int C = 0;
            int A = 0;
            int B = 0;
            double c = 0;
            double e = 0;
            double x_Fuoco1 = 0;
            double y_Fuoco1 = 0;
            double x_Fuoco2 = 0;
            double y_Fuoco2 = 0;
            void Calcolo_Dati(DefFUNZIONE& f) {
                a = Controllo_Coefficiente(f.equazione, 'x', 1);
                b = Controllo_Coefficiente(f.equazione, 'y', 1);
                C = Controllo_Coefficiente(f.equazione, '/', 0);
                A = Controllo_Coefficiente(f.equazione, 'x', 2);
                B = Controllo_Coefficiente(f.equazione, 'y', 2);
                if (A == 0 || B == 0) {
                    cerr << "Errore, ellisse degenere. Arresto del programma, se si vuole riprovare si prega di riavviare manualmente" << endl;
                    exit(EXIT_FAILURE);
                }
                if (A > B) {
                    f.Coordinata_Centro.x = -(a / (2.0 * A));
                    f.Coordinata_Centro.y = -(b / (2.0 * B));
                    c = sqrt(((1.0 / B) - (1.0 / A)));
                    x_Fuoco1 = f.Coordinata_Centro.x;
                    y_Fuoco1 = f.Coordinata_Centro.y - c;
                    x_Fuoco2 = f.Coordinata_Centro.x;
                    y_Fuoco2 = f.Coordinata_Centro.y + c;
                }
                else if (B > A) {
                    f.Coordinata_Centro.x = -(a / (2.0 * A));
                    f.Coordinata_Centro.y = -(b / (2.0 * B));
                    c = sqrt(((1.0 / A) - (1.0 / B)));
                    x_Fuoco1 = f.Coordinata_Centro.x - c;
                    y_Fuoco1 = f.Coordinata_Centro.y;
                    x_Fuoco2 = f.Coordinata_Centro.x + c;
                    y_Fuoco2 = f.Coordinata_Centro.y;
                }
            }
        }ellisse;
        struct S_IPERBOLE {
            int a = 0;
            int b = 0;
            int C = 0;
            int A = 0;
            int B = 0;
            double c = 0;
            double e = 0;
            double x_Fuoco1 = 0;
            double y_Fuoco1 = 0;
            double x_Fuoco2 = 0;
            double y_Fuoco2 = 0;
            void Calcolo_Dati(DefFUNZIONE& f) {
                a = Controllo_Coefficiente(f.equazione, 'x', 1);
                b = Controllo_Coefficiente(f.equazione, 'y', 1);
                C = Controllo_Coefficiente(f.equazione, '/', 0);
                A = Controllo_Coefficiente(f.equazione, 'x', 2);
                B = Controllo_Coefficiente(f.equazione, 'y', 2);
                if (A == 0 || B == 0) {
                    cerr << "Errore, ellisse degenere. Arresto del programma, se si vuole riprovare si prega di riavviare manualmente" << endl;
                    exit(EXIT_FAILURE);
                }
                if ((B > 0) && (A < 0)) {
                    f.Coordinata_Centro.x = -(a / (2.0 * A));
                    f.Coordinata_Centro.y = -(b / (2.0 * B));
                    c = sqrt(((1.0 / abs(A)) + (1.0 / abs(B))));
                    x_Fuoco1 = f.Coordinata_Centro.x;
                    y_Fuoco1 = f.Coordinata_Centro.y - c;
                    x_Fuoco2 = f.Coordinata_Centro.x;
                    y_Fuoco2 = f.Coordinata_Centro.y + c;
                }
                else if (B > A) {
                    f.Coordinata_Centro.x = -(a / (2.0 * A));
                    f.Coordinata_Centro.y = -(b / (2.0 * B));
                    c = sqrt(((1.0 / abs(A)) + (1.0 / abs(B))));
                    x_Fuoco1 = f.Coordinata_Centro.x - c;
                    y_Fuoco1 = f.Coordinata_Centro.y;
                    x_Fuoco2 = f.Coordinata_Centro.x + c;
                    y_Fuoco2 = f.Coordinata_Centro.y;
                }
            }
        }iperbole;
    }Dati;
}DefFUNZIONE;

int main()
{
	DefFUNZIONE f = Inserimento_Funzione();
    Rappresentazione_Grafica(f);

}

bool Controllo_CorrettezzaF(string equazione, bool corretto[]) {    //Controlla se l'equazione data in input è corretta o può essere rappresentata
    
	char iSort[2] = { '!', '!' };                       //Parallelo a iType - memorizza la definizione precedente alla modifica dell'incognita | Standardizzato a '!' per permettere di usare le stesse linee di codice per tutti i processi
	char iType[2] = { 'x', 'y' };                       //Parallelo a iSort - identifica la lettera precedente di iSort nella nuova incognita
	for (int i = 0; i < equazione.length(); i++) {      //Converte le incognite date in equazione in 'x' e 'y' per permettere un controllo più semplice - memorizza la definizione precedente in iSort per permettere di evitare errori
		int j = 0;
        if (isalpha(equazione[i])) {
            if (equazione[i] != 'x' && equazione[i] != 'y') {
                if (equazione[i] != iSort[0]) {
                    iSort[0 + j] = equazione[i];
                    equazione[i] = iType[0 + j];
                    j++;
                }
            }
        }
    }
    for (int i = 0; i < equazione.length(); i++) {
        if (i + 1 < equazione.length()) {
            if (((isalpha(equazione[i])) && (isalpha(equazione[i + 1])))) {
                cerr << "Errore: Il programma non supporta la rotazione. Arresto del programma" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
	for (int i = 0; i < equazione.length(); i++) {
        if (equazione[i] == 'x') {
			corretto[0] = true;
        }
        else if(equazione[i] == 'y') {
			corretto[1] = true;
        }
        else if(equazione[i] == '=') {
			corretto[2] = true;
            if (i == 0) {    
                equazione = '0' + equazione;
			}
			else if (i == equazione.length() - 1) {
                equazione = equazione + '0';
            }
        }
    }
    if (!corretto[0] && !corretto[1] && !corretto[2]) {
        return false;
    }else {
        return true;
    }
}
int Controllo_Esponente(string equazione, char incognita) { //Controlla e restituisce l'esponente dell'incognita data in input
    int Esp = 0;
    for (int i = 0; i < equazione.length(); i++) {    //Controllo esponenti delle incognite
        if (i + 1 < equazione.length()) {             //Controllo esponenti prima che la lunghezza dell'equazione venga egualiata per evitare errori di indice
            if (equazione[i] == incognita) {
                if ((isdigit(equazione[i + 1])) && (stoi(string(1, equazione[i + 1])) > Esp)) {  //Controlla se il carattere dopo l'incognita è un numero e se è maggiore dell'esponente memorizzato in iEsp - se è così, aggiorna iEsp con il nuovo esponente in modo da poter determinare il tipo di funzione
                    Esp = equazione[i + 1] - '0';
                }
				else {  //Se non viene trovato nessun numero dopo l'incognita, si assume sia 1 dato che l'esistenza dell'incognita è stata gia confermata in precedenza
                    Esp = 1;
                }
            }
        }
        else if (isalpha(equazione[equazione.length() - 1])) {  //Controllo esponenti delle incognite se l'ultima lettera dell'equazione è un'incognita
            if (equazione[equazione.length() - 1] == incognita) {
                Esp = 1;
            }
        }
    }
	return Esp;
}
int Controllo_Coefficiente(string equazione, char incognita, int esponente) {   //Estrae il coefficiente dell'incognita data in input con il suo esponente
    
    string coeff = {};
    if (esponente == 0) {
        for (int i = 0; i < equazione.length(); i++) {
            bool Memorizza = true;
            if (i > 0) {
                if ((isdigit(equazione[i])) && (ispunct(equazione[i - 1]) && (equazione[i] != '/'))) {
                    string Tcoeff = "";
                    if (equazione[i - 1] == '-') {
                        Tcoeff = "-";
                    }
                    for (int j = i; j < equazione.length(); j++) {
                        if (!isdigit(equazione[j])) {
                            if ((equazione[j] == 'x') || (equazione[j] == 'y')) {
                                Memorizza = false;
                                i = j;
                            }
                            if (Memorizza) {
                                coeff = Tcoeff;
                            }
                            break;
                        }
                        Tcoeff = Tcoeff + equazione[j];
                    }
                }
            }
            if (Memorizza) {
                break;
            }
        }
    }
    else {
        for (int i = 0; i < equazione.length(); i++) {
            if (equazione[i] == incognita) {
                if (i < equazione.length() - 1) {
                    if (Controllo_Esponente(equazione.substr(i, 2), incognita) == esponente) {
                        for (int j = i - 1; j >= 0; j--) {
                            if (!isdigit(equazione[j])) {
                                if (equazione[j] == '-') {
                                    coeff = '-' + coeff;
                                    if (coeff == "-") {
                                        coeff = "-1";
                                    }
                                }
                                break;
                            }
                            else {
                                coeff = equazione[j] + coeff;
                            }
                        }
                    }
                }
                else {
                    if (1 == esponente) {
                        for (int j = i - 1; j >= 0; j--) {
                            if (!isdigit(equazione[j])) {
                                if (equazione[j] == '-') {
                                    coeff = '-' + coeff;
                                    if (coeff == "-") {
                                        coeff = "-1";
                                    }
                                }
                                break;
                            }
                            else {
                                coeff = equazione[j] + coeff;
                            }
                        }
                    }
                }
            }
        }
    }
	if (coeff == "") {  //Se non viene trovato nessun coefficiente numerico prima dell'incognita, si assume che il coefficiente sia 1 dato che l'esistenza dell'incognita è stata gia confermata in precedenza
        coeff = "1";
	}
	return stoi(coeff); //Converte infine la stringa estratta nel coeffinciente numerico corrispondente
}
void Controllo_TipoF(DefFUNZIONE& f) {  //Controlla il tipo di funzione data in input

	int iEsp[2] = { Controllo_Esponente(f.equazione, 'x'), Controllo_Esponente(f.equazione, 'y')};
    if ((iEsp[0] <= 1) && (iEsp[1] <= 1)) { //Per capire se è una retta ci basta sapere se gli esponenti delle incognite sono uguali a 1 entrambi
        f.tipo = "retta";
    }
    else if (((iEsp[0] == 2 && iEsp[1] == 1)) || ((iEsp[0] == 1) && (iEsp[1] == 2))) {    //Per capire se si tratta di una parabola basta sapere se uno dei due esponenti è uguale a 2, mentre l'altro rimane 1
        f.tipo = "parabola";
    }
    else if ((iEsp[0] == 2) && (iEsp[1] == 2)) { //Le coniche centrali hanno tutte equazioni di secondo grado
        if (Controllo_Coefficiente(f.equazione, 'x', iEsp[0]) == Controllo_Coefficiente(f.equazione, 'y', iEsp[1])) {   //Una circonferenza ha entrambi i coefficienti delle incognite al quadrato uguali, sia in segno che in valore
			f.tipo = "circonferenza";
		}
        else if ((Controllo_Coefficiente(f.equazione, 'x', iEsp[0]) * Controllo_Coefficiente(f.equazione, 'y', iEsp[1]) > 0) && (Controllo_Coefficiente(f.equazione, 'x', iEsp[0]) != Controllo_Coefficiente(f.equazione, 'y', iEsp[1]))) { //Un'ellisse ha i coefficienti delle incognite alla seconda concordi, ma con valori differenti 
            f.tipo = "ellisse";
        }
        else if (Controllo_Coefficiente(f.equazione, 'x', iEsp[0]) * Controllo_Coefficiente(f.equazione, 'y', iEsp[1]) < 0) {   //Un'iperbole ha i segni dei coefficienti delle incognite alla seconda discordi tra loro, e possono essere diversi o uguali per valore, non fa differenza su questo fronte
            f.tipo = "iperbole";
        }
    }
    else {  //Qualunque altra equazione venga proposta verra definita come 'Indefinita'
        f.tipo = "Indefinita";
    }
}
void Risoluzione_Frazioni(DefFUNZIONE& f) { //Rimuove tutte le frazioni in modo da facilitare i calcoli per il programma
    int moltiplicatore = 1;
    for (int i = 0; i < f.equazione.length(); i++) {
        if ((isblank(f.equazione[i])) || (f.equazione[i] == '^')) { //Rimuove gli spazi e '^' per maneggiare meglio i calcoli
            if (i == 0) {
				f.equazione = f.equazione.substr(1, f.equazione.length() - 1);
            }
            else {
                f.equazione = f.equazione.substr(0, i) + f.equazione.substr(i + 1, f.equazione.length() - i - 1);
            }
        }
    }
    for (int i = 0; i < f.equazione.length(); i++) {
        if (f.equazione[i] == '/') {
            string TempMolt = "";
            for (int j = i; j < f.equazione.length(); j++) {
                if (!isdigit(f.equazione[j])) {
                    moltiplicatore *= stoi(TempMolt);
                    break;
                }
                else {
                    TempMolt = TempMolt + f.equazione[j];
                }
            }
        }
    }
	string TempEq = "";                                 //Copia progressivamente l'equazione correggendola - verra sostituito all'equazione originale alla fine del processo
	string TempValore = "";                             //Raccoglie e isola i termini dell'equazione che devono essere moltiplicati per il moltiplicatore
    bool Memorizza = false;                             //Indica al programma se deve memorizzare i caratteri dell'equazione in TempEq o se deve saltarli
    for (int i = 0; i < f.equazione.length(); i++) {    
        if (isalnum(f.equazione[i])) {
			Memorizza = true;
        }
        if (!Memorizza) {
			TempEq = TempEq + f.equazione[i];
        }
        else {
            int divisore = 1;
			string Suffisso = "";
			for (int j = i; j < f.equazione.length(); j++) {
                if ((!isalnum(f.equazione[j])) && (f.equazione[j] != '=')) {
					for (int k = 0; k < TempValore.length(); k++) {     //Estrae il divisore del valore temporaneo
                        if (TempValore[k] == '/') {
                            if (k == 0) {
                                cerr << "Errore logico: tentativo di dividere il nulla. Si prega di riavviare il programma" << endl;
								exit(EXIT_FAILURE);
                            }
                            divisore = stoi(TempValore.substr(k + 1, TempValore.length() - k - 1));
                            TempValore = TempValore.substr(0, k - 1);   //Non c'è bisogno di controllare se k sia maggiore di zero dato che è impossibile che accada (bisognerebbe dividere il nulla, cosa che va contro la logica)                           
                            break;
                        }
                    }
                    for (int k = 0; k < TempValore.length(); k++) {     //Rimuove la parte dell'incognita, così da lasciare solo il coefficiente appositamente per moltiplicarlo
                        if (!isdigit(TempValore[k])) {
							Suffisso = TempValore.substr(k, TempValore.length() - k) + Suffisso;   //Memorizza il resto di TempValore che verra eliminato per poterlo riaggiungere alla fine del processo
                            if (k > 0) {
                                TempValore = TempValore.substr(0, k - 1);                               
                            }
                            else {
                                TempValore = "";
                            }
                            break;
                        }
                    }
                    i = j - 1;    //Aggiorna i in modo da saltare i caratteri gia memorizzati in TempValore
                    break;
                }
                else {
					TempValore = TempValore + f.equazione[j];                   
                }
            }
            if (TempValore.empty()) {
				TempValore = "1" + TempValore;   //Se il termine da moltiplicare non inizia con un numero, si assume che il coefficiente sia 1 dato che l'esistenza dell'incognita è stata gia confermata in precedenza
            }
            if (divisore == 0) {
                divisore = 1;
            }
            else if (moltiplicatore == 0) {
                moltiplicatore = 1;
            }
			moltiplicatore = moltiplicatore / divisore;    //Aggiorna il moltiplicatore in base anche al divisore del termine da moltiplicare
            TempValore = to_string(stoi(TempValore) * moltiplicatore);
			TempEq = TempEq + TempValore + Suffisso;    //Aggiorna l'equazione temporanea con il termine moltiplicato
            Memorizza = false;
        }
    }
	f.equazione = TempEq;    //Sostituisce l'equazione originale con quella corretta senza frazioni
}
DefFUNZIONE Inserimento_Funzione() {    //Permette all'utente di inserire una funzione - ne controlla la correttezza usando funzioni ausiliarie

    DefFUNZIONE f;
	cout << "Inserire la funzione che si vuole rappresentare: " << endl;
	bool TestCorr[3] = { false, false, false };
    bool WHILEKEY = true;
    do {
        cout << "Per evitare problemi interni al programma si consiglia di utilizzare il formato a seguire, specifico per ogni funzione:\n";
        cout << "Retta: ax + by + c = 0\n" << "Parabola: y = ax^2 + bx + c\n";
        cout << "Circonferenza: x^2 + y^2 + ax + by + c = 0\n" << "Ellisse: (x^2/a^2) + (y^2/b^2) = 1\n" << "Iperbole: (x^2/a^2) - (y^2/b^2) = 1 (o viceversa per l'altra versione)\n" << endl;
        cout << "Inoltre la rotazione delle coniche non e' supportata, quindi evitare di utilizzarla" << endl;
        cout << "Inserisci l'equazione da rappresentare:\n " << endl;
        getline(cin, f.equazione);
        Risoluzione_Frazioni(f);
        if (!Controllo_CorrettezzaF(f.equazione, TestCorr)) {
            cout << "La funzione fornita è errata o incompleta: " << endl;
            cout << "|Premere invio per reinserire la funzione|\n" << "|Premere qualsiasi altro tasto per uscire|" << endl;
            if (_getch() == 13) {
                cerr << "Confermato il reinserimento della funzione: " << endl;
                WHILEKEY = false;
            }
            else {
                cerr << "Confermata l'uscita dal programma" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else {
            if (!TestCorr[2]) {

                if (TestCorr[0] && TestCorr[1]) {
                    f.equazione = f.equazione + " = 0";
                }
                else if ((!TestCorr[0] && TestCorr[1]) || (TestCorr[0] && !TestCorr[1])) {
                    cout << "La funzione fornita è errata o incompleta: " << endl;
                    cout << "|Premere invio per reinserire la funzione|\n" << "|Premere qualsiasi altro tasto per uscire|" << endl;
                    if (_getch() == 13) {
                        cerr << "Confermato il reinserimento della funzione: " << endl;
                        WHILEKEY = false;
                    }
                    else {
                        cerr << "Confermata l'uscita dal programma" << endl;
                        exit(EXIT_FAILURE);
                    }
                }               
            }
            else if (!TestCorr[0] && !TestCorr[1] && TestCorr[2]) {
                cout << "La funzione fornita è errata o incompleta: " << endl;
                cout << "|Premere invio per reinserire la funzione|\n" << "|Premere qualsiasi altro tasto per uscire|" << endl;
                if (_getch() == 13) {
                    cerr << "Confermato il reinserimento della funzione: " << endl;
                    WHILEKEY = false;
                }
                else {
                    cerr << "Confermata l'uscita dal programma" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    } while (!WHILEKEY);

    Controllo_TipoF(f);
    if (f.tipo == "retta") {
        f.Dati.retta.Calcolo_Dati(f);
    }
    else if (f.tipo == "parabola") {
        f.Dati.parabola.Calcolo_Dati(f);
    }
    else if (f.tipo == "circonferenza") {
        f.Dati.circonferenza.Calcolo_Dati(f);
    }
    else if (f.tipo == "ellisse") {
        f.Dati.ellisse.Calcolo_Dati(f);
    }
    else if (f.tipo == "iperbole") {
        f.Dati.iperbole.Calcolo_Dati(f);
    }
    else {
        cerr << "Errore, tipo di equazione inesistente o non supportata; Arresto del programma" << endl;
        exit(EXIT_FAILURE);
    }
    return f;
}
int Conversione_Valore_Matrice(double x) {
    return int(round(x / Unita_Matrice)) - 1;
}
void Rappresentazione_Grafica(DefFUNZIONE f) {
    char schermo[MAX_Y][MAX_X] = {};
    int x_Centro = 100;
    int y_Centro = 50;

    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            schermo[y][x] = ' ';
        }
    }
 
    int asse_Y = x_Centro - Conversione_Valore_Matrice(f.Coordinata_Centro.x); // Calcolo della posizione dell'origine degli assi (O) nello schermo
    int asse_X = y_Centro + Conversione_Valore_Matrice(f.Coordinata_Centro.y);

    for (int y = 0; y < MAX_Y; y++) {
        bool Y_griglia = (abs(y - asse_X) % 5 == 0);
        for (int x = 0; x < MAX_X; x++) {
            bool X_griglia = (abs(x - asse_Y) % 5 == 0);

            if (y == asse_X && x == asse_Y) {
                schermo[y][x] = '+'; //Incrocio temporaneo - viene sostituito in seguito dall'O dell'origine
            }
            else if (y == asse_X) {
                schermo[y][x] = '='; //Asse X
            }
            else if (x == asse_Y) {
                schermo[y][x] = 'H'; //Asse Y
            }
            else if (X_griglia && Y_griglia) {
                schermo[y][x] = '+';
            }
            else if (X_griglia) {
                schermo[y][x] = '|';
            }
            else if (Y_griglia) {
                schermo[y][x] = '-';
            }
        }
    }

    
    for (int y = 0; y < MAX_Y; y++) {       //Scansione dello schermo per disegnare la Funzione con '*'
        for (int x = 0; x < MAX_X; x++) {   //Conversione degli indici dello schermo (pixel) in coordinate Cartesiane pure (cX, cY)
            
            double cX = (x - asse_Y) * Unita_Matrice;
            double cY = (asse_X - y) * Unita_Matrice;
            bool appartiene = false;

            if (f.tipo == "retta") {
                
                double a = f.Dati.retta.a;
                double b = f.Dati.retta.b;
                double c = f.Dati.retta.c;
                double dist = abs(a * cX + b * cY + c) / sqrt(a * a + b * b);

                if (dist <= Unita_Matrice * 0.8) appartiene = true; //Tolleranza spessore
            }
            else if (f.tipo == "parabola") {
                
                double dist_F = sqrt(pow(cX - f.Dati.parabola.x_Fuoco, 2) + pow(cY - f.Dati.parabola.y_Fuoco, 2));
                double dist_d = 0;

                if (f.equazione[0] == 'y') { // Asse orizzontale
                    dist_d = abs(cX - f.Dati.parabola.Direttrice);
                }
                else { // Asse verticale
                    dist_d = abs(cY - f.Dati.parabola.Direttrice);
                }

                if (abs(dist_F - dist_d) <= Unita_Matrice * 1.5) appartiene = true;
            }
            else if (f.tipo == "circonferenza") {
                
                double dist_C = sqrt(pow(cX - f.Coordinata_Centro.x, 2) + pow(cY - f.Coordinata_Centro.y, 2));

                if (abs(dist_C - f.Dati.circonferenza.r) <= Unita_Matrice * 0.8) appartiene = true;
            }
            else if (f.tipo == "ellisse") {
                
                double val = f.Dati.ellisse.A * pow(cX, 2) + f.Dati.ellisse.B * pow(cY, 2) + f.Dati.ellisse.a * cX + f.Dati.ellisse.b * cY + f.Dati.ellisse.C;
                double tolleranza = (abs(f.Dati.ellisse.A * cX) + abs(f.Dati.ellisse.B * cY) + abs(f.Dati.ellisse.a) + abs(f.Dati.ellisse.b) + 1) * Unita_Matrice;

                if (abs(val) <= tolleranza) appartiene = true;
            }
            else if (f.tipo == "iperbole") {
                
                double val = f.Dati.iperbole.A * pow(cX, 2) + f.Dati.iperbole.B * pow(cY, 2) + f.Dati.iperbole.a * cX + f.Dati.iperbole.b * cY + f.Dati.iperbole.C;
                double tolleranza = (abs(f.Dati.iperbole.A * cX) + abs(f.Dati.iperbole.B * cY) + abs(f.Dati.iperbole.a) + abs(f.Dati.iperbole.b) + 1) * Unita_Matrice;

                if (abs(val) <= tolleranza) appartiene = true;
            }
            if (appartiene) { //Disegna il punto se rientra nella figura
                schermo[y][x] = '*';
            }
        }
    }
    if (asse_X >= 0 && asse_X < MAX_Y && asse_Y >= 0 && asse_Y < MAX_X) {
        schermo[asse_X][asse_Y] = 'O'; //L'origine del piano cartesiano
    }
    if (y_Centro >= 0 && y_Centro < MAX_Y && x_Centro >= 0 && x_Centro < MAX_X) {
        schermo[y_Centro][x_Centro] = 'X'; //Il centro dello schermo
    }
    for (int y = 0; y < MAX_Y; y++) { //Rendering finale
        for (int x = 0; x < MAX_X; x++) {
            cout << schermo[y][x];
        }
        cout << '\n';
    }
}


