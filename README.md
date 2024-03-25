Inside the GTFS folder there is solution to question 2, in the part where we had to find all routes with one reroute, i have tried to explain the logic via comments and since
there data file for stop_times.txt was too large, i had to use Pandas to preprocess the data to bring it in a format that was usable, i then took the processed data as input in the 
C++ file and used it to calculate the answers. The code has thorough use of STL in it. Thank-You, please do ping me if the logic seems unclear.
<img width="631" alt="image" src="https://github.com/abh1shank/IISC_INTERNSHIP_ASSGN/assets/97939389/cdc21840-c006-4fb1-a6c5-976047d5a827">

This Code assumes that if there are two routes A and B, such that both A and B are direct routes, and if you can go from route A->B, that is also a route change. That means two direct routes connected to each other can also be used for rerouting.
