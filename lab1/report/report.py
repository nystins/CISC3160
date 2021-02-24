import pandas as pd

pd.set_option('display.max_rows', None)
pd.set_option('display.max_columns', None)
pd.set_option('display.width', None)

df = pd.read_csv('regional-global-weekly-latest.csv')
#groupbuy is to get the artist unique (same logic as SQL)
#.agg = allows to count how many artist are there, and sum up streams | aggregations
#reset_index because after we deleted the duplicates original CSV is 0-199, it gets less after deletion
df = df.groupby('Artist').agg({'Artist':'count', 'Streams':'sum'}).rename(columns={'Artist':'Count_dups'}).reset_index()
df['Avg.Streams'] = df['Streams'] / df['Count_dups'] #to get the average streams divide by the number of duplicates 
del df['Count_dups'] #deleted count_dups to not show in print
print(df)
