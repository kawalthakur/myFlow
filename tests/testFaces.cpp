#include <iostream>
#include <vector>

// Your custom header for reading mesh data from files.
// It is assumed to contain the declarations for extractFaces() and extractPoints().
#include "../include/dictionary.h"

// The new, self-contained header for face geometric calculations.
#include "../include/fvFaces.h"

int main() {
    // --- 1. Load Mesh Data ---
    // These vectors will be populated by your custom functions.
    std::vector<std::vector<std::size_t>> Faces;
    extractFaces(Faces);

    std::vector<std::vector<double>> Points;
    extractPoints(Points);

    std::cout << "Successfully loaded " << Faces.size() << " faces and " 
              << Points.size() << " points." << std::endl;

    // --- 2. Prepare Output Vectors ---
    // These vectors will be filled by the calculation function.
    std::vector<Point3D> faceCentroids;
    std::vector<Point3D> faceAreaVectors;

    // --- 3. Perform Calculation ---
    // This function is now available because you included "fvFaces.h".
    // It takes the raw mesh data and populates the output vectors.
    calculateFaceGeometries(Faces, Points, faceCentroids, faceAreaVectors);

    // --- 4. Display Results ---
    // This helper function from "fvFaces.h" prints the results in a formatted way.
    printFaceResults(faceCentroids, faceAreaVectors);

    return 0;
}

