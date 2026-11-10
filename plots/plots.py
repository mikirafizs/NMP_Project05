import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("data/lambda_values.csv", delimiter=",")
k = data[:, 0].astype(int)
it = data[:, 1]
lam = data[:, 2]

colors = ["black", "red", "blue", "magenta", "green", "tab:cyan"]

fig, ax = plt.subplots(figsize=(6, 4.5))
for idx in np.unique(k):
    mask = k == idx
    ax.plot(it[mask], lam[mask], "o-", ms=3, lw=1,
            color=colors[idx], label=rf"$\lambda_{{{idx}}}$")

ax.set_xlabel("iteration")
ax.set_ylabel(r"$\lambda$")
ax.set_title(r"matrix $A_{6\times 6}$")
ax.set_ylim(-4, 0)
ax.legend(loc="upper right")
ax.grid(alpha=0.3)

fig.savefig("plots/eigenvalues.png", dpi=200, bbox_inches="tight")
fig.savefig("plots/eigenvalues.pdf", bbox_inches="tight")
