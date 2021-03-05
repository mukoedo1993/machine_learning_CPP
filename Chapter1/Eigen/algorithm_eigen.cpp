//We have built the Eigen
//I personally symbollic linked it on my Ubuntu machine.
#include<Eigen/Dense>
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;


using MyMatrix33f = Eigen::Matrix<float, 3, 3>;
using MyVector3f = Eigen::Matrix<float, 3, 1>;
using MyMatrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;


int main()
{
    //declaration
    MyMatrix33f a;
    MyVector3f v;
    MyMatrix m(10, 15);


    //initialization
    a = MyMatrix33f::Zero();
    cout << "Zero matrix:\n" << a << endl;

    a = MyMatrix33f::Identity();
    cout << "Identity matrix:\n" << a << endl;

    v = MyVector3f::Random();
    cout << "Random vector:\n" << v << endl;

    a << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "Comma initialized matrix:\n" << a<< endl;

    int data[] = {1, 2, 3, 4};
    Eigen::Map<Eigen::RowVectorXi> v_map(data, 4);
    cout << "Row vector mapped to array:\n" << v_map << endl;

    vector<float> vdata = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    //Eigen::Map: it will use memory and values from the underlying object, and will not allocate the additional memory.
    Eigen::Map<MyMatrix33f> a_map(vdata.data());//std::vector::data returns the underlying built-in array.
    cout << "Matrix mapped to array:\n" << a_map << endl;

    //arithmetic
    {
        Eigen::Matrix2d a;
        a << 1, 2, 3, 4;
        Eigen::Matrix2d b;
        b << 1, 2, 3, 4;

        //element-wise operations:
        Eigen::Matrix2d result = a.array()*b.array();
        cout << "elemnt wise a*b :\n" << result << endl;

        result = a.array() / b.array();
        cout << "element wise a / b:\n" << a << endl;

        a = b.array() * 4;
        cout << "element wise a = b *4:\n" << a << endl;

        //matrix operations:
        result = a + b;
        cout << "matrices a + b:\n" << result << endl;

        a += b;
        cout << "matrixce a+=b: \n" <<result << endl;

        result = a * b;
        cout <<"matrices a * b :\n" << result << endl;

    }

    //partial access:
    //dynamic MatrixXf
    {
    Eigen::MatrixXf m = Eigen::MatrixXf::Random(4, 4);
    cout << "Random 4x4 matrix :\n" << m << endl;

    Eigen::MatrixXf m_ = Eigen::MatrixXf::Random(5, 5);
    cout << "Random 5x5 matrix :\n" << m_ << endl;


    Eigen::Matrix2f b =
    m.block(1, 1, 2, 2);//copying the middle part of matrix
    cout << "Middle part of 4 times 4 matrix: \n"<< b << endl;

    m.block(1, 1, 2, 2) *= 0; // change values in original matrix
    cout << "Modified middle of 4*4 matrix :\n" << m << endl;

    m.row(1).array() += 3;
    cout << "Modified row of 4 times 4 matrix :\n" << m << endl;

    m.col(2).array() /= 4;
    cout << "Modified col of 4 times 4 matrix :\n" << m << endl;
    }

    //broadcasting
    {
        Eigen::MatrixXf mat = Eigen::MatrixXf::Random(2, 4);
        cout << "Random 2 times 4 matrix :\n" << mat <<endl;

        Eigen::VectorXf v(2); //column vector
        v << 100, 100;
        mat.colwise() += v;
        cout << "Sum broadcast over columns: \n"<< mat << endl;
    }    

    
}