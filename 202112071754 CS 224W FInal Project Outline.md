#Stanford #Stanford-Fall-2021 #CS #CS224W #AI 
___
# Dataset
- 26 distinct user nodes
	- 8 are bots or applications
	- 18 are human users
- 1,158 distinct source nodes
- 76,906 unique queries performed over a 30-day period
	- after coalescing distinct queries to get unique user <> source pairs, there are 1,606 edges in the graph
- edge weights in this bipartite graph indicate importance. So if user $U$ executes lots of queries on table $T$, table $T$ is important for user $U$ and vice versa

# Method
- follow [LightGCN paper](https://arxiv.org/pdf/2002.02126.pdf) and use Bayesian Personalized Ranking (cited in Steffen Rendle, Christoph Freudenthaler, Zeno Gantner, and Lars Schmidt-Thieme. 2009. BPR: Bayesian Personalized Ranking from Implicit Feedback. In UAI. 452– 461.)