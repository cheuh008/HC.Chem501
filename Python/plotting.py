# ==============================================================================================================================
# File: plotting.py
# Description: Manages data visualization for ThingSpeak channel data in a 4x4 grid layout.
# Author: Harry @https://github.com/cheuh008
# Created: 2024-11-20
# ==============================================================================================================================

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import pandas as pd

# ==============================================================================================================================
# region: 4x4 Plot Grid
# Description: Function to visualize ThingSpeak channel data in a 4x4 grid.
# Note: Channel 1 occupies columns 1 and 2, Channel 2 occupies columns 3 and 4.
#       Dynamically adapts to the labels and data from the database.
# ==============================================================================================================================

def plot_4x4_grid(df, channels):
    """
    Plot fields in a 4x4 grid:
    - Channel 1: Fields in columns 1-2.
    - Channel 2: Fields in columns 3-4.
    
    Args:
        df (dict): Dictionary of DataFrames for each channel.
        channels (dict): Dictionary containing channel information and labels.
    """
    fig = plt.figure(figsize=(15, 10))                                # Create a figure with a specific size (15x10 inches)
    gs = gridspec.GridSpec(4, 4, figure=fig, wspace=0.5, hspace=0.5)  # Define a 4x4 grid layout with spacing between plots

# ==============================================================================================================================
# region Table 1: Left, plots Channel 1's 5 fields in 4x2 grid
# ==============================================================================================================================

    table_name_1 = "channel_1"                                        # Define the table name for Channel 1
    if table_name_1 in df:                                            # Check if Channel 1 data is available
        df_1 = df[table_name_1]                                       # Retrieve the DataFrame for Channel 1
        time_1 = pd.to_datetime(df_1["created_at"])                   # Convert the "created_at" column to datetime format
        labels_1 = channels[table_name_1]["labels"]                   # Retrieve the labels for Channel 1 fields

        for i, label in enumerate(labels_1):                          # Iterate through each label for Channel 1
            row, col = divmod(i, 2)                                   # Calculate row and column position (2 columns)
            ax = fig.add_subplot(gs[row, col])                        # Add a subplot to the corresponding grid position
            ax.plot(time_1, df_1[label], label=label)                 # Plot the data for the current label
            ax.set_title(label, fontsize=8)                           # Set the title of the plot to the label name
            ax.set_xlabel("Time")                                     # Label the x-axis as "Time"
            ax.set_ylabel("Value")                                    # Label the y-axis as "Value"
            ax.grid(True)                                             # Enable grid for better readability

# ==============================================================================================================================
# region Table 2: Right, plots Channel 2's 8 fields in 4x2 grid
# ==============================================================================================================================

    table_name_2 = "channel_2"                                         # Define the table name for Channel 2
    if table_name_2 in df:                                             # Check if Channel 2 data is available
        df_2 = df[table_name_2]                                        # Retrieve the DataFrame for Channel 2
        time_2 = pd.to_datetime(df_2["created_at"])                    # Convert the "created_at" column to datetime format
        labels_2 = channels[table_name_2]["labels"]                    # Retrieve the labels for Channel 2 fields

        for i, label in enumerate(labels_2):                           # Iterate through each label for Channel 2
            row, col = divmod(i, 2)                                    # Calculate row and column position (2 columns)
            ax = fig.add_subplot(gs[row, col + 2])                     # Add a subplot to the corresponding grid position (offset by 2 columns)
            ax.plot(time_2, df_2[label], label=label)                  # Plot the data for the current label
            ax.set_title(label, fontsize=8)                            # Set the title of the plot to the label name
            ax.set_xlabel("Time")                                      # Label the x-axis as "Time"
            ax.set_ylabel("Value")                                     # Label the y-axis as "Value"
            ax.grid(True)                                              # Enable grid for better readability

    plt.tight_layout()                                                 # Adjust subplots to fit in the figure area without overlap
    plt.show()                                                         # Display the final plot

# ==============================================================================================================================
# End, Well done
# ==============================================================================================================================
