#Stanford #Stanford-Winter-2022 #CS #CS224N #NLP #linguistics #deep-learning #lecture-notes 
___
- today: moving away from DL towards the structure of human language / linguistics
- two things to cover today:
	1. constituency representations
	2. dependency representations

# Lecture Plan
**Syntactic Structure and Dependency Parsing**
1. Syntactic Structure & dependency parsing
2. Dependency grammar and treebanks
3. Transition-based dependency parsing
4. Neural dependency parsing

*this is the lecture for assignment 3*
- building a neural dependency parser using PyTorch
- a lot of scaffolding in assign3, used for teaching PyTorch really

# The linguistic structure of sentences
**Phrase structure** organizes words into *nested* constituents

Two views:
1. Constituency = phrase structure grammar = context-free grammars (**CFGs**)

- build sentences by putting constituent parts together in increasingly complex ways
- to look at human languages, start by looking at **context-free languages**
	- e.g. finite state languages / finite automata from #CS103: can produce long sequences but don't have the nested structure we need
	- tons and tons of words, but those seem to organize themselves into a smaller collection of categories
		- adjectives, nouns, prepositions, verbs, articles (in NLP these are *determiners*), etc.
			- widespread use of determiners is not as common in languages other than English
			- "the cuddly cat" = Det + A + N --> NP (*noun phrase*)
			- NP = Det (A)* N (**Kleene Star** to express any number of adjectives are valid)
		- words combine into phrases, which combine into bigger phrases, then sentences
			- "the cuddly cat by the door" is one Noun Phrase, consisting of a Noun Phrase + a Prepositional Phrase (which is a preposition + another Noun Phrase)
				- can keep going: "the cuddly cat by the door to the study"
	- **context-free grammar rules**
		- NP -> Det A* N {PP* VP*}
		- VP -> V (NP) PP*

2. **Dependency structure**
	- shows which words depend on (modify, attach to, or are arguments of) which other words
	- e.g. "Look in the large crate in the kitchen by the door"
		- "in the large crate" is a dependent of "Look"
		- "the" and "large" are both modifiers of "crate"
		- (using *universal dependencies*) also the preposition "in" is a modifier of "crate" also (not always the case... prepositions are kind of complicated)
		- context-free grammar phrase structure builds up sort of similar "units" given a sentence, but the understanding is different from dependency structure

## Why do we need sentence structure?
- humans communicate complex ideas by composing words into bigger units to convey complex meanings
- listeners need to work out what modifies / attaches to what
	- they aren't given the structure! just the ordered list of words
- a computer model need to understand sentence structure in order to interpret language correctly

### Prepositional phrase attachment ambiguity
- pretty general consequence of human languages
- "San Jose cops kill man with knife"
- "Scientists count whales from space"
- prepositional phrase coming after a noun and a verb -- you *always* have two choices for where to attach the prepositional phrase
	- either a modifier of the object or subject of the sentence
	- "with knife" can either modify "San Jose cops" or "man"
	- compare with programming languages: also comprised of context-free languages, but there is *no* absolute ambiguity, due to structure & conventions
		- convention: e.g. that in `if {} if {} else {}` the `else` happens after the second (nearest) `if`
- these types of ambiguities multiply as prep. phrases get tacked on at the end
	- "The board approved its acquisition by Royal Trustco Ltd. of Toronto for $27 a share at its monthly meeting"
	- choices are made s.t. you still get something that nests well in a context-free grammar -- this slightly limits the number of choices
	- the sequence is called the **Catalan numbers** -- number of ambiguities that arise after $n$ PP additions is the $n$th catalan number
		- this number occurs often when there are tree-based limiting structures on the ways things can be organized

### Coordination scope ambiguity
- coordinations like "and" and "or" -- how you interpret the *scope* is ambiguous (in many languages)
- "Shuttle veteran and longtime NASA executive Fred Gregory appointed to board"
	- is Fred Gregory both a shuttle veteran and NASA exec, or is the shuttle veteran a different person? The "and" has ambiguous scope

### Adjectival / Adverbial Modifier Ambiguity
"Students get first hand job experience"

### Verb Phrase (VP) attachment ambiguity
"Mutilated body washes up on Rio beach to be used for Olympics beach volleyball"
- does "to be used for Olympics beach volleyball" modify "Rio beach" or "mutilated body"?

## Dependency paths help extract semantic interpretation
- can use this structural knowledge to get out other facts, e.g. formal relations btwn objects of the sentence like protein interactions
- dependency syntax postulates that syntactic structure consists of *relations between lexical items*
	- normally *binary asymmetric relations* called *dependencies* (drawn as arrows)
		- we follow Tesniere's convention who pointed them from head to dependent
		- we usually add a fake ROOT word so every actual word is dependent of precisely 1 other node
	- commonly, the relations are *typed* with the type of interaction (the name of the grammatical relations)
	- a sentence starts with a word at the "head" of the dependency structures which traverse down to the leaves
- goes back a long way, to the 5th century with Panini's grammar (& other 1st milleniumn Arabic grammarians)
	- dominant approach in 20th century in the East -- better for languages like Russian with free-er word order, inflected languages
- in early days of AI: people just handwrote rules for CFGs
	- in late 80s / early 90s -- different idea to collect parsed sentences (annotated data) to form "Universal Dependencies treebanks"
	- treebanks give us a lot
		- reusability of the labor of parsing (parsers, POS-taggers)
		- prevalence of different parts of language (distributional info. for linguists)
		- broad coverage of all weird things that happen, rather than availability for individual linguists
		- a way of evaluating NLP systems
			- gives you sentences w/ their correct structure
			- moving to a framework for automatic evaluation, competitions and benchmarks etc.

# Dependency Conditioning Preferences
what are the straightforward sources of information?
1. bilexical affinities
	- we want the dependency to actually be plausible!
2. dependency distance
	- should be between nearby words
3. intervening material
	- dependencies shouldn't often span intervening verbs / punctuation
4. valency of heads
	- what kinds of dependents, on what sides, are usual for a type of head?
		- e.g. usual for a noun to have a determiner to the left, but can't have two determiners to the left (but can have two adjectives)

## To dependency parse:
- some constraints
	- only one word is a dependent of ROOT
	- want a DAG, so no cycles
	- these two produce a *tree* structure
- final issue: whether arrows can cross or not
	- crossing arrows are **non-projective**

# Methods of Dependency Parsing
1. **Dynamic programming**
	- e.g. Eisner (1996)
2. **Graph algorithms**
	- create minimum-spanning tree for a sentence
3. **Constraint satisfaction**: work by eliminating edges that don't match constraints
4. **Transition-based parsing** or **deterministic dependency parsing**
	- greedy choice of attachments made by machine learning classifiers
	- a bit alternative, but highly effective and fast!
	- sequence of bottom-up actions like ==**shift-reduce parsing**==

## Greedy transition-based parsing
### Shift-reduce parser
- parser has a *stack* $\sigma$, a *buffer* $\beta$, a set of *dependency arcs* $A$, and a set of actions
	- stack starts with the root symbol
	- buffer starts with the input sentence
1. Shift: move a word from the buffer onto the stack
2. Left-arc$_r$: first way to build a dependency
	- remove element from stack and add it to set of dependencies
	- $\sigma\mid w_i\mid w_j, \beta, A\rightarrow\sigma\mid w_j, \beta, A\cup\{r(w_j, w_i)\}$
3. Right-arc$_r$
	- $\sigma\mid w_i\mid w_j, \beta, A\rightarrow\sigma\mid w_i, \beta, A\cup\{r(w_i, w_j)\}$
	- Taking the thing on the right as the dependent, deleting it from the stack
- finish with $\sigma = [w]$ and $\beta = \varnothing$ (buffer empty)

#### Example
"I ate fish"
- [ [root] ] + I + ate + fish
- Perform a shift action to get [ [root] + I ] + ate + fish
- We only want [root] to take one child, so can't right or left shift with the I, so instead shift again: [ [root] + I + ate ] + fish
- Now we know that "I" is the subject of "ate", so we can conduct a left-shift operation
- Then a shift, then a right arc, then a right arc should complete the parsing:
	- Root -> ate -- N.subj. --> I; ate -- obj --> fish

### MaltParser (Nivre and Hall 2005)
- we just have to explain how to choose the parser's next action!
	- use machine learning to state transition -- each action predicted by a discriminative classifier
	- max of three untyped choices to choose from
- no search (in the simplest form) in this way
- model's accuracy isn't quite SoTA (fractionally below), but *fast linear-time parsing*
	- great for the web!
- a lot of categorical, symbolic indicator features
	- so binary and super sparse (dim = $10^6 - 10^7$)

### Improving: dense, distributed representations
- use $d$-dimensional dense vectors instead (word embeddings)

- Extract a set of tokens based on the stack / buffer positions
	- extract word, POS, dependencies, etc.
- result: simple feed-forward neural network multi-class classifier
	- input layer, hidden layer with hidden weight+bias and ReLU activation, output layer w/ softmax
		- rectified linear unit (ReLU) $ReLU(z) = \max(z, 0)$: just zeroes all negative values -- has been super successful nonlinearity because it directly propagates information
	- log loss (cross-entropy error) will be back-propagated to the embeddings