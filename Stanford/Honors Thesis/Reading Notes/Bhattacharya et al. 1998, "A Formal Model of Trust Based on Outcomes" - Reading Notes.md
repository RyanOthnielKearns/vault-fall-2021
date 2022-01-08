# [[Bhattacharya et al. 1998, “A Formal Model of Trust Based on Outcomes” (ANNOTATED).pdf|Bhattacharya et al. 1998, "A formal model of trust based on outcomes"]]
## #reading-notes 
Tags: #trust 
___
This paper comes from the management science / economics world, and proposes a formal theory of trust that bridges existing theories from psychology and economics. According to the authors, many existing psychological theories assume inherent trustfulness as a personality trait, which downplays the situation-specificity of trust. At the same time, economic theories are overly concerned with situation-specific constraints and don't consider the interpersonal relationship in transactions where trust is important. So, a composite mathematical theory must encode both aspects of the situation and the trust-giving and -receiving parties.

The authors of this paper purport to do this. For a sequential scenario, in which agent 1 acts before agent 2, agent 1's trust of agent 2 can be given as:
$$T_{1,2}|a_1^* = Pr(\mu_1 > 0 | a_1^*) = \sum_{x\in\gamma_1}Pr(\alpha_1 = x | a_1^*) = \sum_{x\in\gamma_1}\sum_{a_2\in A_2} F_1(x_1; a_1^*, a_2)\cdot c_1(a_2|a_1^*)$$

- $\mu_1$ is the "goodness" of an outcome $x_1$, and when $\mu_1 > 0$ the outcome is favorable for agent 1
- $\alpha_1$ is the function taking an action ($a_1$) to an outcome ($x_1$). In a special case it is determinate, but we assume in general that it can be somewhat random
- $A_2$ is the set of all actions that agent 2 may take after agent 1 has taken their decided action ($a_1^*$)
- $F_1$ is the function taking joint actions from agents 1 and 2 to outcomes for agent 1. $F_2$ is defined similarly
- $c_1(a_2 | a_1^*)$ is agent 1's *conjecture* as to what action agent 2 will take

There are additional technical details I'm omitting, including the case where the actions are simultaneous, and what happens when actions are determinate and outcomes visible (**hint**: trust boils down just to conjectures $c$). But the main takeaway is that this model defines trust as the product $F(\cdot)\cdot c(\cdot)$ of the outcomes function and the conjecture function across different possible worlds, weighted by the probabilities of those worlds. Mentioning back to the first paragraph here, it is the authors' opinion that economists focus too much on the former term, while psychologists focus too much on the latter.

The authors also define trust in words:
> Trust is an expectancy of positive (or nonnegative) outcomes that one can receive based on the expected action of another party in an interaction characterized by uncertainty (462).

This theory is one of so-called "outcome" trust, because agents should be more trustworthy when the expectancy of a positive outcome for them is higher.

Note: this theory does not apply to trust in single-action instances, like "trusting" your car to start.