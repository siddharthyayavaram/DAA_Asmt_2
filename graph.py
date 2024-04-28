import matplotlib.pyplot as plt

def plot_graph(x, y, title, x_label, y_label):
    plt.plot(x, y)
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    # plt.show()

if __name__ == "__main__":
    y = [0.01, 1.466, 11.603, 54.045,172.928, 743.773,2617.650, 6683.985]
    x = [10, 50, 100, 200, 300, 500, 750, 1000]
    plot_graph(x, y, "Timing Analysis", "Sequence Length", "Time Taken (ms)")
    plt.savefig("graph.png")