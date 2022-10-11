#include <iostream>
#include <map>
#include <functional>
#include <cmath>
#include <vector>


using mojafunkcja_t = std::function<double(std::vector<double>)>;
//using inna = std::function<double(double,double)>;
using mojamapa_t = std::map<std::string, std::vector<double>>;

void wypisz(const mojamapa_t& mapa, const mojafunkcja_t& fun) {
    using namespace std;
    for (auto kv : mapa) {
        auto [k, v] = kv;
        cout << "klucz: " << k << "; wartosc " << fun(v) << endl;

    }
}
int main(int argc, char** argv) {
    using namespace std;
    vector<double> values;
    try {
        for (int i = 2; i < argc; i++){
            values.push_back(stoi(argv[i]));
        }
        vector<string> argumenty(argv, argv + argc);
        map<string, vector<double>> mapa = {{argumenty.at(1), values}};
        map<string, mojafunkcja_t> formatery;
        formatery["sin"] = [](vector<double> x) { return sin(x[0]); };
        formatery["add"] = [](vector<double> x) { return  x[0] + x[1]; };
        formatery["mod"] = [](vector<double> x) {return int(x[0])%int(x[1]);};
    try {
        auto selected_f = argumenty.at(1);
        wypisz(mapa,formatery.at(selected_f));
    } catch (std::out_of_range& aor) {
        cout << "out of range" << endl;
    }
    }catch (std::logic_error){
       cout << "To ja program";
    }

    return 0;
}