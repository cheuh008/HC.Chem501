import serial
import serial.tools.list_ports
import pandas as pd
import numpy as np
import matplotlib as mpl
mpl.rcParams['axes.formatter.useoffset'] = False    # Remove annoying auto-offset
import matplotlib.pyplot as plt

plt.ion()  # Enable interactive plotting

# Connect to the Nicla
ports = serial.tools.list_ports.comports()
for n in ports:
    dev = n.device
# See baudrate=115200 below? This is the speed at which the Nicla communicates with the computer. Don't change it.
nicla = serial.Serial(port=dev, baudrate=115200, timeout=.1)

n_readings = 200
column_titles = ['time', 'temp', 'pressure', 'gas']

while True:
    # Start collecting data - tell the Nicla how many data points to take
    nicla.write(bytes("{f0}".format(f0=n_readings), 'utf-8'))
    # Create somewhere to store the data
    data_table = np.zeros((n_readings, len(column_titles)))

    for n in range(n_readings):
        data = nicla.readline()
        # Split the line read from the Nicla every time it finds a ','
        data = np.fromstring(data, sep=',')
        if len(data) == len(column_titles):
            data_table[n,:] = data

    tpg_data = pd.DataFrame(data_table, columns=column_titles)

    data_filtered = tpg_data[['time', 'temp']]
    tpg_data_filter = tpg_data[tpg_data['gas'] > 0]
    lower_bound = tpg_data['gas'].quantile(0.01)
    upper_bound = tpg_data['gas'].quantile(0.99)
    data_clean = tpg_data[(tpg_data['gas'] > lower_bound) & (tpg_data['gas'] < upper_bound)]
    filename = 'plot_name.png'

    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(data_clean['time'], data_clean['gas'])
    ax.set_xlabel('Time (s)')
    ax.set_ylabel('Gas (a.u.)')
    plt.show()
    plt.pause(1)
    plt.close(fig)