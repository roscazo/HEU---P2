import java.util.*;

public class OPEN_list 
{
	Vector<Node> open_nodes;
	
	public OPEN_list(Node initial_node)
	{
		open_nodes = new Vector<Node>();
		open_nodes.add(initial_node);
	}
	
	/**
	 * Inserta el nuevo nodo en orden
	 * 
	 * @param new_node Nodo a introducir
	 */
	public void ordered_insert(Node new_node)
	{
		// Si la lista está vacía, se añade sin comprobar nada
		if(open_nodes.isEmpty()) { open_nodes.add(new_node); }
		
		// En caso contrario
		else
		{
			int new_F = new_node.getState().getF();
			// Se compara con todos los nodos en OPEN
			for(int i = 0; i < open_nodes.size(); i++)
			{
				int aux_F = open_nodes.get(i).getState().getF();
				// Se coloca el nuevo nodo siempre antes que los viejos y en orden ascendente
				if(new_F <= aux_F)
				{ 
					open_nodes.add(i, new_node);
					return;
				}
			}
			open_nodes.add(new_node);
		}
	}
	
	/**
	 * Comprueba si el nodo en la lista OPEN
	 * 
	 * @param new_node Nodo a comprobar
	 * @return True en caso de que este, false en caso contrario
	 */
	public boolean contains(Node new_node)
	{
		boolean check = false;

		for(Node iterator : open_nodes)
		{
			if(iterator.getState().is_equal(new_node.getState()))
			{
				return true;
			}
			else check = false;
		}
		return check;
	}

	@Override
	public String toString() {
		return "OPEN_list [open_nodes=" + open_nodes + "]";
	}
	
	
	
}
