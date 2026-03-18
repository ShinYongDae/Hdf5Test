#include <iostream>
#include <string>
#include <vector>
#include "H5Cpp.h"

using namespace H5;

//void readZygoMetaDataSet(const std::string& filename) {
//	try {
//		// Open the DATX file
//		H5File file(filename, H5F_ACC_RDONLY);
//
//		// Access the "Attributes" group
//		Group attrGroup = file.openGroup("Attributes");
//
//		// Find the specific metadata subgroup (usually labeled, often the first)
//		hsize_t numObjs = attrGroup.getNumObjs();
//		std::string metaSubgroupName0 = attrGroup.getObjnameByIdx(0);
//		std::string metaSubgroupName1 = attrGroup.getObjnameByIdx(1);
//		Group metaGroup0 = attrGroup.openGroup(metaSubgroupName0);
//		Group metaGroup1 = attrGroup.openGroup(metaSubgroupName1);
//
//		// Read specific Attribute: Wavelength
//		Attribute wvlAttr = metaGroup1.openAttribute("Data Context.Data Attributes.attr.lateral_res");
//		double LateralRes;
//		wvlAttr.read(PredType::NATIVE_DOUBLE, &LateralRes);
//		std::cout << "LateralRes: " << LateralRes * 1e9 << " nm" << std::endl;
//
//		//// Read Attribute: Pixel Size (X)
//		//Attribute xResAttr = metaGroup.openAttribute("X Pixel Size");
//		//double xRes;
//		//xResAttr.read(PredType::NATIVE_DOUBLE, &xRes);
//		//std::cout << "X Pixel Size: " << xRes * 1e6 << " um" << std::endl;
//
//	}
//	catch (FileIException& error) {
//		error.printErrorStack();
//	}
//	catch (GroupIException& error) {
//		error.printErrorStack();
//	}
//	catch (AttributeIException& error) {
//		error.printErrorStack();
//	}
//}

void readZygoMetaDataSet(const std::string& filename) {
	try {
		// Open the DATX file
		H5File file(filename, H5F_ACC_RDONLY);

		// Access the "Attributes" group
		Group attrGroup = file.openGroup("/Data/Surface");

		// Find the specific metadata subgroup (usually labeled, often the first)
		hsize_t numObjs = attrGroup.getNumObjs();
		std::string metaSubgroupName0 = attrGroup.getObjnameByIdx(0);

		// Open the dataset containing the spatial data (often "intensity" or "phase")
		DataSet dataset = attrGroup.openDataSet(metaSubgroupName0);

		// Get dataspace to understand dimensions
		DataSpace dataspace = dataset.getSpace();
		hsize_t dims[2];
		dataspace.getSimpleExtentDims(dims, NULL);
		std::cout << "Data Dimensions: " << dims[0] << " x " << dims[1] << std::endl;

		// Allocate memory to read data (assuming float/double)
		std::vector<float> data(dims[0] * dims[1]);

		// Read data
		dataset.read(data.data(), PredType::NATIVE_FLOAT);

		// Data is now in 'data' vector - process as needed
		std::cout << "Successfully read data." << std::endl;
	}
	catch (FileIException& error) {
		error.printErrorStack();
	}
	catch (GroupIException& error) {
		error.printErrorStack();
	}
	catch (AttributeIException& error) {
		error.printErrorStack();
	}
}

int main()
{
	std::string datxFile = "example.datx";
	readZygoMetaDataSet(datxFile);
	return 0;
}


/*
#include <iostream>
#include <string>
#include <vector>
#include "H5Cpp.h"

// Example to read an attribute (e.g., magnification)
void readDatxMetadata(const std::string& filename) 
{
	try {
		// Open file in read-only mode
		H5::H5File file(filename, H5F_ACC_RDONLY);

		// --- Accessing Data ---
		// Based on typical datx structures, data is in datasets.
		// Replace "YourDataSetName" with actual names found in HDFView

		// Example: Reading a string metadata attribute
		H5::DataSet dataset = file.openDataSet("/MetaData");
		H5::DataSpace dataspace = dataset.getSpace();
		hsize_t dims[2];
		int ndims = dataspace.getSimpleExtentDims(dims, NULL);

		H5::StrType str_type(H5::PredType::C_S1, H5T_VARIABLE);
		std::string objName;
		dataset.read(objName, str_type);
		std::cout << "Objective: " << objName << std::endl;

		//// Example: Reading numerical data (e.g., scaling)
		//H5::DataSet scaleSet = file.openDataSet("/Parameters/PixelScale");
		//double scaleValue;
		//scaleSet.read(scaleValue, H5::PredType::NATIVE_DOUBLE);
		//std::cout << "Pixel Scale: " << scaleValue << std::endl;

	}
	catch (H5::FileIException& error) {
		error.printErrorStack();
	}
	catch (H5::DataSetIException& error) {
		error.printErrorStack();
	}
}

int main() 
{
	std::string datxFile = "example.datx";
	readDatxMetadata(datxFile);
	return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <string>
//#include "hdf5.h"
#include "H5Cpp.h"

int main() 
{
	// 1. Open the .datx file
	hid_t file_id = H5Fopen("example.datx", H5F_ACC_RDONLY, H5P_DEFAULT);

	// 2. Open the dataset holding the attributes (e.g., /Measurement/Data)
	//hid_t dataset_id = H5Dopen2(file_id, "/Measurement/Data", H5P_DEFAULT);
	hid_t dataset_id = H5Dopen2(file_id, "/MetaData", H5P_DEFAULT);

	// 3. Open the attribute by name
	const char* attr_name = "Path"; // Replace with actual Zygo attribute name
	hid_t attr_id = H5Aopen_by_name(dataset_id, "Link", attr_name, H5P_DEFAULT, H5P_DEFAULT);

	// 4. Get type and space to read
	hid_t attr_type = H5Aget_type(attr_id);

	// Example: Reading a string attribute
	hsize_t size = H5Tget_size(attr_type);
	std::string attr_data(size, '\0');
	H5Aread(attr_id, attr_type, &attr_data[0]);

	std::cout << "Attribute Value: " << attr_data << std::endl;

	// 5. Close everything
	H5Tclose(attr_type);
	H5Aclose(attr_id);
	H5Dclose(dataset_id);
	H5Fclose(file_id);

	return 0;
}
*/


/*
#include <iostream>
#include <string>
#include "H5Cpp.h"

using namespace H5;

void readLateralResolution(const std::string& filename) {
	try {
		// Open the HDF5 file
		H5File file(filename, H5F_ACC_RDONLY);

		//// Example path to metadata - this may need adjustment based on
		//// specific Zygo MX software version
		//DataSet dataset = file.openDataSet("/Measurement/Surface");
		//H5::Attribute attr0 = dataset.openAttribute("X Converter");
		//// Retrieve attribute value (assuming string for example)
		//hsize_t attrSize = attr0.getStorageSize();
		//std::string attrValue;
		//attrValue.resize(attrSize);
		//attr0.read(attr0.getDataType(), &attrValue[0]);
		//std::cout << "Metadata Link/Value: " << attrValue << std::endl;

		//// Read the string data from the attribute/dataset
		//H5::StrType str_type(H5::PredType::C_S1, H5T_VARIABLE);
		//std::string path_data;
		//dataset.read(path_data, str_type);
		//std::cout << "CopyLink Path/Metadata: " << path_data << std::endl;

		// Open the root group or a specific dataset where attributes are stored
		// Typically, metadata is in the root or a 'Data' group
		Group root = file.openGroup("/Measurement/Attributes");

		// Define Attribute Name (Example: "sample_interval" or similar)
		// Note: Actual attributes vary based on Mx version
		//std::string attrName = "sample_interval";

		Attribute attr;
		std::string attrName;

		//attrName = "Data Context.Data Attributes.attr.wavelength_in";
		attrName = "Data Context.Data Attributes.Wavelength:Value";
		if (root.attrExists(attrName)) {
			attr = root.openAttribute(attrName);

			// Assuming the attribute is a double
			double wavelength_in;
			attr.read(PredType::NATIVE_DOUBLE, &wavelength_in);
			std::cout << "Wavelength: " << wavelength_in << " Meters" << std::endl;
		}
		else {
			std::cout << "Attribute " << attrName << " not found." << std::endl;
		}

		//attrName = "Data Context.Data Attributes.attr.lateral_res";
		attrName = "Data Context.Lateral Resolution:Value";
		if (root.attrExists(attrName)) {
			attr = root.openAttribute(attrName);

			// Assuming the attribute is a double
			double lateralResolution;
			attr.read(PredType::NATIVE_DOUBLE, &lateralResolution);
			std::cout << "Lateral Resolution : " << lateralResolution << " Meters" << std::endl;
		}
		else {
			std::cout << "Attribute " << attrName << " not found." << std::endl;
		}
	}
	catch (FileIException &error) {
		error.printErrorStack();
	}
	catch (AttributeIException &error) {
		error.printErrorStack();
	}
}

int main() {
	std::string datxFile = "example.datx";
	readLateralResolution(datxFile);
	return 0;
}
*/


/*
#include <iostream>
#include "H5Cpp.h"

using namespace H5;

int main() {
	try {
		// .datx 파일 열기
		H5File file("example.datx", H5F_ACC_RDONLY);

		// 메타데이터가 포함된 그룹 또는 데이터 세트 열기
		// (Zygo 버전에 따라 실제 경로는 다를 수 있음)
		Group group = file.openGroup("/Measurement/Attributes");

		// "Lateral Resolution" 또는 "X Scale" 속성 읽기
		Attribute attr = group.openAttribute("Mode");
		std::string unit;
		attr.read(H5::PredType::C_S1, &unit);
		std::cout << "Path: " << unit << " meters" << std::endl;
		//Attribute attr = group.openAttribute("X Scale");
		//double x_resolution;
		//attr.read(PredType::NATIVE_DOUBLE, &x_resolution);
		//std::cout << "Lateral Resolution (X): " << x_resolution << " meters" << std::endl;

	}
	catch (FileIException& error) {
		error.printErrorStack();
	}
	catch (DataSetIException& error) {
		error.printErrorStack();
	}
	return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <string>
#include <H5Cpp.h>

using namespace H5;

void readDatxResolution(const std::string& filename) {
	try {
		Exception::dontPrint(); // Disable automatic error printing
		H5File file(filename, H5F_ACC_RDONLY);

		// Open the "data" group where topography is stored
		Group dataGroup = file.openGroup("Measurement");

		// Open the dataset containing the spatial data (often "intensity" or "phase")
		DataSet dataset = dataGroup.openDataSet("Surface");

		// Get dataspace to understand dimensions
		DataSpace dataspace = dataset.getSpace();
		hsize_t dims[2];
		dataspace.getSimpleExtentDims(dims, NULL);
		std::cout << "Data Dimensions: " << dims[0] << " x " << dims[1] << std::endl;

		// Allocate memory to read data (assuming float/double)
		std::vector<float> data(dims[0] * dims[1]);

		// Read data
		dataset.read(data.data(), PredType::NATIVE_FLOAT);

		// Data is now in 'data' vector - process as needed
		std::cout << "Successfully read data." << std::endl;

		// Access attributes to find spatial spacing
		Attribute attrX = dataset.openAttribute("X Converter"); // Or "pixel_spacing"
		Attribute attrY = dataset.openAttribute("Y Converter");

		//double xSpacing, ySpacing;
		//attrX.read(PredType::NATIVE_DOUBLE, &xSpacing);
		//attrY.read(PredType::NATIVE_DOUBLE, &ySpacing);
		DataType datatype;
		//std::vector<std::string> attr_value;
		//std::vector<int, float, int, int> Array;
		std::string attr_value;
		datatype = attrX.getDataType(); // Read the Attribute data type		
		attrX.read(datatype, attr_value);

		std::cout << "Spatial Resolution (X): " << attr_value << " um" << std::endl;
		//std::cout << "Spatial Resolution (Y): " << ySpacing << " um" << std::endl;

		// Cleanup
		attrX.close();
		attrY.close();
		dataset.close();
		file.close();

	}
	catch (FileIException& error) {
		std::cerr << "File Error: " << error.getDetailMsg() << std::endl;
	}
	catch (DataSetIException& error) {
		std::cerr << "Dataset Error: " << error.getDetailMsg() << std::endl;
	}
	catch (AttributeIException& error) {
		std::cerr << "Attribute Error: " << error.getDetailMsg() << std::endl;
	}
}

int main() {
	std::string datxFile = "example.datx";
	readDatxResolution(datxFile);
	return 0;
}
*/

/*
#include <iostream>
#include <string>
#include "H5Cpp.h"

using namespace H5;

typedef struct stConverter
{
	H5::StrType strCat;
	H5::StrType strUnit;
	//std::string str[2];
	//std::string strUnit;
	//int n0, n1;
	double dVal[4];
	//int n3;
};

int main() 
{
	const std::string FILE_NAME("example.datx");
	const std::string DATASET_NAME("/Measurement/Surface"); // 파일 구조에 따라 다를 수 있음
	const std::string ATTR_NAME_0("Interferometric Scale Factor");
	const std::string ATTR_NAME_1("Unit");
	const std::string ATTR_NAME_2("Wavelength");
	const std::string ATTR_NAME_3("X Converter");
	const std::string ATTR_NAME_4("Y Converter");
	const std::string ATTR_NAME_5("Z Converter");
	const std::string ATTR_NAME_6("Coordinates");

	try {
		// 1. 파일 열기
		H5File file(FILE_NAME, H5F_ACC_RDONLY);

		// 2. 데이터셋 열기
		DataSet dataset = file.openDataSet(DATASET_NAME);

		// 3. Wavelength 속성 열기
		Attribute attr0 = dataset.openAttribute(ATTR_NAME_0);
		Attribute attr1 = dataset.openAttribute(ATTR_NAME_1);
		Attribute attr2 = dataset.openAttribute(ATTR_NAME_2);
		Attribute attr3 = dataset.openAttribute(ATTR_NAME_3);
		Attribute attr4 = dataset.openAttribute(ATTR_NAME_4);
		Attribute attr5 = dataset.openAttribute(ATTR_NAME_5);
		Attribute attr6 = dataset.openAttribute(ATTR_NAME_6);

		DataType datatype;
		// 4. 데이터 타입 확인 및 값 읽기
		double scale = 0.0;
		attr0.read(PredType::NATIVE_DOUBLE, &scale);
		std::cout << "scale: " << scale << std::endl;

		datatype = attr0.getDataType(); // Read the Attribute data type		
		// Determine specific type
		if (datatype == PredType::NATIVE_FLOAT) {
			std::cout << "Data Type: 32-bit Float (Single)" << std::endl;
		}
		else if (datatype == PredType::NATIVE_SHORT) {
			std::cout << "Data Type: 16-bit Integer" << std::endl;
		}
		else if (datatype == PredType::NATIVE_DOUBLE) {
			std::cout << "Data Type: 64-bit Float (Double)" << std::endl;
		}
		else {
			std::cout << "Data Type: Other" << std::endl;
		}


		H5::StrType strType(H5::PredType::C_S1, H5T_VARIABLE);
		std::string unit;
		attr1.read(strType, unit);
		std::cout << "unit: " << unit << std::endl;

		double wavelength = 0.0;
		attr2.read(PredType::NATIVE_DOUBLE, &wavelength);
		std::cout << "Wavelength: " << wavelength << std::endl;

		
		//datatype = attr3.getDataType(); // Read the Attribute data type		
		//// Determine specific type
		//if (datatype == PredType::NATIVE_FLOAT) {
		//	std::cout << "Data Type: 32-bit Float (Single)" << std::endl;
		//}
		//else if (datatype == PredType::NATIVE_SHORT) {
		//	std::cout << "Data Type: 16-bit Integer" << std::endl;
		//}
		//else if (datatype == PredType::NATIVE_DOUBLE) {
		//	std::cout << "Data Type: 64-bit Float (Double)" << std::endl;
		//}
		//else {
		//	std::cout << "Data Type: Other" << std::endl;
		//}
		//std::string attr_value;
		//attr3.read(datatype, attr_value); // Read the Attribute value (assuming it's a string based on the Attribute class)
		//std::cout << "X Converter: " << attr_value << std::endl;

		int coordinates[4] = { 0 };
		datatype = attr6.getDataType(); // Read the Attribute data type	
		attr6.read(datatype, coordinates);
		std::cout << "Coordinates: " << coordinates[2] << std::endl;

		//double converterX = 0.0;
		//stConverter converterX;
		//datatype = attr3.getDataType(); // Read the Attribute data type	
		//attr3.read(datatype, &converterX);
		//std::cout << "X Converter: " << converterX << std::endl;

		//double converterY = 0.0;
		//attr4.read(PredType::NATIVE_DOUBLE, &converterY);
		//std::cout << "Y Converter: " << converterY << std::endl;

		//double converterZ = 0.0;
		//attr5.read(PredType::NATIVE_DOUBLE, &converterZ);
		//std::cout << "Z Converter: " << converterZ << std::endl;
	}
	catch (FileIException error) {
		error.printErrorStack();
	}
	catch (DataSetIException error) {
		error.printErrorStack();
	}
	catch (AttributeIException error) {
		std::cerr << "속성을 찾을 수 없습니다: " << ATTR_NAME_0 << std::endl;
	}

	return 0;
}

*/