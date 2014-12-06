import os


def which(tool):
    """ return the absolute path to the tool """
    for path in os.environ['PATH'].split(os.pathsep):
        p = os.path.join(path, tool)
        if os.path.exists(p):
            return os.path.abspath(p)
    return None


def test_tool_works():
    assert which("coverage")
