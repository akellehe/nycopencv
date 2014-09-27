#include <iostream>

#include "opencv2/core/core.hpp"

int main(){
    // create a big 8Mb matrix
    std::cout << "Creating an 8MB Matrix" << std::endl;
    cv::Mat A(1000, 1000, CV_64F);

    // create another header for the same matrix;
    // this is an instant operation, regardless of the matrix size.
    std::cout << "Creating another header for the same matrix." << std::endl;
    cv::Mat B = A;
    // create another header for the 3-rd row of A; no data is copied either
    std::cout << "Creating a header for the 3rd row." << std::endl;
    cv::Mat C = B.row(3);
    // now create a separate copy of the matrix
    std::cout << "Copying the entire thing" << std::endl;
    cv::Mat D = B.clone();
    // copy the 5-th row of B to C, that is, copy the 5-th row of A
    // to the 3-rd row of A.
    std::cout << "Copying the 5th row of B to C" << std::endl;
    B.row(5).copyTo(C);
    // now let A and D share the data; after that the modified version
    // of A is still referenced by B and C.
    std::cout << "Setting A to D" << std::endl;
    A = D;
    // now make B an empty matrix (which references no memory buffers),
    // but the modified version of A will still be referenced by C,
    // despite that C is just a single row of the original A
    std::cout << "Releasing B" << std::endl;
    B.release();

    // finally, make a full copy of C. As a result, the big modified
    // matrix will be deallocated, since it is not referenced by anyone
    std::cout << "Deallocating C" << std::endl;
    C = C.clone();

    std::cout << "Done!" << std::endl;
    return 0;
}
