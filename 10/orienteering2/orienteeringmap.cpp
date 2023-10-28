#include "orienteeringmap.hh"


OrienteeringMap::OrienteeringMap()
{
}

OrienteeringMap::~OrienteeringMap()
{
}

void OrienteeringMap::set_map_size(int width, int height)
{
    map_height_ = height;
    map_width_ = width;
}

void OrienteeringMap::add_point(std::string name, int x, int y,
                                int height, char marker)
{
    if ( points.find(name) == points.end() ){
        // pistettä ei löydy -> lisätään

        Point_info temp;
        temp.name_ = name;
        temp.x_ = x;
        temp.y_ = y;
        temp.height_ = height;
        temp.marker_ = marker;

        points[name] = temp;
    }
    else {
        // löytyi
        return;
    }
}

bool OrienteeringMap::connect_route(std::string from, std::string to, std::string route_name)
{
    if ( routes_map.find(route_name) == routes_map.end() ){
        // reittiä ei löydy
        routes_map[route_name].push_back(from);
        routes_map[route_name].push_back(to);
    }
    else if ( routes_map.find(route_name) != routes_map.end() ){
        // reitti löytyy jo
        routes_map[route_name].push_back(to);
    }
    else {
        return false;
    }
    return true;
}

void OrienteeringMap::print_map() const
{
    std::cout << " ";

    for ( int y = 0; y <= map_height_; y++){
        if ( y != 0 ){
            std::cout.width(2);std::cout << std::right << y;
        }
        for ( int x = 1; x <= map_width_; x++){
            if ( y == 0){
                std::cout.width(3);std::cout << std::right << x;
            }

            if ( y != 0 ){
                bool right_coord = false;
                char marker;

                for (auto i : points ){
                    int point_x = i.second.x_;
                    int point_y = i.second.y_;

                    if ( point_x == x and point_y == y ){
                        right_coord = true;
                        marker = i.second.marker_;
                    }
                }

                if ( right_coord ){
                    std::cout << "  " << marker;
                }
                else {
                    std::cout << "  .";
                }
            }
        }
        std::cout << std::endl;
    }
}

void OrienteeringMap::print_routes() const
{
    std::cout << "Routes:" << std::endl;
    for ( auto i : routes_map ){
        std::cout << " - " << i.first << std::endl;
    }

}

void OrienteeringMap::print_points() const
{
    std::cout << "Points:" << std::endl;
    for ( auto i : points ){
        std::string point = i.second.name_;
        char marker = i.second.marker_;
        std::cout << " - " << point << " : " << marker << std::endl;
    }
}

void OrienteeringMap::print_route(const std::string &name) const
{
    for ( auto i : routes_map ){
        if ( i.first == name ){
            // löytyy
            auto route_list = i.second;

            std::cout << route_list.at(0) << std::endl;
            for ( unsigned int j = 1; j < route_list.size(); j++){
                std::cout << " -> " << route_list.at(j) << std::endl;
            }
            return;
        }
    }
    std::cout << "Error: Route named " << name
              << " can't be found" << std::endl;
}

void OrienteeringMap::route_length(const std::string &name) const
{
    if ( routes_map.find(name) == routes_map.end() ){
        // reittiä ei löydy
        std::cout << "Error: Route named " << name
                  << " can't be found" << std::endl;
        return;
    }

    double distance = 0;
    // käydään kaikki reitit läpi
    for ( auto i : routes_map ){
        if ( i.first == name){
            auto route_points = i.second;

            for ( unsigned int j = 1; j < route_points.size(); ++j ){
                std::string name2 = route_points.at(j);
                std::string name1 = route_points.at(j-1);

                int x1 = points.at(name1).x_;
                int y1 = points.at(name1).y_;
                int x2 = points.at(name2).x_;
                int y2 = points.at(name2).y_;

                double a = pow(x2-x1,2);
                double b = pow(y2-y1,2);

                distance += sqrt(a+b);
            }
        }
    }

    // loppu printtaukset
    if ( distance >= 10 ){
        std::cout << "Route " << name << " length was "
                  << std::fixed <<std::setprecision(0)
                  << distance << std::endl;
    }
    else {
        std::cout << "Route " << name << " length was "
                  << std::fixed <<std::setprecision(1)
                  << distance << std::endl;
    }
}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    if ( points.find(point_name) == points.end() ){
        // pistettä ei löydy
        std::cout << "Error: Point named " << point_name
                  << " can't be found" << std::endl;
        return;
    }

    // muuttujat
    std::set<std::string> route_name_for_rise;
    int rise = 0;
    int point_height = points.at(point_name).height_;

    // käydään läpi jokainen reitti
    for ( auto i : routes_map ){
        // point_found merkkaa, onko piste löytynyt reitiltä
        bool point_found = false;
        std::vector<std::string> route_points = i.second;

        // käydään läpi reitin jokainen piste
        for ( std::string j : route_points){
            if ( point_name == j ){
                point_found = true;
            }

            // jos piste löytyy reitiltä ja se on korkeammalla kuin alkuperäinen
            // piste, niin tehdään tarkastelut ja muttujien päivitykset
            if ( point_found and points.at(j).height_ >= point_height){
                int temp_rise = points.at(j).height_ - point_height;

                if ( temp_rise > rise ){
                    rise = temp_rise;
                    route_name_for_rise.clear();
                    route_name_for_rise.insert(i.first);
                }
                else if ( temp_rise == rise ){
                    route_name_for_rise.insert(i.first);
                }
            }
            else if ( point_found and points.at(j).height_ < point_height ){
                break;
            }
        }
    }

    // loppu printtaukset
    if ( rise != 0 ){
        std::cout << "Greatest rise after point "
                  << point_name
                  << ", " << rise
                  << " meters, is on route(s):" << std::endl;
        for ( auto k : route_name_for_rise ){
            std::cout << " - " << k << std::endl;
        }
    }
    else {
        std::cout << "No route rises after point " << point_name << std::endl;
    }
}
