/*
873. Length of Longest Fibonacci Subsequence: https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/description/
Exercício resolvido por Diego Souza e Marcos Castilhos

Na nossa abordagem:
O problema pede a maior subsequência onde cada termo é a soma dos dois anteriores.
Testar todas as combinações seria inviável. Usamos Programação Dinâmica (DP)
para resolver em tempo O(N^2).

A ideia central é: Uma sequência de Fibonacci é definida pelos seus dois 
últimos números. Se sabemos o índice do penúltimo (Anterior) e do último (Atual),
podemos calcular exatamente qual valor precisava vir antes deles.

O algoritmo funciona da seguinte forma:
1.  Mapeamento Rápido (Hash Map): Criamos um mapa para relacionar 
    Valor -> Índice. Isso permite verificar se um número existe no array
    em tempo constante O(1), evitando varreduras repetitivas.
    
2.  Definição do Estado da DP: A tabela `tabelaDP[i][j]` armazena o 
    comprimento da sequência de Fibonacci que termina nos índices i e j.
    
3.  Iteração de Pares: Percorremos todos os pares possíveis de índices
    (Anterior, Atual).
    
4.  Cálculo do "Necessário": Para um par (Anterior, Atual) ser válido,
    deve existir um número X tal que: X + arr[Anterior] == arr[Atual].
    Logo, X (valorNecessario) = arr[Atual] - arr[Anterior].
    
5.  Transição e Atualização:
    - Verificamos se 'valorNecessario' existe no mapa e se é menor que o Anterior
      (para manter a ordem crescente estrita).
    - Se existir, estendemos a sequência: O tamanho da sequência terminando em
      (Anterior, Atual) será o tamanho da sequência que terminava em
      (Necessario, Anterior) + 1.
    - Se não havia sequência antes, começamos com tamanho 3 (Necessario, Anterior, Atual).
    
6.  Resultado: Mantemos uma variável global rastreando o maior valor encontrado na tabela.
*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int quantidadeElementos = arr.size();
        
        // 1. Mapear Valor -> Índice para busca rápida (O(1))
        // Isso elimina a necessidade de procurar o 'valorNecessario' com um loop.
        unordered_map<int, int> valorParaIndice;
        for (int i = 0; i < quantidadeElementos; i++) {
            valorParaIndice[arr[i]] = i;
        }

        // 2. Tabela de Programação Dinâmica (DP)
        // tabelaDP[indiceAnterior][indiceAtual] guarda o tamanho da sequência
        // que termina especificamente nesses dois índices.
        vector<vector<int>> tabelaDP(quantidadeElementos, vector<int>(quantidadeElementos, 0));
        
        int maiorTamanhoEncontrado = 0;

        // 3. Loop duplo para testar todos os pares possíveis (Anterior, Atual)
        // Onde 'indiceAnterior' vem sempre antes de 'indiceAtual'
        for (int indiceAtual = 0; indiceAtual < quantidadeElementos; indiceAtual++) {
            for (int indiceAnterior = 0; indiceAnterior < indiceAtual; indiceAnterior++) {
                
                // 4. Matemática da Fibonacci: Quem deveria vir antes?
                int valorNecessario = arr[indiceAtual] - arr[indiceAnterior];

                // Verificações de segurança:
                // a) O valor necessário é menor que o anterior? (Sequência deve ser crescente)
                // b) O valor necessário existe no nosso array original?
                if (valorNecessario < arr[indiceAnterior] && valorParaIndice.count(valorNecessario)) {
                    
                    int indiceDoNecessario = valorParaIndice[valorNecessario];

                    // 5. Lógica de Atualização da DP
                    // Se já existia uma sequência terminando em [Necessario, Anterior],
                    // nós apenas adicionamos mais um elemento (o Atual).
                    if (tabelaDP[indiceDoNecessario][indiceAnterior] == 0) {
                        // Caso base: Encontramos (Necessario, Anterior, Atual) pela primeira vez.
                        // Tamanho é 3.
                        tabelaDP[indiceAnterior][indiceAtual] = 3; 
                    } else {
                        // Estendemos a sequência existente.
                        tabelaDP[indiceAnterior][indiceAtual] = tabelaDP[indiceDoNecessario][indiceAnterior] + 1;
                    }

                    // Atualiza o recorde global
                    maiorTamanhoEncontrado = max(maiorTamanhoEncontrado, tabelaDP[indiceAnterior][indiceAtual]);
                }
            }
        }

        // Se maiorTamanhoEncontrado for menor que 3, a regra diz para retornar 0
        return maiorTamanhoEncontrado;
    }
};
