import heapq
from itertools import permutations
import tkinter as tk
from tkinter import ttk, messagebox
from collections import defaultdict

# --- 1. DATA STRUCTURE: GRAPH AND POSITIONS ---

# The graph is represented as an Adjacency List (Node: {Neighbor: Weight})
GRAPH = {
    'A': {'B': 8, 'D': 12, 'G': 10},  # A: Depot (Start)
    'B': {'A': 8, 'C': 10, 'E': 15, 'G': 9},
    'C': {'B': 10, 'E': 7, 'F': 9, 'H': 4},
    'D': {'A': 12, 'E': 11, 'I': 15},
    'E': {'B': 15, 'C': 7, 'D': 11, 'F': 6},
    'F': {'C': 9, 'E': 6, 'J': 8},
    
    # --- NEW STOPS ---
    'G': {'A': 10, 'B': 9, 'H': 5},        # G: University Campus
    'H': {'G': 5, 'C': 4, 'I': 13, 'J': 7}, # H: Shopping Mall
    'I': {'D': 15, 'H': 13, 'J': 6},       # I: Port Area
    'J': {'F': 8, 'H': 7, 'I': 6}          # J: Old Town
    # --- END NEW STOPS ---
}
START_NODE = 'A'

# Map Node IDs to full names
LOCATION_NAMES = {
    'A': 'Depot (Start)', 'B': 'Suburb West', 'C': 'City Center',
    'D': 'Industrial', 'E': 'Residential', 'F': 'New Development',
    # --- NEW NAMES ---
    'G': 'University Campus', 'H': 'Shopping Mall', 
    'I': 'Port Area', 'J': 'Old Town'
    # --- END NEW NAMES ---
}

# Coordinates for drawing the map on the Canvas (400x400 region)
NODE_POSITIONS = {
    'A': (100, 350),  # Depot (Bottom Left)
    'B': (200, 50),   # Suburb West (Top Middle)
    'C': (350, 150),  # City Center (Right)
    'D': (50, 150),   # Industrial (Left)
    'E': (300, 300),  # Residential (Bottom Right)
    'F': (200, 250),  # New Development (Center)
    # --- NEW POSITIONS ---
    'G': (150, 300),  # University Campus
    'H': (300, 100),  # Shopping Mall
    'I': (50, 300),   # Port Area
    'J': (350, 50)    # Old Town
    # --- END NEW POSITIONS ---
}

# All unique edges (for drawing the background road network only once)
ALL_EDGES = set()
for u, neighbors in GRAPH.items():
    for v in neighbors.keys():
        # Ensure we only store (u, v) where u < v to avoid duplicates
        edge = tuple(sorted((u, v)))
        ALL_EDGES.add(edge)

# Available stops for selection (excluding the start depot)
AVAILABLE_STOPS = sorted([node for node in GRAPH if node != START_NODE])

# --- 2. CORE ALGORITHM: DIJKSTRA'S & PATHFINDING ---

def dijkstras_algorithm(graph, start_node):
    """Finds shortest distances and predecessors from a start node."""
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    predecessors = {node: None for node in graph}
    priority_queue = [(0, start_node)]

    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_distance > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node].items():
            new_distance = current_distance + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                # Correctly assign the current node as the predecessor
                predecessors[neighbor] = current_node 
                heapq.heappush(priority_queue, (new_distance, neighbor))

    return distances, predecessors

def reconstruct_path(start_node, end_node, predecessors):
    """Reconstructs the shortest path from start to end."""
    path = []
    current = end_node
    while current is not None:
        path.insert(0, current)
        if current == start_node:
            return path
        current = predecessors.get(current)
    
    return path if path and path[0] == start_node else None

def find_shortest_tour(start_node, delivery_stops, graph):
    """Calculates the shortest route visiting all delivery stops."""
    if not delivery_stops:
        return None

    shortest_tour = None
    min_distance = float('inf')
    dijkstra_cache = {}

    stop_permutations = list(permutations(delivery_stops))

    for permutation in stop_permutations:
        itinerary = [start_node] + list(permutation)
        current_distance = 0
        full_path_nodes = []
        segment_details_list = []
        is_valid_tour = True

        for i in range(len(itinerary) - 1):
            start = itinerary[i]
            end = itinerary[i+1]

            if start not in dijkstra_cache:
                dijkstra_cache[start] = dijkstras_algorithm(graph, start)
            
            distances, predecessors = dijkstra_cache[start]
            
            distance_segment = distances.get(end, float('inf'))
            path_segment = reconstruct_path(start, end, predecessors)

            if distance_segment == float('inf') or not path_segment:
                is_valid_tour = False
                break
            
            current_distance += distance_segment
            
            # Store segment detail
            segment_details_list.append({
                'start': start,
                'end': end,
                'path': path_segment,
                'distance': distance_segment
            })
            
            if i == 0:
                full_path_nodes.extend(path_segment)
            else:
                full_path_nodes.extend(path_segment[1:])

        if is_valid_tour and current_distance < min_distance:
            min_distance = current_distance
            shortest_tour = {
                'distance': min_distance,
                'path_nodes': itinerary, 
                'full_path': full_path_nodes,
                'segment_details': segment_details_list
            }

    return shortest_tour

# --- 3. TKINTER GUI AND MAP DRAWING ---

class DeliveryPlannerApp:
    def __init__(self, master):
        self.master = master
        master.title("Delivery Route Planner (Dijkstra's + TSP)")
        # Increased and maintained height for detailed results
        master.geometry("550x850") 
        master.resizable(False, False)

        # Set up styles
        style = ttk.Style()
        style.theme_use('clam')
        style.configure('TFrame', background='#f7f7f7')
        style.configure('TLabel', background='#f7f7f7', font=('Arial', 10))
        style.configure('TButton', font=('Arial', 10, 'bold'), padding=8)

        self.checkbox_vars = {} 
        self.setup_ui()
        # Draw initial map
        self.draw_map([]) 

    def setup_ui(self):
        # --- Map Frame (Canvas) ---
        # Reduced external padding
        map_frame = ttk.LabelFrame(self.master, text="Visual Map", padding="10", borderwidth=2, relief="groove")
        map_frame.pack(padx=10, pady=(5, 3), fill='x') 
        
        self.canvas = tk.Canvas(map_frame, width=450, height=400, bg='#ffffff', highlightthickness=1, highlightbackground="grey")
        self.canvas.pack()

        # --- Input Frame (1. Select Delivery Orders + 2. Calculate Button) ---
        # Reduced external padding
        input_frame = ttk.LabelFrame(self.master, text="1. Select Delivery Orders / 2. Calculate Route", padding="10", borderwidth=2, relief="groove")
        input_frame.pack(padx=10, pady=3, fill='x')

        # Reduced internal padding
        ttk.Label(input_frame, text=f"Start Location: {LOCATION_NAMES[START_NODE]} ({START_NODE})", 
                  font=('Arial', 10, 'bold'), foreground='#004d40').pack(anchor='w', pady=(0, 5))

        # Checkbox Grid 
        checkbox_frame = ttk.Frame(input_frame)
        checkbox_frame.pack(fill='x', padx=2, pady=(2, 5)) # Reduced padding
        
        cols = 3 
        for i, node_id in enumerate(AVAILABLE_STOPS):
            var = tk.BooleanVar(value=False)
            self.checkbox_vars[node_id] = var
            name = LOCATION_NAMES[node_id]
            
            chk = ttk.Checkbutton(checkbox_frame, text=f"{node_id}: {name}", variable=var, style='TCheckbutton')
            
            row = i // cols
            col = i % cols
            chk.grid(row=row, column=col, sticky='w', padx=10, pady=2) # Reduced grid padding


        # --- Calculation Button (Placed inside the input frame) ---
        calc_button = ttk.Button(input_frame, text="2. Find Shortest Delivery Tour", command=self.calculate_route, style='TButton')
        calc_button.pack(pady=(3, 0), fill='x') # Reduced pady
        
        # --- Results Frame (3. Optimal Route Results) ---
        # Reduced external padding
        results_frame = ttk.LabelFrame(self.master, text="3. Optimal Route Results", padding="10", borderwidth=2, relief="groove")
        results_frame.pack(padx=10, pady=(3, 5), fill='both', expand=True) 

        self.sequence_label = ttk.Label(results_frame, text="Optimal Sequence: Select Stops", wraplength=480, font=('Arial', 10, 'bold'), foreground='#757575')
        self.sequence_label.pack(anchor='w', pady=(3, 3)) # Reduced pady

        self.distance_label = ttk.Label(results_frame, text="Total Distance: 0.0 km", font=('Arial', 16, 'bold'), foreground='#d32f2f')
        self.distance_label.pack(anchor='w', pady=(3, 5)) # Reduced pady
        
        ttk.Label(results_frame, text="Full Node Path (A → ...):", font=('Arial', 10, 'bold')).pack(anchor='w')
        
        # Path Text Area
        self.path_text = tk.Text(results_frame, height=5, wrap=tk.WORD, state=tk.DISABLED, font=('Courier', 9), relief=tk.FLAT, bg='#eeeeee')
        self.path_text.pack(fill='both', expand=True, pady=(3, 0)) # Reduced pady

        # New: Segment Details (Minimal Path & Distance in km)
        ttk.Label(results_frame, text="Segment Details (Minimal Path & Distance in km):", font=('Arial', 10, 'bold')).pack(anchor='w', pady=(5, 0))
        self.segment_text = tk.Text(results_frame, height=5, wrap=tk.WORD, state=tk.DISABLED, font=('Courier', 9), relief=tk.FLAT, bg='#f0f8ff')
        self.segment_text.pack(fill='x', expand=False, pady=(3, 0)) # Reduced pady


    def draw_map(self, path_nodes):
        """Draws the entire map and highlights the calculated path."""
        self.canvas.delete("all")
        NODE_SIZE = 12

        # 1. Draw all connections (light gray roads)
        for u, v in ALL_EDGES:
            x1, y1 = NODE_POSITIONS[u]
            x2, y2 = NODE_POSITIONS[v]
            # Check if the weight is available to draw it
            weight = GRAPH[u].get(v) or GRAPH[v].get(u)
            self.canvas.create_line(x1, y1, x2, y2, fill='#cccccc', width=2)
            # Add weight label
            if weight is not None:
                mid_x, mid_y = (x1 + x2) / 2, (y1 + y2) / 2
                self.canvas.create_text(mid_x + 5, mid_y + 5, text=str(weight), fill='#999999', font=('Arial', 7))

            
        # 2. Draw the highlighted shortest path (green lines)
        for i in range(len(path_nodes) - 1):
            u = path_nodes[i]
            v = path_nodes[i+1]
            x1, y1 = NODE_POSITIONS[u]
            x2, y2 = NODE_POSITIONS[v]
            
            # Draw line with thickness and color
            self.canvas.create_line(x1, y1, x2, y2, fill='#00796b', width=4, arrow=tk.LAST, tags="path")

        # 3. Draw Nodes (Circles and Labels)
        for node_id, (x, y) in NODE_POSITIONS.items():
            color = '#333333'
            outline = 'black'
            
            if node_id == START_NODE:
                color = '#ff6666' # Red for Start
                outline = 'red'
            elif node_id in AVAILABLE_STOPS and node_id in path_nodes:
                color = '#5cb85c' # Green for Visited Stops
            elif node_id in AVAILABLE_STOPS:
                color = '#00796b' # Blue for Available Stops
                
            # Draw Node Circle
            self.canvas.create_oval(x - NODE_SIZE, y - NODE_SIZE, x + NODE_SIZE, y + NODE_SIZE, 
                                    fill=color, outline=outline, width=2)
            
            # Draw Node Label (ID)
            self.canvas.create_text(x, y, text=node_id, fill='white', font=('Arial', 8, 'bold'))

            # Draw Full Name Text
            self.canvas.create_text(x, y - NODE_SIZE - 5, text=LOCATION_NAMES[node_id], 
                                    fill='#333333', font=('Arial', 8), anchor=tk.S)


    def calculate_route(self):
        # 1. Get selected stops
        selected_stops = [
            node_id for node_id, var in self.checkbox_vars.items() if var.get()
        ]

        if not selected_stops:
            messagebox.showwarning("No Stops Selected", "Please select at least one delivery stop to calculate the route.")
            self.clear_results(initial=True)
            self.draw_map([])
            return

        # Handle too many stops for immediate calculation (TSP is NP-hard!)
        if len(selected_stops) > 6:
             messagebox.showwarning("Too Many Stops", "Selecting more than 6 stops (7 total itinerary length) can take a long time to calculate due to the nature of the Traveling Salesman Problem (TSP). Please try fewer stops.")
             return
             
        # 2. Run the algorithm
        tour_result = find_shortest_tour(START_NODE, selected_stops, GRAPH)
        
        # 3. Update the UI
        self.clear_results(initial=False)

        if tour_result:
            # Format Optimal Sequence (Major Stops)
            sequence_names = ' → '.join([LOCATION_NAMES[n] for n in tour_result['path_nodes']])
            self.sequence_label.config(text=f"Optimal Sequence: {sequence_names}", foreground='#2e7d32')

            # Format Total Distance (Always shows km)
            distance_text = f"{tour_result['distance']:.1f} km"
            self.distance_label.config(text=f"Total Minimal Distance: {distance_text}", foreground='#d32f2f')

            # Format Full Node Path (Every Node Traversed)
            full_path_text = ' → '.join(tour_result['full_path'])
            self.path_text.config(state=tk.NORMAL)
            self.path_text.delete('1.0', tk.END)
            self.path_text.insert(tk.END, full_path_text)
            self.path_text.config(state=tk.DISABLED)
            
            # --- Format Segment Details ---
            segment_output = []
            for i, segment in enumerate(tour_result['segment_details']):
                # Includes distance in km for each segment
                segment_line = (
                    f"{i+1}. {segment['start']} \u2192 {segment['end']}: "
                    f"Path: {' \u2192 '.join(segment['path'])} ({segment['distance']:.1f} km)"
                )
                segment_output.append(segment_line)
            
            final_segment_text = '\n'.join(segment_output)

            self.segment_text.config(state=tk.NORMAL)
            self.segment_text.delete('1.0', tk.END)
            self.segment_text.insert(tk.END, final_segment_text)
            self.segment_text.config(state=tk.DISABLED)
            # ------------------------------

            # DRAW MAP WITH PATH
            self.draw_map(tour_result['full_path'])
            
            # Force UI update to ensure results appear immediately after calculation
            self.master.update_idletasks()
            
        else:
            messagebox.showerror("Path Error", "Could not find a valid tour connecting all selected stops. Check if all stops are reachable.")
            self.clear_results(initial=True)
            self.draw_map([])
            

    def clear_results(self, initial=False):
        """Resets the results display."""
        if initial:
            self.sequence_label.config(text="Optimal Sequence: Select Stops", foreground='#757575')
            self.distance_label.config(text="Total Distance: 0.0 km", foreground='#757575')
        else:
            self.sequence_label.config(text="Optimal Sequence: Calculating...", foreground='#757575')
            self.distance_label.config(text="Total Distance: ...", foreground='#757575')

        self.path_text.config(state=tk.NORMAL)
        self.path_text.delete('1.0', tk.END)
        self.path_text.config(state=tk.DISABLED)
        
        self.segment_text.config(state=tk.NORMAL)
        self.segment_text.delete('1.0', tk.END)
        self.segment_text.config(state=tk.DISABLED)


if __name__ == "__main__":
    root = tk.Tk()
    app = DeliveryPlannerApp(root)
    root.mainloop()
