#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

bool balanceada(char *sequencia) {
    PILHA *pilhaAux = pilha_criar(); //criacao da pilha que armazena a sequencia

    for(unsigned int i = 0; sequencia[i] != '\0' ; ++i) { //laco para cada elemento da sequencia
        if(sequencia[i] == '{' || sequencia[i] == '[' || sequencia[i] == '(') //se o caractere simbolizar uma abertura, ele é empilhado
            pilha_empilhar(pilhaAux, item_criar(sequencia[i]));
        else  //caso contrario, ele deve corresponder ao ultimo caractere aberto
            
            /*Solução elementar

            switch( item_get_chave(pilha_desempilhar(pilhaAux)) ) {
                case '{':
                    if (sequencia[i] != '}') return false;
                    break;
                case '[':
                    if (sequencia[i] != ']') return false;
                    break;
                case '(':
                    if (sequencia[i] != ')') return false;
                    break;
                default: 
                    return false;
            }
            */

            /* Analogamente, por meior dos valores da tabela ASCII para cada caractere de abertura e seu correspondente fechamento:
                '(' 40 e ')' 41
                '[' 91 e ']' 93
                '{' 123 e '}' 125
                é possível perceber que o fechamento corresponde ao próximo número ímpar a partir do número do caractere de abertura

                assim:
            */
           if( (sequencia[i] - 1) != (item_get_chave(pilha_desempilhar(pilhaAux)) + item_get_chave(pilha_desempilhar(pilhaAux)) % 2) )
            return false;
    }

    //se todos os caracteres abertos foram fechados e se todos os caracteres corresponderam a caracteres abertos, a sequencia está balanceada
    if(pilha_vazia(pilhaAux))
        return true;
}