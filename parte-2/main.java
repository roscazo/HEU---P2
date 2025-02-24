import java.util.*;
import java.io.*;

public class main{

	public static void main(String[] args)
	{
		String invalidArgs = "Invalid Arguments\n"+
				"Try: java main -help\n";
		String help_string = "Uso: java main <problem> <heuristic>\n"+
				"\tproblem: el path al archivo que contenga el problema a resolver\n"+
				"\theuristic: nombre de una de las heuristicas disponibles:\n"+
					"\t\tdefault - llama a la heuristica 0\n"+
					"\t\theu_1 - primera heuristica usando las distancias a los alumnos mas cercano\n"+
					"\t\theu_2 - segunda heuristica usando los estados de los alumnos\n"+
				"Para mas informacion acerca de las heuristicas consultar la memoria.";
		
		//Check input
		if(args.length == 2)
		{
			if(!args[1].equals("default") && !args[1].equals("heu_1") && !args[1].equals("heu_2")) 
			{
				System.out.println(invalidArgs);
				return;
			}
		}
		else if(args.length == 1) 
		{
			//Only one parameter. Check for -help
			if(args[0].equals("-help")) 
			{
				System.out.println(help_string);
				return;
			}
			else 
			{
				System.out.println(invalidArgs);
				return;
			}
		}
		else 
		{
			System.out.println(invalidArgs);
			return;
		}
		
		String path = args[0];
		String heuristica = args[1];
		
		Mapa map = new Mapa(path);
		A_star astar = new A_star(map, heuristica);
	}
	
}
