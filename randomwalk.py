import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("random_walk.csv", header = None)

plt.figure(figsize=(10,5))
for col in df.columns:
    plt.plot(df.index, df[col], alpha = 0.7)
plt.grid(True)
plt.show()
