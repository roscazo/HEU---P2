from constraint import *

problem = Problem()

asignaturas = ["CN", "CS", "LC", "MA", "IN", "ED"]
profesores = ['LU', 'AN', 'JU']
# schedule = range(1,12)

# schedule = [(asig, prof) for asig in asignaturas for prof in profesores]
# horas = range(1, 12)
# problem.addVariables(horas, schedule)

# problem.addVariables(['CN', 'IN', 'LC', 'ED'], range(1,12))
# problem.addVariables(['MA'], [1, 4, 7, 10])
# problem.addVariables(['CS'], [3, 6, 9, 11])
# problem.addVariables(['LU', 'AN', 'JU'], range(1,12))

problem.addVariable('CNJU', [2,3,4,5,6,8,9,11])
problem.addVariables(['CNLU', 'CNAN', 'LCLU', 'LCAN', 'LCJU', 'INLU', 'INAN', 'INJU', 'EDLU', 'EDAN', 'EDJU'], range(1,12))
problem.addVariables(['CSLU', 'CSAN', 'CSJU'], [3,6,9,11])
problem.addVariables(['MALU', 'MAAN', 'MAJU'], [1,4,7,10])

def notMA(a, b):
	if a == 1 and b > 3:
		return True
	elif a == 4 and b < 4 or b > 6:
		return True
	elif a == 7 and b < 7 or b > 9:
		return True
	elif a == 10 and b < 10:
		return True

def check(a,b,c):
    if a != b and a != c and b != c:
        return True

# def juan(a,b):
#     if a == b and (b != 1 or b != 10):
#         return True

# def LuAn(a,b,c,d):
#     if a == b and c == d:
#         return True

problem.addConstraint(notMA, ('MA', 'CN'))
problem.addConstraint(notMA, ('MA', 'IN'))

# problem.addConstraint(juan, ('JU', 'CN'))
# problem.addConstraint(juan, ('JU', 'CS'))

# problem.addConstraint(LuAn, ('LU', 'CS', 'AN', 'ED'))

problem.addConstraint(check, ('LU', 'JU', 'AN'))
problem.addConstraint(AllDifferentConstraint())

print(problem.getSolution())


