import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import sys

# --- Configurações ---
CSV_FILE = 'resultados_matriz.csv'
OUTPUT_IMAGE = 'grafico_benchmark_tempo.png'
OUTPUT_IMAGE_LOG = 'grafico_benchmark_tempo_log.png'

# --- Carregar e Processar os Dados ---
try:
    df = pd.read_csv(CSV_FILE)
except FileNotFoundError:
    print(f"Erro: Arquivo '{CSV_FILE}' não encontrado.", file=sys.stderr)
    print("Por favor, rode o script de benchmark primeiro.", file=sys.stderr)
    sys.exit(1)

# 1. Filtrar apenas as linhas que contêm a 'Media'
df_medias = df[df['Run_ID'] == 'Media'].copy()

if df_medias.empty:
    print(f"Erro: Nenhuma linha com 'Run_ID' == 'Media' foi encontrada em '{CSV_FILE}'.", file=sys.stderr)
    sys.exit(1)

# 2. Converter tempo para numérico (segundos)
df_medias['Tempo_Execucao_s'] = pd.to_numeric(df_medias['Tempo_Execucao_s'])

# 3. Ordenar para melhor visualização (do mais lento para o mais rápido)
df_medias = df_medias.sort_values(by='Tempo_Execucao_s', ascending=False)

# --- Criar o Gráfico Principal (Escala Linear) ---
print(f"Gerando gráfico principal: {OUTPUT_IMAGE}...")
plt.figure(figsize=(10, 7))
sns.set_theme(style="whitegrid")

# Gráfico de Barras
barplot = sns.barplot(
    x='Tipo_Execucao',
    y='Tempo_Execucao_s',
    data=df_medias,
    palette='viridis'
)

plt.title('Comparação do Tempo Médio de Execução (GEMM N=1024)', fontsize=16, pad=20)
plt.xlabel('Versão do Código (Compilação)', fontsize=12)
plt.ylabel('Tempo de Execução Médio (Segundos)', fontsize=12)
plt.xticks(rotation=0, ha='center')

# Adicionar o valor exato em cima de cada barra
for p in barplot.patches:
    barplot.annotate(f'{p.get_height():.3f} s',
                     (p.get_x() + p.get_width() / 2., p.get_height()),
                     ha='center', va='center',
                     xytext=(0, 9),
                     textcoords='offset points')

# Salvar o gráfico
plt.tight_layout()
plt.savefig(OUTPUT_IMAGE)
print("Gráfico principal salvo.")

# --- Criar o Gráfico Secundário (Escala Log) ---
# Essencial para ver a diferença entre as versões rápidas
print(f"Gerando gráfico logarítmico: {OUTPUT_IMAGE_LOG}...")
plt.figure(figsize=(10, 7))

barplot_log = sns.barplot(
    x='Tipo_Execucao',
    y='Tempo_Execucao_s',
    data=df_medias,
    palette='rocket'
)

# Aplicar Escala Logarítmica
plt.yscale('log')
plt.title('Comparação do Tempo Médio (Escala Logarítmica)', fontsize=16, pad=20)
plt.xlabel('Versão do Código (Compilação)', fontsize=12)
plt.ylabel('Tempo Médio (Segundos - Escala Log)', fontsize=12)
plt.xticks(rotation=0, ha='center')

# Adicionar o valor exato (formatação um pouco diferente para log)
for p in barplot_log.patches:
    if p.get_height() > 0:
        barplot_log.annotate(f'{p.get_height():.3f} s',
                             (p.get_x() + p.get_width() / 2., p.get_height()),
                             ha='center', va='center',
                             xytext=(0, 9),
                             textcoords='offset points')

# Salvar o gráfico logarítmico
plt.tight_layout()
plt.savefig(OUTPUT_IMAGE_LOG)
print("Gráfico logarítmico salvo.")
print("Processo concluído.")