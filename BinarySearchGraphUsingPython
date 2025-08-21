import matplotlib.pyplot as plt

# Data points: Replace these with your actual results from the C program
n_values = [1000, 3000, 5000, 7000, 9000, 10000, 12000, 15000,17000,20000]  # Number of elements
time_values = [ 0.030000, 0.049000, 0.044000,0.038000, 0.037000, 0.041000, 0.056000, 0.051000,0.062000,0.071000 ]  # Time in seconds

# Create the graph
plt.figure(figsize=(10, 6))
plt.plot(n_values, time_values, marker='o', linewidth=2, markersize=8, color='blue')

# Add titles and labels
plt.title("Binary Search: Average Time vs Number of Elements", fontsize=16, fontweight='bold')
plt.xlabel("Number of Elements (n)", fontsize=12)
plt.ylabel("Average Time per Search (seconds)", fontsize=12)

# Add grid and formatting
plt.grid(True, alpha=0.3)
plt.ticklabel_format(style='scientific', axis='y', scilimits=(0,0))
plt.tight_layout()

# Show the graph
plt.show()
