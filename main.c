
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
	    printf("BRAVO: le programme est correcte!!!");
    else
        printf("PAS BRAVO: fin de programme erronée!!!!");

	getch();
	return 1;
}
