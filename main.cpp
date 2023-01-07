#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// =======================
// ========= Fisiere
// =======================

// Fisierele de intrare
#define CAST_FILE "wednesdayCast.csv"   // IMPORTAT

// Fisierele de iesire
#define FINALCAST_FILE "finalCast.csv"  // EXPORTAT
#define MENU_FILE "menu.csv"            // EXPORTAT
#define COST_FILE "cost.csv"            // EXPORTAT

// =======================
// ========= Costuri - LEI
// =======================

// Curs Valutar
#define CURS_DOLAR 4.5  // lei / dolar

// Cost Machiaj
#define COST_VAMPIR 230         // lei, Pe zi
#define COST_VARCOLAC 550       // lei, Pe zi
#define COST_SIRENA 345         // lei, Pe zi
#define COST_CLARVAZATOR 157    // lei, Pe zi
#define COST_OM 55              // lei, Pe zi

// Cost Dieta
#define COST_DIETA_NORMALA 40       // lei, Pe zi
#define COST_DIETA_VEGETARIANA 33   // lei, Pe zi
#define COST_DIETA_FLEXITARIANA 46  // lei, Pe zi

// Cost Hotel
#define COST_HOTEL_2 350    // lei, 2 Persoane / Pe noapte
#define COST_HOTEL_3 420    // lei, 3 Persoane / Pe noapte

// Cost Bautura
#define COST_APA 6      // 2l
#define COST_CAFEA 30   // 1l
#define COST_SUC 8      // 2l

// Cost Transport
#define COST_AUTOCAR 5680   // lei, 50 Persoane / One-way

// Cost Filmari
#define CHIRIE_CASTEL 10000     // lei, Pe zi
#define PROCENT_REDUCERE 0.02   // 2% reducere
#define PRAG_REDUCERE 10        // zile pana la cresterea procentului de reducere

// =======================
// ========= SETARI
// =======================
#define CAPACITATE_AUTOCAR 50   // Nr. Persoane

#define NR_FIGURANTI 132        // Nr. Persoane

#define CONSUM_APA 1.0          // l / Persoana / Zi
#define CONSUM_CAFEA 0.5        // l / Persoana / Zi
#define CONSUM_SUC 0.8          // l / Persoana / Zi


// =======================

// Clasa Cast
class CastMember{
    private:
        string nume;
        string functie;
        string clasa; // Daca este actor sau figurant
        string dieta;

    public:
        CastMember(string nume, string functie, string clasa, string dieta){
            this->nume = nume;
            this->functie = functie;
            this->clasa = clasa;
            this->dieta = dieta;
        }

        CastMember(string nume, string functie, string dieta){
            this->nume = nume;
            this->functie = functie;
            this->dieta = dieta;
            this->clasa = "N/A";
        }

        CastMember(string nume, string functie){
            this->nume = nume;
            this->functie = functie;
            this->dieta = "N/A";
            this->clasa = "N/A";
        }

        string getNume(){
            return this->nume;
        }

        string getFunctie(){
            return this->functie;
        }

        string getClasa(){
            return this->clasa;
        }

        string getDieta(){
            return this->dieta;
        }

        void setNume(string nume){
            this->nume = nume;
        }

        void setFunctie(string functie){
            this->functie = functie;
        }

        void setClasa(string clasa){
            this->clasa = clasa;
        }

        void setDieta(string dieta){
            this->dieta = dieta;
        }

        void afisare(){
            cout << "Nume: " << this->nume << endl;
            cout << "Functie: " << this->functie << endl;
            cout << "Clasa: " << this->clasa << endl;
            cout << "Dieta: " << this->dieta << endl;
        }

        ~CastMember(){
            //cout << "Destructor CastMember" << endl;
        }
};


// Clasa File Reader
class FileProcessor{
    private:
        string filename;
        vector<CastMember> cast;

        // Cost-Related
        float costMachiaj;
        float costDieta;
        float costHotel;
        float costBautura;
        float costTransport;
        float costFilmari;
        float costTotal;

    public:
        FileProcessor(string filename){
            this->filename = filename;
        }

        // Constructor Default
        FileProcessor(){
            this->filename = CAST_FILE;
        }

        vector<CastMember> getCast(){
            return this->cast;
        }

        // Se citesc doar numele si functia
        void citireCast(){
            ifstream fin(this->filename);
            string line;
            string nume, functie, clasa, dieta;

            while(getline(fin, line)){
                nume = line.substr(0, line.find(","));
                line.erase(0, line.find(",") + 1);

                functie = line.substr(0, line.find(","));
                line.erase(0, line.find(",") + 1);

                cast.push_back(CastMember(nume, functie));
            }

            fin.close();
        }

        void afisare(){
            for(int i = 0; i < this->cast.size(); i++){
                this->cast[i].afisare();
            }
        }

        // Metoda de asignare random a uneia din cele 5 clase (Vampir, Varcolac, Sirena, Clarvazator, Om)
        // Numai daca functia este actor sau figurant
        void asignareClasa(){
            for(int i = 0; i < this->cast.size(); i++){
                if(!strncmp(this->cast[i].getFunctie().c_str(), "actor", 5) || this->cast[i].getFunctie() == "figurant"){
                    int random = rand() % 5;
                    switch(random){
                        case 0:
                            this->cast[i].setClasa("Vampir");
                            break;
                        case 1:
                            this->cast[i].setClasa("Varcolac");
                            break;
                        case 2:
                            this->cast[i].setClasa("Sirena");
                            break;
                        case 3:
                            this->cast[i].setClasa("Clarvazator");
                            break;
                        case 4:
                            this->cast[i].setClasa("Om");
                            break;
                    }
                }
            }
        }

        // Metoda de asignare random a unei din cele 3 diete (Normala, Vegetarian, Flexitarian)
        // Se aplica la toti membrii cast-ului
        void asignareDieta(){
            for(int i = 0; i < this->cast.size(); i++){
                int random = rand() % 3;
                switch(random){
                    case 0:
                        this->cast[i].setDieta("Normala");
                        break;
                    case 1:
                        this->cast[i].setDieta("Vegetarian");
                        break;
                    case 2:
                        this->cast[i].setDieta("Flexitarian");
                        break;
                }
            }
        }

        // Metoda generare figuranti folosind NR_FIGURANTI
        // Numele figurantilor se genereaza random, pe baza unui fisier de nume dat
        void generareFiguranti(){
            string nume;
            string functie = "figurant";
            string clasa = "N/A";
            string dieta = "N/A";

            ifstream fin("nume.txt");
            vector<string> numeFiguranti;

            while(getline(fin, nume)){
                numeFiguranti.push_back(nume);
            }

            fin.close();

            for(int i = 0; i < NR_FIGURANTI; i++){
                int random = rand() % numeFiguranti.size();
                CastMember figurant(numeFiguranti[random], functie, clasa, dieta);
                this->cast.push_back(figurant);
            }
        }

        // Se calculeaza costul machiaju pentru fiecare membru al cast-ului
        // Pentru un numar n de zile
        float calculCostMachiaj(int n){
            float cost = 0;
            for(int i = 0; i < this->cast.size(); i++){
                if(this->cast[i].getFunctie() == "actor" || this->cast[i].getFunctie() == "figurant"){
                    if(this->cast[i].getClasa() == "Vampir"){
                        cost += COST_VAMPIR;
                    }
                    else if(this->cast[i].getClasa() == "Varcolac"){
                        cost = COST_VARCOLAC;
                    }
                    else if(this->cast[i].getClasa() == "Sirena"){
                        cost += COST_SIRENA;
                    }
                    else if(this->cast[i].getClasa() == "Clarvazator"){
                        cost += COST_CLARVAZATOR;
                    }
                    else if(this->cast[i].getClasa() == "Om"){
                        cost += COST_OM;
                    }
                }
            }

            return cost * n;
        }

        // Se calculeaza costul dietei pentru fiecare membru al cast-ului
        // Pentru un numar n de zile
        float calculCostDieta(int n){
            float cost = 0;
            for(int i = 0; i < this->cast.size(); i++){
                if(this->cast[i].getDieta() == "Normala"){
                    cost += COST_DIETA_NORMALA;
                }
                else if(this->cast[i].getDieta() == "Vegetarian"){
                    cost += COST_DIETA_VEGETARIANA;
                }
                else if(this->cast[i].getDieta() == "Flexitarian"){
                    cost += COST_DIETA_FLEXITARIANA;
                }
            }

            return cost * n;
        }

        // Se calculeaza costul total al transportului pentru fiecare membru al cast-ului
        // Se tine cont de capacitatea maxima a autocarului (CAPACITATE_AUTOCAR)
        // Se tine cont de faptul ca drumul este dus-intors
        // Se tine cont de costul unui drum de autocar (COST_AUTOCAR)
        // Se va folosi numarul minim de autocare necesare pentru a transporta tot cast-ul
        // Se va folosi modulul ceil pentru a calcula numarul minim de autocare
        // Transportul se face doar de 2 ori (dus-intors)
        float calculCostTransport(){
            float cost = 0;
            int nrAutocare = ceil((float)this->cast.size() / CAPACITATE_AUTOCAR);
            cost = nrAutocare * COST_AUTOCAR * 2;

            return cost;
        }

        // Se va calcula costul filmarilor
        // In functie de un numar n de zile
        // Reducerea porneste de la 0% si creste cu 2% la fiecare 10 zile
        // Se vor folosi variabilele CHIRIE_CASTEL, PROCENT_REDUCERE, PRAG_REDUCERE
        float calculCostFilmari(int n){
            float cost = 0;
            int nrZile = n;
            int nrReduceri = nrZile / PRAG_REDUCERE;
            float reducere = nrReduceri * PROCENT_REDUCERE;
            cost = CHIRIE_CASTEL * nrZile * (1 - reducere);

            return cost;
        }

        // Se va calcula costul tuturor recipientelor de lichid (Apa: 2l, Cafea: 1l, Suc: 2l)
        // Se va tine cont de variabilele: COST_APA, COST_CAFEA, COST_SUC
        // Se va tine cont de variabilele de consumul fiecarei persoane: CONSUM_APA, CONSUM_CAFEA, CONSUM_SUC
        // Pentru un numar n de zile
        // Consumul se calculeaza pentru toti membrii cast-ului
        // Se va folosi modulul ceil pentru a calcula numarul minim de recipienti necesare
        float calculCostLichide(int n){
            float cost = 0;
            int nrApa = ceil((float)this->cast.size() * CONSUM_APA * n / 2);
            int nrCafea = ceil((float)this->cast.size() * CONSUM_CAFEA * n / 1);
            int nrSuc = ceil((float)this->cast.size() * CONSUM_SUC * n / 2);

            cost = nrApa * COST_APA + nrCafea * COST_CAFEA + nrSuc * COST_SUC;

            return cost;
        }


        void generateMeniu(){
            // Lista 5 supe Dieta Vegetariana
            vector<string> supeVegetariene = {"Supa de legume", "Supa de varza", "Supa de spanac", "Supa de cartofi", "Supa de dovleac"};
            vector<string> EN_supeVegetariene = {"Vegetable soup", "Cabbage soup", "Spinach soup", "Potato soup", "Pumpkin soup"};
            // Lista 5 supe Dieta Normala
            vector<string> supeNormale = {"Supa de legume", "Ciorba de perisoare", "Ciorba de burta", "Ciorba de vacuta", "Ciorba radauteana de pui"};
            vector<string> EN_supeNormale = {"Vegetable soup", "Pork soup", "Beef soup", "Veal soup", "Chicken soup"};
            // Lista 5 supe Dieta Flexitariana (pe baza de Peste)
            vector<string> supeFlexitariene = {"Supa de legume", "Ciorba de crap", "Ciorba de somon", "Ciorba de ton", "Ciorba de sturion"};
            vector<string> EN_supeFlexitariene = {"Vegetable soup", "Carp soup", "Salmon soup", "Tuna soup", "Sturgeon soup"};

            // Lista 5 feluri principale Dieta Vegetariana
            vector<string> feluriVegetariene = {"Rosii umplute cu bulgur si feta", "Conopida gratinata cu branza si spanac", "Canelloni cu spanac si branza de vaci", "Iahnie de fasole cu tofu afumat", "Paste cremoase cu hummus"};
            vector<string> EN_feluriVegetariene = {"Stuffed tomatoes with bulgur and feta", "Gratinated cabbage with cheese and spinach", "Canelloni with spinach and cheese", "Bean stew with smoked tofu", "Creamy pasta with hummus"};
            // Lista 5 feluri principale Dieta Normala
            vector<string> feluriNormale = {"Snitel de pui cu cartofi prajiti", "Pui cu cartofi si legume", "Pui cu ciuperci si orez", "Varza cu ciolan afumat", "Iahnie de fasole cu carne de porc"};
            vector<string> EN_feluriNormale = {"Chicken schnitzel with fried potatoes", "Chicken with potatoes and vegetables", "Chicken with mushrooms and rice", "Cabbage with smoked sausage", "Bean stew with pork"};
            // Lista 5 feluri principale Dieta Flexitariana (pe baza de Peste)
            vector<string> feluriFlexitariene = {"Peste cu cartofi si legume", "Somon la cuptor", "Peste cu spanac si branza de vaci", "Peste cu fasole verde", "Peste cu orez"};
            vector<string> EN_feluriFlexitariene = {"Fish with potatoes and vegetables", "Baked salmon", "Fish with spinach and cheese", "Fish with green beans", "Fish with rice"};

            // Lista 5 deserturi pentru orice dieta
            vector<string> desertVegetariene = {"Tiramisu", "Cheesecake", "Papanasi cu branza dulce", "Papanasi cu branza dulce si ciocolata", "Papanasi cu branza dulce si mere"};
            vector<string> EN_desertVegetariene = {"Tiramisu", "Cheesecake", "Sweet cheese dumplings", "Sweet cheese dumplings with chocolate", "Sweet cheese dumplings with apples"};

            // Generare aleatoare a meniului pe 3 zile si exportarea lui in csv
            // Atat in engleza cat si in romana
            // Meniul se separa in 3 zile, pentru fiecare tip de dieta
            // Se tine cont de variabila MENU_FILE
            // Se va atribui un cost fiecarui fel: supa, fel principal si desert
            // Meniul vegetarien va avea un cost de COST_DIETA_VEGETARIANA
            // Meniul normal va avea un cost de COST_DIETA_NORMALA
            // Meniul flexitarian va avea un cost de COST_DIETA_FLEXITARIANA

            ofstream fout(MENU_FILE);
            // Meniu romana
            fout << "Meniu pentru 3 zile" << endl;
            fout << "Dieta Vegetariana" << endl;
            for(int i = 0; i < 3; i++){
                fout << "Ziua " << i + 1 << endl;
                fout << "Supa: " << supeVegetariene[rand() % supeVegetariene.size()] << endl;
                fout << "Fel principal: " << feluriVegetariene[rand() % feluriVegetariene.size()] << endl;
                fout << "Desert: " << desertVegetariene[rand() % desertVegetariene.size()] << endl;
                fout << COST_DIETA_VEGETARIANA << "LEI" << endl;
                fout << endl;
            }
            fout << "Dieta Normala" << endl;
            for(int i = 0; i < 3; i++){
                fout << "Ziua " << i + 1 << endl;
                fout << "Supa: " << supeNormale[rand() % supeNormale.size()] << endl;
                fout << "Fel principal: " << feluriNormale[rand() % feluriNormale.size()] << endl;
                fout << "Desert: " << desertVegetariene[rand() % desertVegetariene.size()] << endl;
                fout << COST_DIETA_NORMALA << "LEI" << endl;
                fout << endl;
            }
            fout << "Dieta Flexitariana" << endl;
            for(int i = 0; i < 3; i++){
                fout << "Ziua " << i + 1 << endl;
                fout << "Supa: " << supeFlexitariene[rand() % supeFlexitariene.size()] << endl;
                fout << "Fel principal: " << feluriFlexitariene[rand() % feluriFlexitariene.size()] << endl;
                fout << "Desert: " << desertVegetariene[rand() % desertVegetariene.size()] << endl;
                fout << COST_DIETA_FLEXITARIANA << "LEI" << endl;
                fout << endl;
            }

            // Meniu engleza
            fout << "Menu for 3 days" << endl;
            fout << "Vegetarian Diet" << endl;
            for(int i = 0; i < 3; i++){
                fout << "Day " << i + 1 << endl;
                fout << "Soup: " << EN_supeVegetariene[rand() % EN_supeVegetariene.size()] << endl;
                fout << "Main course: " << EN_feluriVegetariene[rand() % EN_feluriVegetariene.size()] << endl;
                fout << "Dessert: " << EN_desertVegetariene[rand() % EN_desertVegetariene.size()] << endl;
                fout << COST_DIETA_VEGETARIANA / CURS_DOLAR << "USD" << endl;
                fout << endl;
            }
            fout << "Normal Diet" << endl;
            for(int i = 0; i < 3; i++){
                fout << "Day " << i + 1 << endl;
                fout << "Soup: " << EN_supeNormale[rand() % EN_supeNormale.size()] << endl;
                fout << "Main course: " << EN_feluriNormale[rand() % EN_feluriNormale.size()] << endl;
                fout << "Dessert: " << EN_desertVegetariene[rand() % EN_desertVegetariene.size()] << endl;
                fout << COST_DIETA_NORMALA / CURS_DOLAR << "USD" << endl;
                fout << endl;
            }
            fout << "Flexitarian Diet" << endl;
            for(int i = 0; i < 3; i++){
                fout << "Day " << i + 1 << endl;
                fout << "Soup: " << EN_supeFlexitariene[rand() % EN_supeFlexitariene.size()] << endl;
                fout << "Main course: " << EN_feluriFlexitariene[rand() % EN_feluriFlexitariene.size()] << endl;
                fout << "Dessert: " << EN_desertVegetariene[rand() % EN_desertVegetariene.size()] << endl;
                fout << COST_DIETA_FLEXITARIANA / CURS_DOLAR << "USD" << endl;
                fout << endl;
            }
            fout.close();
        }


        // Se va calcula costul cazarii la hotel
        // Se va tine cont de variabila de cost pentru o camera de 2 persoane: COST_HOTEL_2
        // Se va tine cont de variabila de cost pentru o camera de 3 persoane: COST_HOTEL_3
        // Camerele de 2 persoane sunt pentru cast-ul initial (citit din fisier)
        // Camerele de 3 persoane sunt pentru figuranti
        // Se va folosi modulul ceil pentru a calcula numarul minim de camere necesare
        // Se va calcula pentru un numar n de zile
        // Se va itera prin vectorul de cast pentru a calcula numarul de membri initiali si numarul de figuranti
        float calculCostCazare(int n){
            
            int nr_membri_initiali = 0;
            int nr_figuranti = 0;
            // Se testeaza daca un membru al cast-ului este figurant
            for(int i = 0; i < this->cast.size(); i++){
                if(this->cast[i].getFunctie() == "Figurant"){
                    nr_figuranti++;
                }
                else{
                    nr_membri_initiali++;
                }
            }
            
            float cost = 0;
            int nrCamere2 = ceil((float)nr_membri_initiali / 2);
            int nrCamere3 = ceil((float)nr_figuranti / 3);

            cost = nrCamere2 * COST_HOTEL_2 * n + nrCamere3 * COST_HOTEL_3 * n;

            return cost;
        }

        // Se exporta cast-ul final cu toate informatiile fiecarui membru
        void scriereCast(){
            ofstream fout(FINALCAST_FILE);
            for(int i = 0; i < this->cast.size(); i++){
                fout << this->cast[i].getNume() << " " << this->cast[i].getFunctie() << endl;
            }
            fout.close();
        }


        ~FileProcessor(){
            cout << "Destructor FileProcessor" << endl;
        }

        // Se va crea un fisier cu costul pentru fiecare scenariu de buget
        // Se va tine cont de variabilele de cost de la inceputul fisierului
        // Se va exprima atat in engleza cat si in romana
        // Costurile se exprima in lei in romana, iar in dolari in engleza
        // Se va lua un vector de numar de zile pentru fiecare scenariu de buget ca parametru
        // Costurile se impart in: transport, cazare, machiaj, mancare si apa, inchiriere spatiu
        // Se va tine cont de filepath-ul COST_FILE
        // Se vor folosi toate metodele de mai sus pentru a calcula costurile
        // Fisierul se va imparti pentru fiecare perioada de timp din vectorul de zile
        // Se va scrie in fisierul de iesire costul total pentru fiecare perioada de timp
        void CostFinal(vector<int> nrZile){
            ofstream fout(COST_FILE);
            // Romana
            for(int i = 0; i < nrZile.size(); i++){
                fout << "Scenariu " << i + 1 << endl;
                fout << "Costul total pentru " << nrZile[i] << " zile este: " << endl;
                fout << "Transport: " << calculCostTransport() << " RON" << endl;
                fout << "Cazare: " << calculCostCazare(nrZile[i]) << " RON" << endl;
                fout << "Machiaj: " << calculCostMachiaj(nrZile[i]) << " RON" << endl;
                fout << "Mancare si apa: " << calculCostDieta(nrZile[i]) + calculCostLichide(nrZile[i]) << " RON" << endl;
                fout << "Inchiriere spatiu: " << calculCostFilmari(nrZile[i]) << " RON" << endl;
                fout << endl;
            }

            // Engleza
            for(int i = 0; i < nrZile.size(); i++){
                fout << "Scenario " << i + 1 << endl;
                fout << "Total cost for " << nrZile[i] << " days is: " << endl;
                fout << "Transport: " << calculCostTransport() / CURS_DOLAR << " USD" << endl;
                fout << "Accommodation: " << calculCostCazare(nrZile[i]) / CURS_DOLAR << " USD" << endl;
                fout << "Makeup: " << calculCostMachiaj(nrZile[i]) / CURS_DOLAR << " USD" << endl;
                fout << "Food and water: " << (calculCostDieta(nrZile[i]) + calculCostLichide(nrZile[i])) / CURS_DOLAR << " USD" << endl;
                fout << "Renting space: " << calculCostFilmari(nrZile[i]) / CURS_DOLAR << " USD" << endl;
                fout << endl;
            }

            fout.close();
        }

        void afisareCast(){
            for(int i = 0; i < this->cast.size(); i++){
                cout << "Nr. " << i << " " << this->cast[i].getNume() << " " << this->cast[i].getFunctie() << endl;
            }}

};


// Functie care sterge toate fisierele dupa ce s-au terminat calculele
void delete_all_files(){
    remove(FINALCAST_FILE);
    remove(MENU_FILE);
    remove(COST_FILE);
}





int main(){

    // Se initializeaza generatorul de numere aleatoare
    srand(time(NULL));

    // Se creeaza un obiect de tip FileProcessor
    FileProcessor fp;

    // Se declara vectorul cu numarul de zile pentru fiecare scenariu de buget
    vector<int> nrZile = {30, 45, 60, 100};

    // Se sterg fisierele daca exista
    // delete_all_files();

    // Se citeste cast-ul din fisierul de intrare
    fp.citireCast();


    // Se genereaza figurantii
    fp.generareFiguranti();

    // Se fac asignarile
    fp.asignareClasa();
    fp.asignareDieta();

    // Se afiseaza cast-ul citit
    fp.afisareCast();

    // Se calculeaza costul total pentru fiecare scenariu de buget
    fp.CostFinal(nrZile);

    // Se scrie meniul in fisierul de iesire
    fp.generateMeniu();

    // Se scrie cast-ul final in fisierul de iesire
    fp.scriereCast();

    return 0;
}