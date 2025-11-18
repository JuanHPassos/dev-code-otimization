#!/bin/bash

# --- Configurações ---
REPETICOES=10
EXECUTAVEL=$1 
LABEL=$2      
CSV_FILE="resultados_matriz.csv" 

# --- Validação ---
if [ -z "$EXECUTAVEL" ] || [ -z "$LABEL" ]; then
    echo "Uso: $0 <caminho_executavel> <rotulo_csv>"
    echo "Exemplo: $0 ./matrix_scalar_app scalar_O0"
    echo "Exemplo: $0 ./matrix_avx_app avx_O3_manual"
    exit 1
fi

if [ ! -x "$EXECUTAVEL" ]; then
    echo "Erro: Executável '$EXECUTAVEL' não encontrado."
    exit 1
fi

# --- Cria o Cabeçalho do CSV (se não existir) ---
if [ ! -f "$CSV_FILE" ]; then
    echo "Tipo_Execucao,Run_ID,Tempo_Execucao_s" > "$CSV_FILE"
fi

echo "--- Iniciando Benchmark: $LABEL ---"
echo "Executando $REPETICOES vezes... Salvo em $CSV_FILE"

TOTAL_TIME=0

# --- Loop de Execução ---
for ((i=1; i<=$REPETICOES; i++)); do
    
    
    TEMPO_EXEC=$($EXECUTAVEL) 
    
    # Validação da saída
    if [[ ! "$TEMPO_EXEC" =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
        echo "Erro na Run $i: Saída inesperada do programa: '$TEMPO_EXEC'"
        continue
    fi

    # 1. Salva a execução individual no CSV
    echo "$LABEL,Run_$i,$TEMPO_EXEC" >> "$CSV_FILE"

    # 2. Soma para a média (usando 'bc' para ponto flutuante)
    TOTAL_TIME=$(echo "scale=6; $TOTAL_TIME + $TEMPO_EXEC" | bc)
    
    echo "Run $i: $TEMPO_EXEC s"
done


MEDIA=$(echo "scale=6; $TOTAL_TIME / $REPETICOES" | bc)

# 3. Salva a Média no CSV
echo "$LABEL,Media,$MEDIA" >> "$CSV_FILE"

echo "----------------------------------------"
echo "Benchmark Concluído para: $LABEL"
echo "Média de 10 execuções: $MEDIA s"
echo "----------------------------------------"