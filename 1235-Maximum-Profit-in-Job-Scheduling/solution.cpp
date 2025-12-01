// exercício resolvido por Diego Souza e Marcos Castilhos
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
private:
    struct Job {
        int start, end, profit;
    };

    // Comparador estático para ordenar apenas pelo tempo de término
    static bool compareJobs(const Job& a, const Job& b) {
        return a.end < b.end;
    }

public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<Job> jobs(n);

        // 1. Unificar os dados em uma estrutura
        for (int i = 0; i < n; ++i) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }

        // 2. Ordenar baseando-se no tempo de término (Greedy approach prep)
        sort(jobs.begin(), jobs.end(), compareJobs);

        // 3. DP + Busca Binária
        // dp[i] armazenará o lucro máximo possível considerando até o trabalho i
        // No entanto, para facilitar a busca por tempo, usaremos um vetor de pares 
        // ou map. Aqui, para performance pura e alinhamento com a busca binária,
        // vamos usar um vetor que guarda {endTime, maxProfitSoFar}
        
        // dp[0] = {0, 0} -> tempo 0, lucro 0 (sentinela)
        vector<pair<int, int>> dp;
        dp.push_back({0, 0});

        for (auto& job : jobs) {
            // Queremos encontrar o índice no DP onde o job.start se encaixa.
            // upper_bound retorna o primeiro elemento que é MAIOR que o valor buscado.
            // Buscamos um job que terminou logo antes ou exatamente quando este começa.
            
            // Queremos o último índice 'i' tal que dp[i].endTime <= job.start.
            // upper_bound com {job.start, infinity} vai achar o primeiro > job.start.
            // O elemento anterior a esse iterador é o nosso alvo.
            auto it = upper_bound(dp.begin(), dp.end(), make_pair(job.start, 2000000000)); // INT_MAX safe
            it--; // Voltamos um para pegar o <= job.start
            
            int currentProfit = job.profit + it->second;
            int maxProfitSoFar = dp.back().second;

            if (currentProfit > maxProfitSoFar) {
                dp.push_back({job.end, currentProfit});
            }
        }

        return dp.back().second;
    }
};