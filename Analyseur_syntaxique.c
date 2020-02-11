#include "analyseur_syntaxique.h"
#include "Analyseur_lexical.h"

void Test_Symbole ( CODE_LEX cl, Erreurs COD_ERR){
    if (SYM_COUR.CODE == cl){
        Sym_Suiv();
    }
    else if(SYM_COUR.CODE==-1) Sym_Suiv();
    else
        Erreur(COD_ERR);
}

void INSTS(){
     if(SYM_COUR.CODE!=-1){
            INST();
            if(SYM_COUR.CODE == PV_TOKEN){
                while (Test_Symbole(PV_TOKEN, ERR_CAR_INC)){
                    INSTS();
                }
            }
    }
}

void INST(){
    switch (SYM_COUR.CODE) {
        case ID_TOKEN : Sym_Suiv();
                        INST_PRIME();
                        break;
        case FUNCTION_TOKEN : FUNCTION();
                                break;
        case IF_TOKEN : SI();
                        break;
        case FOR_TOKEN : POUR();
                         break;
        case WHILE_TOKEN : TANTQUE();
                            break;
        case REPEAT_TOKEN : REPEAT_TOKEN();
                            break;
        default : printf("Erreur Anayse syntaxique");
    }
}

void INST_PRIME(){
    switch(SYM_COUR.CODE){
        case EGAL_TOKEN : AFFECT();
                            break;
        case AFF_TOKEN : AFFECT();
                          break;
        case PT_TOKEN : COMMANDE();
                            break ;
        case PO_TOKEN : COMMANDE();
                        break ;
        default : ;
    }
}

void AFFECT(){
    AFFECT_PRIME();
    AFFECT_PRIME_SECOND();
}

void AFFECT_PRIME(){
    switch(SYM_COUR.CODE){
        case EGAL_TOKEN : Test_Symbole(EGAL_TOKEN, ERR_CAR_INC);
                            break;
        case AFF_TOKEN : Test_Symbole(AFF_TOKEN, ERR_CAR_INC);
                            break;
        default : return ;
    }
}

void AFFECT_PRIME_SECOND(){
    switch(SYM_COUR.CODE){
        case ID_TOKEN : Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        AFFECT_PRIME_TROIS();
                        break ;
        case FUNCTION_TOKEN : FUNCTION();
                                break ;
        default : EXPR();
    }
}

void AFFECT_PRIME_TROIS(){
    switch(SYM_COUR.CODE){
        case PT_TOKEN : COMMANDE();
                        break;
        case PO_TOKEN : COMMANDE();
                        break;
        default : OP(); TERM();
    }
}

void FUNCTION(){
    Test_Symbole(FUNCTION_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    ARGUMENT();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    RETURN();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
}









