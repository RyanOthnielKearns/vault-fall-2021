# [[Mariarosaria Taddeo 2010, "Modelling Trust in Artificial Agents, A First Step Toward the Analysis of e-Trust".pdf|Taddeo 2010, "Modelling Trust in Artificial Agents, A First Step Toward the Analysis of e-Trust"]]
## #reading-notes 
Tags: #trust #e-trust #trustworthiness #ai #artificial-agents
Date: 2020-11-15
___
This paper develops a model of what the author calls "e-trust", which is trust occurring in online or digital environments. Specifically, the model applies to interactions between Artificial Agents (AAs), which allows the decision calculus to be fully rational.

I summarize several interesting features of the author's characterization of #e-trust:
- E-trust is *rational*, specifically appealing to Kant's regulative ideal of a rational agent, in which the agent chooses the best option for itself given a specific scenario and goal-orientation.
- From the above, e-trust is both goal-oriented and action specific. In other words, it is permissible to trust an AA at one task but distrust them at another task; e-trust is not a global property given to AAs.
- E-trust is a second-order relation that affects first order relations characterizing actions. For example, if AAs $A$ and $B$ transact via the sale ($S$) of some good ($g$), then $S(A,B,g)$. E-trust, $T$, is a second-order relation over transactions like $S$, meaning $T(S(A,B,g))$ will affect the conditions under which $A$ sells $g$ to $B$.
- E-trust has the property of minimizing the trustor's effort and committment to the achievement of a given goal. This happens by *delegation* of an action to the trustee, together with limited supervision of the trustee. The less a trustor trusts, the more they will supervise, or even replace, the actions of the trustee.

Roughly, an algorithm for assessing trustworthiness between AAs is spelled out like the following: an AA calculates the ratio of successful actions to total actions performed by the potential trustee to achieve the same or similar goals (7). The technical meaning or formulation of "similar goals" is left out of the paper. Under this algorithm, e-trust is not calculable *a priori*, since the trustor needs previous actions from the trustee in order to assess it.

Lastly, the author indicates that extending the work to more complex cases, such as those where human agents (HAs) are either trustors or trustees, would be more complex. These cases bring #attitudinarian and #psychological factors into play, where previously only #economic factors (rational factors) were relevant.