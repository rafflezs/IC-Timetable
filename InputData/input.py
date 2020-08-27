import pandas as pd
xls = pd.ExcelFile('Input.xlsx')
for sheet_name in xls.sheet_names:
    xls.parse(sheet_name).to_csv ("./"+sheet_name+".csv", sep=";")