import java.util.*;

public class CLOSED_list 
{
	Set<Node> closed_nodes;
	
	public CLOSED_list()
	{
		closed_nodes = new TreeSet<Node>();
	}
	
	public boolean contains(Node new_node)
	{
		boolean check = false;

		for(Node iterator : closed_nodes)
		{
			if(iterator.compareTo(new_node) == 0)
			{
				return true;
			}
			else check = false;
		}
		return check;
	}

	@Override
	public String toString() {
		return "CLOSED_list [closed_nodes=" + closed_nodes + "]";
	}

}
