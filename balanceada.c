#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

bool balanceada(char *sequencia) {
    bool isBalanceada = true;
    PILHA *pilhaAux = pilha_criar(); //criacao da pilha que armazena a sequencia

    //laco para cada elemento da sequencia
    for(unsigned int i = 0; sequencia[i] != '\0' ; ++i) { 
        if(sequencia[i] == '{' || sequencia[i] == '[' || sequencia[i] == '(') //se o caractere simbolizar uma abertura, ele é empilhado
            pilha_empilhar(pilhaAux, item_criar(sequencia[i]));
        else { //caso contrario, ele deve corresponder ao ultimo caractere aberto
            
            /*Solução elementar
            ITEM *itemAux = pilha_desempilhar(pilhaAux);
            switch( item_get_chave(itemAux) ) {
                case '{':
                    if (sequencia[i] != '}') isBalanceada = false;
                    break;
                case '[':
                    if (sequencia[i] != ']') isBalanceada = false;
                    break;
                case '(':
                    if (sequencia[i] != ')') isBalanceada = false;
                    break;
                default: 
                    isBalanceada = false
            }
            item_apagar(&itemAux);
            */

            /* Analogamente, por meior dos valores da tabela ASCII para cada caractere de abertura e seu correspondente fechamento:
                '(' 40 e ')' 41
                '[' 91 e ']' 93
                '{' 123 e '}' 125
                é possível perceber que o fechamento corresponde ao próximo número ímpar a partir do número do caractere de abertura

                assim:
            */

            ITEM *itemAux = pilha_desempilhar(pilhaAux);
            if( (sequencia[i] - 1) != (item_get_chave(itemAux) + itemAux % 2) )
                isBalanceada = false;
            item_apagar(&itemAux);

            if(!isBalanceada) { //caso seja descoberto que a sequencia não esta balanceada em alguma iteraçao
                while(!pilha_vazia(pilhaAux)) {
                    item_apagar(&pilha_desempilhar(pilhaAux));
                }
                pilha_apagar(&pilhaAux);
                return false;
            }
        }
    }

    //se todos os caracteres abertos foram fechados e se todos os caracteres corresponderam a caracteres abertos, a sequencia está balanceada
    if(pilha_vazia(pilhaAux)) {
        pilha_apagar(&pilhaAux);
        return true;
    } else { //caso contrario, caracteres abertos nao foram fechados, sequencia nao balanceada
        while(!pilha_vazia(pilhaAux)) {
            item_apagar(&pilha_desempilhar(pilhaAux));
        }
        pilha_apagar(&pilhaAux);
        return false;
    }
}