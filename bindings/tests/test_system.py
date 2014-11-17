import coverage.system
import subprocess
import os
from mock import patch


class PopenProxy(object):

    def __init__(self, cmd):
        self.name = cmd.split(" ")[0]

    def communicate(self):
        test_path = os.path.dirname(os.path.abspath(__file__))
        file_path = "data/includes/{0}.includes.txt".format(self.name)
        path = os.path.join(test_path, file_path)
        return (open(path).read(), None)


@patch('subprocess.Popen', lambda x, **rest: PopenProxy(x))
@patch('os.path.exists', lambda x: True)
@patch('os.path.abspath', lambda x: os.path.normpath(x))
def test_system_includes_clang_cpp():

    expected = [
        '/usr/include/c++/4.8.3',
        '/usr/include/c++/4.8.3/x86_64-redhat-linux',
        '/usr/include/c++/4.8.3/backward',
        '/usr/local/include',
        '/usr/lib/clang/3.4/include',
        '/usr/include'
    ]
    assert coverage.system.system_includes("clang++") == expected


@patch('subprocess.Popen', lambda x, **rest: PopenProxy(x))
@patch('os.path.exists', lambda x: True)
@patch('os.path.abspath', lambda x: os.path.normpath(x))
def test_system_includes_g_cpp():

    expected = [
        '/usr/include/c++/4.8.3',
        '/usr/include/c++/4.8.3/x86_64-redhat-linux',
        '/usr/include/c++/4.8.3/backward',
        '/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include',
        '/usr/local/include',
        '/usr/include'
    ]
    assert coverage.system.system_includes("g++") == expected


@patch('subprocess.Popen', lambda x, **rest: PopenProxy(x))
@patch('os.path.exists', lambda x: True)
@patch('os.path.abspath', lambda x: os.path.normpath(x))
def test_system_includes_clang_c():

    expected = [
        '/usr/local/include',
        '/usr/lib/clang/3.4/include',
        '/usr/include'
    ]
    assert coverage.system.system_includes("clang") == expected


@patch('subprocess.Popen', lambda x, **rest: PopenProxy(x))
@patch('os.path.exists', lambda x: True)
@patch('os.path.abspath', lambda x: os.path.normpath(x))
def test_system_includes_gcc():

    expected = [
        '/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include',
        '/usr/local/include',
        '/usr/include'
    ]
    assert coverage.system.system_includes("gcc") == expected
