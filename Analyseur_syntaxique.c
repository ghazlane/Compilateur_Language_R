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
    printf("first insts\n");
    if(SYM_COUR.CODE!=-1){
            INST();
            /*while (SYM_COUR.CODE == PV_TOKEN ){
                    if(SYM_COUR.CODE == PV_TOKEN){
                    Test_Symbole(PV_TOKEN, ERR_CAR_INC);
                    INSTS();
                }
            }*/
        while (!EOF){
                    if(SYM_COUR.CODE == PV_TOKEN)Test_Symbole(PV_TOKEN, ERR_CAR_INC);
                    INSTS();
                    if(SYM_COUR.CODE == RETURN_TOKEN)
                        INSTS();
                }
    }
     printf("end insts\n");
}

void INST(){
     printf("first inst\n");
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
        case NUM_TOKEN : EXPR();
                            break;
        case PO_TOKEN : EXPR();
                            break;
        default : printf("Erreur Anayse syntaxique");
    }
     printf("end inst\n");
}

void INST_PRIME(){
    printf("first INST_PRIME\n");
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
    printf("end INST_PRIME\n");
}

void AFFECT(){
    printf("first AFFECT\n");
    AFFECT_PRIME();
    AFFECT_PRIME_SECOND();
    printf("end AFFECT\n");
}

void AFFECT_PRIME(){
    printf("first AFFECT_PRIME\n");
    switch(SYM_COUR.CODE){
        case EGAL_TOKEN : Test_Symbole(EGAL_TOKEN, ERR_CAR_INC);
                            break;
        case AFF_TOKEN : Test_Symbole(AFF_TOKEN, ERR_CAR_INC);
                            break;
        default : return ;
    }
    printf("end AFFECT_PRIME\n");
}

void AFFECT_PRIME_SECOND(){
    printf("first AFFECT_SECOND\n");
    switch(SYM_COUR.CODE){
        case ID_TOKEN : Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        AFFECT_PRIME_TROIS();
                        break ;
        case FUNCTION_TOKEN : FUNCTION();
                                break ;
        default : EXPR();
    }
    printf("end AFFECT_SECOND\n");
}

void AFFECT_PRIME_TROIS(){
    printf("first AFFECT_TROIS\n");
    switch(SYM_COUR.CODE){
        case PT_TOKEN : COMMANDE();
                        break;
        case PO_TOKEN : COMMANDE();
                        break;
        default : OP(); TERM();
    }
    printf("end AFFECT_PRIME\n");
}

void FUNCTION(){
    printf("first FUNCTION\n");
    Test_Symbole(FUNCTION_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    ARGUMENT();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    RETURN();
    printf("im here\n");
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    printf("end FUNCTION\n");
}

void ARGUMENT(){
     printf("first ARGUMENT\n");

    if(SYM_COUR.CODE == ID_TOKEN ||SYM_COUR.CODE == STRING_TOKEN){
        IDENT();
        ARGUMENT_PRIME();
    }
     printf("end ARGUMENT\n");
}

void IDENT(){
    if(SYM_COUR.CODE == ID_TOKEN )
        Test_Symbole(ID_TOKEN, ERR_CAR_INC);
    else
        Test_Symbole(STRING_TOKEN,ERR_CAR_INC);
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
     printf("first COMMANDE\n");
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
     printf("end COMMANDE\n");
}

void PARAMETRE(){
     printf("first PARAMETRE\n");
     if(SYM_COUR.CODE == ID_TOKEN ||SYM_COUR.CODE == STRING_TOKEN){
        IDENT();
        PARAMETRE_PRIME();
    }

     printf("end PARAMETRE\n");
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
     printf("first SI\n");
    Test_Symbole(IF_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    COND();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    if(SYM_COUR.CODE== ELSE_TOKEN){
        Test_Symbole(ELSE_TOKEN, ERR_CAR_INC);
         Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    }
     printf("end SI\n");
}

void POUR(){
    printf("first POUR\n");
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
    printf("end POUR\n");
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
    printf("first cond\n");
    EXPR() ;
    VERF();
    EXPR();
    printf("end cond\n");
}

void EXPR(){
    printf("first EXPR\n");
    TERM();
    OP();
    TERM();
    printf("end EXPR\n");
}

void TERM(){
    printf("first TERM\n");
    switch(SYM_COUR.CODE){
        printf("first TERM\n");
        case ID_TOKEN : Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        break;
        case NUM_TOKEN : Test_Symbole(NUM_TOKEN, ERR_COM);
                        break;
      /*  default : Test_Symbole(PO_TOKEN, ERR_CAR_INC);
                  EXPR();
                  Test_Symbole(PF_TOKEN, ERR_CAR_INC);
                  */
    }
    printf("fin TERM\n");
}

void OP(){
    printf("first OP\n");
    switch(SYM_COUR.CODE){
        case PLUS_TOKEN : Test_Symbole(PLUS_TOKEN, ERR_CAR_INC);
            break;
        case MOINS_TOKEN :Test_Symbole(MOINS_TOKEN, ERR_CAR_INC);
            break;
        case MULT_TOKEN :Test_Symbole(MULT_TOKEN, ERR_CAR_INC);
            break;
        case DIV_TOKEN :Test_Symbole(DIV_TOKEN, ERR_CAR_INC);
            break;
        case PUISS_TOKEN :Test_Symbole(PUISS_TOKEN, ERR_CAR_INC);
            break;
        case REST_TOKEN : Test_Symbole(REST_TOKEN, ERR_CAR_INC);
            break;
        case ENTIER_TOKEN : Test_Symbole(ENTIER_TOKEN, ERR_CAR_INC);
            break;
        case EGAL_TOKEN : Test_Symbole(EGAL_TOKEN, ERR_CAR_INC);
            break;
    }
    printf("end OP\n");
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
     printf("first RETURN\n");
    if(SYM_COUR.CODE == RETURN_TOKEN){
        Test_Symbole(RETURN_TOKEN, ERR_CAR_INC);
        /*Test_Symbole(PO_TOKEN, ERR_CAR_INC);
        INST();
        Test_Symbole(PF_TOKEN, ERR_CAR_INC);*/
        if(SYM_COUR.CODE == PO_TOKEN) {
            Test_Symbole(PO_TOKEN, ERR_CAR_INC);
            EXPR();
            Test_Symbole(PF_TOKEN, ERR_CAR_INC);
        }

    }
     printf("end RETURN\n");
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
                        Test_Symbole(DPT_TOKEN, ERR_CAR_INC);
                        Test_Symbole(NUM_TOKEN, ERR_CAR_INC);break;
    }
}


void Premier_sym(){
    Lire_Caractere();
    Sym_Suiv();

}









