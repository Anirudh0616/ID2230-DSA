
type Graph = Vec<Vec<usize>>;

fn init_graph(n: usize) -> Graph {
    vec![Vec::new(); n]
}

fn add_edge(graph: &mut Graph, from: usize, to: usize){
    graph[from].push(to);
}

fn dfs(v: usize, graph: &Graph, visited: &mut [bool], stack: &mut Vec<usize>) {
    visited[v] = true;
    for &nbr in &graph[v] {
        if !visited[nbr] {
            dfs(nbr, graph, visited, stack);
        }
    }
    stack.push(v);
}

fn reverse_graph(graph: &Graph) -> Graph {
    let n = graph.len();
    let mut rev = init_graph(n);

    for (node, neighs) in graph.iter().enumerate() { // Gives a list with ( node , it's neighbours )
        for &v in neighs {
            rev[v].push(node);
        }
    }

    rev
}

fn rev_dfs(v: usize, graph: &Graph, visited: &mut [bool], comp: &mut Vec<usize>) {
    visited[v] = true;
    comp.push(v);

    for &neigh in &graph[v] {
        if !visited[neigh] {
            rev_dfs(neigh, graph, visited, comp);
        }
    }
}

fn kosaraju(graph: &Graph) -> Vec<Vec<usize>> {
    let n = graph.len();
    let mut visited = vec![false; n];
    let mut stack = Vec::with_capacity(n);

    for v in 0..n {
        if !visited[v] {
            dfs(v, graph, &mut visited, &mut stack);
        }
    }

    let rev_graph = reverse_graph(graph);

    let mut visited = vec![false; n];
    let mut sccs = Vec::new();

    while let Some(v) = stack.pop() {
        if !visited[v] {
            let mut comp = Vec::new();
            rev_dfs(v, &rev_graph, &mut visited, &mut comp);
            sccs.push(comp);
        }
    }

    sccs
}

fn main() {
    let mut graph = init_graph(6);

    add_edge(&mut graph, 0, 1);
    add_edge(&mut graph, 1, 2);
    add_edge(&mut graph, 2, 0);
    add_edge(&mut graph, 1, 3);
    add_edge(&mut graph, 3, 4);
    add_edge(&mut graph, 4, 5);
    add_edge(&mut graph, 5, 3);

    let comps = kosaraju(&graph);

    for comp in comps {
        print!("SCC:");
        for v in comp {
            print!(" {}", v);
        }
        println!();
    }
}
