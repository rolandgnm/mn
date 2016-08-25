#include "stdio.h"
#include "stdlib.h"

/*
 * EP de Metodos Numericos
 * Alunos:
 *     Daniele Delmiro
 *     Joamila Brito
 *     Jonatas Cartaxo
 *     Roland Gabriel
 */

int main(void) {
    char opcao = '0';

    while (opcao != 'F') {
        /*
         * Menu Inicial
         */
        printf("\n‘C’ – Conversão, ‘S’ – Sistema Linear, ‘E’ – Equação Algébrica e ‘F’ – Finalizar: ");
        scanf("%s",&opcao);

        switch (opcao) {
            case 'C':
                printf("%c", opcao); // printfs devem ser substituidos pelas devidas funcoes.
                break;
            case 'S':
                printf("%c", opcao);
                break;
            case 'E':
                printf("%c", opcao);
                break;
            case 'F':
                return 0;
            default:
                printf("Erro! - Entrada desconhecida");
                break;
        }
    }

    return 0;
}