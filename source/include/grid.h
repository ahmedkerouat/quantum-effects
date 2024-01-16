#include <vector>
class Grid {
public:
    Grid(float width, float height, int rows, int columns) :
        width(width), height(height), rows(rows), columns(columns) {
        generateGrid();
    }

    const std::vector<float>& getVertices() const { return vertices; }
    const std::vector<unsigned int>& getIndices() const { return indices; }

private:
    float width;
    float height;
    int rows;
    int columns;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void generateGrid() {
        std::vector<float>().swap(vertices);
        std::vector<unsigned int>().swap(indices);

        float x, y, z = 0.0f;
        float s, t;

        float rowStep = height / rows;
        float columnStep = width / columns;

        for (int i = 0; i <= rows; ++i) {
            y = i * rowStep - height / 2.0f;

            for (int j = 0; j <= columns; ++j) {
                x = j * columnStep - width / 2.0f;

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);

                float nx = 0.0f, ny = 0.0f, nz = 1.0f;
                vertices.push_back(nx);
                vertices.push_back(ny);
                vertices.push_back(nz);

                s = static_cast<float>(j) / columns;
                t = static_cast<float>(i) / rows;
                vertices.push_back(s);
                vertices.push_back(t);
            }
        }

        for (int i = 0; i < rows; ++i) {
            int k1 = i * (columns + 1);
            int k2 = k1 + columns + 1;

            for (int j = 0; j < columns; ++j, ++k1, ++k2) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);

                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
};
