#conference #AI #artificial-intelligence #Stanford-HAI #Stanford #Stanford-Fall-2021 
___
# High-Level Agenda
Panels yesterday:
1. Middleware for protecting consumer interests
2. UBI to offset job loss due to automation

Panels today:
1. Data governance & cooperatives
2. AI accountability & audits

# Introduction
## Daniel Ho
- what unifies each panel: concern for human agency & autonomy
	- UBI: reduce impact of innovation on individuals
	- audits: hold developers accountable to challenge particular forms of deployment
- realignment of public and private objectives
	- AI bill of rights -- privacy, fairness, transparency, and explainability
	- the freedom dividend
	- fostering a middleware market
	- today
		- data coalitions - data coalitions board
		- model oversight board, like those regulating financial accounting industry

## Erik Brynjolfsson
- convene stakeholders for the future of governing AI

# Keynote: "Reimagining AI Systems Governance"
**Rumman Chowdhury**
- directory of META (ML Ethics, Transparency, and Accountability) @ Twitter
- Former CEO & Founder, Parity AI
- Former Global Lead, Responsible AI @ Accenture

## Current State of Algorithmic Ethics
- only a few years old!
- regulation actually moving rather quickly -- "*Collingridge dilemma* / pacing problem": technology changes exponentially, social/economic/legal systems change incrementally
	- when area to make policy / regulation was very simple and easy, it was hard to understand what to prioritize for policy
	- when policy objectives become clearer, systems being regulated are probably more entrenched & harder to change
- standards bodies list NIST coming up
- GDPR as a "crystal ball" -- we know how regulation may go
	- but on corporate side: companies slow to adopt, big gap between regulation and implementation
	- laws do not ensure compliance
- lack of clear definition of "audit" in current laws
	- ripe for regulatory capture -- we have a vacuum of information -- those filling it will be policy-motivated actors --> monopoly-inducing
		- there's a risk in passing laws *too early*, meaning before we have a clear picture of what would be required

### Flaws in Status Quo
- framing ML Ethics as "corporate (social) responsibility" --> ML ethics will be a "**loss leader**"
	- uphill battle, framed as "enemies" of "real" ML engineers
	- instead: ML ethics needs to be invested in building better products, just like everyone else

### Alternate Future Reality
- nothing inherently bad about ML/AI
- ML ethics is about improving product quality
- community-driven standards to bridge our reality w/ aspirations
	- doing something unclear can actually be *worse* than doing nothing at all (see talk about Collingridge dilemma)
- ensure proactive harms identification
	- interested in middleware for this reason -- independent third parties can be proactive here

#### How to Get There
1. Education
	- *not* the same as training! education is higher-level, not practical to the day-to-day
2. Democratization
	- significant open-source tooling exist
	- there are things everyday data scientists / modelers can do -- "Responsible ML Ops"
3. Empowering specialists
	- elevate & hire critical voices in non-eng functions
	- best way to motivate change: where people are incentivized in the day-to-day in their jobs
4. Meaningful regulation
	- Twitter: trying to figure out how to be transparent -- talk about challenges they face and how they're trying to overcome them
		- e.g. Twitter's algorithmic bias bounty challenge
	- sociotechnical system: difference between "algorithmic bias" (baked into the DNA of how this model is built) and user-related behavioral problem

## Common Themes
1. Resilience
	- how does this complex system react to stress? how can it heal itself?
2. Self-organization
	- allow self-org of the atomized entities (like 3rd party auditors) to create the most robust system
3. Hierarchy
	- data collective --> *data advocate*, a trusted individual who understands your data needs

## Q&A
- "nut-picking": the opposite of cherry-picking: pick a random nutcase from the other side of the aisle and amplify them on social media
	- enhances polarization
	- the left quote-tweets more than the right
- the danger of anthropomorphizing AI
	- talk about "the algorithm" like it's an entity in the room, or all-knowing entity / god
	- instead these are systems built by people
	- can lead to *moral outsourcing* (shifting blame from humans to machines)
- how to demonstrate that ethical ML/AI is a business benefit and not a tax?
	- framing as "improving quality" / being a good engineer
	- pushing back on the "fairness vs. accuracy" dilemma
	- "ethical debt" similar to technical debt
		- trying to address these problems later on might get prohibitively expensive

# Proposal # 1: Data Collectives
**Dr. Jennifer King**
- privacy and data policy fellow @ Stanford HAI

- reimagining our relationship with data (at personal, societal, global levels) / our division of power between data producers and data collectors, via a **data collective**

## Intro Talk: Divya Siddarth
### "Data is the new oil"
- Cannonization: The Economist article from 2016 "The world's most valuable resource"
- Takes a lot of infrastructure to collect and process correctly -- like standard oil refining infrastructure
- Access to data is a national security concern / considered very similar to oil reserves
- **but** in other ways data $\neq$ the new oil
	- can't just trade out one dataset for another
		- data is non-fungible and non-rivalrous
	- "**data exhaust**" -- data that is generated and captured as we move throguh the world
		- subject to network effects that natural resources like oil obviously aren't
			- the value of Facebook is not just a sum of the value of each individual user's data value
	- data isn't a latent resource -- actively created through human work, interaction, and labor
		- GPT-3 isn't a natural achievement -- trained on lots of human-generated data that didn't just latently exist
	- consequences
		- cannot treat data as private property due to its interdependent and networked manner
		- are regulatory structures even sufficient to ensure user privacy? we don't have a clear picture of what "private" even should be
		- data producers in something like the state of the workplace before cooperative bargaining / unionization

### Proposal
- a layer of coalitions between data holders (individuals / organizations) and platforms / data consumers
	- coalitions connect to data holders by way of a two-way contract that outlines the desired usage of the data
		- these coalitions / cooperatives can be siloed, e.g. health data cooperative, messaging data cooperative (could be more privacy-focused)
		- utilize their leverage to advocate for better privacy and security standards w/ power of collective bargaining
	- coalitions communicate these constraints to data platforms, and share revenue and decision strategies between each other
	- coalitions perform "data labor"
	- can never "sell" your data; can only "lease" for determined amount of time
- data relations board, like the labor relations board
- there are already co-ops that exercise some of these functions
	- Midata for health data cooperative
	- Driver's Seat: gives revenue back to its workers
	- ability to capture insights from data without exposing the data itself
- as a data producer, don't get cut out from the market and contributions made possible by the new data economy!

## Panel Discussion
### Pamela Samuelson
- collective rights management would give more leverage for communicating with data-consuming firms
- number of different types of cooperatives -- can join the particular cooperatives that meet my needs
- "devil is in the details" -- details might be a little concerning
	- where does the startup money come from?
	- how do you get people to join it?
	- where is the leverage these cooperatives would have when they're small w.r.t. larger entities?
		- where does the duty to negotiate come from other than legal mandate?
	- how to free up or manage data already possessed by data platforms?
	- most people who are privacy people don't want to start a new cooperative
	- network effects problems to work through -- firms will only want to work with the biggest cooperatives anyway
- maybe a better route: per Jack Balkin: make the data platforms themselves to take on this fiduciary role
- mitigating the power of these major firms is an attractive idea to all of us -- but open data & free data is something that benefits startups
	- to commodotize all data is missing some of the benefits of the free / open data movement that's happening today
	- esp. in health data today -- I want to make my health data freely available to people doing research on improving health
		- wouldn't have the vaccine w/o freely-shared health data
- question from Jennifer King: why is it not optimal to own all of your data (in the way proposed by Andrew Yang)?
	- in the matter of intellectual property laws: no one can own data
		- considered as public domain
		- can't be patented, can't usually be trademarked
		- unconstitutional to give people "property rights" over their data
			- but what will work: licensing rights -- you "possess" the data and can charge fees for the leasing / use of the data (you don't "own" data)
	- data privacy most closely resembles trade secrecy law
		- *misappropriation*: when someone holding your data gives it out or does something not agreed to with that data -- can sue and get an injunction
		- give data in confidence, w/ agreed clauses about what can be done w/ the data / who the data can be shared with

### Sandy Pentland
- disagrees with Pam that a new law is required -- weaponize the existing California law s.t. fiduciary responsibility is unavoidable
	- can get cooperatives online without legal framework
- believer that you can't do everything digitally -- have to start with physical neighborhoods -- make it local
	- "how will this affect our local schools? etc..." with local import highlighted immediately
	- don't have to just go after money -- want good medical care for my children, good governments, good schooling etc.
		- money from Google / Facebook would be nice, but not remotely as important
		- if local communities *have the data*, they can get better at making these kinds of demands
- "if you show up with 50 million people, you're going to get listened to"
- in the UK: legal structures like councils can behave naturally with these kinds of ideas
- "**Community Intelligence**"
	- communities able to advocate for themselves based on facts -- requires access to data to get insights
	- community banks turned into the modern financial system -- local to begin with!
		- eventually joined up nationally to have national-level effects
- get the customers to ask about what they want -- provide minimal data services to provide that -- firms will be able to utilize the data they receive to achieve that
	- most mid-sized companies don't see this as a bad way to go (contra major data collectors like Google and Facebook)
- **open data** vs. **community data**: community demands certain services in return for the insights from the data they choose to make available
	- can derive insights from data you don't own or can't see -- new technological availability
- **data ownership**: you don't get ownership, but you get ownership rights -- some say in the disposition of that data, w/ informed consent about data provided / shared
	- 'if you say "is this what you intended?" and they're surprised, you didn't have informed consent'
- objecting to a "data commons" approach -- confusing with "open data"
	- talking about people able to have fiduciary possession of data -- organization can represent people w.r.t. their data (fiduciary representative)
	- creates a more liquid data market, but not necessarily a commons
	- key to making improvements to products: can share statistics about performance in the data without necessarily exposing the data itself (e.g. improving autocorrect without sharing what was actually typed)
		- equivalent performance as if you had possession of the data

### Divya Siddarth
- "how do we do this / where does the money come from?" --> couple different ways
	- start w/ sector-specific data
	- work with cooperatives that already exist / orgs that already exist that could naturally transition to fit that role
		- already belong to local election boards --> also already belong to natively-online communities
- if people aren't interested in commodifying their data, they should just share it!
	- much data is already a commodity, but a terribly organized one that is not serving people well
	- not about shutting down data sharing that currently exists -- about creating commodification schemes that work better than the ones we have now
- what are the incentives of data cooperatives?
	- why more attractive than imposing fiduciary responsibilities onto existing institutions / the current data players today? what's the advantage?
	- section 230 companies -- ones beholden to that duty -- are a small portion of all data-consuming companies today
	- we need incentives aligned across the ecosystem -- the type of technology we're able to build with this new kind of data access has so much potential --> we can align incentives for establishing an ecosystem where these data sharing / access protocols / equitable distribution and decision-making capacity of data producers are available
- how do data cooperatives account for diversity within them?
	- will this just further marginalize minority communities?
		- can build leverage through collective bargaining and action -- data cooperatives provide the ability for this
	- Pam's point: don't want to commodify all data

### Jennifer King
- on disorder in modern data commodification raised by Divya -- can't decide to share data to just Stanford Health and *not also* Proctor and Gamble / other big pharma

# Proposal # 2: Third-Party Auditor Access for AI Accountability
## Keynote Speaker: Deborah Raji
- Fellow, Mozilla Foundation; Algorithmic Justice League; C.S. PhD student at Berkeley
- vaccine allocation: Stanford Medicine allocated only 7 of 5k available doses to frontline healthcare workers
- as w/ any built artifact: algorithmic failure modes e.g. "car crashes"
	- accountability: due to the way artifact was built? who is responsible for making changes?

### External 3rd Party Audits
- auditors have no contractual relationship w/ audit target
	- NIST, ACLU, etc.
	- range is pretty vast
		- academics
		- civil society (ACLU)
		- journalists
		- law firms
		- regulators (FDA)
- **audit**: explanation + accountability
	- see "Actionable Auditing: Investigating the impact of publically naming biased performance results of commercial ai products"
		- e.g. Gender Shades audit

#### Challenges
##### Access
- discouraging audit activity via paywall, etc.
- "Scraping is not a crime" campaign (Julia Angwin)
- Facebook vs. NYU Ad Observatory, Algorithm Watch; Clearview AI vs. watchdog groups using subpoenas
- **Sandvig v. Barr** ruling: 3rd party auditors may be exempt from privacy / anti-hacking laws against scraping

##### Harms Discovery
- identify which vendor to audit for, identifying the algorithm in a broader ecosystem responsible for the discrimination / negative impact taking place
	- who to contact, how to contact?
	- identification is very ad hoc

##### Audit Impact
- how to get audit result to produce result you want to see?
- difficult to target more than just a single demographic group, prediction task, or company

#### Solutions
##### Auditor Oversight Board
- protected access for accredited third-party AI auditors
	- regulators w/in federal agencies already enjoy permissions like these -- but may lack awareness that other 3rd party auditors might have
- mediate disputes between auditor and auditee
- analogy: Algorithmic Justice League's "Audit the Auditors" project

##### National Incident Reporting System
- get logged records for complaints, for purpose of *AI harms discovery*
- requires complimentary legislation -- required *disclosure of algorithmic use* for particular contexts, so people can know when they've been affected and by what
- identifying and flagging repeat offenders (particular company / product / feature)

##### Post-Audit Interventions
- translate audits into accountability outcomes
- require regulatory measures for audit impact
	- enforcement, standard setting, reporting

### Conclusion
- those most harmed by algorithms -> the ones furthest from AI development -> least likely to have access to recourse

## Panel Discussion
### Fiona Scott Morton
- "car example" -- audits like investigations of car crashes
- on the utility of transparency: asked Deborah
- we have a congress that's not going to do anything about this right now
	- what existing laws are out there? then analogize
	- we invent $X$, then worry about harm from $X$ (planes, cars, algorithms, etc.)
	- harm is going to be bigger when the corporation is bigger -- helps us build regulation that doesn't penalize new players so much that they can't enter the space (per DJ's point about regulatory burden)

### Deborah Raji
- **impact assessments**: definitely important tools
	- but often operating more as internal audits than external audits
	- way in which AI capabilities are exaggerated --> when prompted, companies might release code that is totally unreadable b/c variables aren't understandable, lack of documentation etc.
		- we don't need to require large corporations to do anything -- govt / regulator has to be able to come in and double check (in a non-destructive manner)
- the proposal: limiting companies' abilities to limit the amount of data you're allowed to capture via auditing
	- a lot is in the companies' hands right now
	- a lot of the AI policy recommendations / proposals are about limiting or updating company behavior
		- can we reframe this into protecting and supporting external actors that are already doing the work? or doing better work?
- Fiona on the utility of transparency
	- good for exposing certain violations or concerns
	- plays the role of facilitating scrutiny / providing ability for external scrutiny for holding internal stakeholders accountable
		- not going to get us all the way there
- *how practical is it to assume that regulatory bodies will have capacity for successful and informative auditing?*
	- part of the reason to shift this responsibility to 3rd party auditors
	- how do we guarantee that regulators have the same security and privacy guarantees in place, if they're to get access to private company data for an audit? same quality security as Facebook???
		- access is not an all-or-nothing game -- access can be mediated through request

### DJ Patil
- **head of technology, Devoted Health**
- **former US Chief Data Scientist**
- works in very regulated fields, incl. healthcare
- how to accomplish our goals w/o *suffocating regulatory burden*?
- oversight boards: how do we ensure that this is not a political process --> gets us into political gridlock?
- great analogies -- FAA, FDA, etc.
	- what would it look like if EFF had a whistleblower type of a thing?
- turning these ideas into actionable policy -- big theme for the Biden/Harris administration
	- going to require lots of collaborative action between technologists and government

### Cathy O'Neil
- **author, "Weapons of Math Destruction"**
- self-described "2nd-party auditor" -- hired as consultant
- "premium on insurance products?" "how much to pay for a loan?" --> types of algorithmic questions really only possible to answer w/ internal access to data
- wanted field of algorithmic auditing to not get as corrupt as the analogue in financial systems
	- e.g. triple-A ratings for mortgage-backed securities from 2008 -- backed by models only understood / accessible to financial partners
	- "I want what Deborah wants, but don't know if we're there yet"
- we're in the stage of "designing the cockpit" of AI systems -- what are the unique risks of this technology and how should we correspondingly set the dials?
	- likewise: still in the discovery stage learning the proper way to design audits
- problem w/ the car example: I don't know how people are frequently harmed by algorithms / where the correct "safety mechanisms" are
	- per DJ's point: designing a cockpit is a lot of work!
	- should be done by those making a lot of money off of algorithms
	- auditing agency: "here are the tests you have to run, and report the metrics quarter-by-quarter"
		- this is a lot more of an available task for smaller businesses
- disagrees with Deborah the most: *we must burden the people who make money off of these algorithms*
	- if govt agency licenses an algorithm, needs to be vetted, and vetting needs to be supplied by 3rd party
		- make the case that what they're doing is fair and legal
		- per Fiona's point: this does not finish the job -- make requirement that auditees have to know (or pretend to know) the answers to these questions

# Concluding Thoughts
- [Lewis Brandeis's Trust-Busting](https://t4two.wordpress.com/2021/08/22/brandeis-and-trust-busting/)
- Data ownership: even a coherent and constitutional principle?
- proposals are tackling and trying to wrestle w/ common problems
- Andrew Yang: the so-called "[Overton window](https://en.wikipedia.org/wiki/Overton_window)" (window of policy that's acceptable at a given moment) can shift dramatically as the result of a single indvidual's efforts