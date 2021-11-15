/*
                           **************
                           ** BREAK-IT **
                           ************** 
Je veux tout d'abord remercier 'gorgonzola', pour son code source qui 
m'a (beaucoup) aid�, car j'avais des petits probl�mes avec les collisions
de la raquette, et du d�placement de cette derni�re avec le clavier . 
Je veux aussi remercier 'Berenger', pour son code source qui m'a aid� pour 
l'affichage des scores. (Son code source est la foncion de s�paration des termes),
ainsi que pour le placement des objets (au d�part, je placais les objets au 
hasard, puis j'ai eu l'id�e d'utiliser ce code source pour le placement des objets).
Je remercie aussi les testeurs qui m'ont apport� des id�es que j'ai mis
en pratiques, et les bugs que j'ai corrig�s.
Bref, j'esp�re que vous n'aurez pas de mal � comprendre cette source.
                         ---------------
                         -- N�o's prog -
                         ---------------  juin 2004
*/

#include <stdio.h>
#include <conio.c>
#include <string.h>
#include <ctype.h> /* pour la fonction toupper */

/* assignation des touches � des variables
le num�ro est le code ASCII du caract�re press� */
#define    GAUCHE      75
#define    DROITE      77
#define    ENTER       13
#define    ESCAPE      27
#define    SORTIE       0
#define    NORMAL       1
#define    MENU         2
#define    VERT        10
#define    ROUGE       12
#define    JAUNE       14
#define    BLANC       15
#define    SPACE       32
#define    YES         79
#define    CHEAT_F1    59
#define    CHEAT_F2    60
#define    CHEAT_F3    61
#define    CHEAT_F4    62
#define    SOUND       63

/* d�claration de structure : on d�fini nous meme les types*/
typedef struct
{
  int X;
  int Y;
  int A;
  int B;
} POS;

typedef struct
{
    int X;
    int Y;
} BLOC;

/* d�claration des variables globales : utilisable par toutes les fonctions et proc�dures */
BLOC  obj[100];
POS   balle;
int   i, divers, joueur, direction, objet, nbBall,score,vitesse,nivo,choix, chson, objTot;
int   action=MENU;
char  keyP;

/* fonction de s�paration des termes d'une variable texte */
char* sep_term(char *texte, const char *strDelimit, int indexe)
{
    int tempc=0;
    char *resultat="";
    
    resultat=strtok(texte, strDelimit);
    while(tempc!=indexe)
    {
        resultat=strtok(NULL, strDelimit);
        tempc++;
    }
    return resultat;
}

/* fonction qui ne renvoie rien : proc�dure */
void affichscore()
{
    char *fscr="bstscr.neo"; /* d�fini le pointeur vers le fichier � utiliser */
    FILE *fichier=fopen(fscr,"r"); /* ouvre le fichier en mode lecture [(r)ead] */
    char ligne[30];
    int score1, score2, score3;
    char nom1[30], nom2[30], nom3[30], player[15] ;
    char c_score1[10], c_score2[10], c_score3[10];
    
    if(fichier== NULL) /* si il ne trouve pas le fichier : r�sultant de l'op�ration fopen */
    {
        fichier=fopen(fscr,"w"); /* ouvre le fichier en mode �criture [(w)rite] 
        il efface le fichier si il existe et en cr�e un nouveau du meme nom */
        fputs("vide,0\n",fichier); /* ins�re les donn�es dans le fichier */
        fputs("vide,0\n",fichier);
        fputs("vide,0\n",fichier);
        fclose(fichier); /* ferme le fichier ouvert : tr�s important et souvent oubli� */
    }
 /* lecture de la premiere ligne */
    fgets (ligne, sizeof ligne, fichier); /* r�cup�re la premi�re ligne du fichier
                                            et la stocke dans le tableau ligne */
    strcpy(nom1,ligne); /* copie le contenu du tableau ligne dans le tableau nom1 */
 /* lecture de la deuxi�me ligne */
    fgets (ligne, sizeof ligne, fichier);
    strcpy(nom2,ligne);
 /* lecture de la troisi�me ligne */
    fgets (ligne, sizeof ligne, fichier);
    strcpy(nom3,ligne);
        
    score1 = atoi(sep_term(nom1, "," , 1)); /* la fonction atoi converti une variable texte en entier */
    score2 = atoi(sep_term(nom2, "," , 1));
    score3 = atoi(sep_term(nom3, "," , 1));
        
    strcpy(nom1, sep_term(nom1, "," , 0));
    strcpy(nom2, sep_term(nom2, "," , 0));
    strcpy(nom3, sep_term(nom3, "," , 0));
        
    if(score > score3)
    {
       clrscr(); /* clrscr() efface l'�cran : clear screen */
       if (score > score1)
       {
           printf("Vous remportez la premi%cre place\n", 138); /* %c, 138 permet d'afficher
           le caract�re dont le code ASCII est 138, il s'agit du '�'. */
           score3 = score2;
           score2 = score1;
           score1 = score;
           strcpy(nom3, nom2);
           strcpy(nom2, nom1);
           printf("Quel est votre pr%cnom : ",130); /* %c, 130 permet d'afficher le caract�re 
                                                 dont le code ASCII est 130, il s'agit du '�' */
           scanf("%s",&nom1);
       }
       else if (score > score2)
       {
           printf("Vous remportez la deuxi\x8Ame place\n"); /* 8A est la valeur 
           hexad�cimale du caract�re '�'. Le \x indique qu'on �crit en hexad�cimal. 
           En d�cimal 8A = 138, le code ASCII du caract�re '�' */
           score3 = score2;
           score2 = score;
           strcpy(nom3, nom2);
           printf("Quel est votre pr%cnom : ",130);
           scanf("%s",&nom2);
       }
       else
       {
           printf("Vous remportez la troisi\x8Ame place\n");
           score3 = score;
           printf("Quel est votre pr%cnom : ",130);
           scanf("%s",&nom3);
       }
    }
    clrscr();
    textcolor(ROUGE); /* fonction qui permet de changer la couleur du texte affich� 
    il ne faut pas oubli� que j'ai d�clar� ROUGE au d�but du prog, donc il faut 
    penser � d�clarer les couleurs que vous voulez utiliser */
    gotoxy(10,8); /* le gotoxy permet de placer le curseur � un endroit precis de l'�cran 
    et d'y inscrire ce qu'on d�sire : gotoxy(x,y), avec x pour les absisses, et y pour les ordonn�es*/
    printf("**** HI-SCORE ** MEILLEUR SCORE ****");
    textcolor(VERT);        
    gotoxy(5,12);
    printf("1 : %s avec %i points (%i briques cass%ces)",nom1, score1,(score1/10),130);
    gotoxy(5,14);
    printf("2 : %s avec %i points (%i briques cass%ces)",nom2, score2,(score2/10),130);
    gotoxy(5,16);
    printf("3 : %s avec %i points (%i briques cass%ces)",nom3, score3,(score3/10),130);       
    strcat(nom1,","); /* fonction de concat�nation de chaine de caract�res */
    itoa(score1,c_score1,10); /* la fonction itoa est l'inverse de la fonction atoi : elle convertie 
    les entier en chaine de caract�res. On peut remplacer par : sprintf(c_score1,"%d",score1); */
    strcat(nom1,c_score1);
        
    strcat(nom2,",");
    itoa(score2,c_score2,10); 
    strcat(nom2,c_score2);
        
    strcat(nom3,",");
    itoa(score3,c_score3,10);
    strcat(nom3,c_score3);
                
    fclose(fichier);
        
    fichier=fopen(fscr,"w");
    fputs(strcat(nom1,"\n"),fichier);
    fputs(strcat(nom2,"\n"),fichier);
    fputs(nom3,fichier);
    fclose(fichier);
}

void enregistrcfg()
{
    FILE *config = fopen("config.cfg","w");
    char tmp[10];
    char son[1];
    
    fputs("[SOUND]\n",config);
    fputs("son=",config);
    itoa(chson, son, 10);
    fputs(son,config);
    fclose(config);
}

void lirecfg()
{
    FILE *config = fopen("config.cfg","r");
    char ligne[10];
    char tmp[10];
    
    if(config!=NULL)
    {
        fgets(ligne,sizeof ligne, config);
        fgets(ligne,sizeof ligne, config);
        strcpy(tmp, ligne);
        chson=atoi(sep_term(tmp, "=" , 1));
        fclose(config);
    }
}

void placeObj()
{
    char *fpos;
    char ligne[20], valeur[5];
    int X, Y;
    
    switch(nivo) /* structure de possibilit�es : SELON CAS ...
    c'est moins lourd � utiliser qu'une multitude de 
    if(...){...}else if(...){...}else if(...){...} ... */
    {
        case 1: 
                fpos="plcob1.neo"; 
                break; /* break permet de sortir de la structure */
        case 2: 
                fpos="plcob2.neo"; 
                break;
        case 3: 
                fpos="plcob3.neo"; 
                break;
        case 4: 
                fpos="plcob4.neo";
                break;
        case 5: 
                fpos="plcob5.neo";
                break;
        case 6: 
                fpos="plcob6.neo";
                break;
        case 7: 
                fpos="plcob7.neo";
                break;
        case 8: 
                fpos="plcob8.neo";
                break;
        case 9: 
                fpos="plcob9.neo";
                break;
        case 10:
                fpos="plcob10.neo";
                break;
        case 11: 
                fpos="plcob11.neo";
                break;
        case 12: 
                fpos="plcob12.neo";
                break;
        case 13: 
                fpos="plcob13.neo";
                break;
        default: 
                fpos="plcob.neo"; 
                break;
    }
    
    FILE *fichier=fopen(fpos,"r");
    
    srand(time(NULL)); /* initialisation de la fonction rand par rapport au temps */
    textcolor(JAUNE);
    
    if(fichier!=NULL)
    {
        //for(i=0;i<=19;i++)
        i=0;
        while(!feof(fichier))
        {
           fgets (ligne, sizeof ligne, fichier);
           strcpy(valeur,ligne);
           Y = atoi(sep_term(valeur, "," , 1));
           X = atoi(sep_term(valeur, "," , 0));
           obj[i].Y=Y;
           obj[i].X=X;
           gotoxy(obj[i].X, obj[i].Y);
           printf("\xDB\xDB\xDB\xDB");
           i+=1;        
        }  
        fclose(fichier);
    }
    else
    {        
        for(i=0; i<=19;i++)
        {
        /* rand() g�n�re un nombre al�atoire entre 0 et 1 */
           obj[i].X=(rand() % 70)+5; /* ici, il g�n�re un nombre entier entre 0 et 70, et il ajoute 5 */
           obj[i].Y=(rand() % 12)+3;
           gotoxy(obj[i].X, obj[i].Y);
           printf("\xDB\xDB\xDB\xDB");
        }
    }
    objet=i;
    objTot=objet;
}

void execution()
{ 
  /* DESSINE LA BALLE */
    gotoxy(balle.X,balle.Y);
    textcolor(VERT);
    printf("\x0F");
  /* EFFACE L'ANCIENNE POSITION DE LA BALLE */
    gotoxy(balle.A,balle.B);
    printf(" ");
    balle.A=balle.X;
    balle.B=balle.Y;
    
 /* SI LA BALLE TOUCHE L'OBJET A DETRUIRE */
    for(i=0;i<=objTot;i++)
    {
        if((balle.Y==obj[i].Y)&&((balle.X==obj[i].X)||(balle.X==obj[i].X+1)||(balle.X==obj[i].X+2)||(balle.X==obj[i].X+3)||(balle.X==obj[i].X+4)))
        {         
          switch(direction)
          {
            case 1:
                        direction=2;
                        divers=4;
                        break;
            case 2:
                        direction=1;
                        divers=4;
                        break;
            case 3:
                        direction=4;
                        divers=4;
                        break;
            case 4:
                        direction=3;
                        divers=4;
                        break;
            case 5:
                        direction=8;
                        divers=0;
                        break;
            case 6:
                        direction=7;
                        divers=0;
                        break;
            case 7:
                        direction=6;
                        divers=0;
                        break;
            case 8:
                        direction=5;
                        divers=0;
                        break;
            case 9:
                        direction=12;
                        divers=0;
                        break;
            case 10:
                        direction=11;
                        divers=0;
                        break;
            case 11:
                        direction=10;
                        divers=0;
                        break;
            case 12:
                        direction=9;
                        divers=0;
                        break;
          }
          objet-=1; /* �quivaut � objet = objet - 1 ; */
          score+=10; /* �quivaut � score = score + 10 ; */
          gotoxy(obj[i].X, obj[i].Y);
          obj[i].X=1;
          obj[i].Y=25;
          printf("    ");
        }
    }
    
 /* SI LA BALLE TOUCHE LE MUR GAUCHE (X=80) OU DROIT (X=1) */
    if ((balle.X==80)||(balle.X==1)) /* le || signifie "OU" */
    {
      switch (direction)
      {
        case 1:  direction=4;
                 divers=4;
                 break;
        case 2:  direction=3;
                 divers=4;
                 break;
        case 3:  direction=2;
                 divers=4;
                 break;
        case 4:  direction=1;
                 divers=4;
                 break;
        case 5:  direction=12;
                 divers=0;
                 break;
        case 6:  direction=11;
                 divers=0;
                 break;
        case 7:  direction=10;
                 divers=0;
                 break;
        case 8:  direction=9;
                 divers=0;
                 break;
        case 9:  direction=8;
                 divers=0;
                 break;
        case 10: direction=7;
                 divers=0;
                 break;
        case 11: direction=6;
                 divers=0;
                 break;
        case 12: direction=5;
                 divers=0;
                 break;
      }
    }
 /* SI LA BALLE TOUCHE LE MUR HAUT */
    if (balle.Y==1)
    {
      switch(direction)
      {
            case 1:
                        direction=2;
                        divers=4;
                        break;
            case 4:
                        direction=3;
                        divers=4;
                        break;
            case 5:
                        direction=8;
                        divers=0;
                        break;
            case 6:
                        direction=7;
                        divers=0;
                        break;
            case 11:
                        direction=10;
                        divers=0;
                        break;
            case 12:
                        direction=9;
                        divers=0;
                        break;
      }
    }
 /* SI LA BALLE TOUCHE LE MUR BAS */
    if (balle.Y==23)
    {
      nbBall-=1;
      if(chson==0) printf("\a"); /* Ce printf n'affiche pas de texte, mais �met un son (bell alert) */
      direction=4;
      balle.X=40;
      balle.Y=22;
      joueur=37;
      gotoxy(1,25);
      printf("Touche \x22 ESPACE \x22 pour lancer la balle"); 
      keyP=getch(); /* getch() permet de r�cup�rer le caract�re entr�e par l'utilisateur */
      while(keyP!=SPACE) /* SPACE est une variable d�finie au d�but du programme
      elle equivaut au code ASCII 32, correspondant � la touche "espace" */
      {
            keyP=getch();
      }
      gotoxy(1,25);
      printf("                                       ");
      dessineCadre(); /* appel d'une proc�dure */
    }
 /* SI LA BALLE TOUCHE LA RAQUETTE */
    if ((balle.Y==22)&&((balle.X==joueur)||(balle.X==joueur+1)||(balle.X==joueur+6)||(balle.X==joueur+7)))
    /* le && signifie "ET" */
    {
      switch (direction)
      {
        case 2:
        case 7:  direction=5;
                 divers=0;
                 break;
        case 8:  direction=6;
                 divers=0;
                 break;
        case 3:
        case 10: direction=12;
                 divers=0;
                 break;
        case 9:  direction=11;
                 divers=0;
                 break;
      }
    }               
    if ((balle.Y==22)&&((balle.X==joueur+2)||(balle.X==joueur+3)||(balle.X==joueur+4)||(balle.X==joueur+5)))
    {
      switch (direction)
      {
        case 2:
        case 7:
        case 8:  direction=1;
                 divers=4;
                 break;
        case 3:
        case 9:
        case 10: direction=4;
                 divers=4;
                 break;
      }
    }
 /* CHANGE LA POSITION DE LA BALLE */
    switch (direction)
    {
      case 1:  balle.X++; /* balle.X++ �quivaut � balle.X = balle.X + 1 */
               balle.Y--; /* balle.Y-- �quivaut � balle.Y = balle.Y - 1 */
               break;
      case 2:  balle.X++;
               balle.Y++;
               break;
      case 3:  balle.X--;
               balle.Y++;
               break;
      case 4:  balle.X--;
               balle.Y--;
               break;
      case 5:  if (divers==0)
               {
                 balle.X++;
                 balle.Y--;
               }
               else if (divers<3) balle.Y--;
               break;
      case 6:  if (divers==0)
               {
                 balle.X++;
                 balle.Y--;
               }
               else if (divers<3) balle.X++;
               break;
      case 7:  if (divers==0)
               {
                 balle.X++;
                 balle.Y++;
               }
               else if (divers<3) balle.X++;
               break;
      case 8:  if (divers==0)
               {
                 balle.X++;
                 balle.Y++;
               }
               else if (divers<3) balle.Y++;
               break;
      case 9:  if (divers==0)
               {
                 balle.X--;
                 balle.Y++;
               }
               else if (divers<3) balle.Y++;
               break;
      case 10: if (divers==0)
               {
                 balle.X--;
                 balle.Y++;
               }
               else if (divers<3) balle.X--;
               break;
      case 11: if (divers==0)
               {
                 balle.X--;
                 balle.Y--;
               }
               else if (divers<3) balle.X--;
               break;
      case 12: if (divers==0)
               {
                 balle.X--;
                 balle.Y--;
               }
               else if (divers<3) balle.Y--;
               break;
    }
 /* DESSINE LA RAQUETTE DU JOUEUR */
    for (i=1 ; i<=80 ; i++)
    {
        gotoxy(i,23);
        printf(" ");
    }
    textcolor(ROUGE);
    if (joueur==1)
    {
      gotoxy(1,23);
      printf("=======");
    }
    else
    {
      if (joueur==73)
      {
        gotoxy(73,23);
        printf("=======");
      }
      else
      {
        gotoxy(joueur,23);
        printf("=======");
      }
    }
  
    while (kbhit()) /* kbhit() est une fonction qui permet de v�rifier si une touche
    a �t� press�. Ici, TANT QUE (une touche est press�e) ... */
    {
      keyP=getch();
      keyP=toupper(keyP); /* la fonction toupper permet de convertir le caract�re en majuscule */
      switch (keyP)
      {
        case GAUCHE:  joueur=joueur-3;
                      if (joueur<1) joueur=1;
                      break;
        case DROITE:  joueur=joueur+3;
                      if (joueur>73) joueur=73;
                      break;
        case ENTER:   gotoxy(75,25);
                      textcolor(JAUNE);
                      printf("PAUSE");
                      keyP=0;
                      while (keyP!=ENTER) 
                      {
                         keyP=getch();
                         /* que serait un prog sans ces cheats codes ?
                         (utilent pour connaitre les limites du jeu) */
                         if(keyP==CHEAT_F1) nbBall+=10;
                         if(keyP==CHEAT_F2) score+=100;
                         if(keyP==CHEAT_F3) vitesse+=10;
                         if(keyP==CHEAT_F4) objet=0;
                      }
                      gotoxy(75,25);
                      printf("     ");
                      break;
        case ESCAPE:  action=SORTIE;
                      break;
        case SOUND:   if(choix==0)
                      {
                         chson=1;
                         choix=1;
                      }
                      else
                      {
                         chson=0;
                         choix=0;
                      }
                      enregistrcfg();
                      break;
      }
    }
    if(vitesse<=0) vitesse=0;
    sleep(vitesse); /* la fonction sleep(int variable) permet de d�finir le temps 
    que l'ordinateur attend (en milliseconde) avant d'efectuer la prochaine instruction. 
    Ici, le temps d�pend d'une variable vitesse iitialis�e au d�but. Plus la valeur
    de la variable est petite, plus vite l'ordinateur effectuera l'instruction suivante */
    if (direction>4) divers++;
    else divers=0;
    if (divers==3) divers=0;
    gotoxy(2,25);
    textcolor(BLANC);
    printf("Niveau : %i    /    Vitesse : %i %%", nivo, (100-vitesse));
    gotoxy(41,25);
    textcolor(VERT);
    printf("\xB3");
    gotoxy(42,25);
    textcolor(BLANC);
    printf("Score : %5d ",score);
    textcolor(VERT);
    gotoxy(57,25);
    printf("\xB3");
    gotoxy(58,25);
    textcolor(BLANC);
    printf("Nbr balle : %3d ",nbBall);
    gotoxy(74,25);
    textcolor(VERT);
    printf("\xB3");
}

void initialisation()
{
      clrscr();
      placeObj();
      balle.X=40;
      balle.Y=22;
      joueur=37;
      divers=1;
      direction=4;
      dessineCadre();
      action=NORMAL;
}

int dessineCadre()
{
    gotoxy(1,24);
    textcolor(VERT);
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC2\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC2\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC2\xC4\xC4\xC4\xC4\xC4\xC4");
}

void menu()
{
if (action==MENU)
    {
      clrscr();
      gotoxy(1,1);
      textcolor(ROUGE);
      printf("**** BREAK ****\n\n");
      textcolor(VERT);
      printf("Il faut casser toutes les briques !");
      printf("\nN'h%csitez pas \x85 me prevenir pour les bugs !",130);
      printf("\n\nLes touches :");
      printf("\nGAUCHE : K\nDROITE : M\nPAUSE : Entr%ce\nQUITTER : Echap",130);
      printf("\nRELANCER LA BALLE : ESPACE\n(DES)ACTIVER LE SON : F5");
      textcolor(BLANC);
      printf("\n\nPour Win2000 / XP, les touches GAUCHE et DROITES correspondent"); 
      printf("\naux fl%cches pr%csentent sur le clavier",138,130);
      textcolor(ROUGE);
      printf("\n\n\n**** N%co's Prog ****",130);
      textcolor(JAUNE);
      printf("\n\nAppuyer sur une touche pour continuer\n");
      getch();
    /* initialisation des variables */
      score=0;
      vitesse=100;
      nbBall=3;
      nivo=1;
      choix=0;
      chson=0;
      lirecfg();
      initialisation();      
    }
}

int main()
{
  while (action!=SORTIE)
  {
    menu();  
    execution();
    if(objet==0)
    {
        gotoxy(26,12);
        textcolor(ROUGE);
        printf("Vous avez termin%c le niveau %i",130, nivo);
        gotoxy(1,25);
        printf("Touche \x22 ESPACE \x22 pour continuer  ");
        keyP=getch();
        while(keyP!=SPACE)
        {
            keyP=getch();
        }
        vitesse-=10; /* on diminue la valeur du sleep, donc on augmente la vitesse */
        nbBall+=1;
        nivo+=1;
        initialisation();
    }
    if(nbBall==0)
    {
        gotoxy(28,12);
        printf("YOU LOSE - GAME OVER");
        gotoxy(30,13);
        printf("Vous avez perdu");
        sleep(3000);
        affichscore();
        textcolor(JAUNE);
        gotoxy(1,25);
        printf("Voulez vous recommencer ? (O/N) : ");
        keyP=getch();
        keyP=toupper(keyP);
        if(keyP==YES)
        {
            action=MENU;
        }
        else
        {
            action=SORTIE;
        }
    }
  }
  return 0;
}
