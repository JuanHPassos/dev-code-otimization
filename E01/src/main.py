"""
Projeto Fatorial 2^k

Programa que permite analisar o desempenho de sistemas com n fatores,
sendo que cada fator possui apenas 2 níveis (-1 e 1). 

O código gera a matriz de efeitos e resolve um sistema linear para obter
os coeficientes dos efeitos principais e de interação.
"""
import numpy as np
import itertools


def gerar_tabela_fatores(k: int) -> np.ndarray:
    """
    Gera a tabela de fatores para um experimento 2^k.

    Cada linha representa uma combinação dos fatores em níveis -1 e 1.

    Args:
        k (int): Número de fatores.

    Returns:
        np.ndarray: Matriz (2^k x k) com as combinações de fatores.
    """
    mat = np.empty((0, k))

    for i in range(2 ** k):
        linha = np.full(k, -1)
        aux_bin = i
        pos = 0
        while aux_bin != 0:
            if aux_bin % 2:
                linha[pos] = 1
            pos += 1
            aux_bin = aux_bin // 2

        mat = np.append(mat, [linha], axis=0)

    return mat


def gerar_coef(k: int, mat: np.ndarray) -> np.ndarray:
    """
    Gera a matriz de coeficientes para efeitos de um experimento 2^k.

    Para cada linha da matriz de fatores, calcula todos os produtos possíveis
    dos subconjuntos de 1 até k elementos.

    Args:
        k (int): Número de fatores.
        mat (np.ndarray): Matriz de fatores (2^k x k).

    Returns:
        np.ndarray: Matriz de coeficientes (2^k x 2^k).
    """
    mat_coef = np.empty((2 ** k, 2 ** k))

    for i in range(len(mat)):
        j = 0
        for r in range(len(mat[i]) + 1):
            for comb in itertools.combinations(mat[i], r):
                # Produto do subconjunto ou 1 se vazio
                mat_coef[i][j] = np.prod(comb) if comb else 1
                j += 1

    return mat_coef


def calcular_sst(e_feitos: np.ndarray, k: int) -> float:
    """
    Calcula a soma dos quadrados totais (SST) para um experimento 2^k.

    Args:
        e_feitos (np.ndarray): Vetor com os coeficientes de efeitos (efeitos principais e interações).
        k (int): Número de fatores.

    Returns:
        float: Valor do SST.
    """
    # Cada efeito é multiplicado por 2^(k)
    n_replicatas = 2**(k)
    sst = n_replicatas * np.sum(e_feitos**2)
    return sst

def calcular_influencia(e_feitos: np.ndarray, k: int, sst_total: float) -> np.ndarray:
    """
    Calcula a influência dos fatores.

    Args:
        e_feitos (np.ndarray): Vetor com os coeficientes de efeitos (efeitos principais e interações).
        k (int): Número de fatores.

    Returns:
        np.ndarray: valores da influência.
    """
    variacao = np.empty(len(e_feitos))
    n_replicatas = 2**(k)
    # Variação da resposta não tem influência
    variacao[0] = 0
    for i in range(1, len(e_feitos)):
        ss_i = n_replicatas*(e_feitos[i]**2)
        variacao[i] = ss_i/sst_total
    
    return variacao

def main():
    k = 3  # Número de fatores
    mat = gerar_tabela_fatores(k)
    A = gerar_coef(k, mat)

    # Resultados observados do experimento
    # OBS: (Preencha na ordem binária LST -> MST)
    # OBS: deve usar um array para casa variável resposta
    a = np.array([60, 72, 54, 68, 52, 83, 45, 80])

    # Resolve o sistema linear A * x = a
    x = np.linalg.solve(A, a)

    print("Coeficientes do experimento:")
    print(x)
    
    # Calcula SST total
    sst_total = calcular_sst(x, k)
    
    # Calcular a influência dos fatores
    variacao = calcular_influencia(x, k, sst_total)
    porcentagens = (variacao / variacao.sum()) * 100

    # Forma simples com 2 casas decimais
    for i, pct in enumerate(porcentagens):
        print(f"Componente {i+1}: {pct:.2f}%")

if __name__ == "__main__":
    main()
