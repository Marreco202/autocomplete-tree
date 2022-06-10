#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include "trie.h"

#define TAM 26 //sei la oq é esse tamanho, mas parece importante
 

Trie *criaNo(char v)
{
    Trie* novoNo = (Trie*) malloc(sizeof(Trie));

    novoNo->letra = v; //letra a ser inserida

    novoNo->termino = 1; //asumesse que seja a ultima letra
    novoNo->filhos[0] = NULL;
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
int encontraLetra(Trie filhos[], char target){

    for(int i = 0; i <26; i++){
        if(filhos[i].letra == target)
            return i;
    }
    return -1;
}
//AUX

void inserePalavra(Trie *t, char *palavra)
{
    if(palavra == '\0'){
        t->termino = 1; //talvez nao precise, pq o novo no ja nasce com a parada
        return;
    } else if(palavra == NULL)
        return;
    
    int myIndex = encontraLetra(t->filhos,palavra[0]);

    if(myIndex != -1){
        inserePalavra(t->filhos[myIndex],&palavra[1]); //se encontrou a palavra, passa pra proxima letra e nao precisa inserir

    }else{
        Trie* novoNo = criaNo(palavra[0]);
        novoNo->termino = 0;
        t->filhos[t->ocupacao] = novoNo; // o indice de ocupacao eh o proximo indice disponivel para inserir
        t->ocupacao++;
        inserePalavra(t->filhos[t->ocupacao - 1],&palavra[1]);
        }
}


int buscarPalavra(Trie *t, char *palavra)
{
    if(palavra == NULL)
        return;

    if(palavra == '\0'){
        if(t->termino)
            return 1;
        else
            return 0;
    }

    int myIndex = encontraLetra(t->filhos, palavra[0]);

    if(myIndex != -1)
        buscarPalavra(t->filhos[myIndex],&palavra[1]);
    else
        return 0;
}


Trie* buscarPrefixo(Trie *t, char *palavra)
{
  /* implementar busca por prefixo */
}

void removerPalavra(Trie *t, char *palavra)
{
 /* implementar remoca de palavras */
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
                char novo_prefixo[l];
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