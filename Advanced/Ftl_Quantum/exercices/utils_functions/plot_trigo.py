import matplotlib.pyplot as plt
import numpy as np

def plot_multiple_angles_with_probabilities(theta):
    # Create a figure and axis
    fig, ax = plt.subplots(figsize=(6, 6))
    
    # Draw the unit circle
    circle = plt.Circle((0, 0), 1, color='lightgray', fill=False, linewidth=2)
    ax.add_artist(circle)
    
    # Plot the x and y axes
    ax.axhline(0, color='gray', linewidth=0.5)
    ax.axvline(0, color='gray', linewidth=0.5)
    
    # Variables for tracking multiples of theta
    t = 0
    angle = (2 * t + 1) * theta

    # Loop to draw angles until the angle is less than π
    while angle < np.pi:
        # Calculate coordinates for the current angle
        x = np.cos(angle)
        y = np.sin(angle)
        
        # Calculate probability P(A₁) = sin^2(angle)
        probability = np.sin(angle) ** 2
        
        # Plot the angle line and the point on the unit circle with dashed lines
        ax.plot([0, x], [0, y], color='blue', linewidth=1.5, linestyle='--', alpha=0.6)
        ax.scatter(x, y, color='red')
        
        # Annotate with t value and probability
        ax.text(x * 1.05, y * 1.05, f't = {t}', fontsize=12, ha='center')
        ax.text(x * 1.05, y * 1.05 - 0.1, f'P(A₁) = {probability:.2f}', fontsize=10, ha='center', color='purple')
        
        # Prepare for the next iteration
        t += 1
        angle = (2 * t + 1) * theta

    # Annotate the initial angle θ
    ax.text(0.1, -0.1, f"θ = {theta:.6f} rad", fontsize=12)
    
    # Set axis limits and aspect ratio
    ax.set_xlim(-1.2, 1.2)
    ax.set_ylim(-1.2, 1.2)
    ax.set_aspect('equal')
    
    # Add grid and title
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.title(f"Unit Circle with Odd Multiples of θ = {theta:.6f} radians")
    plt.xlabel("x")
    plt.ylabel("y")
    
    plt.show()