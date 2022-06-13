#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include "trie.h"

#define TAM 26
 
 

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
int encontraLetra(Trie* t, char target){

    for(int i = 0; i < TAM; i++){
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

    if(myIndex != -1){
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
        printf("nao encontrei o indice de %c\n",palavra[0]);
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
char* slice(char* palavra, int ini, int fin){


    char* retorno = (char*) malloc(sizeof(char)*(fin - ini + 1));

    int i = 0;
    for(; i< fin; i++)
        *(retorno+i) = *(palavra+i);
    

    retorno[i] = '\0'; //isso aqui talvez de erro, e precise ser i+1, idk
    return retorno;
}

//AUX

void antigaremoverPalavra(Trie *t, char *palavra)
{
    int len = strlen(palavra);

    for(int i = 0; i< len; i++){ //talvez len - 1

        char* manipulada = slice(palavra,0, len - i);
        printf("my slice: %s",manipulada);
        Trie* toRemove = buscarPrefixo(t,manipulada); //nó a ser removido

      
        printf("hello there!\n");
        if(toRemove->termino == 0 && toRemove->ocupacao == 0)
            liberar(toRemove);
        
    }
}   

void removerPalavra(Trie* t, char* palavra){

    if(t->letra != palavra[0]){
        //printf("palavra nao existe");
        return;
    }

    else if(*palavra!= '\0'){
        printf("step %c\n",t->letra);
        int myIndex = encontraLetra(t,palavra[0]);

        removerPalavra(t->filhos[myIndex],&palavra[1]);
    }
    else if(*palavra == '\0'){
        t->termino = 0; // se nos quisermos tirar a palavra "car", porem temos a palavra "carro", precisamos trocar apenas o termino
    }

    if(t->ocupacao == 0){
        free(t);
        return;
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