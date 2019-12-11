public abstract class Parada 
{
	private String id;
	
	public Parada(){};
	
	public Parada(String id)
	{
		this.setId(id);
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}
}
