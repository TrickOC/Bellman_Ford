#include <iostream>
#include <vector>
#include <list>

int main() {
    int n, m, b, i, vo, vd, p;

    std::cin >> n >> m >> b >> i;
    std::vector<std::vector<std::pair<int, int>>> vertices(n, std::vector<std::pair<int, int>>());

    for (int j = 0; j < m; j++) {
        std::cin >> vo >> vd >> p;
        vertices[vo-1].emplace_back(vd-1,p);
    }

    int passos[n];
    passos[i-1] = 0;
    std::vector<int> peso(n, 1e9);
    peso[i-1] = 0;

    for (int j = 0; j < n-1; j++) {
        bool alt = false;
        for (int k = 0; k < n; k++)
            if (peso[k] != 1e9)
                for (auto &[vd, p] : vertices[k]) {
                    if (peso[k]+p >= peso[vd]) continue;
                    peso[vd] = peso[k]+p;
                    alt = true;
                    passos[vd] = k;
                }
        if (!alt) break;
    }

    bool neg = false;
    for (int l = 0; l < n; l++)
        if (peso[l] != 1e9)
            for (auto &[vd, p] : vertices[l])
                if (peso[vd] > peso[l]+p)
                    neg = true;

    if (neg)
        std::cout << "ERRO: CICLO DE CUSTO NEGATIVO!" << std::endl;
    else {
        int v;
        std::list<int> aux;
        for (int l = 0; l < n; l++) {
            if (l == i-1) continue;
            v = l;
            std::cout << l+1 << " (" << peso[l] << "): " << i;
            while (passos[v] != i-1) {
                aux.emplace_front(passos[v]);
                v = passos[v];
            }
            for (auto passo : aux)
                std::cout << " " << passo+1;
            std::cout << " " << l+1 << std::endl;
            aux.clear();
        }
    }

    return 0;
}