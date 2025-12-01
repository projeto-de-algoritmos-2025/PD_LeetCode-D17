// exercício resolvido por Diego Souza e Marcos Castilhos
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        // Direções possíveis do cavalo (r, c)
        vector<pair<int, int>> directions = {
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
        };

        // DP[r][c] armazena a probabilidade do cavalo estar na célula (r, c)
        // Inicializamos com 0.0
        vector<vector<double>> dp(n, vector<double>(n, 0.0));
        
        // Caso base: no passo 0, a probabilidade é 100% na posição inicial
        dp[row][column] = 1.0;

        // Loop para cada um dos K movimentos
        for (int step = 0; step < k; ++step) {
            // Novo tabuleiro para o próximo passo (evita poluição de estado)
            vector<vector<double>> new_dp(n, vector<double>(n, 0.0));
            
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < n; ++c) {
                    // Se a probabilidade atual for 0, não há nada para espalhar
                    if (dp[r][c] > 0.0) {
                        for (auto& dir : directions) {
                            int next_r = r + dir.first;
                            int next_c = c + dir.second;

                            // Verificação de borda (Boundary Check)
                            if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n) {
                                // A probabilidade se divide por 8 para cada movimento possível
                                new_dp[next_r][next_c] += dp[r][c] / 8.0;
                            }
                        }
                    }
                }
            }
            // Atualizamos o estado do mundo
            dp = new_dp;
        }

        // Somatório final de todas as probabilidades restantes no tabuleiro
        double total_prob = 0.0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                total_prob += dp[i][j];
            }
        }
        return total_prob;
    }
};