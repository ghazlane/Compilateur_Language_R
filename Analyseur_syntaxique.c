#include "Analyseur_syntaxique.h"
#include "Analyseur_lexical.h"
#include "Analyseur_semantique.c"

#define TRUE 0
#define FALSE 1
char id[20];
void Test_Symbole ( CODE_LEX cl, Erreurs COD_ERR){
    if (SYM_COUR.CODE == cl){
        Copier_sym(SYM_COUR.NOM);
        Sym_Suiv();
    }
    else if(SYM_COUR.CODE==-1) Sym_Suiv();
    else
        Erreur(COD_ERR);
}

int TestSymobleSpecial(){
    if(SYM_COUR.CODE != NEXT_TOKEN && SYM_COUR.CODE != ACCF_TOKEN && SYM_COUR.CODE != EOF_TOKEN  && SYM_COUR.CODE != BREAK_TOKEN&& SYM_COUR.CODE != RETURN_TOKEN&& SYM_COUR.CODE != PF_TOKEN)
 return TRUE;
 return FALSE;
}

void INSTS(){
    printf("first INSTS\n");
    if(TestSymobleSpecial() == TRUE){
         while(SYM_COUR.CODE == RETOUR_TOKEN)
         Test_Symbole(RETOUR_TOKEN, ERR_CAR_INC);
            if(TestSymobleSpecial() == TRUE)
                INST();
            else return;

            /*while (SYM_COUR.CODE == PV_TOKEN ){
                    if(SYM_COUR.CODE == PV_TOKEN){
                    Test_Symbole(PV_TOKEN, ERR_CAR_INC);
                    INSTS();
                }
            }*/

                    if(SYM_COUR.CODE == PV_TOKEN)  {Test_Symbole(PV_TOKEN, ERR_CAR_INC); /*printf("****** dkhl hna");*/
                  INSTS();  }
                    if(SYM_COUR.CODE == RETOUR_TOKEN){Test_Symbole(RETOUR_TOKEN, ERR_CAR_INC);/*printf("****** dkhl hna 2");*/
                    INSTS(); }
    }
     printf("end INSTS\n");
}

void INST(){
     printf("first INST\n");
    switch (SYM_COUR.CODE) {
        case ID_TOKEN :Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        Copier(id,sym_prec);
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
        default : printf("Erreur Anayse syntaxique 2 "); return;
    }
     printf("end INST\n");
}

void INST_PRIME(){
  //  printf("first INST_PRIME\n");
    switch(SYM_COUR.CODE){
    case EGAL_TOKEN :       if(is_fonction(sym_prec)==0) Erreur(ISFUNCTION);
                            T_DECLARATION(sym_prec,TIDENT,chaine_vide);
                            AFFECT();
                            break;
        case AFF_TOKEN :    if(is_fonction(sym_prec)==0) Erreur(ISFUNCTION);
                            T_DECLARATION(sym_prec,TIDENT,chaine_vide);
                            AFFECT();
                            break;
        case PT_TOKEN :     if(is_fonction(sym_prec)==0) Erreur(ISFUNCTION);
                            T_DECLARATION(sym_prec,TIDENT,chaine_vide);
                            COMMANDE();
                            break ;
        case PO_TOKEN : /*strcmp(chaine_vide,'__');
                            T_DECLARATION(sym_prec,TCMD,chaine_vide);*/
                        if (is_command(sym_prec)!=0 && is_fonction(sym_prec)!=0) { Erreur(NOTCMD);}
                        COMMANDE();
                        break ;
        default : ;
    }
  //  printf("end INST_PRIME\n");
}

void AFFECT(){
    printf("first AFFECT\n");
    AFFECT_PRIME();
    AFFECT_PRIME_SECOND();
    printf("end AFFECT\n");
}

void AFFECT_PRIME(){
  //  printf("first AFFECT_PRIME\n");
    switch(SYM_COUR.CODE){
        case EGAL_TOKEN : Test_Symbole(EGAL_TOKEN, ERR_CAR_INC);
                            break;
        case AFF_TOKEN : Test_Symbole(AFF_TOKEN, ERR_CAR_INC);
                            break;
        default : return ;
    }
   // printf("end AFFECT_PRIME\n");
}

void AFFECT_PRIME_SECOND(){
    //printf("first AFFECT_SECOND\n");
    switch(SYM_COUR.CODE){
        case ID_TOKEN : Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        if (is_declared(sym_prec)!=0 && is_argument(sym_prec)!=0)Erreur(NOTDECLARED);
                        AFFECT_PRIME_TROIS();
                        break ;
        case FUNCTION_TOKEN :   Copier(fun_nom,id);
                                T_DECLARATION(fun_nom,TFUNCT,chaine_vide);
                                FUNCTION();
                                break ;
        case STRING_TOKEN : Test_Symbole(STRING_TOKEN, ERR_CAR_INC);break;
        default : EXPR();
    }
    //printf("end AFFECT_SECOND\n");
}

void AFFECT_PRIME_TROIS(){
   // printf("first AFFECT_TROIS\n");
    switch(SYM_COUR.CODE){
        case PT_TOKEN : if (is_command(sym_prec)!=0 && is_fonction(sym_prec)!=0) { Erreur(NOTCMD);}
                        COMMANDE();
                        break;
        case PO_TOKEN : if (is_command(sym_prec)!=0 && is_fonction(sym_prec)!=0) { Erreur(NOTCMD);}
                        COMMANDE();
                        break;
        default : OP(); TERM();
    }
    //printf("end AFFECT_PRIME\n");
}
void vider(){
    while(SYM_COUR.CODE == RETOUR_TOKEN)
         Test_Symbole(RETOUR_TOKEN, ERR_CAR_INC);
}
void FUNCTION(){
    printf("first FUNCTION\n");
    Test_Symbole(FUNCTION_TOKEN, ERR_CAR_INC);
    vider();
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    ARGUMENT();
    vider();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    vider();
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    RETURN();
    printf("im here\n");
    vider();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    T_FUNCTION(fun_nom,nb_arg);
    printf("end FUNCTION\n");
}

void ARGUMENT(){
     printf("first ARGUMENT\n");
    if(SYM_COUR.CODE == ID_TOKEN ||SYM_COUR.CODE == STRING_TOKEN){
           nb_arg++;
        if(SYM_COUR.CODE == ID_TOKEN ){
                Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                T_DECLARATION(sym_prec,TARG,fun_nom);
        }
        else
        Test_Symbole(STRING_TOKEN,ERR_CAR_INC);
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
        case PT_TOKEN :
                        Test_Symbole(PT_TOKEN, ERR_CAR_INC);
                        Test_Symbole(ID_TOKEN, ERR_CAR_INC);
                        Copier(cmd_nom,sym_prec);
                        Test_Symbole(PO_TOKEN, ERR_CAR_INC);
                        PARAMETRE();
                        Test_Symbole(PF_TOKEN, ERR_CAR_INC);
                        break;
        default :       Copier(cmd_nom,sym_prec);
                        Test_Symbole(PO_TOKEN, ERR_CAR_INC);
                        PARAMETRE();
                        Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    }
     if (is_nb_parameter(cmd_nom, nb_para)!=0 && is_nb_argument(cmd_nom,nb_para)!=0 ) Erreur(NBPARA);
     nb_para = 0;
     printf("end COMMANDE\n");
}

void PARAMETRE(){
     printf("first PARAMETRE\n");
     if(SYM_COUR.CODE == ID_TOKEN ||SYM_COUR.CODE == STRING_TOKEN || SYM_COUR.CODE == NUM_TOKEN ){
        nb_para++;
        if(SYM_COUR.CODE == ID_TOKEN ){Test_Symbole(ID_TOKEN, ERR_CAR_INC);if (is_declared(sym_prec)!=0) Erreur(NOTDECLARED); }
        else if(SYM_COUR.CODE == NUM_TOKEN ) Test_Symbole(NUM_TOKEN,ERR_CAR_INC);
        else Test_Symbole(STRING_TOKEN,ERR_CAR_INC);
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
    vider();
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    vider();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    vider();
    if(SYM_COUR.CODE== ELSE_TOKEN){
        Test_Symbole(ELSE_TOKEN, ERR_CAR_INC);
        vider();
         Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    vider();
    STOP();
    vider();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    }
     printf("end SI\n");
}

void POUR(){
    printf("first POUR\n");
    Test_Symbole(FOR_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    Test_Symbole(ID_TOKEN, ERR_CAR_INC);
    if(is_fonction(sym_prec)==0) Erreur(ISFUNCTION);
    T_DECLARATION(sym_prec,TIDENT,chaine_vide);
    Test_Symbole(IN_TOKEN, ERR_CAR_INC);
    SEQ();
    Test_Symbole(PF_TOKEN,  ERR_CAR_INC);
    vider();
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    vider();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    printf("end POUR\n");
}

void TANTQUE(){
    printf("first TANTQUE\n");
    Test_Symbole(WHILE_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    COND();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    vider();
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    STOP();
    vider();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    printf("end TANTQUE\n");
}

void REPETER(){
    printf("first REPETER\n");
    Test_Symbole(REPEAT_TOKEN,ERR_CAR_INC);
    vider();
    Test_Symbole(ACCO_TOKEN, ERR_CAR_INC);
    INSTS();
    //Test_Symbole(PV_TOKEN, ERR_CAR_INC);
    /*Test_Symbole(IF_TOKEN, ERR_CAR_INC);
    Test_Symbole(PO_TOKEN, ERR_CAR_INC);
    COND();
    Test_Symbole(PF_TOKEN, ERR_CAR_INC);
    Test_Symbole(BREAK_TOKEN,ERR_CAR_INC );*/
    vider();
    Test_Symbole(ACCF_TOKEN, ERR_CAR_INC);
    printf("end REPETER\n");
}

void COND(){
    printf("first COND\n");
    EXPR() ;
    VERF();
    EXPR();
    printf("end COND\n");
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
                        if (is_declared(sym_prec)!=0 && is_argument(sym_prec)!=0)Erreur(NOTDECLARED);
                        break;
        case NUM_TOKEN : Test_Symbole(NUM_TOKEN, ERR_COM);
                        break;
        case PO_TOKEN : Test_Symbole(PO_TOKEN, ERR_CAR_INC);
                  EXPR();
                  Test_Symbole(PF_TOKEN, ERR_CAR_INC);

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
    vider();
    if(SYM_COUR.CODE == RETURN_TOKEN){
            vider();
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
        case BREAK_TOKEN : vider();  Test_Symbole(BREAK_TOKEN, ERR_CAR_INC); break ;
        case NEXT_TOKEN : vider();  Test_Symbole(NEXT_TOKEN, ERR_CAR_INC); printf("next"); break ;
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








