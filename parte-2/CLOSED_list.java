import java.util.*;

public class CLOSED_list 
{
	Set<Node> closed_nodes;
	
	public CLOSED_list()
	{
		closed_nodes = new TreeSet<Node>();
	}
	
	/**
	 * Comprueba si el nodo en la lista CLOSED
	 * 
	 * @param new_node Nodo a comprobar
	 * @return True en caso de que este, false en caso contrario
	 */
	public boolean contains(Node new_node)
	{
		for(Node iterator : closed_nodes)
		{
			if(iterator.compareTo(new_node) == 0)
				return true;
		}
		return false;
	}

	@Override
	public String toString() {
		return "CLOSED_list [closed_nodes=" + closed_nodes + "]";
	}

}
