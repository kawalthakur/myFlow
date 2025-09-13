This is myFlow : A CFD solver designed to leverage GPUs. 
The Linear Solvers will be optimized for GPUs. 
It uses a polyMesh from OpenFOAM, so that we do not need to develop own mesher and can thus focus on CFD code implementation. 

Initial Goals : 
1. Develop a solver to solve Heat diffusion equation in Steady State (Laplace Equation)
2. Demonstrate a Proof of Concept that Linear Solvers can be implemented in CUDA. 
3. Develop utilities for post-processing the results in Paraview. 

Intermediate Goals : 
1. Develop a solver that can solve Steady State incompressible Navier's Stoke Equation. 
2. Develop advanced Linear Solvers like Conjugate Gradient, subspace solvers for GPUs. 
3. Develop some advance postprocessing utilities. 


