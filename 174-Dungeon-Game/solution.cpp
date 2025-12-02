/*
174. Dungeon Game: https://leetcode.com/problems/dungeon-game/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Abordagem: Programação Dinâmica Inversa.
Em vez de simular o cavaleiro indo do início ao fim, calculamos a "vida mínima necessária"
começando da princesa e voltando até a entrada.

Lógica:
1. Para entrar em uma sala, o cavaleiro precisa ter vida suficiente para:
   a) Sobreviver a sala atual.
   b) Ter vida restante suficiente para entrar na próxima sala (seja direita ou baixo).
   
2. Fórmula: VidaNecessaria = (Mínimo exigido pelo próximo passo) - (O que a sala atual oferece).
   - Se a sala dá vida (+30), precisamos de menos vida antes de entrar.
   - Se a sala tira vida (-10), precisamos de mais vida antes de entrar.
   
3. Regra de Ouro: A vida necessária nunca pode ser menor que 1. Se a fórmula der 0 ou negativo
   (significando que a sala cura tudo o que precisamos), ajustamos para 1.
*/

#include <vector>
#include <algorithm>
#include <climits> // Para usar INT_MAX

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int linhas = dungeon.size();
        int colunas = dungeon[0].size();

        // Criamos uma tabela DP com uma linha e uma coluna extra.
        // Inicializamos com INT_MAX (infinito) para representar as "paredes" onde não podemos ir.
        vector<vector<int>> saudeNecessaria(linhas + 1, vector<int>(colunas + 1, INT_MAX));

        // Ponto de partida REVERSO (Base da DP):
        // Para "sair" da posição da princesa (chegar vivo), precisamos de no mínimo 1 de vida.
        // Colocamos 1 nas posições vizinhas virtuais da princesa (abaixo e à direita dela).
        saudeNecessaria[linhas][colunas - 1] = 1;
        saudeNecessaria[linhas - 1][colunas] = 1;

        // Loop Reverso: Começa da princesa (última sala) e volta até o cavaleiro (0,0)
        for (int i = linhas - 1; i >= 0; i--) {
            for (int j = colunas - 1; j >= 0; j--) {
                
                // 1. Olhamos para o futuro: Qual o caminho exige menos vida? Ir para Direita ou Baixo?
                int menorCustoProximo = min(saudeNecessaria[i + 1][j], saudeNecessaria[i][j + 1]);
                
                // 2. Calculamos a vida necessária AQUI baseada no futuro.
                // Fórmula: O que preciso lá na frente - O que ganho/perco nesta sala atual.
                int vidaNecessariaAqui = menorCustoProximo - dungeon[i][j];

                // 3. A vida nunca pode ser menor que 1.
                // Se 'vidaNecessariaAqui' for <= 0, significa que a sala cura o suficiente.
                // Mesmo assim, precisamos chegar nela vivos, então forçamos no mínimo 1.
                saudeNecessaria[i][j] = max(1, vidaNecessariaAqui);
            }
        }

        // O resultado final estará na posição inicial (0,0), dizendo quanto precisamos para começar a jornada.
        return saudeNecessaria[0][0];
    }
};
