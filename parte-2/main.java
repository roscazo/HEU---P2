import java.util.*;
import java.io.*;

public class main{

	public static void main(String[] args)
	{
		String invalidArgs = "Invalid Arguments\n"+
				"Try: java main -help\n";
		String help_string = "Usage: java main <problem> <heuristic>\n"+
				"\tmaze: el path al archivo que contenga el problema a resolver\n"+
				"\theuristic: nombre de una de las heur�sticas disponibles:\n"+
					"\t\tdefault\n"+
					"\t\theu_1\n"+
				"For more information see 346083-362273.pdf.";
		
		//Check input
		if(args.length == 2)
		{
			if(!args[1].equals("default") && !args[1].equals("heu_1")) 
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
