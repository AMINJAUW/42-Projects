import os

def print_env_variables():
    for key, value in os.environ.items():
        print(f"{key}: {value}")

print("\r")
print_env_variables()
