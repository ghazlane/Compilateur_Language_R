
#include "Analyseur_lexical.h"
#include "Analyseur_syntaxique.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
	Ouvrir_Fichier("programR.r");
	Premier_sym();
INSTS();
    if (SYM_COUR.CODE==EOF_TOKEN)
	    printf("\n\n**************BRAVO: le programme est correcte!!!*************\n\n\n\n\n");
    else
        printf("PAS BRAVO: fin de programme erronée!!!!");

	getch();
	return 1;
}
/*
int main(){
	Ouvrir_Fichier("programR.r");
	Lire_Caractere();
	while (Car_Cour!=EOF) {
		Sym_Suiv();
		AfficherToken(SYM_COUR);
	}


	return 1;
}
*/
