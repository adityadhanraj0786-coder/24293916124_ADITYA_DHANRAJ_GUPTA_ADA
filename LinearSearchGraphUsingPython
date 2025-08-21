import matplotlib.pyplot as plt

# Data points: Number of elements vs Time taken
n_values = [1000,1500, 3000, 5000, 7000,8500,9500, 10000,12000,15000]
time_values = [0.011000,0.018000,0.034000 , 0.053000,0.064000 , 0.097000, 0.091000 ,0.102000,0.113000, 0.140000]  # in seconds

# Create the plot
plt.figure(figsize=(10, 6))  # Set figure size for better visibility
plt.plot(n_values, time_values, marker='o', linewidth=2, markersize=8, color='blue')

# Add titles and labels
plt.title("Linear Search: Time vs Number of Elements", fontsize=16, fontweight='bold')
plt.xlabel("Number of Elements (n)", fontsize=12)
plt.ylabel("Time Taken (seconds)", fontsize=12)

# Add grid for better readability
plt.grid(True, alpha=0.3)

# Format the axes
plt.ticklabel_format(style='scientific', axis='y', scilimits=(0,0))  # Scientific notation for y-axis
plt.tight_layout()  # Adjust layout to prevent label cutoff

# Show the plot
plt.show()

# Optional: Save the plot
# plt.savefig('linear_search_performance.png', dpi=300, bbox_inches='tight')
