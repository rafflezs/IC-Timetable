import pandas as pd
print("Digite o nome do arquivo-instancia")
fileName = input()
xls = pd.ExcelFile(fileName)
for sheet_name in xls.sheet_names:
    teste = xls.parse(sheet_name)
    teste.to_csv ("./"+sheet_name+".csv", sep=";",encoding='utf-8', index = False)