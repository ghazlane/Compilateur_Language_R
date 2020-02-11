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
        case REPEAT_TOKEN : REPETER();
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

void ARGUMENT(){
    if(SYM_COUR.CODE == ID_TOKEN){
        Test_Symbole(ID_TOKEN, ERR_CAR_INC);
        ARGUMENT_PRIME();
    }
}

void ARGUMENT_PRIME(){
    switch(SYM_COUR.CODE){
        case VIR_TOKEN : Test_Symbole(VIR_TOKEN, ERR_CAR_INC);
                         ARGUMENT();
                            break;
        case EGAL_TOKEN : Test_Symbole(EGAL_TOKEN, ERR_CAR_INC);
                            EXPR();
                            if(SYM_COUR.CODE == VIR_TOKEN){
                                while(SYM_COUR.CODE == VIR_TOKEN){
                                    Test_Symbole(VIR_TOKEN,ERR_CAR_INC );
                                    ARGUMENT();
                                }
                            }
                            break;
        default : ;
    }
}

void COMMANDE(){
    switch(SYM_COUR.CODE){
        case PT_TOKEN : Test_Symbole(PT_TOKEN, ERR_CAR_INC);
                        Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        Test_Symbole(PO_TOKEN, ERR_CAR_INC);
                        PARAMETRE();
                        Test_Symbole(PF_TOKEN, ERR_CAR_INC);
                        break;
        default :  Test_Symbole(PO_TOKEN, ERR_CAR_INC);
                        PARAMETRE();
                        Test_Symbole(PF_TOKEN, ERR_CAR_INC);

    }
}

void PARAMETRE(){
    if(SYM_COUR.CODE==ID_TOKEN){
        Test_Symbole(ID_TOKEN, ERR_CAR_INC);
        PARAMETRE_PRIME();
    }
}

void PARAMETRE_PRIME(){
    switch(SYM_COUR.CODE){
        case VIR_TOKEN : while(SYM_COUR.CODE == VIR_TOKEN ){
                                Test_Symbole(VIR_TOKEN, ERR_CAR_INC);
                                PARAMETRE();
                        }
                        break ;
        case PT_TOKEN : COMMANDE() ; break;
        case PO_TOKEN : COMMANDE() ; break;
        default : ;
    }
}


void SI(){
    Test_Symbole(IF_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    COND();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
}

void POUR(){
    Test_Symbole(FOR_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    Test_Symbole(ID_TOKEN, ERR_CAR_INC);
    Test_Symbole(IN_TOKEN, ERR_CAR_INC);
    SEQ();
    Test_Symbole(PF_TOKEN,  ERR_CAR_INC);
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
}

void TANTQUE(){
    Test_Symbole(WHILE_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    COND();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
}

void REPETER(){
    Test_Symbole(REPEAT_TOKEN,ERR_CAR_INC);
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    Test_Symbole(PV_TOKEN, ERR_CAR_INC);
    Test_Symbole(IF_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    COND();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    Test_Symbole(BREAK_TOKEN,ERR_CAR_INC );
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
}

void COND(){
    EXPR() ;
    VERF();
    EXPR();
}

void EXPR(){
    TERM();
    OP();
    TERM();
}

void TERM(){
    switch(SYM_COUR.CODE){
        case ID_TOKEN : Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        break;
        case NUM_TOKEN : Test_Symbole(NUM_TOKEN, ERR_CAR_INC);
                            break;
        default : Test_Symbole(PO_TOKEN, ERR_CAR_INC);
                  EXPR();
                  Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    }
}

void OP(){
    switch(SYM_COUR.CODE){
        case PLUS_TOKEN : Test_Symbole(PLUS_TOKEN, ERR_CAR_INC);
            break;
        case MOINS_TOKEN :Test_Symbole(MOINS_TOKEN, ERR_CAR_INC);
            break;
        case MULT_TOKEN :Test_Symbole(MULT_TOKEN, ERR_CAR_INC);
            break;
        case DIV_TOKEN :Test_Symbole(DIV_TOKEN, ERR_CAR_INC);
            break;
    }
}

void VERF(){
switch(SYM_COUR.CODE){
        case DIFF_TOKEN : Test_Symbole(DIFF_TOKEN, ERR_CAR_INC);
            break;
        case EGAL_TOKEN :Test_Symbole(EGAL_TOKEN, ERR_CAR_INC);
            break;
        case INF_TOKEN :Test_Symbole(INF_TOKEN, ERR_CAR_INC);
            break;
        case INFEG_TOKEN :Test_Symbole(INFEG_TOKEN, ERR_CAR_INC);
            break;
        case SUP_TOKEN :Test_Symbole(SUP_TOKEN, ERR_CAR_INC);
            break;
        case SUPEG_TOKEN :Test_Symbole(SUPEG_TOKEN, ERR_CAR_INC);
            break;
    }
}

void RETURN(){
    if(SYM_COUR.CODE == RETURN_TOKEN){
        Test_Symbole(RETURN_TOKEN, ERR_CAR_INC);
        Test_Symbole(PO_TOKEN, ERR_CAR_INC);
        INST();
        Test_Symbole(PF_TOKEN, ERR_CAR_INC)
    }
}

void STOP(){
    switch(SYM_COUR.CODE){
        case BREAK_TOKEN : Test_Symbole(BREAK_TOKEN, ERR_CAR_INC); break ;
        case NEXT_TOKEN : Test_Symbole(NEXT_TOKEN, ERR_CAR_INC); break ;
        default : ;
    }
}

void SEQ(){
    switch(SYM_COUR.CODE){
        case ID_TOKEN : Test_Symbole(ID_TOKEN, ERR_CAR_INC); break ;
        case NUM_TOKEN : Test_Symbole(NUM_TOKEN, ERR_CAR_INC);
                        Test_Symbole(DPT_TOKEN? ERR_CAR_INC);
                        Test_Symbole(NUM_TOKEN, ERR_CAR_INC);
    }
}







