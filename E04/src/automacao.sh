#!/bin/bash

REPETICOES=10
COMPILADOR="gcc"
OTIMIZACOES=("-O0" "-O1" "-O2" "-O3" "-Os") 
PROGRAMAS=("nbody.c" "fannkuch-redux.c")
MATH_FLAG="-lm"
LOG_FILE="resultados_atividade_FINAL.csv"

measure_runtime() {
    local EXECUTAVEL=$1
    local REPETICOES=$2
    local INPUT_ARG=$3
    local TEMPOS_TOTAIS=0
    local VALID_RUNS=0

    # Verifica se o executável existe e é executável
    if [ ! -x "$EXECUTAVEL" ]; then
        echo "0.000000"
        return
    fi

    for ((i=1; i<=REPETICOES; i++)); do
        TMP_TIME_FILE=$(mktemp)

        # Executa e mede tempo real (stderr do time vai para TMP_TIME_FILE)
        /usr/bin/time -p "./$EXECUTAVEL" "$INPUT_ARG" 1>/dev/null 2> "$TMP_TIME_FILE"
        TEMPO_REAL=$(grep real "$TMP_TIME_FILE" | awk '{print $2}')
        rm -f "$TMP_TIME_FILE"

        # Valida se o tempo é numérico
        if [[ "$TEMPO_REAL" =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
            TEMPOS_TOTAIS=$(echo "$TEMPOS_TOTAIS + $TEMPO_REAL" | bc)
            VALID_RUNS=$((VALID_RUNS + 1))
        else
            echo "Aviso: falha na medição $i para $EXECUTAVEL (Tempo capturado: '$TEMPO_REAL')" >&2
        fi
    done

    if [ "$VALID_RUNS" -eq 0 ]; then
        echo "0.000000"
    else
        echo "scale=6; $TEMPOS_TOTAIS / $VALID_RUNS" | bc
    fi
}


echo "Programa,Otimizacao,Tempo_Compilacao_Real,Tamanho_Executavel_Bytes,Tempo_Execucao_Medio_${REPETICOES}x" > "$LOG_FILE"

cd "$(dirname "$0")"
for SRC_FILE in "${PROGRAMAS[@]}"; do
    CURRENT_LINK_FLAGS=""
    if [[ "$SRC_FILE" == "nbody.c" ]]; then
        INPUT_ARG="100000000"
        CURRENT_LINK_FLAGS="$MATH_FLAG"
    elif [[ "$SRC_FILE" == "fannkuch-redux.c" ]]; then
        INPUT_ARG="12"
    fi

    for OPT in "${OTIMIZACOES[@]}"; do
        FLAG_NAME="${OPT:1}"
        OUTPUT_FILE="${SRC_FILE%.*}_${FLAG_NAME}.x"

        echo "Compilando $SRC_FILE com $OPT ..."
        COMP_TIME_OUTPUT=$(/usr/bin/time -f "%e" $COMPILADOR $OPT "$SRC_FILE" -o "$OUTPUT_FILE" $CURRENT_LINK_FLAGS 2>&1 >/dev/null)
        COMP_TIME_REAL="$COMP_TIME_OUTPUT"

        if [ -f "$OUTPUT_FILE" ]; then
            SIZE_BYTES=$(stat -c "%s" "$OUTPUT_FILE")
        else
            SIZE_BYTES="ERRO"
            RUNTIME_AVG="ERRO"
            continue
        fi

        echo "Executando $OUTPUT_FILE ($REPETICOES vezes)..."
        RUNTIME_AVG=$(measure_runtime "$OUTPUT_FILE" "$REPETICOES" "$INPUT_ARG")

        echo "\"$SRC_FILE\",\"$FLAG_NAME\",\"$COMP_TIME_REAL\",\"$SIZE_BYTES\",\"$RUNTIME_AVG\"" >> "$LOG_FILE"
    done
done
