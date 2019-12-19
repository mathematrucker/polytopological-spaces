//
//  Eliminate all inequalities not implied by Figure 1.
//
//  Mark Bowron, 18 Nov 2019.
//

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>

void	k(int *p); 						// closure
void	c(int *p);						// complement
void 	i(int *p);						// interior
void	intersect(int *p, int *q);
void	copy_set(int *from, int *to);
void	f(int *p, int *q);				// frontier
int		contained_in(int *p, int *q);	// returns 1 if p is a subset of q, 0 otherwise
int		**generate_subsets(int **p, int *q);

static const int	Id = 0;
static const int	closure = 1;
static const int	interior = 2;
static const int	frontier = 3;
static const int	ik = 4;
static const int	fk = 5;
static const int	ki = 6;
static const int	fi = 7;
static const int	ib = 8;	// "if" is a reserved word in C
static const int	ff = 9;
static const int	kik = 10;
static const int	fik = 11;
static const int	iki = 12;
static const int	fki = 13;
static const int	kif = 14;
static const int	fif = 15;
static const int	zero = 16;
static const int	complement = 17;
static const int	ck = 18;
static const int	ci = 19;
static const int	cf = 20;
static const int	cik = 21;
static const int	cfk = 22;
static const int	cki = 23;
static const int	cfi = 24;
static const int	cif = 25;
static const int	cff = 26;
static const int	ckik = 27;
static const int	cfik = 28;
static const int	ciki = 29;
static const int	cfki = 30;
static const int	ckif = 31;
static const int	cfif = 32;
static const int	one = 33;

int main(int argc, const char **argv)
{
	int	  		**adj, **p, *q;
	int			i, j, k;

	adj = (int **)malloc(34 * sizeof(int *));
	if (adj==0)
	{
		printf("\nCould not allocate space for adj.\n");
		exit(0);
	}

	p = (int **)malloc(34 * sizeof(int *));
	if (p==0)
	{
		printf("\nCould not allocate space for p.\n");
		exit(0);
	}

	q = (int *)malloc(16 * sizeof(int));
	if (q==0)
	{
		printf("\nCould not allocate space for q.\n");
		exit(0);
	}

	for (i=0; i<34; i++)
	{
		adj[i] = (int *)malloc(34 * sizeof(int));
		if (adj[i]==0)
		{
			printf("\nCould not allocate space for adj[%d].\n", i);
			exit(0);
		}
		p[i] = (int *)malloc(16 * sizeof(int));
		if (p[i]==0)
		{
			printf("\nCould not allocate space for p[%d].\n", i);
			exit(0);
		}
	}

	/*
	 *	Initialize q[] to the empty set.
	 */

	for (i=0; i<16; i++) q[i] = 0;

	/*
	 *	Initialize adj[][] to the zero matrix.
	 */

	for (i=0; i<34; i++)
		for (j=0; j<34; j++)
			adj[i][j] = 0;

	/*
	 *	Add reflexivity.
	 */

	for (i=0; i<34; i++) adj[i][i] = 1;

	/*
	 *	Enter each arrow in Figure 1.
	 */

	adj[Id][closure] = 1;
	adj[closure][one] = 1;
	adj[interior][Id] = 1;
	adj[interior][iki] = 1;
	adj[interior][cf] = 1;
	adj[frontier][closure] = 1;
	adj[frontier][ci] = 1;
	adj[ik][kik] = 1;
	adj[ik][cfk] = 1;
	adj[fk][ff] = 1;
	adj[fk][cik] = 1;
	adj[ki][kik] = 1;
	adj[ki][cif] = 1;
	adj[fi][ki] = 1;
	adj[fi][ff] = 1;
	adj[ib][ik] = 1;
	adj[ib][kif] = 1;
	adj[ib][cki] = 1;
	adj[ib][cff] = 1;
	adj[ff][frontier] = 1;
	adj[ff][cif] = 1;
	adj[kik][closure] = 1;
	adj[fik][fk] = 1;
	adj[fik][kik] = 1;
	adj[iki][ik] = 1;
	adj[iki][ki] = 1;
	adj[iki][cfki] = 1;
	adj[iki][ckif] = 1;
	adj[fki][fi] = 1;
	adj[fki][ciki] = 1;
	adj[kif][frontier] = 1;
	adj[kif][kik] = 1;
	adj[kif][ciki] = 1;
	adj[fif][ff] = 1;
	adj[fif][kif] = 1;
	adj[zero][interior] = 1;
	adj[zero][ib] = 1;
	adj[zero][fik] = 1;
	adj[zero][fki] = 1;
	adj[zero][fif] = 1;
	adj[zero][ck] = 1;
	adj[complement][ci] = 1;
	adj[ck][complement] = 1;
	adj[ck][cf] = 1;
	adj[ck][ckik] = 1;
	adj[ci][one] = 1;
	adj[cf][cff] = 1;
	adj[cf][ckif] = 1;
	adj[cik][cif] = 1;
	adj[cik][ciki] = 1;
	adj[cfk][cfik] = 1;
	adj[cki][cfi] = 1;
	adj[cki][ciki] = 1;
	adj[cfi][cfki] = 1;
	adj[cif][one] = 1;
	adj[cff][cfk] = 1;
	adj[cff][cfi] = 1;
	adj[cff][cfif] = 1;
	adj[ckik][cik] = 1;
	adj[ckik][cki] = 1;
	adj[ckik][cfik] = 1;
	adj[ckik][ckif] = 1;
	adj[cfik][one] = 1;
	adj[ciki][ci] = 1;
	adj[cfki][one] = 1;
	adj[ckif][cif] = 1;
	adj[ckif][cfif] = 1;
	adj[cfif][one] = 1;

	/*
	 *	Apply Floyd-Warshall to get transitive closure of adj[][].
	 */

	for (k=0; k<34; k++)
		for (i=0; i<34; i++)
			for (j=0; j<34; j++)
				adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);

	/*
	 *	Initialize all 34 subsets (p[0], ..., p[33]) to the empty set.
	 */

	for (j=0; j<34; j++)
		for (k=0; k<16; k++)
			p[j][k] = 0;

	/*
	 *	Set p[0] equal to Gaida and Eremenko's seed set $A$.
	 */

	p[0][2] = 1;	// (0,1)
	p[0][4] = 1;	// (1,2)
	p[0][5] = 1;	// {2}
	p[0][6] = 1;	// (2,3) intersect Q
	p[0][10] = 1;	// {4}
	p[0][12] = 1;	// {5}
	p[0][13] = 1;	// (5,6)
	p[0][14] = 1;	// {6}

	/*
	 *	Apply $KF_1$ to seed set p[0] to generate 34 subsets.
	 */

	p = generate_subsets(p, q);

	/*
	 *	For each live inequality that gets killed, add a new "1" to adj[][].
	 */

	for (j=0; j<34; j++)
		for (k=0; k<34; k++)
			if (!adj[j][k])
			{
				if (!contained_in(p[j],p[k])) adj[j][k] = 1;
			}

	/*
	 *	If adj[][] has no 0's, then seed set p[0]
	 *	satisfies partial order on $KF_1$ exactly.
	 */

	int	success = 1;
	for (j=0; j<34; j++)
		for (k=0; k<34; k++)
			if (!adj[j][k])
			{
				success = 0;
				printf("fail: %d %d\n", j, k);
			}

	if (success) printf("success\n");

	for (i=0; i<34; i++)
	{
		free(adj[i]);
		free(p[i]);
	}
	free(adj);
	free(p);
	free(q);
}


void k(int *p)
{
//p[0] = p[0];	(-\infty,0)
	if (p[0]+p[1]+p[2]) p[1] = 1;	// {0}
//p[2] = p[2];	(0,1)
	if (p[2]+p[3]+p[4]) p[3] = 1;	// {1}
//p[4] = p[4];	(1,2)
	if (p[4]+p[5]+p[6]+p[7]) p[5] = 1;	// {2}
	if (p[6]+p[7])
	{
		p[6] = 1;	// (2,3) intersect Q
		p[7] = 1;	// (2,3) minus Q
	}
	if (p[6]+p[7]+p[8]+p[9]) p[8] = 1;	// {3}
//p[9] = p[9];	(3,4)
	if (p[9]+p[10]+p[11]) p[10] = 1;	// {4}
//p[11] = p[11];	(4,5)
	if (p[11]+p[12]+p[13]) p[12] = 1;	// {5}
//p[13] = p[13];	(5,6)
	if (p[13]+p[14]+p[15]) p[14] = 1;	// {6}
//p[15] = p[15];	(6,\infty)
}


void c(int *p)
{
	int	i;

	for (i=0; i<16; i++)
		if (p[i]) p[i] = 0;
		else p[i] = 1;
}


void i(int *p)
{
	c(p);
	k(p);
	c(p);
}


void intersect(int *p, int *q)
{
	int	i;

	for (i=0; i<16; i++)
		if (!(p[i]*q[i])) p[i] = 0;
}


void copy_set(int *from, int *to)
{
	int	i;
	for (i=0; i<16; i++) to[i] = from[i];
}


void f(int *p, int *q)
{
	copy_set(p,q);
	c(q);
	k(q);
	k(p);
	intersect(p,q);
}


int contained_in(int *p, int *q)
{
	int i;

	for (i=0; i<16; i++)
		if (p[i] && !q[i]) break;
	if (i == 16) return 1;
	else return 0;
}


int	**generate_subsets(int **p, int *q)
{
	copy_set(p[Id],p[closure]);
	k(p[closure]);

	copy_set(p[Id],p[interior]);
	i(p[interior]);

	copy_set(p[Id],p[frontier]);
	f(p[frontier],q);

	copy_set(p[closure],p[ik]);
	i(p[ik]);

	copy_set(p[closure],p[fk]);
	f(p[fk],q);

	copy_set(p[interior],p[ki]);
	k(p[ki]);

	copy_set(p[interior],p[fi]);
	f(p[fi],q);

	copy_set(p[frontier],p[ib]);
	i(p[ib]);

	copy_set(p[frontier],p[ff]);
	f(p[ff],q);

	copy_set(p[ik],p[kik]);
	k(p[kik]);

	copy_set(p[ik],p[fik]);
	f(p[fik],q);

	copy_set(p[ki],p[iki]);
	i(p[iki]);

	copy_set(p[ki],p[fki]);
	f(p[fki],q);

	copy_set(p[ib],p[kif]);
	k(p[kif]);

	copy_set(p[ib],p[fif]);
	f(p[fif],q);

//	p[zero] was already initialized to empty set

	copy_set(p[Id],p[complement]);
	c(p[complement]);

	copy_set(p[closure],p[ck]);
	c(p[ck]);

	copy_set(p[interior],p[ci]);
	c(p[ci]);

	copy_set(p[frontier],p[cf]);
	c(p[cf]);

	copy_set(p[ik],p[cik]);
	c(p[cik]);

	copy_set(p[fk],p[cfk]);
	c(p[cfk]);

	copy_set(p[ki],p[cki]);
	c(p[cki]);

	copy_set(p[fi],p[cfi]);
	c(p[cfi]);

	copy_set(p[ib],p[cif]);
	c(p[cif]);

	copy_set(p[ff],p[cff]);
	c(p[cff]);

	copy_set(p[kik],p[ckik]);
	c(p[ckik]);

	copy_set(p[fik],p[cfik]);
	c(p[cfik]);

	copy_set(p[iki],p[ciki]);
	c(p[ciki]);

	copy_set(p[fki],p[cfki]);
	c(p[cfki]);

	copy_set(p[kif],p[ckif]);
	c(p[ckif]);

	copy_set(p[fif],p[cfif]);
	c(p[cfif]);

	copy_set(p[zero],p[one]);
	c(p[one]);

	return p;
}
