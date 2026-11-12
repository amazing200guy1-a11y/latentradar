#ifndef LATENT_SIMD_H
#define LATENT_SIMD_H

#include <stddef.h>
#include <math.h>

#define LATENT_DIM 128

/**
 * Computes dot product of two 128-dimensional activation vectors.
 */
float latent_dot_product(const float* a, const float* b, size_t dim);

/**
 * Computes Euclidean (L2) norm of a vector.
 */
float latent_l2_norm(const float* a, size_t dim);

/**
 * Computes cosine similarity between residual activation vector and safe centroid.
 * Range: [-1.0, 1.0]
 */
float latent_cosine_similarity(const float* activation, const float* centroid, size_t dim);

#endif /* LATENT_SIMD_H */
