import coverage

code = """
int main() {
#define MY_DEFINE 1 and 2
extern bool get_result();

	if(true or false) {
		return 1;
	}
	else {
		return 0;
	}
	if(int i = 0)
		return 2;
	if(int i = 0 && true)
		return 3;
	if(false ? false : true && true)
		return 4;
	if(MY_DEFINE) {
		return 5;
	}
	if(MY_DEFINE and \
	1 != 2)
	  if(MY_DEFINE and (
			2 != 2))
			return 7;
	if((((true))))
		return 8;
	if(not get_result()) {
		return 9;
	}
}
"""


def mark(content, r):
	marker = r
	line = content[marker.end.line]
	line = line[:marker.end.column] + "]" + line[marker.end.column:]
	content[marker.end.line] = line

	line = content[marker.start.line]
	line = line[:marker.start.column] + "[" + line[marker.start.column:]
	content[marker.start.line] = line

def dump(text, ranges):
	content = text.split("\n")
	for r in reversed(ranges):
		mark(content, r)

	return "\n".join(content)


def test_simple():

	res = coverage.annotate(code)
	assert len(res) == 9
	assert all(r.name == 'if' for r in res)
	print repr([repr(r) for r in res])
	assert False

	assert all([r.visual == r.marker for r in res])

	print(dump(code, [r.visual for r in res]))
	assert True
