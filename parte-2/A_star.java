import java.util.*;
import java.io.*;

public class A_star 
{
	private Mapa map;
	private String heuristic_func;
	private String output_path;
	private String statistics_path;
	
	/**
	 * Constructor
	 * @param map
	 */
	public A_star(Mapa map, String heuristic_func)
	{
		this.map = map;
		this.heuristic_func = heuristic_func;
		this.output_path = map.getPath()+".output";
		this.statistics_path = map.getPath()+".statistics";
		
		State initial_state = new State(map.getInitial_pos(), map.getChildren(), map.getCapacity(), 0, heuristic_func);
		boolean exito = search(initial_state);
		
		if(exito) 
			System.out.println("SOLUCI�N ENCONTRADA"); 
		else 
			System.out.println("SOLUCI�N NO ENCONTRADA");
	}
	
	/**
	 * 
	 * @param initial_state
	 * @return
	 */
	public boolean search(State initial_state)
	{
		long first_time = System.currentTimeMillis();
		// Crear root node
		Node root = new Node(null, initial_state);
		// Inicializa OPEN list
		OPEN_list open_list = new OPEN_list(root);
		// Inicializa CLOSED list
		CLOSED_list closed_list = new CLOSED_list();
		// Control exito
		boolean exito = false;
		// Loop de b�squeda
		int num_expansiones = 0;
		
		int k = 0;
		Node to_expand;
		do
		{
			System.out.println(closed_list);
			// Coge el primer elemento en la lista abierta
			to_expand = open_list.open_nodes.remove(0);
			// Inserta el nodo en CLOSED
			closed_list.closed_nodes.add(to_expand);
			
			if(is_final(to_expand)) exito = true;
			
			else
			{
				// Expandir nodo
				num_expansiones++;
				// Guardar resultados
				Vector<Node> sucesores = sucesores(to_expand);
				
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
				sucesores.clear();
			}
		++k;
		} while(!open_list.open_nodes.isEmpty() || !exito);
		
		long final_time = System.currentTimeMillis();
		
		if(exito)
		{
			print_output(to_expand);
			print_statistics(first_time, final_time, num_expansiones, to_expand);
		}
		
		return exito;
	}
	
	/**
	 * 
	 * @param padre
	 * @return
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
	 * 
	 * @param padre
	 * @return
	 */
	public Vector<Node> mover(Node padre)
	{
		Vector<Node> buffer = new Vector<Node>();
		State aux_state = padre.getState();
		int counter = 0;
		
		int pos = Integer.parseInt(aux_state.getPosition().substring(1,2));

		for(int it : map.getConexiones().get(pos-1))
		{
			++counter;
			
			if(it != -1)
			{
				
				String parada = "P" + Integer.toString(counter);
				int cost = it + aux_state.getG();
				
				
				State new_state = new State(parada, aux_state.getChildren(), aux_state.getFree_seats(), cost, heuristic_func);
				Node new_node = new Node(padre, new_state);
				//System.out.println(new_node);
				buffer.add(new_node);
			}
		}
		return buffer;
	}
	
	/**
	 * 
	 * @param padre
	 * @return
	 */
	public Node subir(Node padre)
	{
		State aux_state = padre.getState();
		Node new_node;
		boolean control = false;
		
		Vector<Child> aux_children = new Vector<Child>();
		for(Child it : aux_state.getChildren())
		{
			Child aux_child = new Child(it.getId(), it.getColegio(), it.getEstado());
			aux_children.add(aux_child);
		}
		
		int free_seats = aux_state.getFree_seats();
		
		for(Child it : aux_children)
		{
			if( (it.getEstado() == 0) && (it.getId().equals(aux_state.getPosition())) && (free_seats > 0) )
			{
				it.setEstado(1);
				free_seats -= 1;
				control = true;
			}
		}
		
		if(control)
		{
			State new_state = new State(aux_state.getPosition(), aux_children, free_seats, aux_state.getG(), heuristic_func);
			new_node = new Node(padre.getParent(), new_state);
		}
		else new_node = null;

		return new_node;
	}
	
	/**
	 * 
	 * @param padre
	 * @return
	 */
	public Node bajar(Node padre)
	{
		State aux_state = padre.getState();
		Node new_node;
		boolean control = false;
		
		Vector<Child> aux_children = new Vector<Child>();
		
		for(Child it : aux_state.getChildren())
		{
			Child aux_child = new Child(it.getId(), it.getColegio(), it.getEstado());
			aux_children.add(aux_child);
		}
		
		int free_seats = aux_state.getFree_seats();
		
		for(Child it : aux_children)
		{
			if( (it.getEstado() == 1) && (it.getColegio().equals(check_colegio(aux_state.getPosition()))) )
			{
				it.setEstado(2);
				free_seats += 1;
				control = true;
			}
		}
		
		if(control)
		{
			State new_state = new State(aux_state.getPosition(), aux_children, free_seats, aux_state.getG(), heuristic_func);
			new_node = new Node(padre.getParent(), new_state);
		}
		else new_node = null;

		return new_node;
	}
	
	/**
	 * 
	 * @param node
	 * @return
	 */
	public boolean is_final(Node node)
	{
		State aux = node.getState();
		boolean check = false;
		
		if(aux.getPosition().equals(map.getInitial_pos()))
		{
			for(Child it : aux.getChildren())
			{
				if(it.getEstado() == 2)
					check = true;
				else
					return false;
			}
		}
		else 
			return false;
		
		return check;
	}
	
	/**
	 * 
	 * @param p
	 * @return
	 */
	public String check_colegio(String p)
	{
		for(Colegio it : map.getColegios())
		{
			if(it.getId().equals(p))
				return it.getColegio();
		}
		return null;
	}
	
	/**
	 * 
	 * @param last_node
	 */
	public void print_output(Node last_node)
	{
		Vector<String> path = new Vector<>();
		path = last_node.getPath();
		
		String output = "{" + path.get(0);
		
		for(int i = 1; i < path.size(); i++)
			output += " -> " + path.get(i);
		
		output += "}";
		
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
	 * 
	 * @param intial_time
	 * @param final_time
	 * @param num_expansiones
	 * @param final_node
	 */
	public void print_statistics(long intial_time, long final_time, int num_expansiones, Node final_node)
	{
		String statistics = "";
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
