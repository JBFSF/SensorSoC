# import pandas as pd
# import glob
# csv_path = "csvs/S010_whole_df.csv"
# chunksize = 100_000
# chunks = []
# for file in glob.glob("csvs/*.csv"):
#     for chunk in pd.read_csv(file, usecols=[7, 9], chunksize=chunksize):
#         chunks.append(chunk)
# df = pd.concat(chunks, ignore_index=True)
# df.columns = ['hr','ss']
# print(df.head())

# import pandas as pd
# import glob
# dfs = []
# for file in glob.glob("csvs/*.csv"):
#     sampled_chunks = []
#     for chunk in pd.read_csv(file, usecols=[0, 2, 3, 4, 7, 9], chunksize=64):
#         # Take the LAST row of each 64-row chunk
#         sampled_chunks.append(chunk.iloc[-1])
#     df_sampled = pd.DataFrame(sampled_chunks)
#     dfs.append(df_sampled)
# result_df = pd.concat(dfs, ignore_index=True)
# result_df.to_csv("sd_out.csv", index=False)

import pandas as pd
import glob

dfs = []

for file in glob.glob("csvs/*.csv"):
    sampled_chunks = []
    print ("file:", file)

    for chunk in pd.read_csv(file, usecols=[0, 2, 3, 4, 7, 9], chunksize=64):
        # rename for clarity (optional but helps avoid mistakes)
        chunk.columns = ['time','x','y','z','hr', 'ss']

        # remove rows with unwanted sleep stages
        chunk = chunk[~chunk['ss'].isin(['P', 'prep'])]

        # only sample if the chunk still has data
        if not chunk.empty:
            sampled_chunks.append(chunk.iloc[-1])

    if sampled_chunks:
        df_sampled = pd.DataFrame(sampled_chunks)
        dfs.append(df_sampled)

result_df = pd.concat(dfs, ignore_index=True)
result_df.to_csv("sd_out.csv", index=False)

# import pandas as pd

# df = pd.read_csv("sd_out.csv")

# # remove unwanted sleep stages
# df = df[~df['ss'].isin(['P', 'prep'])]

# df.to_csv("sd_out_clean.csv", index=False)
