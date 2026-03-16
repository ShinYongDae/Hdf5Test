#include <iostream>
#include <string>
#include "H5Cpp.h"

using namespace H5;

void readLateralResolution(const std::string& filename) {
	try {
		// Open the HDF5 file
		H5File file(filename, H5F_ACC_RDONLY);

		// Open the root group or a specific dataset where attributes are stored
		// Typically, metadata is in the root or a 'Data' group
		Group root = file.openGroup("/Measurement/Attributes");

		// Define Attribute Name (Example: "sample_interval" or similar)
		// Note: Actual attributes vary based on Mx version
		//std::string attrName = "sample_interval";

		Attribute attr;
		std::string attrName;

		attrName = "Data Context.Data Attributes.attr.wavelength_in";
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

		attrName = "Data Context.Data Attributes.attr.lateral_res";
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