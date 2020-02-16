
#if !defined(__LEXICAL__H__)

    #define __LEXICAL__H__

    #include <stdio.h>

// DECLARATION DES TOKENS
//--------------------------------------------------------------
typedef enum {
	ID_TOKEN, IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN, REPEAT_TOKEN, BREAK_TOKEN, NEXT_TOKEN, FOR_TOKEN, IN_TOKEN, FUNCTION_TOKEN, RETURN_TOKEN,
    TRUE_TOKEN, FALSE_TOKEN, NULL_TOKEN, PV_TOKEN, PT_TOKEN, PLUS_TOKEN ,MOINS_TOKEN, MULT_TOKEN, DIV_TOKEN, VIR_TOKEN, AFF_TOKEN, INF_TOKEN,
    INFEG_TOKEN, SUP_TOKEN, SUPEG_TOKEN, EGAL_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN, ACCO_TOKEN, ACCF_TOKEN, CRO_TOKEN, CRF_TOKEN, APS_TOKEN,
    NUM_TOKEN, ERREUR_TOKEN, COM_TOKEN, DPT_TOKEN,  PUISS_TOKEN, REST_TOKEN,ENTIER_TOKEN, EOF_TOKEN, RETOUR_TOKEN, STRING_TOKEN
} CODE_LEX ;

typedef  struct { CODE_LEX CODE; char NOM[20]; } TSym_Cour;
TSym_Cour	SYM_COUR;

static char MOTS_CLES[14][10]={ "if", "else", "while", "repeat", "break", "next", "for", "in", "function", "return", "true", "false","null"};


static char Code_Lex_Chaine[50][50] ={
	"ID_TOKEN", "IF_TOKEN", "ELSE_TOKEN", "WHILE_TOKEN", "REPEAT_TOKEN", "BREAK_TOKEN", "NEXT_TOKEN", "FOR_TOKEN", "IN_TOKEN", "FUNCTION_TOKEN",
    "RETURN_TOKEN", "TRUE_TOKEN", "FALSE_TOKEN", "NULL_TOKEN", "PV_TOKEN", "PT_TOKEN","PLUS_TOKEN", "MOINS_TOKEN", "MULT_TOKEN", "DIV_TOKEN",
    "VIR_TOKEN", "AFF_TOKEN", "INF_TOKEN", "INFEG_TOKEN", "SUP_TOKEN", "SUPEG_TOKEN", "EGAL_TOKEN", "DIFF_TOKEN", "PO_TOKEN", "PF_TOKEN",
    "ACCO_TOKEN", "ACCF_TOKEN", "CRO_TOKEN", "CRF_TOKEN", "APS_TOKEN", "NUM_TOKEN", "ERREUR_TOKEN", "COM_TOKEN", "DPT_TOKEN","PUISS_TOKEN",
    "REST_TOKEN","ENTIER_TOKEN", "EOF_TOKEN", "RETOUR_TOKEN", "STRING_TOKEN"
};

static FILE* Fichier = NULL;
char Car_Cour; //caractere courant


//------------------------------------------------------------------------------
// DECLARATION DES CLASSES DES ERREURS
//------------------------------------------------------------------------------
typedef enum {
	ERR_CAR_INC, ERR_FICH_VID, ERR_COM, ERR_STRING, NOTCMD, NUMARG, NOTDECLARED,ISFUNCTION,NBPARA
}Erreurs;

//------------------------------------------------------------------------------
// DECLARATION DU TABLEAU DES ERREURS
//------------------------------------------------------------------------------
typedef  struct  {   Erreurs  CODE_ERR; char mes[40] ;  }Mes_Erreurs;

static Mes_Erreurs	MES_ERR[100]={{ERR_CAR_INC,"caractere inconnu"}, {ERR_FICH_VID,"fichier vide"},{ERR_COM,"erreur commentaire"},{ERR_STRING, "Chaine de caractere incorrecte"},{NOTCMD, "Coomande introuvable"},{NUMARG, "nombre des arguments utilisés dans cette commande est incorrecte"}
,{NOTDECLARED,"identifiant non declaré"},{ISFUNCTION,"l'identifiant est un id d'une fonction deja definie"},{NBPARA,"nombre de parametre est insuffisant"}};


//fonctions
void Ouvrir_Fichier(char* f);
void Lire_Caractere();
void Lire_Mots();
void Lire_Nombre();
void Lire_Special();
void Lire_Commentaire();
void Lire_String();
void Erreur(Erreurs ERR);
void Sym_Suiv();
void AfficherToken(TSym_Cour Sc);


#endif
