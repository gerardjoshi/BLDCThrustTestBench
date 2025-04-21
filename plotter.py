# live_plot.py
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import seaborn as sns


csv_filename = 'motor_test.csv'
sns.set_style("darkgrid") 
#plt.style.use("ggplot")

fig, axs = plt.subplots(3, 1, figsize=(10, 8), sharex=True)
fig.suptitle("BLDC Motor Test: Real-Time Monitoring")

def animate(i):
    try:
        df = pd.read_csv(csv_filename)

        axs[0].clear()
        axs[0].plot(df["Time"], df["Current (A)"], color='tab:red')
        axs[0].set_ylabel("Current (A)")
        axs[0].grid(True)

        axs[1].clear()
        axs[1].plot(df["Time"], df["Load (g)"], color='tab:blue')
        axs[1].set_ylabel("Load (g)")
        axs[1].grid(True)

        axs[2].clear()
        axs[2].plot(df["Time"], df["Temp (C)"], color='tab:green')
        axs[2].set_ylabel("Temp (°C)")
        axs[2].set_xlabel("Time")
        axs[2].grid(True)
    except Exception as e:
        print(f"Error reading file: {e}")

ani = FuncAnimation(fig, animate, interval=1000)
plt.tight_layout()
plt.show()
