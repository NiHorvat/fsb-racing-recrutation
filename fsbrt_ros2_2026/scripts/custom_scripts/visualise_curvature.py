#!/usr/bin/env python3
"""
Visualise a path from a CSV file, coloured by curvature.

CSV format (one point per row):
    x, y, curvature

A header row is detected and skipped automatically. Comma, semicolon,
tab and whitespace delimiters are all accepted.

Usage:
    python plot_curvature.py path.csv
    python plot_curvature.py path.csv --cmap viridis --save out.png
    python plot_curvature.py path.csv --abs        # colour by |curvature|
    python plot_curvature.py path.csv --subplot    # also plot curvature vs arc length
"""

import argparse
import csv
import sys

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
from matplotlib.colors import Normalize, TwoSlopeNorm


def load_csv(path):
    with open(path, newline="") as f:
        sample = f.read(4096)
        f.seek(0)
        try:
            dialect = csv.Sniffer().sniff(sample, delimiters=",;\t ")
        except csv.Error:
            dialect = csv.excel

        rows = []
        for row in csv.reader(f, dialect):
            vals = [v.strip() for v in row if v.strip() != ""]
            if len(vals) < 3:
                continue
            try:
                rows.append([float(vals[0]), float(vals[1]), float(vals[2])])
            except ValueError:
                continue  # header or malformed row

    if not rows:
        sys.exit(f"No valid (x, y, curvature) rows found in {path}")

    data = np.asarray(rows)
    return data[:, 0], data[:, 1], data[:, 2]


def main():
    ap = argparse.ArgumentParser(description="Plot an x,y path coloured by curvature.")
    ap.add_argument("csv", help="input CSV file (x, y, curvature)")
    ap.add_argument("--cmap", default=None,
                    help="matplotlib colormap (default: coolwarm for signed, viridis for --abs)")
    ap.add_argument("--abs", action="store_true", help="colour by absolute curvature")
    ap.add_argument("--linewidth", type=float, default=3.0)
    ap.add_argument("--points", action="store_true", help="also draw the raw points")
    ap.add_argument("--subplot", action="store_true",
                    help="add a second plot of curvature vs. arc length")
    ap.add_argument("--save", metavar="FILE", help="save figure instead of only showing it")
    args = ap.parse_args()

    x, y, k = load_csv(args.csv)
    if args.abs:
        k = np.abs(k)

    # Segments between consecutive points; each segment coloured by mean curvature
    pts = np.column_stack([x, y]).reshape(-1, 1, 2)
    segments = np.concatenate([pts[:-1], pts[1:]], axis=1)
    seg_k = 0.5 * (k[:-1] + k[1:])

    # Diverging colormap centred on 0 when curvature changes sign
    kmin, kmax = float(k.min()), float(k.max())
    if kmin < 0 < kmax:
        norm = TwoSlopeNorm(vmin=kmin, vcenter=0.0, vmax=kmax)
        cmap = args.cmap or "coolwarm"
    else:
        norm = Normalize(vmin=kmin, vmax=kmax if kmax > kmin else kmin + 1e-9)
        cmap = args.cmap or "viridis"

    if args.subplot:
        fig, (ax, ax2) = plt.subplots(1, 2, figsize=(14, 6),
                                      gridspec_kw={"width_ratios": [1.3, 1]})
    else:
        fig, ax = plt.subplots(figsize=(9, 7))

    lc = LineCollection(segments, cmap=cmap, norm=norm, linewidth=args.linewidth)
    lc.set_array(seg_k)
    ax.add_collection(lc)

    if args.points:
        ax.scatter(x, y, c=k, cmap=cmap, norm=norm, s=10, zorder=3, edgecolors="none")

    ax.plot(x[0], y[0], "o", color="green", markersize=8, label="start", zorder=4)
    ax.plot(x[-1], y[-1], "s", color="black", markersize=8, label="end", zorder=4)

    ax.autoscale()
    ax.set_aspect("equal", adjustable="datalim")
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_title(f"Path coloured by {'|curvature|' if args.abs else 'curvature'}")
    ax.grid(True, alpha=0.3)
    ax.legend(loc="best")
    fig.colorbar(lc, ax=ax, label="|κ|" if args.abs else "κ")

    if args.subplot:
        s = np.concatenate([[0.0], np.cumsum(np.hypot(np.diff(x), np.diff(y)))])
        ax2.plot(s, k, color="tab:blue")
        ax2.axhline(0, color="gray", linewidth=0.8)
        ax2.set_xlabel("arc length s")
        ax2.set_ylabel("|κ|" if args.abs else "κ")
        ax2.set_title("Curvature along path")
        ax2.grid(True, alpha=0.3)

    fig.tight_layout()
    if args.save:
        fig.savefig(args.save, dpi=150)
        print(f"Saved to {args.save}")
    plt.show()


if __name__ == "__main__":
    main()