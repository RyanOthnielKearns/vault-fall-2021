#transparency #trust #explainable-ai #scientific-explanation #philosophy-of-science 
See [[Creel 2020, "Transparency in Complex Computational Systems".pdf|reading]]
2021-11-05
___
- scientists concerned with reliance on opaque computational systems for scientific explanations
	- this seems a separate concern from trust -- they actually want insight, not just performance or security
- upshot: provide clearer definition of computational opacity
	- useful for seeking various "epistemic goods"
		- are you using the system for prediction?
		- employing it to explain scientific phenomena?
		- improving / maintaining the system itself?
- "scientists have capitalized on advances in algorithms and computing power without addressing the epistemic problems that can accompany such advances" (569)

# Why Transparency?
- argument: *we should strive for transparency in complex computation*
	- required by scientists / modelers / the public
	- facilitates scientific explanation and artifact detection
- ==Humphreys==: abandon epistemic transparency and focus on trial-and-error procedures
- ACM Conference on Fairness, Accountability, and Transparency
- ==Sørmo, Cassens, and Aamodt 2005==: disagreement on explicit definitions of transparency makes it hard to progress
- "Lack of explanation for the diagnosis given is cited as a cause of doctors’ *lack of trust* in and therefore *failure to use* devices that assist medical diagnoses" (571)
	- this is from [[Ribiero et al. 2016, "'Why Should I Trust You?' Explaning the Predictions of Any Classifier" - Reading Notes|Ribiero et al. 2016]]
	- two things going on here
		- lack of trust: as a result of lack of explanation!!!
			- seeming to implicate that increase in transparency would increase trust -- how do we square this with [[202110102255 Nguyen 2021, "Transparency is Surveillance" - Reading Notes|Nguyen 2021]] on trust vs. transparency?
		- but also failure to use, or opting not to use out of a lack of trust
			- this seems like the real practical problem
- ==Datta, Tschantz, and Datta 2015== on why we need a standard of transparency to address the "right to explanation" in GDPR
## Why do we need transparency?
"Transparency is necessary to illuminate the relationship between the explanans and the explanandum on some leading accounts of scientific explanation" (571)
- required for "mechanistic explanations" -- identify mechanistic parts and causal interactions btwn parts
- also identify artifacts ("bugs") -- debuggers and visualizations are "transparency" to a degree I guess
- detractors: ==Humphreys==, ==Lenhard==, ==Winsberg==

# Three Varieties of Transparency
1. **Algorithmic** or **functional** transparency
	- e.g., possible to understand the high-level logical rules
		- both of the learning procedure *and* the algorithm that is learned
	- problem even w/ competent human programmers: *kludging* (software fixes made without any theoretical intention)
2. **Structural** transparency
	- how an algorithm is realized in code (multiple realization)
	- one path (==Humphreys==): *modular decomposition*
		- Creel disagrees w/ Humphreys that "real-time tracing" is a central part of transparency (or equivalently that opacity occurs when humans are unable to track a model's behavior in real time)
			- not sure who I agree with here! in trusting certain models in real-world "triage" situations (e.g. emergency room load-balancing, computer vision in combat, nuclear strike detection) it seems like Humphreys' "opacity" seems very relevant
	- can have transparency in principle but not in practice -- e.g., if examing every step of a computation was available but would require more than a human lifetime to parse
		- even this line-by-line reading might not suffice, either, b/c structural opacity can emerge at a higher level, if we don't understand how lower-level steps interact to bring about the algorithm
	- [[Marco Tulio Ribiero et al. 2016, "'Why Should I Trust You?' Explaning the Predictions of Any Classifier".pdf|Ribiero et al. 2016]] on how transparency of the model as a whole differs from that of individual predictions / paths (which may have variable length and complexity)
		- Creel: the correct analysis is the "knowledge of relations between the subcomponents", not traversing all possible paths (578) -- the sum of all tokens does not stand in for the type
	- ==Buckner (2019)== on the differences between modern deep neural networks and their predecessors (e.g. perceptrons)
3. **Run** transparency
	- knowledge of how a program was run in a *particular instance* (incl. hardware & input data)
		- hardware example: damaged sensor equipment -- necessary to understand bit-flipping errors, e.g. with space-grade hardware
		- input data example: COMPAS... a "garbage in, gabage out" data problem
	- requires a particular run on the "actual machine" to analyze
- these feel related to Marr's levels of computation!

## When does opacity occur?
1. Deliberately concealed
2. When information is shared by users that cannot fully understand (==(Wagenknecht 2014, 484)==)
	- related: [[Hardwig 1991, "The Role of Trust in Knowledge" - Reading Notes|Hardwig 1991]]

- Creel is only considering opacity for skilled creators / users (not these two above)

## How to the three forms of transparency relate?
- **dissociable**: can be exhibited independently

# Solutions for Transparency
## 1. Post Hoc Explanation (LIME)
- Local Interpretable Model-agnostic Explanations (LIME) from [[Ribiero et al. 2016, "'Why Should I Trust You?' Explaning the Predictions of Any Classifier" - Reading Notes|Ribiero et al. 2016]]
	- explain the predictions of a classifier by fitting a linear model to the pattern of prediction
	- via Creel, a type of functional transparency -- does not demystify the actual decision space (so no structural / run transparency)
	- doctors find the model untrustworthy because there's no available transparency --> when given transparency, the situation might be alleviated, but *not* because you've come to trust, but you've traded the trustworthiness problem with a kind of surveillance
- Google DeepDream feature reconstruction
	- called "visualization" attempts at transparency
	- increases *run transparency*
	- Creel criticizes the explanatory criterion in the researcher's work as a kind of "essentialism about categories" (585)
		- human constraints on what counts as good explanation in practice are nontrivial / not always properly motivated

# Conclusion
- complex computation --> ineliminable opacity
- transparency / interpretability rationalized by widespread efforts to increase transparency / accountability (587)
	- ==does this seem circular??==