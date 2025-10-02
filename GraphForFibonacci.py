import matplotlib.pyplot as plt
# X-axis (n values you tested)
n_values = [10,20,30,40,50]
# Execution times in seconds
recursive_time = [0.000001400,0.000102000,0.008230200,0.878120100,146.084184500]
memoization_time = [0.000000900,0.000000800,0.000001100,0.000000700,0.000001700]
iterative_time = [0.000000200,0.000000500,0.000000500,0.000000600,0.000000400]
bottom_up_time = [0.000000700,0.000000700,0.000000500,0.000000900,0.000000600]
# --- First Graph: Full Range (includes recursive) ---
plt.figure(figsize=(8, 5))
plt.plot(n_values, recursive_time, label=&quot;Recursive&quot;, color=&quot;red&quot;, marker=&quot;o&quot;)
plt.plot(n_values, memoization_time, label=&quot;Memoization&quot;, color=&quot;blue&quot;, marker=&quot;s&quot;)
plt.plot(n_values, iterative_time, label=&quot;Iterative&quot;, color=&quot;green&quot;, marker=&quot;^&quot;)
plt.plot(n_values, bottom_up_time, label=&quot;Bottom-Up&quot;, color=&quot;purple&quot;, marker=&quot;D&quot;)
plt.xlabel(&quot;n (Fibonacci Number Index)&quot;)
plt.ylabel(&quot;Execution Time (seconds)&quot;)
plt.title(&quot;Fibonacci Computation: n vs Execution Time (Full Range)&quot;)
plt.legend()
plt.grid(True)
plt.show()
# --- Second Graph: Zoomed In (Exclude recursive for clarity) ---
plt.figure(figsize=(8, 5))
plt.plot(n_values, memoization_time, label=&quot;Memoization&quot;, color=&quot;blue&quot;, marker=&quot;s&quot;)
plt.plot(n_values, iterative_time, label=&quot;Iterative&quot;, color=&quot;green&quot;, marker=&quot;^&quot;)
plt.plot(n_values, bottom_up_time, label=&quot;Bottom-Up&quot;, color=&quot;purple&quot;, marker=&quot;D&quot;)
plt.xlabel(&quot;n (Fibonacci Number Index)&quot;)
plt.ylabel(&quot;Execution Time (seconds)&quot;)
plt.title(&quot;Fibonacci Computation: n vs Execution Time (Zoomed on DP Methods)&quot;)
plt.legend()
plt.grid(True)
plt.ylim(0, max(memoization_time + iterative_time + bottom_up_time) * 1.2) # Auto-scale just
for small times
plt.show()
