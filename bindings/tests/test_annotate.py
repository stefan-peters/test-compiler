import coverage

code = """
int main() {
#ifndef DISABLE_BRANCH
	if(true) {
		return 1;
	}
	else {
		return 2;
	}
#else
	return 3;
#endif
}
"""

def test_simple():

	coverage.annotate(code)
	assert True

def test_with_parameter():

	res = coverage.annotate(code, ['-DDISABLE_BRANCH'])
	assert len(res) == 1
	assert res[0].name == 'if'
