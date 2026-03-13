#include <iostream>
#include <string>
#include "H5Cpp.h"

using namespace H5;
using namespace std;

const string FILE_NAME("example.h5"); // 읽을 HDF5 파일명
const string DATASET_NAME("IntArray"); // 데이터셋 이름
//const string DATASET_NAME("int_dataset"); // 데이터셋 이름
const int NX = 5; // 행 크기
const int NY = 6; // 열 크기
//const int NY = 10; // 열 크기

int main(void) {
    // 1. 데이터셋 읽기용 버퍼 메모리 할당 (2차원 배열)
    int data_out[NX][NY];

    try {
        // HDF5 예외 처리 비활성화 (오류 발생 시 직접 처리하기 위해)
        Exception::dontPrint();

        // 2. HDF5 파일 열기 (읽기 전용)
        H5File file(FILE_NAME, H5F_ACC_RDONLY);

        // 3. 데이터셋 열기
        DataSet dataset = file.openDataSet(DATASET_NAME);

        // 4. 데이터셋의 데이터 유형(Data Type) 가져오기
        DataType datatype = dataset.getDataType();

        // 5. 데이터셋 읽기 (파일 데이터를 메모리 버퍼로 복사)
        // PredType::NATIVE_INT: 파일 데이터 유형을 C++ 네이티브 int로 변환
        dataset.read(data_out, PredType::NATIVE_INT);

        // 6. 읽은 데이터 출력
        cout << DATASET_NAME << " 데이터 내용:" << endl;
        for (int i = 0; i < NX; i++) {
            cout << "[";
            for (int j = 0; j < NY; j++) {
                cout << data_out[i][j] << (j == NY - 1 ? "" : ", ");
            }
            cout << "]" << endl;
        }

    } // 7. try 블록이 끝나면 파일 및 데이터셋은 자동으로 닫힘 (RAII)
    catch (FileIException &error) {
        error.printErrorStack();
        return -1;
    }
    catch (DataSetIException &error) {
        error.printErrorStack();
        return -1;
    }
    catch (DataSpaceIException &error) {
        error.printErrorStack();
        return -1;
    }

    return 0;
}
