public class Colegio extends Parada
{
	
	private String colegio;
	
	public Colegio(String parada, String colegio)
	{
		super(parada);
		this.colegio = colegio;
	}

	public String getColegio() {
		return colegio;
	}

	public void setColegio(String colegio) {
		this.colegio = colegio;
	}

}
