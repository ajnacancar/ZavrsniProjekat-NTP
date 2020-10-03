#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;
enum Stanje{NEMA=1, IMA};
struct Datum{
	int dan_proizvodnje, mjesec_proizvodnje, godina_proizvodnje;
	int dan_isteka, mjesec_isteka, godina_isteka;
};
struct Kolaci{
	string id;
	string ime;
	double cijena;
	Datum datum;
	Stanje stanje;
/*
Funkcija void unosKolaca() kao sto sam naziv govori vrsi unos novog kolaca u datoteku
s tim da se ne moze unijeti kolac sa istim ID-om koji vec postoji u datoteci za to nam sluzi for(;;) petlja 
koja je objasnjena u nastavku: 
*/	
	void unosKolaca(){
	ofstream datoteka("kolaci.txt", ios::app);
		int br;
		for(;;){ // Beskonacana for petlja
			string provjera; 
			br=0;
			cout << "ID: ";
			cin >> this->id; // Unos id u objekat od strukture
			ifstream datotekakolaca("kolaci.txt"); // Otvaranje datoteke
			while(!datotekakolaca.eof()){ // Pretrazivanje datoteke i trazenje ukoliko postoji isti id
				datotekakolaca >> provjera;
				if(provjera == id){
					br++; // Ako postoji isti ID brjac se povecava
				}
			}
			if(br!=0){ // Ukoliko je brojac razlicit od nule ispisuje se poruka da taj ID vec postoji i trazi se ponovni unos
				cout << "Kolac sa tim ID-om vec postoji!\n";
				cout << "Molimo unesite drugi iD!\n";
			}else if(br==0){ // Ukoliko je brojac jednak nuli 
				break; // Izlazi se iz for petlje
			}
		}
		
		if(datoteka.is_open()){
		datoteka << "ID: " << id << endl;
		cin.ignore();
		cout << "Naziv: ";
		char *kolac = new char[50];
		cin.getline(kolac, 50);
		if(kolac[0]>='a' && kolac[0]<='z'){
			kolac[0]-=32;
		}
		ime = kolac;
		datoteka << "Naziv: " << ime << endl;
		cout << "Datum proizvodnje: ";
		cin >> this->datum.dan_proizvodnje >> this->datum.mjesec_proizvodnje >> this->datum.godina_proizvodnje;
		datoteka << "Proizvedeno: " << setfill('0') << setw(2) << this->datum.dan_proizvodnje << "." << setfill('0') << setw(2) << this->datum.mjesec_proizvodnje << "." << this->datum.godina_proizvodnje << "." << endl;
		cout << "Datum isteka: ";
		cin >> this->datum.dan_isteka >> this->datum.mjesec_isteka >> this->datum.godina_isteka;
		datoteka << "Istice: " << setfill('0') << setw(2) << this->datum.dan_isteka << "." << setfill('0') << setw(2) << this->datum.mjesec_isteka << "." << this->datum.godina_isteka << "." << endl;
								/* setfill('0') << setw(2)  znaci da se doda nula ispred jednoscifrenog nula 
								Primjer: 
								Ako unesemo datum: 5 5 2020
								U datoteku se upisuje 05.05.2020.
								*/
		cout << "Cijena: ";
		cin >> this->cijena;
		datoteka << "Cijena: " << setprecision(2) << fixed << this->cijena << endl;
		int x;
		cout << "Da li kolaca ima trenutno na stanju?\n";
		cout << "\t1. Nema na stanju\n";
		cout << "\t2. Ima na stanju\n";
		do{
			cout << "Odabir: ";
			cin >> x;
			
		}while(x<1 || x>2);
		this->stanje = Stanje(x);
		datoteka << "Stanje: ";
		if(x==1){
			datoteka << "Nema" << endl;
		}else if(x==2){
			datoteka << "Ima" << endl;
		}
	}else{
		cout << "[GRESKA] Datoteka se ne moze otvoriti!\n";
	}
		datoteka.close();
	}
	
	void pregledKolaca(){
		string provjera, tekst;
		
		cout << left << setw(8) << "ID" << left << setw(20) << "Naziv" << left << setw(15) << "Proizvedeno" << left << setw(15) << "Istice"  << left << setw(10) << "Cijena" << left << setw(10) << "Stanje" << endl;
		ifstream sort("kolaci.txt");
		if(sort.is_open()){
		
		while(!sort.eof()){
		sort >> provjera;
		if(provjera == "ID:"){
			sort >> provjera;
			cout << left << setw(8) << provjera << "";
			
		}
			if(provjera == "Naziv:"){
				tekst = "";
				cout << left << setw(20);
				do{
				sort >> provjera;
					if(provjera != "Proizvedeno:"){
						tekst += provjera + " ";
					}
				}while(provjera!="Proizvedeno:");
				cout << tekst;
				
		}
				if(provjera == "Proizvedeno:"){
					sort >> provjera;
					cout << left << setw(15) << provjera;
					
				}
				if(provjera == "Istice:"){
					sort >> provjera;
					cout << left << setw(15) << provjera;
					
				}
				
				if(provjera == "Cijena:"){
					sort >> provjera;
					cout << left << setw(10) << provjera;
					
				}
				if(provjera == "Stanje:"){
					sort >> provjera;
					cout << left << setw(10) << provjera << endl;
				}
				
			}
			cout << endl;
	}else{
		cout << "[GRESKA] Datoteka se ne moze otvoriti!\n";
	}
			sort.close();
			
}
	
	
	
	void pretragapremaID(){
		string pretraga,provjera,tekst;
		bool a=false;
		cout << "Unesite ID za pretragu: ";
		char *pomoc = new char[10];
		cin.getline(pomoc, 10);
		pretraga = pomoc;
		ifstream datoteka1("kolaci.txt");
		if(datoteka1.is_open()){
		
		while(!datoteka1.eof()){
			datoteka1 >> provjera;
			if(provjera == "ID:"){
				datoteka1 >> provjera;
				if(provjera == pretraga){
					cout << "Postoji kolac sa tim ID-om!\n";
					cout << "------------------------------------------\n";
					cout << "Podaci o kolacu:\n";
					a=true;
				}
			}
			
			if(a==true){
				if(provjera == "Naziv:"){
						tekst = "";
						do{
						datoteka1 >> provjera;
					if(provjera != "Proizvedeno:"){
						tekst += provjera + " ";
					}
				}while(provjera!="Proizvedeno:");
				cout << "Naziv: " << tekst << endl;
					}
				if(provjera == "Proizvedeno:"){
					datoteka1 >> provjera;
					cout << "Datum proizvodnje: " << provjera << endl;
				}
				if(provjera == "Istice:"){
					datoteka1 >> provjera;
					cout << "Datum isteka: " << provjera << endl;
				}
				
				if(provjera == "Cijena:"){
					datoteka1 >> provjera;
					cout << "Cijena: " << provjera << " KM" << endl;
				}
				if(provjera == "Stanje:"){
					datoteka1 >> provjera;
					cout << "Stanje: " << provjera << endl;
					break;
				}
				
				
			}
		}

		
	if(a==false){
		cout << "Ne postoji kolac sa tim ID-om!\n";
	}
		
	}else{
		cout << "[GRESKA] Datoteka se ne moze otvoriti!\n";
	}
	datoteka1.close();
}
/*
	Funkcija promjeni mijena datum odredenog kolaca na osnovu unesenog ID-a
	Prvo se provjerava da li uneseni ID postoji u datoteci, ukoliko ne postoji ispisuje se odredena poruka,
	ukoliko postoji obavlja se zamjena datuma proizvodnje i isteka
	Zamjena je opisana u nastavku: 
*/



	void Promjeni(){

		int br=0;
		
		for(;;){
			string provjera;
			cout << "ID: ";
			cin >> this->id;
			
			ifstream datotekakolaca("kolaci.txt");
			while(!datotekakolaca.eof()){
				datotekakolaca >> provjera;
				if(provjera == id){
					br=1;
				}
			}
			if(br==0){
				cout << "Kolac sa tim ID-om ne postoji!\n";
				cout << "Molimo unesite drugi iD!\n";
			}else if(br==1){
				datotekakolaca.close();
				break;
			}
			
		}	
		
		cout << "Unesite novi datum proizvodnje: ";
		cin >> datum.dan_proizvodnje >> datum.mjesec_proizvodnje >> datum.godina_proizvodnje;
		/*
		ostringstream s; 
		je deklaracija string s u koji unosimo datum ali na taj nacin da ga unosimo tako sto automatski namjestamo izgled za datoteku
		odnosno dodaje nule i tacke izmedu brojeva
		*/
		ostringstream s; 
		s << setw(2) << setfill('0') << datum.dan_proizvodnje << "." << setw(2) << setfill('0') << datum.mjesec_proizvodnje << "." << datum.godina_proizvodnje << ".";
		
	string	string_niz[1000], provjera;
	int brojac=0;
	bool nadjen = false;
	fstream file;
	file.open("kolaci.txt", ios::in);
	/*
	U ovoj while petlji se trazi ID unesenog kolaca u datoteci i broji se koliko ima linija do tog ID-a i do datuma proizvodnje jer se prvo unosi datum proizvodnje
	*/
	while(!file.eof()){
		file >> provjera;
		if(provjera == "ID:" && nadjen==false){
			file >> provjera;
			if(provjera == id){
				brojac+=2; // Kada se nade ID dodaje se +2 jer imamo jos 2 linije u datoteci do datuma proizvodnje
				nadjen = true;
			}else{
				while(getline(file,provjera)){
					if(provjera == "Stanje: Ima" || provjera == "Stanje: Nema"){
						break;
					}else{
					 brojac++;
				}
				}
			}
			brojac++;
		}
		if(nadjen == true){ // Nakon sto se pronade ID izlazi se iz petlje
			
		 break;
	}
	}
	file.close();
	
	int brojac_linija=0;
	fstream file2;
	file2.open("kolaci.txt", ios::in);
	/*
	U sljedecoj while petlji broji se ukupan broj linija u datoteci nakon cega se sadrzaj brise iz dtoteke
	*/
	while(getline(file2, string_niz[brojac_linija])){
		brojac_linija++; // Kroz brojanje linija koda, linije se spremaju u prethodno deklarsan string niz 
	}
	file2.clear(); // Brisanje sadrzaja  datoteke
	file2.close();
	fstream file3;
	file3.open("kolaci.txt", ios::out);
	// U sljedecoj for petlji se ponovo unosi sadrzaj u datoteku ali na specifican nacin
	for(int j=0; j<brojac_linija; j++){
		if(j != brojac-1){ // Sve dok je j razlicito od pozicije na kojoj se nalazi datum proizvodnje kolaca 
		
		 file3 << string_niz[j] << endl; // Linije datoteke se pisu u nju iz string niza
	}else{ // Medutim kada program dode do linije u kojoj se nalazi datum proizvodnje kolaca, tada se na to mjesto unosi novi datum
		
	 file3 << "Proizvedeno: " << s.str() << endl; // Mjesto je odredeno prvom while petljom
}
	}
	file3.close();	
	
/*
	Na isti nacin se mijenja datum isteka 
*/
	cout << "Unesite novi datum isteka: ";
	cin >> datum.dan_isteka >> datum.mjesec_isteka >> datum.godina_isteka;
	ostringstream ss;
	ss << setw(2) << setfill('0') << datum.dan_isteka << "." << setw(2) << setfill('0') << datum.mjesec_isteka << "." << datum.godina_isteka << ".";
	
	
	string	string_niz1[1000], provjera1;
	int brojac1=0;
	bool nadjen1 = false;
	fstream file1;
	file1.open("kolaci.txt", ios::in);
	while(!file1.eof()){
		file1 >> provjera1;
		if(provjera1 == "ID:" && nadjen1==false){
			file1 >> provjera1;
			if(provjera1 == id){
				brojac1+=3;
				nadjen1 = true;
			}else{
				while(getline(file1,provjera1)){
					if(provjera1 == "Stanje: Ima" || provjera1 == "Stanje: Nema"){
						break;
					}else{
					 brojac1++;
				}
				}
			}
			brojac1++;
		}
		if(nadjen1 == true){
			
		 break;
	}
	}
	file1.close();
	
	int brojac_linija1=0;
	fstream file21;
	file21.open("kolaci.txt", ios::in);
	while(getline(file21, string_niz1[brojac_linija1])){
		brojac_linija1++;
	}
	file21.clear();
	file21.close();
	fstream file31;
	file31.open("kolaci.txt", ios::out);
	for(int j=0; j<brojac_linija1; j++){
		if(j != brojac1-1){
		
		 file31 << string_niz1[j] << endl;
	}else{
		
	 file31 << "Istice: " << ss.str() << endl;
}
	}
	file31.close();	
	
}


/*
	Kao prethodno objasnjen postupak vrsi se i promjena stanja
*/
	void PromjenaStanja(){
				int br=0;
		
		for(;;){
			string provjera;
			cout << "ID: ";
			cin >> this->id;
			
			ifstream datotekakolaca("kolaci.txt");
			while(!datotekakolaca.eof()){
				datotekakolaca >> provjera;
				if(provjera == id){
					br=1;
				}
			}
			if(br==0){
				cout << "Kolac sa tim ID-om ne postoji!\n";
				cout << "Molimo unesite drugi iD!\n";
			}else if(br==1){
				datotekakolaca.close();
				break;
			}
			
		}
		int x;
		cout << "Unesite novo stanje kolaca:\n";
		cout << "\t1. Nema na stanju\n";
		cout << "\t2. Ima na stanju\n";
		do{
			cout << "Odabir: ";
			cin >> x;
			
		}while(x<1 || x>2);
		this->stanje = Stanje(x);
		
			string	string_niz[1000], provjera;
	int brojac=0;
	bool nadjen = false;
	fstream file;
	file.open("kolaci.txt", ios::in);
	while(!file.eof())
	{
		file >> provjera;
		if(provjera == "ID:" && nadjen==false){
			file >> provjera;
			if(provjera == id){
				brojac+=5;
				nadjen = true;
			}else{
				while(getline(file,provjera)){
					if(provjera == "Stanje: Ima" || provjera == "Stanje: Nema") 
					{
						break;
					}
					else{
						
					 brojac++;
				}
				}
			}
			brojac++;
		}
		if(nadjen == true) break;
		
	}
	file.close();
	
	int brojac_linija=0;
	fstream file2;
	file2.open("kolaci.txt", ios::in);
	while(getline(file2, string_niz[brojac_linija])){
		brojac_linija++;
	}
	file2.clear();
	file2.close();
	fstream file3;
	file3.open("kolaci.txt", ios::out);
	for(int j=0; j<brojac_linija; j++){
		if(j != brojac-1){
			
		 file3 << string_niz[j] << endl;
	}else {
	file3 << "Stanje: ";
		if(x==1){
			file3 << "Nema" << endl;
		}else if(x==2){
			file3 << "Ima" << endl;
			
		}
	}
	}
	file3.close();
		
	}
	
	
		
	};
/*
void pretragapremaNazivu() - je funkcija koja pretrazuje kolace prema nazivu ali se moze pretrazivati i ako su kolaci unijeti malim slovima ili velikim pocetim slovom
*/
void pretragapremaNazivu(){
	char trazeni[50];
	int e=0;
	cout << "Unesite kolac koji zelite da pretrazite: ";
	cin.getline(trazeni, 50);
	ifstream datoteka("kolaci.txt");
	if(datoteka.is_open()){
		string provjera,tekst,temp;
		
	
		while(!datoteka.eof()){
			datoteka >> provjera;
			if(provjera == "ID:"){
				datoteka >> provjera;
				temp.clear();
				temp += provjera;
			}
			
			if(provjera == "Naziv:"){
						tekst = "";
						if(trazeni[0]>='a' && trazeni[0]<='z'){
							trazeni[0]-=32;
						}
						do{
						datoteka >> provjera;
					if(provjera != "Proizvedeno:"){
						tekst += provjera + " ";
					}
				}while(provjera!="Proizvedeno:");
				int a=0;
				
			for(int  i=0; i<tekst.length()-1; i++){
				if(tekst[i]==trazeni[i]){
					a++;
				}
			}
			if(a == tekst.length()-1){
				cout << "Postoji kolac pod tim nazivom!\n";
				cout << "------------------------------------------\n";
				cout << "Podaci o kolacu:\n";
				cout << "ID: " << temp << endl;
				cout << "Naziv: " << tekst << endl;
		
				if(provjera == "Proizvedeno:"){
					datoteka >> provjera;
					cout << "Datum proizvodnje: " << provjera << endl;
				}
				datoteka >> provjera;
				if(provjera == "Istice:"){
					datoteka >> provjera;
					cout << "Datum isteka: " << provjera << endl;
				}
				datoteka >> provjera;
				if(provjera == "Cijena:"){
					datoteka >> provjera;
					cout << "Cijena: " << provjera << " KM" << endl;
				}
				datoteka >> provjera;
				if(provjera == "Stanje:"){
					datoteka >> provjera;
					cout << "Stanje: " << provjera << endl;
					e++;
					break;
				}
				
				
				
				
			}
		}
		
	}
		if(e==0){
			cout << "Ne postoji kolac pod tim nazivom u datoteci!\n";
		}
		
	}else{
		cout << "[GRESKA] Datoteka se ne moze otvoriti!\n";
		
	}

	datoteka.close();
}
/*
	Ovo je rekurzivna funkcija za izracunavanje cijene kolaca gdje svaki treci kupljeni kolac ima 5% popusta 
*/

double CijenaKolaca(double cijena, int kolicina){
	
	if(kolicina == 0){
		return 0;
	}else{
		if(kolicina%3==0){
			return cijena*0.95 + CijenaKolaca(cijena, kolicina-1);
		}else{
			return cijena + CijenaKolaca(cijena, kolicina-1);
		}
		
	}
}
/*
	void narudzbaKolaca() - funkcija koja vrsi upis narudzbe u sistem, ali se narudzba spema u posebnu datoteku u obliku racuna/priznanice
*/
void narudzbaKolaca(){
		
				string pretraga,provjera,tekst;
				double cijena;
				
		bool a=false;
		cout << "Unesite ID za narudzbu: ";
		char *pomoc = new char[10];
		cin.getline(pomoc, 10);
		pretraga = pomoc;
		ifstream datoteka1("kolaci.txt");
		if(datoteka1.is_open()){
		
		while(!datoteka1.eof()){
			datoteka1 >> provjera;
			if(provjera == "ID:"){
				datoteka1 >> provjera;
				if(provjera == pretraga){
					a=true;
				}
			}
			
			if(a==true){
				if(provjera == "Naziv:"){
						tekst = "";
						do{
						datoteka1 >> provjera;
					if(provjera != "Proizvedeno:"){
						tekst += provjera + " ";
					}
				}while(provjera!="Proizvedeno:");

					}
				if(provjera == "Proizvedeno:"){
					datoteka1 >> provjera;
				
				}
				if(provjera == "Istice:"){
					datoteka1 >> provjera;
					
				}
				
				if(provjera == "Cijena:"){
					datoteka1 >> cijena;
						
				}
				if(provjera == "Stanje:"){
					datoteka1 >> provjera;

					break;
				}
				
				
			}
		}

		
	if(a==false){
		cout << "Ne postoji kolac sa tim ID-om!\n";
	}
			
		}else{
			cout << "Postoji problem prilikom narudzbe kolaca!\n";
		}
		datoteka1.close();
		
		string ime, prezime;
		string pom;
		int kolicina;
		cout << "Unesite ime korisnika: ";
		cin >> ime;
		cout << "Unesite prezime korisnika: ";
		cin >> prezime;
		cout << "Koliko komada korisnik zeli: ";
		cin >> kolicina;
		
		double ukupna_cijena;
		ukupna_cijena = CijenaKolaca(cijena, kolicina);
		
		
		pom = ime+prezime+".txt";
		ofstream narudzbenica(pom.c_str());
		narudzbenica << "------------------------------------------------------------\n";
		narudzbenica << "\t\t\tAjna i Amina\n";
		narudzbenica << "------------------------------------------------------------\n";
		narudzbenica << "Ime i prezime: " << ime << " " << prezime << endl;
		narudzbenica << "Naziv kolaca: " << tekst << endl;
		narudzbenica << "Kolicina: " << kolicina << endl;
		narudzbenica << "Ukupna cijena kolaca: " << setprecision(2) << fixed << ukupna_cijena <<  " KM" << endl;
		narudzbenica << "\n\t\t\tPotpis: _________________________\n";
		narudzbenica << "------------------------------------------------------------\n";
		narudzbenica.close();
		cout << "Narudzba je uspjesno snimljena!\n";
		
}



bool Provjera(string username, string password){
	string provjera;
	string all = username + password;
	
	int a=0;
	ifstream datoteka("Djelatnici.txt");
	while(datoteka >> provjera){
		if(provjera == all){
			a++;
		}
		
	}
	
	if(a==1){
		return true;
	}else{
		return false;
	}
	
}


void unosDjelatnika(){
	string username, password;
	cout << "Unesi korisnicko ime novog djelatnika: ";
	cin >> username;
	cout << "Unesi sifru: ";
	cin >> password;
	string s = username + password;
	ofstream datoteka("Djelatnici.txt", ios::app);
	datoteka << s << endl;

}




void Meni_Djelatnik(){
	system("cls");
	cout << "----------------------------------------------\n"; 
	cout << "\t\tDJELATNICKI MENI:\n"; 
	cout << "----------------------------------------------\n";
	cout << "\t1. Unos kolaca\n"; 
	cout << "\t2. Pregled kolaca\n"; 
	cout << "\t3. Pretraga prema ID-u kolaca\n";
	cout << "\t4. Pretraga prema nazivu kolaca\n";
	cout << "\t5. Ispis narudzbe kolaca\n"; 
	cout << "\t6. Promjena datuma\n";
	cout << "\t7. Promjena stanja\n";
	cout << "\t8. Dodaj novog djelatnika\n";
	cout << "\t9. Odjava\n"; 
	cout << "----------------------------------------------\n"; 
	
}


void Meni_Izbor(){
	system("cls");
	cout << "----------------------------------------------\n"; 
	cout << "\t\tIZBOR:\n"; 
	cout << "----------------------------------------------\n";
	cout << "\t1. Korsnik\n";
	cout << "\t2. Djelatnik\n";
	cout << "\t3. Kraj\n";
	cout << "----------------------------------------------\n"; 
	
}

void Meni_Korisnik(){
	system("cls");
	cout << "----------------------------------------------\n"; 
	cout << "\t\tKORISNICKI MENI:\n"; 
	cout << "----------------------------------------------\n";
	cout << "\t1. Pregled kolaca\n"; 
	cout << "\t2. Pretraga prema ID-u kolaca\n";
	cout << "\t3. Pretraga prema nazivu kolaca\n";
	cout << "\t4. Ispis narudzbe kolaca\n"; 
	cout << "\t5. Zavrsi\n"; 
	cout << "----------------------------------------------\n"; 
	
}







int main (){
	setlocale(LC_ALL,"");
	Kolaci k;
	int izbor, izborK, izborD;
	
	cout << endl;
	cout << endl;
	cout << endl;
	cout << setw(40) << "::Ajna i Amina::" << endl;
	cout << setw(20);
	for(int i=0; i<30; i++){
		Sleep(50);
		cout << "*";
	}
	system("cls");
	
	

	do{
		do{
			Meni_Izbor();
			cout << "Izbor: ";
			cin >> izbor;	
			cin.ignore();
			if(izbor == 1){
					if(izbor == 1){
		do{
			do{
				Meni_Korisnik();
				cout << "Izbor: ";
				cin >> izborK;
				cin.ignore();
				if(izborK == 1){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPregled postojecih kolaca\n";
				cout << "------------------------------------------\n";
				k.pregledKolaca();
				cout << endl;
				system("pause");
				}else if(izborK == 2){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPretraga kolaca prema ID-u\n";
				cout << "------------------------------------------\n";
				k.pretragapremaID();
				cout << endl;
				system("pause");
				}else if(izborK == 3){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPretraga kolaca prema ID-u\n";
				cout << "------------------------------------------\n";
				k.pretragapremaID();
				cout << endl;
				system("pause");
				}else if(izborK == 4){
					system("cls");
				cout << "------------------------------------------\n";
				cout << "\tDodavanje narudzbe\n";
				cout << "------------------------------------------\n";
				k.pregledKolaca();
				cout << endl;
				narudzbaKolaca();
				cout << endl;
				system("pause");
				}
				
			}while(izborK!=5);
			
		}while(izborK<1 || izborK >5);
	}
			}else if(izbor == 2){
			string username;
			string password;
			system("cls");
			cout << "----------------------------------------------\n"; 
			cout << "\t\tPRIJAVA DJELATNIKA:\n"; 
			cout << "----------------------------------------------\n";
			cout << "Korisnicko ime: ";
			cin >> username;
			cout << "Sifra: ";
			cin >> password;
			cin.ignore();
			if(Provjera(username, password)==true){
				do{
					do{
				Meni_Djelatnik();
				cout << "Izbor: ";
				cin >> izborD;
				cin.ignore();
				if(izborD == 1){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tUnos novog kolaca\n";
				cout << "------------------------------------------\n";
				k.unosKolaca();
				cout << endl;
				system("pause");
				}else if(izborD == 2){
					system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPregled postojecih kolaca\n";
				cout << "------------------------------------------\n";
				k.pregledKolaca();
				cout << endl;
				system("pause");
				}else if(izborD == 3){
					system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPretraga kolaca prema ID-u\n";
				cout << "------------------------------------------\n";
				k.pretragapremaID();
				cout << endl;
				system("pause");
				}else if(izborD == 4){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPretraga kolaca prema nazivu\n";
				cout << "------------------------------------------\n";
				pretragapremaNazivu();
				cout << endl;
				system("pause");
			}else if(izborD == 5){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tDodavanje narudzbe u sistem\n";
				cout << "------------------------------------------\n";
				k.pregledKolaca();
				cout << endl;
				narudzbaKolaca();
				cout << endl;
				system("pause");
			}else if(izborD == 6){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPromjena datuma\n";
				cout << "------------------------------------------\n";
				k.Promjeni();
				cout << endl;
				system("pause");
			}else if(izborD == 7){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPromjena stanja\n";
				cout << "------------------------------------------\n";
				k.PromjenaStanja();
				cout << endl;
				system("pause");
			}else if(izborD == 8){
					system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPromjena stanja\n";
				cout << "------------------------------------------\n";
				unosDjelatnika();
				cout << endl;
				system("pause");
			}
						
					}while(izborD!=9);
					
				}while(izborD<1 || izborD>9);
				
			}else{
				cout << "Podaci nisu tacni, pokusajte ponovo!" << endl;
				system("pause");
			}
}else if(izbor == 3){
				cout << "Hvala i dovidjenja!";
			}
		}while(izbor!=3);
	}while(izbor<1 || izbor>3);
	

	
	
	
/*	
	do{
		do{
			Meni();
			cout << "Izbor: ";
			cin >> izbor;
			cin.ignore();
			if(izbor == 1){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tUnos novog kolaca\n";
				cout << "------------------------------------------\n";
				k.unosKolaca();
				cout << endl;
				system("pause");
			}else if(izbor == 2){
					system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPregled postojecih kolaca\n";
				cout << "------------------------------------------\n";
				k.pregledKolaca();
				cout << endl;
				system("pause");
			}else if(izbor == 3){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPretraga kolaca prema ID-u\n";
				cout << "------------------------------------------\n";
				k.pretragapremaID();
				cout << endl;
				system("pause");
			}else if(izbor == 4){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPretraga kolaca prema nazivu\n";
				cout << "------------------------------------------\n";
				pretragapremaNazivu();
				cout << endl;
				system("pause");
			}else if(izbor == 5){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tDodavanje narudzbe u sistem\n";
				cout << "------------------------------------------\n";
				k.pregledKolaca();
				cout << endl;
				narudzbaKolaca();
				cout << endl;
				system("pause");
			}else if(izbor == 6){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPromjena datuma\n";
				cout << "------------------------------------------\n";
				k.Promjeni();
				cout << endl;
				system("pause");
			}else if(izbor == 7){
				system("cls");
				cout << "------------------------------------------\n";
				cout << "\tPromjena stanja\n";
				cout << "------------------------------------------\n";
				k.PromjenaStanja();
				cout << endl;
				system("pause");
			}else if(izbor == 8){
				cout << "Hvala i dovidjenja!\n";
			}
			
			
		}while(izbor!=8);
		
	}while(izbor<1 || izbor>8);
	*/

return 0;
}


