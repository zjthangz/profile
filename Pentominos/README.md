# Solving Pentomino Puzzle using Dancing Links Algorithm 

## INTRODUCTION:
"A pentomino (or 5-omino) is a polyomino of order 5, that is, a polygon in the plane made of 5 equal-sized squares connected edge-to-edge". With 5 squares, we could produce 12 different shapes, each marked by a letter.
Note that for a shape, there are multiple ways to be placed into a box. For example, by doing rotation and reflections, pentomino "F" has 8 ways to be fit into the box.
## ALGORITHMS:
1. Backtracking 
The intuitive and natural way of solving this problem is doing Depth First Search (DFS). We try place one pentomino into the box first, and then another, continue this process (recursively call the same function for each pentomino) until all pentominos have been inserted, then we output the solution, or there is no room to put the current pentomino in hand, then we backtrack. It is only possible to print all solution by travering all possible places using backtracking, and this thought is still used in the following algorithms. 
2. Exact cover 
The pentomino puzzle can be transferred to an Exact Cover problem. The Exact Cover problem is, "given a matrix of ones and zeros; that is, where the cells contain either "1" or "0" (true or false), work out which rows of the matrix form a set that contains exactly one "1" in each column. 
Knuth's algorithm X solves the exact cover problem in the similar pattern. Starting from the first column, find a row that has 1 in that column, include this row into partial solution, then for all other rows that have 1 in the columns in which this row also has 1, delete them from matrix, and then recurs, if at some point we cannot find a row that contains 1 for the iterating column, backtrack. Algorithm X is thus still uses depth first search. 
3. Dancing links 
Each matrix value is transferred into a 4-way doubly connected node in the Dancing Links. 
Each column has a header, and there is another "h" node, in which stores the remaining number of columns. So if we pick a column, we remove the column header by changing the pointers for its left and right neighbor. Then all rows have node in that column should be remove from the matrix because we only pick one from them. So for each node within these rows, we change their upper and below neighbor. 
Then we pick one node in the column, then for all nodes in the row this node belongs to, their existence means those columns they belong are covered as well. So we do the "cover" operation on these columns. Because these operations only modify the pointers of nodes remain in the links, nodes that are removed still have access to their neighbor when they are removed, so through backtracking we can put each node back one by one and recover the matrix. 
Dancing Links algorithm saves space because we don't need store 0, in the problem of Pentomino puzzle, each row has only 6 "1"s but 66 "0"s, thus DLX saves majority of data, meanwhile we do not need search every row at any column, which saves running time as well. 
## IMPLEMENTATION:
1. Define patterns for 12 pieces (8+2+8+8+8+4+4+4+4+1+8+4=63). 
	2. Create a board(box) with possibly several barriers. 
	3. Calculated the set of all possible positions of pieces within the board. 
	4. Generate matrix based on above. 
	5. Transfer the matrix to Dancing Links. 
	6. Run DLX to find solution or do backtrack. 
	7. Put each solution into a hash map, together with its rotation, reverse to avoid duplication. 
	8. Output solutions.   





