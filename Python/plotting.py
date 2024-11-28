# ==============================================================================================================================
# File: plotting.py
# Description: Manages data visualization for ThingSpeak channel data in a 4x4 grid layout.
# Author: Harry @https://github.com/cheuh008
# Created: 2024-11-20
# ==============================================================================================================================

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import pandas as pd
import os

# ==============================================================================================================================
# region: 4x4 Plot Grid
# Description: Function to visualize ThingSpeak channel data in a 4x4 grid.
# Note: Channel 1 occupies columns 1 and 2, Channel 2 occupies columns 3 and 4.
#       Dynamically adapts to the labels and data from the database.
# ==============================================================================================================================


def plot(dfs: dict, channels: dict, folder: str = "plots"):
    """ Generate and saves all fields as plots
            dfs (dict): pandas DataFrames 
            channels (dict): Dictionary of channel configurations 
            folder (str): Folder name, defaults to 'plots'.
    """
    fig = plt.figure(figsize=(15, 10))                                # Create a figure with a specific size (15x10 inches)
    gs = gridspec.GridSpec(4, 4, figure=fig, wspace=0.5, hspace=0.5)  # Define a 4x4 grid layout with spacing between plots

    os.makedirs(folder, exist_ok=True)                               # Create the output folder if it doesn't exist
    for count, (name, df) in enumerate(dfs.items()):                                     # Iterate through channels and their data
        labels = channels[name]["labels"]                            # Field labels for the current channel
        time_data = pd.to_datetime(df["created_at"])                 # Convert 'created_at' to datetime

        for i, label in enumerate(labels):                           # Iterate through each label
            row, col = divmod(i, 2)                                  # Calculate row and column position (2 columns per row)
            ax = fig.add_subplot(gs[row, col + count*2])             # Add a subplot to the corresponding grid position
            ax.plot(time_data, df[label], label=label)               # Plot the data for the current label
            ax.set_title(label, fontsize=8)                          # Set the title of the plot to the label name
            ax.set_xlabel("Time")                                    # Label the x-axis as "Time"
            ax.set_ylabel("Value")                                   # Label the y-axis as "Value"
            ax.grid(True)                                            # Add gridlines

            # Save individual plots
            plt.figure(figsize=(8, 6))                               # Create a new figure for saving individual plots
            plt.plot(time_data, df[label], label=label)
            plt.title(f"{label} ({name})", fontsize=14)
            plt.xlabel("Time", fontsize=12)
            plt.ylabel("Value", fontsize=12)
            plt.grid(True)
            plt.legend(loc="best")
            plot_path = os.path.join(folder, f"{label.replace(' ', '_')}_plot.png")
            plt.savefig(plot_path, dpi=300, bbox_inches="tight")
            plt.close()                                              # Close the individual figure
            print(f"Saved: {plot_path}")

    plt.tight_layout()                                               # Adjust subplots to fit in the figure area without overlap
    grid_plot_path = os.path.join(folder, "all_plots_grid.png")      # Save the 4x4 grid plot
    plt.savefig(grid_plot_path, dpi=300, bbox_inches="tight")
    print(f"Saved grid plot: {grid_plot_path}")
    plt.show()                                                       # Display the final grid plot

# ==============================================================================================================================
# End of plotting.py
# ==============================================================================================================================
