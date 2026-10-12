#!/usr/bin/env python3
import importlib


def loading() -> None:
    """
Authorized: pandas, requests, matplotlib, numpy, sys, importlib
First use importlib.import_module(name) to test whether the
 packages can be imported, why use importlib because it can
 take a list of string to test the packages needed.
After every package is installed, then import them.
Use the packages as suggested.
numpy.random.rand(1000) to generate numbers.
pandas.Series() to create instance using data generated.
Then do instance.sort_values().reset_index(drop=True) to sort and
 reset the index came with the numpy.
plt.plot('sorted values') and plt.savefig('output_file') to plot
 and save to desired file name.


    """
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

        print("\nAnalyzing Matrix data...")
        datapoints = numpy.random.rand(1000)
        print("Processing 1000 data points...")
        series = pandas.Series(datapoints)
        series = series.sort_values().reset_index(drop=True)
        print("Generating visualization...")
        plt.plot(series)
        response = requests.get("https://api.github.com")
        requests.get
        print(f"Requesting API, code: {response.status_code}...")
        print("\nAnalysis completed!")
        print("Results saved to: matrix_analysis.png")
        plt.savefig("matrix_analysis.png")


if __name__ == "__main__":
    loading()
