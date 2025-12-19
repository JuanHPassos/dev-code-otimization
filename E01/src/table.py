import itertools
import gspread
from google.oauth2.service_account import Credentials

def gerar_tabela_fatorial(k, sheet_name="Fatorial"):
    # gera todas as combinações possíveis (-1, +1)
    fatores = list(itertools.product([-1, 1], repeat=k))
    
    # conecta ao Google Sheets
    creds = Credentials.from_service_account_file("credenciais.json", scopes=["https://www.googleapis.com/auth/spreadsheets"])
    client = gspread.authorize(creds)

    # abre a planilha (substitua pelo ID da sua planilha)
    spreadsheet = client.open_by_key("SEU_SPREADSHEET_ID")

    # cria ou abre a aba
    try:
        sheet = spreadsheet.worksheet(sheet_name)
        sheet.clear()
    except gspread.exceptions.WorksheetNotFound:
        sheet = spreadsheet.add_worksheet(title=sheet_name, rows="100", cols=str(k))

    # prepara cabeçalho
    header = [f"Fator {i+1}" for i in range(k)]
    dados = [header] + [list(linha) for linha in fatores]

    # escreve na planilha
    sheet.update("A1", dados)
    print(f"Tabela 2^{k} gerada com sucesso na aba '{sheet_name}'.")

# exemplo de uso
gerar_tabela_fatorial(3)
