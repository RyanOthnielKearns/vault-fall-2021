#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
# Learning Objectives
- debugging hardware systems
	- taking a staged approach
- specifically: debugging smart useless boxes
- how to *fail fast*

# Debugging
- the world is not working the way you expected
	- model of the world isn't correct
	- what did you assume to be true that is not true?

## 5 step approach to debugging
1. describe the problem
	- be quantitative about it
	- having *expectations* is necessary for debugging
2. isolate the problem
	- what is the smallest possible subsystem that is failing?
3. brainstorm causes
	- hypothesis generation / probable root causes
4. validate / disprove hypotheses
	- generate data to disprove hypotheses
5. reflection
	- create short cuts in the future

## Parallels to Software Debugging
- smaller systems are easier to debug! fewer things can be going wrong, easier to enumerate
	- also expected outcome is easier to predict
- need to test "programs"
	- start simple: e.g. *unit tests*
- good to think of your design as different function blocks
	- break big design into smaller pieces, with separate and simple(ish) functions
	- test equiptment is *another* set of function blocks to consider!
		- test your own testing equipment
		- should have testing "routines" for all of these reusable blocks, e.g. measurement equipment

### Hardware debugging's wrinkle
- hardware can just break (*bit rot*)
	- big problem with breadboards that aren't built "right"
	- isolation is the key

# General validation strategy
*trust no one*
- trust not a single one of your assumptions -- they can't all be correct, because if they were your system would be working

# Debugging your useless box
- archive test programs! remember that hardware systems sometimes just stop working
- minimize the work required
	- design only the critical stuff you need, borrow the rest from others
		- don't invent stuff you don't need -- good enough is good enough
		- think about the minimal system that will be ok

 # Failing Fast
 - people tend to avoid working on the areas they're worried about working
	 - best plan: fail as fast as you can, work on the riskiest part of the system first
- mantra in entrepreneurship: the hardes thing to predict will be what the customer wants
	- try many products / variations until you find the winning one
	- if people don't actually want it, it makes no sense to make it better
		- find out as early as possible so to minimize sunk investment
- failing is learning: you fail because of conceptual errors
	- learning the way the world *actually* is as early as possible is important!