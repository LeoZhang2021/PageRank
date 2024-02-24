#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#include "prhelper.h"

void pagerank(link_t l[], int nLinks, double rank[], int nPages, double delta,
		int iterations, int nProcesses) {
	// compute number of outgoing links for each page
	int outDegree[nPages];
	for(int i=0; i<nPages; i++) outDegree[i] = 0;
	for(int j=0; j<nLinks; j++) outDegree[l[j].src]++;

	double r[nPages]; // ranks
	double s[nPages]; // new ranks

	// initial guess
	for(int i=0; i<nPages; i++) r[i] = 1.0/nPages;

	// FORK PROCESSES HERE

	pid_t* pid = malloc(sizeof(pid_t)*nProcesses);
	int k = 0;
	int j = 0;
	int a = 0;
	int x = 0;

	for(int i = 0; i < nProcesses; ++i)
	{
		pid[i] = fork();
	}

	while(k < iterations)
	{
		while(j < nPages)
		{
			while(a < nLinks)
			{
				s[j] += delta * r[l[a].src] / outDegree[l[a].src];
				++a;
			}
			++j;
		}
		++k;

		while(x < nPages)
		{
			r[x] = s[x];
			++x;
		}
	}

	// // power method
	// for(int k=0; k<iterations; k++) {
	// 	// calculate new values, placing them in s[]
	// 	for(int i=0; i<nPages; i++) {
	// 		s[i] = (1.0-delta)/nPages;
	// 		for(int j=0; j<nLinks; j++)
	// 			if(l[j].dst == i)
	// 				s[i] += delta * r[l[j].src] / outDegree[l[j].src];
	// 	}

	// 	// copy s[] to r[] for next iteration
	// 	for(int i=0; i<nPages; i++)
	// 		r[i] = s[i];
	// }

	// JOIN PROCESSES HERE

	for(int i = 0; i < nProcesses; ++i)
	{
		wait(NULL);
	}

	for(int i=0; i<nPages; i++)
		rank[i] = r[i];
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("usage: %s <n_process> <link_file>\n", argv[0]);
		return 0;
	}

	// read in links file
	link_t *links;
	char (*names)[NAME_MAX];
	size_t n_links, n_pages;
	if(!readLinks(argv[2], &links, &n_links, &names, &n_pages)) {
		printf("failed to read links file %s\n", argv[2]);
		return 0;
	}

	// start timer
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double startTime = (tv.tv_sec) + tv.tv_usec/1000000.;

	// run pagerank
	double *rank = malloc(n_pages * sizeof(double));
	double delta = 0.80; // convergence rate
	double iterations = 1000;
	int processes = atoi(argv[1]);
	if(processes < 1 || processes > 4) {
		printf("processes %d not in [1,4]\n", processes);
		return 0;
	}
	pagerank(links, n_links, rank, n_pages, delta, iterations, processes);

	// stop timer
	gettimeofday(&tv, NULL);
	double endTime = (tv.tv_sec) + tv.tv_usec/1000000.;
	printf("%s execution time: %.2f seconds\n", argv[0], endTime - startTime);

	// write ranks.txt
	FILE *fout = fopen("ranks.txt", "w");
	for(int i=0; i<n_pages; i++)
		fprintf(fout, "%.8f %s\n", rank[i], names[i]);
	fclose(fout);

	// clean up
	free(links);
	free(names);
	free(rank);
}

