#include <iostream>
#include <string>
#include "H5Cpp.h"

using namespace H5;
using namespace std;

int main() 
{
    const std::string FILE_NAME = "example.datx";
    
    try 
	{
        // 1. DATX 파일 열기 (HDF5 기반)
        H5File file(FILE_NAME, H5F_ACC_RDONLY);

        // 2. 데이터셋 위치 확인 (Zygo 표준 경로 예시: /Data/Surface)
        // ※ 실제 경로는 Mx 소프트웨어 버전에 따라 다를 수 있으므로 HDFView로 확인 권장
        DataSet dataset = file.openDataSet("/Data/Surface/{2F2A75F4-7E35-47B1-B59C-B7A71E3A7613}");

        // 3. 데이터 공간 및 크기 확인
        DataSpace dataspace = dataset.getSpace();
        hsize_t dims_out[2];
        dataspace.getSimpleExtentDims(dims_out, NULL);
        
        std::cout << "Dimensions: " << dims_out[0] << "x" << dims_out[1] << std::endl;

        // 4. 데이터 읽기 (float 배열 등)
        float* data_out = new float[dims_out[0] * dims_out[1]];
        dataset.read(data_out, PredType::NATIVE_FLOAT);

        // 데이터 처리...
		/*
		int NX = dims_out[0]; // 행 크기
		int NY = dims_out[1]; // 열 크기

        // 5. 읽은 데이터 출력
        cout << "/Data/Surface" << " 데이터 내용:" << endl;
        for (int i = 0; i < NX; i++) 
		{
            cout << "[";
            for (int j = 0; j < NY; j++) 
			{
                cout << *(data_out+(i * NX + j)) << (j == NY - 1 ? "" : ", ");
            }
            cout << "]" << endl;
        }*/

        delete[] data_out;

		cout << "Complete reading!!!" << endl;
    } 
	catch (FileIException &error) 
	{
        error.printErrorStack();
    } 
	catch (DataSetIException &error) 
	{
        error.printErrorStack();
    }

    return 0;
}