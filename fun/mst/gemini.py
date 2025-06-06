import math
import itertools
import matplotlib.pyplot as plt
import numpy as np
import copy
import time  # To measure execution time


# -------------------------------------
# Helper Functions (distance, Union-Find, MST - unchanged from previous)
# -------------------------------------
def distance(p1, p2):
    """Calculates the Euclidean distance between two 2D points."""
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)


# --- Union-Find ---
def find_set(parent, i):
    if parent[i] == i:
        return i
    # Path compression
    parent[i] = find_set(parent, parent[i])
    return parent[i]


def union_sets(parent, rank, i, j):
    i_id = find_set(parent, i)
    j_id = find_set(parent, j)
    if i_id != j_id:
        # Union by rank
        if rank[i_id] > rank[j_id]:
            parent[j_id] = i_id
        else:
            parent[i_id] = j_id
            if rank[i_id] == rank[j_id]:
                rank[j_id] += 1
        return True
    return False


# --- End Union-Find ---


def calculate_mst(points):
    """Calculates the Minimum Spanning Tree (MST) using Kruskal's algorithm."""
    num_points = len(points)
    if num_points < 2:
        return [], 0

    edges = []
    for i in range(num_points):
        for j in range(i + 1, num_points):
            dist = distance(points[i], points[j])
            edges.append({"u": i, "v": j, "weight": dist})

    edges.sort(key=lambda x: x["weight"])

    parent = list(range(num_points))
    rank = [0] * num_points
    mst_edges = []
    mst_cost = 0
    edges_count = 0

    for edge in edges:
        if union_sets(parent, rank, edge["u"], edge["v"]):
            mst_edges.append((points[edge["u"]], points[edge["v"]]))
            mst_cost += edge["weight"]
            edges_count += 1
            if edges_count == num_points - 1:
                break

    return mst_edges, mst_cost


# -------------------------------------
# Steiner Tree - Fixed Topology Optimization (mostly unchanged)
# -------------------------------------
def optimize_steiner_points(
    terminals, steiner_initial, topology, max_iterations=500, tolerance=1e-6
):
    """Optimizes Steiner point locations for a GIVEN topology."""
    if (
        not steiner_initial
    ):  # If k=0, no optimization needed, topology is just MST edges
        # This case should ideally be handled before calling optimize
        # For safety, return empty results if called with no initial points
        return [], [], 0

    num_terminals = len(terminals)
    num_steiner = len(steiner_initial)
    # Use numpy arrays for easier vector math, ensure they are float
    steiner_points = np.array(steiner_initial, dtype=float)
    terminals_np = np.array(terminals, dtype=float)  # Keep terminals fixed

    # Pre-build neighbor lookup for efficiency
    steiner_neighbors = [[] for _ in range(num_steiner)]
    point_map_np = {"T": terminals_np, "S": steiner_points}  # Use numpy arrays

    for edge_idx1, edge_type1, edge_idx2, edge_type2 in topology:
        # Add neighbor info to steiner points
        if edge_type1 == "S":
            neighbor_type = edge_type2
            neighbor_idx = edge_idx2
            steiner_idx = edge_idx1
            steiner_neighbors[steiner_idx].append(
                {"type": neighbor_type, "idx": neighbor_idx}
            )
        if edge_type2 == "S":
            neighbor_type = edge_type1
            neighbor_idx = edge_idx1
            steiner_idx = edge_idx2
            # Avoid duplicating if S-S connection
            if not (edge_type1 == "S" and edge_type1 == edge_type2):
                steiner_neighbors[steiner_idx].append(
                    {"type": neighbor_type, "idx": neighbor_idx}
                )

    for iteration in range(max_iterations):
        steiner_points_old = np.copy(steiner_points)
        total_change_sq = 0  # Use squared change to avoid sqrt

        for s_idx in range(num_steiner):
            numerator = np.zeros(2)  # [x, y]
            denominator = 0.0
            has_valid_neighbor = False

            for neighbor_info in steiner_neighbors[s_idx]:
                neighbor_type = neighbor_info["type"]
                neighbor_idx = neighbor_info["idx"]

                # Get neighbor coordinates (use potentially updated Steiner point positions)
                if neighbor_type == "T":
                    neighbor_coord = terminals_np[neighbor_idx]
                else:  # neighbor_type == 'S'
                    neighbor_coord = steiner_points[
                        neighbor_idx
                    ]  # Use current iteration's positions

                dist_sq = np.sum((steiner_points_old[s_idx] - neighbor_coord) ** 2)
                dist = math.sqrt(dist_sq)

                # Avoid division by zero or near-zero
                if dist < 1e-9:
                    # If a Steiner point practically overlaps with a neighbor,
                    # its position is effectively determined by that neighbor.
                    # We can skip the update for this iteration or handle carefully.
                    # Simplest: skip this neighbor's contribution if distance is tiny.
                    # A more robust approach might involve analytical solutions for overlaps.
                    continue

                inv_dist = 1.0 / dist
                numerator += neighbor_coord * inv_dist
                denominator += inv_dist
                has_valid_neighbor = True

            # Update position if neighbors provide valid force
            if has_valid_neighbor and denominator > 1e-9:
                steiner_points[s_idx] = numerator / denominator
            # else: keep the old position if no valid neighbors or zero denominator

        # Check convergence
        total_change_sq = np.sum((steiner_points - steiner_points_old) ** 2)

        if total_change_sq < (tolerance**2) * num_steiner:
            # print(f"    Converged in {iteration + 1} iterations.")
            break
    # else: # Max iterations reached
    #     print(f"    Reached max iterations ({max_iterations}).")

    # Calculate final edges and cost using *final* optimized positions
    final_steiner_edges = []
    final_steiner_cost = 0
    point_map_final = {
        "T": terminals,
        "S": steiner_points.tolist(),
    }  # Convert back to lists/tuples

    for idx1, type1, idx2, type2 in topology:
        try:
            p1_coord = point_map_final[type1][idx1]
            p2_coord = point_map_final[type2][idx2]
            # Ensure coords are tuples for consistency
            p1 = tuple(p1_coord)
            p2 = tuple(p2_coord)
            edge = (p1, p2)
            final_steiner_edges.append(edge)
            final_steiner_cost += distance(p1, p2)
        except (IndexError, KeyError) as e:
            print(
                f"    ERROR calculating final edge cost for topology: {topology}. Details: {e}"
            )
            return [], [], float("inf")  # Return infinity cost for invalid topology

    return steiner_points.tolist(), final_steiner_edges, final_steiner_cost


# -------------------------------------
# NEW: Topology Generation and Main Search Function
# -------------------------------------


def generate_initial_steiner_guesses(terminals, k):
    """Generates simple initial guesses for k Steiner points (e.g., centroid)."""
    if k == 0:
        return []
    # Simple guess: place all initial Steiner points at the centroid of terminals
    centroid_x = sum(p[0] for p in terminals) / len(terminals)
    centroid_y = sum(p[1] for p in terminals) / len(terminals)
    # Add tiny offsets to avoid starting all points at the exact same location
    guesses = []
    for i in range(k):
        offset_x = (i - k / 2) * 0.01  # Small spread
        offset_y = (i - k / 2) * 0.01
        guesses.append((centroid_x + offset_x, centroid_y + offset_y))
    return guesses


def format_topology(topology_edges, n, k):
    """Converts edge list (using combined indices) to the required format."""
    formatted = []
    for u, v in topology_edges:
        type1 = "T" if u < n else "S"
        idx1 = u if u < n else u - n
        type2 = "T" if v < n else "S"
        idx2 = v if v < n else v - n
        formatted.append((idx1, type1, idx2, type2))
    return formatted


def check_topology_validity(formatted_topology, n, k):
    """Checks if the topology connects all n terminals."""
    if n <= 1:
        return True  # Trivial cases

    num_total_nodes = n + k
    adj = [[] for _ in range(num_total_nodes)]
    # Map formatted topology back to combined indices (0..n-1 for T, n..n+k-1 for S)
    for idx1, type1, idx2, type2 in formatted_topology:
        u = idx1 if type1 == "T" else idx1 + n
        v = idx2 if type2 == "T" else idx2 + n
        adj[u].append(v)
        adj[v].append(u)

    # Perform BFS/DFS from terminal 0 to see if all other terminals are reachable
    q = [0]  # Start BFS from terminal 0
    visited = {0}
    terminals_reached = {0} if 0 < n else set()  # Track reached terminals

    head = 0
    while head < len(q):
        curr = q[head]
        head += 1

        # Check if it's a terminal node
        if curr < n:
            terminals_reached.add(curr)

        for neighbor in adj[curr]:
            if neighbor not in visited:
                visited.add(neighbor)
                q.append(neighbor)

    # Check if all terminals (0 to n-1) were reached
    return len(terminals_reached) == n


def generate_spanning_tree_topologies(n, k):
    """
    Generates all possible spanning tree topologies on n terminals and k Steiner points
    using backtracking. Yields edge lists [(u, v), ...].
    Indices 0..n-1 are terminals, n..n+k-1 are Steiner points.
    """
    num_nodes = n + k
    if num_nodes <= 1:  # Handle cases with 0 or 1 total points
        if num_nodes == 1:
            yield []  # Empty topology for single node
        return

    nodes = list(range(num_nodes))
    all_possible_edges = list(itertools.combinations(nodes, 2))

    parent = list(range(num_nodes))  # For Union-Find during generation
    rank = [0] * num_nodes  # For Union-Find rank optimization

    # Local U-F functions for this generator
    gen_parent = list(range(num_nodes))
    gen_rank = [0] * num_nodes
    num_components = num_nodes

    def gen_find(i):
        if gen_parent[i] == i:
            return i
        gen_parent[i] = gen_find(gen_parent[i])
        return gen_parent[i]

    def gen_union(i, j):
        nonlocal num_components
        root_i = gen_find(i)
        root_j = gen_find(j)
        if root_i != root_j:
            # Union by rank
            if gen_rank[root_i] < gen_rank[root_j]:
                gen_parent[root_i] = root_j
            elif gen_rank[root_i] > gen_rank[root_j]:
                gen_parent[root_j] = root_i
            else:
                gen_parent[root_j] = root_i
                gen_rank[root_i] += 1
            num_components -= 1  # Decrement component count
            return True
        return False

    current_edges = []
    num_edges_needed = num_nodes - 1

    # Backtracking function
    def backtrack(edge_idx):
        nonlocal gen_parent, gen_rank, num_components  # Allow modification

        if len(current_edges) == num_edges_needed:
            # Found a potential spanning tree if it connects all components
            # The num_components check ensures connectivity implicitly here
            if num_components == 1:
                yield list(current_edges)
            return

        if edge_idx >= len(all_possible_edges):
            # No more edges to consider
            return

        # Get current edge
        u, v = all_possible_edges[edge_idx]

        # --- Try including the edge ---
        # Store state *before* potential union
        original_parent_state = list(gen_parent)
        original_rank_state = list(gen_rank)
        original_num_components = num_components

        root_u_before = gen_find(u)  # Find roots before potential union
        root_v_before = gen_find(v)

        if root_u_before != root_v_before:  # Check if it connects different components
            # Make the change
            gen_union(u, v)  # This changes parent, rank, num_components
            current_edges.append((u, v))

            # Recurse
            yield from backtrack(edge_idx + 1)

            # Backtrack: remove edge and restore state
            current_edges.pop()
            gen_parent = original_parent_state
            gen_rank = original_rank_state
            num_components = original_num_components
        # else: Edge creates a cycle, do nothing for the 'include' path

        # --- Try excluding the edge ---
        # Only recurse if there's still a chance to form a spanning tree
        # Pruning: Check if remaining edges are enough to connect remaining components
        remaining_edges_count = len(all_possible_edges) - (edge_idx + 1)
        edges_still_needed = num_edges_needed - len(current_edges)
        components_to_connect = (
            num_components - 1
        )  # Need components-1 edges to connect them

        # We need at least 'components_to_connect' more edges among the remaining options
        # A simpler check: ensure we have enough edges overall remaining
        if remaining_edges_count >= edges_still_needed:
            yield from backtrack(edge_idx + 1)

    # Initial call to start generation
    yield from backtrack(0)


def find_minimal_steiner_tree(terminals, max_k=None):
    """
    Finds the Minimal Steiner Tree by enumerating topologies.

    Args:
        terminals (list): List of terminal point coordinates [(x, y), ...].
        max_k (int, optional): Maximum number of Steiner points to consider (0 to max_k).
                               Defaults to n-2 if None. Useful for limiting runtime.

    Returns:
        tuple: (best_steiner_points, best_steiner_edges, best_cost)
    """
    n = len(terminals)
    if n <= 1:
        return [], [], 0
    if n == 2:  # MST is the only possibility and is optimal
        mst_edges, mst_cost = calculate_mst(terminals)
        return [], mst_edges, mst_cost

    # Determine the maximum k to check
    limit_k = n - 2 if max_k is None else min(max_k, n - 2)
    if limit_k < 0:
        limit_k = 0  # Ensure k is not negative

    print(f"Starting Minimal Steiner Tree search for {n} terminals.")
    print(f"Will check topologies with k = 0 up to k = {limit_k} Steiner points.")
    print("WARNING: This process can be extremely slow for n > 5.")

    start_time = time.time()

    best_cost = float("inf")
    best_steiner_points = []
    best_steiner_edges = []
    best_k = -1
    best_topology_repr = "N/A"  # For info

    # Case k=0: MST
    mst_edges, mst_cost = calculate_mst(terminals)
    print(f"\n--- Analyzing k = 0 (MST) ---")
    print(f"    MST cost: {mst_cost:.6f}")
    if mst_cost < best_cost:
        best_cost = mst_cost
        best_steiner_points = []
        best_steiner_edges = mst_edges
        best_k = 0
        best_topology_repr = "MST"

    total_topologies_tested = 0

    # Iterate through possible number of Steiner points
    for k in range(1, limit_k + 1):
        print(f"\n--- Analyzing k = {k} Steiner points ---")
        # Generate initial guesses for k Steiner points
        initial_steiner_guesses = generate_initial_steiner_guesses(terminals, k)

        topology_generator = generate_spanning_tree_topologies(n, k)
        topology_count_for_k = 0

        for topology_edges in topology_generator:
            topology_count_for_k += 1
            total_topologies_tested += 1

            if total_topologies_tested % 1000 == 0:  # Progress indicator
                elapsed = time.time() - start_time
                print(
                    f"    Tested {total_topologies_tested} topologies so far... (k={k}, current topology #{topology_count_for_k}, elapsed {elapsed:.2f}s)"
                )

            # Convert topology to the required format
            formatted_topology = format_topology(topology_edges, n, k)

            # Basic check: Does this topology connect all terminals?
            # This check is vital to avoid optimizing invalid structures.
            if not check_topology_validity(formatted_topology, n, k):
                continue  # Skip this topology

            # Optimize this specific topology
            current_initial_guesses = copy.deepcopy(
                initial_steiner_guesses
            )  # Use fresh guesses
            try:
                # Lower iterations/tolerance per topology maybe?
                optimized_points, optimized_edges, current_cost = (
                    optimize_steiner_points(
                        terminals,
                        current_initial_guesses,
                        formatted_topology,
                        max_iterations=300,  # Reduced iterations per topology
                        tolerance=1e-5,  # Slightly relaxed tolerance
                    )
                )
            except Exception as e:
                # print(f"      Optimization failed or error in topology: {e}") # Debugging
                continue  # Skip if optimization fails

            # Compare with the best found so far
            if optimized_edges and current_cost < best_cost:
                # Small epsilon comparison for floating point
                if not math.isclose(
                    current_cost, best_cost, rel_tol=1e-9, abs_tol=1e-9
                ):
                    print(
                        f"    * New best cost found: {current_cost:.6f} (k={k}, topology #{topology_count_for_k})"
                    )
                    best_cost = current_cost
                    best_steiner_points = optimized_points
                    best_steiner_edges = optimized_edges
                    best_k = k
                    best_topology_repr = f"k={k}, Topology #{topology_count_for_k}"  # Store info about the best

        print(
            f"    Finished analyzing {topology_count_for_k} potentially valid topologies for k={k}."
        )

    end_time = time.time()
    print(f"\n--- Minimal Steiner Tree Search Complete ---")
    print(f"Total topologies tested (approx): {total_topologies_tested}")
    print(f"Total time: {end_time - start_time:.2f} seconds")
    if best_k != -1:
        print(
            f"Best solution found uses k = {best_k} Steiner points ({best_topology_repr})."
        )
        print(f"Minimal Cost: {best_cost:.6f}")
        if best_steiner_points:
            print(
                f"Optimal Steiner Point Locations: {[(float(f'{p[0]:.4f}'), float(f'{p[1]:.4f}')) for p in best_steiner_points]}"
            )
    else:
        print("No valid Steiner tree solution found (should not happen if n>=2).")

    return best_steiner_points, best_steiner_edges, best_cost


# -------------------------------------
# Visualization Function (unchanged)
# -------------------------------------
def plot_trees(
    terminals, mst_edges, steiner_points=None, steiner_edges=None, title_suffix=""
):
    """Visualizes points, MST, and Steiner tree using Matplotlib."""
    plt.figure(figsize=(10, 8))

    # Plot Terminals
    term_x = [p[0] for p in terminals]
    term_y = [p[1] for p in terminals]
    plt.scatter(term_x, term_y, c="blue", label="Terminals", s=100, zorder=5)
    for i, txt in enumerate(range(len(terminals))):
        plt.annotate(
            f"T{i}",
            (term_x[i], term_y[i]),
            textcoords="offset points",
            xytext=(0, 10),
            ha="center",
        )

    # Plot MST Edges (optional display, maybe confusing with Steiner Tree)
    # if mst_edges:
    #    for edge in mst_edges:
    #        plt.plot([edge[0][0], edge[1][0]], [edge[0][1], edge[1][1]], 'g--', linewidth=1.0, label='MST Edge' if 'MST Edge' not in plt.gca().get_legend_handles_labels()[1] else "")

    # Plot Steiner Tree Edges and Points (if found)
    if steiner_edges:
        # Plot Steiner Points
        if steiner_points:
            steiner_x = [p[0] for p in steiner_points]
            steiner_y = [p[1] for p in steiner_points]
            plt.scatter(
                steiner_x,
                steiner_y,
                c="red",
                marker="s",
                label="Steiner Points",
                s=100,
                zorder=5,
            )
            for i, txt in enumerate(range(len(steiner_points))):
                plt.annotate(
                    f"S{i}",
                    (steiner_x[i], steiner_y[i]),
                    textcoords="offset points",
                    xytext=(0, 10),
                    ha="center",
                    color="red",
                )

        # Plot Steiner Edges
        for edge in steiner_edges:
            plt.plot(
                [edge[0][0], edge[1][0]],
                [edge[0][1], edge[1][1]],
                "r-",
                linewidth=2.0,
                label=(
                    "Steiner Edge"
                    if "Steiner Edge" not in plt.gca().get_legend_handles_labels()[1]
                    else ""
                ),
            )
        cost = sum(distance(e[0], e[1]) for e in steiner_edges)
        plt.title(f"Minimal Steiner Tree (Cost: {cost:.4f}) {title_suffix}")
    else:  # If no Steiner tree found/calculated, show MST
        if mst_edges:
            for edge in mst_edges:
                plt.plot(
                    [edge[0][0], edge[1][0]],
                    [edge[0][1], edge[1][1]],
                    "g-",
                    linewidth=2.0,
                    label=(
                        "MST Edge"
                        if "MST Edge" not in plt.gca().get_legend_handles_labels()[1]
                        else ""
                    ),
                )
            cost = sum(distance(e[0], e[1]) for e in mst_edges)
            plt.title(f"Minimum Spanning Tree (Cost: {cost:.4f}) {title_suffix}")

    plt.xlabel("X Coordinate")
    plt.ylabel("Y Coordinate")
    plt.legend()
    plt.grid(True)
    plt.axis("equal")
    plt.show()


# -------------------------------------
# Main Execution
# -------------------------------------
if __name__ == "__main__":
    # --- Input Points ---
    # Example: 4 points forming a rectangle (optimal has 2 Steiner points)
    terminal_points = [(0, 0), (0, 3), (5, 0), (5, 3)]  # n=4
    # Example: 3 points forming equilateral triangle (optimal has 1 Steiner point at center)
    # terminal_points = [(0, 0), (4, 0), (2, 3.464)]  # n=3
    # Example: 5 points (more complex)
    # terminal_points = [(1, 1), (1, 7), (8, 1), (8, 7), (4.5, 4)]  # n=5

    # --- User Input Option ---
    # terminal_points = []
    # print("Enter point coordinates (x y), one per line. Type 'done' to finish:")
    # while True:
    #     try:
    #         line = input().strip()
    #         if line.lower() == 'done': break
    #         x, y = map(float, line.split())
    #         terminal_points.append((x, y))
    #     except ValueError: print("Invalid input. Use 'x y' format or 'done'.")
    #     except EOFError: break
    # if len(terminal_points) < 2:
    #     print("Need at least two points.")
    #     exit()

    print(f"\nInput Terminal Points: {terminal_points}")
    n_terminals = len(terminal_points)

    # --- Calculate MST (for comparison/baseline) ---
    mst_edges, mst_cost = calculate_mst(terminal_points)
    print(f"\n--- MST Calculation ---")
    print(f"MST Cost: {mst_cost:.6f}")

    # --- Find Minimal Steiner Tree ---
    # Set max_k to limit runtime if needed, e.g., max_k=1 means only try 0 and 1 Steiner points.
    # For n=5, max possible k is 3 (n-2). For n=4, max k=2.
    # Setting max_k=None uses the default n-2 limit.
    # WARNING: Even max_k=2 can be slow if n is larger (e.g., n=6, k=2)
    limit_k_input = None  # or set to 0, 1, 2, etc. to restrict search
    if n_terminals >= 6:
        print(
            "\nWARNING: n >= 6 detected. Full search (k up to n-2) will be VERY slow."
        )
        try:
            k_limit_str = input(
                f"Enter max k to check (0 to {n_terminals-2}, press Enter for full search): "
            )
            if k_limit_str:
                limit_k_input = int(k_limit_str)
                if not (0 <= limit_k_input <= n_terminals - 2):
                    print(f"Invalid k. Using default limit k={n_terminals-2}.")
                    limit_k_input = None
        except ValueError:
            print("Invalid input. Using default limit.")
            limit_k_input = None

    best_s_points, best_s_edges, best_s_cost = find_minimal_steiner_tree(
        terminal_points, max_k=limit_k_input
    )

    # --- Visualization ---
    print("\nGenerating visualization...")
    # Decide what to plot: the best Steiner tree found, or MST if that was best (k=0)
    if best_s_edges:
        plot_trees(
            terminal_points,
            mst_edges,
            best_s_points,
            best_s_edges,
            title_suffix=f"(k={len(best_s_points)})",
        )
    else:
        print("Could not find a valid solution to plot.")
