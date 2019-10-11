#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define fichier_tp "ENSEIGNANT-MESRS.bin"

#define fichier_index "index.bin"

#define MAX 50000
#ifndef __CLR__H__
#define __CLR__H__
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif
#define fin gotoxy(109,39);
#define up 72
#define down 80
#define left 75
#define right 77


//define les tableaux 1 lignage
#define _1 192
#define _2 193
#define _3 217
#define _4 195
#define _5 197
#define _6 180
#define _7 218
#define _8 194
#define _9 191
#define _0 179
#define _ 196

//define un etablea 2 soulignage
#define __1 200
#define __2 202
#define __3 188
#define __4 204
#define __5 206
#define __6 185
#define __7 201
#define __8 203
#define __9 187
#define __0 186
#define __ 205

// on define le et et le oou pour faciliter l'ecriture
#define ou ||
#define et &&

#define TAILLE_MAX 50
#define true 1 // booleen
#define false 0
#define et &&
#define ou ||
#define maxath 0 // c'est le nombre minimal deds athletes quils doitexister pour insere un athlete
#define ee 130
#define fin gotoxy(109,39);
#define esc 27
#define ctrl_f 6
#define ctrl_a 1
#define supp 19


typedef struct  {
char element[100] ;
}mn ;

mn menuu [9] ;






typedef struct  {
char nom_wilaya[40] ;
}wilaya ;

      wilaya tab_wly [49] ;

typedef struct  {
char nom_spec[40] ;
}spec ;

      spec tab_spe[31] ;



typedef struct  {
char nom_etab[256] ;
}etab ;

etab tab_etab [108] ;

typedef struct {
    int jj,mm,aa;
}date ;
typedef struct enreg enreg ;
struct enreg {
    int matricule ;
    char nom[30]; ///
    char prenom[30]; ///
    date date_naissance ;
    int wilaya_naissance ;
    int sexe ;
    int Grp_Sang ;
    date date_rec ;
    int grade ;
    int specialite ;
    int der_diplome ;
    int univ ;
};

typedef struct Tbloc Tbloc;
 struct Tbloc {
    enreg tab[1000] ; ///
    int Nb ;
    } ;

typedef struct Entete
{
int adrDerBloc;
} Entete;

typedef struct TObF {
    FILE *fichier ;
    Entete entete ;
}TObF ;




typedef struct enreg_i enreg_i ;
struct enreg_i {
    int matricule ;
    int nb_bloc ;
    int deplacement ;
};

typedef struct Tbloc_i Tbloc_i ;
 struct Tbloc_i {
    enreg_i tab[30000];//
    int Nb ;
    } ;

    typedef struct noms_profs {
    int num_prof ;
    char name_ens [30] ;
}noms_profs ;
Tbloc_i buff ;



int ouvrir(TObF **f,char *chemin,char mode);
void fermer(TObF *f) ;
int alloc_bloc(TObF *f) ;
void aff_entete(TObF *f, int i, int val) ;
int entete(TObF *f,int i);
void ecrireDir(TObF *f,int N_Bloc,Tbloc *buffer) ;
void lireDir(TObF *f,int N_Bloc, Tbloc *buffer) ;
void ecrireDir_i(TObF *f,int N_Bloc,Tbloc_i *buffer) ;
void lireDir_i(TObF *f,int N_Bloc,Tbloc_i *buffer) ;

int random (int nombreMax ) ;


date generate_date (int aa1,int aa2) ;
void chargement_initial (int Nbr) ;
void affichage(int d1,int d2,int num_etablissement) ;
void rech_dech_tab (int matricule ,int  *trouv ,int *i ,int *j,int *pos) ;



//--------------Les Fonctions d'affichage ------------------------//
void color(int couleurDuTexte ,int couleurDuFond);
void gotoxy(short x,short y);
void cadre(int x, int y,int hauteur,int base,int clrT,int clrF,int mode );
void esi (int x, int y,int fond,int couleur,int t);
int delay(int x) ;  // faire un puase au system pendant c millierseconds
int ecrire(char ss[],int tm) ;  // ecrier une chaine de caractaire avec un delay entre les caracteres
void debut() ;
int  menu () ;
void button(int x,int y ,int base,char c[],int mode)  ;// afficher un button ,le mode 0 c'est un cadre ligne , mode 1 : la case est en coulour
int ok_msg(char phrase[]) ; // faire une fenetre dans la console avec une(phrase) et button OK
void quitter(void) ;
void cadre_1(int x, int y,int hauteur,int base,int clrT,int clrF,int mode) ;// le mode pour faire un delay en cas ou mode !=0
void lire(int x,int y,char mot[],int caractere) ;// lire dans une place specifie en remplaçant ce qui est ecrite par (caractere)
int alphabet(const char ch) ;
void afficher_etab() ;
void afficher_wilaya () ;
void afficher_ens (enreg uu) ;
void afficher_ens_par_ens (enreg tab[5000],int taille) ;
int verifier_nombre(char mot[256]) ;
int verifier_mot(char mot[256]) ;
int region (int code_wilaya) ;
void affich_region (int reg_tr) ;

int verifier_date(int jour , int mois , int annee );
int est_valide(int j, int m, int a) ;
int longueur_mois(int m,int a) ;
int bissextile(int an);






