#include<dlib/matrix.h>
#include<iostream>
using std::cout;
using std::endl;

int main(){
    // definitions
    {
        //compile time sized matrix
        dlib::matrix<double, 3, 1>y;

        //dynamically sized matrix
        dlib::matrix<double> m(3,3);

        //later we can change size of this matrix
        m.set_size(6, 6);
    }


        //initializations
    {
        dlib::matrix<double> m(3, 3);
        m = 1., 2., 3. , 4., 5., 6., 7., 8., 9.;
        cout <<  "Matrix from comma operator\n" << m << endl;

        //wrap array
        double data[] = {1, 2, 3, 4, 5, 6};
        auto m2 = dlib::mat(data, 2, 3);

        //matrix elements can be accessed with () operator
        m(1, 2)=300;
        cout <<"Matrix element updated\n" << m << endl;


        //Also you can initialize matrix with some predefined values
        auto a = dlib::identity_matrix<double>(3);
        cout << "Identity matrix \n" << a << endl;

        auto b = dlib::ones_matrix<double>(3, 4);
        cout << "Ones matrix \n"<< b << endl;

        auto c = dlib::randm(3, 4);
        cout << "Random matrix \n" << c <<endl;
    }

    //arithmetic operations
    {
        dlib::matrix<double> a(2, 2);
        a = 1, 1, 1, 1;

        dlib::matrix<double> b(2, 2);
        b = 2, 2, 2, 2;

        auto c = a + b;
        cout << "c = a + b \n" << c << endl;

        auto e = a * b;//real matrix multiplication
        cout << "e = a dot b \n" << e<< endl;

        a += 5;
        cout << "a += 5 \n" << a << endl;

        auto d = dlib::pointwise_multiply(a, b); // element wise multiplication
        cout << "d = a * b \n" << d <<endl;

        auto t = dlib::trans(a); //transpose matrix
        cout << "transposed matrix a \n" << t << endl;
    }
        //partial access
        {
            dlib::matrix<float, 4, 4>m;
            m = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16;
            auto sm =
                dlib::subm(m, dlib::range(1, 2),
                          dlib::range(1, 2)); //original matrix can't be updated
                cout <<"Sub matrix \n" << static_cast<dlib::matrix<float,2,2>>(sm) << endl;

                dlib::set_subm(m, dlib::range(1, 2), dlib::range(1, 2)) = 100;
                cout << "Updated sub matrix \n" << m << endl;
        }

        // there are no implicit broadcasting in dlib
        {
            //we can simulate broadcasting with partial access
            dlib::matrix<float, 2, 1> v;
            v = 10, 10;
            dlib::matrix<float, 2, 3> m;
            m = 1, 2, 3, 4, 5, 6;

            for( int i = 0; i < m.nc(); ++i){//dlib::matrix::nc No. of columns
                dlib::set_colm(m, i) += v;
            }

            cout << "Matrix with updated columns \n" << m <<endl;
        }
    
    
}

/*
(base) zcw@mukoedo1993:~/machine_learning_CPP/Chapter1/Dlib/build$ ./linalg_dlib
Matrix from comma operator
1 2 3 
4 5 6 
7 8 9 

Matrix element updated
  1   2   3 
  4   5 300 
  7   8   9 

Identity matrix 
1 0 0 
0 1 0 
0 0 1 

Ones matrix 
1 1 1 1 
1 1 1 1 
1 1 1 1 

Random matrix 
0.840188 0.394383 0.783099  0.79844 
0.911647 0.197551 0.335223  0.76823 
0.277775  0.55397 0.477397 0.628871 

c = a + b 
3 3 
3 3 

e = a dot b 
4 4 
4 4 

a += 5 
6 6 
6 6 

d = a * b 
12 12 
12 12 

transposed matrix a 
6 6 
6 6 

Sub matrix 
-9.30856e-29   4.5723e-41 
-8.59256e-29   4.5723e-41 

Updated sub matrix 
  1   2   3   4 
  5 100 100   8 
  9 100 100  12 
 13  14  15  16 

Matrix with updated columns 
11 12 13 
14 15 16 

*/