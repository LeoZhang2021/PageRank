# Larry says "Surf's Up!"

In 1998, Sergey Brin and Larry Page published [a paper](http://ilpubs.stanford.edu:8090/361/) describing their new search engine called Google. 

It
calculates a measure of a web page’s quality called PageRank. PageRank is essentially the probably of a "random surfer" navigating to that page. A page's rank is calculated from the rank of other pages that point to it. 

The algorithm initially assigns equal rank to all pages and then uses a technique called the power method to propagate rank among pages.

The "web" is read from one of three (3) input files: `links_small.txt`, `links_medium.txt`,
`links_large.txt`. The program calculates the rank of each page which it outputs to a file called `ranks.txt`.


### Primary Objective
The goal of this exercise is to review concepts covered in previous courses around processes (`fork()`), shared memory, and synchronization (semaphores, barriers). 


### Secondary Objective(s)
If for some reason you haven't used gitlab before, this is an opportunity.

### Description of Behaviour

- Modify the `pagerank()` function using `fork()` so that it uses multiple processes to implement the power method.
-  Each process should calculate an equal portion of the page ranks. The processes should communicate via shared memory. 
-  The processes will need to synchronize each iteration after calculating the new ranks. 
-  A reusable barrier is provided for that in `prhelper.h`. Use `bInit()` to initialize a `barrier_t` struct and `bSync()` to synchronize.
- The program takes two command-line parameters: 1) the number of processes, and 2) the input filename. For
example: `./pagerank 1 links_small.txt`


### Test Cases

When testing, use values between `1` and `4` for the number of processes.

Reference output can be found in these files: `ranks.txt.small`, `ranks.txt.medium`, `ranks.txt.large`.


## Acknowledgements
This was originally developed by Prof. Andrew Morton into an exam question. Thanks to him for letting me use it as an in-class exercise!

The links files come from [Wikispeedia navigation paths dataset](http://snap.stanford.edu/data/wikispeedia.html). The `links_medium.txt` and `links_large.txt` test files are subsets of the `links.tsv` file found in `wikispeedia_paths-and-graph.tar.gz.` 

See also the two related papers: [Human Wayfinding in Information Networks](https://cs.stanford.edu/~jure/pubs/wayfinding-www12.pdf) and [Wikispeedia: An Online Game for Inferring Semantic Distances between Concepts](https://www.ijcai.org/Proceedings/09/Papers/267.pdf).