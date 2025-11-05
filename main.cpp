#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <chrono>

using namespace std;

// Estructura para un punto de datos 2D
struct Point {
    double x, y;
    int cluster_id = -1; // ID del cluster asignado

    Point(double x_val, double y_val) : x(x_val), y(y_val) {}

    // Sobrecarga del operador para imprimir
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

// Funci\u00f3n para calcular la distancia euclidiana cuadr\u00e1tica entre dos puntos
double squared_euclidean_distance(const Point& p1, const Point& p2) {
    return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
}

// Funci\u00f3n para leer los datos del CSV
vector<Point> read_csv(const string& filename) {
    vector<Point> points;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << endl;
        return points;
    }

    string line;
    getline(file, line); // Saltar la cabecera (x,y)

    while (getline(file, line)) {
        stringstream ss(line);
        string segment;
        vector<double> coords;

        while (getline(ss, segment, ',')) {
            try {
                coords.push_back(stod(segment));
            } catch (const invalid_argument& e) {
                // Ignorar l\u00edneas mal formateadas
            }
        }
        if (coords.size() == 2) {
            points.emplace_back(coords[0], coords[1]);
        }
    }
    return points;
}
