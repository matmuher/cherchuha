#include <MolbertFilters.hpp>

// std array? only quadratic? only odd?

// https://en.wikipedia.org/wiki/Kernel_(image_processing)

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

ImageKernel edge_detection = {1,
                        {   
                            {0, -1, 0},
                            {-1, 4, -1},
                            {0, -1, 0}
                        }
                        };

ImageKernel gauss_blur = {1./16,
                        {   
                            {1, 2, 1},
                            {2, 4, 2},
                            {1, 2, 1}
                        }
                        };

ImageKernel sharpen = {1,
                        {   
                            {0, -1, 0},
                            {-1, 5, -1},
                            {0, -1, 0}
                        }
                        };