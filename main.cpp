#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

class Site {
public:
    int position;
    vector<string> links;

    Site() {
        position = 0;
        links = {};
    }

    int get_position() {
        return position;
    }

    vector<string> get_links() {
        return links;
    }

    void set_position(int posi){
        position = posi;
    }

    void add_link_to(string to_site) {
        links.push_back(to_site);
    }

    int get_num_of_links() {
        return links.size();
    }
};

const int NUM_OF_LINES = 7;
const int NUM_OF_ITER = 2;
const string LIST_OF_LINKS[7][2] = {
        {"google.com", "gmail.com"},
        {"google.com", "maps.com"},
        {"facebook.com", "ufl.edu"},
        {"ufl.edu", "google.com"},
        {"ufl.edu", "gmail.com"},
        {"maps.com", "facebook.com"},
        {"gmail.com", "maps.com"}};

int main()
{
    int no_of_lines, power_iterations;
    string from, to;
    vector<string> sites;
    map<string, Site> site_map;

//    cin >> no_of_lines;
//    cin >> power_iterations;

    for(int i = 0; i < NUM_OF_LINES; i++) {
        bool from_site_not_present, to_site_not_present;

        from = LIST_OF_LINKS[i][0];
        to = LIST_OF_LINKS[i][1];
//        cin >> from;
//        cin >> to;

        from_site_not_present = site_map.find(from) == site_map.end();
        to_site_not_present = site_map.find(to) == site_map.end();

        if (from_site_not_present) {
            sites.push_back(from);
            Site site_name;
            site_name.add_link_to(to);
            site_map[from] = site_name;
        } else {
            Site site_name = site_map[from];
            site_name.add_link_to(to);
            site_map[from] = site_name;
        }

        if (to_site_not_present) {
            sites.push_back(to);

            Site site_name;
            site_map[to] = site_name;
        }
    }

    sort(sites.begin(), sites.end());

    auto num_of_sites = sites.size();
    double matrix[num_of_sites][num_of_sites] = {};

    // Updating position of sites in site_map
    for (auto i = 0; i < num_of_sites; i++) {
        cout << "SITE: " << sites[i] << "\n";
        Site site_name = site_map[sites[i]];
        site_name.set_position(i);

        site_map[sites[i]] = site_name;
    }

    for (auto site: sites) {
        Site from_site = site_map[site];
        double out_degree;

        int from_site_pos = from_site.get_position();
        vector<string> links = from_site.get_links();
        double len_of_links = from_site.get_num_of_links();

        if (len_of_links == 0){
            out_degree = 0;
        } else {
            out_degree = 1 / len_of_links;
        }

        cout << "Outside out_degree: " << out_degree << "\n";

        for (auto link: from_site.get_links()) {
            Site to_site = site_map[link];
            int to_site_pos = to_site.get_position();
            cout << "site: " << site << "\n";
            cout << "link: " << link << "\n";
            cout << "from_site_pos: " << from_site_pos << "\n";
            cout << "to_site_pos: " << to_site_pos << "\n";
            cout << "out_degree: " << out_degree << "\n";
            matrix[to_site_pos][from_site_pos] = out_degree;
            cout << "matrix at " << to_site_pos << " and " << from_site_pos << ": " << out_degree << "\n";
        }
    }

    for (auto i = 0; i < num_of_sites; i++){
        for (auto j = 0; j < num_of_sites; j++) {
            cout << fixed << setprecision(2) << matrix[i][j] << " ";
//            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}