import matplotlib.pyplot as plt

# Flexible X-axis
matrix_sizes = [128, 256, 512, 1024, 2048]

# Execution times in seconds
iterative_time = [0.021000,0.069000, 0.441000, 5.464000, 87.297000]
strassen_time = [0.122000, 0.403000, 2.571000, 18.016000, 125.940000]  # Example corrected values
divide_conquer_time = [0.086000, 0.579000, 4.269000, 33.616000, 291.792000]  # Example third method

# Plot all three variables
plt.plot(matrix_sizes, iterative_time, label="Iterative Method (s)", color="blue", marker="o")
plt.plot(matrix_sizes, strassen_time, label="Strassen Method (s)", color="red", marker="s")
plt.plot(matrix_sizes, divide_conquer_time, label="Divide & Conquer (s)", color="green", marker="^")

# Labels and title
plt.xlabel("Matrix Size (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("Comparison of Matrix Multiplication Methods")
plt.legend()
plt.grid(True)

# Show the graph
plt.show()
