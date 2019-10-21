#
#  Eliminate all inequalities not implied by Figure 2.
#
#  Mark Bowron, 21 Oct 2019.
#

# initialize adjacency matrix adj to 60 by 60 identity matrix
adj = [[0] * 60 for _ in range(60)]
for i in range(60):
	adj[i][i] = 1

# 60 operators in KF_2^0
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
'k_2f_1i_1k_*','k_2f_1i_2k_*','k_2f_1k_2i_*f_*','k_2f_1i_2k_*i_*','k_2f_1k_2i_*k_*'
)

# 117 arrows in Figure 2
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
('k_2f_1k_2i_*k_*','k_2f_1k_2')
)

# for each arrow in Figure 2, put a 1 in adj
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
	"""f = family generated by p under KF_2^0"""
	f = [[0] * 13 for _ in range(60)]

	f[op.index('Id')] = p
	f[op.index('k1')] = k_1(p)
	f[op.index('k2')] = k_2(p)
	f[op.index('f1')] = f_1(p)
	f[op.index('f2')] = f_2(p)
	f[op.index('i_1k_*')] = i_1(f[op.index('k1')])
	f[op.index('i_2k_*')] = i_2(f[op.index('k1')])
	f[op.index('f_1k_1')] = f_1(f[op.index('k1')])
	f[op.index('f_1k_2')] = f_1(f[op.index('k2')])
	f[op.index('f_2k_2')] = f_2(f[op.index('k2')])
	f[op.index('k_2f_1')] = k_2(f[op.index('f1')])
	f[op.index('f_1f_1')] = f_1(f[op.index('f1')])
	f[op.index('f_2f_2')] = f_2(f[op.index('f2')])
	f[op.index('f_1f_2')] = f_1(f[op.index('f2')])
	f[op.index('f_2f_1')] = f_2(f[op.index('f1')])
	f[op.index('k_1i_*k_*')] = k_1(f[op.index('i_1k_*')])
	f[op.index('k_2i_*k_*')] = k_2(f[op.index('i_1k_*')])
	f[op.index('f_1i_1k_*')] = f_1(f[op.index('i_1k_*')])
	f[op.index('f_1i_2k_*')] = f_1(f[op.index('i_2k_*')])
	f[op.index('f_2i_2k_*')] = f_2(f[op.index('i_2k_*')])
	f[op.index('k_2f_1k_1')] = k_2(f[op.index('f_1k_1')])
	f[op.index('k_2f_1k_2')] = k_2(f[op.index('f_1k_2')])
	f[op.index('f_1k_2f_1')] = f_1(f[op.index('k_2f_1')])
	f[op.index('k_2f_1f_1')] = k_2(f[op.index('f_1f_1')])
	f[op.index('k_2f_1f_2')] = k_2(f[op.index('f_1f_2')])
	f[op.index('i1')] = i_1(p)
	f[op.index('i2')] = i_2(p)
	f[op.index('k_1i_*')] = k_1(f[op.index('i1')])
	f[op.index('k_2i_*')] = k_2(f[op.index('i1')])
	f[op.index('f_1i_1')] = f_1(f[op.index('i1')])
	f[op.index('f_1i_2')] = f_1(f[op.index('i2')])
	f[op.index('f_2i_2')] = f_2(f[op.index('i2')])
	f[op.index('i_1f_*')] = i_1(f[op.index('f1')])
	f[op.index('i_2f_*')] = i_2(f[op.index('f1')])
	f[op.index('i_1k_*i_*')] = i_1(f[op.index('k_1i_*')])
	f[op.index('i_2k_*i_*')] = i_2(f[op.index('k_1i_*')])
	f[op.index('f_1k_1i_*')] = f_1(f[op.index('k_1i_*')])
	f[op.index('f_1k_2i_*')] = f_1(f[op.index('k_2i_*')])
	f[op.index('f_2k_2i_*')] = f_2(f[op.index('k_2i_*')])
	f[op.index('k_2f_1i_1')] = k_2(f[op.index('f_1i_1')])
	f[op.index('k_2f_1i_2')] = k_2(f[op.index('f_1i_2')])
	f[op.index('f_1i_1f_*')] = f_1(f[op.index('i_1f_*')])
	f[op.index('f_1i_2f_*')] = f_1(f[op.index('i_2f_*')])
	f[op.index('f_2i_2f_*')] = f_2(f[op.index('i_2f_*')])
	f[op.index('k_1i_*f_*')] = k_1(f[op.index('i_1f_*')])
	f[op.index('k_2i_*f_*')] = k_2(f[op.index('i_1f_*')])
	"""f[op.index('0')] was already initialized to the empty set"""
	f[op.index('k_2f_1i_1f_*')] = k_2(f[op.index('f_1i_1f_*')])
	f[op.index('k_2f_1i_2f_*')] = k_2(f[op.index('f_1i_2f_*')])
	f[op.index('f_1k_2i_*f_*')] = f_1(f[op.index('k_2i_*f_*')])
	f[op.index('f_1i_2k_*i_*')] = f_1(f[op.index('i_2k_*i_*')])
	f[op.index('k_2f_1k_1i_*')] = k_2(f[op.index('f_1k_1i_*')])
	f[op.index('k_2f_1k_2i_*')] = k_2(f[op.index('f_1k_2i_*')])
	f[op.index('k_2f_1k_2f_1')] = k_2(f[op.index('f_1k_2f_1')])
	f[op.index('f_1k_2i_*k_*')] = f_1(f[op.index('k_2i_*k_*')])
	f[op.index('k_2f_1i_1k_*')] = k_2(f[op.index('f_1i_1k_*')])
	f[op.index('k_2f_1i_2k_*')] = k_2(f[op.index('f_1i_2k_*')])
	f[op.index('k_2f_1k_2i_*f_*')] = k_2(f[op.index('f_1k_2i_*f_*')])
	f[op.index('k_2f_1i_2k_*i_*')] = k_2(f[op.index('f_1i_2k_*i_*')])
	f[op.index('k_2f_1k_2i_*k_*')] = k_2(f[op.index('f_1k_2i_*k_*')])

	return f

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

# apply the 60 operators in KF_2^0 to the seed set p
	fam = genfam(p)

# attempt to eliminate each live inequality in adj
	for j in range(60):
		for k in range(60):
			if not adj[j][k]:
				if not contained_in(fam[j],fam[k]):
					adj[j][k] = 1

# if every inequality got eliminated then every entry in adj is now 1
success = 1
for j in range(60):
	for k in range(60):
		if not adj[j][k]:
			success = 0
			break
	if not success:
		break
if success:
	print("success")
else:
	print("fail")
