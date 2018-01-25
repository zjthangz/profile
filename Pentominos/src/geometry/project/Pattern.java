package geometry.project;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * Created by jintian on 12/14/17.
 */
public class Pattern {
    private final char name;
    private final int column;
    private final int row;
    private final int[] positions;

    public Pattern(char name, int column, int row, int[] positions) {
        this.column = column;
        this.name = name;
        this.positions = positions;
        this.row = row;
    }

    public int getColumn() {
        return column;
    }

    public int getRow() {
        return row;
    }

    public char getName() {
        return name;
    }

    public int[] getPositions() {
        return positions;
    }

    public static final Pattern[] PATTERNS = {
            //location[i,j]=[i+p[x+1],j+p[x]]=[r,c] --> column in matrix = 12+board.column*r+c.
            // i+pattern.row<=board.row, j+pattern.column<=board.column, and nothing at block
            new Pattern('F', 3, 3, new int[]{1,0,2,0,0,1,1,1,1,2}),
            new Pattern('F', 3, 3, new int[]{0,0,0,1,1,1,2,1,1,2}),
            new Pattern('F', 3, 3, new int[]{1,0,1,1,2,1,0,2,1,2}),
            new Pattern('F', 3, 3, new int[]{1,0,0,1,1,1,2,1,2,2}),
            new Pattern('F', 3, 3, new int[]{0,0,1,0,1,1,2,1,1,2}),
            new Pattern('F', 3, 3, new int[]{1,0,0,1,1,1,2,1,0,2}),
            new Pattern('F', 3, 3, new int[]{1,0,0,1,1,1,1,2,2,2}),
            new Pattern('F', 3, 3, new int[]{2,0,0,1,1,1,2,1,1,2}),

            new Pattern('I', 1, 5, new int[]{0,0,0,1,0,2,0,3,0,4}),
            new Pattern('I', 5, 1, new int[]{0,0,1,0,2,0,3,0,4,0}),

            new Pattern('L', 2, 4, new int[]{0,0,0,1,0,2,0,3,1,3}),
            new Pattern('L', 4, 2, new int[]{3,0,0,1,1,1,2,1,3,1}),
            new Pattern('L', 2, 4, new int[]{0,0,1,0,1,1,1,2,1,3}),
            new Pattern('L', 4, 2, new int[]{0,0,1,0,2,0,3,0,0,1}),
            new Pattern('L', 2, 4, new int[]{1,0,1,1,1,2,0,3,1,3}),
            new Pattern('L', 4, 2, new int[]{0,0,1,0,2,0,3,0,3,1}),
            new Pattern('L', 2, 4, new int[]{0,0,1,0,0,1,0,2,0,3}),
            new Pattern('L', 4, 2, new int[]{0,0,0,1,1,1,2,1,3,1}),

            new Pattern('N', 2, 4, new int[]{1,0,1,1,0,2,1,2,0,3}),
            new Pattern('N', 4, 2, new int[]{0,0,1,0,2,0,2,1,3,1}),
            new Pattern('N', 2, 4, new int[]{1,0,0,1,1,1,0,2,0,3}),
            new Pattern('N', 4, 2, new int[]{0,0,1,0,1,1,2,1,3,1}),
            new Pattern('N', 2, 4, new int[]{0,0,0,1,0,2,1,2,1,3}),
            new Pattern('N', 4, 2, new int[]{2,0,3,0,0,1,1,1,2,1}),
            new Pattern('N', 2, 4, new int[]{0,0,0,1,1,1,1,2,1,3}),
            new Pattern('N', 4, 2, new int[]{1,0,2,0,3,0,0,1,1,1}),

            new Pattern('P', 2, 3, new int[]{0,0,1,0,0,1,1,1,0,2}),
            new Pattern('P', 3, 2, new int[]{0,0,1,0,0,1,1,1,2,1}),
            new Pattern('P', 2, 3, new int[]{1,0,0,1,1,1,0,2,1,2}),
            new Pattern('P', 3, 2, new int[]{0,0,1,0,2,0,1,1,2,1}),
            new Pattern('P', 2, 3, new int[]{0,0,1,0,0,1,1,1,1,2}),
            new Pattern('P', 3, 2, new int[]{0,0,1,0,2,0,0,1,1,1}),
            new Pattern('P', 2, 3, new int[]{0,0,0,1,1,1,0,2,1,2}),
            new Pattern('P', 3, 2, new int[]{1,0,2,0,0,1,1,1,2,1}),

            new Pattern('T', 3, 3, new int[]{0,0,1,0,2,0,1,1,1,2}),
            new Pattern('T', 3, 3, new int[]{0,0,0,1,1,1,2,1,0,2}),
            new Pattern('T', 3, 3, new int[]{1,0,1,1,0,2,1,2,2,2}),
            new Pattern('T', 3, 3, new int[]{2,0,0,1,1,1,2,1,2,2}),

            new Pattern('U', 3, 2, new int[]{0,0,2,0,0,1,1,1,2,1}),
            new Pattern('U', 2, 3, new int[]{0,0,1,0,1,1,0,2,1,2}),
            new Pattern('U', 3, 2, new int[]{0,0,1,0,2,0,0,1,2,1}),
            new Pattern('U', 2, 3, new int[]{0,0,1,0,0,1,0,2,1,2}),

            new Pattern('V', 3, 3, new int[]{0,0,0,1,0,2,1,2,2,2}),
            new Pattern('V', 3, 3, new int[]{2,0,2,1,0,2,1,2,2,2}),
            new Pattern('V', 3, 3, new int[]{0,0,1,0,2,0,2,1,2,2}),
            new Pattern('V', 3, 3, new int[]{0,0,1,0,2,0,0,1,0,2}),

            new Pattern('W', 3, 3, new int[]{0,0,0,1,1,1,1,2,2,2}),
            new Pattern('W', 3, 3, new int[]{2,0,1,1,2,1,0,2,1,2}),
            new Pattern('W', 3, 3, new int[]{0,0,1,0,1,1,2,1,2,2}),
            new Pattern('W', 3, 3, new int[]{1,0,2,0,0,1,1,1,0,2}),

            new Pattern('X', 3, 3, new int[]{1,0,0,1,1,1,2,1,1,2}),

            new Pattern('Y', 2, 4, new int[]{1,0,0,1,1,1,1,2,1,3}),
            new Pattern('Y', 4, 2, new int[]{0,0,1,0,2,0,3,0,1,1}),
            new Pattern('Y', 2, 4, new int[]{0,0,0,1,0,2,1,2,0,3}),
            new Pattern('Y', 4, 2, new int[]{2,0,0,1,1,1,2,1,3,1}),
            new Pattern('Y', 2, 4, new int[]{0,0,0,1,1,1,0,2,0,3}),
            new Pattern('Y', 4, 2, new int[]{1,0,0,1,1,1,2,1,3,1}),
            new Pattern('Y', 2, 4, new int[]{1,0,1,1,0,2,1,2,1,3}),
            new Pattern('Y', 4, 2, new int[]{0,0,1,0,2,0,3,0,2,1}),

            new Pattern('Z', 3, 3, new int[]{0,0,1,0,1,1,1,2,2,2}),
            new Pattern('Z', 3, 3, new int[]{2,0,0,1,1,1,2,1,0,2}),
            new Pattern('Z', 3, 3, new int[]{0,0,1,0,1,1,1,2,2,2}),
            new Pattern('Z', 3, 3, new int[]{2,0,0,1,1,1,2,1,0,2})
    };

    public static char columnToPattern(int column) {
        switch (column) {
            case 0: return 'F';
            case 1: return 'I';
            case 2: return 'L';
            case 3: return 'N';
            case 4: return 'P';
            case 5: return 'T';
            case 6: return 'U';
            case 7: return 'V';
            case 8: return 'W';
            case 9: return 'X';
            case 10: return 'Y';
            case 11: return 'Z';
        }
        return '✖';
    }

    public static int patternToColumn(char pattern) {
        switch (pattern) {
            case 'F': return 0;
            case 'I': return 1;
            case 'L': return 2;
            case 'N': return 3;
            case 'P': return 4;
            case 'T': return 5;
            case 'U': return 6;
            case 'V': return 7;
            case 'W': return 8;
            case 'X': return 9;
            case 'Y': return 10;
            case 'Z': return 11;
        }
        return -1;
    }

    public static ArrayList<ArrayList<Boolean>> createMatrix(Board board) {
        ArrayList<ArrayList<Boolean>> arrayMatrix = new ArrayList();
        int[][] indexMatrix = new int[board.getRow()][board.getColumn()];
        if (board.getBlocks() != null) {
            for (int block : board.getBlocks()) {
                indexMatrix[block/board.getColumn()][block%board.getColumn()] = -1;
            }
        }
        for(int n = 12, i = 0; i < indexMatrix.length; i++) {
            for (int j = 0; j < indexMatrix[0].length; j++) {
                if (indexMatrix[i][j] == -1) continue;
                indexMatrix[i][j] = n;
                n++;
            }
        }
        for (Pattern pattern : PATTERNS) {
            for (int i = 0; i+pattern.row-1<board.getRow(); i++) {
                for (int j = 0; j+pattern.column-1<board.getColumn(); j++) {
                    if (indexMatrix[(i+pattern.getPositions()[1])][j+pattern.getPositions()[0]] == -1 ||
                            indexMatrix[(i+pattern.getPositions()[3])][j+pattern.getPositions()[2]] == -1 ||
                            indexMatrix[(i+pattern.getPositions()[5])][j+pattern.getPositions()[4]] == -1 ||
                            indexMatrix[(i+pattern.getPositions()[7])][j+pattern.getPositions()[6]] == -1 ||
                            indexMatrix[(i+pattern.getPositions()[9])][j+pattern.getPositions()[8]] == -1) continue;
                    ArrayList<Boolean> column = new ArrayList<>(72);
                    for (int k = 0; k < 72; k++) {
                        column.add(false);
                    }
                    column.set(patternToColumn(pattern.name), true);
                    for (int k = 0; k < 5; k++) {
                        column.set(indexMatrix[(i+pattern.getPositions()[2*k+1])][j+pattern.getPositions()[2*k]], true);
                    }
                    arrayMatrix.add(column);
                }
            }
        }
//        --- for testing
//        for (int i = 0; i < arrayMatrix.size(); i++) {
//            for (int j = 0; j < arrayMatrix.get(0).size(); j++) {
//                System.out.printf("%s    ", arrayMatrix.get(i).get(j));
//            }
//            System.out.print('\n');
//        }
//        ---

        return arrayMatrix;
    }
}
