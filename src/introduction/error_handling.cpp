#include <iostream>

#include "opencv2/core/core.hpp"

int main() {
    try {
        /* err code, message, function, file, line */
        throw cv::Exception(1, "My exception", "some func", "some file", 10); 
    } catch(cv::Exception &e) {
        const char *err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
    }
}
