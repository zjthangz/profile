// Author: Rafal Szymanski <me@rafal.io>

// Implementation of the Dancing Links algorithm for exact cover.

//Code source: https://github.com/rafalio/dancing-links-java/tree/master/src/dlx

//Modified by Jintian for Pentominos

package geometry.project;

import java.util.*;

public class DancingLinks{

    public class DancingNode{
        DancingNode L, R, U, D;
        ColumnNode C;

        // hooks node n1 `below` current node
        DancingNode hookDown(DancingNode n1){
            assert (this.C == n1.C);
            n1.D = this.D;
            n1.D.U = n1;
            n1.U = this;
            this.D = n1;
            return n1;
        }

        // this-n1-this.R
        DancingNode hookRight(DancingNode n1){
            n1.R = this.R;
            n1.R.L = n1;
            n1.L = this;
            this.R = n1;
            return n1;
        }

        //L-this-r -> L-R this
        void unlinkLR(){
            this.L.R = this.R;
            this.R.L = this.L;
        }

        void relinkLR(){
            this.L.R = this.R.L = this;
        }

        void unlinkUD(){
            this.U.D = this.D;
            this.D.U = this.U;
        }

        void relinkUD(){
            this.U.D = this.D.U = this;
        }

        public DancingNode(){
            L = R = U = D = this;
        }

        public DancingNode(ColumnNode c){
            this();
            C = c;
        }
    }

    class ColumnNode extends DancingNode{
        int size; // number of ones in current column
        int name;

        public ColumnNode(int n){
            super();
            size = 0;
            name = n;
            C = this;
        }

        //remove remove all nodes in the column
        void cover(){
            unlinkLR();
            for(DancingNode i = this.D; i != this; i = i.D){
                for(DancingNode j = i.R; j != i; j = j.R){
                    j.unlinkUD();
                    j.C.size--;
                }
            }
            header.size--; // not part of original
        }

        void uncover(){
            for(DancingNode i = this.U; i != this; i = i.U){
                for(DancingNode j = i.L; j != i; j = j.L){
                    j.C.size++;
                    j.relinkUD();
                }
            }
            relinkLR();
            header.size++; // not part of original
        }
    }

    private ColumnNode header;
    private List<DancingNode> answer;
    private Pentominos pentominos;

    // Heart of the algorithm
    private void search(){
        if (header.R == header){ // all the columns removed
            handleSolution(answer);
        } else{
            ColumnNode c = selectColumnNodeHeuristic();
            c.cover();

            for(DancingNode r = c.D; r != c; r = r.D){
                answer.add(r);

                for(DancingNode j = r.R; j != r; j = j.R){
                    j.C.cover();
                }

                search();

                r = answer.remove(answer.size() - 1);
                c = r.C;

                for(DancingNode j = r.L; j != r; j = j.L){
                    j.C.uncover();
                }
            }
            c.uncover();
        }
    }

    private ColumnNode selectColumnNodeNaive(){
        return (ColumnNode) header.R;
    }

    private ColumnNode selectColumnNodeHeuristic(){
        int min = Integer.MAX_VALUE;
        ColumnNode ret = null;
        for(ColumnNode c = (ColumnNode) header.R; c != header; c = (ColumnNode) c.R){
            if (c.size < min){
                min = c.size;
                ret = c;
            }
        }
        return ret;
    }


    // grid is a grid of 0s and 1s to solve the exact cover for
    // returns the root column header node
    private ColumnNode makeDLXBoard(ArrayList<ArrayList<Boolean>> grid){
        final int COLS = grid.get(0).size();
        final int ROWS = grid.size();

        ColumnNode headerNode = new ColumnNode(-1);
        ArrayList<ColumnNode> columnNodes = new ArrayList<ColumnNode>();

        for(int i = 0; i < COLS; i++){
            ColumnNode n = new ColumnNode(i);
            columnNodes.add(n);
            headerNode = (ColumnNode) headerNode.hookRight(n);
        }
        headerNode = headerNode.R.C;

        for(int i = 0; i < ROWS; i++){
            DancingNode prev = null;
            for(int j = 0; j < COLS; j++){
                if (grid.get(i).get(j) == true){
                    ColumnNode col = columnNodes.get(j);
                    DancingNode newNode = new DancingNode(col);
                    if (prev == null)
                        prev = newNode;
                    col.U.hookDown(newNode);
                    prev = prev.hookRight(newNode);
                    col.size++;
                }
            }
        }

        headerNode.size = COLS;
        
        return headerNode;
    }

    // Grid consists solely of 1s and 0s. Undefined behaviour otherwise
    public DancingLinks(ArrayList<ArrayList<Boolean>> grid, Pentominos pentominos){
        header = makeDLXBoard(grid);
        this.pentominos = pentominos;
    }

    public void runSolver(){
        answer = new LinkedList<DancingNode>();
        search();
    }

    public void handleSolution(List<DancingNode> answer) throws ArrayIndexOutOfBoundsException{
        if (answer.size() != 12) {
            throw new RuntimeException("Solution size not 12!");
        }
        char[] sol = new char[60];
        for(DancingNode node : answer){
            int count = 0;
            while (node.C.name >= 12) {
                count++;
                if (count >= 6) throw new RuntimeException("Unexpected answer size!");
                node = node.R;
            }
            char letter = Pattern.columnToPattern(node.C.name);
            for (DancingNode itr = node.R; itr != node; itr = itr.R) {
                sol[itr.C.name-12] = letter;
            }
        }
        pentominos.checkSolution(sol);
    }

}
