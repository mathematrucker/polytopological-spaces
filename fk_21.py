# Python script to verify poset diagram for FK_{2,1} on p. 24 in Banakh, et al.
# Mark Bowron, Oct 2019

# By Proposition 9.3, all possible reductions in the free semigroup FS_{L_{2,1}}
# on L_{2,1} = {a,b,1,x} appear in the following list.

reduction_list = {
'axbx': 'ax',
'xbxa': 'xa',
'axax': 'ax',
'xaxa': 'xa',
'bxbx': 'bx',
'xbxb': 'xb',
'aa': 'a',
'ab': 'a',
'ba': 'a',
'bb': 'b',
'xx': 'x',
'a1': 'a',
'1a': 'a',
'b1': 'b',
'1b': 'b',
'x1': 'x',
'1x': 'x'
}

# Two passes of the for loop below are required to fully reduce certain operators.

def reduce_op(op, reduction_list):
    for i, j in reduction_list.items():
        op = op.replace(i, j)
    for i, j in reduction_list.items():
        op = op.replace(i, j)
    return op

def right_a(op):
	op = ''.join([op, 'a'])
	op = reduce_op(op, reduction_list)
	return op

def left_a(op):
	op = ''.join(['a', op])
	op = reduce_op(op, reduction_list)
	return op

def right_b(op):
	op = ''.join([op, 'b'])
	op = reduce_op(op, reduction_list)
	return op

def left_b(op):
	op = ''.join(['b', op])
	op = reduce_op(op, reduction_list)
	return op

def right_x(op):
	op = ''.join([op, 'x'])
	op = reduce_op(op, reduction_list)
	return op

def left_x(op):
	op = ''.join(['x', op])
	op = reduce_op(op, reduction_list)
	return op

# The function gen_new() generates a list of distinct inequalities from a static list by
# multiplying each inequality in the static list on the left and right (separately)
# by a, b, and x.

def gen_new(inequalities):
	buildlist = inequalities.copy()
	for i in inequalities:
		if right_a(i[0]) != right_a(i[1]):
			buildlist.add((right_a(i[0]),right_a(i[1])))
		if left_a(i[0]) != left_a(i[1]):
			buildlist.add((left_a(i[0]),left_a(i[1])))
		if right_b(i[0]) != right_b(i[1]):
			buildlist.add((right_b(i[0]),right_b(i[1])))
		if left_b(i[0]) != left_b(i[1]):
			buildlist.add((left_b(i[0]),left_b(i[1])))
		if right_x(i[0]) != right_x(i[1]):
			buildlist.add((right_x(i[0]),right_x(i[1])))
		if left_x(i[0]) != left_x(i[1]):
			buildlist.add((left_x(i[0]),left_x(i[1])))
	return buildlist

# Every compatible partial preorder on the free semigroup FS_{L_{2,1}}
# is closed under right- and left-multiplication by a, b, and x.
# Thus, starting with the linear order on L_{2,1} and repeatedly performing
# such multiplications until no new inequalities are produced, we get an
# order relation whose transitive closure is the partial order on FK_{2,1},
# i.e., one that contains the full poset diagram of FK_{2,1}.
# The code below performs the task described above and therefore prints
# out an order relation that includes the full poset diagram of FK_{2,1}.

inequalities = {('a','b'), ('b','1'), ('1','x')}

newlist = gen_new(inequalities)

while newlist != inequalities:
	inequalities = newlist.copy()
	newlist = gen_new(inequalities)

print(*sorted(inequalities), sep = "\n")
