#include <iostream>
#include <math.h>
#define M_PI 3.1415926535
#define M_E 2.7182818284590452
#include <vector>
#include <random>
#include <functional>
using namespace std;

random_device rd;
mt19937 gen(rd());

ostream &operator << (ostream &o, vector<double>v){
    for(auto e :v){
        o<<e<<"\t";

    }
    return o;
}

vector<double> hillClimbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, vector <double> distanceBetweenPoints, int iterations){

    auto p = p0;
    double a = distanceBetweenPoints.at(0);
    double b = distanceBetweenPoints.at(1);
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(a,b);

    if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");
    for (int i = 0; i < iterations; i++) {
        auto p2 = p;

        p[distrib(gen)] += distrib_r(gen);
        double y2 = f(p2);
        if (y2 < f(p)) {
            p = p2;
//            cout << p << "\t" << f(p) << endl;
        }
    }
    return p;
}

auto boothFunction = [](vector <double> v){

    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = pow((x + (2 * y) - 7), 2)+pow(((2*x)+y-5),2);
    return results;
};

auto ackleyFunction = [](vector<double> v) {

    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
    return results;
};

auto matyas = [](vector<double> v) {

    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = 0.26*(pow(x,2) + pow(y,2) - 0.48*x*y);
    return results;
};

auto matyasDomain = [](vector<double> v) {
    return (v[0] >= -10 && v[1] <=10);
};

auto ackleyDomain = [](vector<double> v) {
    return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
};
auto boothDomain = [](vector<double> v) {
    return (abs(v[0]) <=10) && (abs(v[1]) <=10);
};

int main() {
    using namespace std;
    vector <double> numbers;
    int wybor;
    cout << "Wybierz funkcje optymalizacyjna: 1 = Booth 2 = Ackley 3 = Matyas";
    cin >> wybor;
    int iteracje;
    vector <double> distanceBetweenPoints {-0.1,0.1};
    if (wybor == 1) {
        cout << "Podaj ilosc iteracji"<<endl;
        cin>>iteracje;

        uniform_real_distribution<> distrib_r(-10,10);
        vector<double> boothP0 = {distrib_r(gen),distrib_r(gen)};
        auto result = hillClimbing(boothFunction,boothDomain,boothP0,distanceBetweenPoints,iteracje);
        cout<<result << "->"<<boothFunction(result)<<endl;
    }
    else if (wybor == 2) {
        cout << "Podaj ilosc iteracji"<<endl;
        cin>>iteracje;
        uniform_real_distribution<> distrib_r(-5,5);
        vector<double> ackleyP0 = {distrib_r(gen),distrib_r(gen)};
        auto result = hillClimbing(ackleyFunction, ackleyDomain, ackleyP0, distanceBetweenPoints, iteracje);
        cout << result << " -> " << ackleyFunction(result) << endl;
    }else {
        cout << "Podaj ilosc iteracji"<<endl;
        cin>>iteracje;
        uniform_real_distribution<> distrib_r(-10,10);
        vector<double> matyasP0 = {distrib_r(gen),distrib_r(gen)};
        auto result = hillClimbing(matyas,matyasDomain,matyasP0,distanceBetweenPoints,iteracje);
        cout<<result <<" -> "<<matyas(result)<<endl;
    }
    return 0;
}