#include <iostream>
#include <vector>
#include <iomanip> // For std::fixed and std::setprecision

// Your custom header for reading mesh data.
// Assumed to contain extractFaces, extractPoints, extractOwners, extractNeighbours.
#include "../include/dictionary.h"

// Your custom classes for 3D points and vectors.
#include "../include/Point.h"
#include "../include/Vector.h"

// The new class-based header for managing face geometry.
#include "../include/fvFace.h"

int main() {
    // --- 1. Load All Necessary Mesh Data ---
    std::cout << "Loading mesh data from polyMesh files..." << std::endl;
    std::vector<std::vector<size_t>> Faces;
    extractFaces(Faces);
    std::vector<std::vector<double>> Points;
    extractPoints(Points);
    std::vector<size_t> Owners;
    extractOwners(Owners);
    std::vector<size_t> Neighbours;
    extractNeighbours(Neighbours);

    std::cout << "Successfully loaded data for: " << std::endl;
    std::cout << " - " << Points.size() << " points" << std::endl;
    std::cout << " - " << Faces.size() << " faces" << std::endl;
    std::cout << " - " << Owners.size() << " owner entries" << std::endl;
    std::cout << " - " << Neighbours.size() << " neighbour entries (internal faces)" << std::endl;
    
    // --- 2. Instantiate the fvFace Class ---
    std::cout << "\nInstantiating fvFace class and calculating geometries..." << std::endl;
    fvFace faceManager(Faces, Points, Owners, Neighbours);
    std::cout << "Calculations complete for " << faceManager.size() << " faces." << std::endl;

    // NOTE: To calculate CN and T vectors, you would first need to calculate cell centroids
    // and then call the following method. For this test, they will be (0,0,0).
    // std::vector<Point> cellCentroids = ... calculate cell centroids ...;
    // faceManager.calculateInterpolationVectors(cellCentroids);


    // --- 3. Test and Display Results ---
    std::cout << "\n--- Verifying Calculated Face Data (Displaying in requested order) ---" << std::endl;
    std::cout << std::fixed << std::setprecision(6);

    const auto& boundaryFlags = faceManager.getBoundaryFlags();

    size_t faces_to_print = 5;
    for (size_t i = 0; i < faceManager.size(); ++i) {
        if (i < faces_to_print || i >= faceManager.size() - faces_to_print) {
            const auto& face = faceManager[i];

            std::cout << "\n----------------------------------------" << std::endl;

            // 1. iNodes
            std::cout << "  - iNodes:          { ";
            for(size_t node_idx : face.iNodes_) {
                std::cout << node_idx << " ";
            }
            std::cout << "}" << std::endl;

            // 2. index
            std::cout << "  - Face Index:      " << face.index_ << std::endl;

            // 3. iOwner
            std::cout << "  - iOwner:          " << face.iOwner_ << std::endl;

            // 4. iNeighbour
            std::cout << "  - iNeighbour:      ";
            if (boundaryFlags[i]) {
                std::cout << "N/A (Boundary Face)" << std::endl;
            } else {
                std::cout << face.iNeighbour_ << std::endl;
            }

            // 5. Centroid
            std::cout << "  - Centroid:        (" << face.centroid_.X() << ", "
                                                 << face.centroid_.Y() << ", "
                                                 << face.centroid_.Z() << ")" << std::endl;

            // 6. Normal Vector
            std::cout << "  - Normal Vector (n): " << face.normal_ << std::endl;

            // 7. Face Area
            std::cout << "  - Scalar Area |S|: " << face.area_ << std::endl;

            // 8. CN Vector
            std::cout << "  - Vector CN:       " << face.CN_ << " (Requires cell centroids)" << std::endl;
            
            // 9. T Vector
            std::cout << "  - Vector T:        ";
            if(boundaryFlags[i]) {
                std::cout << "N/A (Boundary Face)" << std::endl;
            } else {
                std::cout << face.T_ << " (Requires cell centroids)" << std::endl;
            }
        }
        if (i == faces_to_print && faceManager.size() > (2 * faces_to_print)) {
            std::cout << "\n          ... (skipping middle faces) ...\n";
        }
    }

    return 0;
}

