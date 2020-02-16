#include "Analyseur_semantique.h"


void Copier_sym(char *nom){
    strcpy(sym_prec,nom);
}
void Copier(char *noma,char *nomb){
    strcpy(noma,nomb);
}
void T_DECLARATION(char *nom,TSYM sym,char *nom_cmd_func) {
    strcpy(TAB_IDFS[nb_idf].NOM,nom);
    TAB_IDFS[nb_idf].TIDF=sym;
    strcpy(TAB_IDFS[nb_idf].NOM_CMD_FUNC,nom_cmd_func);
    TAB_IDFS[nb_idf].adresse=++OFFSET;
    nb_idf++;
    /*for(int i =0 ;i<nb_idf;i++){
        printf("%s  %d  %s\t",TAB_IDFS[i].NOM,TAB_IDFS[i].TIDF,TAB_IDFS[i].NOM_CMD_FUNC);
    }
    printf("\n");*/
}
void T_FUNCTION(char *nom,int nb){
    strcpy(TAB_FUNC[nb_fun].NOM,nom);
    TAB_FUNC[nb_fun].NB_ARG = nb;
    Copier(fun_nom,"__");
    nb_arg = 0;
    nb_fun++;
}
int is_declared(char * nom){
    for(int i =0 ;i<nb_idf;i++){
        if(strcmp(TAB_IDFS[i].NOM,nom)==0 && (TAB_IDFS[i].TIDF==TIDENT)) return 0;
    }
   // printf("identifiant %s non declaré\n",sym_prec);
    return -1;
}
int is_fonction(char * nom){

    for(int i =0 ;i<nb_fun;i++){
        if(strcmp(TAB_FUNC[i].NOM,nom)==0){
                printf("%s est une fonction\n",sym_prec);
                return 0;
        }
    }
    return -1;
}

int is_nb_parameter(char * nom,int nb){

    for(int i =0 ;i<nb_fun;i++){
        if(strcmp(TAB_FUNC[i].NOM,nom)==0 && TAB_FUNC[i].NB_ARG == nb) return 0;
    }
   // printf("%s : nombre de parametre est insuffisant\n",nom);
    return -1;
}

int is_parameter(char * nom){
    for(int i =0 ;i<nb_idf;i++){
        if(strcmp(TAB_IDFS[i].NOM,nom)==0)
            if(TAB_IDFS[i].TIDF==TPARA)
                return 0;
    }
    return -1;
}

int is_argument(char * nom){
    for(int i =0 ;i<nb_idf;i++){
        if(strcmp(TAB_IDFS[i].NOM,nom)==0)
            if(TAB_IDFS[i].TIDF==TARG && strcmp(fun_nom,"__") != 0)
                return 0;
    }
    return -1;
}

int is_command(char * nom){
    for(int i =0 ;i<nb_cmd;i++){
        if(strcmp(TAB_CMD[i].NOM,nom)==0){
               // printf("%s = %s",TAB_CMD[i].NOM,nom);
                return 0;
        }
    }
    return -1;
}

int is_nb_argument(char * nom,int nb){
    for(int i =0 ;i<nb_cmd;i++){
        if(strcmp(TAB_CMD[i].NOM,nom)==0 )
            if(TAB_CMD[i].NB_PARA==-1 || TAB_CMD[i].NB_PARA==nb)
                return 0;
    }
    //printf("%s : nombre d'argrumments est insuffisant\n",nom);
    return -1;
}
