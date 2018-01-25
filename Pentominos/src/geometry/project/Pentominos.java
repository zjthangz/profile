package geometry.project;

import java.util.*;

/**
 * Created by jintian on 12/14/17.
 */
public class Pentominos {

    private final Board board;
    private final DancingLinks dancingLinks;
    private final HashMap<String,Boolean> answers;
    private int answerCount;

    public Pentominos() {
        this(8,8, new HashSet<Integer>(Arrays.asList(27,28,35,36)));
    }
    public Pentominos(int row, int column) {
        this(row, column, null);
    }
    public Pentominos(int row, int column, HashSet<Integer> blocks) {
        int diff = row*column-60;
        if (diff != 0 && blocks != null && diff != blocks.size()) {
            System.out.println("Invalid input, the program is running 8*8 instead.");
            this.board = new Board(row, column, new HashSet<Integer>(Arrays.asList(27,28,35,36)));
        } else {
            this.board = new Board(row, column, blocks);
        }
        dancingLinks = new DancingLinks(Pattern.createMatrix(board), this);
        answers = new HashMap<>();
        answerCount = 0;
    }

    private void printAnswers() {

        for (Map.Entry<String, Boolean> entry : answers.entrySet()) {
            if(entry.getValue() == false) {
                continue;
            }
            for (int i = 0; i < (board.getColumn()+1)*2+1; i++) {
                System.out.print("-");
            }
            System.out.print("\n");
            String answer = entry.getKey();
            for (int i = 0; i < answer.length(); i++) {
                if ( (i) % board.getColumn() == 0 ) {
                    System.out.print("| ");
                }
                System.out.printf("\u001B[1;%dm%s\033[0m ", Pattern.patternToColumn(answer.charAt(i))%8+31, answer.charAt(i));
                if ( (i) % board.getColumn() == (board.getColumn()-1) ) {
                    System.out.print("\033[0m|\n");
                }
            }
            for (int i = 0; i < (board.getColumn()+1)*2+1; i++) {
                System.out.print("-");
            }
            System.out.print("\n");
        }
        System.out.printf("\033[1;31m%s \033[0msolutions found.%n", answerCount);
        for (int i = 0; i < (board.getColumn()+1)*2+1; i++) {
            System.out.print("-");
        }
        System.out.print("\n");
    }

    public void checkSolution(char[] sol) {
        if (sol.length != 60) throw new RuntimeException("Not a valid solution!");

        char[][] solBoard = new char[board.getRow()][board.getColumn()];
        int blockCount = 0;
        for (int i = 0; i < sol.length; i++) {
            while (board.getBlocks() != null && board.getBlocks().contains(i+blockCount)) {
                solBoard[(i+blockCount)/board.getColumn()][(i+blockCount)%board.getColumn()] = '▨';
                blockCount++;
            }
            solBoard[(i+blockCount)/board.getColumn()][(i+blockCount)%board.getColumn()] = sol[i];
        }

        String solStr = solBoardToString(solBoard);
        if (answers.isEmpty() || !answers.containsKey(solStr)) {
            answers.put(solStr, true);
            answerCount++;
            char[][] revSolBoard = reverse(solBoard);
            String revSolStr = solBoardToString(revSolBoard);
            if (!answers.containsKey(revSolStr)) answers.put(revSolStr, false);
            String temp = solBoardToString(rotate180Clockwise(solBoard));
            if (!answers.containsKey(temp)) answers.put(temp, false);
            temp = solBoardToString(rotate180Clockwise(revSolBoard));
            if (!answers.containsKey(temp)) answers.put(temp, false);
            if (board.getColumn() == board.getRow()) { //board must be symmetric
                temp = solBoardToString(rotate90Clockwise(solBoard));
                if (!answers.containsKey(temp)) answers.put(temp, false);
                temp = solBoardToString(rotate90Clockwise(revSolBoard));
                if (!answers.containsKey(temp)) answers.put(temp, false);
                temp = solBoardToString(rotate270Clockwise(solBoard));
                if (!answers.containsKey(temp)) answers.put(temp, false);
                temp = solBoardToString(rotate270Clockwise(revSolBoard));
                if (!answers.containsKey(temp)) answers.put(temp, false);
            }
        }
    }

    private String solBoardToString(char[][] sol) {
        String ret = new String();
        for(char[] row : sol) {
            ret+=new String(row);
        }
        return ret;
    }

    private char[][] reverse(char[][] src) {
        char[][] ret = new char[src.length][src[0].length];
        for (int i = 0; i < ret.length; i++) {
            for (int j = 0; j < ret[0].length; j++) {
                ret[i][j] = src[src.length-i-1][j];
            }
        }
        return ret;
    }

    private char[][] rotate90Clockwise(char[][] src) {
        char[][] ret = new char[src[0].length][src.length];
        for (int i = 0; i < ret.length; i++) {
            for (int j = 0; j < ret[0].length; j++) {
                ret[i][j] = src[src.length-j-1][i];
            }
        }
        return ret;
    }

    private char[][] rotate180Clockwise(char[][] src) {
        char[][] ret = new char[src.length][src[0].length];
        for (int i = 0; i < ret.length; i++) {
            for (int j = 0; j < ret[0].length; j++) {
                ret[i][j] = src[src.length-i-1][src[0].length-j-1];
            }
        }
        return ret;
    }

    private char[][] rotate270Clockwise(char[][] src) {
        char[][] ret = new char[src[0].length][src.length];
        for (int i = 0; i < ret.length; i++) {
            for (int j = 0; j < ret[0].length; j++) {
                ret[i][j] = src[j][src[0].length-i-1];
            }
        }
        return ret;
    }

    public void solve() {
        dancingLinks.runSolver();
        printAnswers();
    }

}
