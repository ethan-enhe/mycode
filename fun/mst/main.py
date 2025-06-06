import numpy as np
from scipy.optimize import minimize
from scipy.sparse.csgraph import minimum_spanning_tree
import matplotlib.pyplot as plt

# 用户配置区
terminals = np.array([[0, 0], [2, 3], [4, 1], [5, 4]])  # 4个终端点
steiner_count = 2
connections = [
    ("S0", "A"),
    ("S0", "B"),
    ("S0", "S1"),
    ("S1", "C"),
    ("S1", "D"),
]

# 自动生成节点映射表
letters = [chr(65 + i) for i in range(len(terminals))]
node_map = {letter: i for i, letter in enumerate(letters)}
node_map.update({f"S{i}": i + len(terminals) for i in range(steiner_count)})


def total_length(x):
    """计算Steiner树总长度"""
    steiner_pts = x.reshape(steiner_count, 2)
    all_points = np.vstack([terminals, steiner_pts])
    L = 0.0
    for n1, n2 in connections:
        i1 = node_map[n1] if isinstance(n1, str) else n1
        i2 = node_map[n2] if isinstance(n2, str) else n2
        L += np.linalg.norm(all_points[i1] - all_points[i2])
    return L


# 计算最小生成树(MST)
def compute_mst():
    dist_matrix = np.zeros((len(terminals), len(terminals)))
    for i in range(len(terminals)):
        for j in range(len(terminals)):
            dist_matrix[i, j] = np.linalg.norm(terminals[i] - terminals[j])
    mst = minimum_spanning_tree(dist_matrix)
    return mst


mst = compute_mst()
mst_edges = np.transpose(mst.nonzero())
mst_length = mst.sum()

# 优化Steiner树
initial_guess = np.random.uniform(
    low=terminals.min(0), high=terminals.max(0), size=(steiner_count, 2)
).flatten()
res = minimize(total_length, initial_guess, method="L-BFGS-B")
optimized_steiner = res.x.reshape(steiner_count, 2)
steiner_length = res.fun

# 可视化
plt.figure(figsize=(12, 8))
ax = plt.gca()

# 绘制终端点和Steiner点
plt.scatter(
    terminals[:, 0], terminals[:, 1], c="red", s=100, label="Terminals", zorder=4
)
plt.scatter(
    optimized_steiner[:, 0],
    optimized_steiner[:, 1],
    c="blue",
    s=100,
    label="Steiner Points",
    zorder=4,
)

# 绘制Steiner树连接
all_points = np.vstack([terminals, optimized_steiner])
for n1, n2 in connections:
    i1 = node_map[n1] if isinstance(n1, str) else n1
    i2 = node_map[n2] if isinstance(n2, str) else n2
    pts = all_points[[i1, i2]]
    plt.plot(pts[:, 0], pts[:, 1], "k-", lw=3, zorder=2, label="Steiner Tree")

# 绘制MST连接
for i, j in mst_edges:
    plt.plot(
        [terminals[i][0], terminals[j][0]],
        [terminals[i][1], terminals[j][1]],
        "r--",
        lw=2,
        zorder=1,
        label="MST",
    )

# 添加标注信息
ratio = steiner_length / mst_length
info_text = (
    f"MST Length: {mst_length:.4f}\n"
    f"Steiner Length: {steiner_length:.4f}\n"
    f"Ratio (S/M): {ratio:.4f}\n"
    f"√3/2 ≈ {np.sqrt(3)/2:.4f}"
)
plt.text(
    0.05,
    0.95,
    info_text,
    transform=ax.transAxes,
    verticalalignment="top",
    bbox=dict(facecolor="white", alpha=0.9),
)

# 图表设置
plt.title(f"Steiner Tree vs MST Comparison (n={len(terminals)})")
handles, labels = plt.gca().get_legend_handles_labels()
by_label = dict(zip(labels, handles))  # 去除重复图例
plt.legend(by_label.values(), by_label.keys(), loc="lower right")
plt.axis("equal")
plt.grid(True)
plt.tight_layout()
plt.show()
