#include "tplib.h"



/*--------------Fonction d'ouverture d'un fichier--------------*/
int ouvrir(TObF **f,char *chemin,char mode)
{
*f = malloc(sizeof(TObF));
char s[3];
    if((mode == 'A') || (mode == 'a')) sprintf(s,"rb+");
    else if ((mode == 'N') || (mode == 'n')) sprintf(s,"wb+");
    else return 0;
(*f)->fichier = fopen(chemin, s);
if((*f)->fichier == NULL) return 0;
if((mode == 'A') || (mode == 'a'))
{
fread(&((*f)->entete), sizeof(Entete), 1, (*f)->fichier);
}
else if ((mode == 'N') || (mode == 'n'))
{
(*f)->entete.adrDerBloc = 0;
}
return 1;
}
/*---------------Fonction de fermuture d'un fichier -------------*/
void fermer(TObF *f)
{
rewind(f->fichier);
fwrite(&(f->entete), sizeof(Entete), 1, f->fichier);
fclose(f->fichier);
free(f);
}

/*-----------------Fonction de lecture d'un bloc----------------*/
void lireDir(TObF *f,int N_Bloc,Tbloc *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);
fread(buffer, 1, sizeof(Tbloc), f->fichier);
}
}
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/*-----------------Fonction d'écriture d'un bloc----------------*/
void ecrireDir(TObF *f,int N_Bloc,Tbloc *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);
fwrite(buffer, 1, sizeof(Tbloc), f->fichier);
}
}
/*--------------------------------------------------------------*/
int entete(TObF *f,int i)
{
if(i == 1) return (f->entete).adrDerBloc;
// else if(i == 2) return (f->entete).nbEnreg;
// else if(i == 3) return (f->entete).indice_libre;
else return -1;
}
/*--------------------------------------------------------------*/
/*-------------Fonction de modification de l'entête-------------*/
void aff_entete(TObF *f, int i, int val)
{
if(i == 1) (f->entete).adrDerBloc = val;
}
/*--------------------------------------------------------------*/
/*--------------------L'allocation d'un bloc--------------------*/
int alloc_bloc(TObF *f)
{
aff_entete(f,1,entete(f,1)+1);
return entete(f,1);
}
int random (int nombreMax )
{

	return ( rand () % nombreMax );
}



/*-----------------Fonction de lecture d'un bloc de l'index----------------*/
void lireDir_i(TObF *f,int N_Bloc,Tbloc_i *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc_i),SEEK_SET);
fread(buffer, 1, sizeof(Tbloc_i), f->fichier);
}
}
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/*-----------------Fonction d'écriture d'un bloc de l'index----------------*/
void ecrireDir_i(TObF *f,int N_Bloc,Tbloc_i *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc_i),SEEK_SET);
fwrite(buffer, 1, sizeof(Tbloc_i), f->fichier);
}
}
/*--------------------------------------------------------------*/



void rech_dech_tab (int matricule ,int  *trouv ,int *i ,int *j,int *pos)

{


    int inf , sup ;
    inf = 0 ;
    sup = buff.Nb -1;
    int mid ;
    *trouv = 0 ;
    if (buff.tab[buff.Nb-1].matricule < matricule )
        mid = buff.Nb ;

    else if (buff.tab[0].matricule > matricule )
        mid = 0 ;
    else

        while ((sup >= inf ) && ! *trouv )
        {
            mid = (sup  + inf ) / 2 ;
            if ((buff.tab[mid].matricule < matricule ) && (buff.tab[mid+1].matricule > matricule) )
            {
                mid ++ ;
                break ;
            }
            else if ((buff.tab[mid].matricule > matricule ) && (buff.tab[mid-1].matricule < matricule) )
                break ;


            if (buff.tab[mid].matricule == matricule)
            {
                *trouv = 1 ;
            }
            else if (matricule < buff.tab[mid].matricule  )
                sup = mid -1 ;
            else inf = mid +1 ;


        }
    if (*trouv )
    {

        *i = buff.tab[mid].nb_bloc ;
        *j = buff.tab[mid].deplacement ;
    }
    *pos = mid ;

}



void chargement_initial (int Nbr) {
    int i,m=0,u,found,ii=0,jj=8,posi,k,cpt=0;
    int matri ,matri_err , nb_collision=0;
    TObF *z , *s ;
    Tbloc buf ;
    FILE *names ;
    noms_profs tab_noms_ens [750];
    noms_profs tab_prenoms_ens [170] ;
    char ligne[40] ;
    names=fopen("noms.txt","r") ;
    while (!feof(names)) { // téléchargement des noms depuis le fichiers des noms en les mettons dans un tableau dans la mémoire centrale
        fgets(ligne,sizeof(ligne),names) ;
        ligne[strlen(ligne)-1] ='\0' ;
        strcpy(tab_noms_ens[cpt].name_ens,ligne) ;
        tab_noms_ens[cpt].num_prof=cpt ;
        cpt++ ;
    }
    fclose(names) ;
cpt=0 ;
    names=fopen("prenoms.txt","r") ;
    while (!feof(names)) { // téléchargement des noms depuis le fichiers des noms en les mettons dans un tableau dans la mémoire centrale
        fgets(ligne,sizeof(ligne),names) ;
        ligne[strlen(ligne)-1] ='\0' ; // c'est a verifier plus tard caractère 10 est remplacer par space 32 ;
        strcpy(tab_prenoms_ens[cpt].name_ens,ligne) ;
        tab_prenoms_ens[cpt].num_prof=cpt ;
        cpt++ ;
    }

    fclose(names) ;

    /*--------------------------------------------------------------*/





 // l'equivalent de randomize

   /*-----------------------La création des deux fichier -----------------------*/

    ouvrir(&z,fichier_index,'n') ;
    buff.Nb=0 ;
    buf.Nb=0 ;
    aff_entete(z,1,0) ;
    ouvrir(&s,fichier_tp,'n') ;
    aff_entete(s,1,0) ;
    u=1; // initialisation du 1er bloc   //u=1  u représente le numero de bloc

                                           srand ( time ( NULL ));
    for (i=0;i<Nbr;i++) {


            if (i==0) {
                buff.Nb++ ;
                matri =random(888888)+111112 ;
                buff.tab[0].matricule = matri ;
                buff.tab[0].nb_bloc = 1 ;
                buff.tab[0].deplacement = 0 ;
                aff_entete(z,1,1) ;
                aff_entete(s,1,1) ;
            }
            else {
                /*La recherche d'un nouveau matricule */
                matri_err=1 ;

                while (matri_err==1) {
                    matri =random(888888)+111112 ;
                 //   system("pause") ; printf("la %d itération  |   %d   |  %d   \n",i,matri,nb_collision) ;

                    rech_dech_tab(matri,&found,&ii,&jj,&posi) ;
                   //printf("%d",found) ;
                    //printf("%d",found) ;  // ouverture et fermuture du fichier index
                    //system("pause") ; printf("La fonction recherche decho a renvoyer %d , %d , %d , %d\n",found,ii,jj,posi) ;
                    if (found==0) { // ce matricule n'existe pas dans le fichier d'index


                    for (k=i;k>posi;k--)
                    {
                            buff.tab[k] = buff.tab[k-1] ;
                    } // l'insertion du matricule dans le fichier d'index  ;

                        //if(i>0) lireDir_i(z,1,&buf2) ;

                    buff.tab[posi].matricule=matri ;
                    buff.tab[posi].nb_bloc=u ;
                    buff.tab[posi].deplacement=m ;
                    buff.Nb = buff.Nb + 1 ; // incrémenter le nombre d'enregistrements dans la table d'index
                    matri_err = 0 ;
                    }
                    else {
                        nb_collision ++ ;
                    }
                }
                }


            buf.tab[m].matricule = matri;
            buf.tab[m].sexe= random(2) ;
            buf.tab[m].date_naissance = generate_date(1953,1992) ;
            strcpy(buf.tab[m].nom,tab_noms_ens[random(720)+1].name_ens) ;
            strcpy(buf.tab[m].prenom,tab_prenoms_ens[random(160)+1].name_ens) ;
            buf.tab[m].date_rec = generate_date(1979,2018) ;
            buf.tab[m].wilaya_naissance=random(48)+1 ;
            buf.tab[m].der_diplome = random(5)+1 ;
            buf.tab[m].grade=random(6)+1 ;
            buf.tab[m].univ=random(106)+1 ;
            buf.tab[m].Grp_Sang=random(8)+1 ;
            buf.tab[m].specialite = random(30)+1 ;
            buf.Nb++;
            //printf("%d  |",buf.Nb) ;
        m++ ;

        if (m==1000) {

                ecrireDir(s,u,&buf) ;
                u++ ;
                if (Nbr!=(i+1))  alloc_bloc(s) ;
                m=0 ;
                buf.Nb=0 ;
            }
        }

        if (m!=0) { // l'ecriture des derniers elements < 1000 qui ne seront pas ecrit dans la premiere boucle
            ecrireDir(s,u,&buf) ;
        }

ecrireDir_i(z,1,&buff);
aff_entete(z,1,1) ;
fermer(z) ;
fermer(s) ;

}
date generate_date (int aa1,int aa2)
{
    date gen_date ;
    gen_date.mm = random(12)+1 ;
    if (gen_date.mm ==2) {
        gen_date.jj = random(28)+1 ;
        }
    else gen_date.jj = random(31)+1 ;
    gen_date.aa = random(aa2-aa1)+aa1;
    return gen_date ;
}


void affichage(int d1,int d2,int num_etablissement) {

int i,j ;
TObF *z ;
enreg tab_aff [10000];
int Nb_Tab_aff=0 ;
Tbloc bufer;
ouvrir(&z,fichier_tp,'a') ;
for (i=1;i<=entete(z,1);i++) {

        lireDir(z,i,&bufer) ;
        for (j=0;j<bufer.Nb;j++)
        {

            if (bufer.tab[j].univ==num_etablissement)
            {

                if((2018-bufer.tab[j].date_rec.aa>=d1) && (2018-bufer.tab[j].date_rec.aa<=d2)) {
                    tab_aff[Nb_Tab_aff] = bufer.tab[j] ; Nb_Tab_aff ++ ;
                }
                //printf("Matricule %6d |nom %4s %4s| date_rec %4d\n",bufer.tab[j].matricule,bufer.tab[j].nom,bufer.tab[j].prenom,bufer.tab[j].date_rec.aa) ;
            }
        }
}
if (Nb_Tab_aff>0) {
afficher_ens_par_ens(tab_aff,Nb_Tab_aff) ;
}
else ok_msg("Il y'a aucun ensegnant") ;
}

void afficher_ens_par_ens (enreg tab[10000],int taille) {
    int c ;
    int k=0 ;
    afficher_ens(tab[0]) ;
    do {
        c=getch();
        if ((c==left) ou (c==right)) {
            if (c==left) {
                k-- ;
                if (k<0) k=0 ;
                else {
                        system("cls") ;
                        afficher_ens(tab[k]) ;
                     }
            }
            if (c==right) {
                k++ ;
                if (k==taille) k=taille-1;
                else {
                        system("cls") ;
                        afficher_ens(tab[k]) ;
                     }
            }
        }


    } while (c!=esc) ;
}
void afficher_ens (enreg uu) {

//    cadre(0,0,37,109,0,7,0) ;

    if (uu.sexe) cadre(0,0,37,109,1,7,0);
        else cadre (0,0,37,109,12,7,0) ;
    gotoxy(4,1) ;
    printf("Le Matricule : %d",uu.matricule) ;
    gotoxy(4,4) ;
    printf("Le nom : %s",uu.prenom) ;
    gotoxy(4,7) ;
    printf("Le prenom : %s",uu.nom) ;
    gotoxy(4,10) ;
    printf("La date de naissance: %d-%d-%d",uu.date_naissance.jj,uu.date_naissance.mm,uu.date_naissance.aa) ;
    gotoxy(4,13) ;
    printf("Wilaya de naissance : %s",tab_wly[uu.wilaya_naissance-1].nom_wilaya) ;
    gotoxy(4,16) ;
        if (uu.sexe==0) {
        printf("Le Sexe : Femme");
        }
        if (uu.sexe==1) {
        printf("Le Sexe : Homme");
        }
    gotoxy(4,19) ;
    printf("Le groupe sanguin : ") ;
    gotoxy(4+21,19) ;
        switch (uu.Grp_Sang) {
        case 1 : printf("O-") ;
                 break ;
        case 2 : printf("O+") ;
                 break ;
        case 3 : printf("A-") ;
                 break ;
        case 4 : printf("A+") ;
                 break ;
        case 5 : printf("B-") ;
                 break ;
        case 6 : printf("B+") ;
                 break ;
        case 7 : printf("AB-") ;
                 break ;
        case 8 : printf("AB+") ;
                 break ;
        }
    gotoxy(4,22) ;
    printf("La date de recrutement : %d-%d-%d",uu.date_rec.jj,uu.date_rec.mm,uu.date_rec.aa) ;
    gotoxy(4,25) ;
    printf("Le grade : ",uu.grade) ;
    gotoxy(17,25) ;
        switch(uu.grade) {
        case 1 : printf("Professeur") ;
                 break ;
        case 2 : printf("Maitre de conference rang A") ;
                 break ;
        case 3 : printf("Maitre de conference rang B") ;
                 break ;
        case 4 : printf("Maitre assisstant(e) rang A") ;
                 break ;
        case 5 : printf("Maitre assisstant(e) rang B") ;
                 break ;
        case 6 : printf("Assisstant(e)") ;
        }
    gotoxy(4,28) ;
    printf("Le dernier diplome : ",uu.der_diplome) ;
    gotoxy(26,28) ;
        switch (uu.der_diplome) {
        case 1 : printf("Doctorat d'etat") ;
                 break ;
        case 2 : printf("Doctorat en science ") ;
                 break ;
        case 3 : printf("PhD") ;
                 break ;
        case 4 : printf("HDR") ;
                 break ;
        case 5 : printf("Magistere") ;
                 break ;
        }
    gotoxy(4,31) ;
    printf("La specialite : %s ",tab_spe[uu.specialite-1].nom_spec) ;
    gotoxy(4,34) ;
    printf("L'etablissement universitaire : %s",tab_etab[uu.univ-1].nom_etab) ;




    fin
}





//-------------------Les fonctions d'affichage ---------//
void color(int couleurDuTexte ,int couleurDuFond) // du couleurs
{
	HANDLE     H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,couleurDuFond*16+couleurDuTexte);
}

//Defines gotoxy()
void gotoxy(short x,short y)
{
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

// dessener un tableau de deux soulignage  avec des demosions donne avec les couleurs
void cadre(int x, int y,int hauteur,int base,int clrT,int clrF,int mode )
{
	color(clrT,clrF);
	gotoxy(x,y);
	printf("%c",201);
	gotoxy(x+base+1,y+1+hauteur);
	printf("%c",188);
	gotoxy(x+base+1,y);
	printf("%c",187);
	gotoxy(x,y+hauteur+1);
	printf("%c",200);
	int ii;
	for (ii=0;ii<hauteur;ii++)
	{
		gotoxy(x,y+ii+1);
		printf("%c",186);
		gotoxy(x+base+1,y+ii+1);
		printf("%c",186);
		if (mode != 0) delay(12);

	}

		for (ii=0;ii<base;ii++)
	{
		gotoxy(x+ii+1,y);
		printf("%c",205);
		gotoxy(x+ii+1,y+hauteur+1);
		printf("%c",205);
		if (mode != 0)delay(12);
	}
}

void esi (int x, int y,int fond,int couleur,int t)
{
	color(couleur,couleur);
	// E
	gotoxy(x,y);
	printf("*******");
	delay(t);
	gotoxy(x,y+1);
	printf("*******");
	delay(t);
	gotoxy(x,y+2);
	printf("**");
	delay(t);
	gotoxy(x,y+3);
	printf("*****");
	delay(t);
	gotoxy(x,y+4);
	printf("*****");
	delay(t);
	gotoxy(x,y+5);
	printf("**");
	delay(t);
	gotoxy(x,y+6);
	printf("*******");
	delay(t);
	gotoxy(x,y+7);
	printf("*******");
	delay(t);

	// S
	gotoxy(x+8,y+7);
	printf("*******");
	delay(t);
	gotoxy(x+8,y+6);
	printf("*******");
	delay(t);
	gotoxy(x+8+5,y+5);
	printf("**");
	delay(t);
	gotoxy(x+8,y+4);
	printf("*******");
	delay(t);
	gotoxy(x+8,y+3);
	printf("*******");
	delay(t);
	gotoxy(x+8,y+2);
	printf("**");
	delay(t);
	gotoxy(x+8,y+1);
	printf("*******");
	delay(t);
	gotoxy(x+8,y);
	printf("*******");
	delay(t);

	// I
	int ii=0,jj=0;
	for (jj=0;jj<6;jj++)
	{

	for (ii = 0;ii<3;ii++)
	{

	gotoxy(x+16+ii,y+7-jj);
	printf("*");
	delay(t);
	}
	}


	// tete
	for (ii=0;ii<3;ii++)
	{
	switch (ii)
	{

	case 0 : color(4,7);
			break;
	case 1 : color(10,7);
			break;
	case 2 : color(9,7);
			break ;
	}
	gotoxy(x+16,y+1);
	printf("%c",_1);
	delay(t);
	gotoxy(x+17,y+1);
	printf("%c",_);
	delay(t);
	gotoxy(x+18,y+1);
	printf("%c",_3);
	delay(t);

	gotoxy(x+16,y);
	printf("%c",_7);
	delay(t);
	gotoxy(x+17,y);
	printf("%c",_);
	delay(t);
	gotoxy(x+18,y);
	printf("%c",_9);
	delay(t);

	}
	color(4,7);
gotoxy(x+21,y+1);
ecrire("Ecole nationale\n",20);
gotoxy(x+21,y+3);
ecrire("Superieure\n",20);
gotoxy(x+21,y+5);
ecrire("d'Informatique",20);
	gotoxy(110,39);
	return;
}
int delay(int x) // faire un puase au system pendant c millierseconds
{
	clock_t t1,t2;
	float tmp;
	int ii;
	t1=clock();
	do
	{
		t2=clock();
		tmp=(float)(t2-t1)*1000/CLOCKS_PER_SEC ;

	} while (tmp < x);
	return 0;

}

int ecrire(char ss[],int tm) // ecrier une chaine de caractaire avec un delay entre les caracteres
{
	int uu ;
	for (uu=0;uu<strlen(ss);uu++)
	{
		delay(tm);
		printf("%c",ss[uu]);

	}

}



void debut()
{
	int i,j,k;
	char zer ;
for(i=0;i<111;i++)
	{
	for(j=0;j<40;j++)
		{
			color(11,11);
			gotoxy(i,j) ;
			printf(".") ;

		}
	}
	for(i=0;i<55;i++)
	{
		for(j=0;j<40;j++)
		{
			color(2,5) ;
			gotoxy(i,j);
            printf(".");
			color(3,5) ;
			gotoxy(111-i,j) ;
			printf(".") ;
		}
	}
	for (i=0;i<40;i++)
	{
		for (j=0;j<111;j++)
		{
			color(7,7) ;
			gotoxy(j,i) ;
			printf(".") ;
		}
	}
color(15,15) ;
cadre(0,0,38,108,0,7,0) ;
esi(30,1,7,0,50);
gotoxy(20,10);
ecrire("Travail Pratiique N 1 :: Structure Simple de Fichier : Methode TObF",20);
gotoxy(20,11) ;
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196);
gotoxy(24,12) ;
ecrire("    Structure de Fichiers et Structure de Donnees SFSD",20);
gotoxy(24,13) ;
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196);
color(12,7) ;
gotoxy(13,15) ;
ecrire("Realise par :",35) ;
gotoxy(13,16);
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196,196,196,196) ;
color(4,7);
gotoxy(17,18) ;
ecrire("Mimene Younes",25) ;
gotoxy(17,19) ;
ecrire("Kadri Mohamed El Said",25) ;
color(12,7) ;
gotoxy(75,15) ;
ecrire ("Encadre Par :",35) ;
gotoxy(75,16) ;
printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196,196,196,196,196,196) ;
color(4,7)  ;
gotoxy(78,18) ;
printf("Dr. KERMI Adel") ;

/*
color(4,7) ;
gotoxy(84,36) ;
printf("chargement") ;
k=1 ;
for (i=70;i<108;i++)
{
	gotoxy(i,37) ;
	color(1,1) ;
	printf("-") ;
	if((i>85)&&(i<98)) delay(70) ;
	else
	{
		delay(35) ;
	}
	gotoxy(96,36);
	if (i==106) k=98 ;
	if (i==107) k=100;
	color(0,7) ;
	printf("(%d %c)",k,37);
	k=k+3 ;
}
gotoxy(1,38) ;*/
}

int  menu ()
{

	int ch;
	int i,j ;
	system("cls") ;
	cadre(0,0,37,109,0,7,0) ;

	for(i=1;i<23;i++)
	{
	gotoxy(i,1) ;
	color(8,8) ;
	printf(".") ;
	}

	gotoxy(23,1);
	color(4,7);
	ecrire("Minstere de l'Enseigement Superieur et Recheche Scientfique",0) ;
for(i=82;i<=109;i++)
	{
	gotoxy(i,1) ;
	color(8,8) ;
	printf(".") ;
	}
	for (i=1;i<110;i++)
	{
		if((i>=23)&&(i<82)) color(7,7) ;
		else color(8,8) ;
	gotoxy(i,2) ;
	printf(".") ;
	}

	for(j=3;j<7;j++)
	{

		for (i=1;i<110;i++)
		{

			gotoxy(i,j) ;
			color(8,8) ;
			printf(".") ;
	 	}

	}
	gotoxy(31,3) ;
	color(4,8) ;
	printf("Ecole National Superieur De l'informatique ") ;
	gotoxy(25,5) ;
	printf("TP En Structure de Fichiers et Structure de donnees ");


	/*gotoxy(25,8) ;
	color(4,7) ;
	ecrire("I N S C R I P T I O N   A U    J E U   O L Y M P I Q U E",15) ;
	gotoxy(38,10) ;
printf("  ,---.   ,---.   ,---.\n");
gotoxy(38,11) ;
printf(",'     `.'     `.'     `.\n");
gotoxy(38,12) ;
printf("|     ,-|-.   ,-|-.     |\n");
gotoxy(38,13) ;
printf("`.  ,' ,'. `.' ,'. `.  ,'\n");
gotoxy(38,14) ;
printf("  `-|-'   `-|-'   `-|-'\n");
gotoxy(38,15) ;
printf("    `.     ,',     ,'\n");
gotoxy(38,16) ;
printf("      `---'   `---'   \n") ;*/
		for (i=1;i<38;i++)
	{
		if((i>0)&&(i<7))  color(0,8) ;
		else color(0,7) ;

		gotoxy(17,i) ;
		printf("%c",186) ;
		gotoxy(109-18,i);
		printf("%c",186) ;

	}
for(i=0;i<10;i++)
{
	gotoxy(94+i,8) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<6;i++)
{
	gotoxy(94,i+8) ;
	color(8,8) ;
	printf(".") ;
	gotoxy(95,i+8) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<10;i++)
{
	gotoxy(94+i,14) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<10;i++)
{
	gotoxy(94+i,11) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<10;i++)
{
	gotoxy(94+i,16) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<3;i++)
{
	gotoxy(94,i+16) ;
	color(8,8) ;
	printf(".") ;
	gotoxy(95,i+16) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<10;i++)
{
	gotoxy(94+i,19) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<4;i++)
{
	gotoxy(102,i+19) ;
	color(8,8) ;
	printf(".") ;
	gotoxy(103,i+19) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<10;i++)
{
	gotoxy(94+i,23) ;
	color(8,8) ;
	printf(".") ;
}
for(i=0;i<7;i++)
{
	gotoxy(99,i+28) ;
	color(8,8) ;
	printf(".") ;
	gotoxy(100,i+28) ;
	color(8,8) ;
	printf(".") ;
}
gotoxy(99,26) ;
color(1,1) ;
printf(".") ;
gotoxy(100,26) ;
color(1,1) ;
printf(".") ;
gotoxy(99,25) ;
color(1,1) ;
printf(".") ;
gotoxy(100,25) ;
color(1,1) ;
printf(".") ;

color(4,7);
gotoxy(2,28-6) ; printf("TP realiser par") ;
color(0,7) ;
gotoxy(2,30-6) ; printf("* Kadri Mohamed") ;
gotoxy(2,31-6) ; printf("El Said") ;
gotoxy(2,33-6) ;printf("* Mimene Younes") ;
gotoxy(2,35-6) ;color(4,7) ; printf("Encadre Par") ;
gotoxy(2,37-6) ;color(0,7) ; printf("- Dr Kermi Adel") ;
gotoxy(1,36) ; printf("ESI ALGER") ;
gotoxy(6,37) ; printf("2018/2019") ;
int ff = 11 ;
for(i=18;i<91;i++)
{
	if((i>45)&&(i<59)) color(7,7) ;
	else 	color(8,8) ;
	gotoxy(i,19-ff) ;
	printf(".") ;
	if((i>45)&&(i<59)) color(7,7) ;
	else 	color(8,8) ;
	gotoxy(i,20-ff) ;
	printf(".") ;

	gotoxy(i,21-ff) ;
	color(8,8) ;
	printf(".") ;
}
gotoxy(46,19-ff) ;
color(4,7) ;
printf("L E   M E N U");

gotoxy(25,25) ;
color(0,9) ;
int gg = 68 ;
button(46-4 -(gg-22)/2 ,22-ff,gg,"Ajouter un nouvel enseignant",0);
button(46-4-(gg-22)/2,25-ff,gg,"Modifier l'etablissement d'un enseignant",1);
button(46-4-(gg-22)/2,28-ff,gg,"Supprimer un enseignant",1);
button(46-4-(gg-22)/2,31-ff,gg,"Supprimer une specialite",1) ;
button(46-4-(gg-22)/2,34-ff,gg,"Afficher les enseignants selon l'anciennte et l'etablissement",1);
button(46-4-(gg-22)/2,37-ff,gg,"Consulter les enseignant selon la region",1);
button(46-4-(gg-22)/2,40-ff,gg,"Afficher l'entete du fichier ",1);
button(46-4-(gg-22)/2,43-ff,gg,"Sortir",1) ;
fin
int k=0;
int kk= 0 ;
do
{
	ch=getch() ;
	kk= k ;
	if(ch==up) k--;
	if (ch== down)  k++ ;
	k=(k+8)%8 ;
	button(46-4-(gg-22)/2,22+k*3-ff,gg, menuu[k].element ,0);
    button(46-4-(gg-22)/2,22+kk*3-ff,gg, menuu[kk].element ,1);





	fin




}while((ch!=esc)&&(ch!='\r') );
int l ;
if ((k==7) ou (ch==esc))
{
system("cls") ;
l=ok_msg("Etes Vous sur de sortir du programme ") ;
if (l=='\r')
	{
		quitter();
		return -1 ;
		exit(1) ;
	}
else k=menu() ;
}

   return k ;

}


void quitter(void)
{
		gotoxy(33,20) ;

	color(4,7) ;
	ecrire("Le programme va quitter dans : ... ",50);
	int y;
	int ii ;
	printf ("\n") ;
	gotoxy(33,21) ;

	for (y=0;y<3;y++)
	{
		printf(" %d ",3-y);
		if(y!=3){
		for(ii=0;ii<3;ii++)
		{
			printf(".") ;delay(500) ;
		}}
		delay(600);
	}
	exit(EXIT_FAILURE);
	return;
}


int alphabet(const char ch)
{
	if (((ch>96) et (ch<123)) ou (( ch>64)et (ch <91 ) ou (ch == 'é') ou (ch == 'è') ou(ch=='ê')) )return 1;
	else return 0;

}

void lire(int x,int y,char mot[],int caractere) // lire dans une place specifie en remplaçant ce qui est ecrite par (caractere)
{
    int c ,i=0;
    gotoxy(x,y);
    do
    {

        c=getch() ;

        if (((!alphabet(c)) && (c != '\'')&&(c != '\b') &&(c!='\r') &&(c!=esc) && (c!= " ")) || ((i>12) && (c != '\b') && (c!=esc) && (c!='\r') ) ) printf("%c",7);
        else
        if (c != '\r')
        {
            if (c != '\b')
                {
                  if (caractere == 0) printf("%c",c); else   printf("%c",caractere) ;
                    mot[i] = c ;
                    i++;
                }
                else
                {
                    if (i>0)
                    {
                        i-- ;
                        gotoxy(x+i,y);
                        printf(" ");
                        gotoxy(x+i,y);

                    }
                }
        }
    } while ((c != '\r') && (c!=esc)) ;
    int j;
    if (c == esc)
    {
        strcpy(mot,"0");
        for (j=0;j<i;j++)
        {
            gotoxy(x+j,y);
            printf(" ");
        }
    }
    else
        mot[i] = '\0' ;
    return  ;
}



void button(int x,int y ,int base,char c[],int mode) // afficher un button ,le mode 0 c'est un cadre ligne , mode 1 : la case est en coulour
{

	int i=0,j=0;
	int b=(base - strlen(c))/2 ;
	if (mode == 0)
	{
	for (i=0;i<base;i++)
	{
		gotoxy(x+i,y);
		color(4,7);//**
		printf("%c",220);
		gotoxy(x+i,y+1);
		if ((i >=b) && (i<b+strlen(c)))
		{
		color(15,4);
		printf("%c",c[j]);
		++j;
		}
		else
		{
		color(4,4);
			printf("%c",219);
		}
		gotoxy(x+i,y+2);
		color(4,7);//*
		printf("%c",223);
		i+1  ;
	//	delay(10);
	}
	}
	else
	if (mode == 1)
	{
		color(9,7);
		gotoxy(x,y);
		printf("%c",_7);
		gotoxy(x+base-1,y);
		printf("%c",_9);
		gotoxy(x,y+2);
		printf("%c",_1);
		gotoxy(x+base-1,y+2);
		printf("%c",_3);
		gotoxy(x,y+1);
		printf("%c",_0);
		for (i=1;i<base-1;i++)
		{

			gotoxy(x+i,y);
			color(9,7);
			printf("%c",_);
			gotoxy(x+i,y+1);
			if ((i >=b) && (i<b+strlen(c)))
			{
			color(0,7);
			printf("%c",c[j]);
			++j;
			}
			else
			{
			color(7,7);
				printf("%c",219);
			}
			gotoxy(x+i,y+2);
			color(9,7);
			printf("%c",_);
			i+1  ;
		//	delay(10);
		}
		gotoxy(x+base-1,y+1);
		printf("%c",_0);

	}
	return ;
}

void cadre_1(int x, int y,int hauteur,int base,int clrT,int clrF,int mode) // le mode pour faire un delay en cas ou mode !=0
{
	color(clrT,clrF);
	gotoxy(x,y);
	printf("%c",_7);
	gotoxy(x+base+1,y+1+hauteur);
	printf("%c",_3);
	gotoxy(x+base+1,y);
	printf("%c",_9);
	gotoxy(x,y+hauteur+1);
	printf("%c",_1);
	int ii;
	for (ii=0;ii<hauteur;ii++)
	{
		gotoxy(x,y+ii+1);
		printf("%c",_0);
		gotoxy(x+base+1,y+ii+1);
		printf("%c",_0);
		if (mode != 0) delay(12);

	}

		for (ii=0;ii<base;ii++)
	{
		gotoxy(x+ii+1,y);
		printf("%c",_);
		gotoxy(x+ii+1,y+hauteur+1);
		printf("%c",_);
		if (mode != 0) delay(12);
	}

    return ;
}


int ok_msg(char phrase[]) // faire une fenetre dans la console avec une(phrase) et button OK
    {
    int i,j;
    cadre_1(30,14,10,50,15,15,0);
    for (j=0;j<10;j++)
        for (i=0;i<50;i++)
        {

            gotoxy(31+i,15+j);
            printf(" ");

        }
    cadre(30,14,0,50,9,9,0);
    color(12,9);
    gotoxy(30+45,15);
    printf("- [] X");
    gotoxy(30+5,14+4);
    color(0,15);
    printf("%s",phrase);
    cadre_1(30+20,14+7,1,10,0,15,0);
    gotoxy(50+5,21+1);
    printf("OK");
    fin
    int c;
    do c= getch();  while ((c != '\r') && (c !=esc)) ;
    if (c=='\r')
    {
    cadre_1(30+20,14+7,1,10,7,7,0);
    gotoxy(50+1,21+1);
    color(0,7);
    printf("    OK    ");
    delay(50);
    cadre_1(30+20,14+7,1,10,0,15,0);
    gotoxy(50+1,21+1);
    color(0,7);
    printf("    OK    ");
    delay(20);
    }
    color(0,7);
    system("cls");
    cadre(0,0,37,109,15,7,0);

    fin
    return c ;
}

void afficher_etab() {

int yy ;
for (yy=1;yy<107;yy++) {
    printf("%d -- %s\n",yy,tab_etab[yy-1].nom_etab) ;
    if ((yy % 39)==0) getch() ;
    if (yy == 106) getch() ;
}
}
void afficher_wilaya () {
    int yy ;
    for (yy=1;yy<49;yy++) {
        printf("%2d --%20s   | ",yy,tab_wly[yy-1].nom_wilaya) ;
        printf("%2d --%20s   | ",yy+1,tab_wly[yy].nom_wilaya) ;
        printf("%2d --%20s   \n",yy+2,tab_wly[yy+1].nom_wilaya) ;
        yy+=2;
    }
}


int verifier_mot(char mot[256])
{
    int i  ;
    for (i = 0 ; i< strlen(mot) ; i++)
    {
        if (!alphabet(mot[i]) )
            return 0 ;
    }

    return 1;


}

int verifier_nombre(char mot[256]   )
{
    int i  ;
    int s = 0 ;
    for (i = 0 ; i< strlen(mot) ; i++)
    {
        if ((mot[i] < 48) ou (mot[i] >= 58) )
            return -1 ;

        s=s*10 + mot[i] - 48 ;
    }

    return s;
}

int region (int code_wilaya) {
    if (code_wilaya==1) return 1;
    if (code_wilaya==2) return 1 ;
    if (code_wilaya==3) return 2;
    if (code_wilaya==4) return 3 ;
    if (code_wilaya==5) return 3 ;
    if (code_wilaya==6) return 2;
    if (code_wilaya==7) return 3 ;
    if (code_wilaya==8) return 1;
    if (code_wilaya==9) return 2 ;
    if (code_wilaya==10) return 2 ;
    if (code_wilaya==11) return 1;
    if (code_wilaya==12) return 3;
    if (code_wilaya==13) return 1;
    if (code_wilaya==14) return 1;
    if (code_wilaya==15) return 2;
    if (code_wilaya==16) return 2;
    if (code_wilaya==17) return 2;
    if (code_wilaya==18) return 3;
    if (code_wilaya==19) return 3;
    if (code_wilaya==20) return  1;
    if (code_wilaya==21) return  3;
    if (code_wilaya==22) return 1;
    if (code_wilaya==23) return 3;
    if (code_wilaya==24) return 3;
    if (code_wilaya==25) return 3;
    if (code_wilaya==26) return 2;
    if (code_wilaya==27) return 1;
    if (code_wilaya==28) return 2;
    if (code_wilaya==29) return 1;
    if (code_wilaya==30) return  3;
    if (code_wilaya==31) return 1;
    if (code_wilaya==32) return 1;
    if (code_wilaya==33) return 3;
    if (code_wilaya==34) return 3;
    if (code_wilaya==35) return 2;
    if (code_wilaya==36) return 3;
    if (code_wilaya==37) return 1;
    if (code_wilaya==38) return 1;
    if (code_wilaya==39) return 3;
    if (code_wilaya==40) return 3;
    if (code_wilaya==41) return 3;
    if (code_wilaya==42) return 2;
    if (code_wilaya==43) return 3;
    if (code_wilaya==44) return 2;
    if (code_wilaya==45) return 1;
    if (code_wilaya==46) return 1;
    if (code_wilaya==47) return 2;
    if (code_wilaya==48) return 1;

}



void affich_region (int reg_tr)
{

int i,j ;
TObF *z ;
int reg ;
enreg tab_aff [10000];
int Nb_Tab_aff=0 ;
Tbloc bufer;
ouvrir(&z,fichier_tp,'a') ;
for (i=1;i<=entete(z,1);i++) {

        lireDir(z,i,&bufer) ;
        for (j=0;j<bufer.Nb;j++)
        {
            reg=region(bufer.tab[j].wilaya_naissance) ;
            if (reg==reg_tr)
            {

                    tab_aff[Nb_Tab_aff].date_naissance = bufer.tab[j].date_naissance ;
                    tab_aff[Nb_Tab_aff].date_rec = bufer.tab[j].date_rec ;
                    tab_aff[Nb_Tab_aff].der_diplome = bufer.tab[j].der_diplome ;
                    tab_aff[Nb_Tab_aff].grade = bufer.tab[j].grade ;
                    tab_aff[Nb_Tab_aff].Grp_Sang = bufer.tab[j].Grp_Sang ;
                    tab_aff[Nb_Tab_aff].matricule = bufer.tab[j].matricule ;
                    tab_aff[Nb_Tab_aff].sexe = bufer.tab[j].sexe ;
                    tab_aff[Nb_Tab_aff].specialite = bufer.tab[j].specialite ;
                    tab_aff[Nb_Tab_aff].univ = bufer.tab[j].univ ;
                    tab_aff[Nb_Tab_aff].wilaya_naissance = bufer.tab[j].wilaya_naissance ;
                    strcpy( tab_aff[Nb_Tab_aff].nom , bufer.tab[j].nom ) ;
                    strcpy(tab_aff[Nb_Tab_aff].prenom , bufer.tab[j].prenom) ;







                    Nb_Tab_aff ++ ;
            }
        }
}
if (Nb_Tab_aff>0) {
afficher_ens_par_ens(tab_aff,Nb_Tab_aff) ;
}
else ok_msg("Il y'a aucun enseignant") ;

fermer(z) ;
}



/*********************/
// retourne 1 si l'anne est bissextile et 0 si c'est le contraire
int bissextile(int an)
{
   if (an%400==0) return 1;
   if (an%100==0) return 0;
   if (an%4==0) return 1;
   return 0;
}

// retourne la longueur du mois selon le mois et l'année
int longueur_mois(int m,int a)
{
    switch(m)
    {
    case 1: return 31;
    case 2:
         if (bissextile(a))
         return 29;
         else
         return 28;
    case 3: return 31;
    case 4: return 30;
    case 5: return 31;
    case 6: return 30;
    case 7: return 31;
    case 8: return 31;
    case 9: return 30;
    case 10: return 31;
    case 11: return 30;
    case 12: return 31;
    default: return 0;
    }
}

// retourne 0 si la date n'est pas valide et 1 dans le cas contraire
int est_valide(int j, int m, int a)
{
    if (((j > 0) && (j <= longueur_mois(m,a)) && ((m > 0) && (m < 13))))
    return 1;
    else
    return 0;
}


int verifier_date(int jour , int mois , int annee )
{
    time_t my_time;
    struct tm * timeinfo;
    time (&my_time);
    timeinfo = localtime (&my_time);


    if (est_valide(jour, mois , annee))
    {



        if (annee >(timeinfo->tm_year+1900)  ) return 0 ;
        else
        {
            if (annee == (timeinfo->tm_year+1900) )
            {
                if ( mois > (timeinfo->tm_mon+1)) return 0 ;
                else
                {
                    if ( mois == (timeinfo->tm_mon+1))
                    {
                        if ( jour > timeinfo->tm_mday) return 0 ;
                            else
                        {
                            return 1 ;
                        }





                    } else return 1 ;
                }

            } else return 1 ;

        }
    }
    return 0 ;
}


