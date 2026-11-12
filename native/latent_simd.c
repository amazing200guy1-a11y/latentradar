#include "latent_simd.h"
#include <math.h>

float latent_dot_product(const float* a, const float* b, size_t dim) {
    float sum = 0.0f;
    size_t i = 0;
    /* Loop unrolling for high-throughput tensor projection */
    for (; i + 4 <= dim; i += 4) {
        sum += a[i] * b[i]
             + a[i+1] * b[i+1]
             + a[i+2] * b[i+2]
             + a[i+3] * b[i+3];
    }
    for (; i < dim; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

float latent_l2_norm(const float* a, size_t dim) {
    float dot = latent_dot_product(a, a, dim);
    return sqrtf(dot);
}

float latent_cosine_similarity(const float* activation, const float* centroid, size_t dim) {
    float norm_a = latent_l2_norm(activation, dim);
    float norm_c = latent_l2_norm(centroid, dim);
    if (norm_a < 1e-7f || norm_c < 1e-7f) {
        return 0.0f;
    }
    float dot = latent_dot_product(activation, centroid, dim);
    return dot / (norm_a * norm_c);
}
