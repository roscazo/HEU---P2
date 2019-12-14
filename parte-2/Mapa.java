import java.io.*;
import java.util.*;

public class Mapa
{
	private Vector<Vector<Integer>> conexiones;
	private Vector<Colegio> colegios;
	private Vector<Child> children;
	
	private int[][] warshallC; 
	
	private String initial_pos;
	private int capacity;
	
	private String path;
	
	public Mapa(String path)
	{
		this.path = path;
		
		conexiones = new Vector<>();
		colegios = new Vector<>();
		children = new Vector<>();
		
		File map = new File(path);
		String line;
		int line_count = -1;
		int num_paradas = 0;
		
		BufferedReader reader;
		try
		{
			reader = new BufferedReader(new FileReader(map));
			line = reader.readLine();
			
			while(line != null)
			{
				String[] parts = line.split(" ");
				if(line_count == -1)
					num_paradas = num_paradas(parts);
				else if(line_count == num_paradas)
					row_colegios(parts);
				else if(line_count == num_paradas+1)
					row_children(parts);
				else if(line_count == num_paradas+2)
					row_start(parts);
				else
					matriz_conexiones(parts);
					
				++line_count;
				line = reader.readLine();
			}
			
			warshallC = new int[getConexiones().size()][getConexiones().size()];
			floyd_warshall();
		}
		catch(IOException e) {
	    	System.out.println("FileNotFoundException: "+path+ " (No such file or directory)");
	    	return;
	    }

	}
	
	public int num_paradas(String[] str)
	{
		int num = 0;
		
		for(int i = 0; i < str.length; i++)
		{
			String part = str[i].replace("\u00A0","").trim();
			if(!isNumeric(part) && !part.equals(""))
				++num;
		}
		return num;
	}
	
	public void matriz_conexiones(String[] str)
	{
		Vector<Integer> row = new Vector<>();
		
		for(int i = 0; i < str.length; i++)
		{
			String part = str[i].replace("\u00A0","").trim();
			if(!isNumeric(part) && part.equals("--"))
				row.add(Integer.MAX_VALUE);
			if(isNumeric(part))
				row.add(Integer.parseInt(part));
		}
		conexiones.add(row);
	}
	
	public void row_colegios(String[] str)
	{
		String c = "", p = "";
		
		for(int i = 0; i < str.length; i++)
		{
			String part = str[i].replace("\u00A0","").trim();
			
			if(part.contains(":"))
				c = part.substring(0,2);
			else
			{
				p = part.substring(0,2);
				Colegio aux = new Colegio(p, c);
				colegios.add(aux);
			}
				
		}
	}
	
	public void row_children(String[] str)
	{
		int num_children = 0;
		String c = "", p = "";
		
		for(int i = 0; i < str.length; i++)
		{
			String part = str[i].replace("\u00A0","").trim();
			
			if(isNumeric(part))
				num_children = Integer.parseInt(part);
			else if(part.contains(":"))
				p = part.substring(0,2);
			else
			{
				for(int j = 0; j < num_children; j++)
				{
					c = part.substring(0,2);
					Child aux = new Child(p, c, 0);
					children.add(aux);
				}
			}
		}
	}
	
	public void row_start(String[] str)
	{
		for(int i = 0; i < str.length; i++)
		{
			String part = str[i].replace("\u00A0","").trim();
			
			if(isNumeric(part))
				capacity = Integer.parseInt(part);
			else if(!isNumeric(part) && !part.contains(":"))
				initial_pos = part;
		}
	}
	
	/**
	 * Implementa el algoritmo Floyd-Warshall, el cu�l devuelve el camino m�s corto entre dos paradas
	 */
	public void floyd_warshall()
	{
		int i,j,k;
		
		// Guarda la matriz de conexiones en una nueva matriz 
		for (i = 0; i < getConexiones().size(); i++)
			for (j = 0; j < getConexiones().size(); j++)
				warshallC[i][j] = getConexiones().get(i).get(j);
		
		for (k = 0; k < warshallC.length; k++)
		{
			if(i==k) continue;
			for (i = 0; i < warshallC.length; i++)
			{
				for (j = 0; j < warshallC.length; j++)
				{
					if(j==k) continue;
					else if(i==j) continue;
					else
					{
						if(warshallC[i][k] != Integer.MAX_VALUE && warshallC[k][j] != Integer.MAX_VALUE)
							if(warshallC[i][k] + warshallC[k][j] < warshallC[i][j])
								warshallC[i][j] = warshallC[i][k]+warshallC[k][j];
					}
				}
			}
		}
	}
	
	public static boolean isNumeric(String cadena) {
		boolean resultado;
		try {
			Integer.parseInt(cadena);
			resultado = true;
		} catch (NumberFormatException excepcion) {
			resultado = false;
		}
		return resultado;
	}
	
	public String print_map()
	{
		String output = "------DATOS INICIALES------\n";
		
		output += "\tNúmero de paradas: " + conexiones.size() + "\n";
		
		output += "\tParada inicial: " + getInitial_pos() + "\n";
		
		output += "\tCapacidad del autobús: " + getCapacity() + "\n";
		
		output += "\tColegios: ";
		for(int i = 0; i < colegios.size()-1; i++)
			output += colegios.get(i).getColegio() + " en " + colegios.get(i).getId() + ", ";
		output += colegios.get(colegios.size()-1).getColegio() + " en " + colegios.get(colegios.size()-1).getId() + "\n";
		
		output += "\t" + getChildren().size() + " alumnos:\n";
		for(int i = 0; i < children.size(); i++)
			output += "\t\tAlumno " + (i+1) + " en " + getChildren().get(i).getId() + " hacia " + getChildren().get(i).getColegio() + "\n";

		return output;
	}
	
	public void print_warshall()
	{
		for (int i = 0; i < warshallC.length; i++)
		{
			for (int j = 0; j < warshallC.length; j++)
				System.out.print(warshallC[i][j] + " ");
			System.out.print("\n");
		}
			
	}
	
	public Vector<Vector<Integer>> getConexiones() { return conexiones; }

	public Vector<Colegio> getColegios() { return colegios; }

	public Vector<Child> getChildren() { return children; }

	public String getInitial_pos() { return initial_pos; }

	public int getCapacity() { return capacity; }
	
	public String getPath() { return path; }
	
	public int[][] getFW() { return warshallC; }

}
