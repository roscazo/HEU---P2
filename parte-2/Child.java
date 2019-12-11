
public class Child extends Parada
{
	
	private int estado;
	private String colegio;
	
	public Child(String parada, String colegio, int estado)
	{
		super(parada);
		this.setColegio(colegio);
		this.setEstado(estado);
	}

	public int getEstado() {
		return estado;
	}

	public void setEstado(int estado) {
		this.estado = estado;
	}

	public String getColegio() {
		return colegio;
	}

	public void setColegio(String colegio) {
		this.colegio = colegio;
	}

	@Override
	public String toString() {
		return "Child [estado=" + estado + ", colegio=" + colegio + "]";
	}
	
}
