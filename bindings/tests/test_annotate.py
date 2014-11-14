import coverage
import os
import glob


def mark_visual(code):

	content = code.split("\n")
	for r in reversed(coverage.annotate(code)):
		mark(content, r.visual)

	return "\n".join(content)


def mark_marker(data):
	content = code.split("\n")
	for r in reversed(coverage.annotate(code)):
		mark(content, r.marker)

	return "\n".join(content)


def mark(content, r):
	marker = r
	line = content[marker.end.line]
	line = line[:marker.end.column] + "]" + line[marker.end.column:]
	content[marker.end.line] = line

	line = content[marker.start.line]
	line = line[:marker.start.column] + "[" + line[marker.start.column:]
	content[marker.start.line] = line


def sources():
	path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "data")
	for source in glob.glob("{0}/*.cpp".format(path)):
		if "expected" not in source:
			yield source, "{0}.expected.cpp".format("".join(source.split(".")[:-1]))


def test_sources():
	for src, expected in sources():
		with open(src, 'r') as fs:
			with open(expected, 'r') as fe:
				assert mark_visual(fs.read()) == fe.read()
