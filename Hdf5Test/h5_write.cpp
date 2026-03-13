#include <iostream>
#include <vector>
#include "H5Cpp.h"

using namespace H5;
using namespace std;

const string FILE_NAME("example.h5");
const string DATASET_NAME("IntArray");
const int NX = 5; // 행
const int NY = 6; // 열

int main(void) {
    // 1. 데이터 준비 (2D 배열)
    int data[NX][NY];
    for (int i = 0; i < NX; i++)
        for (int j = 0; j < NY; j++)
            data[i][j] = i + j;

    try {
        // 2. HDF5 파일 생성 (H5F_ACC_TRUNC: 파일이 있으면 덮어씀)
        H5File* file = new H5File(FILE_NAME, H5F_ACC_TRUNC);

        // 3. 데이터 공간 정의 (2차원)
        hsize_t dims[2] = {NX, NY};
        DataSpace dataspace(2, dims);

        // 4. 데이터셋 생성 (Int형)
        DataSet* dataset = new DataSet(file->createDataSet(
            DATASET_NAME, PredType::NATIVE_INT, dataspace));

        // 5. 데이터셋에 데이터 쓰기
        dataset->write(data, PredType::NATIVE_INT);

        // 6. 리소스 해제
        delete dataset;
        delete file;
        cout << "파일 '" << FILE_NAME << "' 생성 완료." << endl;

    } catch (FileIException& error) {
        error.printErrorStack();
        return -1;
    } catch (DataSetIException& error) {
        error.printErrorStack();
        return -1;
    } catch (DataSpaceIException& error) {
        error.printErrorStack();
        return -1;
    }

    return 0;
}
