# Yarkoni & Westfall 2017, "Choosing Prediction Over Explanation in Psychology: Lessons from Machine Learning"
## #reading-notes 
#explanation #explanation-vs-prediction #prediction
___
### Summary
Yarkoni & Westfall's paper is addressed to the psychology research community, and surveys machine learning methods with an emphasis on making psychology more about *prediction* than explanation. In terms of methodologies, the authors survey overfitting, k-fold cross-validation, and lasso regularization. The authors say that explanation-based theories of psychological mechanisms are
1. Sometimes incapable of predicting future behavior with any accuracy;
2. Due to overfitting, probably to blame in part for the reproducibility crisis in psychology at the moment.

According to the authors, there is pragmatic tension between explanation and prediction. Psychological "model fitting" is about minimizing the $R^2$ quantity, which answers how much a *general* regression model like $y_i = \beta_0 + \beta_1X_{1i} + \beta_2X_{2i}+\epsilon_i$ will err on repeated random samples from a distribution. By contrast, *prediction errors* as measured in machine learning measure errors with set values for each $\beta_i$, rather than re-fitting them for each random sample. In this way $R^2$ is not good for predicting a model's ability to generalize to unseen populations.

The explanation-prediction comparison relates to a similar dichotomy in statistical modeling, from [[Breiman, 2001]]:
1. In the "data modeling" culture, researchers assume data arises from a particular generating process. The primary goal is to estimate the true parameters of that process.
2. In the "algorithmic modeling" culture, the data is instead the result of some potentially unknowable process. The goal is to find an algorithm that produces the same output as the process when given the same input.

According to the authors, these two cultures align with the explanation-focused and prediction-focused cultures within science at large. The authors believe that incorporating predictive perspectives, even just instrumentally through machine learning techniques as outlined above, can help psychology to become a more reliable and reproducible science.