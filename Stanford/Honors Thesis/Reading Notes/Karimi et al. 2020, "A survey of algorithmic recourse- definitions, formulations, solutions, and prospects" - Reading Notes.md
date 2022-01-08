# Karimi et al. 2020, "A survey of algorithmic recourse: definitions, formulations, solutions, and prospects"
## #reading-notes 
Tags: #explanation #explainable-ai #algorithmic-fairness
___
### Summary
This is a survey paper that delineates two questions one might have about algorithmic decision-making. First, why was a particular decision made? This is a question asking for *explanation*, specifically counterfactual explanation that relies on contrast classes ([[Lipton 1990, "Contrastive explanation" - Reading Notes|Lipton, 1990]]). Second, what could I have done differently to influence the decision the algorithm made? This is a question about *recommendation*, which requires stronger causal knowledge than that required for just contrastive explanations. Put together, answering these two questions for a user amounts to *algorithmic recourse*.

This topic is related to model explainability and interpretability, and also ML fairness and legislature. The authors present a table of algorithms from the past 6 years that provide algorithmic recourse, either by answering question 1 or 2 above. The majority focus on question 1 because it is easier. The bulk of the paper is spent describing the technical details of these different approaches, and how to frame both 1 and 2 as constrained optimization problems in the general case. The authors point out many future directions, including standardizing an online benchmark for evaluating recourse.
___
### 1	Motivation
**Q1**: Why was I rejected the loan?
- Explanation
- Also: what *profile* would have led to me receiving the loan?

**Q2**: What can i do to get the loan in the future?
- Recommendation
- Also: what *actions* would have led me to develop the correct profile?
### 2	Background
- **Contrastive Explanations**: require information about the relationship between input variables $\{X_i\}_{i=1}^D$ and predictions $\hat{Y}$
	- A la David Lewis: the input variables are the "causal history" of the prediction
- **Consequential Recommentations**: require information about the causal relationships betweeen inputs $X_i$ -- "further back" in the causal relationships than explanations
- As a result, generating explanations is easier than generating recommendations
### 3	Formulation
- **Contrastive Explanations**: "the set of counterfactual inputs classified differently from $x$"
	- **Nearest Contrastive Explanation**: the CE with the minimum `dist`$(x, x_F)$
	- Formed as a constrained optimization problem
	- Doesn't directly imply the best course of action to reach that contrastive outcome
- **Consequential Recommendation**: "the set of *feasible* actions that result in $x$ being classified differently"
	- **Minimal Consequential Recommendation**: the CR minimizing `cost`$(\mathbf{a}, x^F)$
		- Solving for this automatically yields a CE (not necessarily the NCE)
- Authors are more interested in the minimal cost recommendations than the most proximate contrastive explanation
#### Defining `dist` and `cost`
- Nontrivial
- Karimi et al. advocate a weighted combination of $l_0$, $l_1$, $l_2$ and $l_\infty$ norms for `dist`
- Cost should encode individual-dependent restrictions, and the difficulty of moving across different distributions (e.g. from the 95th to 99th percentile)
	- Costs needn't be symmetric
#### Plausibility and Actionability (Feasibility)
- Domain-, density-, and prototypical-consistency for plausibility $P(\chi)$
- Actionability $A(x^F)$ divides into actionable/non-actionable and mutable/immutable
	- Interventions can change variables *unconditionally* or *conditionally* (e.g., age can only increase)

#### Datatypes
- Traditionally tabular
- Traditionally heterogenous
	- Requires types of **encoding constraints** to preserve the semantics of variables that might be distributed differently

#### Related formulations
- "Imperceptibility is the anti-thesis of explainability and trust" (6)

### 4	Solution
- Challenges:
	- `dist` or `cost` may be non-linear, non-convex, or non-differentiable
	- Model constraint could be non-linear/monotonic/convex
	- Individual or context-specific constraints may apply
	- Plausibility or actionability might be constrained
- Result: trade-offs:
	- **Optimality**: ideally, identifies a solution if it exists, or else terminates
	- **Perfect coverage**: number of individuals for which the model can identify counterfactual instances
	- **Efficient runtime**
	- **Access**: query access / API / gradients / full ("white-box") access to the model
### 5	Prospects
- Counterfactuals make model predictions more interpretable to developers / users, and also more predictable
- Computing the structural counterfactual, $x^{SCF}$, relies on strong assumptions that the true SCM is exactly known -- what to do with only a partial model?
- Also think about recourse for groups of people in addition to individuals
- Fairness in ML
	- Need to move from a *fairness of prediction* metric to a new *fairness of recourse*
		- Unfairness of recourse implies unfair classification but the opposite direction does not hold -- you can have (demographically) fair prediction with unfair recourse
- **Robustness**: model outputs should not change due to small perturbations in the input
	- You can have robust predictions but non-robust explanations ([[Hancox-Li 2020, "Robustness in machine learning explanations- does it matter?" - Reading Notes|Hancox-Li, 2020]])
- **Model extraction**: using access to a model's predictions (or counterfactual labels) to create a surrogate model
	- Can be used to infer private information on individuals, exploit vulnerabilities, or use the system for free
- Individuals may try to modify their own attributes for better treatment from the model
- Need to unify benchmarks across algorithms solving for recourse