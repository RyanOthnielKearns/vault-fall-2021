i.
	i. One advantage of dot product attention compared to multiplicative is fewer parameters to store, since you don't need to store the attention weight matrix $W$. One disadvantage is that multiplicative can learn a more complex way to compute attention. e.g. "to work out similarity, only consider parts of the vectors, or otherwise handle the different dimensions in different ways"
	ii. One advantage of additive attention compared to multiplicative attention is that you can learn non-linear activations to increase the expressiveness of the attention score you're computing. One disadvantage is that it could be possibly harder to learn, and you have to maintain two weight matrices instead of just one with multiplicative.

==Question here: the most salient advantages / disadvantages for the different attention mechanisms seem to be expressive power vs. variable storage? Is that *enough* of an answer?==
- for ii. think about the `tanh` activation -- kind of a mini feed-forward network inside the attention score
	- more expressive / complex but additional compute for this
	- not necessarily the case that there are more params to store in the additive attention case, just because there are more matrices we're storing...
- dot product kind of a similarity score -- for this to work, *need* to enforce a kind of alignment between source and target language
- no "correct" answer, these attention mechanisms will be dependent on the use case


# 2 Analyzing NMT Systems
a. Cherokee is polysynthetic, meaning words are composed of many morphemes, which have independent meanings but cannot stand alone as words. It then makes sense to model the NMT system at the subword level because the subwords (morphemes) in Cherokee are the meaning-carrying atoms in the language. Polysynthetic languages typically have long words comprised of many morphemes, so the meaning of singular words may be very complex compared to morphemes within them that will repeat in other contexts. It therefore makes a lot of sense to use and embed morpheme tokens instead of the whole words they appear in.

Also, since our dataset is smaller than an ideal one we'd be using for NMT, modeling at the subword level allows for more repetition & better learning, compared to individual words which may occur only a few times in the dataset. ==is this relevant?==

b. Since Cherokee characters are not morphemes, transliterating in order to find common prefixes allows us to better represent *actual* morphemes in the Cherokee language as opposed to characters. For example, there may be multiple characters in Cherokee with the prefix "ts-", but we cannot learn them as identical morphemes if we don't transliterate.
==So, characters and morphemes are not equal...?==
- one character can be broken down into multiple morphemes

c. NMT systems benefit from an inductive bias when learning translation on languages with more resources available. Languages are not created in isolation, so there may be shared syntactical regularities across languages that can be learned in one context and applied to another, like a low-resource context like Cherokee to English, to improve performance.

d.
	i.
		1. The error underlined has to do with the translation of pronouns. "She" is being translated to "it" and "he"
		2. The model must not have learned to sufficiently distinguish pronouns that have the same syntactic appearances, like "it", "she" and "he". There may also be difficulties with the transliteration, e.g. if personal pronouns in Cherokee have regular morphemes like a certain prefix that we're somehow not learning correctly...
		3. We could look at the word embeddings for "she", "he", and "it" being provided to the model and ensure that they're different enough. Maybe we could use higher-dimensional embeddings?
	ii.
		1. Here the problem is repeating a word token -- the "repetition problem" which is common with language models. The decoder model outputs the word "little" 5 times instead of once as in the correct translation. ==Want to ask specifically about this -- can you explain why LMs commonly have the repetition problem?==
- not explicit in the training objective that we punish longer sentences
- the repetition problem is kind of a markov sampling problem thing
	- in this case where it repeats "little" -- suspected that it's the attention mechanism's problem
		- in summarization tasks this is a problem -- can just repeatedly summarize one section instead of the whole passage
		- we need a way for the attention mechanism to identify and punish an identical word as the immediately preceding word, since in English this is not something that happens all too commonly
		1. The model here is identifying that the perplexity of "The little little little little little tree?" is low enough to count as the correct translation. OR, the Markov generation process
		2. We can punish longer sentences more, so that the model is less incentivized to produce these run-on sentences with repetition (==this point about punishing longer sentences is not something we actually do with NMT==). Also, we could consider a more advanced attention mechanism like multiplicative attention that could express that the $n-1$st word should not be the same as the $n$th generated word.
	iii. ==cherokee word could translate to both "humble" and "not a lot" -- maybe in the dataset the word "humble" doesn't occur enough times -- or propose longer context, i.e. get a dataset where the sentences to translate are longer so that "humble" can be understood in that context as a more proper translation==
		1. This is a problem with synonyms. In this case "not a lot" might be apt to describe something like a "humble portion" of something, though in this case the translation is incorrect.
		2. The model might not have a good enough embedding representation of the word "humble" to output it as a highly probable word.
		3. In this case we might benefit from multilingual training to get a better representation of the usage of "humble" in English, or from punishing sentence length more so that "it's not a lot," which is 4 words, is made a worse prediction than "humble" even though "humble" is a highly improbable word according to a language model (the $P(w)$ quantity will be low)
==Ask about these one by one -- is the answer they're looking for more to do with the linguistic concept that the model is missing, or some fault in the design of the LM algorithm?==

e.
	i. #TODO

f. Each of the components asked about -- BLEU scores are all computed using the `nltk` BLEU score module