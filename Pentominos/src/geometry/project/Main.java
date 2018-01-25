package geometry.project;

import java.io.IOException;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException{

//        user input mode
        while(true) {
            System.out.print("Choose a Pattern:\n1. 8✕8 with 4 blocks in the center;\n2. 3✕20;\n3. 4✕15;\n4. 5✕12;\n5. 6✕10;\nInput a number: ");
            Scanner in = new Scanner(System.in);
            int i = in.nextInt();
            Pentominos pentominos;
            switch (i) {
                case 1:
                    pentominos = new Pentominos();
                    break;
                case 2:
                    pentominos = new Pentominos(3, 20);
                    break;
                case 3:
                    pentominos = new Pentominos(4, 15);
                    break;
                case 4:
                    pentominos = new Pentominos(5, 12);
                    break;
                case 5:
                    pentominos = new Pentominos(6, 10);
                    break;
                default:
                    System.out.print("Invalid input.");
                    return;
            }
            pentominos.solve();
        }

//        code define mode
//        Pentominos pentominos = new Pentominos();
//        Pentominos pentominos = new Pentominos(3,20);
//        Pentominos pentominos = new Pentominos(4,15);
//        Pentominos pentominos = new Pentominos(5,12);
//        Pentominos pentominos = new Pentominos(6,10);

//        to define other boards, use the following format. e.g. a block at row r and column c, integer = r*column+c
//        Pentominos pentominos = new Pentominos(row,column, new HashSet<>(Arrays.asList(...integer)));

//        pentominos.solve();
    }
}
