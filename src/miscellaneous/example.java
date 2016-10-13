import java.util.Scanner;

public class example
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        while (T --> 0)
        {
            String str = in.next();
            if (str.matches("[A-F]?A+F+C+[A-F]?"))
                System.out.println("Infected!");
            else
                System.out.println("Good");
        }
    }
}
