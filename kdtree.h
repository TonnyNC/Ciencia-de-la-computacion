#include "KDTree.h"

class KMeans {
private:
    int k;
    int max_iterations;
    vector<Point> centroids;

public:
    KMeans(int k_val, int max_iter) : k(k_val), max_iterations(max_iter) {}

    // Inicializa los centroides seleccionando k puntos al azar
    void initialize_centroids(const vector<Point>& data) {
        centroids.clear();
        srand(time(0));
        vector<Point> data_copy = data;
        random_shuffle(data_copy.begin(), data_copy.end());
        for (int i = 0; i < k; ++i) {
            centroids.push_back(data_copy[i]);
            centroids.back().cluster_id = i; // Asigna ID al centroide
        }
    }

    // Funci\u00f3n central del k-Means (Asignaci\u00f3n + Actualizaci\u00f3n)
    vector<Point> fit(vector<Point> data, bool use_kdtree) {
        initialize_centroids(data);
        bool converged = false;
        int iter = 0;

        while (!converged && iter < max_iterations) {
            iter++;
            vector<Point> old_centroids = centroids;

            // --- PASO 1: ASIGNACI\u00d3N DE CLUSTER ---
            if (use_kdtree) {
                // Construir KD-Tree con los centroides actuales
                KDTree tree;
                tree.build(centroids);
                
                // Asignaci\u00f3n usando el KD-Tree (m\u00e1s r\u00e1pido)
                for (Point& p : data) {
                    const Point& nearest_centroid = tree.find_nearest_neighbor(p);
                    p.cluster_id = nearest_centroid.cluster_id;
                }
            } else {
                // Asignaci\u00f3n por Fuerza Bruta (lento)
                for (Point& p : data) {
                    double min_dist = numeric_limits<double>::max();
                    int best_cluster = -1;
                    
                    for (const Point& c : centroids) {
                        double dist = squared_euclidean_distance(p, c);
                        if (dist < min_dist) {
                            min_dist = dist;
                            best_cluster = c.cluster_id;
                        }
                    }
                    p.cluster_id = best_cluster;
                }
            }

            // --- PASO 2: ACTUALIZACI\u00d3N DE CENTROIDES ---
            vector<Point> new_centroids(k, Point(0.0, 0.0));
            vector<int> counts(k, 0);

            for (const Point& p : data) {
                if (p.cluster_id != -1) {
                    new_centroids[p.cluster_id].x += p.x;
                    new_centroids[p.cluster_id].y += p.y;
                    counts[p.cluster_id]++;
                }
            }

            // Recalcular el promedio
            converged = true;
            for (int i = 0; i < k; ++i) {
                if (counts[i] > 0) {
                    new_centroids[i].x /= counts[i];
                    new_centroids[i].y /= counts[i];
                    new_centroids[i].cluster_id = i;
                } else {
                    // Si un cluster se vac\u00eda, se mantiene el viejo centroide (o se re-inicializa)
                    new_centroids[i] = old_centroids[i]; 
                }
                
                // Verificar convergencia
                if (squared_euclidean_distance(new_centroids[i], old_centroids[i]) > 1e-6) {
                    converged = false;
                }
            }
            centroids = new_centroids;
        }

        return data; // Retorna los puntos con las asignaciones de cluster finalizadas
    }
};
