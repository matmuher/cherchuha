#include <MolbertFilters.hpp>

// std array? only quadratic? only odd?
ImageKernel identity = {1,
                        {   
                            {0, 0, 0},
                            {0, 1, 0},
                            {0, 0, 0}
                        }
                        };

ImageKernel box_blur = {1./9,
                        {   
                            {1, 1, 1},
                            {1, 1, 1},
                            {1, 1, 1}
                        }
                        };