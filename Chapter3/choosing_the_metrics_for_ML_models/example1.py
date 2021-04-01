import numpy as np
import pandas as pd
from sklearn import datasets, linear_model

def metrics(m,X,y):
    yhat = m.predict(X)
    print(yhat)
    SS_Residual = sum((y-yhat)**2)
    SS_Total = sum((y-np.mean(y))**2)
    r_squared = 1 - (float(SS_Residual))/SS_Total
    adj_r_squared = 1 - (1-r_squared)*(len(y)-1)/(len(y)-X.shape[1]-1)
    return r_squared,adj_r_squared
    
data = pd.DataFrame({"x1": [1,2,3,4,5], "x2": [2.1,4,6.1,8,10.1]})
y = np.array([2.1, 4, 6.2, 8, 9])
model1 = linear_model.LinearRegression()
model1.fit( data.drop("x2", axis = 1),y)
metrics(model1,data.drop("x2", axis=1),y)

model2 = linear_model.LinearRegression()
model2.fit( data,y)
metrics(model2,data,y)

data = pd.DataFrame({"x1": [1,2,3,4,5], "x2": [2.1,4,6.1,8,10.1]} )
y = np.array([2.1, 4, 6.2, 8, 9])
model3 = linear_model.LinearRegression()
model3.fit( data,y)
metrics(model3,data,y)


"""
Notes:
Here, Case 1 is the simple case where we have 5 observations
of (x, y). In case 2, we have one more variable which is twice of variable 1 (perfectly correlated with var 1). In case 3, we have produced a slight disturbance in var2 such that it is no longer perfectly correlated with var1.

So, if we fit simple ordinary least squares (OLS) model for each case,
logically we are not providing any extra or useful information to case 2 and case 3 with respect to case 1. So our metric value should not improve for these models. However, it is actually not true for R^2 which gives a 
higher value for model 2 and 3. But your adjusted R^2 takes care of this problem and it is actually decreasing for both cases 2 & 3.
"""




"""
(base) zcw@mukoedo1993:~/machine_learning_CPP/Chapter3/choosing_the_metrics_for_ML_models$ python example1.py
[2.3  4.08 5.86 7.64 9.42]
[2.20666667 4.22       5.76666667 7.78       9.32666667]
[2.20666667 4.22       5.76666667 7.78       9.32666667]
(base) zcw@mukoedo1993:~/machine_learning_CPP/Chapter3/ch
Predicted values are same for both model 1 and model 2 and tehrefore,
r_squared will also be same because it depends only on predicted and 
actual values.
"""
