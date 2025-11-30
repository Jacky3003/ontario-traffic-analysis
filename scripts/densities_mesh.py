import numpy as np
import matplotlib.pyplot as plt
from netCDF4 import Dataset

with Dataset("data/results.nc", "r") as currfile:
    t = currfile.time_steps
    l = currfile.road_len

    file_data = currfile.variables.get("data")
    arr_data = file_data[:].copy()
    np_arr = np.array(arr_data)

    traffic_matrix = np.reshape(arr_data, (t, l))

    l_ranges = np.arange(traffic_matrix.shape[1])
    t_ranges = np.arange(traffic_matrix.shape[0])

    meshx, meshy = np.meshgrid(l_ranges, t_ranges)

    fig = plt.figure(figsize=(10.0,10.0),dpi=100)
    ax = fig.add_subplot(111, projection="3d")
    ax.set_xlabel("Unit Distances in km")
    ax.set_ylabel("Timesteps in Hours")
    ax.set_zlabel("Traffic Density in cars/km")
    ax.plot_surface(meshx, meshy, traffic_matrix)
    ax.set_title("Evolution of Traffic Density")

    plt.savefig("densities_mesh.png")

    plt.show()

    del file_data