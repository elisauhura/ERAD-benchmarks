import os, math
import subprocess
import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt

NUM_EXPERIMENTS = 30


def proccess_file(df, lang):
    data  = { 'language':lang }
    
    f     = open('results/{}.out'.format(lang))

    line = f.readline()
    line = f.readline()

    for i in range (NUM_EXPERIMENTS):
      if 'real' in line:
        # Trata a linha com a informação do tempo real
        line = line.strip().split()
        time = line[1].split("m")
        seg = time[1].split("s")
        seg = seg[0].replace(',', '.')
        time2 = float(time[0])*60 + float(seg)
        data['real'] = time2
        # Trata a linha com a informação do tempo user
        line = f.readline()
        line = line.strip().split()
        time = line[1].split("m")
        seg = time[1].split("s")
        seg = seg[0].replace(',', '.')
        time2 = float(time[0])*60 + float(seg)          
        data['user'] = time2
        # Trata a linha com a informação do tempo sys
        line = f.readline()
        line = line.strip().split()
        time = line[1].split("m")
        seg = time[1].split("s")
        seg = seg[0].replace(',', '.')
        time2 = float(time[0])*60 + float(seg)
        data['sys'] = time2
        line = f.readline()
        line = f.readline()
        df = df.append(data, ignore_index=True)
      
    f.close()

    return df

def proccess_data():
    languages = ['C', 'Python', 'Go'] 

    # Criando o DataFrame a ser populado
    column_names = ['real', 'user', 'sys']
    df = pd.DataFrame(columns = column_names)

    # Insere as informações de cada arquivo de resultado
    for lang in languages:
      df = proccess_file(df,lang)

    return df


def processs_results(df):
    
    languages = ['C', 'Python', 'Go'] 
    metrics = ['real', 'user', 'sys']

    # Gerando Box plot dos gráficos de maneira simples e calculando o intervalo de confiança 
    for lang in languages:
        if lang == 'C':
          str_option = 'C'
        elif lang == 'Python':
          str_option = 'Python'
        elif lang == 'Go':
          str_option = 'Go'

        print("Gerando Imagens para Linguagem {}".format(str_option))
        
        temp_df = df[df['language'] == lang]
        print(temp_df)
        for c in metrics:
            # Calculando o intervalo de confiança à 95% com t-student
            conf_interval = (2.5096 * temp_df[c].std()) / math.sqrt(float(NUM_EXPERIMENTS))

            plt.title("Laguage {} {}=({:.2f} + {:.2f})".format(str_option, c, temp_df[c].mean(), conf_interval ))
            temp_df.boxplot(column=c)
            plt.savefig('figures/fig_{}_{}'.format(lang, c))
            plt.close('all') 
    

if __name__ == '__main__':
    
    print("Processamento os arquivos de resutlados")
    df = proccess_data()
    print("Salvando resultados em disco (results/results.csv)...")
    df.to_csv('results/results.csv', index=False, header=True)
    print("Resultados salvos em um Dataframe {}.".format(df.shape))

    print("Processando a Análise dos dados")
    processs_results(df)
    print("Análise finalizada")
