
#include "Analyseur_lexical.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	Ouvrir_Fichier("programR.r");
	Lire_Caractere();
	while (Car_Cour!=EOF) {
		Sym_Suiv();
		AfficherToken(SYM_COUR);
	}

	return 1;
}
