import java.io.*;
import java.util.*;

public class Mapa
{
	private Vector<Vector<Integer>> conexiones;
	private Vector<Colegio> colegios;
	private Vector<Child> children;
	
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
		}
		catch(IOException e) {
	    	System.out.println("FileNotFoundException: "+path+ " (No such file or directory)");
	    	return;
	    }
		//print_map();
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
				row.add(-1);
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
	
	public void print_map()
	{
		System.out.println("-----PARADAS-----");
		for(int i = 0; i < conexiones.size(); i++)
		{
			System.out.println("P" + (i+1));
			for(int j = 0; j < conexiones.get(i).size(); j++)
			{
				System.out.println("Conectado con P" + (j+1) + " en " + conexiones.get(i).get(j));
			}
		}
		
		System.out.println("-----CONEXIONES-----");
		for(int i = 0; i < colegios.size(); i++)
		{
			System.out.println("Colegio " + colegios.get(i).getColegio() + " en " + colegios.get(i).getId());
		}
		
		System.out.println("-----NIÑOS-----");
		for(int i = 0; i < children.size(); i++)
		{
			System.out.println("Niño en " + children.get(i).getId() + " hacia " + children.get(i).getColegio());
		}
		
		System.out.println("PARADA INICIAL " + initial_pos);
		System.out.println("CAPACIDAD " + capacity);
	}
	
	public Vector<Vector<Integer>> getConexiones() { return conexiones; }

	public Vector<Colegio> getColegios() { return colegios; }

	public Vector<Child> getChildren() { return children; }

	public String getInitial_pos() { return initial_pos; }

	public int getCapacity() { return capacity; }
	
	public String getPath() { return path; }


//	public static void main(String[] args)
//	{
//		Mapa map = new Mapa("ejemplos/problema3.prob");
//	}
}
