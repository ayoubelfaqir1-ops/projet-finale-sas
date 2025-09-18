#include<stdio.h>
#include<string.h>
#include<ctype.h>

char text[1999];
int nmots;
float ntotal=0;

typedef struct 
{
    char valeur[20];
    int occurrence;
    int longueur;
    int position[100];
}mot;

mot dictionnaire[1999];


void analyser(){
    for (int i = 0; i < strlen(text); i++)
    {
        if (ispunct(text[i]))
        {
            text[i]=' ';
        }
    }// enlever la ponctuation.
    


    for (int i = 0; i < strlen(text); i++)
    {
        text[i]=tolower(text[i]);
    }//mettre en minuscules.
    

    
    char *word=strtok(text," ");
    int i=0;
    nmots=0;
    while (word!=NULL)
    { 
        int trouve=0;
        
        for (int k = 0; k <nmots ; k++)
        {
            if (strcmp(dictionnaire[k].valeur,word)==0)
            {
                dictionnaire[k].position[dictionnaire[k].occurrence]=ntotal;
                dictionnaire[k].occurrence++;
                trouve=1;
            }
        }
        if (!trouve)
        {
        strcpy(dictionnaire[i].valeur,word);
        dictionnaire[i].position[0]=ntotal;
        dictionnaire[i].occurrence=1;
        dictionnaire[i].longueur=strlen(dictionnaire[i].valeur);
        nmots++;
        i++;
        }
        ntotal++;
        word=strtok(NULL," ");
      
    }// deviser les mots.
}



void saisir(){
    printf("entrez votre texte :\n");
    fgets(text,sizeof(text),stdin);
    text[strcspn(text,"\n")]=0;
    analyser();
}//lire le texte et analyser;



void afficher(){
    for (int i = 0; i < nmots; i++)
            {
            printf("le mot '%s' repete -%d- fois lenght -%zu- postion:[",dictionnaire[i].valeur,dictionnaire[i].occurrence,strlen(dictionnaire[i].valeur));
            for (int j = 0; j < dictionnaire[i].occurrence; j++)
            {
            printf(" %d ",dictionnaire[i].position[j]);
            }
            printf("]\n");
            }
}//afficher tous les mots;



void recherche_exact(){
    char recherche[25];
    printf("entrez le mot a recherche : ");
    scanf("%s",recherche);
    getchar();
    int trouve=0;
    for (int i = 0; i < nmots; i++)
    {
        if (strcmp(dictionnaire[i].valeur,recherche) == 0)
        {
            printf("le mot -%s- repete -%d- fois lenght -%zu- postion:[",dictionnaire[i].valeur,dictionnaire[i].occurrence,strlen(dictionnaire[i].valeur));
            for (int j = 0; j < dictionnaire[i].occurrence; j++)
            {
            printf("%d,",dictionnaire[i].position[j]);
            }
            printf("]\n");
            trouve=1;
        }
    }
    if (!trouve)
        {
            printf("aucun mot trouvee.\n");
        }
}//recherche exact;



void recherche_partiel(){
    char recherche[25];
    printf("entrez une partie de mot a recherchee : ");
    scanf("%s",recherche);
    getchar();
    int trouve=0;
    for (int i = 0; i < nmots; i++)
    {
        if (strstr(dictionnaire[i].valeur,recherche) != NULL)
        {
            printf("le mot -%s- repete -%d- fois lenght -%lld- postion:[",dictionnaire[i].valeur,dictionnaire[i].occurrence,strlen(dictionnaire[i].valeur));
            for (int j = 0; j < dictionnaire[i].occurrence; j++)
            {
            printf("%d,",dictionnaire[i].position[j]);
            }
            printf("]\n");
            trouve=1;
        }
    }
    if (!trouve)
        {
            printf("aucun mot trouvee.\n");
        }
}//recherche partielement;



void trier_alphabit(){
    mot temp;
    for (int i = 0; i < nmots-1; i++)
    {
        for (int j = 0; j < nmots-i -1; j++){
            if (strcmp(dictionnaire[j].valeur,dictionnaire[j+1].valeur)>0)
            {
            temp=dictionnaire[j];
            dictionnaire[j]=dictionnaire[j+1];
            dictionnaire[j+1]=temp;
            }
        }
    }
}//trier par alphabet



void trier_decroissante(){
    mot temp;
    for (int i = 0; i < nmots-1; i++)
    {
        for (int j = 0; j < nmots-i-1; j++)
        {
        if (dictionnaire[j].occurrence<dictionnaire[j+1].occurrence)
        {
        temp=dictionnaire[j];
        dictionnaire[j]=dictionnaire[j+1];
        dictionnaire[j+1]=temp;
        }
        }
    }
}//trier par frequence decroiussante



void trier_croissante(){
    mot temp;
    for (int i = 0; i < nmots-1; i++)
    {
        for (int j = 0; j < nmots-i-1; j++)
        {
        if (dictionnaire[j].longueur>dictionnaire[j+1].longueur)
        {
        temp=dictionnaire[j];
        dictionnaire[j]=dictionnaire[j+1];
        dictionnaire[j+1]=temp;
        }
        }
    }
}// trier par longueur croissante



void statistiques(){
    float longueur_total=0;
    for (int i = 0; i < nmots; i++)
    {
        longueur_total=longueur_total+(dictionnaire[i].longueur*dictionnaire[i].occurrence);
    }
    float longueur_moyenne=longueur_total/ntotal;
    //calculer longueur moyenne


    mot plus_long=dictionnaire[0];
    for (int i = 1; i < nmots; i++)
    {
        if (dictionnaire[i].longueur>plus_long.longueur)
        {
            plus_long=dictionnaire[i];
        }
    }
    //calculer le mot plus long


    mot plus_court=dictionnaire[0];
    for (int i = 1; i < nmots; i++)
    {
        if (dictionnaire[i].longueur<plus_court.longueur)
        {
            plus_court=dictionnaire[i];
        }
    }//calculer le mot plus court


    float diversite;
    diversite=nmots/ntotal;
    //calcule diversite


    printf("\n------STATISTIQUES GLOBAL------\n");
    printf("nombre total       : %.0f\n",ntotal);
    printf("nombre mots unique : %d\n",nmots);
    printf("longueur moyenne   : %.2f\n",longueur_moyenne);
    printf("mot le plus long   : %s\n",plus_long.valeur);
    printf("mot le plus court  : %s\n",plus_court.valeur);
    printf("diversite lexicale : %.2f\n",diversite);
}



void palindrome(){
    for (int i = 0; i < nmots; i++)
    {
        int trouve=0;
        int debut=0;
        int fin=strlen(dictionnaire[i].valeur)-1;
        while (debut<fin)
        {
            if (dictionnaire[i].valeur[debut]!=dictionnaire[i].valeur[fin])
            {
                trouve=1;
                break;
            }
            debut++;
            fin--;
            
        }
        if (!trouve)
        {
        printf("%s\n",dictionnaire[i].valeur);
        }
    }
    
}



void trier(char mot1[20] ){
    char temp;
    int n=strlen(mot1);
    for (int i = 0; i < n; i++)
    {
    for (int c = 0; c < n-1 ; c++)
    {
        if (mot1[c]>mot1[c+1])
        {
            temp=mot1[c];
            mot1[c]=mot1[c+1];
            mot1[c+1]=temp;
        }  
    }
    }
}// pour anagrame



void anagrame(){
    char mot1[20];
    char mot2[20];
    char mot_trouve[100][20];
    int n=0;
    for (int i = 0; i < nmots; i++)
    {
        int found=0;
        for (int k = 0; k <n ; k++)
        {
        if (strcmp(dictionnaire[i].valeur,mot_trouve[k])==0)
        {
            found=1;
            break;
        }
        }
        if (found==1)
        {
            continue;
        }
        
        for (int j = 0; j < nmots; j++)
        {
            if (dictionnaire[i].longueur!=dictionnaire[j].longueur || i==j)
            {
                continue;
            }
            strcpy(mot1,dictionnaire[i].valeur);
            strcpy(mot2,dictionnaire[j].valeur);
            trier(mot1);
            trier(mot2);
            if (strcmp(mot1,mot2)==0)
            {
                strcpy(mot_trouve[n],dictionnaire[i].valeur);
                n++;
                strcpy(mot_trouve[n],dictionnaire[j].valeur);
                n++;
                printf("anagrame de %s et %s \n",dictionnaire[i].valeur,dictionnaire[j].valeur);  
            }
        }
    }
}



void nuage_mots(){
    for (int i = 0; i < nmots; i++)
    {
        printf("%s : ",dictionnaire[i].valeur);
        for (int j = 0; j < dictionnaire[i].occurrence; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    
}



int main(){
    int choix=0;
    int choix2=0;

    while(choix!=8)
    {
        printf("\n---------MENU PRINCIPAL--------\n");
        printf("1- Saisir un texte et analyser\n");
        printf("2- Afficher tous les mots (dictionnaire)\n");
        printf("3- Rechercher un mot exact\n");
        printf("4- Rechercher un mot partiel\n");
        printf("5- Trier les mots\n");
        printf("6- Statistiques globales\n");
        printf("7- Analyses (palindromes, anagrammes, nuage de mots)\n");
        printf("8- Quitter le programme\n");
        printf("--------------------------------\n");
        printf("entrez votre choix : ");
        scanf("%d",&choix);
        getchar();
        switch (choix)
        {
        case 1:saisir();
            break;
        case 2:afficher();
            break;
        case 3:recherche_exact();
            break;
        case 4:recherche_partiel();
            break;
        case 5:trier_decroissante();
            break;
        case 6:statistiques();
            break;
        case 7:printf("1-pour palindrome\n2-pour anagrammes\n3-pour nuage de mots\nvotre choix : ");
               scanf("%d",&choix2);
               if (choix2==1)
               {
                printf("\n---les palindromes dans le texte---\n");
                palindrome();
               }else if (choix2==2)
               {
                anagrame();
                
               }else if (choix2==3)
               {
                nuage_mots();
               } 
               break;  
        case 8:printf("au revoir.");
            break;
        }
    }
    return 0;
}