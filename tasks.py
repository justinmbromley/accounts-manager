from invoke import task

@task
def test(c):
    c.run("pytest")

@task
def lint(c):
    c.run("ruff check .")

@task
def test_short(c):
    c.run("pytest --tb=line")
