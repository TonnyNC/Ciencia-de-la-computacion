#include "KMeans.h"
#include <iomanip> // Para formatear la salida

// Funci\u00f3n para medir y ejecutar el algoritmo
void run_benchmark(vector<Point> data, int k_val, bool use_kdtree) {
    string method = use_kdtree ? "k-Means con KD-Tree" : "k-Means Fuerza Bruta";
    
    // Inicio de la medici\u00f3n de tiempo
    auto start = chrono::high_resolution_clock::now();

    KMeans km(k_val, 100); // M\u00e1ximo 100 iteraciones
    vector<Point> clustered_data = km.fit(data, use_kdtree);

    // Fin de la medici\u00f3n de tiempo
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "\n--- Resultados de " << method << " (k=" << k_val << ") ---" << endl;
    cout << "Tiempo de ejecuci\u00f3n: " << fixed << setprecision(4) << duration.count() << " ms" << endl;
    
    // Opcional: Escribir los resultados en un archivo para graficar
    /*
    ofstream outfile("results_" + (use_kdtree ? "kdtree" : "bruteforce") + ".csv");
    outfile << "x,y,cluster_id\n";
    for(const auto& p : clustered_data) {
        outfile << p.x << "," << p.y << "," << p.cluster_id << "\n";
    }
    outfile.close();
    */
}

int main() {
    // 1. Lectura de Datos
    vector<Point> data = read_csv("data2k.csv");

    if (data.empty()) {
        return 1;
    }

    cout << "Datos cargados: " << data.size() << " puntos." << endl;
    
    // Se eligen 5 clusters (k=5) como punto de partida seg\u00fan el EDA inicial
    const int K = 5; 
    
    // 2. Ejecutar y medir la versi\u00f3n Fuerza Bruta
    run_benchmark(data, K, false); 

    // 3. Ejecutar y medir la versi\u00f3n Optimizada con KD-Tree
    run_benchmark(data, K, true); 

    // **Tarea Adicional:** Debes repetir este proceso para diferentes valores de K (ej: 2, 5, 10, 20, 50, 100) 
    // para obtener los datos necesarios para las gr\u00e1ficas del informe.
    
    return 0;
}
