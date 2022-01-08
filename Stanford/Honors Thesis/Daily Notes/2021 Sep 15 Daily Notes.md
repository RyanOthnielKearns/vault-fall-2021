# Motivation
- Lots of AI scientists purport that model explainability and interpretability are intended to engender trust in models
	- What do they mean by trust?
	- Do they agree on what they mean?
	- Is it epistemically *rational* that explanation / interpretation might entail trust in black-box models?
	- Is it epistemically rational to infer trust from a suitable kind of explanation or interpretation of black-box behavior? Under what conditions, if at all?
		- Specifically: a supervised classifier (restricting domain to decision trees, random forests, LSTMs, regression classifiers, deep neural classifiers -- and omitting reinforcement learning / probabilistic graphical models / etc)...? Does this help?
# Approach
1. What have AI/ML scientists been saying about explanation/interpretation/trust?
2. What does philosophy have to say about explanation & trust that may be helpful?
3. Is it rational to infer trust from explanation? If so, when?
4. What pragmatic import does this have for the XAI literature?

# Unstructured reading notes
Very cool passage from [[Zachary C. Lipton 2018, "The Mythos of Model Interpretability".pdf|Lipton 2018]]:
> In some cases, transparency may be at odds with the broader objectives of AI (artificial intelligence). Some arguments against black-box algorithms appear to preclude any model that could match or surpass human abilities on complex tasks. As a concrete example, the short-term goal of building trust with doctors by developing transparent models might clash with the longer-term goal of improving health care.

[[Doshi-Velez et al., "The Role of Explanation in Algorithmic Trust".pdf|Doshi-Velez et al.]] say something similar here:
> In particular, there exist concerns that explainable algorithmic decision-making systems would be so difficult to engineer that legally requiring explanation would stifle innovation; that *explanation would come at the price of some other performance objective*, such as decreased system accuracy; ...

(emphasis my own). They also cite B. Brenner, “GDPR’s right to explanation: the pros and the cons” and J. Burrell, “How the machine ‘thinks’: Understanding opacity in machine learning algorithms” for this claim.

I think it's easy to imagine trusting a superhuman doctor with uninterpretable procedures, provided their standard of care and rate of success are demonstrably high. In this case, we see that interpretability is not *necessary* for trusting black box systems, at least at a high and intuitive level.

This also points to the possibility that trust may not be the ultimate goal in our relationships with AI systems. Are we ok relying on a superhuman decision-making system that we know to be benevolent but provably untrustworthy? Does such a position even make sense? I think answering this might depend on and inform what we mean by trust and reliance in the specific context as pertains to human-machine interaction.

From my reading of [[Doshi-Velez et al., "The Role of Explanation in Algorithmic Trust".pdf]], I decided to start compiling a list of [[References of Trust in the Explainable Machine Learning Literature]]. I think this list will be helpful as a preamble to my paper, and as an answer to the question, "Why should machine learning researchers care for a philosophical treatment of trust?"

In general, though, this paper seems more concerned with the legal requisite for explanation in GDPR rather than an analytical treatment of "trust".

The authors do, however, mention this:
> Thus, the question of algorithmic trustworthiness is more complicated than a binary choice between systems that generate explanation or systems that do not. (2)

This seems promising -- a note that "algorithmic trustworthiness" (whatever that is) is defined separately from algorithmic explicability. This meshes with my intuitive judgement that explanations may not necessitate or suffice for trustworthiness in a variety of settings (see the note above about superhuman doctors).