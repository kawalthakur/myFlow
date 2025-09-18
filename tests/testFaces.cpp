#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <cmath>   // For std::sqrt
#include "../include/utilities.h"
#include "../include/dictionary.h"

// A simple struct to represent a 3D point or vector for clarity.
struct Point3D {
    double x = 0.0, y = 0.0, z = 0.0;
};

// --- Function Prototypes ---

// Function to calculate centroids and area vectors for all faces.
// The 'points' parameter is now a 2D vector of doubles.
void calculateFaceGeometries(
    const std::vector<std::vector<size_t> >& Faces,
    const std::vector<std::vector<double> >& Points,
    std::vector<Point3D>& faceCentroids,
    std::vector<Point3D>& faceAreaVectors);

// Helper function to print results for verification.
void printResults(const std::vector<Point3D>& centroids, const std::vector<Point3D>& areaVectors);


int main(){
    std::vector<std::vector<std::size_t>> Faces;
    extractFaces(Faces);
    // std::cout << "\nDisplaying Faces" << std::endl;
    // dispArray(Faces);

    std::vector<std::vector<double>> Points;
    extractPoints(Points);
    // std::cout << "\nDisplaying Points" << std::endl;
    // dispArray(Points);

    // --- Output Vectors ---
    // These still use Point3D for a clear representation of the geometric results.
    std::vector<Point3D> faceCentroids;
    std::vector<Point3D> faceAreaVectors;

    // --- Perform Calculation ---
    calculateFaceGeometries(Faces, Points, faceCentroids, faceAreaVectors);

    // --- Display Results ---
    printResults(faceCentroids, faceAreaVectors);

    return 0;
}

/**
 * @brief Calculates the centroid and area vector for each face in the mesh.
 * @param Faces A 2D vector where each inner vector lists the vertex indices for a face.
 * @param Points A 2D vector of doubles where each inner vector contains the (x,y,z) coordinates.
 * @param faceCentroids A vector to be populated with the calculated face centroids.
 * @param faceAreaVectors A vector to be populated with the calculated face area vectors.
 */
void calculateFaceGeometries(
    const std::vector<std::vector<size_t>>& Faces,
    const std::vector<std::vector<double>>& Points,
    std::vector<Point3D>& faceCentroids,
    std::vector<Point3D>& faceAreaVectors) {
    
    size_t numFaces = Faces.size();
    faceCentroids.resize(numFaces);
    faceAreaVectors.resize(numFaces);

    for (size_t i = 0; i < numFaces; ++i) {
        const auto& currentFaceVertexIndices = Faces[i];
        size_t numVertices = currentFaceVertexIndices.size();

        if (numVertices < 3) continue;

        // --- 1. Calculate Face Centroid ---
        Point3D centroid_sum = {0.0, 0.0, 0.0};
        for (size_t vertexIdx : currentFaceVertexIndices) {
            // Access point coordinates using index [0] for x, [1] for y, [2] for z.
            centroid_sum.x += Points[vertexIdx][0];
            centroid_sum.y += Points[vertexIdx][1];
            centroid_sum.z += Points[vertexIdx][2];
        }
        faceCentroids[i].x = centroid_sum.x / numVertices;
        faceCentroids[i].y = centroid_sum.y / numVertices;
        faceCentroids[i].z = centroid_sum.z / numVertices;

        // --- 2. Calculate Face Area Vector (Sf) ---
        Point3D areaVector_sum = {0.0, 0.0, 0.0};
        for (size_t j = 0; j < numVertices; ++j) {
            const auto& p1_coords = Points[currentFaceVertexIndices[j]];
            const auto& p2_coords = Points[currentFaceVertexIndices[(j + 1) % numVertices]]; 

            // Create temporary Point3D objects for vector math
            Point3D p1 = {p1_coords[0], p1_coords[1], p1_coords[2]};
            Point3D p2 = {p2_coords[0], p2_coords[1], p2_coords[2]};
            
            // Vectors from the centroid to the two vertices of the edge.
            Point3D v1 = {p1.x - faceCentroids[i].x, p1.y - faceCentroids[i].y, p1.z - faceCentroids[i].z};
            Point3D v2 = {p2.x - faceCentroids[i].x, p2.y - faceCentroids[i].y, p2.z - faceCentroids[i].z};

            // Calculate the cross product: 0.5 * (v1 x v2)
            areaVector_sum.x += 0.5 * (v1.y * v2.z - v1.z * v2.y);
            areaVector_sum.y += 0.5 * (v1.z * v2.x - v1.x * v2.z);
            areaVector_sum.z += 0.5 * (v1.x * v2.y - v1.y * v2.x);
        }
        faceAreaVectors[i] = areaVector_sum;
    }
}

/**
 * @brief Prints the calculated face centroids and area vectors to the console.
 */
void printResults(const std::vector<Point3D>& centroids, const std::vector<Point3D>& areaVectors) {
    std::cout << "--- Calculated Face Geometries ---" << std::endl;
    std::cout.precision(4);
    std::cout << std::fixed; // Use fixed-point notation

    for (size_t i = 0; i < centroids.size(); ++i) {
        std::cout << "\nFace " << i << ":" << std::endl;
        
        std::cout << "  - Centroid:        (" << centroids[i].x << ", " << centroids[i].y << ", " << centroids[i].z << ")" << std::endl;
        std::cout << "  - Area Vector (S): (" << areaVectors[i].x << ", " << areaVectors[i].y << ", " << areaVectors[i].z << ")" << std::endl;

        double areaMagnitude = std::sqrt(
            areaVectors[i].x * areaVectors[i].x +
            areaVectors[i].y * areaVectors[i].y +
            areaVectors[i].z * areaVectors[i].z
        );
        std::cout << "  - Scalar Area |S|: " << areaMagnitude << std::endl;
    }
}