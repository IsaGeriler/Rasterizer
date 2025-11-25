# Rasterizer
## Overview
This project implements the standard graphics pipeline using C++ and a custom linear algebra library. It handles the full transformation chain (MVP), rasterization, and shading without relying on external graphics APIs like OpenGL or DirectX.

_Note: Detailed documentation on the mathematics/theory, implementation of the rasterization algorithms and perspective-correct interpolation is currently being written and will be updated soon._

## Key Features
* Rasterization: Triangle rasterization using edge functions and barycentric coordinates.
* Math Library: Custom Matrix (4x4) and Vector implementations.
* Pipeline: Full Model-View-Projection transformation chain.
* Optimization: Z-Buffering for visibility and Backface Culling.
* Shading: Perspective-correct attribute interpolation and Lambertian shading.

## Final Result
### Rainbow 3D Bunny (Geometry Proof)
https://github.com/user-attachments/assets/1bdd06df-8fc0-47b0-84db-2201bb89a2da

### Shaded 3D Bunny (Lighting Proof)
https://github.com/user-attachments/assets/464bf5ab-592d-4a65-ab4c-a30b31f02f26
