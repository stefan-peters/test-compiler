import coverage
import os
import glob
import coverage.system
import itertools
from difflib import ndiff
from functools import partial
import pytest


def mark(code, get):

	content = code.split("\n")
	includes = coverage.system.system_includes("g++")
	include_args = ["-I{0}".format(path) for path in includes]

	for r in reversed(coverage.annotate(code, include_args)):
		marker = get(r)
		line = content[marker.end.line]
		line = line[:marker.end.column] + "]" + line[marker.end.column:]
		content[marker.end.line] = line

		line = content[marker.start.line]
		line = line[:marker.start.column] + "[" + line[marker.start.column:]
		content[marker.start.line] = line

	return "\n".join(content)


def path(name):
	base_path = os.path.dirname(os.path.abspath(__file__))
	path = os.path.join(base_path, "data/sources")
	return os.path.join(path, name)


def source_pair(name, marker):
	source_name = "{0}.original.cpp".format(name)
	expected_name = "{0}.expected.{1}.cpp".format(name, marker)
	return (path(source_name), path(expected_name))


parameter = itertools.product(['visual', 'marker'], [
	"conditional_branch",
	"for_branch",
	"if_branch",
	"while_branch"
])


@pytest.mark.parametrize("marker, name", parameter)
def test_visual_annotation(marker, name):
	(orignal_file, expected_file) = source_pair(name, marker)

	with open(orignal_file, 'r') as fs:
		with open(expected_file, 'r') as fe:
			original = fs.read()
			expected = fe.read()
			generated = mark(original, lambda x: getattr(x, marker))
			diff = ndiff(expected.split("\n"), generated.split("\n"))
			assert generated == expected, "\n".join(diff)
