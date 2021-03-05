1: Understanding the fundamentals of ML
2: An overview of linear algebra
3: An overview of a linear regression example



Machine learning (ML) is one of the implicit methods that uses mathematical and statistical approaches to solve tasks.
It is an actively growing discipline, and a lot of scientists and researchers find it to be one of the best ways to move 
forward toward systems acting as human-level artificial intelligence.(AI)


In general, ML approaches have the idea of searching patterns in a given dataset as their basis.
Consider a recommendation system for a news feed, which provides the user with a personalized feed based on 
their previous activity or preferences.
e,g.1: frequencey of some topics appearing in a set of news articiles
performs some predictive analytics, identifies general patterns, and uses them to populate the users' news feed.
e.g.2: In customer relationship management (CRM) systems, ML models are used to analyze sales team activity, to help them to process
the most important requests first.  
e.g.3: ML models are used in business intelligence(BI) and analytics to find essential data points.
e.g.4: HUman resource(HR) departments use ML models to analyze their employees' characteristiscs in order to identify the most effective ones
and use this information when searching applicants for open posistions.


Techniques of ML, mainly two:
Supervised learning and Unsupervised learning

SUPERVISED LEARNING:
Supervised learning is an approach based on the use of labeled data. Labeled data is 
a set of known data samples with corresponding known target outputs.
1: Classficiation models predict some finite and distinct types of categories- - this could be a 
label that identifies if an email is spam or not, or whether an image contains a human face or not.
e.g.: Support Vector Machine(SVM)
2: Regression models predict continuous responses susch as changes in temperature or values of 
currency exchange rates.


UNSUPERVISED LEARNING:
Unsupervised learning is an approach that does not require labeled data and can search hiiden
patterns and structures in an arbitrary kind of data.
THey create models that use intrinsic relations in data to find hidden patterns that they can
use for make prediction.
The most well-known unsupervised learning technique is clustering. 
Clustering involves dividing a given set of data in a limited number of groups according to some
intrinsic properties of data items.


DEALING WITH ML MODELs:
PARAMETERS:
We can split the ML model's parameters into two types.
The first type consists of parameters internal to the model, and we can estimate the values from the training(input) data.

HYPERPARAMETERS:
The second type consists of parameters external to the model, and we cannot estimate their values from training data.
Hyperparameters that are external to the model are usu. called hyperparameters.


PARAMETERIC:
If the model contains a fixed number of internal parameters, it is called parametric.
Otherwise, we can classify it as non-parameteric.

INTERNAL PARAMETERS:
Basically 4:
They are necessart for making predictions.
They define the quality of the model on the given problem.
We can learn them from training data.
Usu., they are a part of the model.
Examples of internal parameters are as follows:
  1:Weights of artificial neural networks(ANNs)
  2:Support vector values for SVM models
  3:Polynomial coefficients for linear regression or logistic regression
  
  
  EXTERNAL PARAMETERS:
  Bascially 4 characteristics:
 1:They are used to configure algorithms that estimate model parameters
 2: The practioner usu. specifies them.
 3: Their estimation is often based on using heruistics
 4: They are speicific to a concrete modelling problem.
 e.g.1: C and sigma parameters used in the SVM algorithm for a classification quality configuration
 e.g. 2: The learning rate parameter that is used in the neural network training process to configure
 algorithm convergence.
 e.g. 3 The k value that is used in the KNN algorithm to configure the number of neighbors.
 
 
 LOSS FUNCTION:
 A function that evaluates how well a model predicts on the data is called a loss function. If predictions are
 very differnt from the target outputs, the loss function will return a value that can be interpreted as a bad one, usu. a large number.
 e.g.1: Specifics of the given problem--for example, if it is a regression or a classification model
 e.g.2: Ease of calculating derivatives
 e.g.3: Percentage of outliers in the dataset
 
 OPTIMIZER:
 IN ML, THE term optimizer is used to define an algorithm that connects a loss function and a technique for
 updating model parameters in response to the values of the loss function.
 
 
 GPU:
 The rise of ML, and esp. deep learning, began after siginificant performance improvement of the modern 
 Graphics Processing Unit.
 
 
 Also, Central Processing Units(CPUs) have instruction sets specially designed for simultaneous numerical computations.
 Such computations are called vectorized, and common vectorized instruction sets are AVx, SSE, and MMx.
 There is also a term Single Instruction Multiple Data(SIMD) for these instruction sets. Many numeric linear algebra libraries,
 such as Eigen, xtensor, VienaCL, and others, use them to improve computational performances.
 
 Tensor representation in computing:
 The most obvious method is a simple linear array in computer memory (random-access memory, or RAM)
 Eigen use column-major ordering:
 PyTorch use row-major ordering:
 So, developers hsould be aware of internal tensor representation in libraries they use, and also take care of this when 
 performing data loading or implementing algorithms from scartch.
