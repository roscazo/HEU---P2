import java.util.*;

public class Node implements Comparable<Node>
{
	private Node parent;
	private State state;
	
	/**
	 * 
	 * @param parent
	 * @param state
	 */
	public Node(Node parent, State state)
	{
		this.setParent(parent);
		this.setState(state);
	}

	/**
	 * 
	 * @param hyper_node
	 * @return
	 */
	public boolean isAncestor(Node hyper_node)
	{
		if(state.is_equal(hyper_node.state)){ return true; }
		
		else
		{
			if(hyper_node.parent == null) { return false; }
			
			else { return isAncestor(hyper_node.parent); }
		}
	}
	
	/**
	 * 
	 * @return
	 */
	public Vector<String> getPath()
	{
		Vector<String> buffer = new Vector<>();
		String pos = this.getState().getPosition();
		
		if(parent == null)
		{
			buffer.add(pos);
			return buffer;
		}
		else
		{
			buffer = parent.getPath();
			buffer.add(pos);
			return buffer;
		}
	}
	
	/**
	 * 
	 * @return
	 */
	public int getDepth()
	{
		if(parent == null) { return 1; }
		
		else { return (1 + parent.getDepth()); }
	}
	
	/**
	 * 
	 */
	@Override
	public int compareTo(Node other_node)
	{
		if(state.is_equal(other_node.getState())) { return 0; }
		
		else { return -1; }
	}
	
	public Node getParent() { return parent; }

	public void setParent(Node parent) { this.parent = parent; }

	public State getState() { return state; }

	public void setState(State state) { this.state = state; }

	@Override
	public String toString() {
		return "Node [state=" + state + "]";
	}

	
}
