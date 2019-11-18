//
//  Eliminate all inequalities not in the partial order on KF_2.
//
//  Mark Bowron, 18 Nov 2019.
//

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>

void	k_1(int *p);	// Sorgenfrey closure
void	k_2(int *p); 	// usual closure
void	c(int *p);		// complement
void 	i_1(int *p);	// Sorgenfrey interior
void 	i_2(int *p);	// usual interior
void	intersect(int *p, int *q);
void	copy_set(int *from, int *to);
void	f_1(int *p, int *q);	// Sorgenfrey frontier
void	f_2(int *p, int *q);	// usual frontier
int		contained_in(int *p, int *q);	// returns 1 if p is a subset of q, 0 otherwise
void	enter_poset(int **adj);	// enter the 260 arrows in the poset diagram for KF_2
int		**generate_subsets(int i, int **p, int *q);

static const int	exp_two[14]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192};

static const int	Id = 0;
static const int	k1 = 1;
static const int	k2 = 2;
static const int	f1 = 3;
static const int	f2 = 4;
static const int	i_1k_ = 5;
static const int	i_2k_ = 6;
static const int	f_1k_1 = 7;
static const int	f_1k_2 = 8;
static const int	f_2k_2 = 9;
static const int	k_2f_1 = 10;
static const int	f_1f_1 = 11;
static const int	f_2f_2 = 12;
static const int	f_1f_2 = 13;
static const int	f_2f_1 = 14;
static const int	k_1i_k_ = 15;
static const int	k_2i_k_ = 16;
static const int	f_1i_1k_ = 17;
static const int	f_1i_2k_ = 18;
static const int	f_2i_2k_ = 19;
static const int	k_2f_1k_1 = 20;
static const int	k_2f_1k_2 = 21;
static const int	f_1k_2f_1 = 22;
static const int	k_2f_1f_1 = 23;
static const int	k_2f_1f_2 = 24;
static const int	i1 = 25;
static const int	i2 = 26;
static const int	k_1i_ = 27;
static const int	k_2i_ = 28;
static const int	f_1i_1 = 29;
static const int	f_1i_2 = 30;
static const int	f_2i_2 = 31;
static const int	i_1f_ = 32;
static const int	i_2f_ = 33;
static const int	i_1k_i_ = 34;
static const int	i_2k_i_ = 35;
static const int	f_1k_1i_ = 36;
static const int	f_1k_2i_ = 37;
static const int	f_2k_2i_ = 38;
static const int	k_2f_1i_1 = 39;
static const int	k_2f_1i_2 = 40;
static const int	f_1i_1f_ = 41;
static const int	f_1i_2f_ = 42;
static const int	f_2i_2f_ = 43;
static const int	k_1i_f_ = 44;
static const int	k_2i_f_ = 45;
static const int	zero_op = 46;
static const int	k_2f_1i_1f_ = 47;
static const int	k_2f_1i_2f_ = 48;
static const int	f_1k_2i_f_ = 49;
static const int	f_1i_2k_i_ = 50;
static const int	k_2f_1k_1i_ = 51;
static const int	k_2f_1k_2i_ = 52;
static const int	k_2f_1k_2f_1 = 53;
static const int	f_1k_2i_k_ = 54;
static const int	k_2f_1i_1k_ = 55;
static const int	k_2f_1i_2k_ = 56;
static const int	k_2f_1k_2i_f_ = 57;
static const int	k_2f_1i_2k_i_ = 58;
static const int	k_2f_1k_2i_k_ = 59;
static const int	cId = 60;
static const int	ck1 = 61;
static const int	ck2 = 62;
static const int	cf1 = 63;
static const int	cf2 = 64;
static const int	ci_1k_ = 65;
static const int	ci_2k_ = 66;
static const int	cf_1k_1 = 67;
static const int	cf_1k_2 = 68;
static const int	cf_2k_2 = 69;
static const int	ck_2f_1 = 70;
static const int	cf_1f_1 = 71;
static const int	cf_2f_2 = 72;
static const int	cf_1f_2 = 73;
static const int	cf_2f_1 = 74;
static const int	ck_1i_k_ = 75;
static const int	ck_2i_k_ = 76;
static const int	cf_1i_1k_ = 77;
static const int	cf_1i_2k_ = 78;
static const int	cf_2i_2k_ = 79;
static const int	ck_2f_1k_1 = 80;
static const int	ck_2f_1k_2 = 81;
static const int	cf_1k_2f_1 = 82;
static const int	ck_2f_1f_1 = 83;
static const int	ck_2f_1f_2 = 84;
static const int	ci1 = 85;
static const int	ci2 = 86;
static const int	ck_1i_ = 87;
static const int	ck_2i_ = 88;
static const int	cf_1i_1 = 89;
static const int	cf_1i_2 = 90;
static const int	cf_2i_2 = 91;
static const int	ci_1f_ = 92;
static const int	ci_2f_ = 93;
static const int	ci_1k_i_ = 94;
static const int	ci_2k_i_ = 95;
static const int	cf_1k_1i_ = 96;
static const int	cf_1k_2i_ = 97;
static const int	cf_2k_2i_ = 98;
static const int	ck_2f_1i_1 = 99;
static const int	ck_2f_1i_2 = 100;
static const int	cf_1i_1f_ = 101;
static const int	cf_1i_2f_ = 102;
static const int	cf_2i_2f_ = 103;
static const int	ck_1i_f_ = 104;
static const int	ck_2i_f_ = 105;
static const int	czero_op = 106;
static const int	ck_2f_1i_1f_ = 107;
static const int	ck_2f_1i_2f_ = 108;
static const int	cf_1k_2i_f_ = 109;
static const int	cf_1i_2k_i_ = 110;
static const int	ck_2f_1k_1i_ = 111;
static const int	ck_2f_1k_2i_ = 112;
static const int	ck_2f_1k_2f_1 = 113;
static const int	cf_1k_2i_k_ = 114;
static const int	ck_2f_1i_1k_ = 115;
static const int	ck_2f_1i_2k_ = 116;
static const int	ck_2f_1k_2i_f_ = 117;
static const int	ck_2f_1i_2k_i_ = 118;
static const int	ck_2f_1k_2i_k_ = 119;

int main(int argc, const char **argv)
{
	int	  		**adj, **p, *q;
	int			i, j, k;

	adj = (int **)malloc(120 * sizeof(int *));
	if (adj==0)
	{
		printf("\nCould not allocate space for adj.\n");
		exit(0);
	}

	p = (int **)malloc(120 * sizeof(int *));
	if (p==0)
	{
		printf("\nCould not allocate space for p.\n");
		exit(0);
	}

	q = (int *)malloc(13 * sizeof(int));
	if (q==0)
	{
		printf("\nCould not allocate space for q.\n");
		exit(0);
	}

	for (i=0; i<120; i++)
	{
		adj[i] = (int *)malloc(120 * sizeof(int));
		if (adj[i]==0)
		{
			printf("\nCould not allocate space for adj[%d].\n", i);
			exit(0);
		}
		p[i] = (int *)malloc(13 * sizeof(int));
		if (p[i]==0)
		{
			printf("\nCould not allocate space for p[%d].\n", i);
			exit(0);
		}
	}

	/*
	 *	Initialize q[] to the empty set.
	 */

	for (i=0; i<13; i++) q[i] = 0;

	/*
	 *	Initialize adj[][] to the zero matrix.
	 */

	for (i=0; i<120; i++)
		for (j=0; j<120; j++)
			adj[i][j] = 0;

	/*
	 *	Add reflexivity.
	 */

	for (i=0; i<120; i++) adj[i][i] = 1;

	/*
	 *	Enter the 260 arrows in the poset diagram for KF_2.
	 */

	enter_poset(adj);

	/*
	 *	Apply Floyd-Warshall to get transitive closure of adj[][].
	 */

	for (k=0; k<120; k++)
		for (i=0; i<120; i++)
			for (j=0; j<120; j++)
				adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);

	/*
	 *	Exhaust power set of partition P to kill all inequalities, one at a time.
	 */

	for (i=0; i<exp_two[13]; i++)
	{

	/*
	 *	Reset all 120 subsets to the empty set at the start of each pass.
	 */

		for (j=0; j<120; j++)
			for (k=0; k<13; k++)
				p[j][k] = 0;

	/*
	 *	Apply each operator in KF_2^0 to the seed i to generate 120 subsets.
	 */

		p = generate_subsets(i, p, q);

	/*
	 *	For each live inequality that gets killed, add a new "1" to adj[][].
	 */

		for (j=0; j<120; j++)
			for (k=0; k<120; k++)
				if (!adj[j][k])
				{
					if (!contained_in(p[j],p[k])) adj[j][k] = 1;
				}
	}

	/*
	 *	If adj[][] has no zero entries, then the partition P
	 *	successfully verifies the partial order on KF_2.
	 */

	int	success = 1;
	for (j=0; j<120; j++)
		for (k=0; k<120; k++)
			if (!adj[j][k])
			{
				success = 0;
				printf("fail: %d %d\n", j, k);
			}

	if (success) printf("success\n");

	for (i=0; i<120; i++)
	{
		free(adj[i]);
		free(p[i]);
	}
	free(adj);
	free(p);
	free(q);
}


void k_1(int *p) // Sorgenfrey closure
{
	if (p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]) p[0] = 1;
	if (p[1]+p[2]) p[1] = 1;
//p[2] = p[2];
	if (p[3]+p[4]) p[3] = 1;
//p[4] = p[4];
	if (p[5]+p[6]+p[7]) p[5] = 1;
	if (p[6]+p[7])
	{
		p[6] = 1;
		p[7] = 1;
	}
	if (p[8]+p[9]) p[8] = 1;
//p[9] = p[9];
	if (p[10]+p[11]+p[12]) p[10] = 1;
	if (p[11]+p[12])
	{
		p[11] = 1;
		p[12] = 1;
	}
}


void k_2(int *p) // usual closure
{
	if (p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[9]) p[0] = 1;
	if (p[1]+p[2]+p[6]+p[7]) p[1] = 1;
//p[2] = p[2];
	if (p[2]+p[3]+p[4]) p[3] = 1;
//p[4] = p[4];
	if (p[4]+p[5]+p[6]+p[7]) p[5] = 1;
	if (p[6]+p[7])
	{
		p[6] = 1;
		p[7] = 1;
	}
	if (p[6]+p[7]+p[8]+p[9]) p[8] = 1;
//p[9] = p[9];
	if (p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]+p[10]+p[11]+p[12]) p[10] = 1;
	if (p[11]+p[12])
	{
		p[11] = 1;
		p[12] = 1;
	}
}


void c(int *p)
{
	int	i;

	for (i=0; i<13; i++)
		if (p[i]) p[i] = 0;
		else p[i] = 1;
}


void i_1(int *p)
{
	c(p);
	k_1(p);
	c(p);
}


void i_2(int *p)
{
	c(p);
	k_2(p);
	c(p);
}


void intersect(int *p, int *q)
{
	int	i;

	for (i=0; i<13; i++)
		if (!(p[i]*q[i])) p[i] = 0;
}


void copy_set(int *from, int *to)
{
	int	i;
	for (i=0; i<13; i++) to[i] = from[i];
}


void f_1(int *p, int *q)
{
	copy_set(p,q);
	c(q);
	k_1(q);
	k_1(p);
	intersect(p,q);
}


void f_2(int *p, int *q)
{
	copy_set(p,q);
	c(q);
	k_2(q);
	k_2(p);
	intersect(p,q);
}


int contained_in(int *p, int *q)
{
	int i;

	for (i=0; i<13; i++)
		if (p[i] && !q[i]) break;
	if (i == 13) return 1;
	else return 0;
}


void enter_poset(int **adj)
{
	/*
	 *	Enter the 117 arrows in Figure 2.
	 */

	adj[Id][k1] = 1;
	adj[k1][k2] = 1;
	adj[f1][k1] = 1;
	adj[f1][k_2f_1] = 1;
	adj[f2][k2] = 1;
	adj[i_1k_][k_1i_k_] = 1;
	adj[i_2k_][i_1k_] = 1;
	adj[f_1k_1][f_1k_2] = 1;
	adj[f_1k_1][f_1f_1] = 1;
	adj[f_1k_1][k_2f_1k_1] = 1;
	adj[f_1k_2][f_1f_2] = 1;
	adj[f_1k_2][k_2f_1k_2] = 1;
	adj[f_2k_2][f_2f_2] = 1;
	adj[k_2f_1][f2] = 1;
	adj[f_1f_1][f1] = 1;
	adj[f_1f_1][f_1k_2f_1] = 1;
	adj[f_1f_1][k_2f_1f_1] = 1;
	adj[f_2f_2][f2] = 1;
	adj[f_1f_2][k_2f_1f_2] = 1;
	adj[f_2f_1][k_2f_1] = 1;
	adj[f_2f_1][f_2f_2] = 1;
	adj[k_1i_k_][k1] = 1;
	adj[k_1i_k_][k_2i_k_] = 1;
	adj[k_2i_k_][k2] = 1;
	adj[f_1i_1k_][f_1k_1] = 1;
	adj[f_1i_1k_][f_1i_2k_] = 1;
	adj[f_1i_1k_][f_1k_2i_k_] = 1;
	adj[f_1i_1k_][k_2f_1i_1k_] = 1;
	adj[f_1i_2k_][k_1i_k_] = 1;
	adj[f_1i_2k_][k_2f_1i_2k_] = 1;
	adj[f_2i_2k_][f_2k_2] = 1;
	adj[f_2i_2k_][k_2i_k_] = 1;
	adj[k_2f_1k_1][k_2f_1k_2] = 1;
	adj[k_2f_1k_1][k_2f_1f_1] = 1;
	adj[k_2f_1k_2][f_2k_2] = 1;
	adj[k_2f_1k_2][k_2f_1f_2] = 1;
	adj[f_1k_2f_1][f_1f_2] = 1;
	adj[f_1k_2f_1][k_2f_1k_2f_1] = 1;
	adj[k_2f_1f_1][k_2f_1k_2f_1] = 1;
	adj[k_2f_1f_2][f_2f_2] = 1;
	adj[i1][Id] = 1;
	adj[i1][i_1k_i_] = 1;
	adj[i2][i1] = 1;
	adj[i2][i_2k_i_] = 1;
	adj[k_1i_][k_1i_k_] = 1;
	adj[k_1i_][k_2i_] = 1;
	adj[k_2i_][k_2i_k_] = 1;
	adj[f_1i_1][f_1f_1] = 1;
	adj[f_1i_1][f_1i_2] = 1;
	adj[f_1i_1][k_2f_1i_1] = 1;
	adj[f_1i_2][f_1f_2] = 1;
	adj[f_1i_2][k_1i_] = 1;
	adj[f_1i_2][k_2f_1i_2] = 1;
	adj[f_2i_2][f_2f_2] = 1;
	adj[f_2i_2][k_2i_] = 1;
	adj[i_1f_][i_1k_] = 1;
	adj[i_1f_][k_1i_f_] = 1;
	adj[i_2f_][i_2k_] = 1;
	adj[i_2f_][i_1f_] = 1;
	adj[i_1k_i_][i_1k_] = 1;
	adj[i_1k_i_][k_1i_] = 1;
	adj[i_2k_i_][i_2k_] = 1;
	adj[i_2k_i_][i_1k_i_] = 1;
	adj[f_1k_1i_][f_1i_1] = 1;
	adj[f_1k_1i_][f_1k_2i_] = 1;
	adj[f_1k_1i_][f_1i_2k_i_] = 1;
	adj[f_1k_1i_][k_2f_1k_1i_] = 1;
	adj[f_1k_2i_][k_2f_1k_2i_] = 1;
	adj[f_2k_2i_][f_2i_2] = 1;
	adj[k_2f_1i_1][k_2f_1f_1] = 1;
	adj[k_2f_1i_1][k_2f_1i_2] = 1;
	adj[k_2f_1i_2][k_2f_1f_2] = 1;
	adj[k_2f_1i_2][f_2i_2] = 1;
	adj[f_1i_1f_][f_1f_1] = 1;
	adj[f_1i_1f_][f_1i_2f_] = 1;
	adj[f_1i_1f_][k_2f_1i_1f_] = 1;
	adj[f_1i_1f_][f_1k_2i_f_] = 1;
	adj[f_1i_2f_][k_1i_f_] = 1;
	adj[f_1i_2f_][k_2f_1i_2f_] = 1;
	adj[f_2i_2f_][f_2f_1] = 1;
	adj[f_2i_2f_][k_2i_f_] = 1;
	adj[k_1i_f_][f1] = 1;
	adj[k_1i_f_][k_1i_k_] = 1;
	adj[k_1i_f_][k_2i_f_] = 1;
	adj[k_2i_f_][k_2f_1] = 1;
	adj[k_2i_f_][k_2i_k_] = 1;
	adj[zero_op][f_1i_1k_] = 1;
	adj[zero_op][i2] = 1;
	adj[zero_op][i_2f_] = 1;
	adj[zero_op][f_1k_1i_] = 1;
	adj[zero_op][f_1i_1f_] = 1;
	adj[k_2f_1i_1f_][k_2f_1f_1] = 1;
	adj[k_2f_1i_1f_][k_2f_1i_2f_] = 1;
	adj[k_2f_1i_1f_][k_2f_1k_2i_f_] = 1;
	adj[k_2f_1i_2f_][f_2i_2f_] = 1;
	adj[f_1k_2i_f_][f_1k_2f_1] = 1;
	adj[f_1k_2i_f_][k_2f_1k_2i_f_] = 1;
	adj[f_1i_2k_i_][f_1i_2] = 1;
	adj[f_1i_2k_i_][k_2f_1i_2k_i_] = 1;
	adj[k_2f_1k_1i_][k_2f_1i_1] = 1;
	adj[k_2f_1k_1i_][k_2f_1k_2i_] = 1;
	adj[k_2f_1k_1i_][k_2f_1i_2k_i_] = 1;
	adj[k_2f_1k_2i_][f_2k_2i_] = 1;
	adj[k_2f_1k_2f_1][f_2f_1] = 1;
	adj[k_2f_1k_2f_1][k_2f_1f_2] = 1;
	adj[f_1k_2i_k_][f_1k_2] = 1;
	adj[f_1k_2i_k_][k_2f_1k_2i_k_] = 1;
	adj[k_2f_1i_1k_][k_2f_1k_1] = 1;
	adj[k_2f_1i_1k_][k_2f_1i_2k_] = 1;
	adj[k_2f_1i_1k_][k_2f_1k_2i_k_] = 1;
	adj[k_2f_1i_2k_][f_2i_2k_] = 1;
	adj[k_2f_1k_2i_f_][f_2i_2f_] = 1;
	adj[k_2f_1k_2i_f_][k_2f_1k_2f_1] = 1;
	adj[k_2f_1i_2k_i_][f_2k_2i_] = 1;
	adj[k_2f_1i_2k_i_][k_2f_1i_2] = 1;
	adj[k_2f_1k_2i_k_][f_2i_2k_] = 1;
	adj[k_2f_1k_2i_k_][k_2f_1k_2] = 1;

	/*
	 *	Enter the 117 Figure 2-complement arrows.
	 */

	adj[ck1][cId] = 1;
	adj[ck2][ck1] = 1;
	adj[ck1][cf1] = 1;
	adj[ck_2f_1][cf1] = 1;
	adj[ck2][cf2] = 1;
	adj[ck_1i_k_][ci_1k_] = 1;
	adj[ci_1k_][ci_2k_] = 1;
	adj[cf_1k_2][cf_1k_1] = 1;
	adj[cf_1f_1][cf_1k_1] = 1;
	adj[ck_2f_1k_1][cf_1k_1] = 1;
	adj[cf_1f_2][cf_1k_2] = 1;
	adj[ck_2f_1k_2][cf_1k_2] = 1;
	adj[cf_2f_2][cf_2k_2] = 1;
	adj[cf2][ck_2f_1] = 1;
	adj[cf1][cf_1f_1] = 1;
	adj[cf_1k_2f_1][cf_1f_1] = 1;
	adj[ck_2f_1f_1][cf_1f_1] = 1;
	adj[cf2][cf_2f_2] = 1;
	adj[ck_2f_1f_2][cf_1f_2] = 1;
	adj[ck_2f_1][cf_2f_1] = 1;
	adj[cf_2f_2][cf_2f_1] = 1;
	adj[ck1][ck_1i_k_] = 1;
	adj[ck_2i_k_][ck_1i_k_] = 1;
	adj[ck2][ck_2i_k_] = 1;
	adj[cf_1k_1][cf_1i_1k_] = 1;
	adj[cf_1i_2k_][cf_1i_1k_] = 1;
	adj[cf_1k_2i_k_][cf_1i_1k_] = 1;
	adj[ck_2f_1i_1k_][cf_1i_1k_] = 1;
	adj[ck_1i_k_][cf_1i_2k_] = 1;
	adj[ck_2f_1i_2k_][cf_1i_2k_] = 1;
	adj[cf_2k_2][cf_2i_2k_] = 1;
	adj[ck_2i_k_][cf_2i_2k_] = 1;
	adj[ck_2f_1k_2][ck_2f_1k_1] = 1;
	adj[ck_2f_1f_1][ck_2f_1k_1] = 1;
	adj[cf_2k_2][ck_2f_1k_2] = 1;
	adj[ck_2f_1f_2][ck_2f_1k_2] = 1;
	adj[cf_1f_2][cf_1k_2f_1] = 1;
	adj[ck_2f_1k_2f_1][cf_1k_2f_1] = 1;
	adj[ck_2f_1k_2f_1][ck_2f_1f_1] = 1;
	adj[cf_2f_2][ck_2f_1f_2] = 1;
	adj[cId][ci1] = 1;
	adj[ci_1k_i_][ci1] = 1;
	adj[ci1][ci2] = 1;
	adj[ci_2k_i_][ci2] = 1;
	adj[ck_1i_k_][ck_1i_] = 1;
	adj[ck_2i_][ck_1i_] = 1;
	adj[ck_2i_k_][ck_2i_] = 1;
	adj[cf_1f_1][cf_1i_1] = 1;
	adj[cf_1i_2][cf_1i_1] = 1;
	adj[ck_2f_1i_1][cf_1i_1] = 1;
	adj[cf_1f_2][cf_1i_2] = 1;
	adj[ck_1i_][cf_1i_2] = 1;
	adj[ck_2f_1i_2][cf_1i_2] = 1;
	adj[cf_2f_2][cf_2i_2] = 1;
	adj[ck_2i_][cf_2i_2] = 1;
	adj[ci_1k_][ci_1f_] = 1;
	adj[ck_1i_f_][ci_1f_] = 1;
	adj[ci_2k_][ci_2f_] = 1;
	adj[ci_1f_][ci_2f_] = 1;
	adj[ci_1k_][ci_1k_i_] = 1;
	adj[ck_1i_][ci_1k_i_] = 1;
	adj[ci_2k_][ci_2k_i_] = 1;
	adj[ci_1k_i_][ci_2k_i_] = 1;
	adj[cf_1i_1][cf_1k_1i_] = 1;
	adj[cf_1k_2i_][cf_1k_1i_] = 1;
	adj[cf_1i_2k_i_][cf_1k_1i_] = 1;
	adj[ck_2f_1k_1i_][cf_1k_1i_] = 1;
	adj[ck_2f_1k_2i_][cf_1k_2i_] = 1;
	adj[cf_2i_2][cf_2k_2i_] = 1;
	adj[ck_2f_1f_1][ck_2f_1i_1] = 1;
	adj[ck_2f_1i_2][ck_2f_1i_1] = 1;
	adj[ck_2f_1f_2][ck_2f_1i_2] = 1;
	adj[cf_2i_2][ck_2f_1i_2] = 1;
	adj[cf_1f_1][cf_1i_1f_] = 1;
	adj[cf_1i_2f_][cf_1i_1f_] = 1;
	adj[ck_2f_1i_1f_][cf_1i_1f_] = 1;
	adj[cf_1k_2i_f_][cf_1i_1f_] = 1;
	adj[ck_1i_f_][cf_1i_2f_] = 1;
	adj[ck_2f_1i_2f_][cf_1i_2f_] = 1;
	adj[cf_2f_1][cf_2i_2f_] = 1;
	adj[ck_2i_f_][cf_2i_2f_] = 1;
	adj[cf1][ck_1i_f_] = 1;
	adj[ck_1i_k_][ck_1i_f_] = 1;
	adj[ck_2i_f_][ck_1i_f_] = 1;
	adj[ck_2f_1][ck_2i_f_] = 1;
	adj[ck_2i_k_][ck_2i_f_] = 1;
	adj[cf_1i_1k_][czero_op] = 1;
	adj[ci2][czero_op] = 1;
	adj[ci_2f_][czero_op] = 1;
	adj[cf_1k_1i_][czero_op] = 1;
	adj[cf_1i_1f_][czero_op] = 1;
	adj[ck_2f_1f_1][ck_2f_1i_1f_] = 1;
	adj[ck_2f_1i_2f_][ck_2f_1i_1f_] = 1;
	adj[ck_2f_1k_2i_f_][ck_2f_1i_1f_] = 1;
	adj[cf_2i_2f_][ck_2f_1i_2f_] = 1;
	adj[cf_1k_2f_1][cf_1k_2i_f_] = 1;
	adj[ck_2f_1k_2i_f_][cf_1k_2i_f_] = 1;
	adj[cf_1i_2][cf_1i_2k_i_] = 1;
	adj[ck_2f_1i_2k_i_][cf_1i_2k_i_] = 1;
	adj[ck_2f_1i_1][ck_2f_1k_1i_] = 1;
	adj[ck_2f_1k_2i_][ck_2f_1k_1i_] = 1;
	adj[ck_2f_1i_2k_i_][ck_2f_1k_1i_] = 1;
	adj[cf_2k_2i_][ck_2f_1k_2i_] = 1;
	adj[cf_2f_1][ck_2f_1k_2f_1] = 1;
	adj[ck_2f_1f_2][ck_2f_1k_2f_1] = 1;
	adj[cf_1k_2][cf_1k_2i_k_] = 1;
	adj[ck_2f_1k_2i_k_][cf_1k_2i_k_] = 1;
	adj[ck_2f_1k_1][ck_2f_1i_1k_] = 1;
	adj[ck_2f_1i_2k_][ck_2f_1i_1k_] = 1;
	adj[ck_2f_1k_2i_k_][ck_2f_1i_1k_] = 1;
	adj[cf_2i_2k_][ck_2f_1i_2k_] = 1;
	adj[cf_2i_2f_][ck_2f_1k_2i_f_] = 1;
	adj[ck_2f_1k_2f_1][ck_2f_1k_2i_f_] = 1;
	adj[cf_2k_2i_][ck_2f_1i_2k_i_] = 1;
	adj[ck_2f_1i_2][ck_2f_1i_2k_i_] = 1;
	adj[cf_2i_2k_][ck_2f_1k_2i_k_] = 1;
	adj[ck_2f_1k_2][ck_2f_1k_2i_k_] = 1;

	/*
	 *	Enter the 26 arrows connecting KF_2^0 with (KF_2 minus KF_2^0)
	 */

	adj[k2][czero_op] = 1;
	adj[f1][ci1] = 1;
	adj[f2][ci2] = 1;
	adj[i_1k_][cf_1k_2] = 1;
	adj[i_2k_][cf_2k_2] = 1;
	adj[f_1k_2][ci_1k_] = 1;
	adj[f_2k_2][ci_2k_] = 1;
	adj[f_2f_2][ci_2f_] = 1;
	adj[f_1f_2][ci_1f_] = 1;
	adj[i1][cf1] = 1;
	adj[i2][cf2] = 1;
	adj[k_1i_][ci_1f_] = 1;
	adj[k_2i_][ci_2f_] = 1;
	adj[i_1f_][cf_1f_2] = 1;
	adj[i_1f_][ck_1i_] = 1;
	adj[i_2f_][cf_2f_2] = 1;
	adj[i_2f_][ck_2i_] = 1;
	adj[i_1k_i_][cf_1k_2i_] = 1;
	adj[i_1k_i_][ck_1i_f_] = 1;
	adj[i_2k_i_][cf_2k_2i_] = 1;
	adj[i_2k_i_][ck_2i_f_] = 1;
	adj[f_1k_2i_][ci_1k_i_] = 1;
	adj[f_2k_2i_][ci_2k_i_] = 1;
	adj[k_1i_f_][ci_1k_i_] = 1;
	adj[k_2i_f_][ci_2k_i_] = 1;
	adj[zero_op][ck2] = 1;
}


int	**generate_subsets(int i, int **p, int *q)
{
	int	k;

	for (k=0; k<13; k++)
	{
		if (i&exp_two[k]) p[Id][k] = 1;
		p[czero_op][k] = 1;
	}

	copy_set(p[Id],p[k1]);
	k_1(p[k1]);

	copy_set(p[Id],p[k2]);
	k_2(p[k2]);

	copy_set(p[Id],p[f1]);
	f_1(p[f1],q);

	copy_set(p[Id],p[f2]);
	f_2(p[f2],q);

	copy_set(p[k1],p[i_1k_]);
	i_1(p[i_1k_]);

	copy_set(p[k1],p[i_2k_]);
	i_2(p[i_2k_]);

	copy_set(p[k1],p[f_1k_1]);
	f_1(p[f_1k_1],q);

	copy_set(p[k2],p[f_1k_2]);
	f_1(p[f_1k_2],q);

	copy_set(p[k2],p[f_2k_2]);
	f_2(p[f_2k_2],q);

	copy_set(p[f1],p[k_2f_1]);
	k_2(p[k_2f_1]);

	copy_set(p[f1],p[f_1f_1]);
	f_1(p[f_1f_1],q);

	copy_set(p[f2],p[f_2f_2]);
	f_2(p[f_2f_2],q);

	copy_set(p[f2],p[f_1f_2]);
	f_1(p[f_1f_2],q);

	copy_set(p[f1],p[f_2f_1]);
	f_2(p[f_2f_1],q);

	copy_set(p[i_1k_],p[k_1i_k_]);
	k_1(p[k_1i_k_]);

	copy_set(p[i_1k_],p[k_2i_k_]);
	k_2(p[k_2i_k_]);

	copy_set(p[i_1k_],p[f_1i_1k_]);
	f_1(p[f_1i_1k_],q);

	copy_set(p[i_2k_],p[f_1i_2k_]);
	f_1(p[f_1i_2k_],q);

	copy_set(p[i_2k_],p[f_2i_2k_]);
	f_2(p[f_2i_2k_],q);

	copy_set(p[f_1k_1],p[k_2f_1k_1]);
	k_2(p[k_2f_1k_1]);

	copy_set(p[f_1k_2],p[k_2f_1k_2]);
	k_2(p[k_2f_1k_2]);

	copy_set(p[k_2f_1],p[f_1k_2f_1]);
	f_1(p[f_1k_2f_1],q);

	copy_set(p[f_1f_1],p[k_2f_1f_1]);
	k_2(p[k_2f_1f_1]);

	copy_set(p[f_1f_2],p[k_2f_1f_2]);
	k_2(p[k_2f_1f_2]);

	copy_set(p[Id],p[i1]);
	i_1(p[i1]);

	copy_set(p[Id],p[i2]);
	i_2(p[i2]);

	copy_set(p[i1],p[k_1i_]);
	k_1(p[k_1i_]);

	copy_set(p[i1],p[k_2i_]);
	k_2(p[k_2i_]);

	copy_set(p[i1],p[f_1i_1]);
	f_1(p[f_1i_1],q);

	copy_set(p[i2],p[f_1i_2]);
	f_1(p[f_1i_2],q);

	copy_set(p[i2],p[f_2i_2]);
	f_2(p[f_2i_2],q);

	copy_set(p[f1],p[i_1f_]);
	i_1(p[i_1f_]);

	copy_set(p[f1],p[i_2f_]);
	i_2(p[i_2f_]);

	copy_set(p[k_1i_],p[i_1k_i_]);
	i_1(p[i_1k_i_]);

	copy_set(p[k_1i_],p[i_2k_i_]);
	i_2(p[i_2k_i_]);

	copy_set(p[k_1i_],p[f_1k_1i_]);
	f_1(p[f_1k_1i_],q);

	copy_set(p[k_2i_],p[f_1k_2i_]);
	f_1(p[f_1k_2i_],q);

	copy_set(p[k_2i_],p[f_2k_2i_]);
	f_2(p[f_2k_2i_],q);

	copy_set(p[f_1i_1],p[k_2f_1i_1]);
	k_2(p[k_2f_1i_1]);

	copy_set(p[f_1i_2],p[k_2f_1i_2]);
	k_2(p[k_2f_1i_2]);

	copy_set(p[i_1f_],p[f_1i_1f_]);
	f_1(p[f_1i_1f_],q);

	copy_set(p[i_2f_],p[f_1i_2f_]);
	f_1(p[f_1i_2f_],q);

	copy_set(p[i_2f_],p[f_2i_2f_]);
	f_2(p[f_2i_2f_],q);

	copy_set(p[i_1f_],p[k_1i_f_]);
	k_1(p[k_1i_f_]);

	copy_set(p[i_1f_],p[k_2i_f_]);
	k_2(p[k_2i_f_]);

//	p[zero_op] was already initialized to empty set

	copy_set(p[f_1i_1f_],p[k_2f_1i_1f_]);
	k_2(p[k_2f_1i_1f_]);

	copy_set(p[f_1i_2f_],p[k_2f_1i_2f_]);
	k_2(p[k_2f_1i_2f_]);

	copy_set(p[k_2i_f_],p[f_1k_2i_f_]);
	f_1(p[f_1k_2i_f_],q);

	copy_set(p[i_2k_i_],p[f_1i_2k_i_]);
	f_1(p[f_1i_2k_i_],q);

	copy_set(p[f_1k_1i_],p[k_2f_1k_1i_]);
	k_2(p[k_2f_1k_1i_]);

	copy_set(p[f_1k_2i_],p[k_2f_1k_2i_]);
	k_2(p[k_2f_1k_2i_]);

	copy_set(p[f_1k_2f_1],p[k_2f_1k_2f_1]);
	k_2(p[k_2f_1k_2f_1]);

	copy_set(p[k_2i_k_],p[f_1k_2i_k_]);
	f_1(p[f_1k_2i_k_],q);

	copy_set(p[f_1i_1k_],p[k_2f_1i_1k_]);
	k_2(p[k_2f_1i_1k_]);

	copy_set(p[f_1i_2k_],p[k_2f_1i_2k_]);
	k_2(p[k_2f_1i_2k_]);

	copy_set(p[f_1k_2i_f_],p[k_2f_1k_2i_f_]);
	k_2(p[k_2f_1k_2i_f_]);

	copy_set(p[f_1i_2k_i_],p[k_2f_1i_2k_i_]);
	k_2(p[k_2f_1i_2k_i_]);

	copy_set(p[f_1k_2i_k_],p[k_2f_1k_2i_k_]);
	k_2(p[k_2f_1k_2i_k_]);

	copy_set(p[Id],p[cId]);
	c(p[cId]);

	copy_set(p[k1],p[ck1]);
	c(p[ck1]);

	copy_set(p[k2],p[ck2]);
	c(p[ck2]);

	copy_set(p[f1],p[cf1]);
	c(p[cf1]);

	copy_set(p[f2],p[cf2]);
	c(p[cf2]);

	copy_set(p[i_1k_],p[ci_1k_]);
	c(p[ci_1k_]);

	copy_set(p[i_2k_],p[ci_2k_]);
	c(p[ci_2k_]);

	copy_set(p[f_1k_1],p[cf_1k_1]);
	c(p[cf_1k_1]);

	copy_set(p[f_1k_2],p[cf_1k_2]);
	c(p[cf_1k_2]);

	copy_set(p[f_2k_2],p[cf_2k_2]);
	c(p[cf_2k_2]);

	copy_set(p[k_2f_1],p[ck_2f_1]);
	c(p[ck_2f_1]);

	copy_set(p[f_1f_1],p[cf_1f_1]);
	c(p[cf_1f_1]);

	copy_set(p[f_2f_2],p[cf_2f_2]);
	c(p[cf_2f_2]);

	copy_set(p[f_1f_2],p[cf_1f_2]);
	c(p[cf_1f_2]);

	copy_set(p[f_2f_1],p[cf_2f_1]);
	c(p[cf_2f_1]);

	copy_set(p[k_1i_k_],p[ck_1i_k_]);
	c(p[ck_1i_k_]);

	copy_set(p[k_2i_k_],p[ck_2i_k_]);
	c(p[ck_2i_k_]);

	copy_set(p[f_1i_1k_],p[cf_1i_1k_]);
	c(p[cf_1i_1k_]);

	copy_set(p[f_1i_2k_],p[cf_1i_2k_]);
	c(p[cf_1i_2k_]);

	copy_set(p[f_2i_2k_],p[cf_2i_2k_]);
	c(p[cf_2i_2k_]);

	copy_set(p[k_2f_1k_1],p[ck_2f_1k_1]);
	c(p[ck_2f_1k_1]);

	copy_set(p[k_2f_1k_2],p[ck_2f_1k_2]);
	c(p[ck_2f_1k_2]);

	copy_set(p[f_1k_2f_1],p[cf_1k_2f_1]);
	c(p[cf_1k_2f_1]);

	copy_set(p[k_2f_1f_1],p[ck_2f_1f_1]);
	c(p[ck_2f_1f_1]);

	copy_set(p[k_2f_1f_2],p[ck_2f_1f_2]);
	c(p[ck_2f_1f_2]);

	copy_set(p[i1],p[ci1]);
	c(p[ci1]);

	copy_set(p[i2],p[ci2]);
	c(p[ci2]);

	copy_set(p[k_1i_],p[ck_1i_]);
	c(p[ck_1i_]);

	copy_set(p[k_2i_],p[ck_2i_]);
	c(p[ck_2i_]);

	copy_set(p[f_1i_1],p[cf_1i_1]);
	c(p[cf_1i_1]);

	copy_set(p[f_1i_2],p[cf_1i_2]);
	c(p[cf_1i_2]);

	copy_set(p[f_2i_2],p[cf_2i_2]);
	c(p[cf_2i_2]);

	copy_set(p[i_1f_],p[ci_1f_]);
	c(p[ci_1f_]);

	copy_set(p[i_2f_],p[ci_2f_]);
	c(p[ci_2f_]);

	copy_set(p[i_1k_i_],p[ci_1k_i_]);
	c(p[ci_1k_i_]);

	copy_set(p[i_2k_i_],p[ci_2k_i_]);
	c(p[ci_2k_i_]);

	copy_set(p[f_1k_1i_],p[cf_1k_1i_]);
	c(p[cf_1k_1i_]);

	copy_set(p[f_1k_2i_],p[cf_1k_2i_]);
	c(p[cf_1k_2i_]);

	copy_set(p[f_2k_2i_],p[cf_2k_2i_]);
	c(p[cf_2k_2i_]);

	copy_set(p[k_2f_1i_1],p[ck_2f_1i_1]);
	c(p[ck_2f_1i_1]);

	copy_set(p[k_2f_1i_2],p[ck_2f_1i_2]);
	c(p[ck_2f_1i_2]);

	copy_set(p[f_1i_1f_],p[cf_1i_1f_]);
	c(p[cf_1i_1f_]);

	copy_set(p[f_1i_2f_],p[cf_1i_2f_]);
	c(p[cf_1i_2f_]);

	copy_set(p[f_2i_2f_],p[cf_2i_2f_]);
	c(p[cf_2i_2f_]);

	copy_set(p[k_1i_f_],p[ck_1i_f_]);
	c(p[ck_1i_f_]);

	copy_set(p[k_2i_f_],p[ck_2i_f_]);
	c(p[ck_2i_f_]);

	copy_set(p[k_2f_1i_1f_],p[ck_2f_1i_1f_]);
	c(p[ck_2f_1i_1f_]);

	copy_set(p[k_2f_1i_2f_],p[ck_2f_1i_2f_]);
	c(p[ck_2f_1i_2f_]);

	copy_set(p[f_1k_2i_f_],p[cf_1k_2i_f_]);
	c(p[cf_1k_2i_f_]);

	copy_set(p[f_1i_2k_i_],p[cf_1i_2k_i_]);
	c(p[cf_1i_2k_i_]);

	copy_set(p[k_2f_1k_1i_],p[ck_2f_1k_1i_]);
	c(p[ck_2f_1k_1i_]);

	copy_set(p[k_2f_1k_2i_],p[ck_2f_1k_2i_]);
	c(p[ck_2f_1k_2i_]);

	copy_set(p[k_2f_1k_2f_1],p[ck_2f_1k_2f_1]);
	c(p[ck_2f_1k_2f_1]);

	copy_set(p[f_1k_2i_k_],p[cf_1k_2i_k_]);
	c(p[cf_1k_2i_k_]);

	copy_set(p[k_2f_1i_1k_],p[ck_2f_1i_1k_]);
	c(p[ck_2f_1i_1k_]);

	copy_set(p[k_2f_1i_2k_],p[ck_2f_1i_2k_]);
	c(p[ck_2f_1i_2k_]);

	copy_set(p[k_2f_1k_2i_f_],p[ck_2f_1k_2i_f_]);
	c(p[ck_2f_1k_2i_f_]);

	copy_set(p[k_2f_1i_2k_i_],p[ck_2f_1i_2k_i_]);
	c(p[ck_2f_1i_2k_i_]);

	copy_set(p[k_2f_1k_2i_k_],p[ck_2f_1k_2i_k_]);
	c(p[ck_2f_1k_2i_k_]);

	return p;
}
