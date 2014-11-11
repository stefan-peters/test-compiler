import coverage

code = """
int main() {
#ifndef DISABLE_BRANCH
	if(true or false) {
		return 1;
	}
	else {
		return 2;
	}
	if(int i = 0)
		return 4;
#else
	return 3;
#endif
}
"""


def dump(text, range):
	content = text.split("\n")

	line = content[range.end.line]
	line = line[:range.end.column] + "]" + line[range.end.column:]
	content[range.end.line] = line

	line = content[range.start.line]
	line = line[:range.start.column] + "[" + line[range.start.column:]
	content[range.start.line] = line

	return "\n".join(content)


def test_simple():

	res = coverage.annotate(code)
	assert len(res) == 2
	assert res[0].name == 'if'
	print(dump(code, res[0].visual))
	print(dump(code, res[1].visual))
	assert False


def test_with_parameter():
	res = coverage.annotate(code, ['-DDISABLE_BRANCH'])
	assert len(res) == 0
