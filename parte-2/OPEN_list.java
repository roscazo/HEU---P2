import java.util.*;

public class OPEN_list 
{
	Vector<Node> open_nodes;
	
	public OPEN_list(Node initial_node)
	{
		open_nodes = new Vector<Node>();
		open_nodes.add(initial_node);
	}
	
	public void ordered_insert(Node new_node)
	{
		if(open_nodes.isEmpty()) { open_nodes.add(new_node); }
		
		else
		{
			int new_F = new_node.getState().getF();
			
			for(int i = 0; i < open_nodes.size(); i++)
			{
				int aux_F = open_nodes.get(i).getState().getF();
				
				if(new_F <= aux_F)
				{ 
					open_nodes.add(i, new_node);
					return;
				}
			}
			open_nodes.add(new_node);
		}
	}
	
	// Comprueba que el nuevo nodo no esté en OPEN
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
