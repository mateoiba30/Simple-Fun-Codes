import java.util.Scanner;
public class CrearGettersSetters {
    public static void main (String[] args){
        Scanner in = new Scanner(System.in); //no olvidar

        System.out.println("Ingrese cantidad de atributos: ");
        int x=in.nextInt();
        String[] vectorS=new String[x*6];
        int j=0;

        for(int i=0;i<x;i++){

            System.out.println("Ingrese nombre de la varable "+(i+1));
            String nombre=in.next();
            System.out.println("Ingrese tipo de la varable "+(i+1));
            String tipo=in.next();
            
            String set1="public void set"+capitalize(nombre)+"("+tipo+" "+nombre+"){";
            vectorS[j]=set1;
            j++;
            String set2= "    this."+nombre+"="+nombre+";";
            vectorS[j]=set2;
            j++;      
            String set3="}";
            vectorS[j]=set3;
            j++;

            String get1="public "+tipo+" get"+capitalize(nombre)+"(){";
            vectorS[j]=get1;
            j++;
            String get2="    return "+nombre+";";
            vectorS[j]=get2;
            j++;
            String get3="}";
            vectorS[j]=get3;
            j++;

            System.out.println("----------------------------------");
        }

        System.out.println();
        System.out.println();
        System.out.println("| CODIGO |");
        System.out.println();

        for(int i=0;i<x*6;i++){
            System.out.println(vectorS[i]);
            System.out.println();
        }


        in.close();
       
    }

    public static String capitalize(String str)
    {
        if (str == null || str.length() == 0) {
            return str;
        }
 
        return str.substring(0, 1).toUpperCase() + str.substring(1);
    }

}