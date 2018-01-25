package geometry.project;

import java.util.HashSet;

/**
 * Created by jintian on 12/14/17.
 */
public class Board {
    private final int row;
    private final int column;
    private final HashSet<Integer> blocks;
    public Board(int row, int column, HashSet<Integer> blocks) {
        this.row = row;
        this.column = column;
        this.blocks = blocks;
    }

    public int getRow() {
        return row;
    }

    public int getColumn() {
        return column;
    }

    public HashSet<Integer> getBlocks() {
        return blocks;
    }

}