# Análise de Fatores com DOE $2^k$ em Python

Este projeto aplica **Design of Experiments (DOE)** para avaliar a influência de **k fatores** (2 níveis cada) em uma variável resposta, utilizando **Python** para análise estatística. O método baseia-se em um planejamento fatorial completo **$2^k$**, que permite investigar efeitos principais e interações entre fatores.

A implementação em Python calcula automaticamente cada efeito pela **diferença das médias** da resposta nos níveis alto e baixo de cada fator. Adicionalmente, quantifica a contribuição de cada efeito para a variabilidade total por meio da **soma dos quadrados**, obtida multiplicando o quadrado do efeito pelo número total de ensaios (**$2^k$**). Essa abordagem identifica de forma eficiente os fatores estatisticamente significativos para a otimização do processo.

# Referências
[statistics-calculator/design-of-experiments](https://datatab.net/statistics-calculator/design-of-experiments)

[Full Factorial Design (DoE - Design of Experiments) Simply explained](https://youtu.be/cHoYAyYHzB0?si=s16XRS7J3Qde-8iv)

[Understanding full factorial design](https://youtu.be/92dMuk661vw?si=cBOZnxNCTAWTxwKz)

[Datasets](https://www.itl.nist.gov/div898/software/dataplot/datasets.htm)

