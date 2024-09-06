import subprocess

def run_tests():
    subprocess.run(["poetry", "run", "pytest", "-s", "-v"])

def run_tests_short():
    subprocess.run(["poetry", "run", "pytest", "--tb=line"])

def run_lint():
    subprocess.run(["poetry", "run", "ruff", "check", "."])

def run_lint_fix():
    subprocess.run(["poetry", "run", "ruff", "check", "--fix", "."])

if __name__ == "__main__":
    run_tests()
