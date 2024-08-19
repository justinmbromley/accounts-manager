from invoke import task

@task
def test(c):
    c.run("pytest -s -v", pty=True)

@task
def lint(c):
    c.run("ruff check .", pty=True)

@task
def lint_fix(c):
    c.run("ruff check --fix .", pty=True)

@task
def test_short(c):
    c.run("pytest --tb=line", pty=True)
