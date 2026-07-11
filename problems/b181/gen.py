import sys
import random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    n = rng.randint(2, 10)
    max_m = n * (n - 1) // 2
    m = rng.randint(n - 1, max_m)
    
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))
            
    nodes = list(range(1, n + 1))
    rng.shuffle(nodes)
    
    tree_edges = set()
    for i in range(1, n):
        u, v = nodes[i-1], nodes[i]
        if u > v:
            u, v = v, u
        tree_edges.add((u, v))
        
    remaining_edges = [e for e in all_edges if e not in tree_edges]
    rng.shuffle(remaining_edges)
    
    extra_edges = remaining_edges[:m - (n - 1)]
    selected_edges = list(tree_edges) + extra_edges
    rng.shuffle(selected_edges)
    
    print(f"{n}  {m}")
    for u, v in selected_edges:
        cost = rng.randint(1, 100)
        print(f"W{u} W{v} {cost}")

if __name__ == "__main__":
    main()
