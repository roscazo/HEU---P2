import java.util.*;
import java.io.*;

public class A_star 
{
	private Mapa map;
	private String heuristic_func;
	private String output_path;
	private String statistics_path;
	
	/**
	 * Constructor de la clase A_star. Esta funciona como la clase agente de busqueda.
	 * 
	 * @param map El mapa que contiene los datos del problema
	 * @param heuristic_func La funcion especificada como argumento del main
	 */
	public A_star(Mapa map, String heuristic_func)
	{
		// Inicializa las variables 
		this.map = map;
		this.heuristic_func = heuristic_func;
		this.output_path = map.getPath()+".output";
		this.statistics_path = map.getPath()+".statistics";
		// Crea el estado inicial con los valores iniciales del problema
		State initial_state = new State(map.getInitial_pos(), map.getChildren(), map.getCapacity(), 0);
		initial_state.setH(heuristica(heuristic_func, initial_state));
		// Comienza el proceso de busqueda
		boolean exito = search(initial_state);
		// Mensaje en pantalla al finalizar la busqueda
		if(exito) 
			System.out.println("Solucion encontrada"); 
		else 
			System.out.println("Solucion NO encontrada");
	}
	
	/**
	 * Se dedica a la busqueda de la solucion aplicando A*
	 * 
	 * @param initial_state El estado inicial
	 * @return Devuelva true en caso de encontrar una solucion, false en caso contrario
	 */
	public boolean search(State initial_state)
	{
		// Comienza a medir el tiempo de ejecucion
		long first_time = System.currentTimeMillis();
		// Crear root node
		Node root = new Node(null, initial_state);
		// Inicializa OPEN list
		OPEN_list open_list = new OPEN_list(root);
		// Inicializa CLOSED list
		CLOSED_list closed_list = new CLOSED_list();
		// Control exito
		boolean exito = false;
		// Lleva la cuenta del numero de expansiones
		int num_expansiones = 0;
		//Nodo auxiliar para expandir
		Node to_expand;
		
		// Loop de busqueda
		do
		{
			// Coge el primer elemento en la lista abierta
			to_expand = open_list.open_nodes.remove(0);
			// Inserta el nodo en CLOSED
			closed_list.closed_nodes.add(to_expand);
			// Comprueba si el nodo es el goal
			if(is_final(to_expand)) exito = true;
			// Si no exito, expande los sucesores 
			else
			{
				// Expandir nodo
				num_expansiones++;
				// Guardar resultados en un vector auxiliar
				Vector<Node> sucesores = sucesores(to_expand);
				// Comprueba que el nodo no esta vacio, no esta en CLOSED ni en OPEN
				for(Node iterator : sucesores)
				{
					if(iterator != null)
					{
						if(!closed_list.contains(iterator))
						{
							if(!open_list.contains(iterator))
								open_list.ordered_insert(iterator);		
						}
					}
				}
			}
			// Checkea si la lista open esta vacia
			if(open_list.open_nodes.isEmpty()) continue;
		// El loop continua hasta que se encuentra una solucion
		} while(!exito);
		// Toma el tiempo final de ejecucion
		long final_time = System.currentTimeMillis();
		// En caso de exito se crean los archivos de salida y de estadisticas
		if(exito)
		{
			print_output(to_expand);
			print_statistics(first_time, final_time, num_expansiones, to_expand);
		}
		
		return exito;
	}
	
	/**
	 * Funcion manager de la expansion de los nodos
	 * 
	 * @param padre Nodo a expandir
	 * @return Devuelve un vector con todos los sucesores
	 */
	public Vector<Node> sucesores(Node padre)
	{
		Vector<Node> buffer = new Vector<Node>();
		
		buffer.addAll(mover(padre));
		buffer.add(subir(padre));
		buffer.add(bajar(padre));
		
		return buffer;
	}
	
	/**
	 * Implementa el operador MOVER
	 * 
	 * @param padre El nodo a expandir
	 * @return Devuelve un vector con los sucesores 
	 */
	public Vector<Node> mover(Node padre)
	{
		// Varaibles y vectores auxiliares
		Vector<Node> buffer = new Vector<Node>();
		State aux_state = padre.getState();
		// Counter para guardar el numero de la parada sucesora
		int counter = 0;
		// Toma solo el numero de la parada
		int pos = Integer.parseInt(aux_state.getPosition().substring(1,2));
		// Recorre la fila de la matriz correspondiente a la parada de partida
		for(int it : map.getConexiones().get(pos-1))
		{
			++counter;
			// Ignora los valores == -1, donde no hay camino
			if(it != Integer.MAX_VALUE)
			{				
				// Crea el nombre de la parada
				String parada = "P" + Integer.toString(counter);
				// Suma el coste del movimiento con el coste previo
				int cost = it + aux_state.getG();
				// Crea las nuevas variables
				State new_state = new State(parada, aux_state.getChildren(), aux_state.getFree_seats(), cost);
				new_state.setH(heuristica(heuristic_func, new_state));
				Node new_node = new Node(padre, new_state);
				// A�ade el nuevo nodo al vector auxiliar
				buffer.add(new_node);
			}
		}
		return buffer;
	}
	
	/**
	 * Implementa el operador SUBIR
	 * 
	 * @param padre El nodo a expandir
	 * @return Devuelve el nuevo nodo, null en caso de que no haya "subido" ningun alumno
	 */
	public Node subir(Node padre)
	{
		// Variables auxiliares
		State aux_state = padre.getState();
		Node new_node;
		boolean control = false;
		// Datos para output
		String trace = "(S: ";
		String colegio = "";
		int i = 0;
		// Creamos un nuevo vector children para evitar referencias al vector del padre
		Vector<Child> aux_children = new Vector<Child>();
		for(Child it : aux_state.getChildren())
		{
			Child aux_child = new Child(it.getId(), it.getColegio(), it.getEstado());
			aux_children.add(aux_child);
		}
		// Guardamos el numero de asientos libres en el nodo padre
		int free_seats = aux_state.getFree_seats();
		// Loop que recorre el vector children
		for(Child it : aux_children)
		{
			// Si encuentra algun alumno esperando en la parada y hay sitio en el autob�s
			if( (it.getEstado() == 0) && (it.getId().equals(aux_state.getPosition())) && (free_seats > 0) )
			{
				// Guarda datos del colegio para crear el output
				if(colegio.equals("")) colegio = it.getColegio();
				
				// Cambia el estado de los alumnos a "en ruta"
				it.setEstado(1);
				// Resta un asiento libre del bus
				free_seats -= 1;
				// La variable de control se activa para confirmar que al menos un alumno ha cambiado de estado
				control = true;
				
				// Datos para output
				if(!colegio.equals(it.getColegio()))
				{
					trace += i + " " + colegio + ", ";
					i = 1;
					colegio = it.getColegio();
				}
				else 
					++i;
			}
		}
		// Datos para output
		trace += i + " " + colegio + ")";
		// En caso de que algun alumno haya "subido" al bus
		if(control)
		{
			// Se crea los nuevos estado y nodo a devolver
			State new_state = new State(aux_state.getPosition(), aux_children, free_seats, aux_state.getG());
			// Calculo heuristica
			new_state.setH(heuristica(heuristic_func, new_state));
			new_node = new Node(padre.getParent(), new_state);
			
			new_node.setTrace(trace);
		}
		// En caso contrario, se devuelve null
		else 
			new_node = null;

		return new_node;
	}
	
	/**
	 * Implementa el operador BAJAR
	 * 
	 * @param padre El nodo a expandir
	 * @return Devuelve el nuevo nodo, null en caso de que no haya "bajado" ningun alumno
	 */
	public Node bajar(Node padre)
	{
		// Varaibles auxiliares
		State aux_state = padre.getState();
		Node new_node;
		boolean control = false;
		// Datos para output
		String trace = "(B: ";
		String colegio = "";
		int i = 0;
		// Creamos un nuevo vector children para evitar referencias al vector del padre
		Vector<Child> aux_children = new Vector<Child>();
		for(Child it : aux_state.getChildren())
		{
			Child aux_child = new Child(it.getId(), it.getColegio(), it.getEstado());
			aux_children.add(aux_child);
		}
		// Guardamos el numero de asientos libres en el nodo padre
		int free_seats = aux_state.getFree_seats();
		// Loop que recorre el vector children
		for(Child it : aux_children)
		{
			// En caso de que el alumno esta "en ruta" y que su colegio esta en la parada actual
			if( (it.getEstado() == 1) && (it.getColegio().equals(check_colegio(aux_state.getPosition()))) )
			{
				// Cambia el estado a "en destino"
				it.setEstado(2);
				// Suma un sitio libre al bus
				free_seats += 1;
				// Activa el signo de control que indica que al menos un alumno ha "bajado"
				control = true;
				
				// Datos para output
				++i;
				colegio = check_colegio(aux_state.getPosition());
			}
		}
		// Datos para output
		trace += i + " " + colegio + ")";
		
		// En caso de que algun alumno haya "bajado"
		if(control)
		{
			// Se crea los nuevos estado y nodo a devolver
			State new_state = new State(aux_state.getPosition(), aux_children, free_seats, aux_state.getG());
			new_state.setH(heuristica(heuristic_func, new_state));
			new_node = new Node(padre.getParent(), new_state);
			new_node.setTrace(trace);
		}
		// En caso contrario se devuelve null
		else new_node = null;

		return new_node;
	}
	
	/**
	 * Decide cual es la función heurística a implementar según se haya decidido al correr el programa
	 * 
	 * @param h String con la heuristica elegida
	 * @param s Estado a evaluar
	 * @return
	 */
	public int heuristica(String h, State s)
	{
		switch(h)
		{
		// Dijkstra
		case "default":
			return 0;
		// Heurística: colegio mas lejano
		case "heu_1":
			if(todos_entregados(s))
				return back_home(s);
			else
				return colegio_lejos(s);
			
		default:
			return 0;
		}
	}
	
	/**
	 * Comprueba que si el nodo de entrada es el goal
	 * 
	 * @param node Nodo a comprobar
	 * @return Devuelve true en caso de que lo sea, false en caso de que no
	 */
	public boolean is_final(Node node)
	{
		// Variables auxiliares
		State aux = node.getState();
		boolean check = false;
		
		// Si la posición es la misma que la posici�n inicial
		if(aux.getPosition().equals(map.getInitial_pos()))
		{
			// Loop del vector children
			for(Child it : aux.getChildren())
			{
				// Comprueba si todos los alumnos se encuentran en sus colegios
				if(it.getEstado() == 2)
					check = true;
				else
					return false;
			}
		}
		// En caso contrario devuelve false
		else 
			return false;
		
		return check;
	}
	
	/**
	 * Funcion auxiliar que comprueba si hay un colegio en la parada de entrada
	 * 
	 * @param p String con la parada de entrada
	 * @return Devuelve el nombre del colegio en caso de que exista, null en caso contrario
	 */
	public String check_colegio(String p)
	{
		// Recorre el vector de colegios
		for(Colegio it : map.getColegios())
		{
			if(it.getId().equals(p))
				return it.getColegio();
		}
		return null;
	}
	
	/**
	 * ---- Funcion auxiliar para la heuristica ----
	 * Comprueba si todos los alumnos han sido entregados en sus colegios
	 * 
	 * @param s Estado al que calcular la heuristica
	 * @return Devuelve el valor del camino mas corto
	 */
	public boolean todos_entregados(State s)
	{
		boolean check = false;
		
		for(Child it : s.getChildren())
		{
			if(it.getEstado() == 2)
				check = true;
			else
				return false;
		}
		return check;
	}
	
	/**
	 * ---- Funcion auxiliar para la heuristica ----
	 * Busca el camino mas corto hacia el nodo final
	 * 
	 * @param s Estado al que calcular la heuristica
	 * @return Devuelve el valor del camino mas corto
	 */
	public int back_home(State s)
	{
		String p = s.getPosition();
		int value = 0;
		
		int pos1 = Integer.parseInt(p.substring(1,2)) - 1;
		int pos2 = Integer.parseInt(map.getInitial_pos().substring(1,2)) - 1 ;
			
		value = map.getFW()[pos1][pos2];
		
		return value;
	}
	
	/**
	 * ---- Funcion auxiliar para la heuristica ----
	 * Busca el camino mas corto hacia el colegio mas lejano
	 * 
	 * @param s Estado al que calcular la heuristica
	 * @return Devuelve el valor del camino mas corto
	 */
	public int colegio_lejos(State s)
	{
		String p = s.getPosition();
		int value = 0;
		int pos1 = Integer.parseInt(p.substring(1,2)) - 1;
		
		for(Colegio it : map.getColegios())
		{
			int pos2 = Integer.parseInt(it.getId().substring(1,2)) - 1 ;
			
			if(map.getFW()[pos1][pos2] > value)
				value = map.getFW()[pos1][pos2];
		}
		return value;
	}
	

	
	/**
	 * Funcion auxiliar para imprimir el fichero output
	 * 
	 * @param last_node Recibe el ultimo nodo en CLOSED
	 */
	public void print_output(Node last_node)
	{
		Vector<String> path = new Vector<>();
		path = last_node.getPath();
		
		String output = map.print_map() + "\n" + path.get(0);
		
		for(int i = 1; i < path.size(); i++)
			output += " -> " + path.get(i);
		
		File output_file = new File(output_path);
		BufferedWriter out;
		try 
		{
			out = new BufferedWriter(new FileWriter(output_file));
			out.write(output);
			out.close();
		} catch (IOException e) { e.printStackTrace(); }
	}
	
	/**
	 * Funcion auxiliar para imprimir las estadisticas de la busqueda
	 * 
	 * @param intial_time El tiempo inicial
	 * @param final_time El tiempo final
	 * @param num_expansiones El numero total de nodos expandidos
	 * @param final_node El ultimo nodo expandido
	 */
	public void print_statistics(long intial_time, long final_time, int num_expansiones, Node final_node)
	{
		String statistics = "----- ESTADISTICAS -----\n";
		long execution_time = final_time - intial_time;
		statistics += "Tiempo total: "+execution_time+"\n";
		statistics += "Coste total: "+final_node.getState().getG()+"\n";
		statistics += "Paradas visitadas: "+final_node.getDepth()+"\n";
		statistics += "Nodos expandidos: "+num_expansiones;
		
		File statistics_file = new File(statistics_path);
    	BufferedWriter sta;
		try {
			sta = new BufferedWriter(new FileWriter(statistics_file));
			sta.write(statistics);
			sta.close();
		} catch (IOException e) { e.printStackTrace(); }
	}

}
