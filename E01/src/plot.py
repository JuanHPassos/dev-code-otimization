import pandas as pd
import matplotlib.pyplot as plt

# Mapeamento dos fatores para nomes curtos
factor_map = {
    'TEMPERATURE': 'X1',
    'CONCENTRATION': 'X2',
    'CATALYST': 'X3',
    'CONCENTRATION*TEMPERATURE': 'X1*X2',
    'CATALYST*TEMPERATURE': 'X1*X3',
    'CATALYST*CONCENTRATION': 'X2*X3',
    'CATALYST*CONCENTRATION*TEMPERATURE': 'X1*X2*X3'
}

# Dados
data = pd.DataFrame({
    'Factor': list(factor_map.keys()),
    'Response': [11.5, -2.5, 0.75, 0.75, 5, 0, 0.25]
})

# Substitui pelos nomes curtos
data['Short'] = data['Factor'].map(factor_map)

# Plotagem
plt.figure(figsize=(9, 6))
colors = ['steelblue'] * 3 + ['orange'] * 3 + ['green']  # principais, 2-way, 3-way

plt.bar(data['Short'], data['Response'], color=colors)
plt.title("Main Effects and Interactions", fontsize=14)
plt.xlabel("Factors", fontsize=12)
plt.ylabel("Response", fontsize=12)
plt.axhline(0, color='black', linewidth=0.8)

# Legenda explicando X1, X2, X3
plt.legend(
    handles=[
        plt.Rectangle((0, 0), 1, 1, color='steelblue', label='Main Effects'),
        plt.Rectangle((0, 0), 1, 1, color='orange', label='2-Way Interactions'),
        plt.Rectangle((0, 0), 1, 1, color='green', label='3-Way Interaction')
    ],
    title="Legend", loc="upper right"
)

# Explicação extra dos fatores (subido para dentro da área visível)
factor_labels = ["X1 = Temperature", "X2 = Concentration", "X3 = Catalyst"]
plt.figtext(0.05, 0.01, "\n".join(factor_labels), ha="left", fontsize=10)

plt.tight_layout()
plt.show()
