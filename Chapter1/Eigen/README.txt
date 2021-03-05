(base) zcw@mukoedo1993:~/C++_machine_learning_clone/machine_learning_C-/Chapter1/Eigen$ ./linalg_eigen
Zero matrix:
0 0 0
0 0 0
0 0 0
Identity matrix:
1 0 0
0 1 0
0 0 1
Random vector:
 0.680375
-0.211234
 0.566198
Comma initialized matrix:
1 2 3
4 5 6
7 8 9
Row vector mapped to array:
1 2 3 4
Matrix mapped to array:
1 4 7
2 5 8
3 6 9
elemnt wise a*b :
 1  4
 9 16
element wise a / b:
1 2
3 4
element wise a = b *4:
 4  8
12 16
matrices a + b:
 5 10
15 20
matrixce a+=b: 
 5 10
15 20
matrices a * b :
 35  50
 75 110
Random 4x4 matrix :
   0.59688   0.536459   0.257742    0.83239
  0.823295  -0.444451  -0.270431   0.271423
 -0.604897    0.10794  0.0268018   0.434594
 -0.329554 -0.0452059   0.904459  -0.716795
Random 5x5 matrix :
 0.213938 -0.686642 -0.563486  0.275105  0.542715
-0.967399 -0.198111 0.0258648 0.0485743 0.0534899
-0.514226 -0.740419  0.678224 -0.012834  0.539828
-0.725537 -0.782382   0.22528   0.94555 -0.199543
 0.608353  0.997849 -0.407937 -0.414966  0.783059
Middle part of 4 times 4 matrix: 
-0.444451 -0.270431
  0.10794 0.0268018
Modified middle of 4*4 matrix :
   0.59688   0.536459   0.257742    0.83239
  0.823295         -0         -0   0.271423
 -0.604897          0          0   0.434594
 -0.329554 -0.0452059   0.904459  -0.716795
Modified row of 4 times 4 matrix :
   0.59688   0.536459   0.257742    0.83239
   3.82329          3          3    3.27142
 -0.604897          0          0   0.434594
 -0.329554 -0.0452059   0.904459  -0.716795
Modified col of 4 times 4 matrix :
   0.59688   0.536459  0.0644355    0.83239
   3.82329          3       0.75    3.27142
 -0.604897          0          0   0.434594
 -0.329554 -0.0452059   0.226115  -0.716795
Random 2 times 4 matrix :
-0.433371  0.615449 -0.860489 0.0519907
-0.295083  0.838053  0.898654 -0.827888
Sum broadcast over columns: 
99.5666 100.615 99.1395 100.052
99.7049 100.838 100.899 99.1721
(base) zcw@mukoedo1993:~/C++_machine_learning_clone/machine_learning_C-/Chapter1/Eigen$ ./linreg_eigen
Estimated parameters vector :4.00851
0.30001
Estimated with normal equation parameters vector :4.00852
0.30001
Predicted values: 
4.00851 0.30001
4.00851 0.60002
4.00851 0.90003
4.00851 1.20004
4.00851 1.50005
b_norm is: 4.00852
0.30001
Predicted(norm) values: 
 4.00852  0.30001
 4.00852  0.60002
 4.00852 0.900029
 4.00852  1.20004
 4.00852  1.50005