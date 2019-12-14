import java.util.Vector;

public class State 
{
	private String position;
	private Vector<Child> children;
	private int free_seats;
	
	private int g;
	private int h;
	
	public State(String position, Vector<Child> children, int free_seats, int g)
	{
		this.setPosition(position);
		this.setChildren(children);
		this.setFree_seats(free_seats);
		this.setG(g);
//		this.setH(h);
	}
	
	public int getF()
	{
		return (g + h);
	}
	
	public boolean is_equal(State other_state)
	{
		boolean check = false;
		
		if(this.getPosition().equals(other_state.getPosition()))
		{
			for(int i = 0; i < this.getChildren().size(); i++)
			{
				if(this.getChildren().get(i).getEstado() == other_state.getChildren().get(i).getEstado())
					check = true;
				else 
					return false;
			}
			return check;
		}
		else 
			return false;
	}

	public String getPosition() {
		return position;
	}

	public void setPosition(String position) {
		this.position = position;
	}

	public Vector<Child> getChildren() {
		return children;
	}

	public void setChildren(Vector<Child> children) {
		this.children = children;
	}

	public int getFree_seats() {
		return free_seats;
	}

	public void setFree_seats(int free_seats) {
		this.free_seats = free_seats;
	}

	public int getG() {
		return g;
	}

	public void setG(int g) {
		this.g = g;
	}

	public int getH() {
		return h;
	}

	public void setH(int h) {
		this.h = h;
	}

	@Override
	public String toString() {
		return "State [position=" + position + ", children=" + children.toString() + ", free_seats=" + free_seats + ", g=" + g
				+ ", h=" + h + "]";
	}
	
	
}
