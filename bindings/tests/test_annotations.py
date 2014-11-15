import coverage
import os
import glob
from difflib import ndiff
from functools import partial


def mark(code, get):

	content = code.split("\n")
	for r in reversed(coverage.annotate(code)):
		marker = get(r)
		line = content[marker.end.line]
		line = line[:marker.end.column] + "]" + line[marker.end.column:]
		content[marker.end.line] = line

		line = content[marker.start.line]
		line = line[:marker.start.column] + "[" + line[marker.start.column:]
		content[marker.start.line] = line

	return "\n".join(content)


def sources(name):
	""" read all sources from the data directory
		as a pair (source, expected-source)"""
	path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "data")
	for source in glob.glob("{0}/*.cpp".format(path)):
		if "expected" not in source:
			base = "".join(source.split(".")[:-2])
			yield source, "{0}.expected.{1}.cpp".format(base, name)


def run_tests(invoker, name):
	for orignal_file, expected_file in sources(name):
		with open(orignal_file, 'r') as fs:
			with open(expected_file, 'r') as fe:
				original = fs.read()
				expected = fe.read()
				generated = invoker(original)
				diff = ndiff(expected.split("\n"), generated.split("\n"))

				assert generated == expected, "\n".join(diff)


def test_visual_annotation():
	run_tests(partial(mark, get=lambda x: x.visual), 'visual')


def test_marker_annotation():
	run_tests(partial(mark, get=lambda x: x.marker), 'marker')
