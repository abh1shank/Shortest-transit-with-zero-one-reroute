#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

vector<string> readTextFile(const string& filename) {
    vector<string> fileContents;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            fileContents.push_back(line);
        }
        file.close();
    } else {
        cerr << "Unable to open " << filename << endl;
    }
    return fileContents;
}

map<string, set<string>> constructMap(const vector<string>& lines) {
    map<string, set<string>> resultMap;

    for(auto line : lines) {
        string word="";
        string key="&";
        for(auto chars : line) {
            if(chars == ',') {
                if(key == "&") {
                    key = word;
                    word = "";
                } else {
                    resultMap[key].insert(word);
                    word = "";
                }
                continue;
            }
            word += chars;
        }
    }

    return resultMap;
}
set<pair<string,string>> routesWithOneChange(string source_id,string destid,map<string, set<string>>& stop_route_map,map<string, set<string>>& route_stop_map) {


    //routes that originate from the source;
    set<string>routes_from_source;
    for(auto route: stop_route_map[source_id])
    {
        routes_from_source.insert(route);
    }

    //stops that fall on the routes i.e. possible junctions to switch routes
    //this is possible junction datastructure will keep track of possible junctions
    //as well as the routes that you can possibly take from source to reach there

    map<string,set<string>> possible_junctions;
    for(auto route:routes_from_source)
    {
        for(auto junction: route_stop_map[route])
        {   
            if(junction!=destid)
            possible_junctions[junction].insert(route);
        }
    }

    //Now we will see if there is a route from these junctions that can
    //take us to the route that is directly connected to destination.
    
    set<string>dest_connected_routes;

    //if we find a junction that can take us to the destination route,all
    //routes taking us to that junction can be used to reroute 

    map<string,set<set<string>>>reachable_routes;
    for(auto route:stop_route_map[destid])
    {
        dest_connected_routes.insert(route);
    }
    //transfer junctions are the ones from which u can switch to the route that
    //will take u to destination
    set<pair<string,string>>route_switches;
    for(auto dest_route:dest_connected_routes)
    {
        for(auto junctions:possible_junctions)
        {
            string junction_id=junctions.first;
            bool route_present=stop_route_map[junction_id].find(dest_route) != stop_route_map[junction_id].end();
            if(route_present)
            {
                for(auto incoming_routes:possible_junctions[junction_id])
                    route_switches.insert({incoming_routes,dest_route});
            }
        }
    }

    return route_switches;
}

set<string> direct_routes_find(string source_id,string destination_id,map<string, set<string>>route_stop_map,map<string, set<string>>stop_route_map)
{
    set<string>directly_routes;
    for(auto& routes : route_stop_map) 
    {
        const string& route_id = routes.first;
        bool present_in_both = (stop_route_map[source_id].find(route_id) != stop_route_map[source_id].end()) &&
                               (stop_route_map[destination_id].find(route_id) != stop_route_map[destination_id].end());
        if (present_in_both) {
            directly_routes.insert(route_id);
        }
    }
    return directly_routes;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <source_id> <destination_id>" << endl;
        return 1;
    }

    string source_id = argv[1];
    string destination_id = argv[2];

    vector<string> stop_route = readTextFile("C:/Users/saran/ULTRA/Runnables/Question_2/GTFS/stop_route_map.txt");
    vector<string> route_stop = readTextFile("C:/Users/saran/ULTRA/Runnables/Question_2/GTFS/route_stop_map.txt");
    map<string, set<string>> stop_route_map = constructMap(stop_route);
    map<string, set<string>> route_stop_map = constructMap(route_stop);


    set<string> directly_routes=direct_routes_find(source_id, destination_id,route_stop_map,stop_route_map);
    set<pair<string,string>>one_switch_routes=routesWithOneChange(source_id,destination_id,stop_route_map,route_stop_map);

    cout<<"Direct Routes are :\n";
    for(auto routes:directly_routes)    
        cout<<routes<<"\n";
    
    cout<<"Routes with one change are :\n";
    for(auto routes:one_switch_routes)
        if(routes.first!=routes.second)
            cout<<routes.first<<" -> "<<routes.second<<"\n";
    return 0;
}
