from constraint import *

# RESTRICCIONES
def notEqual(a, b):
	if a != b:
		return True

def equal(a, b):
	if a == b:
		return True

def greater(a, b):
    if a > b:
	    return True

def lower(a, b):
    if a < b:
	    return True

def notMA(a, b):
	if a == 1 and b > 3:
		return True
	elif a == 4 and b < 4 or b > 6:
		return True
	elif a == 7 and b < 7 or b > 9:
		return True
	elif a == 10 and b < 10:
		return True

# MAIN
# -----------------------------------------------------------------------------
if __name__ == '__main__':

	problem = Problem()	

	asignaturas = ['CN1','CN2','LC1','LC2','IN1','IN2','EF','MA1','MA2','CS1','CS2']
	Profesores  = ['LU1','LU2','AN1','AN2','JU1','JU2']

	# VARIABLES
	# -------------------------------------------------------------------------	
	# Asignaturas
	# Para todas las materias se deben impartir 2 horas semanales
	# La duración de cada una de las clases es de 1 hora
	problem.addVariables(['CN1','CN2','LC1','LC2','IN1','IN2','EF'], range(1,12))
	problem.addVariables(['MA1','MA2'], [1, 4, 7, 10])
	problem.addVariables(['CS1','CS2'], [3, 6, 9, 11])

	# Profesores
	# Cada profesor debe impartir 2 materias
	problem.addVariables(['LU1','LU2','AN1','AN2','JU1','JU2'], range(1,12))	
	# RESTRICCIONES
	# -------------------------------------------------------------------------	
	# Sólo se puede impartir una única materia por hora
	for i in asignaturas:
		for j in asignaturas:
			if i == j: continue
			else: problem.addConstraint(notEqual, (i, j))	
	# La materia de Matemáticas no puede impartirse el mismo día que Ciencias de la Naturaleza e Inglés	
	# Cada profesor debe impartir 2 materias, que son diferentes a las de sus compañeros	
	# Lucía solo se encargará de Ciencias Sociales, si Andrea se encarga de Educación Física	
	# Juan no quiere encargarse de Ciencias de la Naturaleza o de Ciencias Sociales, si algunas de sus horas se imparte a primera hora los lunes y jueves	
	# SOLUCIÓN
	print(problem.getSolution())