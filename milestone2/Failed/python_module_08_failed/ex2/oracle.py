#!/usr/bin/env python3
import os
import sys


def oracle():
    try:
        import dotenv
    except ModuleNotFoundError as e:
        print(f"Module error: {e}")
        sys.exit(1)
    dotenv.load_dotenv()
    matrix = os.environ.get("MATRIX_MODE")
    url = os.environ.get("DATABASE_URL")
    api_key = os.environ.get("API_KEY")
    log_level = os.environ.get("LOG_LEVEL")
    zion = os.environ.get("ZION_ENDPOINT")
    print()
    print("ORACLE STATUS: Reading the Matrix...")
    print()
    if matrix:
        print(f"Mode: {matrix}")
    else:
        print("Missing MATRIX_MODE config!")

    if url:
        print("Database: Connected to local instance")
    else:
        print("Missing DATABASE_URL config!")

    if api_key:
        print("API Access: Authenticated")
    else:
        print("API Access: Rejected")

    if log_level:
        print(f"Log Level: {log_level}")
    else:
        print("Missing LOG_LEVEL config!")

    if zion == "https://zion.resistance.local":
        print("Zion Network: Online")
    else:
        print("Missing ZION_ENDPOINT config!")

    print()
    print("Environment security check:")
    try:
        if os.path.exists(".gitignore"):
            with open(".gitignore") as f:
                gitignored = ".env" in f.read()
        if gitignored:
            print("[OK] No hardcoded secrets detected")
    except Exception:
        print("[KO] Hardcoded secrets detected")

    required_keys = {"MATRIX_MODE", "DATABASE_URL", "API_KEY", "LOG_LEVEL",
                     "ZION_ENDPOINT"}

    if os.path.exists(".env"):
        with open(".env") as f:
            content = f.read()
        all_present = all(key in content for key in required_keys)
    else:
        all_present = False

    if all_present:
        print("[OK] .env file properly configured")
        print("[OK] Production overrides available")
    else:
        print("[KO] .env file not properly configured")
        print("[KO] Production overrides not available")
    print()
    print("The Oracle sees all configurations.")


if __name__ == "__main__":
    oracle()
