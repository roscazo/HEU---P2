from constraint import *

problem = Problem()

# VARIABLES
# Días
problem.addVariables(['L', 'M', 'X'], [1, 2, 3, 4, 5, 6, 7, 8, 9])
problem.addVariable('J', [10, 11])

# Asignaturas
problem.addVariables(['NA12', 'LC12', 'IN12'], [1, 2])
problem.addVariables(['NA13', 'LC13', 'IN13'], [1, 3])
problem.addVariables(['NA14', 'LC14', 'IN14'], [1, 4])
problem.addVariables(['NA15', 'LC15', 'IN15'], [1, 5])
problem.addVariables(['NA16', 'LC16', 'IN16'], [1, 6])
problem.addVariables(['NA17', 'LC17', 'IN17'], [1, 7])
problem.addVariables(['NA18', 'LC18', 'IN18'], [1, 8])
problem.addVariables(['NA19', 'LC19', 'IN19'], [1, 9])
problem.addVariables(['NA10', 'LC10', 'IN10'], [1, 10])
problem.addVariables(['NA11', 'LC11', 'IN11'], [1, 11])
problem.addVariables(['NA23', 'LC23', 'IN23'], [2, 3])
problem.addVariables(['NA24', 'LC24', 'IN24'], [2, 4])
problem.addVariables(['NA25', 'LC25', 'IN25'], [2, 5])
problem.addVariables(['NA26', 'LC26', 'IN26'], [2, 6])
problem.addVariables(['NA27', 'LC27', 'IN27'], [2, 7])
problem.addVariables(['NA28', 'LC28', 'IN28'], [2, 8])
problem.addVariables(['NA29', 'LC29', 'IN29'], [2, 9])
problem.addVariables(['NA20', 'LC20', 'IN20'], [2, 10])
problem.addVariables(['NA21', 'LC21', 'IN21'], [2, 11])
problem.addVariables(['NA34', 'LC34', 'IN34'], [3, 4])
problem.addVariables(['NA35', 'LC35', 'IN35'], [3, 5])
problem.addVariables(['NA36', 'LC36', 'IN36'], [3, 6])
problem.addVariables(['NA37', 'LC37', 'IN37'], [3, 7])
problem.addVariables(['NA38', 'LC38', 'IN38'], [3, 8])
problem.addVariables(['NA39', 'LC39', 'IN39'], [3, 9])
problem.addVariables(['NA30', 'LC30', 'IN30'], [3, 10])
problem.addVariables(['NA31', 'LC31', 'IN31'], [3, 11])
problem.addVariables(['NA45', 'LC45', 'IN45'], [4, 5])
problem.addVariables(['NA46', 'LC46', 'IN46'], [4, 6])
problem.addVariables(['NA47', 'LC47', 'IN47'], [4, 7])
problem.addVariables(['NA48', 'LC48', 'IN48'], [4, 8])
problem.addVariables(['NA49', 'LC49', 'IN49'], [4, 9])
problem.addVariables(['NA40', 'LC40', 'IN40'], [4, 10])
problem.addVariables(['NA41', 'LC41', 'IN41'], [4, 11])
problem.addVariables(['NA56', 'LC56', 'IN56'], [5, 6])
problem.addVariables(['NA57', 'LC57', 'IN57'], [5, 7])
problem.addVariables(['NA58', 'LC58', 'IN58'], [5, 8])
problem.addVariables(['NA59', 'LC59', 'IN59'], [5, 9])
problem.addVariables(['NA50', 'LC50', 'IN50'], [5, 10])
problem.addVariables(['NA51', 'LC51', 'IN51'], [5, 11])
problem.addVariables(['NA67', 'LC67', 'IN67'], [6, 7])
problem.addVariables(['NA68', 'LC68', 'IN68'], [6, 8])
problem.addVariables(['NA69', 'LC69', 'IN69'], [6, 9])
problem.addVariables(['NA60', 'LC60', 'IN60'], [6, 10])
problem.addVariables(['NA61', 'LC61', 'IN61'], [6, 11])
problem.addVariables(['NA78', 'LC78', 'IN78'], [7, 8])
problem.addVariables(['NA79', 'LC79', 'IN79'], [7, 9])
problem.addVariables(['NA70', 'LC70', 'IN70'], [7, 10])
problem.addVariables(['NA71', 'LC71', 'IN71'], [7, 11])
problem.addVariables(['NA89', 'LC89', 'IN89'], [8, 9])
problem.addVariables(['NA80', 'LC80', 'IN80'], [8, 10])
problem.addVariables(['NA81', 'LC81', 'IN81'], [8, 11])
problem.addVariables(['NA90', 'LC90', 'IN90'], [9, 10])
problem.addVariables(['NA91', 'LC91', 'IN91'], [9, 11])
problem.addVariables(['NA01', 'LC01', 'IN01'], [10, 11])
problem.addVariable(['MA14'], [1, 4])
problem.addVariable(['MA17'], [1, 7])
problem.addVariable(['MA10'], [1, 10])
problem.addVariable(['MA47'], [4, 7])
problem.addVariable(['MA40'], [4, 10])
problem.addVariable(['MA70'], [7, 10])
problem.addVariable(['CS36'], [3, 6])
problem.addVariable(['CS39'], [3, 9])
problem.addVariable(['CS31'], [3, 11])
problem.addVariable(['CS69'], [6, 9])
problem.addVariable(['CS61'], [6, 11])
problem.addVariable(['CS91'], [9, 11])
problem.addVariable(['ED'], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11])

# Profesores
problem.addVariables(['Lu', 'An', 'Ju'], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11])

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

#def consecutive(a, b):
#    if 

# La duración de cada una de las clases es de 1 hora, en la que sólo se puede impartir una única materia


# Para todas las materias se deben impartir 2 horas semanales, excepto para Educación Física que sólo tiene asignada 1 hora semanal


# Las 2 horas dedicadas a Ciencias de la Naturaleza que sí se deben impartir de forma consecutiva el mismo día


# La materia de Matemáticas no puede impartirse el mismo día que Ciencias de la Naturaleza e Inglés


# Cada profesor debe impartir 2 materias, que son diferentes a las de sus compañeros


# Lucía solo se encargará de Ciencias Sociales, si Andrea se encarga de Educación Física


# Juan no quiere encargarse de Ciencias de la Naturaleza o de Ciencias Sociales, si algunas de sus horas se imparte a primera hora los lunes y jueves

# SOLUCIÓN
print(problem.getSolutions())