import tkinter as tk
from tkinter import messagebox, simpledialog

class FoodDeliveryRouting:
    def __init__(self, root):
        self.root = root
        self.root.title("Food Delivery Routing (BFS)")
        self.graph = {}  # Adjacency List
        self.restaurant = "Restaurant"
        self.customer_location = None

        # Add restaurant node initially
        self.graph[self.restaurant] = []

        # UI Buttons
        tk.Button(root, text="Add Location", width=25, command=self.add_location).pack(pady=5)
        tk.Button(root, text="Add Road (2-way)", width=25, command=self.add_road).pack(pady=5)
        tk.Button(root, text="Set Customer Location", width=25, command=self.set_customer_location).pack(pady=5)
        tk.Button(root, text="Find Shortest Route", width=25, command=self.find_route).pack(pady=5)

        self.output = tk.Text(root, height=12, width=50)
        self.output.pack(pady=10)

    def add_location(self):
        location = simpledialog.askstring("Add Location", "Enter new location name:")
        if location:
            if location in self.graph:
                messagebox.showerror("Error", "Location already exists!")
            else:
                self.graph[location] = []
                self.output.insert(tk.END, f"Location added: {location}\n")

    def add_road(self):
        loc1 = simpledialog.askstring("Add Road", "Enter first location:")
        loc2 = simpledialog.askstring("Add Road", "Enter second location:")

        if not loc1 or not loc2:
            return

        if loc1 not in self.graph or loc2 not in self.graph:
            messagebox.showerror("Error", "One or both locations do not exist!")
            return

        # Undirected Road
        self.graph[loc1].append(loc2)
        self.graph[loc2].append(loc1)

        self.output.insert(tk.END, f"Road added: {loc1} ↔ {loc2}\n")

    def set_customer_location(self):
        location = simpledialog.askstring("Set Customer", "Customer lives at (location name):")
        if location in self.graph:
            self.customer_location = location
            self.output.insert(tk.END, f"Customer location set: {location}\n")
        else:
            messagebox.showerror("Error", "Location does not exist! Add it first.")

    def bfs(self, start, goal):
        visited = set()
        queue = [[start]]

        while queue:
            path = queue.pop(0)
            node = path[-1]

            if node == goal:
                return path

            if node not in visited:
                visited.add(node)
                for neighbor in self.graph[node]:
                    new_path = list(path)
                    new_path.append(neighbor)
                    queue.append(new_path)
        return None

    def find_route(self):
        if not self.customer_location:
            messagebox.showerror("Error", "Set customer location first!")
            return

        route = self.bfs(self.restaurant, self.customer_location)

        self.output.insert(tk.END, "\n--- Route Result ---\n")

        if route:
            path_str = " → ".join(route)
            self.output.insert(tk.END, f"Shortest Route (BFS): {path_str}\n")
            self.output.insert(tk.END, f"Visual Path:\n{' - '.join(route)}\n")
        else:
            self.output.insert(tk.END, "No route found!\n")


root = tk.Tk()
app = FoodDeliveryRouting(root)
root.mainloop()
