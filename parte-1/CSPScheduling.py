import constraint

# RESTRICCIONES
# -----------------------------------------------
def notEqual(a, b):
	if a != b:
		return True

def consecutive(a, b):
	if b == a + 1:
		return True

def onlyMA(a, b):
	if a == 1 and b > 3:
		return True
	if a == 4 and (b < 4 or b > 6):
		return True
	if a == 7 and (b < 7 or b > 9):
		return True
	if a == 10 and b < 10:
		return True

def csyef(a, b):
	if a == 'CS' and b != 'EF':
		return False
	else: 
		return True

def lateJU(a, b):
	if a == 'CN' and (b == 1 or b == 10):
		return False
	if a == 'CS' and (b == 1 or b == 10):
		return False
	else:
		return True

# MAIN
# -----------------------------------------------------------------------------
if __name__ == '__main__':

	problem = constraint.Problem ()	

	# VARIABLES Y DOMINIOS:
	# -------------------------------------------------------------------------	

	# Asignaturas:
	# -------------------------------------------------------------------------
	asignaturas = ['CN1','CN2','LC1','LC2','IN1','IN2','EF','MA1','MA2','CS1','CS2']
	# Para todas las materias se deben impartir 2 horas semanales, excepto Educación Física
	# La duración de cada una de las clases es de 1 hora
	problem.addVariables(['CN1','CN2','LC1','LC2','IN1','IN2','EF'], range(1,12))
	# La materia de Matemáticas debe impartirse en las primeras horas
	problem.addVariables(['MA1','MA2'], [1, 4, 7, 10])
	# La materia de Ciencias Sociales debe impartirse en las últimas
	problem.addVariables(['CS1','CS2'], [3, 6, 9, 11])
	
	# Profesores:
	# -------------------------------------------------------------------------
	profesores = ['LU1','LU2','AN1','AN2','JU1','JU2']
	# Cada profesor debe impartir 2 materias
	problem.addVariables(['LU1','LU2','AN1','AN2','JU1','JU2'], ['CN','CS','MA','IN','EF','LC'])

	# RESTRICCIONES
	# -------------------------------------------------------------------------	
	# Sólo se puede impartir una única materia por hora
	for i in asignaturas:
		for j in asignaturas:
			if i == j: continue
			else: problem.addConstraint(notEqual, (i, j))	

	# Las dos horas de Ciencias Naturales deben impartirse de forma consecutiva
	problem.addConstraint(consecutive, ('CN1', 'CN2'))

	# La materia de Matemáticas no puede impartirse el mismo día que Ciencias de la Naturaleza e Inglés	
	problem.addConstraint(onlyMA, ('MA1', 'CN1'))
	problem.addConstraint(onlyMA, ('MA1', 'CN2'))
	problem.addConstraint(onlyMA, ('MA1', 'IN1'))
	problem.addConstraint(onlyMA, ('MA1', 'IN2'))
	problem.addConstraint(onlyMA, ('MA2', 'CN1'))
	problem.addConstraint(onlyMA, ('MA2', 'CN2'))
	problem.addConstraint(onlyMA, ('MA2', 'IN1'))
	problem.addConstraint(onlyMA, ('MA2', 'IN2'))

	# Cada profesor debe impartir 2 materias, que son diferentes a las de sus compañeros
	for i in profesores:
		for j in profesores:
			if i == j: continue
			else: problem.addConstraint(notEqual, (i, j))	

	# Lucía solo se encargará de Ciencias Sociales, si Andrea se encarga de Educación Física
	problem.addConstraint(csyef, ('LU1', 'AN1'))
	problem.addConstraint(csyef, ('LU1', 'AN2'))
	problem.addConstraint(csyef, ('LU2', 'AN1'))
	problem.addConstraint(csyef, ('LU2', 'AN2'))

	# Juan no quiere encargarse de Ciencias de la Naturaleza o de Ciencias Sociales, si algunas de sus horas se imparte 
	# a primera hora los lunes y jueves	
	problem.addConstraint( lateJU, ('JU1','CN1') )
	problem.addConstraint( lateJU, ('JU1','CN2') )
	problem.addConstraint( lateJU, ('JU1','CS1') )
	problem.addConstraint( lateJU, ('JU1','CS2') )
	problem.addConstraint( lateJU, ('JU2','CN1') )
	problem.addConstraint( lateJU, ('JU2','CN2') )
	problem.addConstraint( lateJU, ('JU2','CS1') )
	problem.addConstraint( lateJU, ('JU2','CS2') )

	# SOLUCIÓN
	# -------------------------------------------------------------------------
	# print(problem.getSolution())

	solutions = problem.getSolution ()
    
	print("#{0} solutions have been found: ".format (len (solutions)))

# 	print("""
# Ciencias Naturales: {0} y {1}
# Ciencias Sociales:  {2} y {3}
# Matematicas: 		{4} y {5}
# Ingles:  			{6} y {7}
# Lengua castellana:  {8} y {9}
# Educacion fisica:   {10}""" .format (solutions['CN1'], solutions['CN2'], solutions['CS1'], solutions['CS2'], 
# 			 						 solutions['MA1'], solutions['MA2'], solutions['IN1'], solutions['IN2'],
# 									 solutions['LC1'], solutions['LC2'], solutions['EF']))

# 	print("""
# Andrea: {0} y {1}
# Lucia:  {2} y {3}
# Juan: 	{4} y {5}
# """ .format (solutions['AN1'], solutions['AN2'], solutions['LU1'], solutions['LU2'], 
# 			 						 solutions['JU1'], solutions['JU2']))
