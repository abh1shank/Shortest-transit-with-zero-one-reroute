Finding transit routes between two destinations A and B to find:
1) All paths with no route change
2) All paths when one route change is allowed

The data used is in GTFS format, for more information on it: https://developers.google.com/transit/gtfs#:~:text=The%20General%20Transit%20Feed%20Specification,schedules%20and%20associated%20geographic%20information.

Below is a demonstration of how it works when you compile the C++ file to form a binary file and run it on shell

<img width="631" alt="image" src="https://github.com/abh1shank/IISC_INTERNSHIP_ASSGN/assets/97939389/cdc21840-c006-4fb1-a6c5-976047d5a827">

This Code assumes that if there are two routes A and B, such that both A and B are direct routes, and if you can go from route A->B, that is also a route change. That means two direct routes connected to each other can also be used for rerouting.
