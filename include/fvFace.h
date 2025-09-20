#ifndef FV_FACE_H
#define FV_FACE_H

#include <vector>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <map> // Used to handle neighbour mapping

// Include your custom classes for points and vectors.
#include "Point.h"
#include "Vector.h"

/**
 * @class fvFace
 * @brief Main class to manage all faces in the mesh.
 *
 * This class is instantiated with the raw data extracted from the polyMesh
 * files. It processes this data to create a list of individual face objects,
 * each containing its own geometric and topological information.
 */
class fvFace {
public:
    /**
     * @struct FaceData
     * @brief Holds all geometric and topological data for a single face.
     */
    struct FaceData {
        size_t index_ = 0;
        std::vector<size_t> iNodes_;
        size_t iOwner_ = 0;
        size_t iNeighbour_ = std::numeric_limits<size_t>::max();

        Point  centroid_;
        Vector areaVector_;
        Vector normal_;
        double area_ = 0.0;
        
        // Geometric vectors for interpolation schemes.
        // These are calculated later once cell centroids are known.
        Vector CN_; // Vector from owner cell centroid to face centroid
        Vector T_;  // Vector from owner cell centroid to neighbour cell centroid

        bool isBoundary() const { return iNeighbour_ == std::numeric_limits<size_t>::max(); }
    };

    // --- Constructor ---
    /**
     * @brief Constructs the fvFace manager object from raw polyMesh data.
     * @param Faces Raw face-to-node connectivity list.
     * @param Points Raw point coordinates list.
     * @param Owners Raw owner cell index for each face.
     * @param Neighbours Raw neighbour cell index for internal faces.
     */
    fvFace(const std::vector<std::vector<size_t>>& Faces,
           const std::vector<std::vector<double>>& Points,
           const std::vector<size_t>& Owners,
           const std::vector<size_t>& Neighbours) 
    {
        // 1. Convert raw double points to your Point class objects
        std::vector<Point> allPoints;
        allPoints.reserve(Points.size());
        for (const auto& p_coords : Points) {
            allPoints.emplace_back(p_coords[0], p_coords[1], p_coords[2]);
        }

        // 2. Create a map for efficient neighbour lookup
        // The `neighbour` file only lists internal faces. We map the global face index
        // to its neighbour cell.
        std::map<size_t, size_t> internalFaceToNeighbour;
        size_t internalFaceCounter = 0;
        for (size_t i = 0; i < Owners.size(); ++i) {
            // If the owner is greater than the running count of neighbours, it's a boundary face
            if (Owners[i] < Neighbours.size() && internalFaceCounter < Neighbours.size()) {
                 if (Owners[i] == internalFaceCounter) {
                    internalFaceToNeighbour[i] = Neighbours[Owners[i]];
                    internalFaceCounter++;
                 }
            }
        }


        // 3. Create all individual face objects
        allFaces_.reserve(Faces.size());
        for (size_t i = 0; i < Faces.size(); ++i) {
            FaceData face;
            face.index_ = i;
            face.iNodes_ = Faces[i];
            face.iOwner_ = Owners[i];

            // Check if this face has a neighbour from our map
            if (internalFaceToNeighbour.count(i)) {
                face.iNeighbour_ = internalFaceToNeighbour.at(i);
            } else {
                face.iNeighbour_ = std::numeric_limits<size_t>::max(); // Boundary face
            }
            
            if (face.iNodes_.size() < 3) continue;

            // Perform geometric calculations for this face
            calculateCentroid(face, allPoints);
            calculateAreaVector(face, allPoints);
            
            face.area_ = std::sqrt(face.areaVector_ * face.areaVector_);
            
            if (face.area_ > 1e-12) {
                double inv_area = 1.0 / face.area_;
                face.normal_ = Vector(face.areaVector_.X() * inv_area,
                                      face.areaVector_.Y() * inv_area,
                                      face.areaVector_.Z() * inv_area);
            }
            
            allFaces_.push_back(face);
        }

        // 4. Populate the boundary flags vector for efficient access
        isBoundaryFlags_.reserve(allFaces_.size());
        for(const auto& face : allFaces_) {
            isBoundaryFlags_.push_back(face.isBoundary());
        }
    }
    
    // --- Public Methods ---

    /**
     * @brief Returns the total number of faces.
     */
    size_t size() const {
        return allFaces_.size();
    }

    /**
     * @brief Provides access to a single face's data.
     * @param index The global index of the face.
     * @return A constant reference to the FaceData object.
     */
    const FaceData& operator[](size_t index) const {
        return allFaces_[index];
    }
    
    /**
     * @brief Provides access to the pre-computed list of boundary flags.
     * @return A constant reference to the vector of booleans (true if boundary).
     */
    const std::vector<bool>& getBoundaryFlags() const {
        return isBoundaryFlags_;
    }
    
    /**
     * @brief Calculates the CN and T vectors required for interpolation.
     * This method should be called after the cell centroids have been calculated.
     * @param cellCentroids A vector containing the centroids of all cells.
     */
    void calculateInterpolationVectors(const std::vector<Point>& cellCentroids) {
        for (auto& face : allFaces_) {
            const Point& ownerCentroid = cellCentroids[face.iOwner_];
            const Point& faceCentroid = face.centroid_;

            // CN vector: from owner cell centroid to face centroid
            face.CN_ = Vector(faceCentroid.X() - ownerCentroid.X(),
                              faceCentroid.Y() - ownerCentroid.Y(),
                              faceCentroid.Z() - ownerCentroid.Z());

            // T vector: from owner to neighbour (only for internal faces)
            if (!face.isBoundary()) {
                const Point& neighbourCentroid = cellCentroids[face.iNeighbour_];
                face.T_ = Vector(neighbourCentroid.X() - ownerCentroid.X(),
                                 neighbourCentroid.Y() - ownerCentroid.Y(),
                                 neighbourCentroid.Z() - ownerCentroid.Z());
            }
        }
    }


private:
    // --- Member Variables ---
    std::vector<FaceData> allFaces_;
    std::vector<bool> isBoundaryFlags_; // Stores true (1) if a face is boundary, false (0) otherwise.

    // --- Private Calculation Methods ---
    void calculateCentroid(FaceData& face, const std::vector<Point>& allPoints) {
        double sumX = 0.0, sumY = 0.0, sumZ = 0.0;
        for (size_t nodeIdx : face.iNodes_) {
            sumX += allPoints[nodeIdx].X();
            sumY += allPoints[nodeIdx].Y();
            sumZ += allPoints[nodeIdx].Z();
        }
        size_t numVertices = face.iNodes_.size();
        face.centroid_ = Point(sumX / numVertices, sumY / numVertices, sumZ / numVertices);
    }

    void calculateAreaVector(FaceData& face, const std::vector<Point>& allPoints) {
        face.areaVector_ = Vector(0.0, 0.0, 0.0);
        for (size_t j = 0; j < face.iNodes_.size(); ++j) {
            const Point& p1 = allPoints[face.iNodes_[j]];
            const Point& p2 = allPoints[face.iNodes_[(j + 1) % face.iNodes_.size()]];
            
            Vector v1(p1.X() - face.centroid_.X(), p1.Y() - face.centroid_.Y(), p1.Z() - face.centroid_.Z());
            Vector v2(p2.X() - face.centroid_.X(), p2.Y() - face.centroid_.Y(), p2.Z() - face.centroid_.Z());

            Vector cross_product = v1 ^ v2;
            Vector scaled_cross = Vector(cross_product.X() * 0.5, cross_product.Y() * 0.5, cross_product.Z() * 0.5);
            face.areaVector_ = face.areaVector_ + scaled_cross;
        }
    }
};

#endif // FV_FACE_H