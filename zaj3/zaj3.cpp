#include <iostream>
#include <math.h>
#define M_PI 3.1415926535
#include <vector>
#include <cstdio>
#include <random>
#include <functional>
#include <optional>
using namespace std;

random_device rd;
mt19937 gen(rd());

ostream& operator << (ostream& o, vector<double>v) {
    for (auto e : v) {
        o << e << " ";
    }
    return o;
}

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
{
    auto p = p0;
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");
    for (int i = 0; i < iterations; i++) {
        auto p2 = p;
        p2[distrib(gen)] += distrib_r(gen);
        if (f_domain(p2)) {
            double y2 = f(p2);
            if (y2 < f(p)) {
                p = p2;
//                cout << p << " " << f(p) << endl;

            }
            cout << f(p) << endl;
        }
    }
    return p;
}

vector<double> simulated_annealing(function<double(vector<double>)> f,function<bool(vector<double>)> f_domain,vector<double> p0,int iterations,function<vector<double>(vector<double>)> N,function<double(int)> T)
{
    auto s_current = p0;
    auto s_global_best = p0;

    uniform_real_distribution<> u_k(0.0, 1.0);

    if (!f_domain(s_current)) throw std::invalid_argument("The p0 point must be in domain");

    for (int k = 0; k < iterations; k++) {
        auto s_next = N(s_current);
        if (f(s_next) < f(s_current)) {
            s_current = s_next;
        }
        else {
            double u = u_k(gen);
            if (u < exp(-abs(f(s_next) - f(s_current)) / T(k))) {
                s_current = s_next;
            }
            else {

            }
        }
        if (f(s_current) < f(s_global_best)) {
            s_global_best = s_current;
        }
        cout << f(s_current) << endl;
    }
    return s_global_best;
}

using domain_t = std::vector<double>;
domain_t brute_force_method(const std::function<double(domain_t)> f, const std::function<std::optional<domain_t>()> &domain_generator) {

    auto best_p = domain_generator();
    for (auto current_p = best_p; current_p.has_value(); current_p = domain_generator()) {
        if (f(current_p.value()) < f(best_p.value())) {
            best_p = current_p;

        }
        cout << best_p.value() << endl;
    }
    return best_p.value_or(domain_t());
}

domain_t hill_climbing2(const std::function<double(domain_t)> &f, domain_t start_point, std::function<std::vector<domain_t>(domain_t)> get_close_points, int max_iterations) {
    domain_t best_p = start_point;
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        auto close_points = get_close_points(best_p);
        auto best_neighbour = *std::min_element(close_points.begin(), close_points.end(), [f](auto a, auto b){return f(a) > f(b);});
        if (f(best_neighbour) < f(best_p)) best_p = best_neighbour;
    }
    return best_p;
}



auto boothFunction = [](vector <double> v) {
    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = pow((x + (2 * y) - 7), 2) + pow(((2 * x) + y - 5), 2);
    return results;
};

auto ackleyFunction = [](vector<double> v) {

    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
    return results;
};

auto leviFunction = [](vector<double> v) {
    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = pow(sin(3 * M_PI * x), 2) + pow((x - 1), 2) * (1 + pow(sin(3 * M_PI * y), 2)) + pow((y - 1), 2) * (1 + pow(sin(2 * M_PI * y), 2));
    return results;
};

auto ackleyDomain = [](vector<double> v) {
    return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
};

auto levi_domain = [](vector<double> v) {
    return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
};
auto booth_domain = [](vector<double> v) {
    return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
};



int main() {
    using namespace std;
    vector <double> numbers;
    int wybor;
    int iteracje;
    uniform_real_distribution<> distrib_r(-10, 10);
    uniform_real_distribution<> distrib_r2(-5 ,5);
    cout << "Wybierz funkcje optymalizacyjna:" << endl << " 1. hill climbing" << endl << " 2. simulated annealing " <<  endl << " 3. brute force " << endl;
    cin >> wybor;


    switch (wybor)
    {
        case 1:
        {
            cout << "Wybierz test:" << endl << " 1. Booth" << endl << " 2. Levi " << endl << " 3. Ackley " << endl;
            cin >> wybor;
            switch (wybor)
            {
                case 1: {
                    cout << "Podaj ilosc iteracji" << endl;
                    cin >> iteracje;
                        vector<double> booth_p0 = {distrib_r(gen), distrib_r(gen)};
                        auto result = hill_climbing(boothFunction, booth_domain, booth_p0, iteracje);
                        cout << "(" << result << ") = " << boothFunction(result) << endl;
                    return 0;
                    break;}
                case 2: {
                    cout << "Podaj ilosc iteracji" << endl;
                    cin >> iteracje;
                        vector<double> levi_p0 = {distrib_r(gen), distrib_r(gen)};
                        auto result = hill_climbing(leviFunction, levi_domain, levi_p0, iteracje);
                        cout << "(" << result << ") = " << leviFunction(result) << endl;
                    return 0;
                    break;
                }
                case 3: {
                    cout << "Podaj ilosc iteracji" << endl;
                    cin >> iteracje;
                        vector<double> ackley_p0 = {distrib_r2(gen), distrib_r2(gen)};
                        auto result = hill_climbing(ackleyFunction, ackleyDomain, ackley_p0, iteracje);
                        cout << "(" << result << ") = " << ackleyFunction(result) << endl;
                    return 0;
                }
                default: {
                    cout << "error" << endl;
                    return 0;
                    break;
                }
            }
        }
        case 2: {
            cout << "Wybierz test:" << endl << " 1. Booth" << endl << " 2. Levi " << " 3. Ackley " << endl;
            cin >> wybor;
            switch (wybor)
            {
                case 1: {
                    cout << "Podaj ilosc iteracji" << endl;
                    cin >> iteracje;
                        vector<double> booth_p0 = {distrib_r(gen), distrib_r(gen)};
                        auto result = simulated_annealing(boothFunction, booth_domain, booth_p0, iteracje, [](auto p) {
                                                              normal_distribution<double> n(0.0, 0.3);
                                                              for (auto &e: p) {
                                                                  e = e + n(gen);
                                                              }
                                                              return p;
                                                          },
                                                          [](int k) { return 1000.0 / k; });
                        cout << "(" << result << ") = " << boothFunction(result) << endl;
                    return 0;
                    break;
                }
                case 2: {
                    cout << "Podaj ilosc iteracji" << endl;
                    cin >> iteracje;
                        vector<double> levi_p0 = {distrib_r(gen), distrib_r(gen)};
                        auto result = simulated_annealing(leviFunction, levi_domain, levi_p0, iteracje, [](auto p) {
                                                              normal_distribution<double> n(0.0, 0.3);
                                                              for (auto &e: p) {
                                                                  e = e + n(gen);
                                                              }
                                                              return p;
                                                          },
                                                          [](int k) { return 1000.0 / k; });
                        cout << "(" << result << ") = " << leviFunction(result) << endl;

                    return 0;
                    break;
                }
                case 3: {
                    cout << "Podaj ilosc iteracji" << endl;
                    cin >> iteracje;
                        vector<double> ackley_p0 = {distrib_r2(gen), distrib_r2(gen)};
                        auto result = simulated_annealing(ackleyFunction, ackleyDomain, ackley_p0, iteracje,
                                                          [](auto p) {
                                                              normal_distribution<double> n(0.0, 0.3);
                                                              for (auto &e: p) {
                                                                  e = e + n(gen);
                                                              }
                                                              return p;
                                                          },
                                                          [](int k) { return 1000.0 / k; });
                        cout << "(" << result << ") = " << ackleyFunction(result) << endl;
                    return 0;
                }
                default: {
                    cout << "error" << endl;
                    return 0;
                }
            }
            case 3: {
                const double precision = 1.0/2.0;
                auto sphere_f_v = [](domain_t x) {return x[0]*x[0] + x[1]*x[1];};
                auto sphere_f_generator = [precision]() -> std::optional<domain_t>{
                    static domain_t p = {-10, -10};
                    int i = 0;
                    for (i; i < p.size(); i++) {
                        p[i] = p[i] + precision;
                        if (p[i] < 10) return std::optional( p );
                        p[i] = -10;
                    }
                    return {};
                };
                auto get_random_point = []() -> domain_t {
                    std::uniform_real_distribution<double>distr(-10,10);
                    return {distr(rd), distr(rd)};
                };
                auto get_close_points_random = [](domain_t p0) -> std::vector<domain_t> {
                    std::uniform_real_distribution<double>distr(-10,10);
                    return {{distr(rd), distr(rd)}};
                };

                auto best1 = hill_climbing2(sphere_f_v, get_random_point(), get_close_points_random,10000);
                std::cout << "hill_climbing x = " << best1[0] << " " << best1[1] << std::endl;
                auto best2 = brute_force_method(sphere_f_v, sphere_f_generator);
                std::cout << "Brute force x = " << best2[0] << " " << best2[1] << std::endl;

            }

            default: {
                cout << "error" << endl;
                return 0;
                break;
            }}
    }
}