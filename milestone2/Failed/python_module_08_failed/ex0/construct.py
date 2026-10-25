#!/usr/bin/env python3
import site
import sys


def construct():
    """
Authorized: sys, os, site modules, print()
sys.base_prefix and sys.prefix both will be the same when in global
sys.base_prefix is the global env
sys.prefix will differ when in virtual env
In sys.getsitepackages() you can see your installed packages in your venv
    """
    base_prefix = sys.base_prefix
    prefix = sys.prefix
    virtual = sys.prefix.split("/")
    print("\nMATRIX STATUS: ", end="")
    if base_prefix != prefix:
        site_package = site.getsitepackages()[0]
        print("Welcome to the construct\n")
        print(f"Current Python: {sys.executable}")
        print(f"Virtual Environment: {virtual[len(virtual) - 1]}")
        print(f"Environment Path: {prefix}")
        print("SUCCESS: You're in an isolated environment!\n"
              "Safe to install packages without affecting\n"
              "the global system.\n")
        print("Package installation path:")
        print(site_package)
    else:
        print("You're still plugged in\n")
        print("Virtual Environment: None detected\n"
              "WARNING: You're in the global environment!\n"
              "The machines can see everything you install.\n"
              "\nTo enter the construct, run:\n"
              "python -m venv matrix_env\n"
              "source matrix_env/bin/activate # On Unix\n"
              "matrix_env\\Scripts\\activate # On Windows\n"
              "\nThen run this program again.")


if __name__ == "__main__":
    construct()
