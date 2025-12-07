import pandas as pd
import matplotlib.pyplot as plt
from geopy.distance import distance, lonlat

CAMERA_ROAD = "camera_road"
TRAFFIC_SOURCE = "traffic_source"
AREA = "Toronto"
WKT = "WKT"

if __name__ == "__main__":

    # example using two points in steeles ave from the dataset
    # see the dataset and map below for valid street names
    # problem assumes that there exists a straight road from point A to point B
    # https://www150.statcan.gc.ca/n1/pub/71-607-x/71-607-x2022018-eng.htm

    street = "STEELES AVE"
    date = "x2025_06_10"

    traffic_df = pd.read_csv("data/tf-ft-eng.csv")
    traffic_df = traffic_df.filter(items=[WKT, TRAFFIC_SOURCE, CAMERA_ROAD, date])
    traffic_df = traffic_df[traffic_df[TRAFFIC_SOURCE] == AREA]
    traffic_df = traffic_df[traffic_df[CAMERA_ROAD].str.contains(street)]
    traffic_df[WKT] = traffic_df[WKT].map(lambda s: s.strip("() POINT").split(" "))
    traffic_df[WKT] = traffic_df[WKT].map(lambda s: (float(s[0]), float(s[1])))
    traffic_df = traffic_df.sort_values(by=WKT)

    # distance between furthest two points
    first_pt = traffic_df.head()
    last_pt = traffic_df.tail()
    fp = first_pt.values[0][0]
    lp = last_pt.values[0][0]
    point_dist = distance(lonlat(*fp), lonlat(*lp)).km

    # go through each of the values in order, increase by 5% until threshold is hit
    res_arr = []
    critical_pts_num = traffic_df.shape[0]
    increment = 0.01
    for i in range(0, critical_pts_num-1):
        correlation = 0
        num_cars_curr = traffic_df.values[i][3]
        num_cars_next = traffic_df.values[i+1][3]

        if num_cars_curr < num_cars_next:
            correlation = 1
            car_num = num_cars_curr
            while car_num < num_cars_next:
                res_arr.append(car_num)
                car_num += correlation*(car_num*increment)
        elif num_cars_curr > num_cars_next:
            correlation = -1
            car_num = num_cars_curr
            while car_num > num_cars_next:
                res_arr.append(car_num)
                car_num += correlation*(car_num*increment)
        else:
            continue

    plot = plt.figure(figsize=(15.0,15.0),dpi=100)
    plt.suptitle(f"Traffic Progress on {street}")
    plt.ylabel("Number of Spotted Cars")
    plt.xlabel(f"{point_dist/len(res_arr)} km per unit")
    plt.plot(res_arr)
    plt.show()

    with open("data/traffic_density.data", "w") as f:
        for num in res_arr:
            f.write(f"{num}\n")
