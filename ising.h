#include <cmath>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int N, NN, N2;//gittergroesse N wird festgesetzt in der "complete_ising_init(int argc, char* argv[])"
double rezNN;
int Size = 1, SizeN;// Skalierfaktor, wird auch in "complete_ising_init" initiiert;




double speed;



double Ecurrent = 0;// falls man sich fuer die energie interessiert
double Emid = 0;
double Ef();// sehr aufwaendige funktion zum berechnen der energie




double T, dT, H, dH, J; //T Temperatur, H Magnetfeld, J Kopplung;
// anfangswerte werden in der init_ising() festgelegt und koennen durch tastaturbefehle geaendert werden (ausser J)
//dT und dH sind die Schritte in denen man die T und H durch die Tastaturbefehle veraendern kann

long double eT; // das wird spaeter exp (-2/kB*T), damit man den Wert nicht immer neu berechnen muss
const double kB = 0.00008673324; //Boltzmann-Konstante;
double kBT; // kB * T, damit man nicht jedes mal multiplizieren muss;

char *TStr, *TstepStr, *HStr, *HstepStr, *mStr, *mmidStr, *speedStr, *EStr, *EmidStr;// Platzhalter fuer die textausgabe

FILE *mOut; // Ausgabedatei

int counter = 0;// zaehler der anzeige-schritte
double mmid = 0;// mittlere magnetisierung gemittelt über die anzahl der anzeige-schritte;

//die texte fuer die werte, die selten (eigentlich nur nach einer manuellen aenderung) veraendert werden
// werden damit erneuert
int update_strings(){
	free(TStr); free(HStr); free(speedStr);
	free(TstepStr); free (HstepStr);
	TStr = (char*) malloc (sizeof(char)*100);
	TstepStr = (char*) malloc (sizeof(char)*100);
	HStr = (char*) malloc (sizeof(char)*100);
	HstepStr = (char*) malloc (sizeof(char)*100);
	speedStr = (char*) malloc (sizeof(char)*100);

	sprintf (TStr, " T=%12.5lf", T);
    sprintf (TstepStr, "dT=%12.5lf", dT);
	sprintf (HStr, " H=%13.9lf", H);
    sprintf (HstepStr, "dH=%13.9lf", dH);
	sprintf (speedStr, "speed=%6.3lf", speed*rezNN);
	return 1;
}

//der magnetisierungswert muss bei jedem anzeige-schritt erneuert werden
int update_mStr(){
	free(mStr);	mStr = (char*) malloc(sizeof(char)*100); 	sprintf (mStr, "    m=%9.6lf", m*rezNN);
	free(mmidStr);	mmidStr = (char*) malloc(sizeof(char)*100);	sprintf (mmidStr, "m_mid=%9.6lf", mmid);
	free(EStr);	EStr = (char*) malloc(sizeof(char)*100);	sprintf (EStr, "E    =%9.6lf", Ecurrent*rezNN);
	free(EmidStr);	EmidStr = (char*) malloc(sizeof(char)*100);	sprintf (EmidStr, "E_mid=%9.6lf", Emid*rezNN);


}

void updateT();// Alles, was von Temperatur abhaengt, wird neu berechnet; wird nach einer manuellen Temperaturaenderung aufgerufen



int flip(int i){//selbsterklaerend
	s[i] = -s[i];
	m += 2*s[i];
}


double Ef(){
	int mf;//mf = mean field, aber in diesem fall nur sie summe der nachbarspins
	double E = 0;
	for (int x = 0; x< N; x++) for (int y = 0; y< N ; y++){
	 	mf = s[(x+1)%N + N*y] + s[(x+N-1)%N + N*y] + s[x+((y+1)%N)*N] + s[x+((y+N-1)%N)*N];
		E += -J/2 * s[x+N*y] * mf - H*s[x+N*y]; //J/2 wegen der doppelten zaehlung 
	}
	return E;
}

int x, y, Ny, mf;
int iterate(){//iterationsschritt am gitter
	int i = rand()%NN;//zufaellig ausgewaehlter spin
	if ((i+N)%NN > N2 && (i+1)%N > 1){// wenn der spin i im inneren ist, brauche ich kein modulo fuer die nachbarindices
		mf = s[i-1] + s[i+1] + s[i-N] + s[i+N];
	} else {//spin i ist irgendwo am rand. bestime die indices der nachbarspins mit modulo 
		x = i%N;
		Ny = ((int)i/N)*N;
		mf = s[(x+1)%N + Ny] + s[(x+N-1)%N + Ny] + s[x+(Ny+N)%NN] + s[x+ (Ny+NN-N)%NN];
	}
	// E1 = -J*mf*s[i] - H*s[i];
	// E2 = + J*mf*s[i] + H*s[i]; weil s[i] nun -s[i] ist
	double dE = (J*mf + H)*s[i]; // die Energiedifferenz. die 2 ist in eT versteckt

	if ( dE <= 0 || pow(eT, dE)*RAND_MAX > rand()) { 
		flip(i); 
		Ecurrent += 2*dE; 
	}
	return i; 
}

void resetCounter(){
	counter = 0;
	mmid = 0;
	Ecurrent = Ef();
	Emid = 0;
	fclose(mOut);
	mOut = fopen ("m.out", "w");//starte neue datei
}


void updateT (){
	kBT = T*kB;	
	eT = exp ((long double) -2.0/(kBT));
	resetCounter();
}

bool showmeanvalues = 0;// schalter fuer die zwei anzeigemodi

void resetMeanValues(){	
	for (int i = 0; i<NN; i++){ sm[i]=0;}
	resetCounter();
}





//Texte zeichnen
void drawtext(cairo_t *cr){
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 13);

	cairo_move_to(cr, 0, SizeN+15);		cairo_show_text(cr, TStr);
	cairo_move_to(cr, 0, SizeN+30);		cairo_show_text(cr, TstepStr);
	cairo_move_to(cr, 150, SizeN+15);	cairo_show_text(cr, HStr);
	cairo_move_to(cr, 150, SizeN+30); 	cairo_show_text(cr, HstepStr);
	update_mStr();
	cairo_move_to(cr, 0, SizeN+45);		cairo_show_text(cr, mStr);
	cairo_move_to(cr, 0, SizeN+60);		cairo_show_text(cr, mmidStr);
	cairo_move_to(cr,150 , SizeN+45);	cairo_show_text(cr, EStr);
	cairo_move_to(cr,150, SizeN+60);	cairo_show_text(cr, EmidStr);

	cairo_move_to(cr, 0, SizeN+90);		cairo_show_text(cr, speedStr);

	/*char* test = (char*) malloc (sizeof(char)*100); 
	cairo_move_to(cr, 150, SizeN+80);
	cairo_show_text(cr, test);
	free(test);*/
}

// Mittelwerte der einzelnen spin-sites zeichnen
void fillmeanvalues( cairo_t *cr){
	int i = 0;
	cairo_set_source_rgb (cr, .9, .9, .9);
        cairo_paint(cr);
	double rezcounter = 0.5/(double) counter, color;
	for (int k = 0; k<SizeN; k+=Size) for (int j = 0; j<SizeN; j+=Size){
		//color = 1-(smalt[i]/(double)acciepted_configurations+0.5);//fuer den fall, dass man die smalt darstellen will
		color = 1-(sm[i]*rezcounter+0.5);
		cairo_set_source_rgb(cr, color, color, color);
		cairo_rectangle(cr, k, j, Size,Size);
		cairo_fill(cr);
		sm[i]+=s[i];
		i++;
	}
}

// aktuelle spin zeichnen
void fillfield( cairo_t *cr){
	int i = 0;
        cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
        cairo_paint(cr);
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
 
	for (int k = 0; k<SizeN; k+=Size) for (int j = 0; j<SizeN; j+=Size){
		if (s[i]==1){
			cairo_rectangle(cr, k, j, Size,Size);
		}
		sm[i]+=s[i];//nutze die iteration ueber alle spins im sm-Array zu erneuern
		i++;
	}
	cairo_fill(cr);
}


//die methode, die jedesmal aufgerufen wird, wenn die zeichne-umgebung ein neues frame zeichnen will
void do_ising(cairo_t *cr){
        for (int i = 0; i < speed; i++){
                iterate();
        }
        counter++;
        mmid = (mmid*(counter-1) +  m*rezNN)/(double)counter;
	Emid = (Emid*(counter-1) + Ecurrent	)/(double)counter;
        fprintf (mOut, "%f\n", mmid);
	if (showmeanvalues){
                fillmeanvalues(cr);
        } else {
                fillfield(cr);
        }
        drawtext(cr);
}




