Following primarily from [[Nguyen 2021, "Trust as an Unquestioning Attitude" - Reading Notes|Nguyen]] and [[Buechner and Tavani 2011, "Trust and multi-agent systems- applying the 'diffuse, default approach' to experiments involving artificial agents" - Reading Notes|Buechner and Tavani's]] work on trust in non-agential settings, our goal here is to formalize a conception a *four-place predicate* relating to trust^[Here in saying four-place predicate "related" to trust we're leaving room for the allowance that $T$ does not actually *mean* trust but rather defines a set of contextual scenarios in which trust is appropriate.]:
$$T(a, b, x, C)$$
Where
1. $a$ is the trustor -- in these settings we only consider human trustors
2. $b$ is the trustee
3. $x$ is the action $b$ is trusted to undertake
4. $C$ is a multiset of contextual *facts* describing the relationship between $a$, $b$, and $x$

We can rely on the set of conditions under which trust obtains that [[Buechner and Tavani 2011, "Trust and multi-agent systems- applying the 'diffuse, default approach' to experiments involving artificial agents" - Reading Notes|Buecher and Tavani]] contribute. This pertains to a trusting relationship between $A$ and $B$:
1. $A$ has a *normative expectation* that $B$ will do *such-and-such*;
2. $B$ is responsible for what it is that $A$ normatively expects her to do;
3. $A$ has the disposition to normatively expect that $B$ will do such-and-such responsibly;
4. $A$'s normative expectation that $B$ will do such-and-such can be mistaken;
5. Subsequent to the satisfaction of the above conditions, $A$ develops a disposition to trust $B$. ([[Buechner and Tavani 2011, “Trust and multi-agent systems- applying the “diffuse, default model” of trust to experiments involving artificial agents” (partial annotations).pdf|Buechner and Tavani 2011, 41]])

Buechner and Tavani call this the "Strawson-Holton-Walker" account of trust, after the three researchers primarily responsible for its origin. I do not think that these conditions are particularly objectionable at the outset, but something can be said immediately about the use of "such-and-such" in clauses 1, 3, and 4. We should just specify "such-and-such" with a third variable, $x$, and specify in 5 that "$A$ develops a disposition to trust $B$ *to do $x$*." I may trust my dentist to perform adequate dental care without trusting her to prove modal logic theorem or water my cactus; this relationship can be one of trust specific to one or more discrete actions^[Credit to [[Nguyen 2021, “Trust as an Unquestioning Attitude” (annotated).pdf|(Nguyen 2021, 21)]] for this observation].

Thus, rewritten with $x$ in mind, our conditions would look like this:
1. $A$ has a *normative expectation* that $B$ will do $x$;
2. $B$ is responsible for $x$;
3. $A$ has the disposition to normatively expect that $B$ will do $x$ responsibly;
4. $A$'s normative expectation that $B$ will do $x$ can be mistaken;
5. Subsequent to the satisfaction of the above conditions, $A$ develops a disposition to trust $B$ to do $x$.

Buechner and Tavani go on to explain how they think the Strawson-Holton-Walker model fails to account for trust outside of interpersonal relationships. They instead want an account that extends to cases of trust between persons and "non-human entities such as institutions, animals, and artificial agents" (42). Specifically, the notion of *responsibility* falls apart, because we cannot justifiably hold non-human entities responsible for what they're relied on.

So, what I want to do is investigate how Buechner and Tavani and Nguyen's theories (among maybe others?) can be adapted to a *context-specific* account of trust that
1. works for non-human entities, and
2. is responsive in the right ways to transparency and explanation.

A lot of researchers posit a connection between trust, transparency, and explanation, though there's no appratus to my knowledge that explains how these concepts might interact. A suitable formulation of trust *for the XAI literature(???)* would be one that responds appropriately to transparency's role in modifying trust.

We can actually draw up this account of transparency -> trust without taking a hard stance on whether transparency is basically beneficial or detrimental to trust. Increasing transparency only serves to extend the context set $C$, moving questions of trust to a different model where the $T$ predicate might hold for certain trustors $A$.
___
- Margaret Urban Walker talks about "zones" of default trust -- we can consider such zones model-theoretically and encapsulate them in our context variable $C$!
	- She also talks about such zones as "unreflective and habitual background... for specific episodes and relationships of trust and entrusting" (p. 85) -- we don't consciously reflect on what behaviors are appropriate within these zones
		- Does [[Nguyen 2021, "Trust as an Unquestioning Attitude" - Reading Notes|Nguyen]] have anyting to say about Walker? Apparently not...
	- Something that's key to "diffuse, default trust" is the notion that you can hold a normative expectation about service from, say, an airline, without *knowing* all of the component pieces of the airline's inner functioning. E.g., you can trust United to get you to your destination without individually trusting the ticketing agent, the baggage personnel, air traffic control, etc. You might be wholly ignorant of ATC and yet still trust United, and feel resentment *toward the airline* when that trust is let down
- Should read [[Responsible_computers_A_case_for_ascribi.pdf|Stahl 2006]] for a discussion on why the ascription of "responbility" to non-human entities could be appropriate

___
Now moving to a more formal document on this subject, [[202111281602 Trust as a Four-Place Relation, Take I]]