#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {TPARA, TARG, TIDENT,TFUNCT,TCMD} TSYM;
char	sym_prec[20],cmd_nom[20],fun_nom[20],id[20],chaine_vide[20];
typedef  struct {
      char	NOM[20];
      TSYM	TIDF;
      char	NOM_CMD_FUNC[20];
      int adresse;
} T_TAB_IDF;

typedef  struct {
      char	NOM[20];
      int NB_ARG;
} T_TAB_FUNCTION;

T_TAB_FUNCTION TAB_FUNC[1000];

typedef  struct {
      char	NOM[20];
      int NB_PARA;
} T_TAB_COMMANDE;

T_TAB_COMMANDE TAB_CMD[200] ={{"print",-1},{"paste",-1},{"read",-1},{"write",-1},{"help",1},{"start",0},{"search",1},
{"c",2},{"length",1},{"min",1},{"max",1},{"factor",1},{"order",1},{"median",1},{"integer",1},{"matrix",3},{"library",1},
{"getwd",0},{"setwd",1}};

int nb_cmd = 19,nb_arg=0,nb_para=0,nb_fun=0;

/*typedef  struct {
      char	NOM[20];
      TSYM	TIDF;
      char	NOM_CMD[20];
      int adresse;
} T_TAB_PARA;

typedef  struct {
      char	NOM[20];
      TSYM	TIDF;
      char	NOM_FUNCT[20];
      int adresse;
} T_TAB_ARG;*/

T_TAB_IDF	TAB_IDFS[200];

double OFFSET=0;
int nb_idf =0;
char Function_courant[20] ;
char Commande_courant[20] ;
void Copier_sym(char * nom);
void Copier(char *noma,char *nomb);
void T_DECLARATION(char *nom,TSYM sym,char *nom_cmd_func);
void T_FUNCTION(char *nom,int nb);
int is_declared(char * nom);
int is_fonction(char * nom);
int is_nb_parameter(char * nom,int nb);
int is_parameter(char * nom);
int is_argument(char * nom);
int is_command(char * nom);
int is_nb_argument(char * nom,int nb);
void vider_parameter(char * nom);
void vider_argument(char * nom);

