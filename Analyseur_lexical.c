#include"Analyseur_lexical.h"
#include <stdlib.h>
#include <string.h>



void Ouvrir_Fichier(char* f){
    Fichier= fopen(f, "r");
}

void Lire_Caractere(){
         Car_Cour=fgetc(Fichier);
}

void Lire_Mots(){
    int i =0 ;
	while(Car_Cour != ' ' && Car_Cour != '\n'  && Car_Cour != '\t'  && Car_Cour != ';' && Car_Cour != '.' && Car_Cour!= '=' && Car_Cour!= '+'
            && Car_Cour!= '-' && Car_Cour!='*'&& Car_Cour!= '/'&& Car_Cour!= ',' && Car_Cour!= ':' && Car_Cour !='<' && Car_Cour!='>'
            && Car_Cour!= '(' && Car_Cour!=')' && Car_Cour!='#' && Car_Cour!= '{' && Car_Cour!= '}' && Car_Cour!= '[' && Car_Cour!= ']' &&
            Car_Cour != '"' && Car_Cour != ':'&& Car_Cour != '^' && Car_Cour != '%' && Car_Cour!=EOF)
        {
            SYM_COUR.NOM[i] = Car_Cour;
            Lire_Caractere();
            i++;
	    }
	SYM_COUR.NOM[i]='\0';
	for(int j=0;j<14;j++){
        if(!strcmp(SYM_COUR.NOM , MOTS_CLES[j])){
            SYM_COUR.CODE=j+1;
            return ;
        }
	}
    SYM_COUR.CODE=ID_TOKEN;

}

void Lire_Nombre(){
    int i =0;
   while(Car_Cour != ' ' && Car_Cour != '\n'  && Car_Cour != '\t'&& Car_Cour != ';' &&Car_Cour!= '.' &&Car_Cour!= '=' && Car_Cour!= '+'
        && Car_Cour!= '-'&& Car_Cour!='*'&& Car_Cour!= '/'&&Car_Cour!= ',' &&Car_Cour!= ':' &&Car_Cour!='<' &&Car_Cour!='>'
        &&Car_Cour!= '(' &&Car_Cour!=')' && Car_Cour!='#' && Car_Cour!= '{' && Car_Cour!= '}' && Car_Cour!= '[' && Car_Cour!= ']' &&
        Car_Cour != '"' && Car_Cour != ':' && Car_Cour != '^' && Car_Cour != '%' && Car_Cour!=EOF){
            SYM_COUR.NOM[i] = Car_Cour;
            Lire_Caractere();
            i++;
	}
	int j =0;

	while(SYM_COUR.NOM[j] != '\0'){
        if(SYM_COUR.NOM[j]>= '0' &&  SYM_COUR.NOM[j]<= '9'){
            j++;
        }

        else{
            SYM_COUR.CODE=ERREUR_TOKEN;
            Erreur(ERR_CAR_INC);
            return;
        }
    SYM_COUR.CODE=NUM_TOKEN;
	}
}


void Lire_Special(){
    int i =0;
	SYM_COUR.NOM[i]=Car_Cour;
	if(Car_Cour=='+') SYM_COUR.CODE= PLUS_TOKEN;
	else if(Car_Cour=='-') SYM_COUR.CODE= MOINS_TOKEN;
	else if(Car_Cour=='*') SYM_COUR.CODE= MULT_TOKEN;
	else if(Car_Cour=='/') SYM_COUR.CODE= DIV_TOKEN;
	else if(Car_Cour=='.') SYM_COUR.CODE= PT_TOKEN;
	else if(Car_Cour==';') SYM_COUR.CODE= PV_TOKEN;
	else if(Car_Cour==',') SYM_COUR.CODE= VIR_TOKEN;
    else if(Car_Cour=='=') {
            Lire_Caractere();
            if(Car_Cour=='='){
                i++; SYM_COUR.NOM[i]=Car_Cour;
                SYM_COUR.CODE= EGAL_TOKEN;
            }
            else SYM_COUR.CODE= AFF_TOKEN;
    }
	else if(Car_Cour=='<') {
            Lire_Caractere();
            if(Car_Cour=='='){
                i++;
                SYM_COUR.NOM[i]=Car_Cour;
                SYM_COUR.CODE=INFEG_TOKEN;
            }
            else if(Car_Cour=='>'){
                i++;
                SYM_COUR.NOM[i]=Car_Cour;
                SYM_COUR.CODE=DIFF_TOKEN;
            }
            else if(Car_Cour=='-'){
                i++;
                SYM_COUR.NOM[i]=Car_Cour;
                SYM_COUR.CODE=AFF_TOKEN;
            }
            else SYM_COUR.CODE=INF_TOKEN;
	}
	else if(Car_Cour=='>') {
            Lire_Caractere();
            if(Car_Cour=='='){
                i++;
                SYM_COUR.NOM[i]=Car_Cour;
                SYM_COUR.CODE=SUPEG_TOKEN;
            }
            else SYM_COUR.CODE=SUP_TOKEN;
	}
	else if(Car_Cour=='(') SYM_COUR.CODE = PO_TOKEN;
	else if(Car_Cour==')') SYM_COUR.CODE = PF_TOKEN;
    else if(Car_Cour=='{') SYM_COUR.CODE = ACCO_TOKEN;
	else if(Car_Cour=='}') SYM_COUR.CODE = ACCF_TOKEN;
    else if(Car_Cour=='[') SYM_COUR.CODE = CRO_TOKEN;
	else if(Car_Cour==']') SYM_COUR.CODE = CRF_TOKEN;
    else if(Car_Cour==':') SYM_COUR.CODE = DPT_TOKEN;
    //else if(Car_Cour=='"') SYM_COUR.CODE = APS_TOKEN;
    else if(Car_Cour=='^') SYM_COUR.CODE = PUISS_TOKEN;
    else if(Car_Cour=='%') {
            Lire_Caractere();
            if(Car_Cour=='%'){
                i++;
                SYM_COUR.NOM[i]=Car_Cour;
                SYM_COUR.CODE=REST_TOKEN;
            }
            else if(Car_Cour=='/'){
                i++;
                SYM_COUR.NOM[i]=Car_Cour;
                Lire_Caractere();

                if(Car_Cour=='%'){
                i++;
                SYM_COUR.NOM[i]=Car_Cour;
                SYM_COUR.CODE=ENTIER_TOKEN;
                }
            }
            else  Erreur(ERR_CAR_INC);
	}
    else if(Car_Cour==EOF) SYM_COUR.CODE = EOF_TOKEN ;
    else if(Car_Cour=='\n') {SYM_COUR.NOM[0]=' ' ; SYM_COUR.CODE = RETOUR_TOKEN ; }
	Lire_Caractere();
}

void Lire_Commentaire(){
    Lire_Caractere();
    do{
        SYM_COUR.NOM[0] =Car_Cour;
        Lire_Caractere();
    }while(SYM_COUR.NOM[0] !='\n');

    /*if(SYM_COUR.NOM[0]=='\n')
        SYM_COUR.CODE = COM_TOKEN;
    else {
        SYM_COUR.CODE=ERREUR_TOKEN;
        Erreur(ERR_COM);
    }  */
   // printf("Commentaire \n");
}

void Lire_String(){
    Lire_Caractere();
    do{
        SYM_COUR.NOM[0] =Car_Cour;
        Lire_Caractere();
    }while(SYM_COUR.NOM[0] !='"');

    if(SYM_COUR.NOM[0]=='"')
        SYM_COUR.CODE = STRING_TOKEN;
    else {
        SYM_COUR.CODE=ERREUR_TOKEN;
        Erreur(ERR_STRING);
    }
  // printf("Chaine de caractere \n");
}

void Erreur(Erreurs ERR){
	int  ind_err=ERR;
	printf( "Erreur  numero  %d \t : %s \n", ind_err, MES_ERR[ind_err] .mes);
	//getch();
	exit(1);
}

void Sym_Suiv(){
    for(int j = 0; j < 20; j++) {
            SYM_COUR.NOM[j] = '\0';
    }

	while((Car_Cour == ' ' /*|| Car_Cour == '\n' */ || Car_Cour == '\t' )  ){
        Lire_Caractere();
	}

    if ((Car_Cour>= 'a' &&  Car_Cour<= 'z' ) || (Car_Cour>= 'A' &&  Car_Cour<= 'Z' )){
        Lire_Mots();
    }

    else if (Car_Cour>= '0' &&  Car_Cour<= '9' ){
        Lire_Nombre();
    }

    else if(Car_Cour=='#') {
        Lire_Commentaire();
	}

   else if (Car_Cour == '\n' || Car_Cour==EOF || Car_Cour >= '^' || Car_Cour >= '%' || Car_Cour>= ';' ||Car_Cour>= '.' || Car_Cour>= '='|| Car_Cour>= '+' || Car_Cour>= '-'|| Car_Cour>= '*'|| Car_Cour>= '/'||Car_Cour>= ',' ||Car_Cour>= '<' ||Car_Cour>= '>' ||Car_Cour>= '(' || Car_Cour>= ')' || Car_Cour>= '{' || Car_Cour>= '}' || Car_Cour>= '[' || Car_Cour>= ']' || Car_Cour>= ':' ){
        Lire_Special();
    }

    else if(Car_Cour=='"') {
        Lire_String();
        //SYM_COUR.NOM[0] ='"';
	}
    else{
       SYM_COUR.CODE=ERREUR_TOKEN;
       Erreur(ERR_CAR_INC);
    }
}

void AfficherToken(TSym_Cour Sc){
    printf("  %s    : %s \n",SYM_COUR.NOM , Code_Lex_Chaine[SYM_COUR.CODE]);
}


