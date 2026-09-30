import importlib
import sys


if __name__ == "__main__":
    modulelist = ["pandas", "numpy", "requests", "matplotlib"]
    print("\nLOADING STATUS: Loading programs...")
    print("\nChecking dependencies:")
    mode: int = 0

    for n in modulelist:
        try:
            modulestring = importlib.import_module(n)
            print(f"[OK] {modulestring.__name__} "
                  f"({modulestring.__version__})",
                  end="")
            if n == "pandas":
                print(" - Data manipulation ready")
                mode += 1
            elif n == "numpy":
                print(" - Numerical computation ready")
                mode += 1
            elif n == "requests":
                print(" - Network access ready")
                mode += 1
            elif n == "matplotlib":
                print(" - Visualization ready")
                mode += 1
        except ImportError as e:
            print(f"[KO] {e}")

    if mode == 4:
        import pandas
        import numpy
        import requests
        import matplotlib.pyplot as plt
        print()
        print(sys.base_prefix)
        print(sys.prefix)
        print(sys.executable)

        print("\nAnalyzing Matrix data...")
        datapoints = numpy.random.rand(1000)
        print("Processing 1000 data points...")
        series = pandas.Series(datapoints)
        series = series.sort_values().reset_index(drop=True)
        print("Generating visualization...")
        plt.plot(series)
        print("\nResults saved to: matrix_analysis.png")
        plt.savefig("matrix_analysis.png")
        response = requests.get("https://api.github.com")
