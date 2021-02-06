#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>


typedef struct arvore{
	int cod;
	int heuristica;
	int matriz[3][3];
	struct arvore* rsup;
	struct arvore* rinf;
	struct arvore* rdir;
	struct arvore* resq;
	char movimento[30];
	int qtdmov;
}Arvore;

int qtdmovimentos = 0;

typedef struct lista{
   int info;
   struct lista* prox;
}Lista;

Lista* L = NULL;
Lista* L2 = NULL;
Arvore* aux = NULL;
Arvore* aux2 = NULL;

Lista* insereIni(int valor, Lista* L){
    Lista* aux = (Lista*) malloc(sizeof(Lista));
    aux->info = valor;
    aux->prox=L;
    return aux;
}

Lista* removeLista(Lista *L, int valor){
	
	Lista* aux = L;
	Lista* ant = NULL;
	
	while(aux->info!= valor && aux!=NULL){
		ant = aux;
		aux = aux->prox;
	}
	if(aux==NULL){
		return L;
	}
	if(ant == NULL){
		L= L->prox;
		free(aux);
	} else {
			ant->prox = aux->prox;
			free(aux);
	}
	
	return L;
}

int achaMenor(Lista* L) {
	if(L==NULL){
		return 10000;
	}else{
		int menor;
		menor=achaMenor(L->prox); 
		if(menor<L->info)
		return menor;
		else
		return L->info; 		
	}
}


// matriz global
int matriz[3][3];
int matrizComp[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

//int matriz[3][3] = {{2,1,3},{4,5,6},{7,8,9}};
//int matriz[3][3] = {{1,2,3},{4,5,6},{7,9,8}};
//int matriz[3][3] = {{2,3,6},{1,4,9},{7,5,8}};
//int matriz[3][3] = {{2,9,5},{1,6,8},{4,3,7}};
//int matriz[3][3] = {{3,2,5},{6,1,8},{7,4,9}};
//int matriz[3][3] = {{4,3,2},{9,5,8},{1,6,7}};
//int matriz[3][3] = {{5,6,2},{4,9,8},{7,1,3}};

//int matriz[3][3] = {{1,2,3},{9,4,5},{6,7,8}};
//{5,6,2,4,0,8,7,1,3}
//4 3 2 9 5 8 1 6 7
//3 2 5 6 1 8 7 4 9
int codigo= 1;


// verifica se existe valor na matriz
int  existeValor(int valor){
		int i, j; 
		
		for(i = 0; i < 3; i++){
			for(j= 0; j < 3; j++){
				
				if(matriz[i][j] == valor){
					return 1;
				}
			}
		}
		return 0;
}

void imprimeMatriz(int m[][3]){
	int contador = 0;
//	getch();
//	printf("passo %d\n", contador);
	contador++;
	int i=0,j=0;
	
	for(i = 0; i < 3;i++){
		for(j = 0; j < 3; j++){
			if(m[i][j] == 9){
				printf("\t - ");
			} else
				printf(" \t %d", m[i][j]);		
		}
			printf("\n");
	}
}


 criaMatriz(){
	
	int num =0, i, j;
	int comp;
	
	
	
	for(i = 0; i < 3;i++){
		for(j= 0;j < 3; j++){
				 srand(time(NULL));
				 num = rand() % 9;
				 
				 // Enquanto esse va
				 //lor existir gere outro 
				 while((existeValor(num)) == 1 || num == 0){
				 		num = rand() % 10;
				 }
				
				matriz[i][j] = num;
		}
	} 
	
	imprimeMatriz(matriz);
	
}


void criaMatrizComparacao(){

	int i=0,j=0,cont=1;

		for(i = 0; i < 3;i++){
			for(j = 0; j < 3; j++){
				if(i == 0 && j ==0 ){
					matrizComp[i][j] = 9;
				}
				else{
					matrizComp[i][j] = cont;
					cont++;
					
				}
		}	
	}

}

int calculaHeuristica(int m[][3]){
	
	int i=0, j = 0;
	int h=0,valor =0, linha = 0, coluna = 0,linhaComp =0, colunaComp=0;
	int flag=0;
	int cont=0;
	
	
	for(valor = 1; valor<=8; valor++){// encontrar a distancia de cada valor
		
		
			for(i = 0; i < 3;i++){
				for(j = 0; j < 3; j++){
					if(m[i][j] == valor ){
						linha = i;
						coluna = j;		
											// Encontra a linha e a coluna desse valor			
					}
				}
			}
		
			for(i = 0; i < 3;i++){
				for(j = 0; j < 3; j++){
					if(matrizComp[i][j] == valor ){	
						linhaComp = i;						// Encontra a posição em que esse valor deveria estar
						colunaComp = j;
					}
				}
			}
			
		while(flag != 1 ){
			
			if(linhaComp > linha){
				linhaComp--;
				cont++;
			}
			
			else if(linhaComp < linha){
				linhaComp++;
				cont++;
			}
			
			else if(colunaComp > coluna){
				colunaComp--;
				cont++;
			}
			
			else if(colunaComp < coluna){
				colunaComp++;
				cont++;
				
			}
			
			else{
				flag = 1;
				
			}
			
		}
		
		h = h + cont;
		cont = 0;
		flag = 0;
			
	}
		return h;
}



Arvore* insereArvore(int m[][3],int altura){
	
	int i=0;
	int j=0;
	
	Arvore* arv = (Arvore*) malloc(sizeof(Arvore));
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			
			arv->matriz[i][j] = m[i][j];
			arv->rsup = NULL;
			arv->rinf = NULL;
			arv->rdir = NULL;
			arv->resq = NULL;
			arv->cod = codigo;
			codigo++;
		}
	}
	
	arv->heuristica = calculaHeuristica(arv->matriz);
	
	return arv;
	
}


void copia(int b[][3],int a[][3])

{

     int i,j;
     for(i=0;i<3;i++)
                     for(j=0;j<3;j++)
                                     a[i][j]=b[i][j];
                                     	                                  


}

void troca(int *a,int *b)
{

     int aux;
     aux=*a;
     *a=*b;
     *b=aux;

}

void achaMatriz(Arvore* arv,int codigo){
	
	if(arv != NULL){
	
	
		if(arv->cod != codigo ){
			achaMatriz(arv->rdir,codigo);
			achaMatriz(arv->resq,codigo);
			achaMatriz(arv->rsup,codigo);
			achaMatriz(arv->rinf,codigo);
		}
		
		else{
			
			aux2 = arv;
		}
	
	}
}

int compara(int matriz[][3],Arvore* raiz){
	
	int i,j;
	int flag=0;
	
	Lista* Laux = NULL;
	Laux = L2;
	
	
	
		
	while(Laux != NULL){
		
		achaMatriz(raiz,Laux->info);

		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				
				if(matriz[i][j] != aux2->matriz[i][j]){
					flag = 1;
				}
			}	
		}
		
		if(flag == 0){
			return 1; // possui uma matriz aberta identica
			
		}
		
		else{
			flag = 0;
			Laux = Laux->prox;
		}
		
	}
	
	return 0; // não possui matriz desse tipo aberto
	
	
	
}



void arranjaArvore(Arvore* arv,Arvore* raiz){
	
	int i=0;
	int j = 0;
	
	Arvore* rsup = (Arvore*) malloc(sizeof(Arvore));
	Arvore* rinf = (Arvore*) malloc(sizeof(Arvore));
	Arvore* rdir = (Arvore*) malloc(sizeof(Arvore));
	Arvore* resq = (Arvore*) malloc(sizeof(Arvore));
	
	rsup->rdir = NULL;
	rsup->resq = NULL;
	rsup->rsup = NULL;
	rsup->rinf = NULL;
	
	rinf->rdir = NULL;
	rinf->resq = NULL;
	rinf->rsup = NULL;
	rinf->rinf = NULL;
	
	resq->rdir = NULL;
	resq->resq = NULL;
	resq->rsup = NULL;
	resq->rinf = NULL;
	
	rdir->rdir = NULL;
	rdir->resq = NULL;
	rdir->rsup = NULL;
	rdir->rinf = NULL;
	
	rsup->qtdmov = arv->qtdmov+1;
	rinf->qtdmov = arv->qtdmov+1;
	rdir->qtdmov = arv->qtdmov+1;
	resq->qtdmov = arv->qtdmov+1;
	
	//printf("\t\tINICIO\n\n");
	//imprimeMatriz(arv->matriz);
//	printf("\n\n");
	
	int x,y;
	
	
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
			
				if(arv->matriz[i][j] == 9){
					x = i;
					y=j;
				}
			
			}
		}
	
	
	if((x-1) >=0 ){
	//	printf("superior\n");
		copia(arv->matriz, rsup->matriz);
		troca(&rsup->matriz[x][y],&rsup->matriz[x-1][y]);
		rsup->heuristica = calculaHeuristica(rsup->matriz);
		rsup->cod = codigo;
		codigo++;
	//	printf("\n\n");
		//imprimeMatriz(rsup->matriz);
		strcpy(rsup->movimento, "MOVER PARA BAIXO");
				
	} else {
		rsup = NULL;
	}
	
	if((x+1) <= 2){
	//	printf("inferior\n");
				
		copia(arv->matriz, rinf->matriz);

		troca(&rinf->matriz[x][y],&rinf->matriz[x+1][y]);
		rinf->heuristica = calculaHeuristica(rinf->matriz);
		rinf->cod = codigo;
		codigo++;
	//	printf("\n\n");
		//imprimeMatriz(rinf->matriz);
		strcpy(rinf->movimento, "MOVER PARA CIMA");



		
	} else {
		rinf = NULL;
	}
	
	
	if((y+1) <= 2){
		//printf("direita\n");

		copia(arv->matriz, rdir->matriz);
		troca(&rdir->matriz[x][y],&rdir->matriz[x][y+1]);
		rdir->heuristica = calculaHeuristica(rdir->matriz);
		rdir->cod = codigo;
		codigo++;
	//	printf("\n\n");
		//imprimeMatriz(rdir->matriz);
		strcpy(rdir->movimento, "MOVER PARA ESQUERDA");



	} else {
		rdir = NULL;
	}
	
	if((y-1) >=0){
		//printf("esquerda\n");

		copia(arv->matriz, resq->matriz);
		troca(&resq->matriz[x][y],&resq->matriz[x][y-1]);
		resq->heuristica = calculaHeuristica(resq->matriz);
		resq->cod = codigo;
		codigo++;
	//	printf("\n\n");
		//imprimeMatriz(resq->matriz);
		strcpy(resq->movimento, "MOVER PARA DIREITA");


	}	else {
		resq = NULL;
	}
	
	if(rdir != NULL){
	
		if(compara(rdir->matriz,raiz) == 0){
			arv->rdir = rdir;
			L = insereIni(rdir->heuristica, L);	
		}
	}
	else{
		arv->rdir = NULL;
	}
	
	
	
	if(resq != NULL){
	
		if(compara(resq->matriz,raiz) == 0){
			arv->resq = resq;
				L = insereIni(resq->heuristica, L);	
		}
	}
	else{
		arv->resq = NULL;		
	}
	
	if(rinf != NULL){
	
		if(compara(rinf->matriz,raiz) == 0){
			arv->rinf = rinf;
			L = insereIni(rinf->heuristica, L);		
		}
	}
	else{
		arv->rinf = NULL;
	}
	
	
	if(rsup != NULL){
	
	if(compara(rsup->matriz,raiz) == 0){
		arv->rsup = rsup;	
			L = insereIni(rsup->heuristica, L);	
	}
	
	}
	
	else{
		arv->rsup = NULL;
	}
	
	
}

void imprimeLista(Lista* L){
  Lista* aux = L;
  while(aux!=NULL){
    printf("%d\n", aux->info);
    aux=aux->prox;
  }
}

int verificaAberto(int cod,Lista* L2){
	
	while(L2 != NULL){
		if(L2->info == cod){
			return 1;
		}
		L2 = L2->prox;
		
	}
	
	return 0;

}


void procura(Arvore* arv,int h,Lista* L2){
	
	if(arv != NULL){
	
		int aberto = verificaAberto(arv->cod,L2);
	
	
		if(arv->heuristica != h || aberto != 0){
			procura(arv->rdir,h,L2);
			procura(arv->resq,h,L2);
			procura(arv->rsup,h,L2);
			procura(arv->rinf,h,L2);
		}
		
		else{
			aux = arv;
		}
	
	}
}

int qtdHeuristica(Lista* L,int valor){
	
	int qtd = 0;
	
	while( L != NULL){
		
		if(L->info == valor){
			qtd++;
		}
		L = L->prox;
	}
	
	return qtd;
	
}

void verifica(Arvore *arv,Arvore* raiz){
	
	//printf("heuristica = %d\n",arv->heuristica);
	//printf("Cod: %d\n",arv->cod);
	int menor = achaMenor(L);
	if(menor == 0 && arv->heuristica == 0){
		printf("\nFIM\n\n");
		
		imprimeMatriz(arv->matriz);
		printf("\nEm %d movimentos!\n",arv->qtdmov);
	}
	
	else {
		
		
	//	printf("\nmenor:%d",menor);
	//	printf("\nLISTA\n");
	//	imprimeLista(L);
	//	printf("\nLISTA2\n");
	//	imprimeLista(L2);
		procura(raiz,menor,L2);
		arv = aux;
		//qtdmovimentos++;
		printf("------------------------------------------\n");
		printf("\n%s\n\n", arv->movimento);
		imprimeMatriz(arv->matriz);
		printf("------------------------------------------\n");
	//	printf("codigo : %d\n",arv->cod);
			
			
		if(arv->rdir != NULL &&  arv->rdir->heuristica == menor && arv->rdir->heuristica != 0){
			arranjaArvore(arv->rdir,raiz);
			if(menor != 0){
			L = removeLista(L, menor);
			}
			L2 = insereIni(arv->cod,L2);
			verifica(arv->rdir,raiz);
		}
		 
		if(arv->rsup != NULL &&  arv->rsup->heuristica == menor && arv->rsup->heuristica != 0){
			arranjaArvore(arv->rsup,raiz);
			if(menor != 0){
			L = removeLista(L, menor);
			}
			L2 = insereIni(arv->cod,L2);
			verifica(arv->rsup,raiz);
		}
		if(arv->rinf != NULL &&  arv->rinf->heuristica == menor && arv->rinf->heuristica != 0){
			arranjaArvore(arv->rinf,raiz);
			if(menor != 0){
			L = removeLista(L, menor);
			}
			L2 = insereIni(arv->cod,L2);
			verifica(arv->rinf,raiz);
		}
		if(arv->resq != NULL &&  arv->resq->heuristica == menor && arv->resq->heuristica != 0){
			arranjaArvore(arv->resq,raiz);
			if(menor != 0){
			L = removeLista(L, menor);
			}
			L2 = insereIni(arv->cod,L2);
			verifica(arv->resq,raiz);
		}
		
		
		
		else{ // quando é raiz e esta com todas as ramificações null
			
			arranjaArvore(arv,raiz);
			if(menor != 0){
			L = removeLista(L, menor);
			}
			L2 = insereIni(arv->cod,L2);
			verifica(arv,raiz);
			
		}
	}
	
}


int soluvel(int matriz[][3]){
	
	int inversao=0;
	int i,j;
	int vetor[8];
	int k=0;
	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			
			if(matriz[i][j] != 9){
				vetor[k] = matriz[i][j];
				k++;
			}
		}
	}
	
	
	
	for(i=0;i<8;i++){
		for(j=i+1;j<8;j++){
			if(vetor[j] > vetor[i]){
				inversao++;
			}
		}
	}
	
	if(inversao%2 == 1){
		return 0; // não é soluvel
	}
	
	else{
		return 1; // é soluvel.
	}
	
	
}


int main(){
	
	int h;
	int i,j;
	
	
    criaMatriz();
    

    // raiz->heuristica = calculaHeuristica(arv->matriz);
	//imprimeMatriz(raiz->matriz); 
	//printf("h = %d\n",raiz->heuristica);    

 
    
  //  L = insereIni(arv->heuristica, L);	
	
	/*
    
    printf("raiz %d \n\n", arv->heuristica);
    if (arv->rdir!=NULL){
	
    printf("direita %d \n\n", arv->rdir->heuristica);
	}
    if (arv->resq!=NULL){
	imprimeMatriz(arv->resq->matriz);
	L = insereIni(arv->resq->heuristica, L);
    printf("esquerda %d\n\n", arv->resq->heuristica);
	}
    if (arv->rinf!=NULL){
	imprimeMatriz(arv->rinf->matriz);
	L = insereIni(arv->rinf->heuristica, L);
    printf("inferior %d \n\n", arv->rinf->heuristica);
	}
    if (arv->rsup!=NULL){
    	imprimeMatriz(arv->rsup->matriz); 
    	L = insereIni(arv->rsup->heuristica, L);
    printf("superior %d \n\n", arv->rsup->heuristica);
	} */
	
/*	imprimeLista(L);
	printf("\n\n%d\n\n", achaMenor(L));
	L = removeLista(L,achaMenor(L));
	imprimeLista(L); */
	
//	imprimeLista(L);
	
	if(soluvel(matriz) == 0){
		printf("Não e soluvel!");
	}
	
	else{
		
	//	imprimeMatriz(matriz);
	     //criaMatrizComparacao();
	//     printf("\n");
	     //imprimeMatriz(matrizComp);
	     
	     Arvore* raiz = (Arvore*) malloc(sizeof(Arvore));
	     for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				
				raiz->matriz[i][j] = matriz[i][j];
				
			}
		}
		
		raiz->rsup = NULL;
		raiz->rinf = NULL;
		raiz->rdir = NULL;
		raiz->resq = NULL;	
		raiz->qtdmov=0;
		
		raiz->cod = codigo;
		codigo++;
		raiz->heuristica = calculaHeuristica(raiz->matriz);
		L = insereIni(raiz->heuristica,L);
		strcpy(raiz->movimento, "ESTADO INICIAL");
			
		verifica(raiz,raiz);
	}
}