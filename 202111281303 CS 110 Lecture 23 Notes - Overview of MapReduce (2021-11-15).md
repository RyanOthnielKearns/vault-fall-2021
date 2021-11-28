#Stanford #Stanford-Fall-2021 #CS #CS110 #lecture-notes 
See [[Lecture 23 Slides - Overview of MapReduce.pdf|slides]]
2021-11-15
___
MapReduce: in the "big data" domain
Course concepts:
1. filesystems
2. multiprocessing
3. multithreading
4. networking

MapReduce will use the latter 3!
- how can we parallelize data processing across many, many machines?

# Today
1. leverage networking / concurrency to study MapReduce
2. learn the programming model for MapReduce / operation parallelization
3. understand how to write a program that can run using MapReduce

leads up to an optional *Assignment 7*
- expose more or less all of the tests -- easy to get 100% on the assignment

# Overview of MapReduce
- suppose we want to parse a document and create a histogram of all words used in the documents (& how frequently)
- *idea*: combine all the output, split into chunks, process on the chunks, and combine each count into a single global count
	- act of *combining* and *sorting* is *always* done, regardless of the problem you're solving
	- the processing on chunks shouldn't do any counting -- leave the summation for the accumulation / summing step (the "Reduce")

## Parallelizing the Combining and Sorting Step
use buckets!
bucket # = hash(key) % R where R = # of reduce tasks
- then apply sorting and reducing (summing) in each bucket, rather than all in 1 total list
- input files -> map phase -> intermediate files -> reduce phase -> output files

## Example: PageRank
- create a map of referenced URL -> list of referencing URLs
- builds an "inverted index"
- still using the general hashing scheme / distributed collation / reduction steps ("bundling common keys")

## 2 Step Process
1. *map* the input to intermediate data representation
	- `map(k1, v1) -> list(k2, v2)`
2. *reduce* intermediate representation to final result
	- `reduce(k2, list(v2)) -> list(v2)`

*the right abstraction can revolutionize computing*

More terminology:
- **worker**: machine performing map or reduce task
- **leader** or **orchestrator**: assigns tasks to workers
- **task**: a single map or reduce step

## Challenges
1. machine failure -- how to know whether machine really went down?
2. communicating over the network (leader/orchestrator and 100k+ other machines)
3. coordinating tasks

- have to execute all maps before we execute any reduces