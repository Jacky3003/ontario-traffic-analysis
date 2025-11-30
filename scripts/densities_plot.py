from scipy.io import netcdf_file
import numpy as np
import matplotlib.pyplot as plt

with netcdf_file("data/results-large.nc", "r") as currfile:
    t = currfile.time_steps
    l = currfile.road_len

    file_data = currfile.variables.get("data")
    arr_data = file_data[:].copy()
    np_arr = np.array(arr_data)

    traffic_matrix = np.reshape(arr_data, (t, l))

    multiplot = plt.figure(figsize=(15.0,15.0),dpi=1000)
    times_to_plot = []
    for off in range(1, 5):
        times_to_plot.append((int(t/4)*off - 1))

    plt.suptitle("Traffic Density Plots")
    idx = 1
    for t_plot in times_to_plot:
        ax = multiplot.add_subplot(2,2, idx)
        ax.title.set_text(f"At Time t={t_plot+1}")
        ax.set_xlabel("Unit Distances in km")
        ax.set_ylabel("Traffic Density in cars/km")
        ax.plot(traffic_matrix[t_plot, :])
        idx += 1

    plt.savefig("densities.png")

    del file_data