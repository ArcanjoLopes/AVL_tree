    //---------------------BIBLIOTECAS-----------------------------------------
    #include<stdio.h> 
    #include<stdlib.h>
    #include<string.h>
    #include<conio.h>

    //----------------------STRUCT---------------------------------------------
    typedef struct arv{
        int info, fb;//informação do nó e fator de Balanceamento respectivamente
        struct arv* esq;
        struct arv* dir;
    }AVL;
    //------------------PROTÓTIPOS---------------------------------------------
    AVL* insere();
    static int max2();
    int arv_altura();
    AVL* rodarEsq();
    AVL* rodarDir();
    AVL* dupla_dir_esq();
    AVL* dupla_esq_dir();
    AVL* arv_remove();
    void imprimePreordem();
    void imprimePosordem();
    void imprimeOrdem();
    AVL* arv_apagartoda();
    void menu();
    void imprime();
    void ordem();
    void busca();
    void apenas_um();
    AVL* balanceamento();
    
    //----------------------------------FUNÇÕES-------------------------------------
    AVL *insere (AVL *arvore, int num)//função que realiza iserção na AVL
    { 
      if(arvore == NULL)
      {         
      arvore = (AVL*) malloc (sizeof(AVL));//alocação dinâmica
      arvore->dir = NULL;
      arvore->esq = NULL;
      arvore->info = num;//informação do Nó
      arvore->fb = 0;//fator de balanceamento
      printf("\tnumero inserido com sucesso!!!\n\n");
      return arvore; 
      }//fim if
      if (arvore->info == num) printf("\tnumero ja foi inserido anteriormente\n\n");
      else
      { 
      if(num > arvore->info)
      {
      arvore->dir = insere(arvore->dir, num);
      if(arvore->dir != NULL)
      arvore = balanceamento(arvore);
      }//fim if
      else 
       {
       if(num < arvore->info)
       {
       arvore->esq = insere(arvore->esq, num);
       if(arvore->esq != NULL)
       arvore = balanceamento(arvore);
       }//fim IF
       }//fim else 
    }//fim else
    return arvore;
    }//fim insere

    static int max2 (int a, int b)
    {
    return (a > b)? a:b;//retona apenas um dos valores que for maior
    }
    
    int arv_altura(AVL* arvore)//função que retorna o fator de balanceamento
    {
    if(arvore == NULL)
    return -1;
    else 
    return 1 + max2(arv_altura(arvore->dir), arv_altura(arvore->esq));//realiza a soma de cada nó
    }
    
    AVL* rodarEsq(AVL *arvore)
    {
     AVL *q, *temp;
     q = arvore->dir;
     temp = q->esq;
     q->esq = arvore;
     arvore->dir = temp;
     arvore = q;
     arvore->esq->fb = arv_altura(arvore->esq->dir) - arv_altura(arvore->esq->esq);//atualiza o fator de balanceamento
     arvore->fb = arv_altura(arvore->dir) - arv_altura(arvore->esq);//atualiza o fator de balanceamento
     return q;
    }//fim rodarEsq
    
    AVL* rodarDir(AVL *arvore)
    {
     AVL *q, *temp;
     q = arvore->esq;
     temp = q->dir;
     q->dir = arvore;
     arvore->esq = temp;
     arvore = q;
     arvore->dir->fb = arv_altura(arvore->dir->dir) - arv_altura(arvore->dir->esq);//atualiza o fator de balanceamento
     arvore->fb = arv_altura(arvore->dir) - arv_altura(arvore->esq);//atualiza o fator de balanceamento
     return q;
    }//fim rodarDir
    
    AVL* dupla_dir_esq(AVL *arvore)
    {
     AVL* q, *temp;
     q = arvore->dir;
     temp = q->esq;
     q->esq = temp->dir;
     temp->dir = q;
     arvore->dir = temp->esq;
     temp->esq = arvore;
     arvore = temp;
     arvore->esq->fb = arv_altura(arvore->esq->dir) - arv_altura(arvore->esq->esq);//atualiza o fator de balanceamento
     arvore->dir->fb = arv_altura(arvore->dir->dir) - arv_altura(arvore->dir->esq);//atualiza o fator de balanceamento
     arvore->fb = arv_altura(arvore->dir) - arv_altura(arvore->esq);//atualiza o fator de balanceamento
     return temp;
    }//fim dupla_dir_esq
    
    AVL* dupla_esq_dir(AVL* arvore)
    {
     AVL* q, *temp;
     q = arvore->esq;
     temp = q->dir;
     q->dir = temp->esq;
     temp->esq = q;
     arvore->esq = temp->dir;
     temp->dir = arvore;
     arvore = temp;
     arvore->esq->fb = arv_altura(arvore->esq->dir) - arv_altura(arvore->esq->esq);//atualiza o fator de balanceamento
     arvore->dir->fb = arv_altura(arvore->dir->dir) - arv_altura(arvore->dir->esq);//atualiza o fator de balanceamento
     arvore->fb = arv_altura(arvore->dir) - arv_altura(arvore->esq);//atualiza o fator de balanceamento
     return temp;
    }//fim dupla_esq_dir
    
    AVL* arv_remove(AVL* arvore, int num)
    { 
     AVL* temp, aux;
     if (arvore == NULL)
     { 
     printf("numero nao foi inserido\n");
     return NULL;
     }
     if (num > arvore->info)
     {
     arvore->dir = arv_remove(arvore->dir, num);
     } 
     else if(num < arvore->info)
     {
     arvore->esq = arv_remove(arvore->esq, num);
     }
     else 
       { 
       if (arvore->dir == NULL && arvore->esq == NULL)
       {
       free(arvore);
       return NULL;
       }
       else if (arvore->esq != NULL && arvore->dir == NULL)
       {
       temp = arvore;
       free(temp);
       }
       else if (arvore->esq == NULL && arvore->dir != NULL)
          {
          temp = arvore;
          free(temp);    
          }
          else {
               temp = arvore->esq;
               while (temp->dir != NULL)
               {
               temp = temp->dir;
               }
               arvore->info = temp->info;
               temp->info = num;
               arvore->esq = arv_remove(arvore->esq, num);
               }
    }//fim else
    
    arvore = balanceamento(arvore);//atualiza o fator de balanceamento de toda árvore
    return arvore;    
    }//remover

    AVL* arv_apagartoda(AVL* arvore)//elimina toda árvore
    {
     if(arvore != NULL)
     {
     arv_apagartoda(arvore->esq);
     arv_apagartoda(arvore->dir);
     free(arvore);
     } 
    return NULL;
    }
    
    void imprimePreordem(AVL *arvore)
    {
     if(arvore != NULL) 
     {
     printf("%d, ", arvore->info);
     imprimePreordem(arvore->esq);
     imprimePreordem(arvore->dir);
     }
    }//fim imprimePreordem
    
    void imprimeOrdem(AVL *arvore)
    {
     if(arvore != NULL) 
     {
     imprimeOrdem(arvore->esq);
     printf("%d, ", arvore->info);
     imprimeOrdem(arvore->dir);
     }
    }//fim imprimeOrdem
    
    void imprimePosordem(AVL *arvore)
    {
     if(arvore != NULL) 
     {
     imprimePosordem(arvore->esq);
     imprimePosordem(arvore->dir);
     printf("%d, ", arvore->info);
     }
    }//fim imprimePosordem
   
   
    AVL* balanceamento(AVL* arvore)
    {
     arvore->fb = arv_altura(arvore->dir) - arv_altura(arvore->esq);
     if(arvore->fb == -2)
     {
     if(arvore->esq->fb == 0 || arvore->esq->fb == -1 ) 
     arvore = rodarDir(arvore);
     else if((arvore->fb == -2) && (arvore->esq->fb > 0))
     arvore = dupla_esq_dir(arvore);
     }
     if(arvore->fb == 2)
     {
     if (arvore->dir->fb == 0 || arvore->dir->fb == 1) 
     arvore = rodarEsq(arvore);
     else if((arvore->fb == 2) && (arvore->dir->fb < 0))
     arvore = dupla_dir_esq(arvore);      
     }
    return arvore;
    }


    void menu()
    {    
     int i; 
     printf("\t");printf("%c",201);
     for(i=1; i<=50; i++) printf("%c", 205); printf("%c",187);//linhas do menu ASCII
     printf("\n\t%c\t\t   MENU DA AVL                     %c\n \t",186, 186);printf("%c",204);//linhas do menu
     for(i=1; i<=50; i++) printf("%c", 205);printf("%c",185);//linhas do menu ASCII
     printf("\n\t%c   ESCOLHA SUA op%cao                              %c\n\t%c \t\t\t\t\t\t   %c\n",186,135,186,186,186);
     printf("\t%c\t1 - inserir                                %c\n",186,186);
     printf("\t%c\t2 - Imprimir                               %c\n",186,186);
     printf("\t%c\t3 - Remover numero                         %c\n",186,186);
     printf("\t%c\t4 - eliminar toda arvore para nova inser%cao%c\n",186,135,186);
     printf("\t%c\t9 - Para sair do programa \t \t   %c\n \t%c",186,186,200,186);
     for(i=1; i<=50; i++) printf("%c", 205);printf("%c",188);//linhas de menu ASCII
     printf("\n\n\t");
    }
    
    void imprime(AVL* arvore)
    {     
      int op, num; 
      char a, b;
      while(op!=9){
      system("cls"); 
      printf("\n\tescolha a op%cao\n\t\t 1 - imprimir apenas um numero da arvore\n\t\t 2 - imprimir toda arvore\n \t\t 9 - Para Voltar ao Menu Principal\n",135);
      printf("\t%c",16);
      scanf("%d", &op);
      
      switch(op)
          {
          case 1:system("cls");
                 do{
                   system("cls");
                   printf("informe o numero para impressao\n");
                   scanf(" %d", &num);
                   busca(arvore, num);//busca o numero na AVL para impressão
                   printf("\n\n\tdeseja imprimir mais algum numero S/N?\n\t%c",16);
                   scanf("  %c",&a);
                   }while(a == 'S' || a == 's');
                   break;
          case 2: system("cls");
                  do{
                  system("cls");              
                  ordem(arvore);//escolhe a ordem para impressão
                  printf("deseja fazer mais alguma impressão?\n S/N =>");
                  scanf(" %c", &b);
                  }while (b == 'S' || b == 's');
                  break;
          }//fim switch
          }
    }//fim void imprime

    void ordem(AVL* arvore)//escolhe a ordem de Impressão da AVL
    {
      int op;
      printf("\tem qual ordem deseja imprimir a arvore??\n\n");
      printf("\t1- EM-ORDEM (ERD)\n \t2- PRE-ORDEM (RED)\n \t3- POS-ORDEM (EDR)\n\n");
      printf("%c",16);
      scanf("%d", &op);
      switch(op)
         {
         case 1: system("cls");
                 printf("\n\tArvore ORDENADA\n %c ",16);
                 imprimeOrdem(arvore);
                 printf("\n\n ");
                 break;
         case 2: system("cls");
                 printf("\n\tArvore PRE-ORDENADA\n %c",16);
                 imprimePreordem(arvore);
                 printf("\n\n ");
                 break;
         case 3: system("cls");
                 printf("\n\tArvore POS-ORDENADA\n %c",16);
                 imprimePosordem(arvore);
                 printf("\n\n ");
                 break;
          }// fim switch
    }//fim  void ordem

    void busca (AVL* arvore, int num)//realiza a busca de apenas uma informção na árvore
    {        
     if (arvore == NULL) 
     printf("numero não existe na árvore\n");
     else if (num > arvore->info) 
     busca (arvore->dir, num);
     else if ( num < arvore->info) 
     busca (arvore->esq, num);
     else
     printf("este eh o numero: %d \n",arvore->info);
    }// fim void busca

    int main(void)
    {
      char c;
      int num, op,opc=0;
      AVL *arvore = NULL; 
      while (op!=9)
       {
         system("cls");
         menu(); //cria o MENU de opções
         printf("%c",16);
         scanf("%d", &op);
         switch(op)
             {
             case 1: system("cls");
                     printf("\n\t%c   informe o numero: ", 1);
                     //scanf("%d", &num); printf("\n\n");
                     //arvore = insere(arvore, num); //inserção na AVL
                     arvore = insere(arvore, 1);
                     /*arvore = insere(arvore, 2);
                     arvore = insere(arvore, 3);
                     arvore = insere(arvore, 4);
                     arvore = insere(arvore, 5);
                     arvore = insere(arvore, 6);
                     arvore = insere(arvore, 7);
                     arvore = insere(arvore, 8);
                     arvore = insere(arvore, 9);
                     arvore = insere(arvore, 10);*/
                     system("pause");
                     break;
             case 2: system("cls");
                     if(arvore == NULL){
                     printf("arvore esta vazia\n");
                     system("pause");
                     break;
                     }else
                     system("cls");
                     imprime(arvore);//imprime a árvore AVL
                     //system("pause");
                     break;                
             case 3: system("cls");
                     if(arvore == NULL){
                     printf("nada foi inserido\n");
                     system("pause");
                     break;
                     }else
                     printf("informe o numero para remover: ");
                     scanf("%d", &num);
                     arvore = arv_remove(arvore, num);//remove as informções da AVL
                     printf("numero removido \n");
                     system("pause");
                     break;
             case 4: system("cls");
                     if(arvore == NULL){
                     printf("arvore ja esta vazia\n");
                     system("pause");
                     break;
                     }else
                     if(arvore != NULL)//eliminar toda AVL da memória
                     printf(" deseja eliminar toda a arvore???\n S/N =>");
                     scanf(" %c",&c);
                     fflush(stdin);
                     switch(c){
                              case 'S':
                              case 's': arvore = arv_apagartoda(arvore);
                                        puts("arvore completamente apagada\n");
                                        system("pause");
                                        break;
                              case 'N':
                              case 'n': printf("voltando para o menu principal");
                                        system("pause");
                                        break;
                              }// fim switch
            case 9: system("cls");
                    printf("SAINDO DO PROGRAMA \nOBRIGADO POR USAR O SOTWARE \n\n\n");
                    system("pause");
                    break;    
                      }//FIM SWITCH                                     
              }//FIM WHILE
    }//FIM MAIN
