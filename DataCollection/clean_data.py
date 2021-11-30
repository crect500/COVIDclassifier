import pandas as pd

df = pd.read_csv("../data/cdc.csv")

#Filter Nan
df = df.dropna()

#Filter SEX
df = df.drop(df[(df['sex'] == 'Unknown') | (df['sex'] == 'Missing') | (df['sex'] == 'NA') | (df['sex'] == 'Other')].index)

#Filter AGE
df = df.drop(df[(df['age_group'] == 'Missing') | (df['age_group'] == 'NA') | (df['age_group'] == 'Unknown')].index)

#Filter RACE
df = df.drop(df[(df['race_ethnicity_combined'] == 'Multiple/Other, Non-Hispanic') | (df['race_ethnicity_combined'] == 'Unknown') | (df['race_ethnicity_combined'] == 'Missing') | (df['race_ethnicity_combined'] == 'NA')].index)
df['race_ethnicity_combined'] = df['race_ethnicity_combined'].str.replace(', Non-Hispanic', '')

#Filter MEDCOND_yn
df = df.drop(df[(df['medcond_yn'] == 'Unknown') | (df['medcond_yn'] == 'Missing') | (df['medcond_yn'] == 'NA')].index)

#Filter hosp_yn
df = df.drop(df[(df['hosp_yn'] == 'Unknown') | (df['hosp_yn'] == 'Missing') | (df['hosp_yn'] == 'NA')].index)

#Shuffle rows to random positions
df = df.sample(frac = 1)



#Write to csv
df.to_csv('../data/clean_data.csv',sep=',',index=False)

