import pandas as pd

#Pull data 1 in million line increments to avoid time out errors.

#First million
print("Reading in batch...1/33", end = '\r')
data = pd.read_json("https://data.cdc.gov/resource/vbim-akqf.json?$select=sex,age_group,race_ethnicity_combined,medcond_yn,hosp_yn,icu_yn,death_yn&$limit=1000000")
#Write to csv
data.to_csv("../data/cdc.csv", index = False)

#Ramaining data
for i in range(1,33):
    print("Reading in batch..." + str(i + 1) + "/33", end = '\r')
    data = pd.read_json("https://data.cdc.gov/resource/vbim-akqf.json?$select=sex,age_group,race_ethnicity_combined,medcond_yn,hosp_yn,icu_yn,death_yn&$limit=1000000&$offset=" + str(i * 1000000))
    data.to_csv("../data/cdc.csv", mode = 'a', header=False, index=False)
