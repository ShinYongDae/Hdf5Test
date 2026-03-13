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

