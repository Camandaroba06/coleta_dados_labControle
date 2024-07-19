import pandas as pd

# Leitura dos arquivos CSV
df_tempo_valor = pd.read_csv("dados_1500RPM_clonartempo.csv")
df_pwm_rpm = pd.read_csv("dados_PWM_e_RPM2.csv")

# Supondo que os arquivos são:
# arquivo_tempo_valor.csv: colunas ['Tempo', 'ValorAleatorio']
# arquivo_pwm_rpm.csv: colunas ['PWM', 'RPM']

# Criando um DataFrame combinado, mantendo a coluna de Tempo e adicionando PWM e RPM
df_combinado = pd.concat([df_tempo_valor["Tempo (s)"], df_pwm_rpm], axis=1)

# Salvando o DataFrame combinado em um novo arquivo CSV
df_combinado.to_csv("arquivo_combinado.csv", index=False)

print("Arquivo combinado salvo com sucesso!")
