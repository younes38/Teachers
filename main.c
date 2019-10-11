#include <stdio.h>
#include <stdlib.h>
#include "tplib.h"
//here
void rech_dech(int matricule ,int  *trouv ,int *i ,int *j,int *pos) // faire un recherhe dichotomie
{

    TObF *f ;
    ouvrir(&f,fichier_index , 'a') ;
    //Tbloc_i buff ;
    lireDir_i(f,1,&buff) ;
    int inf , sup ;
    inf = 0 ;
    sup = buff.Nb -1;
    int mid ;

    *trouv = 0 ;
    if (buff.tab[buff.Nb-1].matricule < matricule ) // bien fait
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
    fermer(f) ;


}
int supp_ens (int matricule ) // matricule : a supprimer
{

   // printf(" Debut \n");

    int trouv , i,  j,pos=0 ;
    rech_dech(matricule , &trouv , &i , &j,&pos) ;
    if (! trouv)
    {
            //printf(" Fin \n");

        return 0 ;

    }
    else
    {
            // suppression du fichier de TP

        TObF *f ;
        Tbloc buff1 ;
        Tbloc buff2 ;
        int dernier_mat ;
        ouvrir(&f,fichier_tp,'a') ;
        int n = entete(f,1) ;
        int change =  1 ;
        if (n != i)
        {
            lireDir(f,i,&buff1) ;
            lireDir(f,n,&buff2) ;
            //buff1.tab[j] = buff2.tab[buff2.Nb -1] ;
            buff1.tab[j].date_naissance = buff2.tab[buff2.Nb -1].date_naissance ;
            buff1.tab[j].date_rec = buff2.tab[buff2.Nb -1].date_rec;
            buff1.tab[j].der_diplome = buff2.tab[buff2.Nb -1].der_diplome;
            buff1.tab[j].grade = buff2.tab[buff2.Nb -1].grade;
            buff1.tab[j]. Grp_Sang = buff2.tab[buff2.Nb -1].Grp_Sang;
            buff1.tab[j]. matricule = buff2.tab[buff2.Nb -1].matricule;
            strcpy(buff1.tab[j]. nom , buff2.tab[buff2.Nb -1].nom );
            strcpy( buff1.tab[j]. prenom , buff2.tab[buff2.Nb -1].prenom ) ;
            buff1.tab[j]. sexe = buff2.tab[buff2.Nb -1].sexe;
            buff1.tab[j]. specialite = buff2.tab[buff2.Nb -1].specialite;
            buff1.tab[j]. univ = buff2.tab[buff2.Nb -1].univ;
            buff1.tab[j]. wilaya_naissance = buff2.tab[buff2.Nb -1].wilaya_naissance;






            dernier_mat = buff2.tab[buff2.Nb -1].matricule ;

            buff2.Nb -- ;
            ecrireDir(f,i,&buff1) ;
            if (buff2.Nb >0)
            {
                ecrireDir(f,n,&buff2) ;
            }
            else
            {
                aff_entete(f,1,n-1) ;

            }

        }
        else
        {
            lireDir(f,n,&buff2) ;
            //buff2.tab[j] = buff2.tab[buff2.Nb -1] ;
            buff2.tab[j].date_naissance = buff2.tab[buff2.Nb -1].date_naissance ;
            buff2.tab[j].date_rec = buff2.tab[buff2.Nb -1].date_rec;
            buff2.tab[j].der_diplome = buff2.tab[buff2.Nb -1].der_diplome;
            buff2.tab[j].grade = buff2.tab[buff2.Nb -1].grade;
            buff2.tab[j]. Grp_Sang = buff2.tab[buff2.Nb -1].Grp_Sang;
            buff2.tab[j]. matricule = buff2.tab[buff2.Nb -1].matricule;
            strcpy(buff2.tab[j]. nom , buff2.tab[buff2.Nb -1].nom );
            strcpy( buff2.tab[j]. prenom , buff2.tab[buff2.Nb -1].prenom ) ;
            buff2.tab[j]. sexe = buff2.tab[buff2.Nb -1].sexe;
            buff2.tab[j]. specialite = buff2.tab[buff2.Nb -1].specialite;
            buff2.tab[j]. univ = buff2.tab[buff2.Nb -1].univ;
            buff2.tab[j]. wilaya_naissance = buff2.tab[buff2.Nb -1].wilaya_naissance;



            dernier_mat = buff2.tab[buff2.Nb -1].matricule ;


            buff2.Nb -- ;

            if (buff2.Nb >0)
            {
                ecrireDir(f,n,&buff2) ;
            }
            else
            {
                change = 0 ; // l'element a supprimer c"est le dernier
                aff_entete(f,1,n-1) ;

            }
        }

        fermer(f) ;

        // suppression de l'indexe
    f = NULL ;
    int position ;
    rech_dech(dernier_mat , &trouv , &i,&j, &position) ;
    ouvrir(&f,fichier_index , 'a') ;

    Tbloc_i buff ;

    lireDir_i(f,1,&buff) ;

    buff.tab[position].nb_bloc = buff.tab[pos].nb_bloc ;
    buff.tab[position].deplacement = buff.tab[pos].deplacement ;
    buff.Nb -- ;
    for (i=pos ; i < buff.Nb ; i++  )
    {
        buff.tab[i] = buff.tab[i+1] ;

    }
    if (buff.Nb == 0)
        aff_entete(f,1,0) ;
    else
        ecrireDir_i(f,1,&buff) ;

    fermer(f) ;
        //printf(" Fin \n");

        return 1 ;
    }

}


void supp_spe(int specialitee)
{
    int cpt =0 ;
    TObF *f_i = NULL , *f = NULL;
    Tbloc_i buff_i ;
    Tbloc buff1 ;

  //  ouvrir(&f_i,fichier_index,'a') ;
   // lireDir_i(f_i,1,&buff_i) ;
    ouvrir(&f , fichier_tp , 'a');
    int i=0,j=0;
    int ent = entete(f,1) ;
    for (i=1;i<= ent ;i++) {

        lireDir(f,i,&buff1) ;

        for (j=0;j<buff1.Nb;j++)
        {

            while (buff1.tab[j].specialite==specialitee)
            {


                supp_ens(buff1.tab[j].matricule) ;


                ouvrir(&f , fichier_tp , 'a');
                lireDir(f,i,&buff1) ;

                if (buff1.Nb <= j ) break ;

                }

            }
        }
          fermer(f) ;
}

int modify_univ (int matricule , int new_univ ) // matricule : a changer ; new_univ : the new university
{
    int trouv , i,  j,pos=0 ;
    rech_dech(matricule , &trouv , &i , &j,&pos) ;
    if (! trouv)
    {
        return 0 ;
    }
    else
    {
        TObF *f ;
        Tbloc buff ;

        ouvrir(&f,fichier_tp,'a') ;
        lireDir(f,i,&buff) ;
        buff.tab[j].univ= new_univ  ;

        ecrireDir(f,i,&buff) ;
        fermer(f) ;
        return 1 ;
    }

}

int ajouter_ens ( enreg ens  )
{

    int trouv , i,  j,pos=0 ;
    rech_dech(ens.matricule , &trouv , &i , &j,&pos) ;
    if ( !trouv)
    {
        // l'insertion dans le fichier du TP
        TObF *file ;
        ouvrir( &file , fichier_tp , 'a' ) ;
        Tbloc buf ;
        int n = entete(file,1) ;
        if (n !=0) // le fichier n'est pas vide
        {
            lireDir(file , n , &buf) ; // lire le dernier bloc

        }
        else
        {
            n = 1;
            aff_entete(file , 1,1) ;
            buf.Nb  =0 ;
        }
        int bloc ;
        int dep;
        if ( (buf.Nb) < 1000)
        {
            buf.Nb ++ ;
            buf.tab[buf.Nb-1] = ens ;

            bloc = n ;
            dep = buf.Nb-1 ;
            ecrireDir(file , n , &buf) ;

        }
        else
        {
            buf.Nb = 1 ;
            buf.tab[0] = ens ;

            bloc = n+1 ;
            dep = buf.Nb-1 ;


            ecrireDir(file ,  n+1 , &buf) ;
            aff_entete(file , 1 , n+1) ;

        }
        fermer(file) ;

        // l'insertion dans le fichier index

        TObF *f ;
        ouvrir(&f,fichier_index , 'a') ;

        Tbloc_i buf0 ;
        int m = entete(f,1) ;
        if (m !=0) // le bloc n'est pas vide
        {
            lireDir_i(f,1,&buf0) ;
            int i  ;

            for (i = buf0.Nb ; i >pos ; i--) // faire des decalages
            {
                buf0.tab[i] = buf0.tab[i-1] ;

            }
            buf0.Nb ++ ;


            buf0.tab[pos].matricule = ens.matricule ;
            buf0.tab[pos].nb_bloc = bloc ;
            buf0.tab[pos].deplacement = dep ;
        }
        else
        {
            m =1 ;
            aff_entete(f,1,1) ;
            buf0.Nb = 0 ;
            buf0.Nb ++ ;
            buf0.tab[pos].matricule = ens.matricule ;
            buf0.tab[pos].nb_bloc = bloc ;
            buf0.tab[pos].deplacement = dep ;
        }

        ecrireDir_i(f,1,&buf0) ;
        fermer(f);

        return 1 ;
    }
    return 0 ;

}


int main()
{
    printf("Bonjour a tous !!") ;
    system("pause") ;

    strcpy( menuu[0].element , "Ajouter un nouvel enseignant") ;
    strcpy( menuu[1].element , "Modifier l'etablissement d'un enseignant") ;
    strcpy( menuu[2].element  ,"Supprimer un enseignant") ;
    strcpy( menuu[3].element , "Supprimer une specialite") ;
    strcpy(menuu[4].element , "Afficher les enseignant selon l'anciennte et l'etablissement" ) ;
    strcpy( menuu[5].element , "Consulter les enseignant selon la region") ;
    strcpy(menuu[6].element , "Afficher l'entete de fichier " );
    strcpy(menuu[7].element , "Sortir" );

    int Nb_e ;
    system("mode con LINES=40 COLS=111");
    debut() ;
    gotoxy(22,23) ;
    color(12,7) ;
    printf("    Veuillez introduire le nombre d'enregistrements a remplire");
    color(4,7);
    gotoxy(49,25) ;
    scanf("%d",&Nb_e) ;
    int cpt=0 ;
    char ligne[40] ;
    char ligne2[256] ;
    FILE *names=NULL ;
    names=fopen("wilaya.txt","r") ;

    while ( fgets(ligne,sizeof(ligne),names) != NULL) {
        ligne[strlen(ligne)-1] ='\0' ;
        strcpy(tab_wly[cpt].nom_wilaya,ligne) ;
        cpt++ ;
    }
    fclose(names) ;
    cpt=0 ;
    names=fopen("etab.txt","r") ;
    while ( fgets(ligne2,sizeof(ligne2),names) != NULL) {
        ligne2[strlen(ligne2)-1] ='\0' ;
        strcpy(tab_etab[cpt].nom_etab,ligne2) ;
        cpt++ ;
    }
    fclose(names);
    cpt=0 ;
    names=fopen("specialites.txt","r") ;
    while ( fgets(ligne2,sizeof(ligne2),names) != NULL) {
        ligne2[strlen(ligne2)-1] ='\0' ;
        strcpy(tab_spe[cpt].nom_spec,ligne2) ;
        cpt++ ;
    }
    fclose(names) ;


    int t,j,v ,k,i,u,fq;
    TObF *q ,*p ;
    Tbloc qf ;
    char on[14] ;
    Tbloc_i pf ;

    chargement_initial(Nb_e) ;
        ouvrir(&q,fichier_tp,'a') ;

    //Chargement affichage //
    color(4,7) ;
gotoxy(47,27) ;
printf("chargement") ;
k=1 ;
for (i=70-35;i<108-35;i++)
{
	gotoxy(i,29) ;
	color(1,1) ;
	printf("-") ;
	if((i>85-35)&&(i<98-35)) delay(70) ;
	else
	{
		delay(35) ;
	}
	gotoxy(96-45,31);
	if (i==106-35) k=98 ;
	if (i==107-35) k=100;
	color(0,7) ;
	printf("(%d %c)",k,37);
	k=k+3 ;
}
gotoxy(35,33) ;
    printf("Le chargement inital est bien fait ... \n") ;
getch() ; system("cls") ;
int choix ;
char matrr[50] ;
char vv[30] , uu [30],fqq[30];
int cnd ;
int matriculee ;
int trouve , ii , jj , poos ;
int supprimer ;
int repete ;
char new_etab[100];
int new_etab_nb ;
enreg new_ens ;
char  teacher_matr[20] ,nom_teacher[50] ,prenom_teacher[50] , yr_birth[10] , day_birth[10],month_birth[10], rec_yr[30],rec_day[10],rec_month[10], grade_teacher[30], birth_wly[10], gender[10],blood[10], spc_teacher[40],last_dip[30],uni_etb[10];
int aaa,aa,bb,cc1,cc2,cc3,dd,eee , cnd_aj;




    men:
    choix = menu() ;


    if (choix == 0 )
    {
        system("cls") ;
        Le_mtrc:
        gotoxy (4,1);
        printf("                                         ") ;
        gotoxy (4,1);
        printf("Le matricule : ");
        scanf("%s",&teacher_matr) ;
        aaa=verifier_nombre(teacher_matr) ;
        if ((aaa==-1) ou (aaa>999999)) goto Le_mtrc;
        new_ens.matricule=aaa;

        Le_nm:
        gotoxy(4,4) ;
        printf("                                                        ") ;
        gotoxy(4,4) ;
        printf("Le Nom : ") ;
        scanf("%s",&nom_teacher) ;
        aa=verifier_mot(nom_teacher) ;
        if(aa==0) goto Le_nm ;
        strcpy(new_ens.nom,nom_teacher) ;

        Le_pnm:
        gotoxy(4,7) ;
        printf("                                                     ") ;
        gotoxy(4,7) ;
        printf("Le prenom : ") ;
        scanf("%s",&prenom_teacher) ;
        bb=verifier_mot(prenom_teacher) ;
        if(bb==0) goto Le_pnm ;
        strcpy(new_ens.prenom,prenom_teacher) ;

        La_dte:
        gotoxy(4,10) ;
        printf("                                                              ") ;
        gotoxy(4,10) ;
        printf("La date de naissance : ") ;
        scanf("%s %s %s",&day_birth,&month_birth,&yr_birth) ;
        cc1 = verifier_nombre(day_birth) ;
        cc2 = verifier_nombre(month_birth) ;
        cc3 = verifier_nombre(yr_birth) ;
        if ((cc1==-1) ou(cc2==-1) ou (cc3==-1)) goto La_dte;
        if (verifier_date(cc1,cc2,cc3)==0) goto La_dte;
        new_ens.date_naissance.jj=cc1 ;
        new_ens.date_naissance.mm=cc2 ;
        new_ens.date_naissance.aa=cc3 ;
        gotoxy(1,12) ;
        afficher_wilaya();

        wly:
        gotoxy(4,30) ;
        printf("                                                                 ") ;
        gotoxy(4,30) ;
        printf("La wilaya de naissance : ") ;
        scanf("%s",&birth_wly) ;
        dd=verifier_nombre(birth_wly);
        if ((dd==-1) ou (dd<1) ou (dd>48)) goto wly ;
        new_ens.wilaya_naissance=dd;

        sx:
        gotoxy(4,32) ;
        printf("                                                                      ") ;
        gotoxy(4,32) ;
        printf("Le sexe (femme=0 / Homme=1) : ") ;
        scanf("%s",&gender) ;
        eee=verifier_nombre(gender) ;
        if ((eee==-1) ou (eee>1)) goto sx;
        new_ens.sexe=eee ;

        new_ens.date_rec=generate_date(1979,2018) ;
        new_ens.grade = random(6)+1 ;
        new_ens.univ = random(106)+1 ;
        new_ens.specialite = random(30)+1 ;
        new_ens.der_diplome = random(5)+1 ;
        new_ens.Grp_Sang = random(8)+1 ;
        cnd_aj = ajouter_ens(new_ens) ;
            if (cnd_aj==1) {
                                ok_msg("Enseignant ajoutee") ;
                                system("cls") ; goto men;
                            }
            else {
                ok_msg("Ce matricule existe deja") ;
                system("cls") ; goto men ;
            }

    }



    if (choix == 1)
    {


        do
        {

        system("cls") ;
        cadre(0,0,37,109,0,7,0) ;
        gotoxy(10 , 5) ;
        printf("Enter le matricule :") ;
        gotoxy(10  + strlen ("Enter le matricule : ") ,5 ) ;

        matriculee = 0;
        scanf("%s" , &matrr) ;
        matriculee =verifier_nombre(matrr)  ;

        if ( matriculee != -1 ) // vrai
        {
            rech_dech(matriculee , &trouve , &ii , &jj , &poos) ;
            if (trouve)

            {
               // prinf()
               gotoxy(20,20) ;
               printf("La liste des etablissement va etre afficher ...") ;
               delay(3000);
               system("cls") ;
                afficher_etab() ;
                y_lire:
                system("cls") ;
                cadre(0,0,37,109,0,7,0) ;
                gotoxy(10 , 5) ;
                printf ("Entrer la nouvelle etablissement : ") ;
                scanf("%s" , &new_etab) ;
                new_etab_nb =verifier_nombre(new_etab) ;
                if (new_etab_nb==-1)
                {
                    gotoxy(10 + strlen("Entrer la nouvelle etablissement : "),5) ;
                    printf ("                                                    ");
                    goto y_lire ;
                }
                else
                {
                    if ((new_etab_nb <=106) et (new_etab_nb >= 1))
                    {
                        modify_univ(matriculee , new_etab_nb) ;
                        ok_msg("La modification est bien faite") ;
                        goto men ;
                    }
                    else
                    {
                        ok_msg("Le matricule doit etre compris entre 1 et 106") ;
                        goto y_lire ;

                    }
                }





            }else
            {
                repete = ok_msg("Le matricule n'existe pas! (OK pour le MENU)") ;
                if (repete !=  esc)
                {
                    goto men ;
                }
            }

        } else
        {
            gotoxy(10  + strlen ("Enter le matricule :") ,5 ) ;
            printf("                               ") ;

        }

        } while (1) ;


    }


    if (choix == 2)
    {


        do
        {

        system("cls") ;
        cadre(0,0,37,109,0,7,0) ;
        gotoxy(10 , 5) ;
        printf("Enter le matricule :") ;
        gotoxy(10  + strlen ("Enter le matricule : ") ,5 ) ;

        matriculee = 0;
        scanf("%s" , &matrr) ;
        matriculee =verifier_nombre(matrr)  ;

        if ( matriculee != -1 ) // vrai
        {
            rech_dech(matriculee , &trouve , &ii , &jj , &poos) ;
            if (trouve)
            {
                supprimer = ok_msg("Attention ! L'enseignant va etre supprime") ;
                if (supprimer == esc) goto men ;
                else
                {
                    supp_ens(matriculee) ;
                    ok_msg("La suppression est bien faite")  ;
                    goto men ;
                }


            }else
            {
                repete = ok_msg("Le matricule n'existe pas! (OK pour le MENU)") ;
                if (repete !=  esc)
                {
                    goto men ;
                }
            }

        } else
        {
            gotoxy(10  + strlen ("Enter le matricule :") ,5 ) ;
            printf("                               ") ;

        }

        } while (1) ;


    }


int cppt ;

     if (choix == 3)
    {


        do
        {

        system("cls") ;
        cadre(0,0,37,109,0,7,0) ;
        gotoxy(30,3) ;
        printf( "La liste des specialites : " ) ;
        for( cppt = 0 ; cppt < 30 ; cppt ++ )
        {
            gotoxy(5,5+cppt) ;
            printf ("%d - %s",cppt+1,tab_spe[cppt].nom_spec  ) ;

        }
        fin
        getch() ;
        system("cls") ;
        cadre(0,0,37,109,0,7,0) ;
        gotoxy(10 , 5) ;



        printf("Enter la specialite : ") ;


        gotoxy(10  + strlen ("Enter la specialite : ") ,5 ) ;

        matriculee = 0;
        scanf("%s" , &matrr) ;
        matriculee =verifier_nombre(matrr)  ;

        if ( matriculee != -1 ) // vrai
        {

            if ((matriculee<=30) et (matriculee>=1) ) trouve = 1 ;
                else trouve = 0 ;
            if (trouve)
            {
                supprimer = ok_msg("Attention ! La specialite va etre supprimee") ;
                if (supprimer == esc) goto men ;
                else
                {
                    gotoxy(28,20) ;
                    color(4,7) ;
                    printf("La suppression est en cours , Veuillez patientez ! ") ;

                    supp_spe(matriculee) ;
                    ok_msg("La suppression est bien faite")  ;
                    goto men ;
                }


            }else
            {
                repete = ok_msg("invalide specialite (OK pour le MENU)") ;
                if (repete !=  esc)
                {
                    goto men ;
                }
            }

        } else
        {
            repete = ok_msg("invalide specialite (OK pour le MENU)") ;
                if (repete !=  esc)
                {
                    goto men ;
                }

        }

        } while (1) ;


    }




if (choix == 4)
    {
        cnd=1 ;
        while (cnd){ // il faut que la deuxieme valeur entre soit superieur a la premiere
         lo:
         system("cls") ;
         gotoxy(10,5) ;
         printf("Entrer l'intervalle de l'anciennte :  ") ;
         scanf("%s %s",&vv,&uu) ;
         v=verifier_nombre(vv) ;
         u=verifier_nombre(uu) ;
         if ((v==-1) ou(u==-1)) goto lo ;

         if (v<=u) cnd = 0 ;
        }

        rr:
        strcat(on, "") ;
         gotoxy(10,7) ;
         printf("                                                                                            ") ;
         gotoxy(10,7) ;
         printf("Visualiser la liste des codes etablissements (oui/non) : ") ;
         scanf("%s",on) ;

         if (strcmp(on,"oui")==0) {
            system("cls") ;
            afficher_etab() ; getch();

            tttt:
            system("cls") ;
            gotoxy(10,9) ;
            printf("Entrer Le numero de l'etablissement  ") ;
            scanf("%s",&fqq) ;
            fq=verifier_nombre(fqq) ;
            if (fq==-1) goto tttt;
         }
         else {
                if (strcmp(on,"non")==0) {
                    rtr:
                    gotoxy(10,9) ;
                    printf("                                                                                  ");
                    gotoxy(10,9) ;
                    printf("Entrer Le numero de l'etablissement  ") ;
                    scanf("%s",&fqq) ;
                    fq=verifier_nombre(fqq) ;
                    if (fq==-1) goto rtr;
                }

                else{
                    goto rr ;
                }
         }
         system("cls") ;
    affichage(v,u,fq);
    goto men ;
    }

    if (choix == 5) { // afichage selon la region
         tyt:
         system("cls") ;
         gotoxy(10,5) ;
         printf("Veuillez Introduire la region a visualiser (1 ouest)/(2 centre)/(3 est) : ");
         scanf("%s",&vv) ;
         v=verifier_nombre(vv) ;

         if ((v<=3) && (v>=1) )
         {
             system("cls") ;
             affich_region(v) ;
         }
         else goto tyt;
         goto men ;
    }


if (choix == 6) {
            system("cls") ;
            cadre(0,0,38,108,0,7,0) ;
            gotoxy(37,9) ;
            ecrire("L' e n t e t e   d u   f i c h i e r  ",30) ;
            gotoxy(37,10) ;
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196);
            gotoxy(26,18) ;

            printf("Le Nombre de Bloc du fichier ENSEIGNANT_MESRS.bin est  : %d ",entete(q,1)) ;



            getch() ;

        goto men;
        }


    fermer(q) ;
    return 0;
}
