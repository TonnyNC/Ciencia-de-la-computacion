#include "Point.h"

// Estructura para un nodo del KD-Tree
struct KDNode {
    Point point;
    int axis; // Eje de divisi\u00f3n (0 para x, 1 para y)
    KDNode *left = nullptr;
    KDNode *right = nullptr;

    KDNode(const Point& p, int ax) : point(p), axis(ax) {}
    ~KDNode() { delete left; delete right; }
};

class KDTree {
private:
    KDNode* root = nullptr;

    // Funci\u00f3n auxiliar para construir el \u00e1rbol (recursiva)
    KDNode* build_recursive(vector<Point>& points, int depth) {
        if (points.empty()) return nullptr;

        // Determinar el eje de divisi\u00f3n (0:x, 1:y)
        int axis = depth % 2;

        // Ordenar los puntos por el eje actual para encontrar la mediana
        if (axis == 0) {
            sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
                return a.x < b.x;
            });
        } else {
            sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
                return a.y < b.y;
            });
        }

        size_t median_index = points.size() / 2;
        Point median_point = points[median_index];

        // Crear el nodo ra\u00edz para este sub\u00e1rbol
        KDNode* node = new KDNode(median_point, axis);

        // Dividir los puntos para las llamadas recursivas
        vector<Point> left_points, right_points;
        for (size_t i = 0; i < points.size(); ++i) {
            if (i == median_index) continue;
            if (i < median_index) {
                left_points.push_back(points[i]);
            } else {
                right_points.push_back(points[i]);
            }
        }

        node->left = build_recursive(left_points, depth + 1);
        node->right = build_recursive(right_points, depth + 1);

        return node;
    }

    // Funci\u00f3n auxiliar para la b\u00fasqueda de vecino m\u00e1s cercano (recursiva)
    void nearest_neighbor_recursive(KDNode* node, const Point& target, KDNode*& best_node, double& min_dist) {
        if (node == nullptr) return;

        double current_dist = squared_euclidean_distance(node->point, target);
        if (current_dist < min_dist) {
            min_dist = current_dist;
            best_node = node;
        }

        int axis = node->axis;
        double diff = (axis == 0) ? (target.x - node->point.x) : (target.y - node->point.y);

        // Determinar qu\u00e9 lado explorar primero
        KDNode* first_side = (diff < 0) ? node->left : node->right;
        KDNode* second_side = (diff < 0) ? node->right : node->left;

        nearest_neighbor_recursive(first_side, target, best_node, min_dist);

        // Poda: \u00bfNecesitamos revisar el otro lado?
        // Solo si la distancia al plano de divisi\u00f3n es menor que la mejor distancia encontrada
        if (pow(diff, 2) < min_dist) {
            nearest_neighbor_recursive(second_side, target, best_node, min_dist);
        }
    }

public:
    KDTree() = default;
    ~KDTree() { delete root; }

    // Construye el KD-Tree a partir de una lista de puntos
    void build(vector<Point> points) {
        if (root) { delete root; root = nullptr; }
        root = build_recursive(points, 0);
    }

    // Encuentra el vecino m\u00e1s cercano a un punto objetivo
    const Point& find_nearest_neighbor(const Point& target) {
        if (root == nullptr) {
            throw runtime_error("El KD-Tree est\u00e1 vac\u00edo.");
        }
        KDNode* best_node = nullptr;
        double min_dist = numeric_limits<double>::max();

        nearest_neighbor_recursive(root, target, best_node, min_dist);
        
        // Se asume que siempre encontrar\u00e1 un nodo ya que el \u00e1rbol no est\u00e1 vac\u00edo
        return best_node->point;
    }
};
