import java.util.ArrayList;
import java.util.Scanner;

import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;
import java.util.regex.*;

enum Color {
    RED, GREEN
}

abstract class Tree {

    private int value;
    private Color color;
    private int depth;

    public Tree(int value, Color color, int depth) {
        this.value = value;
        this.color = color;
        this.depth = depth;
    }

    public int getValue() {
        return value;
    }

    public Color getColor() {
        return color;
    }

    public int getDepth() {
        return depth;
    }

    public abstract void accept(TreeVis visitor);
}

class TreeNode extends Tree {

    private ArrayList<Tree> children = new ArrayList<>();

    public TreeNode(int value, Color color, int depth) {
        super(value, color, depth);
    }

    public void accept(TreeVis visitor) {
        visitor.visitNode(this);

        for (Tree child : children) {
            child.accept(visitor);
        }
    }

    public void addChild(Tree child) {
        children.add(child);
    }
}

class TreeLeaf extends Tree {

    public TreeLeaf(int value, Color color, int depth) {
        super(value, color, depth);
    }

    public void accept(TreeVis visitor) {
        visitor.visitLeaf(this);
    }
}

abstract class TreeVis {
    public abstract int getResult();
    public abstract void visitNode(TreeNode node);
    public abstract void visitLeaf(TreeLeaf leaf);
}

class SumInLeavesVisitor extends TreeVis {
    public int getResult() {
      	//implement this
        return 0;
    }

    public void visitNode(TreeNode node) {
      	//implement this
    }

    public void visitLeaf(TreeLeaf leaf) {
      	//implement this
    }
}

class ProductOfRedNodesVisitor extends TreeVis {
    public int getResult() {
      	//implement this
        return 1;
    }

    public void visitNode(TreeNode node) {
      	//implement this
    }

    public void visitLeaf(TreeLeaf leaf) {
      	//implement this
    }
}

class FancyVisitor extends TreeVis {
    public int getResult() {
      	//implement this
        return 0;
    }

    public void visitNode(TreeNode node) {
    	//implement this
    }

    public void visitLeaf(TreeLeaf leaf) {
    	//implement this
    }
}

public class SolutionVisitator {
    private static int[] values;
    private static int[] colors;
    private static HashMap<Integer, HashSet<Integer>> adjList;

    public static Tree solve() {
        //read the tree from STDIN and return its root as a return value of this function
        Scanner input = new Scanner(System.in);
        int N = input.nextInt();
        values = new int[N];
        colors = new int[N];
        for (int it = 0; it < N; it++) {
            values[it] = input.nextInt();
        }
        for (int it = 0; it < N; it++) {
            colors[it] = input.nextInt();
        }
        int u = 0, v = 0;
        adjList = new HashMap<Integer, HashSet<Integer>>();
        while (input.hasNextInt()) {
            u = input.nextInt();
            v = input.nextInt();

            if (adjList.get(u) == null) {
                adjList.put(u, new HashSet<Integer>());
            }
            adjList.get(u).add(v);
        }
        Tree root;


        return null;
    }

    public static void main(String[] args) {
        Tree root = solve();
        SumInLeavesVisitor vis1 = new SumInLeavesVisitor();
        ProductOfRedNodesVisitor vis2 = new ProductOfRedNodesVisitor();
        FancyVisitor vis3 = new FancyVisitor();

        root.accept(vis1);
        root.accept(vis2);
        root.accept(vis3);

        int res1 = vis1.getResult();
        int res2 = vis2.getResult();
        int res3 = vis3.getResult();

        System.out.println(res1);
        System.out.println(res2);
        System.out.println(res3);
	}
}
