#include <iostream>
#include <vector>
#include <string>
#include "H5Cpp.h"

// Note: Ensure your compiler is linked against HDF5 libraries
int main() 
{
    std::string filename = "example.datx";
    
    try {
        // Open the HDF5 DATX file
        H5::H5File file(filename.c_str(), H5F_ACC_RDONLY);
        
        // Open the "Phase" dataset (path depends on Mx version, usually /Measurement/0/Phase)
        // Adjust path based on your specific DATX structure
        H5::DataSet dataset = file.openDataSet("/Measurement/Surface");
        
        // Get datatype and dataspace
        H5::DataType datatype = dataset.getDataType();
        H5::DataSpace dataspace = dataset.getSpace();
        
        // Get dimensions
        hsize_t dims[2];
        dataspace.getSimpleExtentDims(dims, NULL);
        int rows = dims[0];
        int cols = dims[1];
        std::cout << "Data size: " << rows << " x " << cols << std::endl;
        
        // Read data into vector
        std::vector<double> data(rows * cols);
        dataset.read(data.data(), H5::PredType::NATIVE_DOUBLE);
        
        // Process data (x, y, z... where z is surface height)
        std::cout << "First data point: " << data[0] << std::endl;
        
    } catch (H5::FileIException &error) {
        error.printErrorStack();
    } catch (H5::DataSetIException &error) {
        error.printErrorStack();
    }
    
    return 0;
}