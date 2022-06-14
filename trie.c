#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include "trie.h"

#define TAM 26
 
/*
Aluno: João Victor Godinho Woitschach
Matricula: 2011401
*/


/*
Para melhor entendimento do codigo abaixo, deve-se levar em conta que os nós das letras foram inseridos na ordem de disponibilidade do espaço do vetor.
Ou seja, o indice [1] nao necessariamente representa a letra 'b', por exemplo
*/


Trie *criaNo(char v)
{
    Trie* novoNo = (Trie*) malloc(sizeof(Trie));

    novoNo->letra = v; //letra a ser inserida

    novoNo->termino = 1; //asumesse que seja a ultima letra
    for(int i = 0; i< TAM; i++){
        novoNo->filhos[i] = NULL; 
    }
    novoNo->ocupacao = 0;

    return novoNo;
}

Trie *criaTrie()
{
    Trie *t = criaNo(' ');
    t->termino = 1;
    return t;
}

//AUX
int encontraLetra(Trie* t, char target){ //funcao para encontrar o indice do filho de certo nó de certa letra

    for(int i = 0; i < t->ocupacao; i++){
        if(t->filhos[i] == NULL){
            return -1;
        }
        if(t->filhos[i]->letra == target)
            return i;
    }
    return -1;
}
//AUX

void inserePalavra(Trie *t, char *palavra) 
{
    if(*palavra == '\0'){
       // printf("fim da insercao, ultima letra da palavra: %c\n\n",t->letra);
        t->termino = 1; //talvez nao precise, pq o novo no ja nasce com a parada
        return;
    } else if(palavra == NULL)
        return;
        
    if(t->ocupacao == 0){
       // printf("Nao encontrei nenhum no existente, criando novo no para a letra %c\n",palavra[0]);
        Trie* nNo = criaNo(palavra[0]);
        nNo->termino = 0;
        t->filhos[t->ocupacao] = nNo;
        t->ocupacao++;
        return inserePalavra(t->filhos[t->ocupacao - 1],&palavra[1]);
    }

    int myIndex = encontraLetra(t,palavra[0]);

    if(myIndex != -1){ //caso encontre o indice
        //printf("Encontrei o indice! Nova chamada, proxima letra: %c\n\n",palavra[1]);
        return inserePalavra(t->filhos[myIndex],&palavra[1]); //se encontrou a palavra, passa pra proxima letra e nao precisa inserir

    }else{
       // printf("Nao encontrei o indice, criando novo no para a letra %c\n",palavra[0]);
        Trie* novoNo = criaNo(palavra[0]);
        novoNo->termino = 0;
        t->filhos[t->ocupacao] = novoNo; // o indice de ocupacao eh o proximo indice disponivel para inserir
        t->ocupacao++;
        return inserePalavra(t->filhos[t->ocupacao - 1],&palavra[1]);
        }
}


int buscarPalavra(Trie *t, char *palavra)
{
    if(palavra[0] == '\0'){
        //printf("fim da palavra, checando se termino == 1...\n");
        if(t->termino == 1){
            //printf("termino = 1, encontrei!\n");
            return 1;

        }
        else{
            //printf("termino != 1, nao encontrei\n");
            return 0;
        }
    }

    int myIndex = encontraLetra(t, palavra[0]);
    //printf("myIndex de %c: %d\n",palavra[0],myIndex);
    
    if(myIndex != -1){
        //printf("Encontrei o indice! Nova chamada, proxima letra: %c\n\n",palavra[1]);
        return buscarPalavra(t->filhos[myIndex],&palavra[1]);

    }
    else{
       // printf("nao encontrei o indice de %c\n",palavra[0]);
        return 0;
    }
}


Trie* buscarPrefixo(Trie *t, char *palavra)
{
    //printf("letra da vez: %c\n",palavra[0]);
    if(palavra == NULL)
        return NULL;
    
    if(*palavra == '\0'){
        //printf("encontrei! ultima letra do prefixo: %c\n",t->letra);
        return t;
    }
    
    //printf("buscando indice para %c\n",palavra[0]);
    int myIndex = encontraLetra(t,palavra[0]);
    //printf("valor de myindex: %d\n",myIndex);

    if(myIndex != -1){
        //printf("encontrei! indice para %c: %d\n",palavra[0],myIndex);
        buscarPrefixo(t->filhos[myIndex],&palavra[1]);
    }
    else{
        //printf("Nao encontrei seu prefixo, retornando nulo...\n");
        return NULL; //talvez exit(1) seja mais adequado ...?
    }
}
//AUX
char* slice(char* palavra, int ini, int fin){ //fatia string


    char* retorno = (char*) malloc(sizeof(char)*(fin - ini + 1));

    int i = 0;
    for(; i< fin; i++)
        *(retorno+i) = *(palavra+i);
    

    retorno[i] = '\0'; //isso aqui talvez de erro, e precise ser i+1, idk
    return retorno;
}

//AUX
 

void showFilhos(Trie* t){ //mostra os filhos de determinado no
    printf("ocupacao: %d\n",t->ocupacao);
    for(int i = 0; i< t->ocupacao; i++){
        printf("indice %d: letra: %c\n",i,t->filhos[i]->letra);
    }
    printf("\n");
}


void removerPalavra(Trie* t, char* palavra){

    int myIndex = encontraLetra(t,palavra[0]);
    //printf("letra de t: %c\n",t->letra);
    //printf("ocupacao de t: %d\n",t->ocupacao);
    //showFilhos(t);
    
    
    if(*palavra != '\0' && myIndex != -1){//ou seja, encontrou a palavra
        //printf("encontrei a letra %c !\n\n",t->filhos[myIndex]->letra);
        removerPalavra(t->filhos[myIndex],&palavra[1]);
        if(t->ocupacao <= 0){
            free(t);
        }
    }
    else if (myIndex == -1 && t->ocupacao > 0 && *palavra != '\0'){
       // printf("letra nao encontrada, a palavra nao existe\n");
        return;
    }
    
    if(*palavra == '\0'){ //essa condicional so acontece uma vez
        //printf("tirando o termino do ultimo no\n (%c)",t->letra);
        t->termino = 0;
    }
    
    if(t->ocupacao <= 0){ // vai cair aqui apenas quando nao tiver filhos
        //printf("dando free no noh: %c\n",t->letra);
    }
}


void alphabetize2(Trie * t, char prefixo[])
{
    int i;

    if (t->termino == 1){
        printf("%s\n", prefixo); 
    }

    for (i = 0; i < TAM; ++i)
    {
        if (t->filhos[i] != NULL)
        {
            char ch = t->filhos[i]->letra;
            
            int l = strlen(prefixo);
            if(l > 0){
                char novo_prefixo[TAM];
                strcpy(novo_prefixo, prefixo);
                strncat(novo_prefixo, &ch, 1); 
                alphabetize2(t->filhos[i], novo_prefixo);
            }
            else{
                char novo_prefixo[] = {ch, '\0'};
                alphabetize2(t->filhos[i], novo_prefixo);
            }
        }
    }
}

void alphabetize(Trie * t){
    char prefixo[] = "";
    alphabetize2(t, prefixo);
}

void liberar(Trie *t){
    
    int i;
    for (i = 0; i < TAM; ++i)
        if (t->filhos[i] != NULL)
            liberar(t->filhos[i]);
    
    free(t);
}