#
#  Eliminate all inequalities not in the partial order on KF_2.
#
#  Mark Bowron, 18 Nov 2019.
#

# initialize adjacency matrix adj to 120 by 120 identity matrix
adj = [[0] * 120 for _ in range(120)]
for i in range(120):
	adj[i][i] = 1

# 120 operators in KF_2
op = (
'Id','k1','k2','f1','f2',
'i_1k_*','i_2k_*','f_1k_1','f_1k_2','f_2k_2',
'k_2f_1','f_1f_1','f_2f_2','f_1f_2','f_2f_1',
'k_1i_*k_*','k_2i_*k_*','f_1i_1k_*','f_1i_2k_*','f_2i_2k_*',
'k_2f_1k_1','k_2f_1k_2','f_1k_2f_1','k_2f_1f_1','k_2f_1f_2',
'i1','i2','k_1i_*','k_2i_*','f_1i_1',
'f_1i_2','f_2i_2','i_1f_*','i_2f_*','i_1k_*i_*',
'i_2k_*i_*','f_1k_1i_*','f_1k_2i_*','f_2k_2i_*','k_2f_1i_1',
'k_2f_1i_2','f_1i_1f_*','f_1i_2f_*','f_2i_2f_*','k_1i_*f_*',
'k_2i_*f_*','0','k_2f_1i_1f_*','k_2f_1i_2f_*','f_1k_2i_*f_*',
'f_1i_2k_*i_*','k_2f_1k_1i_*','k_2f_1k_2i_*','k_2f_1k_2f_1','f_1k_2i_*k_*',
'k_2f_1i_1k_*','k_2f_1i_2k_*','k_2f_1k_2i_*f_*','k_2f_1i_2k_*i_*','k_2f_1k_2i_*k_*',
'cId','ck1','ck2','cf1','cf2',
'ci_1k_*','ci_2k_*','cf_1k_1','cf_1k_2','cf_2k_2',
'ck_2f_1','cf_1f_1','cf_2f_2','cf_1f_2','cf_2f_1',
'ck_1i_*k_*','ck_2i_*k_*','cf_1i_1k_*','cf_1i_2k_*','cf_2i_2k_*',
'ck_2f_1k_1','ck_2f_1k_2','cf_1k_2f_1','ck_2f_1f_1','ck_2f_1f_2',
'ci1','ci2','ck_1i_*','ck_2i_*','cf_1i_1',
'cf_1i_2','cf_2i_2','ci_1f_*','ci_2f_*','ci_1k_*i_*',
'ci_2k_*i_*','cf_1k_1i_*','cf_1k_2i_*','cf_2k_2i_*','ck_2f_1i_1',
'ck_2f_1i_2','cf_1i_1f_*','cf_1i_2f_*','cf_2i_2f_*','ck_1i_*f_*',
'ck_2i_*f_*','c0','ck_2f_1i_1f_*','ck_2f_1i_2f_*','cf_1k_2i_*f_*',
'cf_1i_2k_*i_*','ck_2f_1k_1i_*','ck_2f_1k_2i_*','ck_2f_1k_2f_1','cf_1k_2i_*k_*',
'ck_2f_1i_1k_*','ck_2f_1i_2k_*','ck_2f_1k_2i_*f_*','ck_2f_1i_2k_*i_*','ck_2f_1k_2i_*k_*'
)

# 260 arrows in partial order on KF_2
ineqs = (
('Id','k1'),
('k1','k2'),
('f1','k1'),
('f1','k_2f_1'),
('f2','k2'),
('i_1k_*','k_1i_*k_*'),
('i_2k_*','i_1k_*'),
('f_1k_1','f_1k_2'),
('f_1k_1','f_1f_1'),
('f_1k_1','k_2f_1k_1'),
('f_1k_2','f_1f_2'),
('f_1k_2','k_2f_1k_2'),
('f_2k_2','f_2f_2'),
('k_2f_1','f2'),
('f_1f_1','f1'),
('f_1f_1','f_1k_2f_1'),
('f_1f_1','k_2f_1f_1'),
('f_2f_2','f2'),
('f_1f_2','k_2f_1f_2'),
('f_2f_1','k_2f_1'),
('f_2f_1','f_2f_2'),
('k_1i_*k_*','k1'),
('k_1i_*k_*','k_2i_*k_*'),
('k_2i_*k_*','k2'),
('f_1i_1k_*','f_1k_1'),
('f_1i_1k_*','f_1i_2k_*'),
('f_1i_1k_*','f_1k_2i_*k_*'),
('f_1i_1k_*','k_2f_1i_1k_*'),
('f_1i_2k_*','k_1i_*k_*'),
('f_1i_2k_*','k_2f_1i_2k_*'),
('f_2i_2k_*','f_2k_2'),
('f_2i_2k_*','k_2i_*k_*'),
('k_2f_1k_1','k_2f_1k_2'),
('k_2f_1k_1','k_2f_1f_1'),
('k_2f_1k_2','f_2k_2'),
('k_2f_1k_2','k_2f_1f_2'),
('f_1k_2f_1','f_1f_2'),
('f_1k_2f_1','k_2f_1k_2f_1'),
('k_2f_1f_1','k_2f_1k_2f_1'),
('k_2f_1f_2','f_2f_2'),
('i1','Id'),
('i1','i_1k_*i_*'),
('i2','i1'),
('i2','i_2k_*i_*'),
('k_1i_*','k_1i_*k_*'),
('k_1i_*','k_2i_*'),
('k_2i_*','k_2i_*k_*'),
('f_1i_1','f_1f_1'),
('f_1i_1','f_1i_2'),
('f_1i_1','k_2f_1i_1'),
('f_1i_2','f_1f_2'),
('f_1i_2','k_1i_*'),
('f_1i_2','k_2f_1i_2'),
('f_2i_2','f_2f_2'),
('f_2i_2','k_2i_*'),
('i_1f_*','i_1k_*'),
('i_1f_*','k_1i_*f_*'),
('i_2f_*','i_2k_*'),
('i_2f_*','i_1f_*'),
('i_1k_*i_*','i_1k_*'),
('i_1k_*i_*','k_1i_*'),
('i_2k_*i_*','i_2k_*'),
('i_2k_*i_*','i_1k_*i_*'),
('f_1k_1i_*','f_1i_1'),
('f_1k_1i_*','f_1k_2i_*'),
('f_1k_1i_*','f_1i_2k_*i_*'),
('f_1k_1i_*','k_2f_1k_1i_*'),
('f_1k_2i_*','k_2f_1k_2i_*'),
('f_2k_2i_*','f_2i_2'),
('k_2f_1i_1','k_2f_1f_1'),
('k_2f_1i_1','k_2f_1i_2'),
('k_2f_1i_2','k_2f_1f_2'),
('k_2f_1i_2','f_2i_2'),
('f_1i_1f_*','f_1f_1'),
('f_1i_1f_*','f_1i_2f_*'),
('f_1i_1f_*','k_2f_1i_1f_*'),
('f_1i_1f_*','f_1k_2i_*f_*'),
('f_1i_2f_*','k_1i_*f_*'),
('f_1i_2f_*','k_2f_1i_2f_*'),
('f_2i_2f_*','f_2f_1'),
('f_2i_2f_*','k_2i_*f_*'),
('k_1i_*f_*','f1'),
('k_1i_*f_*','k_1i_*k_*'),
('k_1i_*f_*','k_2i_*f_*'),
('k_2i_*f_*','k_2f_1'),
('k_2i_*f_*','k_2i_*k_*'),
('0','f_1i_1k_*'),
('0','i2'),
('0','i_2f_*'),
('0','f_1k_1i_*'),
('0','f_1i_1f_*'),
('k_2f_1i_1f_*','k_2f_1f_1'),
('k_2f_1i_1f_*','k_2f_1i_2f_*'),
('k_2f_1i_1f_*','k_2f_1k_2i_*f_*'),
('k_2f_1i_2f_*','f_2i_2f_*'),
('f_1k_2i_*f_*','f_1k_2f_1'),
('f_1k_2i_*f_*','k_2f_1k_2i_*f_*'),
('f_1i_2k_*i_*','f_1i_2'),
('f_1i_2k_*i_*','k_2f_1i_2k_*i_*'),
('k_2f_1k_1i_*','k_2f_1i_1'),
('k_2f_1k_1i_*','k_2f_1k_2i_*'),
('k_2f_1k_1i_*','k_2f_1i_2k_*i_*'),
('k_2f_1k_2i_*','f_2k_2i_*'),
('k_2f_1k_2f_1','f_2f_1'),
('k_2f_1k_2f_1','k_2f_1f_2'),
('f_1k_2i_*k_*','f_1k_2'),
('f_1k_2i_*k_*','k_2f_1k_2i_*k_*'),
('k_2f_1i_1k_*','k_2f_1k_1'),
('k_2f_1i_1k_*','k_2f_1i_2k_*'),
('k_2f_1i_1k_*','k_2f_1k_2i_*k_*'),
('k_2f_1i_2k_*','f_2i_2k_*'),
('k_2f_1k_2i_*f_*','f_2i_2f_*'),
('k_2f_1k_2i_*f_*','k_2f_1k_2f_1'),
('k_2f_1i_2k_*i_*','f_2k_2i_*'),
('k_2f_1i_2k_*i_*','k_2f_1i_2'),
('k_2f_1k_2i_*k_*','f_2i_2k_*'),
('k_2f_1k_2i_*k_*','k_2f_1k_2'),
('ck1','cId'),
('ck2','ck1'),
('ck1','cf1'),
('ck_2f_1','cf1'),
('ck2','cf2'),
('ck_1i_*k_*','ci_1k_*'),
('ci_1k_*','ci_2k_*'),
('cf_1k_2','cf_1k_1'),
('cf_1f_1','cf_1k_1'),
('ck_2f_1k_1','cf_1k_1'),
('cf_1f_2','cf_1k_2'),
('ck_2f_1k_2','cf_1k_2'),
('cf_2f_2','cf_2k_2'),
('cf2','ck_2f_1'),
('cf1','cf_1f_1'),
('cf_1k_2f_1','cf_1f_1'),
('ck_2f_1f_1','cf_1f_1'),
('cf2','cf_2f_2'),
('ck_2f_1f_2','cf_1f_2'),
('ck_2f_1','cf_2f_1'),
('cf_2f_2','cf_2f_1'),
('ck1','ck_1i_*k_*'),
('ck_2i_*k_*','ck_1i_*k_*'),
('ck2','ck_2i_*k_*'),
('cf_1k_1','cf_1i_1k_*'),
('cf_1i_2k_*','cf_1i_1k_*'),
('cf_1k_2i_*k_*','cf_1i_1k_*'),
('ck_2f_1i_1k_*','cf_1i_1k_*'),
('ck_1i_*k_*','cf_1i_2k_*'),
('ck_2f_1i_2k_*','cf_1i_2k_*'),
('cf_2k_2','cf_2i_2k_*'),
('ck_2i_*k_*','cf_2i_2k_*'),
('ck_2f_1k_2','ck_2f_1k_1'),
('ck_2f_1f_1','ck_2f_1k_1'),
('cf_2k_2','ck_2f_1k_2'),
('ck_2f_1f_2','ck_2f_1k_2'),
('cf_1f_2','cf_1k_2f_1'),
('ck_2f_1k_2f_1','cf_1k_2f_1'),
('ck_2f_1k_2f_1','ck_2f_1f_1'),
('cf_2f_2','ck_2f_1f_2'),
('cId','ci1'),
('ci_1k_*i_*','ci1'),
('ci1','ci2'),
('ci_2k_*i_*','ci2'),
('ck_1i_*k_*','ck_1i_*'),
('ck_2i_*','ck_1i_*'),
('ck_2i_*k_*','ck_2i_*'),
('cf_1f_1','cf_1i_1'),
('cf_1i_2','cf_1i_1'),
('ck_2f_1i_1','cf_1i_1'),
('cf_1f_2','cf_1i_2'),
('ck_1i_*','cf_1i_2'),
('ck_2f_1i_2','cf_1i_2'),
('cf_2f_2','cf_2i_2'),
('ck_2i_*','cf_2i_2'),
('ci_1k_*','ci_1f_*'),
('ck_1i_*f_*','ci_1f_*'),
('ci_2k_*','ci_2f_*'),
('ci_1f_*','ci_2f_*'),
('ci_1k_*','ci_1k_*i_*'),
('ck_1i_*','ci_1k_*i_*'),
('ci_2k_*','ci_2k_*i_*'),
('ci_1k_*i_*','ci_2k_*i_*'),
('cf_1i_1','cf_1k_1i_*'),
('cf_1k_2i_*','cf_1k_1i_*'),
('cf_1i_2k_*i_*','cf_1k_1i_*'),
('ck_2f_1k_1i_*','cf_1k_1i_*'),
('ck_2f_1k_2i_*','cf_1k_2i_*'),
('cf_2i_2','cf_2k_2i_*'),
('ck_2f_1f_1','ck_2f_1i_1'),
('ck_2f_1i_2','ck_2f_1i_1'),
('ck_2f_1f_2','ck_2f_1i_2'),
('cf_2i_2','ck_2f_1i_2'),
('cf_1f_1','cf_1i_1f_*'),
('cf_1i_2f_*','cf_1i_1f_*'),
('ck_2f_1i_1f_*','cf_1i_1f_*'),
('cf_1k_2i_*f_*','cf_1i_1f_*'),
('ck_1i_*f_*','cf_1i_2f_*'),
('ck_2f_1i_2f_*','cf_1i_2f_*'),
('cf_2f_1','cf_2i_2f_*'),
('ck_2i_*f_*','cf_2i_2f_*'),
('cf1','ck_1i_*f_*'),
('ck_1i_*k_*','ck_1i_*f_*'),
('ck_2i_*f_*','ck_1i_*f_*'),
('ck_2f_1','ck_2i_*f_*'),
('ck_2i_*k_*','ck_2i_*f_*'),
('cf_1i_1k_*','c0'),
('ci2','c0'),
('ci_2f_*','c0'),
('cf_1k_1i_*','c0'),
('cf_1i_1f_*','c0'),
('ck_2f_1f_1','ck_2f_1i_1f_*'),
('ck_2f_1i_2f_*','ck_2f_1i_1f_*'),
('ck_2f_1k_2i_*f_*','ck_2f_1i_1f_*'),
('cf_2i_2f_*','ck_2f_1i_2f_*'),
('cf_1k_2f_1','cf_1k_2i_*f_*'),
('ck_2f_1k_2i_*f_*','cf_1k_2i_*f_*'),
('cf_1i_2','cf_1i_2k_*i_*'),
('ck_2f_1i_2k_*i_*','cf_1i_2k_*i_*'),
('ck_2f_1i_1','ck_2f_1k_1i_*'),
('ck_2f_1k_2i_*','ck_2f_1k_1i_*'),
('ck_2f_1i_2k_*i_*','ck_2f_1k_1i_*'),
('cf_2k_2i_*','ck_2f_1k_2i_*'),
('cf_2f_1','ck_2f_1k_2f_1'),
('ck_2f_1f_2','ck_2f_1k_2f_1'),
('cf_1k_2','cf_1k_2i_*k_*'),
('ck_2f_1k_2i_*k_*','cf_1k_2i_*k_*'),
('ck_2f_1k_1','ck_2f_1i_1k_*'),
('ck_2f_1i_2k_*','ck_2f_1i_1k_*'),
('ck_2f_1k_2i_*k_*','ck_2f_1i_1k_*'),
('cf_2i_2k_*','ck_2f_1i_2k_*'),
('cf_2i_2f_*','ck_2f_1k_2i_*f_*'),
('ck_2f_1k_2f_1','ck_2f_1k_2i_*f_*'),
('cf_2k_2i_*','ck_2f_1i_2k_*i_*'),
('ck_2f_1i_2','ck_2f_1i_2k_*i_*'),
('cf_2i_2k_*','ck_2f_1k_2i_*k_*'),
('ck_2f_1k_2','ck_2f_1k_2i_*k_*'),
('k2','c0'),
('f1','ci1'),
('f2','ci2'),
('i_1k_*','cf_1k_2'),
('i_2k_*','cf_2k_2'),
('f_1k_2','ci_1k_*'),
('f_2k_2','ci_2k_*'),
('f_2f_2','ci_2f_*'),
('f_1f_2','ci_1f_*'),
('i1','cf1'),
('i2','cf2'),
('k_1i_*','ci_1f_*'),
('k_2i_*','ci_2f_*'),
('i_1f_*','cf_1f_2'),
('i_1f_*','ck_1i_*'),
('i_2f_*','cf_2f_2'),
('i_2f_*','ck_2i_*'),
('i_1k_*i_*','cf_1k_2i_*'),
('i_1k_*i_*','ck_1i_*f_*'),
('i_2k_*i_*','cf_2k_2i_*'),
('i_2k_*i_*','ck_2i_*f_*'),
('f_1k_2i_*','ci_1k_*i_*'),
('f_2k_2i_*','ci_2k_*i_*'),
('k_1i_*f_*','ci_1k_*i_*'),
('k_2i_*f_*','ci_2k_*i_*'),
('0','ck2')
)

# for each arrow in the poset diagram for KF_2, put a 1 in adj
for arrow in ineqs:
	adj[op.index(arrow[0])][op.index(arrow[1])] = 1

def warshall(a):
	"""
	compute the transitive closure of an adjacency matrix
	using Floyd-Warshall algorithm
	"""
	assert (len(row) == len(a) for row in a)
	n = len(a)
	for k in range(n):
		for i in range(n):
			for j in range(n):
				a[i][j] = a[i][j] or (a[i][k] and a[k][j])
	return a

adj = warshall(adj)

# x represents an arbitrary union of blocks in P

def k_1(x):
	"""Sorgenfrey closure operator"""
	assert (len(x) == 13)
	p = list(x)
	if p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]:
		p[0] = 1
	if p[1]+p[2]:
		p[1] = 1
	"""p[2] = p[2]"""
	if p[3]+p[4]:
		p[3] = 1
	"""p[4] = p[4]"""
	if p[5]+p[6]+p[7]:
		p[5] = 1
	if p[6]+p[7]:
		p[6] = 1
		p[7] = 1
	if p[8]+p[9]:
		p[8] = 1
	"""p[9] = p[9]"""
	if p[10]+p[11]+p[12]:
		p[10] = 1
	if p[11]+p[12]:
		p[11] = 1
		p[12] = 1
	return p

def k_2(x):
	"""usual closure operator"""
	assert (len(x) == 13)
	p = list(x)
	if p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[9]:
		p[0] = 1
	if p[1]+p[2]+p[6]+p[7]:
		p[1] = 1
	"""p[2] = p[2]"""
	if p[2]+p[3]+p[4]:
		p[3] = 1
	"""p[4] = p[4]"""
	if p[4]+p[5]+p[6]+p[7]:
		p[5] = 1
	if p[6]+p[7]:
		p[6] = 1
		p[7] = 1
	if p[6]+p[7]+p[8]+p[9]:
		p[8] = 1
	"""p[9] = p[9]"""
	for i in range(13):
		if p[i]:
			p[10] = 1
			break
	if p[11]+p[12]:
		p[11] = 1
		p[12] = 1
	return p

def c(x):
	"""complement operator"""
	assert (len(x) == 13)
	p = list(x)
	for i in range(13):
		if p[i]:
			p[i] = 0
		else:
			p[i] = 1
	return p

def i_1(x):
	"""Sorgenfrey interior operator"""
	assert (len(x) == 13)
	p = list(x)
	p = c(p)
	p = k_1(p)
	p = c(p)
	return p

def i_2(x):
	"""usual interior operator"""
	assert (len(x) == 13)
	p = list(x)
	p = c(p)
	p = k_2(p)
	p = c(p)
	return p

def intersect(x,y):
	assert (len(x) == 13 and len(y) == 13)
	p = list(x)
	q = list(y)
	for i in range(13):
		if not p[i]*q[i]:
			p[i] = 0
	return p

def f_1(x):
	"""Sorgenfrey frontier operator"""
	assert (len(x) == 13)
	p = list(x)
	cp = c(list(p))
	p = intersect(k_1(p),k_1(cp))
	return p

def f_2(x):
	"""usual frontier operator"""
	assert (len(x) == 13)
	p = list(x)
	cp = c(list(p))
	p = intersect(k_2(p),k_2(cp))
	return p

def genfam(p):
	assert (len(p) == 13)
	"""F = family generated by p under KF_2"""
	F = [[0] * 13 for _ in range(120)]

	F[op.index('Id')] = p
	F[op.index('k1')] = k_1(p)
	F[op.index('k2')] = k_2(p)
	F[op.index('f1')] = f_1(p)
	F[op.index('f2')] = f_2(p)
	F[op.index('i_1k_*')] = i_1(F[op.index('k1')])
	F[op.index('i_2k_*')] = i_2(F[op.index('k1')])
	F[op.index('f_1k_1')] = f_1(F[op.index('k1')])
	F[op.index('f_1k_2')] = f_1(F[op.index('k2')])
	F[op.index('f_2k_2')] = f_2(F[op.index('k2')])
	F[op.index('k_2f_1')] = k_2(F[op.index('f1')])
	F[op.index('f_1f_1')] = f_1(F[op.index('f1')])
	F[op.index('f_2f_2')] = f_2(F[op.index('f2')])
	F[op.index('f_1f_2')] = f_1(F[op.index('f2')])
	F[op.index('f_2f_1')] = f_2(F[op.index('f1')])
	F[op.index('k_1i_*k_*')] = k_1(F[op.index('i_1k_*')])
	F[op.index('k_2i_*k_*')] = k_2(F[op.index('i_1k_*')])
	F[op.index('f_1i_1k_*')] = f_1(F[op.index('i_1k_*')])
	F[op.index('f_1i_2k_*')] = f_1(F[op.index('i_2k_*')])
	F[op.index('f_2i_2k_*')] = f_2(F[op.index('i_2k_*')])
	F[op.index('k_2f_1k_1')] = k_2(F[op.index('f_1k_1')])
	F[op.index('k_2f_1k_2')] = k_2(F[op.index('f_1k_2')])
	F[op.index('f_1k_2f_1')] = f_1(F[op.index('k_2f_1')])
	F[op.index('k_2f_1f_1')] = k_2(F[op.index('f_1f_1')])
	F[op.index('k_2f_1f_2')] = k_2(F[op.index('f_1f_2')])
	F[op.index('i1')] = i_1(p)
	F[op.index('i2')] = i_2(p)
	F[op.index('k_1i_*')] = k_1(F[op.index('i1')])
	F[op.index('k_2i_*')] = k_2(F[op.index('i1')])
	F[op.index('f_1i_1')] = f_1(F[op.index('i1')])
	F[op.index('f_1i_2')] = f_1(F[op.index('i2')])
	F[op.index('f_2i_2')] = f_2(F[op.index('i2')])
	F[op.index('i_1f_*')] = i_1(F[op.index('f1')])
	F[op.index('i_2f_*')] = i_2(F[op.index('f1')])
	F[op.index('i_1k_*i_*')] = i_1(F[op.index('k_1i_*')])
	F[op.index('i_2k_*i_*')] = i_2(F[op.index('k_1i_*')])
	F[op.index('f_1k_1i_*')] = f_1(F[op.index('k_1i_*')])
	F[op.index('f_1k_2i_*')] = f_1(F[op.index('k_2i_*')])
	F[op.index('f_2k_2i_*')] = f_2(F[op.index('k_2i_*')])
	F[op.index('k_2f_1i_1')] = k_2(F[op.index('f_1i_1')])
	F[op.index('k_2f_1i_2')] = k_2(F[op.index('f_1i_2')])
	F[op.index('f_1i_1f_*')] = f_1(F[op.index('i_1f_*')])
	F[op.index('f_1i_2f_*')] = f_1(F[op.index('i_2f_*')])
	F[op.index('f_2i_2f_*')] = f_2(F[op.index('i_2f_*')])
	F[op.index('k_1i_*f_*')] = k_1(F[op.index('i_1f_*')])
	F[op.index('k_2i_*f_*')] = k_2(F[op.index('i_1f_*')])
	"""F[op.index('0')] was already initialized to the empty set"""
	F[op.index('k_2f_1i_1f_*')] = k_2(F[op.index('f_1i_1f_*')])
	F[op.index('k_2f_1i_2f_*')] = k_2(F[op.index('f_1i_2f_*')])
	F[op.index('f_1k_2i_*f_*')] = f_1(F[op.index('k_2i_*f_*')])
	F[op.index('f_1i_2k_*i_*')] = f_1(F[op.index('i_2k_*i_*')])
	F[op.index('k_2f_1k_1i_*')] = k_2(F[op.index('f_1k_1i_*')])
	F[op.index('k_2f_1k_2i_*')] = k_2(F[op.index('f_1k_2i_*')])
	F[op.index('k_2f_1k_2f_1')] = k_2(F[op.index('f_1k_2f_1')])
	F[op.index('f_1k_2i_*k_*')] = f_1(F[op.index('k_2i_*k_*')])
	F[op.index('k_2f_1i_1k_*')] = k_2(F[op.index('f_1i_1k_*')])
	F[op.index('k_2f_1i_2k_*')] = k_2(F[op.index('f_1i_2k_*')])
	F[op.index('k_2f_1k_2i_*f_*')] = k_2(F[op.index('f_1k_2i_*f_*')])
	F[op.index('k_2f_1i_2k_*i_*')] = k_2(F[op.index('f_1i_2k_*i_*')])
	F[op.index('k_2f_1k_2i_*k_*')] = k_2(F[op.index('f_1k_2i_*k_*')])
	F[op.index('cId')] = c(F[op.index('Id')])
	F[op.index('ck1')] = c(F[op.index('k1')])
	F[op.index('ck2')] = c(F[op.index('k2')])
	F[op.index('cf1')] = c(F[op.index('f1')])
	F[op.index('cf2')] = c(F[op.index('f2')])
	F[op.index('ci_1k_*')] = c(F[op.index('i_1k_*')])
	F[op.index('ci_2k_*')] = c(F[op.index('i_2k_*')])
	F[op.index('cf_1k_1')] = c(F[op.index('f_1k_1')])
	F[op.index('cf_1k_2')] = c(F[op.index('f_1k_2')])
	F[op.index('cf_2k_2')] = c(F[op.index('f_2k_2')])
	F[op.index('ck_2f_1')] = c(F[op.index('k_2f_1')])
	F[op.index('cf_1f_1')] = c(F[op.index('f_1f_1')])
	F[op.index('cf_2f_2')] = c(F[op.index('f_2f_2')])
	F[op.index('cf_1f_2')] = c(F[op.index('f_1f_2')])
	F[op.index('cf_2f_1')] = c(F[op.index('f_2f_1')])
	F[op.index('ck_1i_*k_*')] = c(F[op.index('k_1i_*k_*')])
	F[op.index('ck_2i_*k_*')] = c(F[op.index('k_2i_*k_*')])
	F[op.index('cf_1i_1k_*')] = c(F[op.index('f_1i_1k_*')])
	F[op.index('cf_1i_2k_*')] = c(F[op.index('f_1i_2k_*')])
	F[op.index('cf_2i_2k_*')] = c(F[op.index('f_2i_2k_*')])
	F[op.index('ck_2f_1k_1')] = c(F[op.index('k_2f_1k_1')])
	F[op.index('ck_2f_1k_2')] = c(F[op.index('k_2f_1k_2')])
	F[op.index('cf_1k_2f_1')] = c(F[op.index('f_1k_2f_1')])
	F[op.index('ck_2f_1f_1')] = c(F[op.index('k_2f_1f_1')])
	F[op.index('ck_2f_1f_2')] = c(F[op.index('k_2f_1f_2')])
	F[op.index('ci1')] = c(F[op.index('i1')])
	F[op.index('ci2')] = c(F[op.index('i2')])
	F[op.index('ck_1i_*')] = c(F[op.index('k_1i_*')])
	F[op.index('ck_2i_*')] = c(F[op.index('k_2i_*')])
	F[op.index('cf_1i_1')] = c(F[op.index('f_1i_1')])
	F[op.index('cf_1i_2')] = c(F[op.index('f_1i_2')])
	F[op.index('cf_2i_2')] = c(F[op.index('f_2i_2')])
	F[op.index('ci_1f_*')] = c(F[op.index('i_1f_*')])
	F[op.index('ci_2f_*')] = c(F[op.index('i_2f_*')])
	F[op.index('ci_1k_*i_*')] = c(F[op.index('i_1k_*i_*')])
	F[op.index('ci_2k_*i_*')] = c(F[op.index('i_2k_*i_*')])
	F[op.index('cf_1k_1i_*')] = c(F[op.index('f_1k_1i_*')])
	F[op.index('cf_1k_2i_*')] = c(F[op.index('f_1k_2i_*')])
	F[op.index('cf_2k_2i_*')] = c(F[op.index('f_2k_2i_*')])
	F[op.index('ck_2f_1i_1')] = c(F[op.index('k_2f_1i_1')])
	F[op.index('ck_2f_1i_2')] = c(F[op.index('k_2f_1i_2')])
	F[op.index('cf_1i_1f_*')] = c(F[op.index('f_1i_1f_*')])
	F[op.index('cf_1i_2f_*')] = c(F[op.index('f_1i_2f_*')])
	F[op.index('cf_2i_2f_*')] = c(F[op.index('f_2i_2f_*')])
	F[op.index('ck_1i_*f_*')] = c(F[op.index('k_1i_*f_*')])
	F[op.index('ck_2i_*f_*')] = c(F[op.index('k_2i_*f_*')])
	F[op.index('c0')] = c(F[op.index('0')])
	F[op.index('ck_2f_1i_1f_*')] = c(F[op.index('k_2f_1i_1f_*')])
	F[op.index('ck_2f_1i_2f_*')] = c(F[op.index('k_2f_1i_2f_*')])
	F[op.index('cf_1k_2i_*f_*')] = c(F[op.index('f_1k_2i_*f_*')])
	F[op.index('cf_1i_2k_*i_*')] = c(F[op.index('f_1i_2k_*i_*')])
	F[op.index('ck_2f_1k_1i_*')] = c(F[op.index('k_2f_1k_1i_*')])
	F[op.index('ck_2f_1k_2i_*')] = c(F[op.index('k_2f_1k_2i_*')])
	F[op.index('ck_2f_1k_2f_1')] = c(F[op.index('k_2f_1k_2f_1')])
	F[op.index('cf_1k_2i_*k_*')] = c(F[op.index('f_1k_2i_*k_*')])
	F[op.index('ck_2f_1i_1k_*')] = c(F[op.index('k_2f_1i_1k_*')])
	F[op.index('ck_2f_1i_2k_*')] = c(F[op.index('k_2f_1i_2k_*')])
	F[op.index('ck_2f_1k_2i_*f_*')] = c(F[op.index('k_2f_1k_2i_*f_*')])
	F[op.index('ck_2f_1i_2k_*i_*')] = c(F[op.index('k_2f_1i_2k_*i_*')])
	F[op.index('ck_2f_1k_2i_*k_*')] = c(F[op.index('k_2f_1k_2i_*k_*')])

	return F

def contained_in(p,q):
	assert (len(p) == 13 and len(q) == 13)
	for i in range(13):
		if p[i] and not q[i]:
			return 0
	return 1

power_set = 2**13
for i in range(power_set):
	p = [0] * 13
	for j in range(13):
		if i & 2**j:
			p[j] = 1

# apply the 120 operators in KF_2 to the seed set p
	fam = genfam(p)

# attempt to eliminate each live inequality in adj
	for j in range(120):
		for k in range(120):
			if not adj[j][k]:
				if not contained_in(fam[j],fam[k]):
					adj[j][k] = 1

# if every inequality got eliminated then every entry in adj is now 1
success = 1
for j in range(120):
	for k in range(120):
		if not adj[j][k]:
			success = 0
			break
	if not success:
		break
if success:
	print("success")
else:
	print("fail")
