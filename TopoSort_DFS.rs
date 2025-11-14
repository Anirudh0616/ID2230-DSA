struct Node {
    neighbours: Vec<usize>,
}

fn init_graph(num: usize) -> Vec<Node> {
    let mut graph = Vec::with_capacity(num);
    for _ in 0..num {
        graph.push(Node { neighbours: Vec::with_capacity(2)});
    }
    graph
}

fn add_edge(graph: &mut [Node], from: usize, to: usize) {
    graph[from].neighbours.push(to);
}

fn dfs(v: usize, graph: &[Node], visited: &mut [bool], stack: &mut Vec<usize>) {
    visited[v] = true;

    for &neigh in &graph[v].neighbours {
        if !visited[neigh] {
            dfs(neigh, graph, visited, stack);
        }
    }

    stack.push(v);
}

fn topo_sort(graph: &[Node]) -> Vec<usize> {
    let n = graph.len();
    let mut visited = vec![false; n];
    let mut stack = Vec::with_capacity(n);

    for v in 0..n {
        if !visited[v] {
            dfs(v, graph, &mut visited, &mut stack);
        }
    }

    stack.reverse();
    stack
}


fn main() {
    let n = 6;
    let mut graph = init_graph(n);

    add_edge(&mut graph, 0, 1);
    add_edge(&mut graph, 0, 2);
    add_edge(&mut graph, 1, 3);
    add_edge(&mut graph, 2, 3);
    add_edge(&mut graph, 3, 4);
    add_edge(&mut graph, 3, 5);
    add_edge(&mut graph, 4, 5);

    let order = topo_sort(&graph);

    print!("Topological Sort: ");
    for v in order {
        print!("{v} ");
    }
    println!();
}
